using System;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Security.Cryptography;
using System.Windows.Forms;
using ComIf;

namespace File_TryAccess_Tool
{
    public partial class Form1 : Form
    {
        //DateTime dt = DateTime.Now;
        //string dtn = dt.ToLongTimeString();

        TakeHexdata Hexval = new TakeHexdata();

        bool IsFileVaild = false;

        private string FilePath = null, flashBaseAddress = null, RxMessageDataIN = null, FlashEraseMry = null;
        private string Fileline = null, hexOffset = null, hexDatelength = null, HexData = null,hexRecordType = null;

        private string rxdata = null;

        //Channel TxRX = new Channel("Trasmit_MCU", ChannelType.String,TransmitToMCU,TransmitToMCU_Error_nofi);
        //TxMessage TxRX_id = new TxMessage(0xB5,1);
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] Ports = SerialPort.GetPortNames();
            CBoxComPort.Items.AddRange(Ports);

            chkBoxFlashMode.Checked = true;
            chkBoxNVSMode.Checked = false;
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            RxMessageDataIN += serialPort1.ReadExisting();
        }

        private void chkBoxNVSMode_CheckedChanged(object sender, EventArgs e)
        {
            if(chkBoxNVSMode.Checked)
            {
                chkBoxNVSMode.Checked = true;
                chkBoxFlashMode.Checked = false;
            }
            //else { chkBoxNVSMode.Checked = false; }
        }

        private void chkBoxFlashMode_CheckedChanged(object sender, EventArgs e)
        {
            if(chkBoxFlashMode.Checked)
            {
                chkBoxFlashMode.Checked = true;
                chkBoxNVSMode.Checked = false;
            }
            //else { chkBoxFlashMode.Checked = false; }
        }
        private void BtnSearch_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                tBoxView.Text = "";
                FilePath = null;
                try
                {
                    using (OpenFileDialog ofd = new OpenFileDialog())
                    {
                        ofd.Filter = "Hex files (*.Hex)|*.Hex|All files (*.*)|*.*"; ;
                        if (ofd.ShowDialog() == DialogResult.OK)
                        {
                            string checkFileValid = null;
                            //path save in a string to open the particular file
                            FilePath = ofd.FileName;
                            tBoxView.Text = ofd.FileName;
                            StreamReader sr = new StreamReader(FilePath);

                            if ((checkFileValid = sr.ReadLine()) != null)
                            {
                                if (checkFileValid[0] == ':')
                                {
                                    IsFileVaild = true;
                                }
                                else { MessageBox.Show("Invalid File Format", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
                            }   
                            sr.Close();
                        }
                    }
                }
                catch (Exception ex) { MessageBox.Show(ex.Message,"Error", MessageBoxButtons.OK, MessageBoxIcon.Error); tBoxView.Text = ""; }

            }
            else { MessageBox.Show("Please Select the Port", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }

        } // end Searchbtn

        private void MStripDisconnect_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
                progressBar1.Value = 0;
            }
        } // end port disconnected

        private void MStripPortConnect_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = CBoxComPort.Text;
                serialPort1.BaudRate = Convert.ToInt32(CboxBaudRate.Text);
                serialPort1.DataBits = Convert.ToInt32(CboxDataBits.Text);
                serialPort1.StopBits = (StopBits)Enum.Parse(typeof(StopBits), CboxStopBit.Text);
                serialPort1.Parity = (Parity)Enum.Parse(typeof(Parity), CboxParityBit.Text);

                serialPort1.Open();
                progressBar1.Value = 100;
            }

            catch (Exception err)
            {
                MessageBox.Show(err.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        } // end port connected

        private void BtnTransmit_Click(object sender, EventArgs e)
        {
            bool Modestatus = true;
            string modeupdate = null;
            string flashErase = null;
            string flashStart = "F50000000000000000000000000000000000000000";
            string NvsMode    = "FA0000000000000000000000000000000000000000";
            string FlashMode  = "FB0000000000000000000000000000000000000000";

            modeupdate = flashStart;

            while (true)
            {
                if(Modestatus)
                {
                    serialPort1.Write(modeupdate+" ");
                    Modestatus = false;
                }

                if (RxMessageDataIN == "00")
                {
                    RxMessageDataIN = null;

                    if(modeupdate == flashStart)
                    {
                        if (chkBoxNVSMode.Checked && !chkBoxFlashMode.Checked)
                        {
                            modeupdate = NvsMode;
                            Modestatus = true;
                        }
                        else if (chkBoxFlashMode.Checked && !chkBoxNVSMode.Checked)
                        {
                            modeupdate = FlashMode;
                            Modestatus = true;
                        }
                    }
                    else
                    {
                        if (modeupdate == NvsMode)
                        {
                            Modestatus = true;
                            break;
                        }

                        if (modeupdate == flashErase)
                        {
                            Modestatus = true;
                            break;
                        }

                        if (modeupdate == FlashMode)
                        {
                            if (cBoxAppAddressSelect.Text == "App1")
                            {
                                FlashEraseMry = "08006000";
                                tBoxOutData.Text = FlashEraseMry;
                            }
                            else if (cBoxAppAddressSelect.Text == "App2")
                            {
                                FlashEraseMry = "08016000";
                                tBoxOutData.Text = FlashEraseMry;
                            }

                            flashErase = "FE" + FlashEraseMry + "00000000000000000000000000000000";

                            modeupdate = flashErase;
                            Modestatus = true;
                        }                       
                    }
                }
                else if (RxMessageDataIN == "01")
                {
                    RxMessageDataIN = null;
                    Modestatus = true;
                }

            } //end of the flashstart , flash mode, erase mode 

            if(Modestatus == true)
            {
                if (IsFileVaild == true) //&& serialPort1.IsOpen
                {
                    bool Flh_CompleteStatus = false;
                    StreamReader sr = new StreamReader(FilePath);
                    string Flashcompleted = null;
                    while ((Fileline = sr.ReadLine()) != null)
                    {
                        if (Fileline.Count() < 11)
                        {
                            MessageBox.Show("Invalid Data", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                        else
                        {
                            if (Fileline[0] == ':')
                            {
                                hexDatelength = Hexval.ReadByte(Fileline, 1);
                                hexOffset = Hexval.Readword(Fileline, 3);
                                hexRecordType = Hexval.ReadByte(Fileline, 7);
                                //tBoxOutData.Text = type;
                                HexData = Hexval.ReadDatas(Fileline, 9, Convert.ToUInt16(hexDatelength, 16));

                                try
                                {
                                    switch (Convert.ToInt16(hexRecordType))
                                    {
                                        case 0:
                                            {
                                              bool change = true;
                                                while (true)
                                                {
                                                    
                                                    if (change)
                                                    {
                                                        if (flashBaseAddress != null)
                                                        {
                                                            var mryadd = flashBaseAddress + hexOffset;
                                                            mryadd = "FD" + mryadd + HexData;
                                                            serialPort1.Write(mryadd+"  ");
                                                        }
                                                        change=false;
                                                    }
                                                    
                                                    if (RxMessageDataIN == "00")
                                                    {
                                                        RxMessageDataIN = null;
                                                        break;
                                                    }
                                                    else if(RxMessageDataIN == "01")
                                                    {
                                                        RxMessageDataIN = null;
                                                        change = true;
                                                    }
                                                }
                                                
                                            }
                                            break;
                                        case 1:
                                            {
                                                flashBaseAddress = null;
                                                hexOffset = null;
                                                HexData = null;
                                                hexRecordType = null;
                                                Flh_CompleteStatus = true;
                                            }
                                            break;
                                        case 4:
                                            {
                                                if (HexData.Length == 4)
                                                {
                                                    flashBaseAddress = HexData;
                                                }
                                            }
                                            break;
                                        case 5:
                                            {

                                            }
                                            break;
                                        default:
                                            {
                                                MessageBox.Show("Invaid Switchcase ", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                            }
                                            break;
                                    }
                                }
                                catch (Exception ex) { MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
                            }
                            else
                            {
                                MessageBox.Show("Invalid File Format", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            }
                        }
                    }
                    sr.Close(); // file closed

                    if (Flh_CompleteStatus == true)
                    {
                        if (cBoxAppAddressSelect.Text == "App1")
                        {
                            FlashEraseMry = "08006000";
                            tBoxOutData.Text = FlashEraseMry;
                        }
                        else if (cBoxAppAddressSelect.Text == "App2")
                        {
                            FlashEraseMry = "08016000";
                            tBoxOutData.Text = FlashEraseMry;
                        }

                        Flashcompleted = "FC" + FlashEraseMry + "00000000000000000000000000000000";

                        bool chg_status = true;
                        while (true)
                        {
                            if(chg_status == true)
                            {
                                serialPort1.Write(Flashcompleted+" ");
                                chg_status = false;
                            }

                            if (RxMessageDataIN == "00")
                            {
                                tBoxOutData.AppendText("\nFc Completed");
                                RxMessageDataIN = null;
                                break;
                            }
                            else if (RxMessageDataIN == "01")
                            {
                                RxMessageDataIN = null;
                                chg_status = true;
                            }
                        }
                        Flh_CompleteStatus = false;
                    }                 
                }
                else
                {
                    MessageBox.Show("Please Select the valid file Format", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else { MessageBox.Show("Please Select Mode ", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }
    }

}

class TakeHexdata
{
    public string ReadByte(string line, int index = 0)
    {
        return line.Substring(index, 2);
    }

    public string Readword(string line, int index = 0)
    {
        return line.Substring(index, 4);
    }

    public string ReadDatas(String line, int index = 0,int size = 0 )
    {
        return line.Substring(index, (size*2));
    }
}