using File_TryAccess_Tool.Class;
using System;
using System.Collections.Generic;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Xml;
using System.Xml.Linq;
using System.Threading;

namespace File_TryAccess_Tool
{
    public partial class NVM_Form : Form
    {
        private NvmDataHandling nvm;
        private FlowControlHandling flowhandle = new FlowControlHandling();
        private Thread flashThread;
        private string OpenedXMLfilepath = null;
        preloadHandling waitprocess;
        public NVM_Form()
        {
            InitializeComponent();
            nvm = new NvmDataHandling(tvNvmBlk);
        } // nvm form end

        private void btnNVMclear_Click(object sender, EventArgs e)
        {
            waitprocess = new preloadHandling();
            var clear = MessageBox.Show("Do you want Clear Nvm Memory", "Alert", MessageBoxButtons.YesNo, MessageBoxIcon.Question,MessageBoxDefaultButton.Button2);
            if (clear == DialogResult.Yes)
            {
                flashThread = new Thread(() => {

                    waitprocess.showWaitState();
                    nvm.NvmClearCmD();
                    waitprocess.closeWaitState();
                });
                flashThread.Start();               
            }
        } // clear end

        private void btnNVMreOrg_Click(object sender, EventArgs e)
        {
            waitprocess = new preloadHandling();
            var reorg = MessageBox.Show("Do you want Reorg Nvm Memory", "Alert", MessageBoxButtons.YesNo, MessageBoxIcon.Question,MessageBoxDefaultButton.Button2);
            if (reorg == DialogResult.Yes)
            {
                flashThread = new Thread(() =>
                {
                    waitprocess.showWaitState();
                    nvm.NvmReOrgCMD();
                    waitprocess.closeWaitState();

                });
                flashThread.Start();
            }            
        } // reorg end

        private void btnNVMupdate_Click(object sender, EventArgs e)
        {
            waitprocess = new preloadHandling();
            flashThread = new Thread(() => {
                string SingleNVMBlockData = rtbxNVMDataOut.Text.Replace(" ","");

                waitprocess.showWaitState();
                nvm.NvmUpdateCMD(SingleNVMBlockData);
                waitprocess.closeWaitState();
            });
            flashThread.Start();
        } //update end

        private void btnGetAllNvmData_Click(object sender, EventArgs e)
        {
            waitprocess = new preloadHandling();
            flashThread = new Thread(() => {
                if (FlowControlHandling.FcRxtype == FlowControlHandling.FCFrameType.frameUnkown)
                {
                    List<byte> get = new List<byte>();
                    UInt32 address = Convert.ToUInt32(Xmlfilehandling.setStartAddress[5].InnerText);

                    get.Add(Commands.NVMGetAlldata);
                    get.Add(0x00);
                    get.Add(0x00);
                    get.Add((byte)(address >> 24));
                    get.Add((byte)(address >> 16));
                    get.Add((byte)(address >> 8));
                    get.Add((byte)(address));                

                    try
                    {
                        waitprocess.showWaitState();
                        flowhandle.FCDataReceive(get.ToArray());
                        if (FlowControlHandling.FCReceivedData.Count == FlowControlHandling.FCTotalDataLength)
                        {
                            waitprocess.closeWaitState();
                            for (int i = 0; i < FlowControlHandling.FCReceivedData.Count; i++)
                            {
                                rtbxNVMDataOut.Text += FlowControlHandling.FCReceivedData[i].ToString("X2") + " ";
                                Log.Message("Data  " + i.ToString() + "  " + FlowControlHandling.FCReceivedData[i].ToString("X2"));
                            }                                                
                        }
                   
                    }
                    catch (Exception ex) { MessageBox.Show("NVM", ex.Message); }                
                }
                else
                {
                    MessageBox.Show("Please wait Data Processed");
                }
            });
            flashThread.Start();

        } // getall end 

