using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static File_TryAccess_Tool.Xmlfilehandling;
using static File_TryAccess_Tool.Tooltransmit;
using System.Collections;
using System.Net;
using Microsoft.SqlServer.Server;

namespace File_TryAccess_Tool
{
    public class NVSDataHandling
    {
        uint nvsDataCksum = 0;
        UInt16 totalnvsbytes = 0;
        public UInt32 NextblockAdd = Convert.ToUInt32(Xmlfilehandling.setStartAddress[4].InnerText);
        public NVSDataHandling() {  }

        public char[] removeSpace(string input)
        {
            char[] arr = input.ToCharArray();

            for (int i = 0; i < arr.Length; i++)
            {
                if (arr[i] != ' ')
                {
                    arr[i] = arr[i];
                }
            }

            return arr;
        }

        public byte[] StringTobyte(string inputString)
        {
            string[] split = inputString.Split(' ');

            byte[] byteArray = new byte[split.Length];

            for (int i = 0; i < split.Length; i++)
            {
                byteArray[i] = Convert.ToByte(split[i], 16);
            }
            return byteArray;
        }

        public bool NVSflashstartcommands()
        {
            byte[] dataUpdate = new byte[5];
            bool retval = false, startcommandflag = true;
            dataUpdate[0] = Commands.Flashstart;

            Log.Message("Nvs Flash Start");
            while (true)
            {
                if (startcommandflag)
                {
                    FlashDatabytesupdate(dataUpdate);
                    MCUTransmitFunction.Transmit(FlashDataTransmit);
                    startcommandflag = false;
                }

                if (MCUStatusRxData[0] == Commands.Responce_OK) 
                {
                    MCUStatusRxData[0] = 0xFF; // reset

                    if (dataUpdate[0] == Commands.Flashstart)
                    {
                        dataUpdate[0] = Commands.ChooseNVSMode;
                        startcommandflag = true;
                    }
                    else
                    {
                        if (dataUpdate[0] == Commands.ChooseNVSMode)
                        {
                            retval = true;
                            break;
                        }
                    }
                }
                else if (MCUStatusRxData[0] == Commands.Responce_NOTOK)
                {
                    MCUStatusRxData[0] = 0xFF; // reset
                    startcommandflag = true;
                }

            } //"while" end of the flashstart , nvs mode, erase mode 

            return retval;
        }

        public uint CalculateCKsum_NVS(byte[] hex)
        {
            uint[] hexval = new uint[hex.Length];

            if ((hex.Length / 4) == 1)
            {
                hexval[0] = (uint)(hex[3] << 24 | hex[2] << 16 | hex[1] << 8 | hex[0]);
            }
            else if ((hex.Length / 4) == 2)
            {
                hexval[0] = (uint)(hex[3] << 24 | hex[2] << 16 | hex[1] << 8 | hex[0]);
                hexval[1] = (uint)(hex[7] << 24 | hex[6] << 16 | hex[5] << 8 | hex[4]);
            }
            else if ((hex.Length / 4) == 3)
            {
                hexval[0] = (uint)(hex[3] << 24 | hex[2] << 16 | hex[1] << 8 | hex[0]);
                hexval[1] = (uint)(hex[7] << 24 | hex[6] << 16 | hex[5] << 8 | hex[4]);
                hexval[2] = (uint)(hex[11] << 24 | hex[10] << 16 | hex[9] << 8 | hex[8]);
            }
            else if ((hex.Length / 4) == 4)
            {
                hexval[0] = (uint)(hex[3] << 24 | hex[2] << 16 | hex[1] << 8 | hex[0]);
                hexval[1] = (uint)(hex[7] << 24 | hex[6] << 16 | hex[5] << 8 | hex[4]);
                hexval[2] = (uint)(hex[11] << 24 | hex[10] << 16 | hex[9] << 8 | hex[8]);
                hexval[3] = (uint)(hex[15] << 24 | hex[14] << 16 | hex[13] << 8 | hex[12]);
            }

            return (uint)(hexval[0] + hexval[1] + hexval[2] + hexval[3]);
        }
        public bool NVSDataTransmit(UInt32 add,byte[] Databytes)
        {
            bool retval = false;

            int loopstr = 0, loopend = 16;
            totalnvsbytes = (UInt16)Databytes.Length;

            UInt32 baseadd = add; //08010000
            baseadd += 0x10;

            for(ushort i=0;i< totalnvsbytes / 16;i++)
            {
                List<byte> data = new List<byte>();

                data.Add(Commands.FlashData);
                data.Add((byte)(baseadd >> 24));
                data.Add((byte)(baseadd >> 16));
                data.Add((byte)(baseadd >> 8));
                data.Add((byte)(baseadd));

                for (loopstr = loopstr; loopstr < loopend; loopstr++)
                {
                    data.Add(Databytes[loopstr]);
                }
                loopend = loopstr + 16;

                NvsDataUpdateinComif(data.ToArray());
                baseadd += 0x10;
            }

            UInt16 ballen = (UInt16)((loopstr - 1) + totalnvsbytes % 16);

            if ((totalnvsbytes % 16  != 0) && (totalnvsbytes % 16 < 16))
            {
                List<byte> baldata = new List<byte>();

                baldata.Add(Commands.FlashData);
                baldata.Add((byte)(baseadd >> 24));
                baldata.Add((byte)(baseadd >> 16));
                baldata.Add((byte)(baseadd >> 8));
                baldata.Add((byte)(baseadd));

                for (loopstr = loopstr; loopstr <= ballen; loopstr++)
                {
                    baldata.Add(Databytes[loopstr]);
                }
                baseadd += 0x10;
                if(NvsDataUpdateinComif(baldata.ToArray()))
                {
                    if(UpdateNvsHeader(add))
                    {
                        NextblockAdd = baseadd;
                        Log.Message("Nvs Flash complete"); retval = true;
                    }

                }
            }
            else 
            {
                if (UpdateNvsHeader(add))
                {
                    NextblockAdd = baseadd;
                    Log.Message("Nvs Flash complete"); retval = true;
                }
            }

            return retval;
        }

