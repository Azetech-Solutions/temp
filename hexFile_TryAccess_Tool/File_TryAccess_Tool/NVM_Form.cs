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
        private Tooltransmit toolTransmit;
        public NVM_Form(Tooltransmit s)
        {
            InitializeComponent();
            toolTransmit = s;
        }

    }
}
