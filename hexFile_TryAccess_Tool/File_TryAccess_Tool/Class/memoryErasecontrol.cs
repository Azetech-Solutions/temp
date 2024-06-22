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
                    TooldataBytemsgUpdate(data);
                    mcuTransmit.Transmit(mcuTransmitmessage);
                    eraseFlag = false;
                }
                
                if (mcuRxData[0] == Commands.Responce_OK)
                {
                    retval = true;
                    mcuRxData[0] = 0xFF;
                    break;
                }
                else if (mcuRxData[0] == Commands.Responce_NOTOK)
                {
                    mcuRxData[0] = 0xFF;
                    eraseFlag = true;
                }

            }
            return retval;
        }



    }
}