        private void btnNVMexport_Click(object sender, EventArgs e)
        {            
            string path = null, needchangestringvalue = rtbxNVMDataOut.Text;
            SaveFileDialog sfd = new SaveFileDialog();
            try
            {

                sfd.Filter = "XML files (*.xml)|*.xml";

                if (sfd.ShowDialog() == DialogResult.OK)
                {
                    path = sfd.FileName;

                   if(path != null)
                    {
                        nvm.NvmExportXML(needchangestringvalue.Replace(" ", ""), path);
                        MessageBox.Show("Data Saved!!!","Alert",MessageBoxButtons.OK,MessageBoxIcon.None);
                    }
                }
                
            }
            catch(Exception ex) { MessageBox.Show(ex.Message); }
        } // export end

        private void btnNVMimport_Click(object sender, EventArgs e)
        {           
            try
            {
                OpenFileDialog ofd = new OpenFileDialog();
                ofd.Filter = "XML files (*.xml)|*.xml";

                if (ofd.ShowDialog() == DialogResult.OK)
                {
                    OpenedXMLfilepath = ofd.FileName;

                    if (OpenedXMLfilepath != null)
                    {
                        nvm.NvmImportXML(OpenedXMLfilepath);
                        ViewvalidNvmBlock(OpenedXMLfilepath);
                    }
                }
            }
            catch(Exception ex) { MessageBox.Show(ex.Message); }                                 
        } // import end

        private void ViewvalidNvmBlock(string path)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(path);
            XmlNodeList node = doc.GetElementsByTagName("nvmblock");

            XmlNode temp = node[0];

            foreach (XmlNode node2 in node)
            {
                if (Convert.ToInt32(temp.ChildNodes[3].InnerText) < Convert.ToInt32(node2.ChildNodes[3].InnerText))
                {
                    temp = node2;
                }
            }
            int i = 0;
            while (i < temp.InnerText.Length)
            {
                rtbxNVMDataOut.Text += temp.InnerText.Substring(i, 2) + " ";
                i += 2;
            }
        } // ViewvalidNvmBlock end

        private void btnNVMupdateAll_Click(object sender, EventArgs e)
        {
            waitprocess = new preloadHandling();
            flashThread = new Thread(() => {
                UInt32 address = Convert.ToUInt32(Xmlfilehandling.setStartAddress[5].InnerText);
                List<byte> FCtxdata = new List<byte>();

                FCtxdata.Add(Commands.NVMUpdateAlldata);
                FCtxdata.Add(0x00);
                FCtxdata.Add(0x00);
                FCtxdata.Add((byte)(address >> 24));
                FCtxdata.Add((byte)(address >> 16));
                FCtxdata.Add((byte)(address >> 8));
                FCtxdata.Add((byte)(address));

                waitprocess.showWaitState();
                nvm.UpdateAllCMD(OpenedXMLfilepath, FCtxdata.ToArray());
                waitprocess.closeWaitState();
            });
            flashThread.Start();

        } // update all

        private void btnClearlog_Click(object sender, EventArgs e)
        {
            var log = MessageBox.Show("Do you want to clear the NVM Log", "Alert",
                                       MessageBoxButtons.YesNo, MessageBoxIcon.Warning,MessageBoxDefaultButton.Button2);

            if(log == DialogResult.Yes)
            {
                rtbxNVMDataOut.Text = "";
            }
        }

        private void NVM_Form_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (flashThread != null && flashThread.IsAlive)
            {
                flashThread.Abort(); // Caution: Thread.Abort is not recommended due to abrupt termination
                Log.Message("NVM operation Aborted.");
            }
        }

        private void rtbxNVMDataOut_KeyPress(object sender, KeyPressEventArgs e)
        {
            Char key = e.KeyChar;
            if ((key >= 'A' && key <= 'F') || (key >= 'a' && key <= 'f') || (key >= '0' && key <= '9') || key == ' ') // 32 is space char
            {
                e.Handled = false;
            }
            else { e.Handled = true; }
        }
    }
}
