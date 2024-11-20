using ComIf;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Xml.Linq;
using static File_TryAccess_Tool.Tooltransmit;

namespace File_TryAccess_Tool.Class
{
    public class FlowControlHandling
    {
        public enum FCFrameType
        {
            frameUnkown = 0,
            singleFrame = 1,
            firstFrame = 2,
            consecutiveFrame = 3,
        };
        
        private bool FCinitialflag = false;
        private bool FCsingleframeflag = false;
        private bool FCfirstframeflag = false;
        private bool FCconsecutiveflag = false;

        public static ushort FCTotalDataLength;
        public static ushort FCBalanceDataLength;
        public static ushort FCReceivedDataLength;
    

        public static FCFrameType FcRxtype = FCFrameType.frameUnkown;
        public static FCFrameType FcTxtype = FCFrameType.frameUnkown;

        public static List<byte> FCReceivedData = new List<byte>();


        public byte[] ConvertHexStringToByteArray(string hexString)
        {
            // Calculate the length of the byte array
            int byteArrayLength = hexString.Length / 2;
            byte[] byteArray = new byte[byteArrayLength];

            for (int i = 0; i < byteArrayLength; i++)
            {
                // Take two characters at a time and convert to byte
                string byteValue = hexString.Substring(i * 2, 2);
                byteArray[i] = Convert.ToByte(byteValue, 16);
            }

            return byteArray;
        }

        public void FCDataReceive(byte[] Getdata)
        {
            #region Reset the variables

            FCTotalDataLength = 0;
            FCBalanceDataLength = 0;
            FCReceivedDataLength = 0;
            FCReceivedData.Clear(); // clear the received buffer

            #endregion

            FCDatabytesupdate(Getdata.ToArray());
            FCTransmit.Length = (byte)Getdata.Length;
            MCUTransmitFunction.Transmit(FCTransmit);

            while (true)
            {
                if (Commands.FCrxCbkFlag == true)
                {
                    if ((FCRxData[0] & 0x0F) == Commands.FCFirstFrame)
                    {
                        List<byte> FCTxdata = new List<byte>();
                        FcRxtype = FCFrameType.firstFrame;
                        if (FCFramesHandleReceive(FCRxData.ToArray()))
                        {
                            FCTxdata.Add( (byte)((byte)((FCBalanceDataLength & 0x0F00) >> 4) | Commands.FCFlowcontrolFrame) );
                            FCTxdata.Add( (byte) (FCBalanceDataLength & 0x00FF) );
                            FCTxdata.Add((byte)(Commands.FCSendstatus << 4));

                            FCDatabytesupdate(FCTxdata.ToArray());
                            FCTransmit.Length = (byte)FCTxdata.Count;
                            MCUTransmitFunction.Transmit(FCTransmit);
                        }
                        else
                        {
                            FCTxdata.Add(Commands.NVMGetAlldata);
                            FCTxdata.Add(0x00);
                            FCTxdata.Add((byte)(Commands.FCRepeatstatus << 4));
                            // data transmit
                            FCDatabytesupdate(FCTxdata.ToArray());
                            FCTransmit.Length = (byte)FCTxdata.Count;
                            MCUTransmitFunction.Transmit(FCTransmit);
                        }
                    }
                    else if ((FCRxData[0] & 0x0F) == Commands.FCConsecutiveFrame)
                    {
                        List<byte> FCTxdata = new List<byte>();
                        FcRxtype = FCFrameType.consecutiveFrame;
                        if (FCFramesHandleReceive( FCRxData.ToArray()))
                        {
                            if (FCBalanceDataLength == 0)
                            {                               
                                FCTxdata.Add(Commands.FCFlowcontrolFrame);
                                FCTxdata.Add(0x00);
                                FCTxdata.Add((byte)(Commands.FCAbortstatus << 4));  // consider all data's are received
                                //Data transmit
                                FCDatabytesupdate(FCTxdata.ToArray());
                                FCTransmit.Length = (byte)FCTxdata.Count;
                                MCUTransmitFunction.Transmit(FCTransmit);
                                FcRxtype = FCFrameType.frameUnkown;
                                break; // terminate the loop after all data's received.
                            }
                            else { /*Do nothig waiting to all data received */ }
                        }
                    }
                    else if ((FCRxData[0] & 0x0F) == Commands.FCSingleFrame)
                    {
                        List<byte> FCTxdata = new List<byte>();
                        FcRxtype = FCFrameType.singleFrame;
                        if (FCFramesHandleReceive(FCRxData.ToArray()))
                        {
                            FCTxdata.Add(Commands.NVMGetAlldata);
                            FCTxdata.Add(0x00);
                            FCTxdata.Add((byte)(Commands.FCAbortstatus << 4));  // consider all data's are received
                            // data transmit
                            FCDatabytesupdate(FCTxdata.ToArray());
                            FCTransmit.Length = (byte)FCTxdata.Count;
                            MCUTransmitFunction.Transmit(FCTransmit);
                            FcRxtype = FCFrameType.frameUnkown;
                            break;  // terminate the loop after all data's received.
                        } // if end
                        else
                        {
                            FCTxdata.Add(Commands.NVMGetAlldata);
                            FCTxdata.Add(0x00);
                            FCTxdata.Add((byte)(Commands.FCRepeatstatus << 4));
                            // data transmit
                            FCDatabytesupdate(FCTxdata.ToArray());
                            FCTransmit.Length = (byte)FCTxdata.Count;
                            MCUTransmitFunction.Transmit(FCTransmit);
                        } // else end                        
                    }

                    Commands.FCrxCbkFlag = false;
                }           
            }
        }

