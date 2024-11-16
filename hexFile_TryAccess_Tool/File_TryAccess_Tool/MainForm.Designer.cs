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
            this.btnRefresh = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.label1 = new System.Windows.Forms.Label();
            this.CBoxComPort = new System.Windows.Forms.ComboBox();
            this.BtnTransmit = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btnVerApp2 = new System.Windows.Forms.Button();
            this.lblMinorVer = new System.Windows.Forms.Label();
            this.lblReleseVer = new System.Windows.Forms.Label();
            this.lblMajorVer = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.btnVerApp1 = new System.Windows.Forms.Button();
            this.lblBulidVer = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
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
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.btnClearLog = new System.Windows.Forms.Button();
            this.rtbxDataOut = new System.Windows.Forms.RichTextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.groupBox1.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tBoxView
            // 
            this.tBoxView.Font = new System.Drawing.Font("Microsoft Tai Le", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tBoxView.Location = new System.Drawing.Point(12, 42);
            this.tBoxView.Multiline = true;
            this.tBoxView.Name = "tBoxView";
            this.tBoxView.Size = new System.Drawing.Size(789, 32);
            this.tBoxView.TabIndex = 0;
            this.tBoxView.WordWrap = false;
            // 
            // BtnSearch
            // 
            this.BtnSearch.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.BtnSearch.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.BtnSearch.Cursor = System.Windows.Forms.Cursors.Hand;
            this.BtnSearch.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold);
            this.BtnSearch.Location = new System.Drawing.Point(807, 42);
            this.BtnSearch.Name = "BtnSearch";
            this.BtnSearch.Size = new System.Drawing.Size(164, 35);
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
            this.cBoxAppAddressSelect.Location = new System.Drawing.Point(210, 118);
            this.cBoxAppAddressSelect.Name = "cBoxAppAddressSelect";
            this.cBoxAppAddressSelect.Size = new System.Drawing.Size(127, 29);
            this.cBoxAppAddressSelect.TabIndex = 5;
            this.cBoxAppAddressSelect.SelectedValueChanged += new System.EventHandler(this.cBoxAppAddressSelect_SelectedValueChanged);
            // 
            // LMryAddress
            // 
            this.LMryAddress.AutoSize = true;
            this.LMryAddress.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LMryAddress.Location = new System.Drawing.Point(69, 108);
            this.LMryAddress.Name = "LMryAddress";
            this.LMryAddress.Size = new System.Drawing.Size(134, 46);
            this.LMryAddress.TabIndex = 6;
            this.LMryAddress.Text = "Flash Memory \r\n     Address";
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.SystemColors.ControlDark;
            this.groupBox1.Controls.Add(this.btnRefresh);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.progressBar1);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.CBoxComPort);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(13, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(357, 184);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            // 
            // btnRefresh
            // 
            this.btnRefresh.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnRefresh.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.btnRefresh.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.btnRefresh.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnRefresh.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btnRefresh.Font = new System.Drawing.Font("Microsoft Tai Le", 8F);
            this.btnRefresh.Image = global::File_TryAccess_Tool.Properties.Resources.icons8_refresh_30;
            this.btnRefresh.Location = new System.Drawing.Point(270, 49);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(57, 22);
            this.btnRefresh.TabIndex = 22;
            this.btnRefresh.UseVisualStyleBackColor = false;
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Imprint MT Shadow", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(26, 37);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(194, 21);
            this.label6.TabIndex = 10;
            this.label6.Text = "COM PORT Control";
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(59, 154);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(243, 10);
            this.progressBar1.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(26, 108);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(115, 23);
            this.label1.TabIndex = 5;
            this.label1.Text = "COM PORT :";
            // 
            // CBoxComPort
            // 
            this.CBoxComPort.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.CBoxComPort.FormattingEnabled = true;
            this.CBoxComPort.Location = new System.Drawing.Point(206, 105);
            this.CBoxComPort.Name = "CBoxComPort";
            this.CBoxComPort.Size = new System.Drawing.Size(121, 31);
            this.CBoxComPort.TabIndex = 0;
            // 
            // BtnTransmit
            // 
            this.BtnTransmit.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.BtnTransmit.Cursor = System.Windows.Forms.Cursors.Hand;
            this.BtnTransmit.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BtnTransmit.Location = new System.Drawing.Point(537, 108);
            this.BtnTransmit.Name = "BtnTransmit";
            this.BtnTransmit.Size = new System.Drawing.Size(136, 46);
            this.BtnTransmit.TabIndex = 9;
            this.BtnTransmit.Text = "Download";
            this.BtnTransmit.UseVisualStyleBackColor = false;
            this.BtnTransmit.Click += new System.EventHandler(this.BtnTransmit_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.btnVerApp2);
            this.groupBox4.Controls.Add(this.lblMinorVer);
            this.groupBox4.Controls.Add(this.lblReleseVer);
            this.groupBox4.Controls.Add(this.lblMajorVer);
            this.groupBox4.Controls.Add(this.label9);
            this.groupBox4.Controls.Add(this.label8);
            this.groupBox4.Controls.Add(this.btnVerApp1);
            this.groupBox4.Controls.Add(this.lblBulidVer);
            this.groupBox4.Controls.Add(this.label11);
            this.groupBox4.Controls.Add(this.label7);
            this.groupBox4.Controls.Add(this.label10);
            this.groupBox4.Location = new System.Drawing.Point(13, 196);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(357, 240);
            this.groupBox4.TabIndex = 15;
            this.groupBox4.TabStop = false;
            // 
            // btnVerApp2
            // 
            this.btnVerApp2.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.btnVerApp2.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnVerApp2.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnVerApp2.Location = new System.Drawing.Point(206, 60);
            this.btnVerApp2.Name = "btnVerApp2";
            this.btnVerApp2.Size = new System.Drawing.Size(124, 40);
            this.btnVerApp2.TabIndex = 13;
            this.btnVerApp2.Text = "App2";
            this.btnVerApp2.UseVisualStyleBackColor = false;
            this.btnVerApp2.Click += new System.EventHandler(this.btnVerApp2_Click);
            // 
            // lblMinorVer
            // 
            this.lblMinorVer.AutoSize = true;
            this.lblMinorVer.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblMinorVer.Location = new System.Drawing.Point(257, 144);
            this.lblMinorVer.Name = "lblMinorVer";
            this.lblMinorVer.Size = new System.Drawing.Size(17, 23);
            this.lblMinorVer.TabIndex = 19;
            this.lblMinorVer.Text = "-";
            this.lblMinorVer.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblReleseVer
            // 
            this.lblReleseVer.AutoSize = true;
            this.lblReleseVer.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblReleseVer.Location = new System.Drawing.Point(256, 204);
            this.lblReleseVer.Name = "lblReleseVer";
            this.lblReleseVer.Size = new System.Drawing.Size(17, 23);
            this.lblReleseVer.TabIndex = 21;
            this.lblReleseVer.Text = "-";
            this.lblReleseVer.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblMajorVer
            // 
            this.lblMajorVer.AutoSize = true;
            this.lblMajorVer.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblMajorVer.Location = new System.Drawing.Point(256, 113);
            this.lblMajorVer.Name = "lblMajorVer";
            this.lblMajorVer.Size = new System.Drawing.Size(17, 23);
            this.lblMajorVer.TabIndex = 18;
            this.lblMajorVer.Text = "-";
            this.lblMajorVer.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(10, 144);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(155, 23);
            this.label9.TabIndex = 15;
            this.label9.Text = "Minor Version    :";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(10, 113);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(154, 23);
            this.label8.TabIndex = 14;
            this.label8.Text = "Major Version    :";
            // 
            // btnVerApp1
            // 
            this.btnVerApp1.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.btnVerApp1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnVerApp1.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnVerApp1.Location = new System.Drawing.Point(30, 60);
            this.btnVerApp1.Name = "btnVerApp1";
            this.btnVerApp1.Size = new System.Drawing.Size(124, 40);
            this.btnVerApp1.TabIndex = 12;
            this.btnVerApp1.Text = "App1";
            this.btnVerApp1.UseVisualStyleBackColor = false;
            this.btnVerApp1.Click += new System.EventHandler(this.btnVerApp1_Click);
            // 
            // lblBulidVer
            // 
            this.lblBulidVer.AutoSize = true;
            this.lblBulidVer.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblBulidVer.Location = new System.Drawing.Point(256, 176);
            this.lblBulidVer.Name = "lblBulidVer";
            this.lblBulidVer.Size = new System.Drawing.Size(17, 23);
            this.lblBulidVer.TabIndex = 20;
            this.lblBulidVer.Text = "-";
            this.lblBulidVer.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label11.Location = new System.Drawing.Point(9, 204);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(154, 23);
            this.label11.TabIndex = 17;
            this.label11.Text = "Release Version :";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Imprint MT Shadow", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(120, 22);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(129, 24);
            this.label7.TabIndex = 11;
            this.label7.Text = "App Version";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.Location = new System.Drawing.Point(10, 176);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(153, 23);
            this.label10.TabIndex = 16;
            this.label10.Text = "Build Version     :";
            // 
            // menuStrip1
            // 
            this.menuStrip1.GripMargin = new System.Windows.Forms.Padding(2, 2, 0, 2);
            this.menuStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Visible;
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.comportToolStripMenuItem,
            this.eraseToolStripMenuItem,
            this.settingsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.menuStrip1.Size = new System.Drawing.Size(1410, 33);
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
            this.MStripExitApplication.Click += new System.EventHandler(this.MStripExitApplication_Click);
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
            this.nVSMemoryToolStripMenuItem.Click += new System.EventHandler(this.nVSMemoryToolStripMenuItem_Click);
            // 
            // nVMMemoryToolStripMenuItem
            // 
            this.nVMMemoryToolStripMenuItem.Name = "nVMMemoryToolStripMenuItem";
            this.nVMMemoryToolStripMenuItem.Size = new System.Drawing.Size(294, 34);
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
            this.settingsToolStripMenuItem.Size = new System.Drawing.Size(92, 29);
            this.settingsToolStripMenuItem.Text = "Settings";
            // 
            // nVSSettingsToolStripMenuItem
            // 
            this.nVSSettingsToolStripMenuItem.Name = "nVSSettingsToolStripMenuItem";
            this.nVSSettingsToolStripMenuItem.Size = new System.Drawing.Size(223, 34);
            this.nVSSettingsToolStripMenuItem.Text = "NVS Settings";
            this.nVSSettingsToolStripMenuItem.Click += new System.EventHandler(this.nVSSettingsToolStripMenuItem_Click);
            // 
            // nVMSettingsToolStripMenuItem
            // 
            this.nVMSettingsToolStripMenuItem.Name = "nVMSettingsToolStripMenuItem";
            this.nVMSettingsToolStripMenuItem.Size = new System.Drawing.Size(223, 34);
            this.nVMSettingsToolStripMenuItem.Text = "NVM Settings";
            this.nVMSettingsToolStripMenuItem.Click += new System.EventHandler(this.nVMSettingsToolStripMenuItem_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.SystemColors.ControlDark;
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.btnClearLog);
            this.groupBox2.Controls.Add(this.BtnTransmit);
            this.groupBox2.Controls.Add(this.cBoxAppAddressSelect);
            this.groupBox2.Controls.Add(this.rtbxDataOut);
            this.groupBox2.Controls.Add(this.LMryAddress);
            this.groupBox2.Controls.Add(this.tBoxView);
            this.groupBox2.Controls.Add(this.BtnSearch);
            this.groupBox2.Location = new System.Drawing.Point(8, 25);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(981, 599);
            this.groupBox2.TabIndex = 10;
            this.groupBox2.TabStop = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Tai Le", 14F, System.Drawing.FontStyle.Bold);
            this.label2.Location = new System.Drawing.Point(412, 114);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(114, 35);
            this.label2.TabIndex = 16;
            this.label2.Text = "Flash   :";
            // 
            // btnClearLog
            // 
            this.btnClearLog.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.btnClearLog.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnClearLog.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold);
            this.btnClearLog.Location = new System.Drawing.Point(807, 131);
            this.btnClearLog.Name = "btnClearLog";
            this.btnClearLog.Size = new System.Drawing.Size(164, 38);
            this.btnClearLog.TabIndex = 11;
            this.btnClearLog.Text = "Clear Log";
            this.btnClearLog.UseVisualStyleBackColor = false;
            this.btnClearLog.Click += new System.EventHandler(this.btnClearLog_Click);
            // 
            // rtbxDataOut
            // 
            this.rtbxDataOut.BackColor = System.Drawing.SystemColors.ControlLight;
            this.rtbxDataOut.Font = new System.Drawing.Font("Microsoft Tai Le", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rtbxDataOut.Location = new System.Drawing.Point(14, 177);
            this.rtbxDataOut.Name = "rtbxDataOut";
            this.rtbxDataOut.ReadOnly = true;
            this.rtbxDataOut.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.rtbxDataOut.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.ForcedBoth;
            this.rtbxDataOut.Size = new System.Drawing.Size(957, 416);
            this.rtbxDataOut.TabIndex = 10;
            this.rtbxDataOut.Text = "";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.panel1);
            this.groupBox3.Controls.Add(this.groupBox2);
            this.groupBox3.Location = new System.Drawing.Point(12, 35);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(1391, 635);
            this.groupBox3.TabIndex = 11;
            this.groupBox3.TabStop = false;
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.ControlDark;
            this.panel1.Controls.Add(this.groupBox1);
            this.panel1.Controls.Add(this.groupBox4);
            this.panel1.Location = new System.Drawing.Point(995, 25);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(386, 593);
            this.panel1.TabIndex = 11;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.ClientSize = new System.Drawing.Size(1410, 674);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
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
        private System.Windows.Forms.Button btnClearLog;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button btnVerApp2;
        private System.Windows.Forms.Button btnVerApp1;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label lblReleseVer;
        private System.Windows.Forms.Label lblBulidVer;
        private System.Windows.Forms.Label lblMinorVer;
        private System.Windows.Forms.Label lblMajorVer;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button btnRefresh;
    }
}

