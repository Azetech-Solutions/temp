using System;
using System.Configuration;
using System.IO.Ports;
using System.Windows.Forms;
using System.Xml;
using static File_TryAccess_Tool.Log;


namespace File_TryAccess_Tool
{
    public enum XmlFlashtype
    {
        Unkown = 0,
        BootManager = 1,
        BootLoader = 2,
        App1 = 3,
        App2 = 4,
        NVS = 5,
        NVM = 6,
    }
    public partial class Form1 : Form
    {
        //obj creation
        public XmlDocument gettingxmldoc = new XmlDocument();
        public XmlNodeList settingType;
        public XmlNodeList settingSector;
        public XmlNodeList settingSectorLength;
        public XmlNodeList settingBank;
        public XmlNodeList settingStartAddress;
        public XmlNodeList settingEndAddress;
        public XmlNodeList settingDataBlock;
        public XmlNodeList settingVerinfo;
        public XmlNodeList settingComport;
        public XmlNodeList settingComiflist;

        //obj creation
        public memoryErasecontrol erasetype;
        public Tooltransmit tooltransmit;
        public Hexfilehandling hexfilehandling;

        // flag creations
        bool IsFileVaild = false;
      
        public Form1()
        {
            InitializeComponent();
            logRegister(tboxDataOut);
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
        private void Form1_Load(object sender, EventArgs e)
        {
            string[] Ports = SerialPort.GetPortNames();
            CBoxComPort.Items.AddRange(Ports);

            gettingxmldoc.Load(@"D:\Mohan\Class\Bootlodaer\STM32H5_Controller\Boot_Git\28-05-24\temp\hexFile_TryAccess_Tool\File_TryAccess_Tool\XMLFile1.xml");

            settingType = gettingxmldoc.GetElementsByTagName("type");
            settingSector = gettingxmldoc.GetElementsByTagName("sector");
            settingSectorLength = gettingxmldoc.GetElementsByTagName("sectorLength");
            settingBank = gettingxmldoc.GetElementsByTagName("bank");
            settingStartAddress = gettingxmldoc.GetElementsByTagName("startAddress");
            settingEndAddress = gettingxmldoc.GetElementsByTagName("endAddress");
            settingDataBlock = gettingxmldoc.GetElementsByTagName("DataBlock");
            settingVerinfo = gettingxmldoc.GetElementsByTagName("versioninfo");
            settingComport = gettingxmldoc.GetElementsByTagName("comport");
            settingComiflist = gettingxmldoc.GetElementsByTagName("comif");

            loadDefaultValues();

            tooltransmit = new Tooltransmit(serialPort1);
            erasetype = new memoryErasecontrol(tooltransmit);
            hexfilehandling = new Hexfilehandling(tooltransmit);
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            //int ByteSize = serialPort1.BytesToRead;

            //byte[] data = new byte[ByteSize];

            //serialPort1.Read(data, 0, data.Length);

                string data = serialPort1.ReadExisting();

                tooltransmit.mcuTransmit.RxIndication(data);


            //for (int i = 0; i < data.Length; i++)
            //{
            //    tooltransmit.mcuTransmit.RxIndication(data[i]);
            //}       
            //tBoxOutData.Text = RxMessageDataIN;
        } // serial data rx part end

        private void bootmanagerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string command = null, sec = null, bank = null, toMCU = null;
            try
            {
                if (serialPort1.IsOpen)
                {
                    if (Convert.ToInt16(settingType[0].InnerText) == (UInt16)XmlFlashtype.BootManager)
                    {
                        command = "FE";
                        sec = settingSector[0].InnerText;  // copy sector value from xml file
                        bank = settingBank[0].InnerText;  // copy bank value from xml file
                        toMCU = command + sec + bank + "000000000000000000000000000000000000";
                        erasetype.eraseFlag = true;
                    }
                    if (erasetype.eraseFlag == true) { erasetype.Memoryerasecommand(toMCU); }
                }
                else { MessageBox.Show("Please Connect Serial port", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }

        private void bootloaderToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string command = null, sec = null, bank = null, toMCU = null;
            
                try
                {
                    if (serialPort1.IsOpen)
                    {
                        if (Convert.ToInt16(settingType[1].InnerText) == (UInt16)XmlFlashtype.BootLoader)
                        {
                            command = "FE";
                            sec = settingSector[1].InnerText;  // copy sector value from xml file
                            bank = settingBank[1].InnerText;  // copy bank value from xml file
                            toMCU = command + sec + bank + "000000000000000000000000000000000000";
                            erasetype.eraseFlag = true;
                        }
                    if (erasetype.eraseFlag == true) { erasetype.Memoryerasecommand(toMCU); }
                }
                    else { MessageBox.Show("Please Connect Serial port", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
                }
                catch (Exception ex) { MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }
        private void application1MemoryToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string command = null, sec =null, bank = null, toMCU = null;
            try 
            { 
                if (serialPort1.IsOpen)
                {
                    if (Convert.ToInt16(settingType[2].InnerText) == (UInt16)XmlFlashtype.App1)
                    {
                        command = "FE";
                        sec = settingSector[2].InnerText;  // copy sector value from xml file
                        bank = settingBank[2].InnerText;  // copy bank value from xml file
                        toMCU = command + sec + bank + "000000000000000000000000000000000000";
                        erasetype.eraseFlag = true;
                    }
                    if (erasetype.eraseFlag == true) { erasetype.Memoryerasecommand(toMCU); }
                }
                else { MessageBox.Show("Please Connect Serial port", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }
            catch(Exception ex) { MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }

        }

        private void application2MemoryToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string command = null, sec = null, bank = null, toMCU = null;
            try
            {
                if (serialPort1.IsOpen)
                {
                    if (Convert.ToInt16(settingType[3].InnerText) == (UInt16)XmlFlashtype.App2)
                    {
                        command = "FE";
                        sec = settingSector[3].InnerText;  // copy sector value from xml file
                        bank = settingBank[3].InnerText;  // copy bank value from xml file
                        toMCU = command + sec + bank + "000000000000000000000000000000000000";
                        erasetype.eraseFlag = true;
                    }
                    if (erasetype.eraseFlag == true) { erasetype.Memoryerasecommand(toMCU); }
                }
                else { MessageBox.Show("Please Connect Serial port", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }

        }

        private void nVSSettingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            NVS_Form nvs = new NVS_Form(tooltransmit);
            nvs.ShowDialog();
        } // nvs end

        private void nVMSettingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            NVM_Form nvm = new NVM_Form(tooltransmit);
            nvm.ShowDialog();
        } // nvm end

        private void MStripExitApplication_Click(object sender, EventArgs e)
        {
            var ext = MessageBox.Show("Do you want to \"Exit\"","Exit",MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (ext == DialogResult.Yes) { Application.Exit(); }            
        } // application exit end

        private void BtnSearch_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                tBoxView.Text = "";
                try
                {
                    using (OpenFileDialog ofd = new OpenFileDialog())
                    {
                        ofd.Filter = "Hex files (*.Hex)|*.Hex|All files (*.*)|*.*";
                        if (ofd.ShowDialog() == DialogResult.OK)
                        {
                            if(hexfilehandling.Hexfileverity(ofd))
                            {
                                IsFileVaild = true;
                                tBoxView.Text = ofd.FileName;
                                Log.Info(ofd.FileName);
                            }
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
            {   var DS = MessageBox.Show("Do you want to Disconnect COM Port", "Alert", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (DS == DialogResult.Yes)
                { serialPort1.Close(); progressBar1.Value = 0; }        
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
            catch (Exception err) { MessageBox.Show(err.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }           
        } // end port connected

        private void BtnTransmit_Click(object sender, EventArgs e)
        {
            bool Modestatus = false;
          
            if(IsFileVaild == true)
            {
                if (cBoxAppAddressSelect.Text == "App1" || cBoxAppAddressSelect.Text == "App2")
                {
                    if (cBoxAppAddressSelect.Text == "App1")
                    {
                        if (hexfilehandling.Flashstartcommands("08006000"))  // to change the xml app1 start address
                        {
                            Modestatus = true;
                        }
                    }
                    else
                    {
                        if (hexfilehandling.Flashstartcommands("08016000"))   // to change the xml app2 start address
                        {
                            Modestatus = true;
                        }
                    }


                    if (Modestatus == true)
                    {
                        bool Flh_CompleteStatus = false;

                        if (hexfilehandling.FlashDatatransmit())
                        {
                            Flh_CompleteStatus = true;
                        }

                        if (Flh_CompleteStatus == true)
                        {
                            if (cBoxAppAddressSelect.Text == "App1")
                            {
                                if (hexfilehandling.flashcompletecommand("08006000"))
                                {                                    
                                    hexfilehandling.UpdateflashappHeader("08006000");
                                }
                            }
                            else
                            {
                                if (hexfilehandling.flashcompletecommand("08016000"))
                                {
                                    hexfilehandling.UpdateflashappHeader("08016000");
                                }
                            }
                        }// end 
                    }

                }
                else { MessageBox.Show("Please Select Flash Memory Address to flash ", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }
            else { MessageBox.Show("Please select the Correct \"Hex file\"", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }

        }// btn transmit end

    }// end form1 class

}