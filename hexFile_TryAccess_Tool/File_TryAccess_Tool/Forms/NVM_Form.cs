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
    }
}
