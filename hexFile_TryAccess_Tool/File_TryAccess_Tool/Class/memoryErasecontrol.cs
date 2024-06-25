using static File_TryAccess_Tool.Tooltransmit;
using static File_TryAccess_Tool.Log;

namespace File_TryAccess_Tool
{
    public class memoryErasecontrol
    {
        //Tooltransmit toolTransmit;
        public bool eraseFlag = false;

        public memoryErasecontrol() {  }


        public bool Memoryerasecommand(byte[] data)
        {
            bool retval = false;
            while (true)
            {
                if (eraseFlag == true)
                {
                    FlashDatabytesupdate(data);
                    MCUTransmitFunction.Transmit(FlashDataTransmit);
                    eraseFlag = false;
                }
                
                if (MCUStatusRxData[0] == Commands.Responce_OK)
                {
                    retval = true;
                    MCUStatusRxData[0] = 0xFF;
                    break;
                }
                else if (MCUStatusRxData[0] == Commands.Responce_NOTOK)
                {
                    MCUStatusRxData[0] = 0xFF;
                    eraseFlag = true;
                }

            }
            return retval;
        }



    }
}
