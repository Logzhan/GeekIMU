namespace DM_CalibrationTools
{
    partial class IMUConnect
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
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.Btn_not_recognition = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(68)))), ((int)(((byte)(68)))), ((int)(((byte)(68)))));
            this.label2.Location = new System.Drawing.Point(227, 437);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(544, 28);
            this.label2.TabIndex = 2;
            this.label2.Text = "请用USB连接IMU设备或者采用无线接收器连接IMU设备";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(379, 523);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(263, 17);
            this.label1.TabIndex = 4;
            this.label1.Text = "使用中遇到问题请加入技术支持群：115438931";
            // 
            // Btn_not_recognition
            // 
            this.Btn_not_recognition.BackgroundImage = global::DM_CalibrationTools.Properties.Resources.question_32px;
            this.Btn_not_recognition.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.Btn_not_recognition.FlatAppearance.BorderSize = 0;
            this.Btn_not_recognition.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Btn_not_recognition.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Btn_not_recognition.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(30)))), ((int)(((byte)(120)))), ((int)(((byte)(213)))));
            this.Btn_not_recognition.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.Btn_not_recognition.Location = new System.Drawing.Point(785, 436);
            this.Btn_not_recognition.Name = "Btn_not_recognition";
            this.Btn_not_recognition.Size = new System.Drawing.Size(198, 32);
            this.Btn_not_recognition.TabIndex = 3;
            this.Btn_not_recognition.Text = "已经连接，但无法识别？";
            this.Btn_not_recognition.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.Btn_not_recognition.UseVisualStyleBackColor = true;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::DM_CalibrationTools.Properties.Resources.usb_783px;
            this.pictureBox1.Location = new System.Drawing.Point(332, 44);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(349, 359);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // IMUConnect
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(1027, 557);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Btn_not_recognition);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.pictureBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "IMUConnect";
            this.Text = "IMUConnect";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button Btn_not_recognition;
        private System.Windows.Forms.Label label1;
    }
}