namespace File_TryAccess_Tool
{
    partial class Form1
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
            this.chkBoxNVSMode = new System.Windows.Forms.CheckBox();
            this.chkBoxFlashMode = new System.Windows.Forms.CheckBox();
            this.cBoxAppAddressSelect = new System.Windows.Forms.ComboBox();
            this.LMryAddress = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.CboxParityBit = new System.Windows.Forms.ComboBox();
            this.CboxStopBit = new System.Windows.Forms.ComboBox();
            this.CboxDataBits = new System.Windows.Forms.ComboBox();
            this.CboxBaudRate = new System.Windows.Forms.ComboBox();
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
            this.tboxDataOut = new System.Windows.Forms.RichTextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // tBoxView
            // 
            this.tBoxView.Location = new System.Drawing.Point(12, 45);
            this.tBoxView.Multiline = true;
            this.tBoxView.Name = "tBoxView";
            this.tBoxView.Size = new System.Drawing.Size(442, 32);
            this.tBoxView.TabIndex = 0;
            this.tBoxView.WordWrap = false;
            // 
            // BtnSearch
            // 
            this.BtnSearch.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.BtnSearch.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.BtnSearch.Cursor = System.Windows.Forms.Cursors.Hand;
            this.BtnSearch.Font = new System.Drawing.Font("Microsoft Tai Le", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BtnSearch.Location = new System.Drawing.Point(467, 45);
            this.BtnSearch.Name = "BtnSearch";
            this.BtnSearch.Size = new System.Drawing.Size(92, 32);
            this.BtnSearch.TabIndex = 1;
            this.BtnSearch.Text = "File Path";
            this.BtnSearch.UseVisualStyleBackColor = false;
            this.BtnSearch.Click += new System.EventHandler(this.BtnSearch_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // chkBoxNVSMode
            // 
            this.chkBoxNVSMode.AutoSize = true;
            this.chkBoxNVSMode.Cursor = System.Windows.Forms.Cursors.Hand;
            this.chkBoxNVSMode.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.chkBoxNVSMode.Location = new System.Drawing.Point(426, 127);
            this.chkBoxNVSMode.Name = "chkBoxNVSMode";
            this.chkBoxNVSMode.Size = new System.Drawing.Size(126, 27);
            this.chkBoxNVSMode.TabIndex = 3;
            this.chkBoxNVSMode.Text = "NVS Mode";
            this.chkBoxNVSMode.UseVisualStyleBackColor = true;
            this.chkBoxNVSMode.CheckedChanged += new System.EventHandler(this.chkBoxNVSMode_CheckedChanged);
            // 
            // chkBoxFlashMode
            // 
            this.chkBoxFlashMode.AutoSize = true;
            this.chkBoxFlashMode.Cursor = System.Windows.Forms.Cursors.Hand;
            this.chkBoxFlashMode.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.chkBoxFlashMode.Location = new System.Drawing.Point(426, 161);
            this.chkBoxFlashMode.Name = "chkBoxFlashMode";
            this.chkBoxFlashMode.Size = new System.Drawing.Size(133, 27);
            this.chkBoxFlashMode.TabIndex = 4;
            this.chkBoxFlashMode.Text = "Flash Mode";
            this.chkBoxFlashMode.UseVisualStyleBackColor = true;
            this.chkBoxFlashMode.CheckedChanged += new System.EventHandler(this.chkBoxFlashMode_CheckedChanged);
            // 
            // cBoxAppAddressSelect
            // 
            this.cBoxAppAddressSelect.Cursor = System.Windows.Forms.Cursors.Default;
            this.cBoxAppAddressSelect.Font = new System.Drawing.Font("Microsoft Tai Le", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cBoxAppAddressSelect.FormattingEnabled = true;
            this.cBoxAppAddressSelect.Items.AddRange(new object[] {
            "App1",
            "App2"});
            this.cBoxAppAddressSelect.Location = new System.Drawing.Point(430, 256);
            this.cBoxAppAddressSelect.Name = "cBoxAppAddressSelect";
            this.cBoxAppAddressSelect.Size = new System.Drawing.Size(127, 29);
            this.cBoxAppAddressSelect.TabIndex = 5;
            // 
            // LMryAddress
            // 
            this.LMryAddress.AutoSize = true;
            this.LMryAddress.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LMryAddress.Location = new System.Drawing.Point(429, 201);
            this.LMryAddress.Name = "LMryAddress";
            this.LMryAddress.Size = new System.Drawing.Size(134, 46);
            this.LMryAddress.TabIndex = 6;
            this.LMryAddress.Text = "Flash Memory \r\n     Address";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.progressBar1);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.CboxParityBit);
            this.groupBox1.Controls.Add(this.CboxStopBit);
            this.groupBox1.Controls.Add(this.CboxDataBits);
            this.groupBox1.Controls.Add(this.CboxBaudRate);
            this.groupBox1.Controls.Add(this.CBoxComPort);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(7, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(317, 433);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "COM PORT Control";
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(19, 320);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(254, 18);
            this.progressBar1.TabIndex = 2;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(29, 249);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(99, 23);
            this.label5.TabIndex = 9;
            this.label5.Text = "Parity Bit :";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(29, 198);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(88, 23);
            this.label4.TabIndex = 8;
            this.label4.Text = "Stop Bit :";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(29, 147);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(97, 23);
            this.label3.TabIndex = 7;
            this.label3.Text = "Data Bits :";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(25, 93);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(108, 23);
            this.label2.TabIndex = 6;
            this.label2.Text = "Baud Rate :";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(25, 46);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(115, 23);
            this.label1.TabIndex = 5;
            this.label1.Text = "COM PORT :";
            // 
            // CboxParityBit
            // 
            this.CboxParityBit.FormattingEnabled = true;
            this.CboxParityBit.Items.AddRange(new object[] {
            "None",
            "Odd",
            "Even"});
            this.CboxParityBit.Location = new System.Drawing.Point(152, 246);
            this.CboxParityBit.Name = "CboxParityBit";
            this.CboxParityBit.Size = new System.Drawing.Size(121, 31);
            this.CboxParityBit.TabIndex = 4;
            // 
            // CboxStopBit
            // 
            this.CboxStopBit.FormattingEnabled = true;
            this.CboxStopBit.Items.AddRange(new object[] {
            "1",
            "2"});
            this.CboxStopBit.Location = new System.Drawing.Point(152, 194);
            this.CboxStopBit.Name = "CboxStopBit";
            this.CboxStopBit.Size = new System.Drawing.Size(121, 31);
            this.CboxStopBit.TabIndex = 3;
            // 
            // CboxDataBits
            // 
            this.CboxDataBits.FormattingEnabled = true;
            this.CboxDataBits.Items.AddRange(new object[] {
            "7",
            "8",
            "9"});
            this.CboxDataBits.Location = new System.Drawing.Point(152, 144);
            this.CboxDataBits.Name = "CboxDataBits";
            this.CboxDataBits.Size = new System.Drawing.Size(121, 31);
            this.CboxDataBits.TabIndex = 2;
            // 
            // CboxBaudRate
            // 
            this.CboxBaudRate.FormattingEnabled = true;
            this.CboxBaudRate.Items.AddRange(new object[] {
            "2400",
            "4800",
            "9600",
            "19200",
            "38400",
            "57600",
            "115200"});
            this.CboxBaudRate.Location = new System.Drawing.Point(152, 94);
            this.CboxBaudRate.Name = "CboxBaudRate";
            this.CboxBaudRate.Size = new System.Drawing.Size(121, 31);
            this.CboxBaudRate.TabIndex = 1;
            // 
            // CBoxComPort
            // 
            this.CBoxComPort.FormattingEnabled = true;
            this.CBoxComPort.Location = new System.Drawing.Point(152, 43);
            this.CBoxComPort.Name = "CBoxComPort";
            this.CBoxComPort.Size = new System.Drawing.Size(121, 31);
            this.CBoxComPort.TabIndex = 0;
            // 
            // menuStrip1
            // 
            this.menuStrip1.GripMargin = new System.Windows.Forms.Padding(2, 2, 0, 2);
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.comportToolStripMenuItem,
            this.eraseToolStripMenuItem,
            this.settingsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(940, 33);
            this.menuStrip1.TabIndex = 8;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MStripExitApplication});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(54, 29);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // MStripExitApplication
            // 
            this.MStripExitApplication.Name = "MStripExitApplication";
            this.MStripExitApplication.Size = new System.Drawing.Size(141, 34);
            this.MStripExitApplication.Text = "Exit";
            // 
            // comportToolStripMenuItem
            // 
            this.comportToolStripMenuItem.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.comportToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MStripPortConnect,
            this.MStripPortDisconnect});
            this.comportToolStripMenuItem.Name = "comportToolStripMenuItem";
            this.comportToolStripMenuItem.Size = new System.Drawing.Size(100, 29);
            this.comportToolStripMenuItem.Text = "Comport";
            // 
            // MStripPortConnect
            // 
            this.MStripPortConnect.Name = "MStripPortConnect";
            this.MStripPortConnect.Size = new System.Drawing.Size(201, 34);
            this.MStripPortConnect.Text = "Connect";
            this.MStripPortConnect.Click += new System.EventHandler(this.MStripPortConnect_Click);
            // 
            // MStripPortDisconnect
            // 
            this.MStripPortDisconnect.Name = "MStripPortDisconnect";
            this.MStripPortDisconnect.Size = new System.Drawing.Size(201, 34);
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
            this.eraseToolStripMenuItem.Size = new System.Drawing.Size(146, 29);
            this.eraseToolStripMenuItem.Text = "Erase Memory ";
            // 
            // bootmanagerToolStripMenuItem
            // 
            this.bootmanagerToolStripMenuItem.Name = "bootmanagerToolStripMenuItem";
            this.bootmanagerToolStripMenuItem.Size = new System.Drawing.Size(294, 34);
            this.bootmanagerToolStripMenuItem.Text = "Bootmanager Memory";
            this.bootmanagerToolStripMenuItem.Click += new System.EventHandler(this.bootmanagerToolStripMenuItem_Click);
            // 
            // bootloaderToolStripMenuItem
            // 
            this.bootloaderToolStripMenuItem.Name = "bootloaderToolStripMenuItem";
            this.bootloaderToolStripMenuItem.Size = new System.Drawing.Size(294, 34);
            this.bootloaderToolStripMenuItem.Text = "Bootloader Memory";
            this.bootloaderToolStripMenuItem.Click += new System.EventHandler(this.bootloaderToolStripMenuItem_Click);
            // 
            // application1MemoryToolStripMenuItem
            // 
            this.application1MemoryToolStripMenuItem.Name = "application1MemoryToolStripMenuItem";
            this.application1MemoryToolStripMenuItem.Size = new System.Drawing.Size(294, 34);
            this.application1MemoryToolStripMenuItem.Text = "Application1 Memory";
            this.application1MemoryToolStripMenuItem.Click += new System.EventHandler(this.application1MemoryToolStripMenuItem_Click);
            // 
            // application2MemoryToolStripMenuItem
            // 
            this.application2MemoryToolStripMenuItem.Name = "application2MemoryToolStripMenuItem";
            this.application2MemoryToolStripMenuItem.Size = new System.Drawing.Size(294, 34);
            this.application2MemoryToolStripMenuItem.Text = "Application2 Memory";
            this.application2MemoryToolStripMenuItem.Click += new System.EventHandler(this.application2MemoryToolStripMenuItem_Click);
            // 
            // nVSMemoryToolStripMenuItem
            // 
            this.nVSMemoryToolStripMenuItem.Name = "nVSMemoryToolStripMenuItem";
            this.nVSMemoryToolStripMenuItem.Size = new System.Drawing.Size(294, 34);
            this.nVSMemoryToolStripMenuItem.Text = "NVS Memory";
            // 
            // nVMMemoryToolStripMenuItem
            // 
            this.nVMMemoryToolStripMenuItem.Name = "nVMMemoryToolStripMenuItem";
            this.nVMMemoryToolStripMenuItem.Size = new System.Drawing.Size(294, 34);
            this.nVMMemoryToolStripMenuItem.Text = "NVM Memory";
            // 
            // settingsToolStripMenuItem
            // 
            this.settingsToolStripMenuItem.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.settingsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.nVSSettingsToolStripMenuItem,
            this.nVMSettingsToolStripMenuItem});
            this.settingsToolStripMenuItem.Name = "settingsToolStripMenuItem";
            this.settingsToolStripMenuItem.Size = new System.Drawing.Size(92, 29);
            this.settingsToolStripMenuItem.Text = "Settings";
            // 
            // nVSSettingsToolStripMenuItem
            // 
            this.nVSSettingsToolStripMenuItem.Name = "nVSSettingsToolStripMenuItem";
            this.nVSSettingsToolStripMenuItem.Size = new System.Drawing.Size(223, 34);
            this.nVSSettingsToolStripMenuItem.Text = "NVS Settings";
            // 
            // nVMSettingsToolStripMenuItem
            // 
            this.nVMSettingsToolStripMenuItem.Name = "nVMSettingsToolStripMenuItem";
            this.nVMSettingsToolStripMenuItem.Size = new System.Drawing.Size(223, 34);
            this.nVMSettingsToolStripMenuItem.Text = "NVM Settings";
            // 
            // BtnTransmit
            // 
            this.BtnTransmit.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.BtnTransmit.Cursor = System.Windows.Forms.Cursors.Hand;
            this.BtnTransmit.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BtnTransmit.Location = new System.Drawing.Point(439, 324);
            this.BtnTransmit.Name = "BtnTransmit";
            this.BtnTransmit.Size = new System.Drawing.Size(124, 54);
            this.BtnTransmit.TabIndex = 9;
            this.BtnTransmit.Text = "Transmit";
            this.BtnTransmit.UseVisualStyleBackColor = false;
            this.BtnTransmit.Click += new System.EventHandler(this.BtnTransmit_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.tboxDataOut);
            this.groupBox2.Controls.Add(this.tBoxView);
            this.groupBox2.Controls.Add(this.BtnTransmit);
            this.groupBox2.Controls.Add(this.BtnSearch);
            this.groupBox2.Controls.Add(this.LMryAddress);
            this.groupBox2.Controls.Add(this.chkBoxFlashMode);
            this.groupBox2.Controls.Add(this.cBoxAppAddressSelect);
            this.groupBox2.Controls.Add(this.chkBoxNVSMode);
            this.groupBox2.Location = new System.Drawing.Point(330, 15);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(577, 431);
            this.groupBox2.TabIndex = 10;
            this.groupBox2.TabStop = false;
            // 
            // tboxDataOut
            // 
            this.tboxDataOut.Location = new System.Drawing.Point(12, 100);
            this.tboxDataOut.Name = "tboxDataOut";
            this.tboxDataOut.Size = new System.Drawing.Size(404, 278);
            this.tboxDataOut.TabIndex = 10;
            this.tboxDataOut.Text = "";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.groupBox2);
            this.groupBox3.Controls.Add(this.groupBox1);
            this.groupBox3.Location = new System.Drawing.Point(12, 36);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(913, 452);
            this.groupBox3.TabIndex = 11;
            this.groupBox3.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.ClientSize = new System.Drawing.Size(940, 499);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
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
        private System.Windows.Forms.CheckBox chkBoxNVSMode;
        private System.Windows.Forms.CheckBox chkBoxFlashMode;
        private System.Windows.Forms.ComboBox cBoxAppAddressSelect;
        private System.Windows.Forms.Label LMryAddress;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox CboxParityBit;
        private System.Windows.Forms.ComboBox CboxStopBit;
        private System.Windows.Forms.ComboBox CboxDataBits;
        private System.Windows.Forms.ComboBox CboxBaudRate;
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
        private System.Windows.Forms.RichTextBox tboxDataOut;
        private System.Windows.Forms.GroupBox groupBox3;
    }
}

