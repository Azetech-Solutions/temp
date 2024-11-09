using ComIf;
using System;
using System.IO.Ports;
using static File_TryAccess_Tool.Xmlfilehandling;
using static File_TryAccess_Tool.Log;
using System.Collections.Generic;

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

        public static List<byte> FCRxData = new List<byte>();
        public static void TooltransmitRegister(SerialPort s)
        {
            ComifConfig();
            serialPort1 = s;            
        } // end


        private static void ComifConfig()
        {
            //channel  //
            MCUTransmitFunction = new Channel("MCUTransmitFunction", (ChannelType)Enum.Parse(typeof(ChannelType), setComiflist[0].ChildNodes[3].InnerText), // channelType is set based on xml file
                                        MCUDataTransmitfunction, MCUDataTransmitErrornotify);
            // Flash tx 
            FlashDataTransmit = new TxMessage((byte)Convert.ToInt16(setComiflist[0].ChildNodes[0].ChildNodes[0].InnerText),  //set the TX id based on Xml file
                                                (byte)Convert.ToInt16(setComiflist[0].ChildNodes[0].ChildNodes[1].InnerText)); //Set the Tx Length based on Xml file
            // Flash rx
            MCUStatus = new RxMessage((byte)Convert.ToInt16(setComiflist[0].ChildNodes[1].ChildNodes[0].InnerText),   //set the RX id based on Xml file
                                            (byte)Convert.ToInt16(setComiflist[0].ChildNodes[1].ChildNodes[1].InnerText), MCUStatus_Rxcbk);  //Set the Rx Length based on Xml file
            // FC tx
            FCTransmit = new TxMessage(0xD3, 247);
            // FC rx
            FCReceive = new RxMessage(0xD5, 255, FCData_Rxcbk);
            FCReceive.EnableDynamicLength = true;

            // rx message register
            MCUTransmitFunction.RegisterRxMessage(MCUStatus);
            MCUTransmitFunction.RegisterRxMessage(FCReceive);
            //serialport            
        }

        #region Serial receive Part 
        //private static void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        //{
        //    ushort len = (ushort)serialPort1.BytesToRead;
        //    byte[] data = new byte[len];

        //    serialPort1.Read(data, 0, data.Length);

        //    for (ushort i = 0; i < data.Length; i++)
        //    {
        //        MCUTransmitFunction.RxIndication(data[i]);
        //    }

        //    //string data = serialPort1.ReadExisting();
        //    //MCUTransmitFunction.RxIndication(data);
        //} // serial data rx part end

        #endregion

        private static void FCData_Rxcbk(byte Length, byte[] Data)
        {
            FCRxData.Clear();
            for (int i = 0; i < Length; i++)
            {
                FCRxData.Add(Data[i]);    
            }
            Commands.FCrxCbkFlag = true;
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
            Log.Error($"Debug0 -{Debug0.ToString("X2")}, Debug1 -{Debug1.ToString("X2")}");
        } // end

        public static void MCUDataTransmitfunction(ushort Length, byte[] Data)
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
