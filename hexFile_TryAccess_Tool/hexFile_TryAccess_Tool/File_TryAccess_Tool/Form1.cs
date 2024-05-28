using System;
using System.Configuration;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Windows.Forms;
using System.Xml.Linq;
using ComIf;

namespace File_TryAccess_Tool
{
    public partial class Form1 : Form
    {
        //obj creation
        TakeHexdata Hexval = new TakeHexdata();

        // Channel Creation Tx & Rx
        public Channel Trns_MCU;
        public TxMessage Trns_MCU_Data;
        public RxMessage Rcve_MCU;

        public byte[] RxData = new byte[1] { 0xFF };
        // flag creations
        bool IsFileVaild = false;
        
        // properties creation
        private string FilePath = null, flashBaseAddress = null, RxMessageDataIN = null, FlashEraseMry = null;
        private string Fileline = null, hexOffset = null, hexDatelength = null, HexData = null,hexRecordType = null; // these variables are used to store the Hexfile data's
        private uint CKsum = 0; // used to find the checksum
        public Form1()
        {
            InitializeComponent();         
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] Ports = SerialPort.GetPortNames();
            CBoxComPort.Items.AddRange(Ports);

			Trns_MCU = new Channel("Trasmit_MCU", ChannelType.Number, TransmitToMCU, TransmitToMCU_Error_nofi);
            Trns_MCU_Data = new TxMessage(0xB3, 21);
            Rcve_MCU = new RxMessage(0xB5, 1, Responce_Rxcbk);
            Trns_MCU.RegisterRxMessage(Rcve_MCU);

            loadDefaultValues();
            chkBoxFlashMode.Checked = true;
            chkBoxNVSMode.Checked = false;
        }

        private void TransmitToMCU_Error_nofi(uint Debug0, uint Debug1)
        {
            tBoxOutData.AppendText($"Error: Debug0 = {Debug0}, Debug1 = {Debug1}\r\n");
        }

        private void TransmitToMCU(ushort Length, byte[] Data)
        {
		     serialPort1.Write(Data , 0 , Length);
        }

        private void Responce_Rxcbk(byte Length, byte[] Data)
        {
            for(int i = 0;i<Length;i++)
            {
                RxData[i] = Data[i];
            }
        }

        private void TxMsgUpdate(string Txdata)
        {
            char[] loadComifData = Txdata.ToCharArray();

            for(int i = 0;i<loadComifData.Length - 1;i++)
            {
                Trns_MCU_Data.Data[i] = ((byte)loadComifData[i]);
            }
         }
        private void loadDefaultValues()
        {
            CBoxComPort.Text = ConfigurationManager.AppSettings["COMPort"];
            CboxBaudRate.Text = ConfigurationManager.AppSettings["BaudRate"];
            CboxDataBits.Text = ConfigurationManager.AppSettings["DataBit"];
            CboxParityBit.Text = ConfigurationManager.AppSettings["ParityBit"];
            CboxStopBit.Text = ConfigurationManager.AppSettings["StopBit"];
            cBoxAppAddressSelect.Text = ConfigurationManager.AppSettings["FlhMryAds"];
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            //int ByteSize = serialPort1.BytesToRead;

            //byte[] data = new byte[ByteSize];

            //serialPort1.Read(data, 0, data.Length);

            string data = serialPort1.ReadExisting();

            Trns_MCU.RxIndication(data);
            //byte[] ReceivedMessage = new byte[ByteSize];  //create an array of the same size
            //Array.Copy(data, ReceivedMessage, data.Length);  //copy it across

            //for (int i = 0; i < data.Length; i++)
            //{
            //    Trns_MCU.RxIndication(data[i]);
            //}       
            //tBoxOutData.Text = RxMessageDataIN;
        }

        private void chkBoxNVSMode_CheckedChanged(object sender, EventArgs e)
        {
            if(chkBoxNVSMode.Checked)
            {
                chkBoxNVSMode.Checked = true;
                chkBoxFlashMode.Checked = false;
            }
        }

        private void chkBoxFlashMode_CheckedChanged(object sender, EventArgs e)
        {
            if(chkBoxFlashMode.Checked)
            {
                chkBoxFlashMode.Checked = true;
                chkBoxNVSMode.Checked = false;
            }
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

            //SaveConfigurationSettings(); //if you need add it, this is save the Every time configuration setting
                                           //and restore store saved value of the configuration box
           
        } // end port connected