        private static void DatacopyComiftoLocal(byte[] data)
        {
            for (int i = 3; i < data.Length; i++) // first 3 byte to considers the flow control status remaining byte are valid data's
            {
                FCReceivedData.Add(data[i]);
            }
        }

        private static bool FCFramesHandleReceive( byte[] fcData)
        {
            bool retval = false;
            switch (FcRxtype)
            {
                case FCFrameType.frameUnkown:
                    { }
                    break;
                case FCFrameType.singleFrame:
                    {
                        FCTotalDataLength = (ushort) (( ((fcData[0] & 0xF0) << 4) | fcData[1]) & 0x0FFF);
                        FCReceivedDataLength = (ushort)(fcData.Length - 3);

                        DatacopyComiftoLocal(fcData);

                        if (FCTotalDataLength == (fcData.Length - 3))
                        {
                            retval = true ;
                        }
                    }
                    break;
                case FCFrameType.firstFrame:
                    {
                        FCTotalDataLength = (ushort) (((fcData[0] & 0xF0) << 4) | fcData[1]);
                        FCReceivedDataLength = (ushort)(fcData.Length - 3);

                        DatacopyComiftoLocal(fcData);

                        FCBalanceDataLength = (ushort) (FCTotalDataLength - FCReceivedDataLength);

                        if (FCBalanceDataLength != 0 && FCBalanceDataLength < FCTotalDataLength)
                        {
                            retval = true;
                        }
                    }
                    break;
                case FCFrameType.consecutiveFrame:
                    {
                        FCReceivedDataLength += (ushort)(fcData.Length - 3);
                        FCBalanceDataLength = (ushort)(FCTotalDataLength - FCReceivedDataLength);

                        DatacopyComiftoLocal(fcData);

                        if (FCReceivedDataLength == FCTotalDataLength)
                        {
                            retval = true;
                        }                       
                    }
                    break;

            }
            return retval;
        } // FCFramesHandleReceive end 

        private FCFrameType FindFrameType(ushort len)
        {
            FCFrameType retval = 0;

            if (len < Commands.MAXTransmitSize)
            {
                FCsingleframeflag = true;
                retval = FCFrameType.singleFrame;
            }
            else
            {
                FCfirstframeflag = true;
                retval = FCFrameType.firstFrame;
            }

            return retval;
        }

