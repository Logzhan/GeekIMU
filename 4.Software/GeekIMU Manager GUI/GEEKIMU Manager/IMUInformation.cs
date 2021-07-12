using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SharpGL;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.Diagnostics;
using System.Threading;
using  CCWin;
namespace DM_CalibrationTools
{
//     struct mVector3
//     {
//         public float x, y, z;
//     };
    public partial class IMUInformation : Form
    {
        Boolean global_IsCali=false;
        HashSet<double[]> magcalidata = new HashSet<double[]>();

        private Point mPoint;

        bool isGetCalibrateData = false;

        public IMUInformation()
        {
            InitializeComponent();
        }

        csgl gl;
        private void Form1_Load(object sender, EventArgs e)
        {
            Debug.WriteLine(CaliAPI.InitCaliAPI("VID_2833&PID_0002"));
            this.Text = "GeekIMU管理软件";
            gl = new csgl(openGLControl1);
            this.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.GLpanel_MouseWheel);

            // 默认状态为隐藏
            //Gbox_OpenGL.Hide();
            //Panel_Sensor_Information.Hide();
            //Panel_Bottom.Hide();

            DrawIMUInformationGrid(0, 0);
        }

        private void GLpanel_MouseWheel(object sender, MouseEventArgs e)
        {
            if (gl.Global_MouseInGLPanel)
                gl.zoomCameraDelta(e.Delta / 60);
        }

        private void GLpanel_MouseEnter(object sender, EventArgs e)
        {
            gl.Global_MouseInGLPanel = true;
        }

        private void GLpanel_MouseLeave(object sender, EventArgs e)
        {
            gl.Global_MouseInGLPanel = false;
        }

        private void sceneControl1_OpenGLDraw(object sender, PaintEventArgs e)
        {
            gl.Draw();
        }

