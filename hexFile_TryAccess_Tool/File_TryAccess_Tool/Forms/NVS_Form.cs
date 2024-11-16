using ComIf;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Threading;
using System.Windows.Forms;
using static File_TryAccess_Tool.Tooltransmit;
using static File_TryAccess_Tool.Log;
using System.IO;
using System.Net.Http.Headers;

namespace File_TryAccess_Tool
{
    public partial class NVS_Form : Form
    {
        private NVSDataHandling nvsDataHandling;
        private List<Button> Addbuttons;
        private List<string> StringNVShexData;
        private Thread flashThread;

        private int Btop = 87, Bleft = 56, cnt = 0,reftag=0, pressedbtn = 0;
        private bool btnclkchk = false;
        public NVS_Form()
        {
            string basePath = AppDomain.CurrentDomain.BaseDirectory;
            string filePath = Path.Combine(basePath, "Nvsblockdata.xml");

            InitializeComponent();
            nvsDataHandling = new NVSDataHandling(filePath);
            Addbuttons = new List<Button>();
            StringNVShexData = new List<string>();
        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            string userinput = rtbxDataOut.Text;

            flashThread = new Thread(() => {
                
                if (userinput != null)
                {
                    Log.Message("NVS data update start");
                    nvsDataHandling.NVSUpdate(userinput.Replace(" ", ""));

                    Log.Message("NVS data update End");
                }
                else { MessageBox.Show("Enter a Valid Data", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Warning); }
            });

            flashThread.Start();   
        }

        private void rtbxDataOut_TextChanged(object sender, EventArgs e)
        {
            if (rtbxDataOut.TextLength == 0)
            { 
                lblLength.Text = "-";
            }
            else 
            { 
                lblLength.Text = Convert.ToString(rtbxDataOut.Text.Replace(" ", "").Length/ 2); 
            }
        }

        private void rtbxDataOut_KeyPress(object sender, KeyPressEventArgs e)
        {
            Char key = e.KeyChar;
            if ((key >= 'A' && key<= 'F') || (key >= 'a' && key <= 'f') || (key >= '0' && key <= '9') || key == ' ') // 32 is space char
            {
                e.Handled = false;
            }
            else { e.Handled = true; }
        }

        private void NVS_Form_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (flashThread != null && flashThread.IsAlive)
            {
                flashThread.Abort(); // Caution: Thread.Abort is not recommended due to abrupt termination                
            }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            if (((cnt >= 0) && (cnt <10)))
            {
                DynamicButtonAdd();

                Btop += 35;
                cnt = ++reftag;
                
                rtbxDataOut.Clear();
            }
          
        }

        private void DynamicButtonAdd()
        {
            // Nvs Hexdata added to string list
            StringNVShexData.Add(rtbxDataOut.Text);

            Button UserInputBtn = new Button();

            UserInputBtn.Font = new System.Drawing.Font("Microsoft Tai Le", 12F, System.Drawing.FontStyle.Bold,
                                                            System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            
            UserInputBtn.Location = new System.Drawing.Point(Bleft, Btop);
            UserInputBtn.Size = new System.Drawing.Size(90, 25);

            UserInputBtn.Text = "+"+ reftag.ToString();
            UserInputBtn.TabIndex = 3;

            UserInputBtn.Tag = reftag; // user reference

            UserInputBtn.UseVisualStyleBackColor = false;

            UserInputBtn.Cursor = System.Windows.Forms.Cursors.Hand;
            UserInputBtn.Click += new System.EventHandler(this.NVSDataBlock_Click);

            //this.Controls.Add(UserInputBtn);
            UserInputBtn.BringToFront();

            Addbuttons.Add(UserInputBtn); // dynamic button was added the buttons list
            
            flowLayoutPanelBtnAdd.Controls.Add(UserInputBtn);
            

            
        }

        private void btnRemove_Click(object sender, EventArgs e)
        {
            Control buttonToRemove = this.Controls.Find("dynamicButton", true).FirstOrDefault();
            
            rtbxDataOut.Clear();
            try {

                if (Addbuttons.Count != 0U ) // change check
                {
                    Controls.Remove(Addbuttons[Addbuttons.Count - 1]);  // Removed in form control collection
                    flowLayoutPanelBtnAdd.Controls.RemoveAt(flowLayoutPanelBtnAdd.Controls.Count - 1);  // removed in flow layout panal

                    StringNVShexData.RemoveAt(StringNVShexData.Count - 1);  // hex data was removed in list
                    Addbuttons.RemoveAt(Addbuttons.Count - 1);  // button was removed in list
                                                                //rtbxDataOut.Text = userhexData[pressedbtn];                
                    lblUpdateBlkName.Text = "";
                    cnt = --reftag;

                    pressedbtn = 0; // for error check (reset)
                }
            }
            catch(Exception ex) { MessageBox.Show(ex.Message); }
        }

        private void NVSDataBlock_Click(object sender, EventArgs e)
        {
            Button b = (Button)sender;
            rtbxDataOut.Text = StringNVShexData[ ((int)b.Tag) ];
        }

    }
}
