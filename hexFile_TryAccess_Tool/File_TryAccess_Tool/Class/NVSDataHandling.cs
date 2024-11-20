using System;
using System.Collections.Generic;
using static File_TryAccess_Tool.Tooltransmit;
using File_TryAccess_Tool.Class;
using System.Xml;
using System.IO;


namespace File_TryAccess_Tool
{
    public class NVSDataHandling
    {
        private static uint nvsDataCksum = 0;
        private static UInt16 NVSID = 0;
        private static UInt16 NVSLength = 0;
        private static string nvsXMlPath;
        UInt16 totalnvsbytes = 0;
        private FlowControlHandling fctxhandle = new FlowControlHandling();
        private UInt32 NVSblockAdd = 0;
        private UInt32 PreviousNVSblockAdd = 0;
        public NVSDataHandling(string p) { InitializeXmlFile(p); nvsXMlPath = p; }

        public static void InitializeXmlFile(string filePath)
        {
            if (!File.Exists(filePath))
            {
                using (XmlWriter writer = XmlWriter.Create(filePath))
                {
                    writer.WriteStartDocument();
                    writer.WriteStartElement("Nvsblocks");
                    writer.WriteEndElement();
                    writer.WriteEndDocument();
                }
            }
            else
            {
                File.Delete(filePath);

                using (XmlWriter writer = XmlWriter.Create(filePath))
                {
                    writer.WriteStartDocument();
                    writer.WriteStartElement("Nvsblocks");
                    writer.WriteEndElement();
                    writer.WriteEndDocument();
                }
            }
        }

        public static bool nvsXMLAppendDataBlock(string filePath, string genname, string blockName, string blockId, string blockLen)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(filePath);

            XmlNode newBlock = doc.CreateElement(genname);

            doc.DocumentElement.AppendChild(newBlock);

            XmlNode newBlock1 = doc.CreateElement("name");
            newBlock1.InnerText = blockName;
            newBlock.AppendChild(newBlock1);

            XmlNode newBlock2 = doc.CreateElement("id");
            newBlock2.InnerText = blockId;
            newBlock.AppendChild(newBlock2);

            XmlNode newBlock3 = doc.CreateElement("len");
            newBlock3.InnerText = blockLen;
            newBlock.AppendChild(newBlock3);

            doc.Save(filePath);

            return true;
        }
        public void NVSUpdate(string inputdata)
        {
            List<byte> NVSStart = new List<byte>();

            byte[] Nvstx = fctxhandle.ConvertHexStringToByteArray(inputdata);

            NVSblockAdd = getNvsNextblockstartaddress();

            if (NVSblockAdd > PreviousNVSblockAdd)
            {
                PreviousNVSblockAdd = NVSblockAdd;

                NVSStart.Add(Commands.NVSstartCMD);
                NVSStart.Add(0x00);
                NVSStart.Add(0x00);
                NVSStart.Add((byte)(NVSblockAdd >> 24));
                NVSStart.Add((byte)(NVSblockAdd >> 16));
                NVSStart.Add((byte)(NVSblockAdd >> 8));
                NVSStart.Add((byte)(NVSblockAdd));

                FCDatabytesupdate(NVSStart.ToArray());
                FCTransmit.Length = (byte)NVSStart.Count;
                MCUTransmitFunction.Transmit(FCTransmit);

                while (true)
                {
                    if (MCUStatusRxData[0] == 0x00)
                    {
                        MCUStatusRxData[0] = 0xFF;
                        break;
                    }
                    //Thread.Sleep(3);
                }

                BytetoCksumCalculate(Nvstx);

                fctxhandle.FCDataTransmit(MeragethetotalNvsdata(Nvstx));


                if (nvsXMLAppendDataBlock(nvsXMlPath, "nvsblock", ("block" + NVSID.ToString()), NVSID.ToString(), NVSLength.ToString())) { NVSID++; }

                NVSblockAdd = 0; // reset it
            }
        }


