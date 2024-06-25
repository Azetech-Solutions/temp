using ComIf;
using System;
using System.IO.Ports;
using static File_TryAccess_Tool.Xmlfilehandling;
using static File_TryAccess_Tool.Log;

namespace File_TryAccess_Tool
{
    public static class Tooltransmit
    {
        public static Channel MCUTransmitFunction;
        public static TxMessage FlashDataTransmit;
        public static TxMessage FCTransmit;
        public static RxMessage MCUStatus;
        public static RxMessage FCReceive;
        public static SerialPort serialPort1;

        public static byte[] MCUStatusRxData = new byte[1] {0xFF};

        public static byte[] FCRxData = new byte[247] ;    
        public static void TooltransmitRegister(SerialPort s)
        {
            //channel  //
            MCUTransmitFunction = new Channel("MCUTransmitFunction", (ChannelType)Enum.Parse(typeof(ChannelType), setComiflist[0].ChildNodes[3].InnerText), // channelType is set based on xml file
                                        FlashDataTransmitTriggerfunction, MCUDataTransmitErrornotify);
            // Flash tx 
            FlashDataTransmit = new TxMessage((byte)Convert.ToInt16(setComiflist[0].ChildNodes[0].ChildNodes[0].InnerText),  //set the TX id based on Xml file
                                                (byte)Convert.ToInt16(setComiflist[0].ChildNodes[0].ChildNodes[1].InnerText)); //Set the Tx Length based on Xml file
            // Flash rx
            MCUStatus = new RxMessage((byte)Convert.ToInt16(setComiflist[0].ChildNodes[1].ChildNodes[0].InnerText),   //set the RX id based on Xml file
                                            (byte)Convert.ToInt16(setComiflist[0].ChildNodes[1].ChildNodes[1].InnerText), MCUStatus_Rxcbk);  //Set the Rx Length based on Xml file
            // FC tx
            FCTransmit = new TxMessage(0xD3,247);
            // FC rx
            FCReceive = new RxMessage(0xD5, 247, FCDataRx);
            MCUTransmitFunction.RegisterRxMessage(MCUStatus);
            MCUTransmitFunction.RegisterRxMessage(FCReceive);
            //serialport 
            serialPort1 = s;
        } // end

        private static void FCDataRx(byte Length, byte[] Data)
        {
            //FCRxData[2] = 0xF0;
            //byte cnt = 0;
            for (int i = 0; i < Length; i++)
            {
                FCRxData[i] = Data[i];
                //Log.Message( " byte "+cnt.ToString()+"  " +Data[i].ToString()); // to check this data properly received or not
                //cnt++;
            }
        } // end

        public static void MCUStatus_Rxcbk(byte Length, byte[] Data)
        {
            for (int i = 0; i < Length; i++)
            {
                MCUStatusRxData[i] = Data[i];
            }
        } // end

        public static void MCUDataTransmitErrornotify(uint Debug0, uint Debug1)
        {
            Log.Error($"Debug0 -{Debug0}, Debug1 -{Debug1}");
        } // end

        public static void FlashDataTransmitTriggerfunction(ushort Length, byte[] Data)
        {
            serialPort1.Write(Data, 0, Length);
        } // end

        public static void FlashDatabytesupdate(byte[] Data) 
        {
            for (int i = 0; i < Data.Length; i++)
            {
                FlashDataTransmit.Data[i] = Data[i];
            }
        } // end

        public static void FCDatabytesupdate(byte[] Data)
        {
            for (int i = 0; i < Data.Length; i++)
            {
                FCTransmit.Data[i] = Data[i];
            }
        } // end
    }
}