        public void FCDataTransmit(byte[] Senddata) // cmd consider the updateall command and address
        {
            FCTotalDataLength =(ushort)Senddata.Length; // total length of tha transmit data
            FcTxtype = FindFrameType(FCTotalDataLength); // find the frame type to transmit the data to uC
            FCinitialflag = true; // to start send the data to uC

            while(true)
            {
                if(FcTxtype == FCFrameType.singleFrame) 
                {
                    if(FCinitialflag == true)
                    {
                        int cnt = 0;
                        List<byte> singleframedata = new List<byte>();

                        singleframedata.Add((byte)((byte)((FCTotalDataLength & 0x0F00) >> 4) | Commands.FCSingleFrame));
                        singleframedata.Add((byte)(FCTotalDataLength & 0xFF));
                        singleframedata.Add(0x00);

                        while ((cnt < FCTotalDataLength) && (cnt < Commands.MAXTransmitSize))
                        {
                            singleframedata.Add(Senddata[cnt]);
                            cnt++;
                        }

                        FCDatabytesupdate(singleframedata.ToArray());
                        FCTransmit.Length = (byte)singleframedata.Count;
                        MCUTransmitFunction.Transmit(FCTransmit);

                        FCinitialflag = false;
                    }
                    
                    if(Commands.FCrxCbkFlag == true)
                    {
                        if ( (FCRxData[0] & 0x0F) == Commands.FCSingleFrame)
                        {
                            if ( ((FCRxData[2] & 0xF0) >> 4) == Commands.FCAbortstatus )
                            {
                                break;
                            }
                            else if( ((FCRxData[2] & 0xF0) >> 4) == Commands.FCRepeatstatus)
                            {
                                FCinitialflag = true;
                            }
                        }                       
                        Commands.FCrxCbkFlag =  false;
                    }
                }
                else if(FcTxtype == FCFrameType.firstFrame)
                {
                    if(FCinitialflag == true)
                    {
                        int cnt = 0;
                        List<byte> firstFramedata = new List<byte>();

                        firstFramedata.Add((byte)((byte)((FCTotalDataLength & 0x0F00) >> 4) | Commands.FCFirstFrame));
                        firstFramedata.Add((byte)(FCTotalDataLength & 0xFF));
                        firstFramedata.Add(0x00);

                        while ( cnt < Commands.MAXTransmitSize )
                        {
                            firstFramedata.Add(Senddata[cnt]);
                            ++cnt;
                        }

                        FCReceivedDataLength = (ushort)cnt;
                        FCBalanceDataLength = (ushort)(FCTotalDataLength - cnt);

                        FCDatabytesupdate(firstFramedata.ToArray());
                        FCTransmit.Length = (byte)firstFramedata.Count;
                        MCUTransmitFunction.Transmit(FCTransmit);

                        FCinitialflag = false;
                    }

                   if (Commands.FCrxCbkFlag == true)
                   {
                        if ((FCRxData[0] & 0x0F) == Commands.FCFlowcontrolFrame)
                        {

                            if (((FCRxData[2] & 0xF0) >> 4) == Commands.FCAbortstatus)
                            {
                                break;
                            }
                            else if (((FCRxData[2] & 0xF0) >> 4) == Commands.FCSendstatus)  // check this state
                            {                                
                                ushort TransmitDataLength = (ushort)((((FCRxData[0] & 0xF0) << 4) | FCRxData[1]) & 0x0FFF);
                                if (TransmitDataLength == FCReceivedDataLength)
                                {
                                    FCconsecutiveflag = true;
                                    FcTxtype = FCFrameType.consecutiveFrame;
                                }
                            }
                            else if (((FCRxData[2] & 0xF0) >> 4) == Commands.FCRepeatstatus)
                            {
                                FCinitialflag = true;
                            }

                        }
                        Commands.FCrxCbkFlag = false;
                   }

                }
                else if(FcTxtype == FCFrameType.consecutiveFrame)
                {
                    if(FCconsecutiveflag == true)
                    {
                        int index = 0;
                        int cnt = FCReceivedDataLength, i = 0,ballen = FCBalanceDataLength,reslen = FCReceivedDataLength;
                        while (FCBalanceDataLength > 0 )
                        {
                            i = 0;
                            List<byte> consecutiveFramedata = new List<byte>();

                            consecutiveFramedata.Add((byte)((byte)((FCBalanceDataLength & 0x0F00) >> 4) | Commands.FCConsecutiveFrame));
                            consecutiveFramedata.Add((byte)(FCBalanceDataLength & 0xFF));
                            consecutiveFramedata.Add(0x00);

                            while ((i < FCBalanceDataLength) && (i < Commands.MAXTransmitSize))
                            {
                                consecutiveFramedata.Add(Senddata[cnt]);
                                cnt++;
                                ++i;
                            }

                            index++;
                            FCReceivedDataLength += (ushort)i;
                            FCBalanceDataLength = (ushort)(FCBalanceDataLength - i);

                            FCDatabytesupdate(consecutiveFramedata.ToArray());
                            FCTransmit.Length = (byte)consecutiveFramedata.Count;
                            MCUTransmitFunction.Transmit(FCTransmit);

                            while (true)
                            {
                                if (Commands.FCrxCbkFlag == true)
                                {
                                    if ((FCRxData[0] & 0x0F) == Commands.FCFlowcontrolFrame)
                                    {
                                        ushort TransmitDataLength = (ushort)((((FCRxData[0] & 0xF0) << 4) | FCRxData[1]) & 0x0FFF);

                                        if ( TransmitDataLength == FCReceivedDataLength )
                                        {
                                            if ((FCRxData[2] & 0xF0) == Commands.FCSendstatus)
                                            {
                                                break;
                                            }
                                        }
                                        else if (TransmitDataLength == 0)
                                        {
                                             if ((FCRxData[2] & 0xF0) >> 4 == Commands.FCAbortstatus)
                                            {
                                                break;
                                            }
                                        }
                                    }                                   
                                    Commands.FCrxCbkFlag = false;
                                }
                            }
                  
                        }
                        FCconsecutiveflag = false;
                    }

                    #region need changes
                    if (Commands.FCrxCbkFlag == true)
                    {
                        if ((FCRxData[0] & 0x0F) == Commands.FCFlowcontrolFrame)
                        {
                            if ((FCRxData[2] & 0xF0) >> 4 == Commands.FCAbortstatus)
                            {
                                FcTxtype = FCFrameType.frameUnkown;
                                break;
                            }
                        }
                        Commands.FCrxCbkFlag = false;
                    }
                    #endregion
                }

            }
        }

    }
}
