using ComIf;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static File_TryAccess_Tool.Tooltransmit;

namespace File_TryAccess_Tool
{
    public partial class NVM_Form : Form
    {
        private NvmDataHandling nvm;
        public NVM_Form()
        {

            InitializeComponent();
            nvm = new NvmDataHandling();
        }

        private void btnNVMclear_Click(object sender, EventArgs e)
        {
            nvm.NvmClearCmD();
        }

        private void btnNVMreOrg_Click(object sender, EventArgs e)
        {
            nvm.NvmReOrgCMD();
        }

        private void btnNVMupdate_Click(object sender, EventArgs e)
        { 
            nvm.NvmUpdateCMD();
        }

        private void btnGetAllNvmData_Click(object sender, EventArgs e)
        {
            List<byte> get = new List<byte>();
            FCRxData[2] = 0xF0;
            byte cmd = Commands.NVMGetAlldata;
            uint address = 0x08010000;
            get.Add(cmd);
            get.Add(0x00);
            get.Add(0x00);
            get.Add((byte)(address >> 24));
            get.Add((byte)(address >> 16));
            get.Add((byte)(address >> 8));
            get.Add((byte)(address));

            FCDatabytesupdate(get.ToArray());

            MCUTransmitFunction.Transmit(FCTransmit);
        }
    }
}
