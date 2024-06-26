﻿using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using static File_TryAccess_Tool.Tooltransmit;

namespace File_TryAccess_Tool
{
    public class NvmDataHandling
    {
        public NvmDataHandling() { }


        public void NvmClearCmD()
        {
            List<byte> list = new List<byte>();

            list.Add(Commands.NVMClear);

            FCDatabytesupdate(list.ToArray());

            MCUTransmitFunction.Transmit(FCTransmit);

            Log.Message("NvmClear start");
            while(true)
            {
                if (MCUStatusRxData[0] == 0x00)
                {
                    MCUStatusRxData[0] = 0xFF;
                    break;
                }
                else if (MCUStatusRxData[0] == 0x01)
                {
                    MCUStatusRxData[0] = 0xFF;

                    MCUTransmitFunction.Transmit(FCTransmit);
                }
            }

            Log.Message("NvmClear start end ");
        }

        public void NvmReOrgCMD()
        {
            List<byte> list = new List<byte>();

            list.Add(Commands.NVMReOrg);

            FCDatabytesupdate(list.ToArray());

            MCUTransmitFunction.Transmit(FCTransmit);

            Log.Message("NvmReOrg start");
            while (true)
            {
                if (MCUStatusRxData[0] == 0x00)
                {
                    MCUStatusRxData[0] = 0xFF;
                    break;
                }
                else if (MCUStatusRxData[0] == 0x01)
                {
                    MCUStatusRxData[0] = 0xFF;

                    MCUTransmitFunction.Transmit(FCTransmit);
                }
            }

            Log.Message("NvmReOrg start end ");
        }

        public void NvmUpdateCMD()
        {
            List<byte> list = new List<byte>();
            uint Add = Convert.ToUInt32(Xmlfilehandling.setStartAddress[5].InnerText);
            // nvm cmd
            list.Add(Commands.NVMUpdate); // 1st
            // length
            list.Add(0x00); // 2nd
            // flg and timing
            list.Add(0x00); // 3rd
            // address
            list.Add(((byte)(Add >> 24))); // 4th
            list.Add(((byte)(Add >> 16))); // 5th
            list.Add(((byte)(Add >> 8))); // 6th
            list.Add(((byte)Add)); // 7th


            FCDatabytesupdate(list.ToArray());

            MCUTransmitFunction.Transmit(FCTransmit);
        }
    }
}
