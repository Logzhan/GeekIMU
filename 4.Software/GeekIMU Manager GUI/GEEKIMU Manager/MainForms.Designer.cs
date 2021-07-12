namespace DM_CalibrationTools
{
    partial class MainForms
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForms));
            this.Control_Panel = new System.Windows.Forms.Panel();
            this.label_line = new System.Windows.Forms.Label();
            this.Panel_logo = new System.Windows.Forms.Panel();
            this.label_dev_status = new System.Windows.Forms.Label();
            this.label_Form_Name = new System.Windows.Forms.Label();
            this.MainPanel = new System.Windows.Forms.Panel();
            this.Btn_my_dev = new System.Windows.Forms.Button();
            this.Btn_support = new System.Windows.Forms.Button();
            this.Btn_software_Setting = new System.Windows.Forms.Button();
            this.Btn_min = new System.Windows.Forms.Button();
            this.Btn_dev_Setting = new System.Windows.Forms.Button();
            this.Btn_DFU_DownLoad = new System.Windows.Forms.Button();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.Btn_Close = new System.Windows.Forms.Button();
            this.Control_Panel.SuspendLayout();
            this.Panel_logo.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            this.SuspendLayout();
            // 
            // Control_Panel
            // 
            this.Control_Panel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Control_Panel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(58)))), ((int)(((byte)(151)))), ((int)(((byte)(229)))));
            this.Control_Panel.Controls.Add(this.Btn_my_dev);
            this.Control_Panel.Controls.Add(this.Btn_support);
            this.Control_Panel.Controls.Add(this.Btn_software_Setting);
            this.Control_Panel.Controls.Add(this.label_line);
            this.Control_Panel.Controls.Add(this.Btn_min);
            this.Control_Panel.Controls.Add(this.Btn_dev_Setting);
            this.Control_Panel.Controls.Add(this.Btn_DFU_DownLoad);
            this.Control_Panel.Controls.Add(this.Panel_logo);
            this.Control_Panel.Controls.Add(this.Btn_Close);
            this.Control_Panel.Location = new System.Drawing.Point(-1, 0);
            this.Control_Panel.Name = "Control_Panel";
            this.Control_Panel.Size = new System.Drawing.Size(1028, 88);
            this.Control_Panel.TabIndex = 16;
            this.Control_Panel.Paint += new System.Windows.Forms.PaintEventHandler(this.Control_Panel_Paint);
            this.Control_Panel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Control_Panel_MouseDown);
            this.Control_Panel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Control_Panel_MouseMove);
            // 
            // label_line
            // 
            this.label_line.AutoSize = true;
            this.label_line.BackColor = System.Drawing.Color.Transparent;
            this.label_line.ForeColor = System.Drawing.Color.White;
            this.label_line.Location = new System.Drawing.Point(959, 7);
            this.label_line.Name = "label_line";
            this.label_line.Size = new System.Drawing.Size(11, 12);
            this.label_line.TabIndex = 16;
            this.label_line.Text = "|";
            // 
            // Panel_logo
            // 
            this.Panel_logo.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(42)))), ((int)(((byte)(138)))), ((int)(((byte)(219)))));
            this.Panel_logo.Controls.Add(this.pictureBox2);
            this.Panel_logo.Controls.Add(this.pictureBox3);
            this.Panel_logo.Controls.Add(this.label_dev_status);
            this.Panel_logo.Controls.Add(this.label_Form_Name);
            this.Panel_logo.Location = new System.Drawing.Point(3, 0);
            this.Panel_logo.Name = "Panel_logo";
            this.Panel_logo.Size = new System.Drawing.Size(207, 88);
            this.Panel_logo.TabIndex = 16;
            this.Panel_logo.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Panel_logo_MouseDown);
            this.Panel_logo.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Panel_logo_MouseMove);
            // 
            // label_dev_status
            // 
            this.label_dev_status.AutoSize = true;
            this.label_dev_status.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_dev_status.ForeColor = System.Drawing.Color.White;
            this.label_dev_status.Location = new System.Drawing.Point(88, 47);
            this.label_dev_status.Name = "label_dev_status";
            this.label_dev_status.Size = new System.Drawing.Size(79, 20);
            this.label_dev_status.TabIndex = 11;
            this.label_dev_status.Text = "设备未连接";
            // 
            // label_Form_Name
            // 
            this.label_Form_Name.AutoSize = true;
            this.label_Form_Name.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_Form_Name.ForeColor = System.Drawing.Color.White;
            this.label_Form_Name.Location = new System.Drawing.Point(70, 19);
            this.label_Form_Name.Name = "label_Form_Name";
            this.label_Form_Name.Size = new System.Drawing.Size(130, 19);
            this.label_Form_Name.TabIndex = 16;
            this.label_Form_Name.Text = "GeekIMU管理中心";
            // 
            // MainPanel
            // 
            this.MainPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.MainPanel.Location = new System.Drawing.Point(0, 91);
            this.MainPanel.Name = "MainPanel";
            this.MainPanel.Size = new System.Drawing.Size(1027, 554);
            this.MainPanel.TabIndex = 17;
            // 
            // Btn_my_dev
            // 
            this.Btn_my_dev.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Btn_my_dev.FlatAppearance.BorderSize = 0;
            this.Btn_my_dev.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Btn_my_dev.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Btn_my_dev.ForeColor = System.Drawing.Color.White;
            this.Btn_my_dev.Image = global::DM_CalibrationTools.Properties.Resources.home_48px;
            this.Btn_my_dev.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.Btn_my_dev.Location = new System.Drawing.Point(209, 1);
            this.Btn_my_dev.Name = "Btn_my_dev";
            this.Btn_my_dev.Size = new System.Drawing.Size(77, 87);
            this.Btn_my_dev.TabIndex = 22;
            this.Btn_my_dev.Text = "我的传感器";
            this.Btn_my_dev.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.Btn_my_dev.UseVisualStyleBackColor = true;
            // 
            // Btn_support
            // 
            this.Btn_support.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Btn_support.FlatAppearance.BorderSize = 0;
            this.Btn_support.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Btn_support.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Btn_support.ForeColor = System.Drawing.Color.White;
            this.Btn_support.Image = global::DM_CalibrationTools.Properties.Resources.help_48px;
            this.Btn_support.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.Btn_support.Location = new System.Drawing.Point(441, 1);
            this.Btn_support.Name = "Btn_support";
            this.Btn_support.Size = new System.Drawing.Size(77, 87);
            this.Btn_support.TabIndex = 21;
            this.Btn_support.Text = "帮助与支持";
            this.Btn_support.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.Btn_support.UseVisualStyleBackColor = true;
            this.Btn_support.Click += new System.EventHandler(this.Btn_support_Click);
            // 
            // Btn_software_Setting
            // 
            this.Btn_software_Setting.FlatAppearance.BorderSize = 0;
            this.Btn_software_Setting.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Btn_software_Setting.Image = global::DM_CalibrationTools.Properties.Resources.btn_setting_18px_1;
            this.Btn_software_Setting.Location = new System.Drawing.Point(933, 3);
            this.Btn_software_Setting.Name = "Btn_software_Setting";
            this.Btn_software_Setting.Size = new System.Drawing.Size(18, 18);
            this.Btn_software_Setting.TabIndex = 20;
            this.Btn_software_Setting.UseVisualStyleBackColor = true;
            // 
            // Btn_min
            // 
            this.Btn_min.FlatAppearance.BorderSize = 0;
            this.Btn_min.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Btn_min.Image = global::DM_CalibrationTools.Properties.Resources.btn_mini_18px_1;
            this.Btn_min.Location = new System.Drawing.Point(978, 3);
            this.Btn_min.Name = "Btn_min";
            this.Btn_min.Size = new System.Drawing.Size(18, 18);
            this.Btn_min.TabIndex = 19;
            this.Btn_min.UseVisualStyleBackColor = true;
            this.Btn_min.Click += new System.EventHandler(this.Btn_min_Click);
            // 
            // Btn_dev_Setting
            // 
            this.Btn_dev_Setting.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Btn_dev_Setting.FlatAppearance.BorderSize = 0;
            this.Btn_dev_Setting.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Btn_dev_Setting.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Btn_dev_Setting.ForeColor = System.Drawing.Color.White;
            this.Btn_dev_Setting.Image = global::DM_CalibrationTools.Properties.Resources.settings_48px;
            this.Btn_dev_Setting.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.Btn_dev_Setting.Location = new System.Drawing.Point(285, 1);
            this.Btn_dev_Setting.Name = "Btn_dev_Setting";
            this.Btn_dev_Setting.Size = new System.Drawing.Size(77, 87);
            this.Btn_dev_Setting.TabIndex = 18;
            this.Btn_dev_Setting.Text = "设备设置";
            this.Btn_dev_Setting.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.Btn_dev_Setting.UseVisualStyleBackColor = true;
            // 
            // Btn_DFU_DownLoad
            // 
            this.Btn_DFU_DownLoad.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Btn_DFU_DownLoad.FlatAppearance.BorderSize = 0;
            this.Btn_DFU_DownLoad.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Btn_DFU_DownLoad.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Btn_DFU_DownLoad.ForeColor = System.Drawing.Color.White;
            this.Btn_DFU_DownLoad.Image = global::DM_CalibrationTools.Properties.Resources.download_48px;
            this.Btn_DFU_DownLoad.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.Btn_DFU_DownLoad.Location = new System.Drawing.Point(359, 1);
            this.Btn_DFU_DownLoad.Name = "Btn_DFU_DownLoad";
            this.Btn_DFU_DownLoad.Size = new System.Drawing.Size(77, 87);
            this.Btn_DFU_DownLoad.TabIndex = 17;
            this.Btn_DFU_DownLoad.Text = "固件升级";
            this.Btn_DFU_DownLoad.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.Btn_DFU_DownLoad.UseVisualStyleBackColor = true;
            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = global::DM_CalibrationTools.Properties.Resources.tools;
            this.pictureBox2.Location = new System.Drawing.Point(6, 13);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(60, 60);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox2.TabIndex = 15;
            this.pictureBox2.TabStop = false;
            // 
            // pictureBox3
            // 
            this.pictureBox3.Image = global::DM_CalibrationTools.Properties.Resources.test;
            this.pictureBox3.Location = new System.Drawing.Point(75, 47);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(12, 21);
            this.pictureBox3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox3.TabIndex = 17;
            this.pictureBox3.TabStop = false;
            // 
            // Btn_Close
            // 
            this.Btn_Close.FlatAppearance.BorderSize = 0;
            this.Btn_Close.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Btn_Close.Image = global::DM_CalibrationTools.Properties.Resources.btn_close_18px_1;
            this.Btn_Close.Location = new System.Drawing.Point(1002, 3);
            this.Btn_Close.Name = "Btn_Close";
            this.Btn_Close.Size = new System.Drawing.Size(18, 18);
            this.Btn_Close.TabIndex = 14;
            this.Btn_Close.UseVisualStyleBackColor = true;
            this.Btn_Close.Click += new System.EventHandler(this.Btn_Close_Click);
            // 
            // MainForms
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1027, 645);
            this.Controls.Add(this.MainPanel);
            this.Controls.Add(this.Control_Panel);
            this.CornerRadius = 1;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainForms";
            this.ShadowStyle = CCWin.RoundStyle.None;
            this.Text = "MainForms";
            this.Control_Panel.ResumeLayout(false);
            this.Control_Panel.PerformLayout();
            this.Panel_logo.ResumeLayout(false);
            this.Panel_logo.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel Control_Panel;
        private System.Windows.Forms.Button Btn_my_dev;
        private System.Windows.Forms.Button Btn_support;
        private System.Windows.Forms.Button Btn_software_Setting;
        private System.Windows.Forms.Label label_line;
        private System.Windows.Forms.Button Btn_min;
        private System.Windows.Forms.Button Btn_dev_Setting;
        private System.Windows.Forms.Button Btn_DFU_DownLoad;
        private System.Windows.Forms.Panel Panel_logo;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.Label label_dev_status;
        private System.Windows.Forms.Label label_Form_Name;
        private System.Windows.Forms.Button Btn_Close;
        private System.Windows.Forms.Panel MainPanel;


    }
}