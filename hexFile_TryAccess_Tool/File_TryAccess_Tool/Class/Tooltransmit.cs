using ComIf;
using System;
using System.IO.Ports;
using static File_TryAccess_Tool.Xmlfilehandling;
using static File_TryAccess_Tool.Log;

namespace File_TryAccess_Tool
{
    public static class Tooltransmit
    {
        public static Channel mcuTransmit;
        public static TxMessage mcuTransmitmessage;
        public static TxMessage mcuNvmTransmitmessage;
        public static RxMessage receivemcuData;
        public static RxMessage receiveNvmData;
        public static SerialPort serialPort1;

        public static byte[] mcuRxData = new byte[] {0xFF};

        public static byte[] NvmRxData = new byte[243];
        public static void TooltransmitRegister(SerialPort s)
        {
            //channel  //
            mcuTransmit = new Channel("mcuTransmit", (ChannelType)Enum.Parse(typeof(ChannelType), setComiflist[0].ChildNodes[3].InnerText), // channelType is set based on xml file
                                        mcuDataTransmit, mcuDataTransmitErrnofi);
            // Flash tx 
            mcuTransmitmessage = new TxMessage((byte)Convert.ToInt16(setComiflist[0].ChildNodes[0].ChildNodes[0].InnerText),  //set the TX id based on Xml file
                                                (byte)Convert.ToInt16(setComiflist[0].ChildNodes[0].ChildNodes[1].InnerText)); //Set the Tx Length based on Xml file
            // Flash rx
            receivemcuData = new RxMessage((byte)Convert.ToInt16(setComiflist[0].ChildNodes[1].ChildNodes[0].InnerText),   //set the RX id based on Xml file
                                            (byte)Convert.ToInt16(setComiflist[0].ChildNodes[1].ChildNodes[1].InnerText), mcuResponce_Rxcbk);  //Set the Rx Length based on Xml file
            // nvm tx
            mcuNvmTransmitmessage = new TxMessage(0xD3,247);
            // nvm rx
            receiveNvmData = new RxMessage(0xD5, 255, NvmDataRx);

            mcuTransmit.RegisterRxMessage(receivemcuData);
            mcuTransmit.RegisterRxMessage(receiveNvmData);
            //serialport 
            serialPort1 = s;
        } // end

        private static void NvmDataRx(byte Length, byte[] Data)
        {
            for(int i = 0; i < Length; i++)
            {
                NvmRxData[i] = Data[i];
                Log.Message(Data[i].ToString()); // to check this data properly received or not
            }
        }

        public static void mcuResponce_Rxcbk(byte Length, byte[] Data)
        {
            for (int i = 0; i < Length; i++)
            {
                mcuRxData[i] = Data[i];
            }
        } // end

        public static void mcuDataTransmitErrnofi(uint Debug0, uint Debug1)
        {
            Log.Error($"Debug0 -{Debug0}, Debug1 -{Debug1}");
        } // end

        public static void mcuDataTransmit(ushort Length, byte[] Data)
        {
            serialPort1.Write(Data, 0, Length);
        } // end

        public static void TooldataBytemsgUpdate(byte[] Data) 
        {
            for (int i = 0; i < Data.Length; i++)
            {
                mcuTransmitmessage.Data[i] = Data[i];
            }
        } // end

        public static void NVMDataByteUpdate(byte[] Data)
        {
            for (int i = 0; i < Data.Length; i++)
            {
                mcuNvmTransmitmessage.Data[i] = Data[i];
            }
        } // end
    }
}
