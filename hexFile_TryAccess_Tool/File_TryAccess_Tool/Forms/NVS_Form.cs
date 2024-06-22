using ComIf;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Threading;
using System.Windows.Forms;
using static File_TryAccess_Tool.Tooltransmit;
using static File_TryAccess_Tool.Log;

namespace File_TryAccess_Tool
{
    public partial class NVS_Form : Form
    {
        private NVSDataHandling nvsDataHandling;
        private List<Button> buttons;
        private List<string> userhexData;

        private int Btop = 87, Bleft = 36, cnt = 0, blkcnt = 1, pressedbtn = 0,reftag=0;
        private bool btnclkchk = false;
        public NVS_Form()
        {
            InitializeComponent();
            nvsDataHandling = new NVSDataHandling();
            buttons = new List<Button>();
            userhexData = new List<string>();
        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            string userinput = rtbxDataOut.Text;

            if (nvsDataHandling.NVSflashstartcommands())
            {
                nvsDataHandling.NVSDataTransmit(nvsDataHandling.NextblockAdd,nvsDataHandling.StringTobyte(userinput));
            }
        }

        private void rtbxDataOut_TextChanged(object sender, EventArgs e)
        {
            int i = rtbxDataOut.TextLength;
            if (rtbxDataOut.TextLength == 0) { lblLength.Text = "-"; }
            else { lblLength.Text = Convert.ToString(i); }
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

        private void btnAdd_Click(object sender, EventArgs e)
        {
            const string BlkName = "Block-";
            
            if (((cnt >= 0) && (cnt <10)))
            {
                userhexData.Add(rtbxDataOut.Text);

                Button UserInput = new Button();

                UserInput.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, 
                                                                System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                UserInput.Location = new System.Drawing.Point(Bleft, Btop);
                UserInput.Size = new System.Drawing.Size(140, 25);
                UserInput.TabIndex = 3;
                UserInput.Text = BlkName + blkcnt.ToString();

                UserInput.Tag = reftag; // user reference

                UserInput.Name = "btn"+UserInput.Text;
                UserInput.UseVisualStyleBackColor = false;
                UserInput.Cursor = System.Windows.Forms.Cursors.Hand;
                UserInput.Click += new System.EventHandler(this.NVSDataBlock_Click);
                this.Controls.Add(UserInput);
                UserInput.BringToFront();

                buttons.Add(UserInput); // dynamic button was added the buttons list
                flpBlockAdded.Controls.Add(UserInput);                
                Btop += 35;
                cnt++;
                blkcnt++;
                reftag++;
                rtbxDataOut.Clear();
            }
            else { }
          
        }
        private void btnRemove_Click(object sender, EventArgs e)
        {
            if (btnclkchk == true)
            {
                rtbxDataOut.Clear();
                if (pressedbtn == 0 && (pressedbtn) < 10) // change check
                {
                    Controls.Remove(buttons[pressedbtn]);  // Removed in form control collection
                    buttons.RemoveAt(pressedbtn);  // button was removed in list
                                                   //rtbxDataOut.Text = userhexData[pressedbtn];
                    userhexData.RemoveAt(pressedbtn);  // hex data was removed in list
                    flpBlockAdded.Controls.RemoveAt(pressedbtn);  // removed in flow layout panal
                    lblUpdateBlkName.Text = "";
                    blkcnt = cnt;
                    reftag--;
                    cnt--;
                    pressedbtn = 0; // for error check (reset)
                }
                btnclkchk = false;
            }
           
        }

        private void NVSDataBlock_Click(object sender, EventArgs e)
        {
            Button b = (Button)sender;
            pressedbtn =(int)b.Tag;
            lblUpdateBlkName.Text = b.Text;

            rtbxDataOut.Text = userhexData[pressedbtn]; 

            btnclkchk = true; // to check the added button is pressed
        }

    }
}