        private void sceneControl1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Middle)
            {
                gl.resetView();
            }
            
        }

        private void sceneControl1_MouseDown(object sender, MouseEventArgs e)
        {
            gl.Global_MouseDown = true;
            gl.setMousePos(e.X, e.Y);
        }

        private void sceneControl1_MouseMove(object sender, MouseEventArgs e)
        {if(gl!=null)
            if (gl.Global_MouseDown)
            { 
                if (e.Button == MouseButtons.Left && Control.ModifierKeys == Keys.Control)
                {
                    gl.moveCameraXY(e.X, e.Y);
                }
                else if (e.Button == MouseButtons.Right && Control.ModifierKeys == Keys.Control)
                {
                    gl.moveCameraZ(e.X, e.Y);
                }
                else if (e.Button == MouseButtons.Left)
                {
                    gl.rotateCamera(e.X, e.Y);
                }
                else if (e.Button == MouseButtons.Right)
                {
                    gl.zoomCamera(e.Y);
                }
               
            }
        }

        private void sceneControl1_MouseUp(object sender, MouseEventArgs e)
        {
            gl.Global_MouseDown = false;
            gl.setMousePos(e.X, e.Y);
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
        }

        private void sceneControl1_Resized(object sender, EventArgs e)
        {if(gl!=null)
            gl.resize();
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            this.Invoke(new EventHandler(delegate
            {
                if(global_IsCali)
                {
                    if (magcalidata.Count <= 4000) 
                    {
                        mVector3 v3f = CaliAPI.GetPoint();
                        double[] v3d = { v3f.x, v3f.y, v3f.z };
                        if (v3d[0] != -99999.0 || v3d[1] != -99999.0 || v3d[2] != -99999.0)
                        magcalidata.Add(v3d);
                        gl.setPointarr(magcalidata);
                    }
                    else
                    {
                        global_IsCali = false;
                        timer1.Interval = 100;
                        Debug.WriteLine("auto stop:" + CaliAPI.FinishMagCali());
                    }     
                }
                if (global_IsCali)
                {
                    btnLoadorCali.Enabled = false;
                }
                else
                {
                    btnLoadorCali.Enabled = true;
                }
                if (CaliAPI.CheckDevice() == 1)
                {
                    btnCalliGyro.Enabled = true;
                    btnResetCalibrationData.Enabled = true;
                    btnMagCalibtation.Enabled = true;
                    mVector3 v = CaliAPI.GetEulerianAngle();
                    if (v.x != -99999.0 || v.y != -99999.0 || v.z != -99999.0)
                    {
                        v.z += v.z > 0 ? -90 : 90;
                        v.y += 180;
                        v.y = v.y > 180 ? v.y - 360 : v.y;

                        labelAngle.Text = "Pitch : " + v.z.ToString("+#.#;-#.#;0") + "° " +
                                          " Roll : " + v.y.ToString("+#.#;-#.#;0") + "° " +
                                          " Yaw : " + v.x.ToString("+#.#;-#.#;0") + "°"; 
                    }

                    if (isGetCalibrateData == false) {
                        MagCaliParam p = CaliAPI.GetMagCali();
                        mVector3     g = CaliAPI.GetGyroCali();

                        labelMagOffset.Text = p.xOffset + " " + p.xScale + "\n" + p.yOffset + " " + p.yScale + "\n" + p.yOffset + " " + p.zScale;
                        labelGyroOffset.Text = g.x + " " + g.y + " " + g.z;

                        isGetCalibrateData = true;
                    }
                }
                else
                {
                    btnCalliGyro.Enabled = false;
                    btnResetCalibrationData.Enabled = false;
                    btnMagCalibtation.Enabled = false;
                }

            }));
        }

        private void button3_Click(object sender, EventArgs e)
        {
            gl.DrawFlag = 1;
            if (btnMagCalibtation.Text.Equals("开始校准磁力计"))
            {
                this.Invoke(new EventHandler(delegate
                    {
                        magcalidata.Clear();
                        CaliAPI.MagCali();
                        global_IsCali = true;
                        timer1.Interval = 5;
                    }));
                btnMagCalibtation.Text = "结束校准磁力计";
            }
            else
            {
                global_IsCali = false;
                timer1.Interval = 50;
                CaliAPI.FinishMagCali();
                txtreader.saveData(magcalidata);
                MagCaliParam p = CaliAPI.CalculateMagParam();
                //Debug.WriteLine(p.xOffset + "," + p.yOffset + "," + p.zOffset + "," + p.xScale + "," + p.yScale + "," + p.zScale);
                labelMagOffset.Text = p.xOffset + " " + p.xScale + "\n" + p.yOffset + " " + p.yScale + "\n" + p.yOffset + " " + p.zScale;
                CaliAPI.SetMagCali(p.xOffset, p.yOffset, p.zOffset, p.xScale, p.yScale, p.zScale);
                pointstage = 0;
                button4_Click(sender, e);
                btnMagCalibtation.Text = "开始校准磁力计";
            }


        }

        private void button2_Click(object sender, EventArgs e)
        {
            if(MessageBox.Show("该操作不可逆，是否继续？","重置校准数据",MessageBoxButtons.OKCancel,MessageBoxIcon.Question,MessageBoxDefaultButton.Button2)==DialogResult.OK)
            {
                if (CaliAPI.SetMagCali(0, 0, 0, 1, 1, 1) == 1) {
                    isGetCalibrateData = false;
                }
                
            }
                
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MagCaliParam p = CaliAPI.GetMagCali();
            mVector3 g = CaliAPI.GetGyroCali();
           
            labelMagOffset.Text = p.xOffset + " " + p.xScale + "\n" + p.yOffset + " " + p.yScale + "\n" + p.yOffset +" "+ p.zScale ;
            labelGyroOffset.Text = g.x + " " + g.y + " "+g.z;

        }
        static int pointstage = 0;
        txtreader global_tr = null;
        HashSet<double[]> hs;
        private void button4_Click(object sender, EventArgs e)
        {
            gl.DrawFlag = 1;
            //mVector3 v3 = CaliAPI.GetPoint();
            //Debug.WriteLine(v3.x+" "+v3.y+" "+v3.z+" ");
            
            if ((global_tr == null) || (pointstage == 0))
            {
                btnLoadorCali.Text = "绘制校准数据";
                global_tr = new txtreader("data");
                global_tr.GetData();
                pointstage=1;
                hs = global_tr.getHashset();
            }
            else if(pointstage == 1 )
            {
                btnLoadorCali.Text = "加载原始数据";
                HashSet<double[]> hs1 = new HashSet<double[]>();
                if(hs.Count >100)                
                {
                    MagCaliParam mcp= CaliAPI.CalculateMagParam();
                                   
                    foreach (var d in hs)
                    {
                        double[] v = { (d[0] - mcp.xOffset) * mcp.xScale, (d[1] - mcp.yOffset) * mcp.yScale, (d[2] - mcp.zOffset) * mcp.zScale };
                        hs1.Add(v);
                    }
                    hs = hs1;
                }
                else
                {
                    MessageBox.Show("数据太少，无法计算校准参数！");
                }
                pointstage = 0;
            }

            gl.setPointarr(hs);

        }

        private void DrawIMUInformationGrid(int cols, int rows)
        {

            Bitmap b = new Bitmap(Panel_Sensor_Information.Width, Panel_Sensor_Information.Height);
            Graphics g = Graphics.FromImage(b);
            Rectangle rect = new Rectangle(5, 
                                           0, 
                                           Panel_Sensor_Information.Width - 10, 360);
            g.DrawRectangle(new Pen(Color.FromArgb(228, 228, 228), 1), rect);

            g.FillRectangle(new SolidBrush(Color.FromArgb(249, 249, 249)), 
                                           new Rectangle(new Point(6, 1), 
                                           new Size(Panel_Sensor_Information.Width - 11, 40)));

            int padding    = 28;
            int stLocation = 68;
            for (int i = 0; i < 4; i++) {
                g.FillRectangle(new SolidBrush(Color.FromArgb(249, 249, 249)),
                                   new Rectangle(new Point(6, 1 + i * padding * 2 + stLocation),
                                   new Size(Panel_Sensor_Information.Width - 11, padding)));
            }
            
            g.Dispose();

            Panel_Sensor_Information.Show();
            Panel_Sensor_Information.BackgroundImage = b; 

  
        }
        // 获取传感器的状态
        public bool GetIMUStatus()
        {
            if (CaliAPI.CheckDevice() == 1) {
                return true;
            }
            return false;
        }
        private void button5_Click(object sender, EventArgs e)
        {
            global_IsCali = false;
            timer1.Interval = 100;
            Debug.WriteLine(CaliAPI.FinishMagCali());
            txtreader.saveData(magcalidata);
            MagCaliParam p = CaliAPI.CalculateMagParam();
            Debug.WriteLine(p.xOffset + "," + p.yOffset + "," + p.zOffset + "," + p.xScale + "," + p.yScale + "," + p.zScale);
            Debug.WriteLine(CaliAPI.SetMagCali(p.xOffset, p.yOffset, p.zOffset, p.xScale, p.yScale, p.zScale));
            pointstage = 0;
            button4_Click(sender, e);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            DialogResult dr = MessageBox.Show("校准过程约2秒，请保持设备静置，单击确定开始。", "陀螺仪校准", MessageBoxButtons.OKCancel, MessageBoxIcon.Information, MessageBoxDefaultButton.Button2);
            if (dr != DialogResult.OK && CaliAPI.CheckDevice() == 1)
            {
                return;
            }
            else
            {
                int result = CaliAPI.GyroCali();
                Thread.Sleep(1000);
                if (result == 1)
                {
                    MessageBox.Show("校准成功!");
                    mVector3 g = CaliAPI.GetGyroCali();
                    labelGyroOffset.Text = g.x + "  " + g.y + "  " + g.z + "\n";
                }
                else
                    MessageBox.Show("校准失败!");
            }
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("https://shop408976235.taobao.com/");
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("https://shop408976235.taobao.com/");
        }

        private void BtnShowAngle_Click(object sender, EventArgs e)
        {
            gl.DrawFlag = 2;
            CaliAPI.Correction();
        }

        private void BtnHelp_Click(object sender, EventArgs e)
        {

            System.Diagnostics.Process.Start(Application.StartupPath+"/DM上位机校准软件说明.pdf");
        }

        private void sceneControl1_OpenGLDraw(object sender)
        {
        }

        private void sceneControl1_OpenGLInitialized(object sender, EventArgs e)
        {
            OpenGL gl = openGLControl1.OpenGL;
            gl.ClearColor(0, 0, 0, 0);
        }

        private void Btn_Close_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Control_Panel_MouseDown(object sender, MouseEventArgs e)
        {
            mPoint = new Point(e.X, e.Y);
        }

        private void Control_Panel_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                this.Location = new Point(this.Location.X + e.X - mPoint.X, this.Location.Y + e.Y - mPoint.Y);
            }
        }

        private void Btn_min_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void Btn_support_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(Application.StartupPath + "/DM上位机校准软件说明.pdf");
        }

        private void panel2_Paint(object sender, PaintEventArgs e)
        {

        }

        private void labelAngle_Click(object sender, EventArgs e)
        {

        }

    }
}