        private void BytetoCksumCalculate(byte[] inputdata)
        {
            UInt16 len = (UInt16) inputdata.Length;
            
            byte pos = 0,cnt=0;
            nvsDataCksum = 0;
            NVSLength = len;
            while (len > 0)
            {
                List<byte> store16bytedata = new List<byte>();
               
                while((cnt < 4) && len > 0)
                {
                    store16bytedata.Add(inputdata[pos]);
                    pos++;
                    len--;
                    cnt++;
                }
                cnt = 0;
                nvsDataCksum += CalculateCKsum_NVS(store16bytedata.ToArray());
            }

            //NVSID++;

        }
        private uint CalculateCKsum_NVS(byte[] hex)
        {
            uint[] hexval = new uint[1];
            uint retval = 0;

            if (hex.Length == 4)
            {
                hexval[0] = (uint)((hex[3] << 24) | (hex[2] << 16) | (hex[1] << 8) | (hex[0]));
                //NVSblockAdd += 4;
                retval = (uint)hexval[0];
            }
            else if (hex.Length == 3)
            {
                hexval[0] = (uint)((hex[2] << 16) | (hex[1] << 8) | (hex[0]));
                //NVSblockAdd += 4;
                retval = (uint)hexval[0];
            }
            else if (hex.Length == 2)
            {
                hexval[0] = (uint)((hex[1] << 8) | (hex[0]));
                //NVSblockAdd += 4;
                retval = (uint)hexval[0];
            }
            else if (hex.Length == 1)
            {
                hexval[0] = (uint)((hex[0]));
                //NVSblockAdd += 4;
                retval = (uint)hexval[0];
            }

            return retval;
        }

        private byte[] MeragethetotalNvsdata(byte[] dta)
        {
            List<byte> Tomerge = new List<byte>();

            // pattern
            Tomerge.Add((byte)(Commands.NVS_Pattern >> 24));
            Tomerge.Add((byte)(Commands.NVS_Pattern >> 16));
            Tomerge.Add((byte)(Commands.NVS_Pattern >> 8));
            Tomerge.Add((byte)(Commands.NVS_Pattern));
            //data len
            Tomerge.Add((byte)(NVSLength >> 8));
            Tomerge.Add((byte)(NVSLength));
            // nvs block id
            Tomerge.Add((byte)(NVSID >> 8));
            Tomerge.Add((byte)(NVSID));
            //nvs block data checksum
            Tomerge.Add((byte)(nvsDataCksum >> 24));
            Tomerge.Add((byte)(nvsDataCksum >> 16));
            Tomerge.Add((byte)(nvsDataCksum >> 8));
            Tomerge.Add((byte)(nvsDataCksum));

            //NVSblockAdd += 12; // data byte + pattern +id/len + cksum (12bytes)
            
            for (int i= 0; i < dta.Length; i++)
            {
                Tomerge.Add(dta[i]);
            }

            ushort quotient = (ushort)(Tomerge.Count % 16);

            for(int i= 0; i < (16 - quotient); i++)
            {
                Tomerge.Add(0);
                NVSLength++;
            }

            return Tomerge.ToArray();
        }

        private UInt32 getNvsNextblockstartaddress()
        {
            UInt32 nvsNextblockstartaddress;

            List<byte> NVSStart = new List<byte>();

            NVSStart.Add(Commands.GETNVSLASTADDRESSCMD);            

            FCDatabytesupdate(NVSStart.ToArray());
            FCTransmit.Length = (byte)NVSStart.Count;
            MCUTransmitFunction.Transmit(FCTransmit);

            while (true)
            {
                if (Commands.FCrxCbkFlag == true)
                {
                    if (FCRxData[0] == Commands.GETNVSLASTADDRESSCMD)
                    {
                        nvsNextblockstartaddress = (UInt32)(FCRxData[3] << 24 | FCRxData[4] << 16 | FCRxData[5] << 8 | FCRxData[6]);
                        
                        break;
                    }

                    Commands.FCrxCbkFlag = false;
                }
            }

            return nvsNextblockstartaddress;
        }

        #region Update NVS Not used
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


            return retval;
        }
        #endregion
    }
}
