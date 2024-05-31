using ComIf;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace File_TryAccess_Tool
{
    public partial class NVM_Form : Form
    {
        private static Channel Trns_MCU;
        private static TxMessage Trns_MCU_Data;
        private RxMessage Rcve_MCU;
        private SerialPort serialport1;
        public NVM_Form(Channel myChannel, TxMessage tx, RxMessage rx, SerialPort s)
        {
            InitializeComponent();

            Trns_MCU = myChannel;
            Trns_MCU_Data = tx;
            RxMessage Rcve_MCU = rx;
            serialport1 = s;
        }

    }
}
