namespace DM_CalibrationTools
{
    partial class IMUInformation
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(IMUInformation));
            this.Gbox_OpenGL = new System.Windows.Forms.GroupBox();
            this.GLpanel = new System.Windows.Forms.Panel();
            this.openGLControl1 = new SharpGL.OpenGLControl();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.Panel_Bottom = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.linkLabel1 = new System.Windows.Forms.LinkLabel();
            this.BtnShowAngle = new System.Windows.Forms.Button();
            this.btnLoadorCali = new System.Windows.Forms.Button();
            this.btnResetCalibrationData = new System.Windows.Forms.Button();
            this.btnCalliGyro = new System.Windows.Forms.Button();
            this.Panel_Sensor_Information = new System.Windows.Forms.Panel();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btnMagCalibtation = new System.Windows.Forms.Button();
            this.label_dev_name = new System.Windows.Forms.Label();
            this.labelAngle = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.labelMagOffset = new System.Windows.Forms.Label();
            this.labelGyroOffset = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.bindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            this.Gbox_OpenGL.SuspendLayout();
            this.GLpanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.openGLControl1)).BeginInit();
            this.Panel_Bottom.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.Panel_Sensor_Information.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).BeginInit();
            this.SuspendLayout();
            // 
            // Gbox_OpenGL
            // 
            this.Gbox_OpenGL.Controls.Add(this.GLpanel);
            this.Gbox_OpenGL.Location = new System.Drawing.Point(7, 6);
            this.Gbox_OpenGL.Name = "Gbox_OpenGL";
            this.Gbox_OpenGL.Size = new System.Drawing.Size(698, 499);
            this.Gbox_OpenGL.TabIndex = 7;
            this.Gbox_OpenGL.TabStop = false;
            this.Gbox_OpenGL.Text = "3D显示";
            // 
            // GLpanel
            // 
            this.GLpanel.Controls.Add(this.openGLControl1);
            this.GLpanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GLpanel.Location = new System.Drawing.Point(3, 17);
            this.GLpanel.Name = "GLpanel";
            this.GLpanel.Size = new System.Drawing.Size(692, 479);
            this.GLpanel.TabIndex = 10;
            this.GLpanel.MouseEnter += new System.EventHandler(this.GLpanel_MouseEnter);
            this.GLpanel.MouseLeave += new System.EventHandler(this.GLpanel_MouseLeave);
            // 
            // openGLControl1
            // 
            this.openGLControl1.BitDepth = 24;
            this.openGLControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.openGLControl1.DrawFPS = true;
            this.openGLControl1.FrameRate = 20;
            this.openGLControl1.Location = new System.Drawing.Point(0, 0);
            this.openGLControl1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.openGLControl1.Name = "openGLControl1";
            this.openGLControl1.RenderContextType = SharpGL.RenderContextType.NativeWindow;
            this.openGLControl1.Size = new System.Drawing.Size(692, 479);
            this.openGLControl1.TabIndex = 0;
            this.openGLControl1.OpenGLDraw += new System.Windows.Forms.PaintEventHandler(this.sceneControl1_OpenGLDraw);
            this.openGLControl1.Resized += new System.EventHandler(this.sceneControl1_Resized);
            this.openGLControl1.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.sceneControl1_MouseDoubleClick);
            this.openGLControl1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.sceneControl1_MouseDown);
            this.openGLControl1.MouseEnter += new System.EventHandler(this.GLpanel_MouseEnter);
            this.openGLControl1.MouseLeave += new System.EventHandler(this.GLpanel_MouseLeave);
            this.openGLControl1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.sceneControl1_MouseMove);
            this.openGLControl1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.sceneControl1_MouseUp);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 50;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Panel_Bottom
            // 
            this.Panel_Bottom.Controls.Add(this.button1);
            this.Panel_Bottom.Controls.Add(this.pictureBox1);
            this.Panel_Bottom.Controls.Add(this.linkLabel1);
            this.Panel_Bottom.Controls.Add(this.BtnShowAngle);
            this.Panel_Bottom.Controls.Add(this.btnLoadorCali);
            this.Panel_Bottom.Controls.Add(this.btnResetCalibrationData);
            this.Panel_Bottom.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.Panel_Bottom.Location = new System.Drawing.Point(0, 506);
            this.Panel_Bottom.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Panel_Bottom.Name = "Panel_Bottom";
            this.Panel_Bottom.Size = new System.Drawing.Size(1027, 51);
            this.Panel_Bottom.TabIndex = 12;
            // 
            // button1
            // 
            this.button1.BackgroundImage = global::DM_CalibrationTools.Properties.Resources._3d_32px;
            this.button1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.button1.FlatAppearance.BorderSize = 0;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.button1.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.button1.Location = new System.Drawing.Point(13, 7);
            this.button1.Margin = new System.Windows.Forms.Padding(0, 2, 2, 2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(119, 32);
            this.button1.TabIndex = 19;
            this.button1.Text = "3D场景显示";
            this.button1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.button1.UseVisualStyleBackColor = true;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::DM_CalibrationTools.Properties.Resources.link_48px;
            this.pictureBox1.Location = new System.Drawing.Point(866, 7);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(32, 32);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 13;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Click += new System.EventHandler(this.pictureBox1_Click);
            // 
            // linkLabel1
            // 
            this.linkLabel1.AutoSize = true;
            this.linkLabel1.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.linkLabel1.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.linkLabel1.LinkColor = System.Drawing.Color.Black;
            this.linkLabel1.Location = new System.Drawing.Point(899, 12);
            this.linkLabel1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.linkLabel1.Name = "linkLabel1";
            this.linkLabel1.Size = new System.Drawing.Size(122, 21);
            this.linkLabel1.TabIndex = 12;
            this.linkLabel1.TabStop = true;
            this.linkLabel1.Text = "电科神技淘宝店";
            this.linkLabel1.VisitedLinkColor = System.Drawing.Color.Aqua;
            this.linkLabel1.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
            // 
            // BtnShowAngle
            // 
            this.BtnShowAngle.BackgroundImage = global::DM_CalibrationTools.Properties.Resources.pose_32px;
            this.BtnShowAngle.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.BtnShowAngle.FlatAppearance.BorderSize = 0;
            this.BtnShowAngle.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.BtnShowAngle.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.BtnShowAngle.Location = new System.Drawing.Point(136, 7);
            this.BtnShowAngle.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.BtnShowAngle.Name = "BtnShowAngle";
            this.BtnShowAngle.Size = new System.Drawing.Size(102, 32);
            this.BtnShowAngle.TabIndex = 10;
            this.BtnShowAngle.Text = "航向对准";
            this.BtnShowAngle.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.BtnShowAngle.UseVisualStyleBackColor = true;
            this.BtnShowAngle.Click += new System.EventHandler(this.BtnShowAngle_Click);
            // 
            // btnLoadorCali
            // 
            this.btnLoadorCali.BackgroundImage = global::DM_CalibrationTools.Properties.Resources.earth_grid_32px;
            this.btnLoadorCali.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.btnLoadorCali.FlatAppearance.BorderSize = 0;
            this.btnLoadorCali.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnLoadorCali.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.btnLoadorCali.Location = new System.Drawing.Point(245, 7);
            this.btnLoadorCali.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.btnLoadorCali.Name = "btnLoadorCali";
            this.btnLoadorCali.Size = new System.Drawing.Size(128, 32);
            this.btnLoadorCali.TabIndex = 10;
            this.btnLoadorCali.Text = "加载磁力数据";
            this.btnLoadorCali.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnLoadorCali.UseVisualStyleBackColor = false;
            this.btnLoadorCali.Click += new System.EventHandler(this.button4_Click);
            // 
            // btnResetCalibrationData
            // 
            this.btnResetCalibrationData.BackgroundImage = global::DM_CalibrationTools.Properties.Resources.refresh_32px;
            this.btnResetCalibrationData.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.btnResetCalibrationData.FlatAppearance.BorderSize = 0;
            this.btnResetCalibrationData.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnResetCalibrationData.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.btnResetCalibrationData.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnResetCalibrationData.Location = new System.Drawing.Point(376, 7);
            this.btnResetCalibrationData.Margin = new System.Windows.Forms.Padding(0, 2, 2, 2);
            this.btnResetCalibrationData.Name = "btnResetCalibrationData";
            this.btnResetCalibrationData.Size = new System.Drawing.Size(127, 32);
            this.btnResetCalibrationData.TabIndex = 9;
            this.btnResetCalibrationData.Text = "重置校准数据";
            this.btnResetCalibrationData.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnResetCalibrationData.UseVisualStyleBackColor = true;
            this.btnResetCalibrationData.Click += new System.EventHandler(this.button2_Click);
            // 
            // btnCalliGyro
            // 
            this.btnCalliGyro.BackgroundImage = global::DM_CalibrationTools.Properties.Resources.refresh_32px1;
            this.btnCalliGyro.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.btnCalliGyro.FlatAppearance.BorderSize = 0;
            this.btnCalliGyro.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnCalliGyro.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.btnCalliGyro.Location = new System.Drawing.Point(19, 430);
            this.btnCalliGyro.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.btnCalliGyro.Name = "btnCalliGyro";
            this.btnCalliGyro.Size = new System.Drawing.Size(117, 32);
            this.btnCalliGyro.TabIndex = 10;
            this.btnCalliGyro.Text = "校准陀螺仪";
            this.btnCalliGyro.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnCalliGyro.UseVisualStyleBackColor = true;
            this.btnCalliGyro.Click += new System.EventHandler(this.button6_Click);
            // 
            // Panel_Sensor_Information
            // 
            this.Panel_Sensor_Information.BackColor = System.Drawing.Color.White;
            this.Panel_Sensor_Information.Controls.Add(this.label9);
            this.Panel_Sensor_Information.Controls.Add(this.label8);
            this.Panel_Sensor_Information.Controls.Add(this.label7);
            this.Panel_Sensor_Information.Controls.Add(this.label6);
            this.Panel_Sensor_Information.Controls.Add(this.label5);
            this.Panel_Sensor_Information.Controls.Add(this.label2);
            this.Panel_Sensor_Information.Controls.Add(this.btnMagCalibtation);
            this.Panel_Sensor_Information.Controls.Add(this.label_dev_name);
            this.Panel_Sensor_Information.Controls.Add(this.btnCalliGyro);
            this.Panel_Sensor_Information.Controls.Add(this.labelAngle);
            this.Panel_Sensor_Information.Controls.Add(this.label4);
            this.Panel_Sensor_Information.Controls.Add(this.label3);
            this.Panel_Sensor_Information.Controls.Add(this.labelMagOffset);
            this.Panel_Sensor_Information.Controls.Add(this.labelGyroOffset);
            this.Panel_Sensor_Information.Controls.Add(this.label1);
            this.Panel_Sensor_Information.Location = new System.Drawing.Point(710, 13);
            this.Panel_Sensor_Information.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Panel_Sensor_Information.Name = "Panel_Sensor_Information";
            this.Panel_Sensor_Information.Size = new System.Drawing.Size(306, 491);
            this.Panel_Sensor_Information.TabIndex = 13;
            this.Panel_Sensor_Information.Paint += new System.Windows.Forms.PaintEventHandler(this.panel2_Paint);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.BackColor = System.Drawing.Color.Transparent;
            this.label9.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.label9.Location = new System.Drawing.Point(15, 128);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(121, 20);
            this.label9.TabIndex = 18;
            this.label9.Text = "无线传输：不支持";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.BackColor = System.Drawing.Color.Transparent;
            this.label8.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label8.ForeColor = System.Drawing.Color.Red;
            this.label8.Location = new System.Drawing.Point(245, 103);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(44, 17);
            this.label8.TabIndex = 17;
            this.label8.Text = "未校准";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.BackColor = System.Drawing.Color.Transparent;
            this.label7.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label7.ForeColor = System.Drawing.Color.Red;
            this.label7.Location = new System.Drawing.Point(245, 75);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(44, 17);
            this.label7.TabIndex = 16;
            this.label7.Text = "未校准";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.BackColor = System.Drawing.Color.Transparent;
            this.label6.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.label6.Location = new System.Drawing.Point(16, 101);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(105, 20);
            this.label6.TabIndex = 15;
            this.label6.Text = "磁力计：   支持";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.BackColor = System.Drawing.Color.Transparent;
            this.label5.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.label5.Location = new System.Drawing.Point(16, 73);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(105, 20);
            this.label5.TabIndex = 14;
            this.label5.Text = "陀螺仪：   支持";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.label2.Location = new System.Drawing.Point(16, 45);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(107, 20);
            this.label2.TabIndex = 13;
            this.label2.Text = "加速度计：支持";
            // 
            // btnMagCalibtation
            // 
            this.btnMagCalibtation.BackgroundImage = global::DM_CalibrationTools.Properties.Resources.refresh_32px1;
            this.btnMagCalibtation.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.btnMagCalibtation.FlatAppearance.BorderSize = 0;
            this.btnMagCalibtation.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnMagCalibtation.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.btnMagCalibtation.Location = new System.Drawing.Point(156, 430);
            this.btnMagCalibtation.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.btnMagCalibtation.Name = "btnMagCalibtation";
            this.btnMagCalibtation.Size = new System.Drawing.Size(115, 32);
            this.btnMagCalibtation.TabIndex = 10;
            this.btnMagCalibtation.Text = "校准磁力计";
            this.btnMagCalibtation.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnMagCalibtation.UseVisualStyleBackColor = true;
            this.btnMagCalibtation.Click += new System.EventHandler(this.button3_Click);
            // 
            // label_dev_name
            // 
            this.label_dev_name.AutoSize = true;
            this.label_dev_name.BackColor = System.Drawing.Color.Transparent;
            this.label_dev_name.Font = new System.Drawing.Font("微软雅黑", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_dev_name.Location = new System.Drawing.Point(16, 11);
            this.label_dev_name.Name = "label_dev_name";
            this.label_dev_name.Size = new System.Drawing.Size(234, 19);
            this.label_dev_name.TabIndex = 12;
            this.label_dev_name.Text = "设备名称：GeekIMU有线版 v1.0";
            // 
            // labelAngle
            // 
            this.labelAngle.AutoSize = true;
            this.labelAngle.BackColor = System.Drawing.Color.Transparent;
            this.labelAngle.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.labelAngle.Location = new System.Drawing.Point(16, 184);
            this.labelAngle.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelAngle.Name = "labelAngle";
            this.labelAngle.Size = new System.Drawing.Size(27, 20);
            this.labelAngle.TabIndex = 11;
            this.labelAngle.Text = "---";
            this.labelAngle.Click += new System.EventHandler(this.labelAngle_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.BackColor = System.Drawing.Color.Transparent;
            this.label4.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(16, 157);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(52, 19);
            this.label4.TabIndex = 1;
            this.label4.Text = "欧拉角:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.Transparent;
            this.label3.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(16, 267);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(87, 19);
            this.label3.TabIndex = 1;
            this.label3.Text = "磁力计校准值";
            // 
            // labelMagOffset
            // 
            this.labelMagOffset.AutoSize = true;
            this.labelMagOffset.BackColor = System.Drawing.Color.Transparent;
            this.labelMagOffset.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.labelMagOffset.Location = new System.Drawing.Point(16, 295);
            this.labelMagOffset.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelMagOffset.Name = "labelMagOffset";
            this.labelMagOffset.Size = new System.Drawing.Size(27, 20);
            this.labelMagOffset.TabIndex = 0;
            this.labelMagOffset.Text = "---";
            // 
            // labelGyroOffset
            // 
            this.labelGyroOffset.AutoSize = true;
            this.labelGyroOffset.BackColor = System.Drawing.Color.Transparent;
            this.labelGyroOffset.Font = new System.Drawing.Font("微软雅黑", 10F);
            this.labelGyroOffset.Location = new System.Drawing.Point(16, 239);
            this.labelGyroOffset.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelGyroOffset.Name = "labelGyroOffset";
            this.labelGyroOffset.Size = new System.Drawing.Size(27, 20);
            this.labelGyroOffset.TabIndex = 0;
            this.labelGyroOffset.Text = "---";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(16, 214);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(91, 19);
            this.label1.TabIndex = 0;
            this.label1.Text = "陀螺仪校准值:";
            // 
            // IMUInformation
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(1027, 557);
            this.Controls.Add(this.Panel_Sensor_Information);
            this.Controls.Add(this.Panel_Bottom);
            this.Controls.Add(this.Gbox_OpenGL);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Name = "IMUInformation";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Resize += new System.EventHandler(this.Form1_Resize);
            this.Gbox_OpenGL.ResumeLayout(false);
            this.GLpanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.openGLControl1)).EndInit();
            this.Panel_Bottom.ResumeLayout(false);
            this.Panel_Bottom.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.Panel_Sensor_Information.ResumeLayout(false);
            this.Panel_Sensor_Information.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox Gbox_OpenGL;
        private System.Windows.Forms.Panel GLpanel;
        private System.Windows.Forms.Button btnResetCalibrationData;
        private System.Windows.Forms.Button btnMagCalibtation;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button btnLoadorCali;
        private System.Windows.Forms.Panel Panel_Bottom;
        private System.Windows.Forms.Button btnCalliGyro;
        private System.Windows.Forms.LinkLabel linkLabel1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Panel Panel_Sensor_Information;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label labelMagOffset;
        private System.Windows.Forms.Label labelGyroOffset;
        private System.Windows.Forms.Button BtnShowAngle;
        private System.Windows.Forms.Label labelAngle;
        private System.Windows.Forms.Label label4;
        private SharpGL.OpenGLControl openGLControl1;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.BindingSource bindingSource1;
        private System.Windows.Forms.Label label_dev_name;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button button1;

    }
}

