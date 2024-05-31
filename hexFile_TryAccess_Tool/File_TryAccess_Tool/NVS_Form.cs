using ComIf;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Windows.Forms;

namespace File_TryAccess_Tool
{
    public partial class NVS_Form : Form
    {
        private static Channel Trns_MCU;
        private static TxMessage Trns_MCU_Data;
        private RxMessage Rcve_MCU;
        private SerialPort serialport1;

        private List<Button> buttons = new List<Button>();
        private List<string> rtbxData = new List<string>();
        public NVS_Form(Channel myChannel,TxMessage tx,RxMessage rx,SerialPort s)
        {
            InitializeComponent();

            Trns_MCU = myChannel;
            Trns_MCU_Data = tx;
            RxMessage Rcve_MCU = rx;
            serialport1 = s;
        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            string s = rtbxDataOut.Text;
            char[] arr = s.ToCharArray();


            for(int i = 0; i < arr.Length; i++)
            {
                Trns_MCU_Data.Data[i] = (byte)arr[i];
            }
            Trns_MCU.Transmit(Trns_MCU_Data);
            
        }

        private int Btop = 87, Bleft = 36, cnt = 5, blkcnt = 1;

        private void rtbxDataOut_TextChanged(object sender, EventArgs e)
        {
            int i = rtbxDataOut.TextLength;
            if (i == 0) { lblLength.Text = "-"; }
            else { lblLength.Text = Convert.ToString(i); }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            const string BlkName = "Block-";
            rtbxData.Add(rtbxDataOut.Text);
            while (cnt != 0)
            {
                Button UserInput = new Button();

                UserInput.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                UserInput.Location = new System.Drawing.Point(Bleft, Btop);
                UserInput.Size = new System.Drawing.Size(140, 25);
                UserInput.TabIndex = 3;
                UserInput.Text = BlkName + blkcnt.ToString();
                UserInput.Name = "btn"+UserInput.Text;
                UserInput.UseVisualStyleBackColor = false;
                UserInput.Cursor = System.Windows.Forms.Cursors.Hand;
                UserInput.Click += new System.EventHandler(this.NVSDataBlock_Click);
                this.Controls.Add(UserInput);
                UserInput.BringToFront();
                
                flpBlockAdded.Controls.Add(UserInput);
                buttons.Add(UserInput); // added list
                Btop += 35;
                cnt--;

                if(blkcnt == 5) { blkcnt = 0; }
                blkcnt++;
                rtbxDataOut.Clear();
                break;
            }
          
        }
        private void btnRemove_Click(object sender, EventArgs e)
        {
            try
            {   rtbxDataOut.Clear();
                int Bindex = buttons.Count;  // Find the index in the list
                rtbxDataOut.Text = rtbxData[Bindex - 1];
                if (Bindex > 0 && Bindex <= 5)
                {
                    Controls.Remove(buttons[Bindex - 1]);  // Remove from control collection
                    buttons.RemoveAt(Bindex - 1);  // Remove from list
                    rtbxData.RemoveAt(Bindex - 1);
                    flpBlockAdded.Controls.RemoveAt(Bindex - 1);
                    lblUpdateBlkName.Text = "";
                    if (blkcnt == 0) { blkcnt = 1; } else { blkcnt = Bindex; }
                    cnt++;
                }
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }

        private void NVSDataBlock_Click(object sender, EventArgs e)
        {
            NVSCollection btncheck = new NVSCollection();
            Button b = (Button)sender;
            string s= b.Text;
            lblUpdateBlkName.Text = s;
            int i = btncheck.findButton(s);

            rtbxDataOut.Text = rtbxData[i];
        }
    }

    public class NVSCollection
    {
        public int findButton(string s)
        {
            int retval = 5;
            switch (s)
            {
                case "Block-1":{ retval= 0;}
                break;
                case "Block-2":{ retval= 1;}
                break;
                case "Block-3":{ retval= 2; }
                break;
                case "Block-4":{ retval= 3; }
                break;
                case "Block-5":{ retval= 4; }
                break;
            }

            return retval;
        }

    }
}
