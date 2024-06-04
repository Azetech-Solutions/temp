using ComIf;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace File_TryAccess_Tool
{
    public class memoryErasecontrol
    {
        Tooltransmit toolTransmit;
        public bool eraseFlag = false;

        public memoryErasecontrol(Tooltransmit s) { toolTransmit = s; }


        public bool Memoryerasecommand(string data)
        {
            bool retval = false;
            while (true)
            {
                if (eraseFlag == true)
                {
                    toolTransmit.tooldatamsgUpdate(data);
                    //mainform.TxMsgUpdate(data);  // check this changes
                    toolTransmit.mcuTransmit.Transmit(toolTransmit.mcuTransmitmessage);
                    //Trns_MCU.Transmit(Trns_MCU_Data);
                    eraseFlag = false;
                }
                
                if (toolTransmit.mucRxData[0] == 0x00)
                {
                    retval = true;
                    toolTransmit.mucRxData[0] = 0xFF;
                    //MessageBox.Show("Success");
                    break;
                }
                else if (toolTransmit.mucRxData[0] == 0x01)
                {
                    toolTransmit.mucRxData[0] = 0xFF;
                    eraseFlag = true;
                }

            }
            return retval;
        }



    }
}
