namespace File_TryAccess_Tool
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.tBoxView = new System.Windows.Forms.TextBox();
            this.BtnSearch = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.cBoxAppAddressSelect = new System.Windows.Forms.ComboBox();
            this.LMryAddress = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.tbxParityBit = new System.Windows.Forms.TextBox();
            this.tbxStopBit = new System.Windows.Forms.TextBox();
            this.tbxDataBit = new System.Windows.Forms.TextBox();
            this.tbxBaudRate = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.CBoxComPort = new System.Windows.Forms.ComboBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MStripExitApplication = new System.Windows.Forms.ToolStripMenuItem();
            this.comportToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MStripPortConnect = new System.Windows.Forms.ToolStripMenuItem();
            this.MStripPortDisconnect = new System.Windows.Forms.ToolStripMenuItem();
            this.eraseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.bootmanagerToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.bootloaderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.application1MemoryToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.application2MemoryToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nVSMemoryToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nVMMemoryToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.settingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nVSSettingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nVMSettingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.BtnTransmit = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btnClearLog = new System.Windows.Forms.Button();
            this.rtbxDataOut = new System.Windows.Forms.RichTextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // tBoxView
            // 
            this.tBoxView.Font = new System.Drawing.Font("Microsoft Tai Le", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tBoxView.Location = new System.Drawing.Point(8, 29);
            this.tBoxView.Margin = new System.Windows.Forms.Padding(2);
            this.tBoxView.Multiline = true;
            this.tBoxView.Name = "tBoxView";
            this.tBoxView.Size = new System.Drawing.Size(557, 22);
            this.tBoxView.TabIndex = 0;
            this.tBoxView.WordWrap = false;
            // 
            // BtnSearch
            // 
            this.BtnSearch.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.BtnSearch.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.BtnSearch.Cursor = System.Windows.Forms.Cursors.Hand;
            this.BtnSearch.Font = new System.Drawing.Font("Microsoft Tai Le", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BtnSearch.Location = new System.Drawing.Point(580, 29);
            this.BtnSearch.Margin = new System.Windows.Forms.Padding(2);
            this.BtnSearch.Name = "BtnSearch";
            this.BtnSearch.Size = new System.Drawing.Size(61, 21);
            this.BtnSearch.TabIndex = 1;
            this.BtnSearch.Text = "File Path";
            this.BtnSearch.UseVisualStyleBackColor = false;
            this.BtnSearch.Click += new System.EventHandler(this.BtnSearch_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // cBoxAppAddressSelect
            // 
            this.cBoxAppAddressSelect.Cursor = System.Windows.Forms.Cursors.Default;
            this.cBoxAppAddressSelect.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cBoxAppAddressSelect.Font = new System.Drawing.Font("Microsoft Tai Le", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cBoxAppAddressSelect.FormattingEnabled = true;
            this.cBoxAppAddressSelect.Items.AddRange(new object[] {
            "App1",
            "App2"});
            this.cBoxAppAddressSelect.Location = new System.Drawing.Point(567, 236);
            this.cBoxAppAddressSelect.Margin = new System.Windows.Forms.Padding(2);
            this.cBoxAppAddressSelect.Name = "cBoxAppAddressSelect";
            this.cBoxAppAddressSelect.Size = new System.Drawing.Size(86, 22);
            this.cBoxAppAddressSelect.TabIndex = 5;
            // 
            // LMryAddress
            // 
            this.LMryAddress.AutoSize = true;
            this.LMryAddress.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LMryAddress.Location = new System.Drawing.Point(566, 202);
            this.LMryAddress.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.LMryAddress.Name = "LMryAddress";
            this.LMryAddress.Size = new System.Drawing.Size(87, 32);
            this.LMryAddress.TabIndex = 6;
            this.LMryAddress.Text = "Flash Memory \r\n     Address";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.tbxParityBit);
            this.groupBox1.Controls.Add(this.tbxStopBit);
            this.groupBox1.Controls.Add(this.tbxDataBit);
            this.groupBox1.Controls.Add(this.tbxBaudRate);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.progressBar1);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.CBoxComPort);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(5, 8);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox1.Size = new System.Drawing.Size(211, 422);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            // 
            // tbxParityBit
            // 
            this.tbxParityBit.Location = new System.Drawing.Point(101, 192);
            this.tbxParityBit.Margin = new System.Windows.Forms.Padding(2);
            this.tbxParityBit.Name = "tbxParityBit";
            this.tbxParityBit.Size = new System.Drawing.Size(82, 23);
            this.tbxParityBit.TabIndex = 14;
            // 
            // tbxStopBit
            // 
            this.tbxStopBit.Location = new System.Drawing.Point(101, 161);
            this.tbxStopBit.Margin = new System.Windows.Forms.Padding(2);
            this.tbxStopBit.Name = "tbxStopBit";
            this.tbxStopBit.Size = new System.Drawing.Size(82, 23);
            this.tbxStopBit.TabIndex = 13;
            // 
            // tbxDataBit
            // 
            this.tbxDataBit.Location = new System.Drawing.Point(101, 127);
            this.tbxDataBit.Margin = new System.Windows.Forms.Padding(2);
            this.tbxDataBit.Name = "tbxDataBit";
            this.tbxDataBit.Size = new System.Drawing.Size(82, 23);
            this.tbxDataBit.TabIndex = 12;
            // 
            // tbxBaudRate
            // 
            this.tbxBaudRate.Location = new System.Drawing.Point(101, 93);
            this.tbxBaudRate.Margin = new System.Windows.Forms.Padding(2);
            this.tbxBaudRate.Name = "tbxBaudRate";
            this.tbxBaudRate.Size = new System.Drawing.Size(82, 23);
            this.tbxBaudRate.TabIndex = 11;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Imprint MT Shadow", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(36, 27);
            this.label6.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(135, 14);
            this.label6.TabIndex = 10;
            this.label6.Text = "COM PORT Control";
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(11, 239);
            this.progressBar1.Margin = new System.Windows.Forms.Padding(2);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(186, 8);
            this.progressBar1.TabIndex = 2;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(19, 194);
            this.label5.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(64, 16);
            this.label5.TabIndex = 9;
            this.label5.Text = "Parity Bit :";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(19, 161);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(58, 16);
            this.label4.TabIndex = 8;
            this.label4.Text = "Stop Bit :";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(19, 128);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(63, 16);
            this.label3.TabIndex = 7;
            this.label3.Text = "Data Bits :";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(17, 93);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(70, 16);
            this.label2.TabIndex = 6;
            this.label2.Text = "Baud Rate :";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(17, 62);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(74, 16);
            this.label1.TabIndex = 5;
            this.label1.Text = "COM PORT :";
            // 
            // CBoxComPort
            // 
            this.CBoxComPort.FormattingEnabled = true;
            this.CBoxComPort.Location = new System.Drawing.Point(101, 60);
            this.CBoxComPort.Margin = new System.Windows.Forms.Padding(2);
            this.CBoxComPort.Name = "CBoxComPort";
            this.CBoxComPort.Size = new System.Drawing.Size(82, 24);
            this.CBoxComPort.TabIndex = 0;
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.comportToolStripMenuItem,
            this.eraseToolStripMenuItem,
            this.settingsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(4, 1, 0, 1);
            this.menuStrip1.Size = new System.Drawing.Size(904, 24);
            this.menuStrip1.TabIndex = 8;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MStripExitApplication});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 22);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // MStripExitApplication
            // 
            this.MStripExitApplication.Name = "MStripExitApplication";
            this.MStripExitApplication.Size = new System.Drawing.Size(93, 22);
            this.MStripExitApplication.Text = "Exit";
            this.MStripExitApplication.Click += new System.EventHandler(this.MStripExitApplication_Click);
            // 
            // comportToolStripMenuItem
            // 
            this.comportToolStripMenuItem.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.comportToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MStripPortConnect,
            this.MStripPortDisconnect});
            this.comportToolStripMenuItem.Name = "comportToolStripMenuItem";
            this.comportToolStripMenuItem.Size = new System.Drawing.Size(67, 22);
            this.comportToolStripMenuItem.Text = "Comport";
            // 
            // MStripPortConnect
            // 
            this.MStripPortConnect.Name = "MStripPortConnect";
            this.MStripPortConnect.Size = new System.Drawing.Size(133, 22);
            this.MStripPortConnect.Text = "Connect";
            this.MStripPortConnect.Click += new System.EventHandler(this.MStripPortConnect_Click);
            // 
            // MStripPortDisconnect
            // 
            this.MStripPortDisconnect.Name = "MStripPortDisconnect";
            this.MStripPortDisconnect.Size = new System.Drawing.Size(133, 22);
            this.MStripPortDisconnect.Text = "Disconnect";
            this.MStripPortDisconnect.Click += new System.EventHandler(this.MStripDisconnect_Click);
            // 
            // eraseToolStripMenuItem
            // 
            this.eraseToolStripMenuItem.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.eraseToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.bootmanagerToolStripMenuItem,
            this.bootloaderToolStripMenuItem,
            this.application1MemoryToolStripMenuItem,
            this.application2MemoryToolStripMenuItem,
            this.nVSMemoryToolStripMenuItem,
            this.nVMMemoryToolStripMenuItem});
            this.eraseToolStripMenuItem.Name = "eraseToolStripMenuItem";
            this.eraseToolStripMenuItem.Size = new System.Drawing.Size(97, 22);
            this.eraseToolStripMenuItem.Text = "Erase Memory ";
            // 
            // bootmanagerToolStripMenuItem
            // 
            this.bootmanagerToolStripMenuItem.Name = "bootmanagerToolStripMenuItem";
            this.bootmanagerToolStripMenuItem.Size = new System.Drawing.Size(194, 22);
            this.bootmanagerToolStripMenuItem.Text = "Bootmanager Memory";
            this.bootmanagerToolStripMenuItem.Click += new System.EventHandler(this.bootmanagerToolStripMenuItem_Click);
            // 
            // bootloaderToolStripMenuItem
            // 
            this.bootloaderToolStripMenuItem.Name = "bootloaderToolStripMenuItem";
            this.bootloaderToolStripMenuItem.Size = new System.Drawing.Size(194, 22);
            this.bootloaderToolStripMenuItem.Text = "Bootloader Memory";
            this.bootloaderToolStripMenuItem.Click += new System.EventHandler(this.bootloaderToolStripMenuItem_Click);
            // 
            // application1MemoryToolStripMenuItem
            // 
            this.application1MemoryToolStripMenuItem.Name = "application1MemoryToolStripMenuItem";
            this.application1MemoryToolStripMenuItem.Size = new System.Drawing.Size(194, 22);
            this.application1MemoryToolStripMenuItem.Text = "Application1 Memory";
            this.application1MemoryToolStripMenuItem.Click += new System.EventHandler(this.application1MemoryToolStripMenuItem_Click);
            // 
            // application2MemoryToolStripMenuItem
            // 
            this.application2MemoryToolStripMenuItem.Name = "application2MemoryToolStripMenuItem";
            this.application2MemoryToolStripMenuItem.Size = new System.Drawing.Size(194, 22);
            this.application2MemoryToolStripMenuItem.Text = "Application2 Memory";
            this.application2MemoryToolStripMenuItem.Click += new System.EventHandler(this.application2MemoryToolStripMenuItem_Click);
            // 
            // nVSMemoryToolStripMenuItem
            // 
            this.nVSMemoryToolStripMenuItem.Name = "nVSMemoryToolStripMenuItem";
            this.nVSMemoryToolStripMenuItem.Size = new System.Drawing.Size(194, 22);
            this.nVSMemoryToolStripMenuItem.Text = "NVS Memory";
            this.nVSMemoryToolStripMenuItem.Click += new System.EventHandler(this.nVSMemoryToolStripMenuItem_Click);
            // 
            // nVMMemoryToolStripMenuItem
            // 
            this.nVMMemoryToolStripMenuItem.Name = "nVMMemoryToolStripMenuItem";
            this.nVMMemoryToolStripMenuItem.Size = new System.Drawing.Size(194, 22);
            this.nVMMemoryToolStripMenuItem.Text = "NVM Memory";
            this.nVMMemoryToolStripMenuItem.Click += new System.EventHandler(this.nVMMemoryToolStripMenuItem_Click);
            // 
            // settingsToolStripMenuItem
            // 
            this.settingsToolStripMenuItem.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.settingsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.nVSSettingsToolStripMenuItem,
            this.nVMSettingsToolStripMenuItem});
            this.settingsToolStripMenuItem.Name = "settingsToolStripMenuItem";
            this.settingsToolStripMenuItem.Size = new System.Drawing.Size(61, 22);
            this.settingsToolStripMenuItem.Text = "Settings";
            // 
            // nVSSettingsToolStripMenuItem
            // 
            this.nVSSettingsToolStripMenuItem.Name = "nVSSettingsToolStripMenuItem";
            this.nVSSettingsToolStripMenuItem.Size = new System.Drawing.Size(146, 22);
            this.nVSSettingsToolStripMenuItem.Text = "NVS Settings";
            this.nVSSettingsToolStripMenuItem.Click += new System.EventHandler(this.nVSSettingsToolStripMenuItem_Click);
            // 
            // nVMSettingsToolStripMenuItem
            // 
            this.nVMSettingsToolStripMenuItem.Name = "nVMSettingsToolStripMenuItem";
            this.nVMSettingsToolStripMenuItem.Size = new System.Drawing.Size(146, 22);
            this.nVMSettingsToolStripMenuItem.Text = "NVM Settings";
            this.nVMSettingsToolStripMenuItem.Click += new System.EventHandler(this.nVMSettingsToolStripMenuItem_Click);
            // 
            // BtnTransmit
            // 
            this.BtnTransmit.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.BtnTransmit.Cursor = System.Windows.Forms.Cursors.Hand;
            this.BtnTransmit.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BtnTransmit.Location = new System.Drawing.Point(570, 317);
            this.BtnTransmit.Margin = new System.Windows.Forms.Padding(2);
            this.BtnTransmit.Name = "BtnTransmit";
            this.BtnTransmit.Size = new System.Drawing.Size(83, 43);
            this.BtnTransmit.TabIndex = 9;
            this.BtnTransmit.Text = "Transmit";
            this.BtnTransmit.UseVisualStyleBackColor = false;
            this.BtnTransmit.Click += new System.EventHandler(this.BtnTransmit_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btnClearLog);
            this.groupBox2.Controls.Add(this.rtbxDataOut);
            this.groupBox2.Controls.Add(this.tBoxView);
            this.groupBox2.Controls.Add(this.BtnTransmit);
            this.groupBox2.Controls.Add(this.BtnSearch);
            this.groupBox2.Controls.Add(this.LMryAddress);
            this.groupBox2.Controls.Add(this.cBoxAppAddressSelect);
            this.groupBox2.Location = new System.Drawing.Point(220, 10);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox2.Size = new System.Drawing.Size(665, 417);
            this.groupBox2.TabIndex = 10;
            this.groupBox2.TabStop = false;
            // 
            // btnClearLog
            // 
            this.btnClearLog.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.btnClearLog.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnClearLog.Font = new System.Drawing.Font("Microsoft Tai Le", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnClearLog.Location = new System.Drawing.Point(557, 65);
            this.btnClearLog.Margin = new System.Windows.Forms.Padding(2);
            this.btnClearLog.Name = "btnClearLog";
            this.btnClearLog.Size = new System.Drawing.Size(51, 49);
            this.btnClearLog.TabIndex = 11;
            this.btnClearLog.Text = "Clear \r\nLog";
            this.btnClearLog.UseVisualStyleBackColor = false;
            this.btnClearLog.Click += new System.EventHandler(this.btnClearLog_Click);
            // 
            // rtbxDataOut
            // 
            this.rtbxDataOut.Font = new System.Drawing.Font("Microsoft Tai Le", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rtbxDataOut.Location = new System.Drawing.Point(8, 58);
            this.rtbxDataOut.Margin = new System.Windows.Forms.Padding(2);
            this.rtbxDataOut.Name = "rtbxDataOut";
            this.rtbxDataOut.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.rtbxDataOut.Size = new System.Drawing.Size(545, 348);
            this.rtbxDataOut.TabIndex = 10;
            this.rtbxDataOut.Text = "";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.groupBox2);
            this.groupBox3.Controls.Add(this.groupBox1);
            this.groupBox3.Location = new System.Drawing.Point(8, 23);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox3.Size = new System.Drawing.Size(892, 434);
            this.groupBox3.TabIndex = 11;
            this.groupBox3.TabStop = false;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.ClientSize = new System.Drawing.Size(904, 461);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tBoxView;
        private System.Windows.Forms.Button BtnSearch;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.ComboBox cBoxAppAddressSelect;
        private System.Windows.Forms.Label LMryAddress;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox CBoxComPort;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem comportToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem MStripPortConnect;
        private System.Windows.Forms.ToolStripMenuItem MStripPortDisconnect;
        private System.Windows.Forms.ToolStripMenuItem MStripExitApplication;
        private System.Windows.Forms.Button BtnTransmit;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.ToolStripMenuItem eraseToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem bootmanagerToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem bootloaderToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem application1MemoryToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem application2MemoryToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nVSMemoryToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nVMMemoryToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem settingsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nVSSettingsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nVMSettingsToolStripMenuItem;
        private System.Windows.Forms.RichTextBox rtbxDataOut;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox tbxParityBit;
        private System.Windows.Forms.TextBox tbxStopBit;
        private System.Windows.Forms.TextBox tbxDataBit;
        private System.Windows.Forms.TextBox tbxBaudRate;
        private System.Windows.Forms.Button btnClearLog;
    }
}

