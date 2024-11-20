using System;
using System.Configuration;
using System.IO.Ports;
using System.Windows.Forms;
using System.Xml;
using static File_TryAccess_Tool.Log;
using static File_TryAccess_Tool.Xmlfilehandling;
using static File_TryAccess_Tool.Tooltransmit;
using System.Linq;
using System.IO;
using System.Collections.Generic;
using System.Threading;
using File_TryAccess_Tool.Forms;
using File_TryAccess_Tool.Class;


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
    public partial class MainForm : Form
    {
        //obj creation
        public XmlDocument xmldoc = new XmlDocument();
        public memoryErasecontrol erasetype;
        public Hexfilehandling hexfilehandling;
        private Thread flashThread;
        private bool application_1_choose = false;
        private bool application_2_choose = false;

        private preloadHandling waitprocess;

        // flag creations
        bool IsFileVaild = false;
      
        public MainForm()
        {
            InitializeComponent();

            //xml register
            xmldoc.Load(Directory.GetCurrentDirectory() + @"\Toolsetting.xml"); //(@"D:\Mohan\Class\Bootlodaer\STM32H5\Boot_Git\03-06-24\temp\hexFile_TryAccess_Tool\File_TryAccess_Tool\Toolsetting.xml");
            XMLRegister(xmldoc);

            // channel register
            TooltransmitRegister(serialPort1);

            // log register
            logRegister(rtbxDataOut);
        } // end
        private void loadDefaultValues()
        {
            CBoxComPort.Text = ConfigurationManager.AppSettings["COMPort"];
            //tbxBaudRate.Text = setComport[0].ChildNodes[0].InnerText;
            //tbxDataBit.Text = setComport[0].ChildNodes[1].InnerText;
            //tbxStopBit.Text = setComport[0].ChildNodes[2].InnerText;
            //tbxParityBit.Text = setComport[0].ChildNodes[3].InnerText;            
        } // default value end
        private void Form1_Load(object sender, EventArgs e)
        {
            string[] Ports = SerialPort.GetPortNames();
            CBoxComPort.Items.AddRange(Ports);
            loadDefaultValues();

            erasetype = new memoryErasecontrol();
            hexfilehandling = new Hexfilehandling();
        } // end

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            string[] Ports = SerialPort.GetPortNames();
            CBoxComPort.Items.Clear();
            loadDefaultValues();
            CBoxComPort.Items.AddRange(Ports);
        }
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            ushort len = (ushort) serialPort1.BytesToRead;
            byte[] data = new byte[len];

            serialPort1.Read(data, 0, data.Length);

            for (ushort i = 0; i < data.Length; i++)
            {
                MCUTransmitFunction.RxIndication(data[i]);
            }

            //string data = serialPort1.ReadExisting();
            //MCUTransmitFunction.RxIndication(data);
        } // serial data rx part end

        #region Memory Erase region
        private void bootmanagerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            byte[] erase = new byte[3];
            try
            {
                if (serialPort1.IsOpen)
                {
                    Log.Info("Bootmanager Memory Erase start");
                    if (Convert.ToInt16(setType[0].InnerText) == (UInt16)XmlFlashtype.BootManager)
                    {
                        erase[0] = Commands.Flasherase;
                        erase[1] = (byte)Convert.ToInt16(setSector[0].InnerText);
                        erase[2] = (byte)(Convert.ToInt16(setBank[0].InnerText));
                        erasetype.eraseFlag = true;
                    }
                    
                    if (erasetype.eraseFlag == true) 
                    {
                        flashThread = new Thread(() => {
                            if (erasetype.Memoryerasecommand(erase.ToArray())) { Log.Message("Bootmanager Memory Erase Complete");}
                        });

                        flashThread.Start();
                    }
                }
                else { MessageBox.Show("Please Connect Serial port", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }  // bootmanager Erase block end

        private void bootloaderToolStripMenuItem_Click(object sender, EventArgs e)
        {
            byte[] erase = new byte[3];

            try
            {
                if (serialPort1.IsOpen)
                {
                    Log.Info("Bootloader Memory Erase start");
                    if (Convert.ToInt16(setType[1].InnerText) == (UInt16)XmlFlashtype.BootLoader)
                    {
                        erase[0] = Commands.Flasherase;
                        erase[1] = (byte)Convert.ToInt16(setSector[1].InnerText);
                        erase[2] = (byte)(Convert.ToInt16(setBank[1].InnerText));
                        erasetype.eraseFlag = true;
                    }
                    if (erasetype.eraseFlag == true) 
                    {
                        flashThread = new Thread(() => {
                            if (erasetype.Memoryerasecommand(erase.ToArray())) { Log.Message("Bootloader Memory Erase complete"); }
                        });

                        flashThread.Start();
                    }
                }
                else { MessageBox.Show("Please Connect Serial port", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }   // bootloader Erase block end
        private void application1MemoryToolStripMenuItem_Click(object sender, EventArgs e)
        {
            byte[] erase = new byte[3];
            try 
            { 
                if (serialPort1.IsOpen)
                {
                    Log.Info("Application 1 Memory Erase start");
                    if (Convert.ToInt16(setType[2].InnerText) == (UInt16)XmlFlashtype.App1)
                    {
                        erase[0] = Commands.Flasherase;
                        erase[1] = (byte)Convert.ToInt16(setSector[2].InnerText);
                        erase[2] = (byte)(Convert.ToInt16(setBank[2].InnerText));
                        erasetype.eraseFlag = true;
                    }
                    if (erasetype.eraseFlag == true) 
                    {
                        flashThread = new Thread(() => {

                            if (erasetype.Memoryerasecommand(erase.ToArray()))
                            {
                                Log.Message("Application 1 Memory Erase complete");
                            }
                        });

                        flashThread.Start();
                    }
                }
                else { MessageBox.Show("Please Connect Serial port", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }
            catch(Exception ex) { MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }

        }   // App1 Erase block end

        private void application2MemoryToolStripMenuItem_Click(object sender, EventArgs e)
        {
            byte[] erase = new byte[3];
            try
            {
                if (serialPort1.IsOpen)
                {
                    Log.Info("Application 2 Memory Erase start");
                    if (Convert.ToInt16(setType[3].InnerText) == (UInt16)XmlFlashtype.App2)
                    {
                        erase[0] = Commands.Flasherase;
                        erase[1] = (byte)Convert.ToInt16(setSector[3].InnerText);
                        erase[2] = (byte)(Convert.ToInt16(setBank[3].InnerText));
                        erasetype.eraseFlag = true;
                    }
                    if (erasetype.eraseFlag == true) 
                    {
                        flashThread = new Thread(() => {
                            if (erasetype.Memoryerasecommand(erase.ToArray())){ Log.Message("Application 2 Memory Erase complete"); }
                        });

                        flashThread.Start();
                    }
                }
                else { MessageBox.Show("Please Connect Serial port", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }

        }  // App2 Erase block end

        private void nVSMemoryToolStripMenuItem_Click(object sender, EventArgs e)
        {
            byte[] erase = new byte[3];
            try
            {
                if (serialPort1.IsOpen)
                {
                    Log.Info("NVS block Memory Erase start");
                    if (Convert.ToInt16(setType[4].InnerText) == (UInt16)XmlFlashtype.NVS)
                    {
                        erase[0] = Commands.Flasherase;
                        erase[1] = (byte)Convert.ToInt16(setSector[4].InnerText);
                        erase[2] = (byte)(Convert.ToInt16(setBank[4].InnerText));
                        erasetype.eraseFlag = true;
                    }
                    if (erasetype.eraseFlag == true) 
                    {
                        flashThread = new Thread(() => {
                            if (erasetype.Memoryerasecommand(erase.ToArray())) { Log.Message("NVS block Memory Erase complete"); }
                        });

                        flashThread.Start();
                    }
                }
                else { MessageBox.Show("Please Connect Serial port", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }  // nvs Erase block end

        private void nVMMemoryToolStripMenuItem_Click(object sender, EventArgs e)
        {
            byte[] erase = new byte[3];
            try
            {
                if (serialPort1.IsOpen)
                {
                    Log.Info("NVM block Memory Erase start");
                    if (Convert.ToInt16(setType[5].InnerText) == (UInt16)XmlFlashtype.NVM)
                    {
                        erase[0] = Commands.Flasherase;
                        erase[1] = (byte)Convert.ToInt16(setSector[5].InnerText);
                        erase[2] = (byte)(Convert.ToInt16(setBank[5].InnerText));
                        erasetype.eraseFlag = true;
                    }
                    if (erasetype.eraseFlag == true) 
                    {
                        flashThread = new Thread(() => {
                            if (erasetype.Memoryerasecommand(erase.ToArray())) { Log.Message("NVM block Memory Erase complete"); }
                        });

                        flashThread.Start();
                    }
                }
                else { MessageBox.Show("Please Connect Serial port", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }  // nvm Erase block end
        #endregion

        private void nVSSettingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            NVS_Form nvs = new NVS_Form();
            nvs.ShowDialog();
        } // nvs form end

        private void nVMSettingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            NVM_Form nvm = new NVM_Form();
            nvm.ShowDialog();
        } // nvm form end

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
                            if(hexfilehandling.Hexfileverify(ofd))
                            {
                                IsFileVaild = true;
                                tBoxView.Text = ofd.FileName;
                                Log.Info("Filepath :"+ofd.FileName);                                                              
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
                serialPort1.BaudRate = Convert.ToInt32(setComport[0].ChildNodes[0].InnerText); //Convert.ToInt32(tbxBaudRate.Text);
                serialPort1.DataBits = Convert.ToInt32(setComport[0].ChildNodes[1].InnerText);  //Convert.ToInt32(tbxDataBit.Text);
                serialPort1.StopBits = (StopBits)Enum.Parse(typeof(StopBits), setComport[0].ChildNodes[2].InnerText);   //(StopBits)Enum.Parse(typeof(StopBits), tbxStopBit.Text);
                serialPort1.Parity = (Parity)Enum.Parse(typeof(Parity), setComport[0].ChildNodes[3].InnerText);  // (Parity)Enum.Parse(typeof(Parity), tbxParityBit.Text);

                serialPort1.Open();
                progressBar1.Value = 100;
            }
            catch (Exception err) { MessageBox.Show(err.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }           
        } // end port connected

        private void btnClearLog_Click(object sender, EventArgs e)
        {
            var close = MessageBox.Show("Do you want to Erase the Log", "Alert", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (close == DialogResult.Yes)
            {
                if (rtbxDataOut.Text != "") { rtbxDataOut.Clear(); }
            }
        }   // clear log end

        private void BtnTransmit_Click(object sender, EventArgs e)
        {
            waitprocess = new preloadHandling();

            flashThread = new Thread( () =>
            {                
                bool Modestatus = false;

                if (IsFileVaild == true)
                {
                    if (application_1_choose == true || application_2_choose == true )
                    {
                        if (application_1_choose == true)
                        {
                            waitprocess.showWaitState(this);
                            
                            if (hexfilehandling.Flashstartcommands(Convert.ToUInt32(setStartAddress[2].InnerText)))  // based on xml app1 start address
                            {                                
                                Modestatus = true;
                            }
                        }
                        else
                        {
                            if (hexfilehandling.Flashstartcommands(Convert.ToUInt32(setStartAddress[3].InnerText)))   // based on xml app2 start address
                            {
                                Modestatus = true;
                            }
                        }


                        if (Modestatus == true)
                        {
                            bool Flh_CompleteStatus = false;

                            Log.Message("Flash transmit start");
                            if (hexfilehandling.FlashDatatransmit())
                            {
                                //Log.Message("Flash transmit start end");
                                Flh_CompleteStatus = true; // to confirm all data's are transmit to uC
                            }

                            if (Flh_CompleteStatus == true)
                            {
                                if (application_1_choose == true)
                                {
                                    //Log.Message("Flash update start");
                                    if (hexfilehandling.UpdateflashappHeader(Convert.ToUInt32(setStartAddress[2].InnerText)))   // based on xml app1 start address
                                    {
                                        //Log.Message("Flash update start end");
                                        //Log.Message("Flash Complete start");
                                        hexfilehandling.flashcompletecommand(Convert.ToUInt32(setStartAddress[2].InnerText));   // based on xml app1 start address
                                        Log.Message("Flash Complete");

                                        application_1_choose = false;
                                        application_2_choose = false;
                                    }
                                }
                                else
                                {
                                    //Log.Message("Flash update start");
                                    if (hexfilehandling.UpdateflashappHeader(Convert.ToUInt32(setStartAddress[3].InnerText)))   // based on xml app2 start address
                                    {
                                        //Log.Message("Flash update start end");
                                        //Log.Message("Flash Complete start");                                        
                                        hexfilehandling.flashcompletecommand(Convert.ToUInt32(setStartAddress[3].InnerText));    // based on xml app2 start address
                                        Log.Message("Flash Complete");

                                        application_1_choose = false;
                                        application_2_choose = false;
                                    }
                                }
                            waitprocess.closeWaitState();
                            }// end 
                        }

                    }
                    else { MessageBox.Show("Please Select Flash Memory Address to flash ", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
                }
                else { MessageBox.Show("Please select the Correct \"Hex file\"", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            });

            flashThread.Start();           

        }// btn transmit end

        #region "Application Version"
        private void btnVerApp1_Click(object sender, EventArgs e)
        {
            
            flashThread = new Thread(() =>
            {
                List<byte> ver1 = new List<byte>();
                uint add = Convert.ToUInt32(setStartAddress[2].InnerText); // application 1 header address
                
                lblMajorVer.Text = "-";
                lblMinorVer.Text = "-";
                lblBulidVer.Text = "-";
                lblReleseVer.Text = "-";

                ver1.Add(Commands.GETAPPVERSIONCMD);
                ver1.Add(0x00);
                ver1.Add(0x00);
                ver1.Add((byte)(add >> 24));
                ver1.Add((byte)(add >> 16));
                ver1.Add((byte)(add >> 8));
                ver1.Add((byte)(add));


                byte[] verval = hexfilehandling.GetAppVersion(ver1.ToArray());

                byte len = (byte)(verval.Length - 3);

                lblMajorVer.Text = ((verval[3] << 24) | (verval[4] << 16) | (verval[5] << 8) | (verval[6])).ToString("X2");
                lblMajorVer.Refresh();
               
                lblMinorVer.Text = ((verval[7] << 24) | (verval[8] << 16) | (verval[9] << 8) | (verval[10])).ToString("X2");
                lblMinorVer.Refresh();
                
                lblBulidVer.Text = ((verval[11] << 24) | (verval[12] << 16) | (verval[13] << 8) | (verval[14])).ToString("X2");
                lblBulidVer.Refresh();
                
                lblReleseVer.Text = ((verval[15] << 24) | (verval[16] << 16) | (verval[17] << 8) | (verval[18])).ToString("X2");
                lblReleseVer.Refresh();
            });
            flashThread.Start();

        }

        private void btnVerApp2_Click(object sender, EventArgs e)
        {
            flashThread = new Thread(() =>
            {
                List<byte> ver1 = new List<byte>();
                uint add = Convert.ToUInt32(setStartAddress[3].InnerText); // application 2 header address

                lblMajorVer.Text = "-";
                lblMinorVer.Text = "-";
                lblBulidVer.Text = "-";
                lblReleseVer.Text = "-";

                ver1.Add(Commands.GETAPPVERSIONCMD);
                ver1.Add(0x00);
                ver1.Add(0x00);
                ver1.Add((byte)(add >> 24));
                ver1.Add((byte)(add >> 16));
                ver1.Add((byte)(add >> 8));
                ver1.Add((byte)(add));

                byte[] verval = hexfilehandling.GetAppVersion(ver1.ToArray());

                byte len = (byte)(verval.Length - 3);

                lblMajorVer.Text = ((verval[3] << 24) | (verval[4] << 16) | (verval[5] << 8) | (verval[6])).ToString("X2");
                lblMajorVer.Refresh();

                lblMinorVer.Text = ((verval[7] << 24) | (verval[8] << 16) | (verval[9] << 8) | (verval[10])).ToString("X2") ;
                lblMinorVer.Refresh();

                lblBulidVer.Text = ((verval[11] << 24) | (verval[12] << 16) | (verval[13] << 8) | (verval[14])).ToString("X2");
                lblBulidVer.Refresh();

                lblReleseVer.Text = ((verval[15] << 24) | (verval[16] << 16) | (verval[17] << 8) | (verval[18])).ToString("X2");
                lblReleseVer.Refresh();

            });
            flashThread.Start();
        }
        #endregion


        private void cBoxAppAddressSelect_SelectedValueChanged(object sender, EventArgs e)
        {
            if (cBoxAppAddressSelect.Text == "App1")
            {
                application_1_choose = true;
                application_2_choose = false;
            }
            else if (cBoxAppAddressSelect.Text == "App2")
            {
                application_1_choose = false;
                application_2_choose = true;
            }
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            var close = MessageBox.Show("Do you want Close Application", "Alret", MessageBoxButtons.YesNo,
                                          MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2);

            if (close == DialogResult.Yes)
            {
                if (flashThread != null && flashThread.IsAlive)
                {
                    flashThread.Abort(); // Caution: Thread.Abort is not recommended due to abrupt termination
                    Log.Message("Flash operation stopped.");
                }

                Application.Exit();
            }
            else
            {
                e.Cancel = true;
            }
        }
    }// end form1 class

}