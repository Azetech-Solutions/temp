namespace File_TryAccess_Tool
{
    partial class NVM_Form
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.tvNvmBlk = new System.Windows.Forms.TreeView();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.btnNVMexport = new System.Windows.Forms.Button();
            this.btnNVMimport = new System.Windows.Forms.Button();
            this.btnNVMupdateAll = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btnClearlog = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.lblControlsNVM = new System.Windows.Forms.Label();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.btnGetAllNvmData = new System.Windows.Forms.Button();
            this.btnNVMreOrg = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btnNVMclear = new System.Windows.Forms.Button();
            this.btnNVMupdate = new System.Windows.Forms.Button();
            this.rtbxNVMDataOut = new System.Windows.Forms.RichTextBox();
            this.groupBox1.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.groupBox1.Controls.Add(this.tvNvmBlk);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(320, 655);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            // 
            // tvNvmBlk
            // 
            this.tvNvmBlk.BackColor = System.Drawing.Color.LightGray;
            this.tvNvmBlk.Location = new System.Drawing.Point(8, 14);
            this.tvNvmBlk.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.tvNvmBlk.Name = "tvNvmBlk";
            this.tvNvmBlk.Size = new System.Drawing.Size(304, 633);
            this.tvNvmBlk.TabIndex = 0;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.btnNVMexport);
            this.groupBox5.Controls.Add(this.btnNVMimport);
            this.groupBox5.Controls.Add(this.btnNVMupdateAll);
            this.groupBox5.Location = new System.Drawing.Point(13, 58);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(296, 113);
            this.groupBox5.TabIndex = 0;
            this.groupBox5.TabStop = false;
            // 
            // btnNVMexport
            // 
            this.btnNVMexport.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.btnNVMexport.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnNVMexport.Location = new System.Drawing.Point(12, 15);
            this.btnNVMexport.Name = "btnNVMexport";
            this.btnNVMexport.Size = new System.Drawing.Size(122, 38);
            this.btnNVMexport.TabIndex = 4;
            this.btnNVMexport.Text = "Export";
            this.btnNVMexport.UseVisualStyleBackColor = false;
            this.btnNVMexport.Click += new System.EventHandler(this.btnNVMexport_Click);
            // 
            // btnNVMimport
            // 
            this.btnNVMimport.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.btnNVMimport.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnNVMimport.Location = new System.Drawing.Point(164, 15);
            this.btnNVMimport.Name = "btnNVMimport";
            this.btnNVMimport.Size = new System.Drawing.Size(122, 38);
            this.btnNVMimport.TabIndex = 7;
            this.btnNVMimport.Text = "Import";
            this.btnNVMimport.UseVisualStyleBackColor = false;
            this.btnNVMimport.Click += new System.EventHandler(this.btnNVMimport_Click);
            // 
            // btnNVMupdateAll
            // 
            this.btnNVMupdateAll.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.btnNVMupdateAll.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnNVMupdateAll.Location = new System.Drawing.Point(12, 64);
            this.btnNVMupdateAll.Name = "btnNVMupdateAll";
            this.btnNVMupdateAll.Size = new System.Drawing.Size(122, 38);
            this.btnNVMupdateAll.TabIndex = 8;
            this.btnNVMupdateAll.Text = "Update All";
            this.btnNVMupdateAll.UseVisualStyleBackColor = false;
            this.btnNVMupdateAll.Click += new System.EventHandler(this.btnNVMupdateAll_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.groupBox2.Controls.Add(this.btnClearlog);
            this.groupBox2.Controls.Add(this.groupBox3);
            this.groupBox2.Controls.Add(this.rtbxNVMDataOut);
            this.groupBox2.Location = new System.Drawing.Point(338, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(1171, 655);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            // 
            // btnClearlog
            // 
            this.btnClearlog.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.btnClearlog.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnClearlog.Location = new System.Drawing.Point(1020, 454);
            this.btnClearlog.Name = "btnClearlog";
            this.btnClearlog.Size = new System.Drawing.Size(122, 38);
            this.btnClearlog.TabIndex = 6;
            this.btnClearlog.Text = "Clear Log";
            this.btnClearlog.UseVisualStyleBackColor = false;
            this.btnClearlog.Click += new System.EventHandler(this.btnClearlog_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.lblControlsNVM);
            this.groupBox3.Controls.Add(this.groupBox6);
            this.groupBox3.Controls.Add(this.groupBox5);
            this.groupBox3.Controls.Add(this.groupBox4);
            this.groupBox3.Location = new System.Drawing.Point(199, 455);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(748, 187);
            this.groupBox3.TabIndex = 3;
            this.groupBox3.TabStop = false;
            // 
            // lblControlsNVM
            // 
            this.lblControlsNVM.AutoSize = true;
            this.lblControlsNVM.Font = new System.Drawing.Font("Microsoft Tai Le", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblControlsNVM.Location = new System.Drawing.Point(6, 22);
            this.lblControlsNVM.Name = "lblControlsNVM";
            this.lblControlsNVM.Size = new System.Drawing.Size(163, 21);
            this.lblControlsNVM.TabIndex = 8;
            this.lblControlsNVM.Text = "Controls NVM Block";
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.btnGetAllNvmData);
            this.groupBox6.Controls.Add(this.btnNVMreOrg);
            this.groupBox6.Location = new System.Drawing.Point(329, 57);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(254, 113);
            this.groupBox6.TabIndex = 7;
            this.groupBox6.TabStop = false;
            // 
            // btnGetAllNvmData
            // 
            this.btnGetAllNvmData.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.btnGetAllNvmData.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnGetAllNvmData.Location = new System.Drawing.Point(4, 16);
            this.btnGetAllNvmData.Name = "btnGetAllNvmData";
            this.btnGetAllNvmData.Size = new System.Drawing.Size(122, 38);
            this.btnGetAllNvmData.TabIndex = 7;
            this.btnGetAllNvmData.Text = "Get All";
            this.btnGetAllNvmData.UseVisualStyleBackColor = false;
            this.btnGetAllNvmData.Click += new System.EventHandler(this.btnGetAllNvmData_Click);
            // 
            // btnNVMreOrg
            // 
            this.btnNVMreOrg.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.btnNVMreOrg.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnNVMreOrg.Location = new System.Drawing.Point(4, 65);
            this.btnNVMreOrg.Name = "btnNVMreOrg";
            this.btnNVMreOrg.Size = new System.Drawing.Size(122, 38);
            this.btnNVMreOrg.TabIndex = 6;
            this.btnNVMreOrg.Text = "Re-Org";
            this.btnNVMreOrg.UseVisualStyleBackColor = false;
            this.btnNVMreOrg.Click += new System.EventHandler(this.btnNVMreOrg_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.btnNVMclear);
            this.groupBox4.Controls.Add(this.btnNVMupdate);
            this.groupBox4.Location = new System.Drawing.Point(598, 57);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(140, 113);
            this.groupBox4.TabIndex = 5;
            this.groupBox4.TabStop = false;
            // 
            // btnNVMclear
            // 
            this.btnNVMclear.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.btnNVMclear.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnNVMclear.Location = new System.Drawing.Point(10, 16);
            this.btnNVMclear.Name = "btnNVMclear";
            this.btnNVMclear.Size = new System.Drawing.Size(122, 38);
            this.btnNVMclear.TabIndex = 5;
            this.btnNVMclear.Text = "Clear";
            this.btnNVMclear.UseVisualStyleBackColor = false;
            this.btnNVMclear.Click += new System.EventHandler(this.btnNVMclear_Click);
            // 
            // btnNVMupdate
            // 
            this.btnNVMupdate.BackColor = System.Drawing.SystemColors.ScrollBar;
            this.btnNVMupdate.Font = new System.Drawing.Font("Microsoft Tai Le", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnNVMupdate.Location = new System.Drawing.Point(10, 65);
            this.btnNVMupdate.Name = "btnNVMupdate";
            this.btnNVMupdate.Size = new System.Drawing.Size(122, 40);
            this.btnNVMupdate.TabIndex = 2;
            this.btnNVMupdate.Text = "Update";
            this.btnNVMupdate.UseVisualStyleBackColor = false;
            this.btnNVMupdate.Click += new System.EventHandler(this.btnNVMupdate_Click);
            // 
            // rtbxNVMDataOut
            // 
            this.rtbxNVMDataOut.Location = new System.Drawing.Point(14, 14);
            this.rtbxNVMDataOut.Name = "rtbxNVMDataOut";
            this.rtbxNVMDataOut.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.rtbxNVMDataOut.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.ForcedBoth;
            this.rtbxNVMDataOut.Size = new System.Drawing.Size(1143, 434);
            this.rtbxNVMDataOut.TabIndex = 0;
            this.rtbxNVMDataOut.Text = "";
            this.rtbxNVMDataOut.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.rtbxNVMDataOut_KeyPress);
            // 
            // NVM_Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1512, 671);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
            this.MaximumSize = new System.Drawing.Size(1534, 727);
            this.Name = "NVM_Form";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "NVM_Form";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.NVM_Form_FormClosed);
            this.groupBox1.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btnNVMexport;
        private System.Windows.Forms.Button btnNVMclear;
        private System.Windows.Forms.Button btnNVMreOrg;
        private System.Windows.Forms.Button btnNVMimport;
        private System.Windows.Forms.Button btnNVMupdateAll;
        private System.Windows.Forms.Button btnNVMupdate;
        private System.Windows.Forms.RichTextBox rtbxNVMDataOut;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Button btnGetAllNvmData;
        private System.Windows.Forms.TreeView tvNvmBlk;
        private System.Windows.Forms.Button btnClearlog;
        private System.Windows.Forms.Label lblControlsNVM;
    }
}