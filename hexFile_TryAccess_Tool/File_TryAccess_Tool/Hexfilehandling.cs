using System;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace File_TryAccess_Tool
{
    public class Hexfilehandling
    {
        Tooltransmit toolTransmit;
        GetHexfileValue Hexval;
        public Hexfilehandling(Tooltransmit s) { toolTransmit = s; Hexval = new GetHexfileValue(); }

        public string Filepath = null, flashBaseAddress = null;
        private string Fileline = null, hexOffset = null, hexDatelength = null, HexData = null, hexRecordType = null; // these variables are used to store the Hexfile data's
        private uint hexCKsum = 0;

        public bool Hexfileverity(OpenFileDialog ofd)
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

        public bool Flashstartcommands(string address)
        {
            const string flashStart = "F50000000000000000000000000000000000000000";
            const string flashmode = "FB0000000000000000000000000000000000000000";

            bool retval = false, startcommandflag = true;
            string dataUpdate = flashStart, flashErase = null;

            
            while (true)
            {
                if (startcommandflag)
                {
                    toolTransmit.tooldatamsgUpdate(dataUpdate);
                    toolTransmit.mcuTransmit.Transmit(toolTransmit.mcuTransmitmessage);
                    //serialPort1.Write(modeupdate + " "); // changes
                    startcommandflag = false;
                }

                if (toolTransmit.mucRxData[0] == 0x00) // check this 
                {
                    toolTransmit.mucRxData[0] = 0xFF; //RxMessageDataIN = null;

                    if (dataUpdate == flashStart)
                    {
                        dataUpdate = flashmode;
                        startcommandflag = true;
                    }
                    else
                    {
                        if (dataUpdate == flashErase)
                        {
                            retval = true;
                            break;
                        }

                        if (dataUpdate == flashmode)
                        {
                           // flashErasemry = address;

                            flashErase = "FE" + address + "00000000000000000000000000000000";

                            dataUpdate = flashErase;
                            startcommandflag = true;
                        }
                    }
                }
                else if (toolTransmit.mucRxData[0] == 0x01)
                {
                    toolTransmit.mucRxData[0] = 0xFF; //RxMessageDataIN = null;
                    startcommandflag = true;
                }

            } //"while" end of the flashstart , flash mode, erase mode 

            return retval;
        }

        public bool FlashDatatransmit()
        {
            bool retval = false;

            StreamReader sr = new StreamReader(Filepath);

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
                        hexDatelength = Hexval.HexfileReadByte(Fileline, 1);
                        hexOffset = Hexval.HexfileReadword(Fileline, 3);
                        hexRecordType = Hexval.HexfileReadByte(Fileline, 7);
                        //tBoxOutData.Text = type;
                        HexData = Hexval.HexfileReadDatas(Fileline, 9, Convert.ToUInt16(hexDatelength, 16));

                        try
                        {
                            switch (Convert.ToInt16(hexRecordType))
                            {
                                case 0:
                                    {
                                        bool change = true;
                                        while (true)
                                        {

                                            if (change)
                                            {
                                                if (flashBaseAddress != null)
                                                {
                                                    var mryadd = flashBaseAddress + hexOffset;
                                                    mryadd = "FD" + mryadd + HexData;

                                                    toolTransmit.tooldatamsgUpdate(mryadd);
                                                    toolTransmit.mcuTransmit.Transmit(toolTransmit.mcuTransmitmessage);

                                                    hexCKsum += Hexval.HexfileSumOfLine(HexData);
                                                }
                                                change = false;
                                            }

                                            if (toolTransmit.mucRxData[0] == 0x00)
                                            {
                                                toolTransmit.mucRxData[0] = 0xFF; //RxMessageDataIN = null;
                                                break;
                                            }
                                            else if (toolTransmit.mucRxData[0] == 0x01)
                                            {
                                                toolTransmit.mucRxData[0] = 0xFF; //RxMessageDataIN = null;
                                                change = true;
                                            }
                                        } // while end 

                                    }
                                    break;
                                case 1:
                                    {
                                        flashBaseAddress = null;
                                        hexOffset = null;
                                        HexData = null;
                                        hexRecordType = null;

                                        if (true) //(updateAppHeader())
                                        {
                                            retval = true; // this bool is indicate the flash write operation is complete.
                                        }
                                    }
                                    break;
                                case 4:
                                    {
                                        if (HexData.Length == 4)
                                        {
                                            flashBaseAddress = HexData;
                                        }
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

        public bool flashcompletecommand(string address) 
        {
            bool retval = false;

            string Flashcompleted = "FC" + address + "00000000000000000000000000000000";

            bool chg_status = true;
            while (true)
            {
                if (chg_status == true)
                {
                    toolTransmit.tooldatamsgUpdate(Flashcompleted);
                    toolTransmit.mcuTransmit.Transmit(toolTransmit.mcuTransmitmessage);
                    chg_status = false;
                }

                if (toolTransmit.mucRxData[0] == 0x00)
                {                    
                    toolTransmit.mucRxData[0] = 0xFF;
                    retval = true;
                    break;
                }
                else if (toolTransmit.mucRxData[0] == 0x01)
                {
                    toolTransmit.mucRxData[0] = 0xFF;
                    chg_status = true;
                }
            } // while end

            return retval;
        }   // flash completed function end

        public bool UpdateflashappHeader(string address)
        {
            string Header = null, SAdd = null, EAdd = null, flag = null;
            bool retval = false, headerflg = false, headerStatus = false;
            string headerUpdate = null;

            hexCKsum = ((~hexCKsum) + 1);

            if (address == "08006000")
            {
                // change to xml file based
                Header = "A1A1A1A1"; 
                SAdd = "08006000";
                EAdd = "0800FFFC";
                flag = "00000000";
                headerflg = true;
                headerUpdate = "FD" + SAdd + Header + SAdd + EAdd + flag;

            }
            else if (address == "08016000")
            {
                Header = "A2A2A2A2";
                SAdd = "08016000";
                EAdd = "0801FFFC";
                flag = "00000000";
                headerflg = true;
                headerUpdate = "FD" + SAdd + Header + SAdd + EAdd + flag;
            }

            while (true)
            {
                if (headerflg == true)
                {
                    toolTransmit.tooldatamsgUpdate(headerUpdate);
                    toolTransmit.mcuTransmit.Transmit(toolTransmit.mcuTransmitmessage);
                    headerflg = false;
                }

                if (toolTransmit.mucRxData[0] == 0x00)
                {
                    if (headerStatus == true)
                    { 
                        headerStatus = false; retval = true;
                        Log.Message("Flash Complete");
                        break; 
                    }

                    if (headerStatus == false)
                    {
                        string ck = Convert.ToString(hexCKsum, 16);
                        SAdd = Convert.ToString(Convert.ToInt32(SAdd) + 10U);
                        headerUpdate = "FD" + SAdd + ck + "000000000000000000000000";
                        toolTransmit.mucRxData[0] = 0xFF; //RxMessageDataIN = null;
                        headerflg = true;
                        headerStatus = true;
                    }
                }
                else if (toolTransmit.mucRxData[0] == 0x01)
                {
                    toolTransmit.mucRxData[0] = 0xFF; //RxMessageDataIN = null;
                    headerflg = true;
                }

            }// while end
            return retval;
        }// updateAppHeader end
    }
}