        // data updated in comif channel
        public bool NvsDataUpdateinComif(byte[] data) 
        {
            bool retval = false,nvsflg = true;
           

            while(true)
            {

                if(nvsflg == true)
                {
                    for (int i = 0; i < data.Length; i++)
                    {  FlashDataTransmit.Data[i] = data[i]; }

                    MCUTransmitFunction.Transmit(FlashDataTransmit);
                    nvsDataCksum += CalculateCKsum_NVS(data);
                    nvsflg = false;
                }


                if (MCUStatusRxData[0] == Commands.Responce_OK)
                {
                    MCUStatusRxData[0] = 0xFF; // reset
                    retval = true;
                    break;
                }
                else if (MCUStatusRxData[0] == Commands.Responce_NOTOK)
                {
                    MCUStatusRxData[0] = 0xFF; // reset
                    nvsflg = true;
                }
            } // while end
            return retval;
        } // end

        public bool NvsflashComplete()
        {
            bool retval = false,cntflg = true;
            byte[] cmd = new byte[1];
            cmd[0] = Commands.Flashcomplete;

            while (true)
            {
                if (cntflg == true)
                {
                    FlashDatabytesupdate(cmd);
                    MCUTransmitFunction.Transmit(FlashDataTransmit);
                    cntflg = false;
                }

                if (MCUStatusRxData[0] == Commands.Responce_OK)
                {
                    MCUStatusRxData[0] = 0xFF;
                    retval = true;
                    break;
                }
                else if (MCUStatusRxData[0] == Commands.Responce_NOTOK)
                {
                    MCUStatusRxData[0] = 0xFF;
                    cntflg = true;
                }
            } // while end

            return retval;
        }

        public bool UpdateNvsHeader(UInt32 add)
        {
            bool retval = false;
            List<byte> headerdata = new List<byte>();

            uint pat = 0xC1C1C1C1;
            UInt16 id = 0x0000;
            UInt16 len = totalnvsbytes;
            uint ck = ((~nvsDataCksum)+1) ;


            
            // cmd added
            headerdata.Add(Commands.FlashData);
            // Address added
            headerdata.Add((byte)((add >> 24)&(0xFF)));
            headerdata.Add((byte)((add >> 16)&(0xFF)));
            headerdata.Add((byte)((add >> 8) & (0xFF)));
            headerdata.Add((byte)((add) & (0xFF)));
            // Pattern added
            headerdata.Add((byte)((pat >> 24) & (0xFF)));
            headerdata.Add((byte)((pat >> 16) & (0xFF)));
            headerdata.Add((byte)((pat >> 8) & (0xFF)));
            headerdata.Add((byte)((pat) & (0xFF)));
            // Id added
            headerdata.Add((byte)((id >> 8) & (0xFF)));
            headerdata.Add((byte)((id) & (0xFF)));
            // length added
            headerdata.Add((byte)((len >> 8) & (0xFF)));
            headerdata.Add((byte)((len) & (0xFF)));
            // Cksum added
            headerdata.Add((byte)((ck >> 24) & (0xFF)));
            headerdata.Add((byte)((ck >> 16) & (0xFF)));
            headerdata.Add((byte)((ck >> 8) & (0xFF)));
            headerdata.Add((byte)((ck) & (0xFF)));
            // Future changes
            headerdata.Add(0xFF);
            headerdata.Add(0xFF);
            headerdata.Add(0xFF);
            headerdata.Add(0xFF);

            if (NvsDataUpdateinComif(headerdata.ToArray()))
            {   
                if(NvsflashComplete())
                {
                    retval = true;
                }             
            }

            return retval;
        }
    }
}
