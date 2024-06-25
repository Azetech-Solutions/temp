using System;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using static File_TryAccess_Tool.Xmlfilehandling;
using static File_TryAccess_Tool.Tooltransmit;
using System.Collections.Generic;
using System.Runtime.Remoting.Metadata.W3cXsd2001;

namespace File_TryAccess_Tool
{
    public class Hexfilehandling
    {
        GetHexfileValue Hexval;
        public Hexfilehandling() { Hexval = new GetHexfileValue(); }

        public string Filepath = null;
        private string Fileline = null;
        private byte[] HexData = new byte[16];
        private ushort hexOffset, flashBaseAddress;
        private byte hexDatelength, hexRecordType; // these variables are used to store the Hexfile data's
        private uint hexCKsum = 0;

        private enum DataIndex
        {
            Unknown = 0,
            DatalengthIndex = 1,
            DataOffsetIndex = 3,
            RecordTypeIndex = 7,
            DataIndex = 9,
        }

        public bool Hexfileverify(OpenFileDialog ofd)
        {
            bool retval = false;
            string checkFileValid = null;
            //path save in a string to open the particular file
            Filepath = ofd.FileName;
            StreamReader sr = new StreamReader(Filepath);

            if ((checkFileValid = sr.ReadLine()) != null)
            {
                if (checkFileValid[0] == ':')
                {
                    retval = true;
                }
                else { MessageBox.Show("Invalid File Format", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }
            sr.Close();
            return retval;
        }

        public bool Flashstartcommands(UInt32 address)
        {
            bool retval = false, startcommandflag = true;
            byte[] dataUpdate = new byte[5];
            dataUpdate[0] = Commands.Flashstart;

            Log.Message("FlashStart");
            while (true)
            {
                if (startcommandflag == true)
                {
                    FlashDatabytesupdate(dataUpdate);

                    MCUTransmitFunction.Transmit(FlashDataTransmit);
                    startcommandflag = false;
                }

                if (MCUStatusRxData[0] == Commands.Responce_OK)
                {
                    MCUStatusRxData[0] = 0xFF; // Reset

                    if (dataUpdate[0] == Commands.Flashstart)
                    {
                        dataUpdate[0] = Commands.ChooseFlashMode;
                        startcommandflag = true;
                    }
                    else
                    {
                        if (dataUpdate[0] == Commands.Flasherase)
                        {
                            retval = true;
                            break;
                        }

                        if (dataUpdate[0] == Commands.ChooseFlashMode)
                        {
                            dataUpdate[0] = Commands.Flasherase;
                            dataUpdate[1] = (byte)(address >> 24);
                            dataUpdate[2] = (byte)(address >> 16);
                            dataUpdate[3] = (byte)(address >> 8);
                            dataUpdate[4] = (byte)(address);
                            startcommandflag = true;
                        }
                    }
                }
                else if (MCUStatusRxData[0] == Commands.Responce_NOTOK)
                {
                    MCUStatusRxData[0] = 0xFF; // Reset
                    startcommandflag = true;
                }

            } //"while" end of the flashstart , flash mode, erase mode 

            Log.Message("FlashStart end ");
            return retval;
        }

        public bool FlashDatatransmit()
        {
            bool retval = false;

            StreamReader sr = new StreamReader(Filepath);
            hexCKsum = 0; // reset the cksum
            while ((Fileline = sr.ReadLine()) != null)
            {
                if (Fileline.Count() < 11)
                {
                    MessageBox.Show("Invalid Data", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    if (Fileline[0] == ':')
                    {
                        hexDatelength = Hexval.ReadByte_Hexfile(Fileline, (Int16)DataIndex.DatalengthIndex);
                        hexOffset = Hexval.ReadWord_Hexfile(Fileline, (Int16)DataIndex.DataOffsetIndex);
                        hexRecordType = Hexval.ReadByte_Hexfile(Fileline, (Int16)DataIndex.RecordTypeIndex);

                        try
                        {
                            switch (Convert.ToInt16(hexRecordType))
                            {
                                case 0:
                                    {                                    
                                        bool change = true;

                                        HexData = Hexval.ReadData_Hexfile(Fileline, (Int16)DataIndex.DataIndex, hexDatelength);
                                        while (true)
                                        {

                                            if (change)
                                            {
                                                if (flashBaseAddress != 0)
                                                {
                                                    FlashDatabytesupdate(Hexval.Changeformat_HexDatas(Commands.FlashData, (flashBaseAddress << 16 | hexOffset), HexData));
                                                    MCUTransmitFunction.Transmit(FlashDataTransmit);

                                                    hexCKsum += Hexval.CalculateCKsum_Hexfile(HexData);  // to calculate the total image checksum
                                                }
                                                change = false;
                                            }

                                            if (MCUStatusRxData[0] == Commands.Responce_OK)
                                            {
                                                MCUStatusRxData[0] = 0xFF; //RxMessageDataIN = null;
                                                break;
                                            }
                                            else if (MCUStatusRxData[0] == Commands.Responce_NOTOK)
                                            {
                                                MCUStatusRxData[0] = 0xFF; //RxMessageDataIN = null;
                                                change = true;
                                            }
                                        } // while end 

                                    }
                                    break;
                                case 1:
                                    {
                                        flashBaseAddress = 0;
                                        hexOffset = 0;
                                        HexData = null;
                                        hexRecordType = 0;                                      
                                        retval = true; // this bool is indicate the flash write operation is complete.                                       
                                    }
                                    break;
                                case 4:
                                    {
                                        flashBaseAddress = Hexval.ReadWord_Hexfile(Fileline, (UInt16)DataIndex.DataIndex);
                                    }
                                    break;
                                case 5:
                                    {

                                    }
                                    break;
                                default:
                                    {
                                        MessageBox.Show("Invaid Data Record ", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                    }
                                    break;
                            }
                        }
                        catch (Exception ex) { MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
                    }
                    else
                    {
                        MessageBox.Show("Invalid File Format", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                } // else block end
            } // while end
            sr.Close(); // file closed

            return retval;
        } // flash data transmit end

        public bool flashcompletecommand(UInt32 address) 
        {
            bool retval = false;

            List<byte> flhcmpt = new List<byte>();

            flhcmpt.Add(Commands.Flashcomplete);
            // set app1 or app2 
            flhcmpt.Add((byte)(address>>24));
            flhcmpt.Add((byte)(address >> 16));
            flhcmpt.Add((byte)(address >> 8));
            flhcmpt.Add((byte)(address));

            bool chg_status = true;
            while (true)
            {
                if (chg_status == true)
                {
                    FlashDatabytesupdate(flhcmpt.ToArray());
                    MCUTransmitFunction.Transmit(FlashDataTransmit);
                    chg_status = false;
                }

                if (MCUStatusRxData[0] == Commands.Responce_OK)
                {   
                    hexCKsum = 0;
                    MCUStatusRxData[0] = 0xFF;
                    retval = true;
                    Log.Message("Flash Complete");
                    break;
                }
                else if (MCUStatusRxData[0] == Commands.Responce_NOTOK)
                {
                    MCUStatusRxData[0] = 0xFF;
                    chg_status = true;
                }
            } // while end

            return retval;
        }   // flash completed function end

        public bool UpdateflashappHeader(uint address)
        {
            UInt32 StAdd = 0, EnAdd = 0, AppPatrn = 0,cksum = 0 , memloc=0;
            bool retval = false, headerflg = false, headerStatus = false;

            cksum = ((~hexCKsum) + 1);

            if (address == Convert.ToUInt32(setStartAddress[2].InnerText))
            {
                memloc = address;
                AppPatrn = Commands.APP1_Pattern;              
                StAdd = (Convert.ToUInt32(setStartAddress[2].InnerText) + 0x40 );
                EnAdd = Convert.ToUInt32(setEndAddress[2].InnerText);                                
                headerflg = true;
            }
            else if (address == Convert.ToUInt32(setStartAddress[3].InnerText))
            {
                memloc = address;
                StAdd = (Convert.ToUInt32(setStartAddress[3].InnerText) + 0x40);
                EnAdd = Convert.ToUInt32(setEndAddress[3].InnerText);
                AppPatrn = Commands.APP2_Pattern;
                
                headerflg = true;
            }

            while (true)
            {
                if (headerflg == true)
                {
                    FlashDatabytesupdate( Tohelpupdateheader(memloc, AppPatrn, StAdd, EnAdd, cksum) );
                    MCUTransmitFunction.Transmit(FlashDataTransmit);
                    headerflg = false;
                }

                if (MCUStatusRxData[0] == Commands.Responce_OK)
                {
                    if (headerStatus == true)
                    { 
                        headerStatus = false; retval = true;                     
                        break; 
                    }

                    if (headerStatus == false)
                    {
                        memloc += 0x10; // to store next block in uC

                        StAdd = Commands.AppmajorVer;
                        EnAdd = Commands.AppminorVer;
                        AppPatrn = Commands.AppBuildVer;
                        cksum = Commands.AppReleaseVer;

                        MCUStatusRxData[0] = 0xFF; //RxMessageDataIN = null;
                        headerflg = true;
                        headerStatus = true;
                    }
                }
                else if (MCUStatusRxData[0] == Commands.Responce_NOTOK)
                {
                    MCUStatusRxData[0] = 0xFF; //RxMessageDataIN = null;
                    headerflg = true;
                }

            }// while end
            return retval;
        }// updateAppHeader end

        private byte[] Tohelpupdateheader(uint memloc,uint Pattern, uint StAdd, uint EnAdd, uint cksum)
        {
            List<byte> Header_app = new List<byte>();
            //flash cmd
            Header_app.Add(Commands.FlashData);
            // storing locaiton
            Header_app.Add((byte)(memloc >> 24));
            Header_app.Add((byte)(memloc >> 16));
            Header_app.Add((byte)(memloc >> 8));
            Header_app.Add((byte)(memloc));

            // app Header
            Header_app.Add((byte)(Pattern));
            Header_app.Add((byte)(Pattern >> 8));            
            Header_app.Add((byte)(Pattern >> 16));            
            Header_app.Add((byte)(Pattern >> 24));
            // start address
            Header_app.Add((byte)(StAdd));
            Header_app.Add((byte)(StAdd >> 8));
            Header_app.Add((byte)(StAdd >> 16));
            Header_app.Add((byte)(StAdd >> 24));
            // end address
            Header_app.Add((byte)(EnAdd));
            Header_app.Add((byte)(EnAdd >> 8));
            Header_app.Add((byte)(EnAdd >> 16));
            Header_app.Add((byte)(EnAdd >> 24));

            Header_app.Add((byte)(cksum));
            Header_app.Add((byte)(cksum >> 8));
            Header_app.Add((byte)(cksum >> 16));
            Header_app.Add((byte)(cksum >> 24));            

            return Header_app.ToArray();
        }


    }
}