        private void SaveConfigurationSettings()
        {
            var config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);

            config.AppSettings.Settings.Remove("COMPort");
            config.AppSettings.Settings.Remove("BaudRate");
            config.AppSettings.Settings.Remove("DataBit");
            config.AppSettings.Settings.Remove("ParityBit");
            config.AppSettings.Settings.Remove("StopBit");
            config.AppSettings.Settings.Remove("FlhMryAds");

            config.AppSettings.Settings.Add("COMPort", CBoxComPort.Text);
            config.AppSettings.Settings.Add("BaudRate", CboxBaudRate.Text);
            config.AppSettings.Settings.Add("DataBit", CboxDataBits.Text);
            config.AppSettings.Settings.Add("ParityBit", CboxParityBit.Text);
            config.AppSettings.Settings.Add("StopBit", CboxStopBit.Text);
            config.AppSettings.Settings.Add("FlhMryAds", cBoxAppAddressSelect.Text);

            config.Save(ConfigurationSaveMode.Modified);
            ConfigurationManager.RefreshSection("appSettings");

        }

        private void BtnTransmit_Click(object sender, EventArgs e)
        {
            bool Modestatus = true;
            string modeupdate = null;
            string flashErase = null;
            string flashStart = "F50000000000000000000000000000000000000000";  // this string used to start the flash operation
            string NvsMode    = "FA0000000000000000000000000000000000000000"; // nvs mode
            string FlashMode  = "FB0000000000000000000000000000000000000000"; // flash mode --> this mode is used to write the image file in bank1 or bank2

            if (cBoxAppAddressSelect.Text == "App1" || cBoxAppAddressSelect.Text =="App2")
            {
                if(chkBoxFlashMode.Checked == true || chkBoxNVSMode.Checked == true)
                {
                    modeupdate = flashStart;

                    while (true)
                    {
                        if (Modestatus)
                        {
                            TxMsgUpdate(modeupdate);  // check this changes
                            Trns_MCU.Transmit(Trns_MCU_Data);
                            //serialPort1.Write(modeupdate + " "); // changes
                            Modestatus = false;
                        }

                        if (RxData[0] == 0x00) // check this 
                        {
                            RxData[0] = 0xFF; //RxMessageDataIN = null;

                            if (modeupdate == flashStart)
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
                        else if (RxData[0] == 0x01)
                        {
                            RxData[0] = 0xFF; //RxMessageDataIN = null;
                            Modestatus = true;
                        }

                    } //"while" end of the flashstart , flash mode, erase mode 

                    if (Modestatus == true)
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

                                                                TxMsgUpdate(mryadd);  // check this changes
                                                                Trns_MCU.Transmit(Trns_MCU_Data);

                                                                CKsum += Hexval.SumOfLine(HexData);
                                                            }
                                                            change = false;
                                                        }

                                                        if (RxData[0] == 0x00)
                                                        {
                                                                RxData[0] = 0xFF; //RxMessageDataIN = null;
                                                                break;
                                                        }
                                                        else if (RxData[0] == 0x01)
                                                        {
                                                                RxData[0] = 0xFF; //RxMessageDataIN = null;
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

                                                    if (updateAppHeader())
                                                    {
                                                        Flh_CompleteStatus = true; // this bool is indicate the flash write operation is complete.
                                                    }
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
                                                    MessageBox.Show("Invaid Data Record ", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
                                } // else block end
                            } // while end
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
                                    if (chg_status == true)
                                    {
                                        TxMsgUpdate(Flashcompleted);  // check this changes
                                        Trns_MCU.Transmit(Trns_MCU_Data);
                                        chg_status = false;
                                    }

                                    if (RxData[0] == 0x00)
                                    {
                                        tBoxOutData.AppendText("\nFc Completed");
                                        RxData[0] = 0xFF; //RxMessageDataIN = null;
                                        break;
                                    }
                                    else if (RxData[0] == 0x01)
                                    {
                                        RxData[0] = 0xFF; //RxMessageDataIN = null;
                                        chg_status = true;
                                    }
                                } // while end
                                Flh_CompleteStatus = false;
                            }// end 
                        }
                        else
                        {
                            MessageBox.Show("Please Select the valid file Format", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                    }
                    else { MessageBox.Show("Please Select Mode ", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
                }
                else { MessageBox.Show("Please Select Mode ", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }
            else { MessageBox.Show("Please Select Flash Memory Address to flash ", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }// btn transmit end

        private bool updateAppHeader()
        {
            string Header =null, SAdd = null, EAdd = null, flag = null;
            bool retval = false,headerflg = false,headerStatus=false;
            string headerUpdate = null;

            CKsum = ((~CKsum) + 1);

            if (cBoxAppAddressSelect.Text == "App1")
            {
                Header = "A1A1A1A1";
                SAdd = "08006000";
                EAdd = "0800FFFC";
                flag = "00000000";
                headerflg = true;
                headerUpdate = "FD" + SAdd + Header + SAdd + EAdd + flag;

            }
            else if (cBoxAppAddressSelect.Text == "App2")
            {
                Header = "A2A2A2A2";
                SAdd = "08016000";
                EAdd = "0801FFFC";
                flag = "00000000";
                headerflg = true;
                headerUpdate = "FD" + SAdd + Header + SAdd + EAdd + flag;
            }

            while (true)
            {
                if(headerflg == true)
                {
                    TxMsgUpdate(headerUpdate);  // check this changes
                    Trns_MCU.Transmit(Trns_MCU_Data);
                    headerflg = false;
                }

                if (RxData[0] == 0x00)
                {
                    if(headerStatus == true)
                    { headerStatus = false;retval = true; break; }
                    
                    if(headerStatus == false)
                    {
                        string ck = Convert.ToString(CKsum,16);
                        SAdd = Convert.ToString(Convert.ToInt32(SAdd) + 10U);
                        headerUpdate = "FD" + SAdd + ck + "000000000000000000000000";
                        RxData[0] = 0xFF; //RxMessageDataIN = null;
                        headerflg = true;
                        headerStatus = true;
                    }
                }
                else if (RxData[0] == 0x01)
                {
                    RxData[0] = 0xFF; //RxMessageDataIN = null;
                    headerflg = true;
                }
                           
            }// while end
            return retval;
        }// updateAppHeader


    }// end class

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

    public uint SumOfLine(string hex)
    {
        uint[] hexval = new uint[hex.Length / 2];

        // Convert hexadecimal string to byte array
        byte[] byteArray = new byte[hex.Length / 2];

        for (int i = 0; i < byteArray.Length; i++)
        {
            byteArray[i] = Convert.ToByte(hex.Substring(i * 2, 2), 16);
        }

        if ((byteArray.Length / 4) == 1)
        {
            hexval[0] = (uint)(byteArray[3] << 24 | byteArray[2] << 16 | byteArray[1] << 8 | byteArray[0]);
        }
        else if ((byteArray.Length / 4) == 2)
        {
            hexval[0] = (uint)(byteArray[3] << 24 | byteArray[2] << 16 | byteArray[1] << 8 | byteArray[0]);
            hexval[1] = (uint)(byteArray[7] << 24 | byteArray[6] << 16 | byteArray[5] << 8 | byteArray[4]);
        }
        else if ((byteArray.Length / 4) == 3)
        {
            hexval[0] = (uint)(byteArray[3] << 24 | byteArray[2] << 16 | byteArray[1] << 8 | byteArray[0]);
            hexval[1] = (uint)(byteArray[7] << 24 | byteArray[6] << 16 | byteArray[5] << 8 | byteArray[4]);
            hexval[2] = (uint)(byteArray[11] << 24 | byteArray[10] << 16 | byteArray[9] << 8 | byteArray[8]);
        }
        else if ((byteArray.Length / 4) == 4)
        {
            hexval[0] = (uint)(byteArray[3] << 24 | byteArray[2] << 16 | byteArray[1] << 8 | byteArray[0]);
            hexval[1] = (uint)(byteArray[7] << 24 | byteArray[6] << 16 | byteArray[5] << 8 | byteArray[4]);
            hexval[2] = (uint)(byteArray[11] << 24 | byteArray[10] << 16 | byteArray[9] << 8 | byteArray[8]);
            hexval[3] = (uint)(byteArray[15] << 24 | byteArray[14] << 16 | byteArray[13] << 8 | byteArray[12]);
        }


        uint sum = hexval[0] + hexval[1] + hexval[2] + hexval[3];

        return sum;
    }
}