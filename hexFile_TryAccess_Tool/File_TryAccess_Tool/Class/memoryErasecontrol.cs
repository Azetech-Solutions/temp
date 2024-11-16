using static File_TryAccess_Tool.Tooltransmit;
using static File_TryAccess_Tool.Log;
using System;
using System.Threading;
using File_TryAccess_Tool.Class;

namespace File_TryAccess_Tool
{    
    public class memoryErasecontrol
    {
        //Tooltransmit toolTransmit;
        public bool eraseFlag = false;

        preloadHandling waitprocess;
        public memoryErasecontrol() {  }


        public bool Memoryerasecommand(byte[] data)
        {
            bool retval = false;
            waitprocess = new preloadHandling();


            while (true)
            {
                if (eraseFlag == true)
                {
                    FlashDatabytesupdate(data);
                    MCUTransmitFunction.Transmit(FlashDataTransmit);
                    waitprocess.showWaitState();
                    eraseFlag = false;
                }
                
                if (MCUStatusRxData[0] == Commands.Responce_OK)
                {
                    retval = true;
                    MCUStatusRxData[0] = 0xFF;
                    waitprocess.closeWaitState();
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
