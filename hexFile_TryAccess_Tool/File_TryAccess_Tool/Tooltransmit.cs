using ComIf;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web;

namespace File_TryAccess_Tool
{
    public class Tooltransmit
    {
        public Channel mcuTransmit;
        public TxMessage mcuTransmitmessage;
        public RxMessage receivemcuData;
        public SerialPort serialPort1;

        public byte[] mucRxData = new byte[] {0xFF};
        public Tooltransmit(SerialPort s)
        {
            mcuTransmit = new Channel("mcuTransmit", ChannelType.String, mcuDataTransmit, mcuDataTransmitErrnofi);
            mcuTransmitmessage = new TxMessage(0xB3, 21);
            receivemcuData = new RxMessage(0xB5, 1, mucResponce_Rxcbk);
            mcuTransmit.RegisterRxMessage(receivemcuData);
            serialPort1 = s;
        } // end

        public void mucResponce_Rxcbk(byte Length, byte[] Data)
        {
            for (int i = 0; i < Length; i++)
            {
                mucRxData[i] = Data[i];
            }
        } // end

        public void mcuDataTransmitErrnofi(uint Debug0, uint Debug1)
        {
            Log.Error($"Debug0 -{Debug0}, Debug1 -{Debug1}");
        } // end

        public void mcuDataTransmit(ushort Length, byte[] Data)
        {
            serialPort1.Write(Data, 0, Length);
        } // end
        public void tooldatamsgUpdate(string Txdata)
        {
            char[] loadComifData = Txdata.ToCharArray();

            int Length = loadComifData.Length;
            int i = 0,j = 0;

            if ((Length % 2) == 0)
            {
                while (Length > 0)
                {
                    byte Data = 0;

                    Data = (byte) ((((byte)loadComifData[i] - 0x30) << 4) | ((byte)loadComifData[i + 1] - 0x30));

                    mcuTransmitmessage.Data[j] = Data;

                    i += 2; // Move to next step
                    Length -= 2;
                    j++;
                    if(Length == 0)
                    {
                        break;
                    }
                }
            }
        }//end
    }
}
