using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CCWin;
namespace DM_CalibrationTools
{
    public partial class MainForms : SkinMain
    {
        private Point mPoint;
        private Point mPoint_logo;

        IMUInformation frm_IMUInformation;
        IMUConnect     frm_IMUConnect;

        System.Windows.Forms.Timer mTimer_Main;
        public MainForms()
        {
            InitializeComponent();
            this.Load += new System.EventHandler(this.MainForms_Load);

        }

        private void MainForms_Load(object sender, EventArgs e)
        {
            this.Text = "GeekIMU管理中心";

            // 设置传感器信息为主默认窗口
            frm_IMUInformation = new IMUInformation();
            frm_IMUInformation.TopLevel = false;
            this.MainPanel.Controls.Add(frm_IMUInformation);

            frm_IMUConnect = new IMUConnect();
            frm_IMUConnect.TopLevel = false;
            this.MainPanel.Controls.Add(frm_IMUConnect);

            frm_IMUInformation.Show();
            frm_IMUConnect.Show();
            frm_IMUInformation.Hide();

            // 配置定时器，定时器用于定期查询设备状态
            mTimer_Main = new System.Windows.Forms.Timer();
            mTimer_Main.Interval = 1500;
            mTimer_Main.Enabled = true;
            mTimer_Main.Tick += new EventHandler(timer_Tick);

            
        }

        void timer_Tick(object sender, EventArgs e)
        {
            label_dev_status.Text = frm_IMUInformation.GetIMUStatus() == true ? "设备已连接" : "未连接";

            if (frm_IMUInformation.GetIMUStatus() == false)
            {
                frm_IMUInformation.Hide();
                frm_IMUConnect.Show();
            }
            else
            {
                frm_IMUInformation.Show();
                frm_IMUConnect.Hide();
            }
        }

        private void Btn_Close_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Btn_min_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void Control_Panel_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                this.Location = new Point(this.Location.X + e.X - mPoint.X, this.Location.Y + e.Y - mPoint.Y);
            }
        }

        private void Control_Panel_MouseDown(object sender, MouseEventArgs e)
        {
            mPoint = new Point(e.X, e.Y);
        }


        private void Panel_logo_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                this.Location = new Point(this.Location.X + e.X - mPoint_logo.X, this.Location.Y + e.Y - mPoint_logo.Y);
            }
        }

        private void Panel_logo_MouseDown(object sender, MouseEventArgs e)
        {
            mPoint_logo = new Point(e.X, e.Y);
        }

        private void Control_Panel_Paint(object sender, PaintEventArgs e)
        {

        }

        private void Btn_support_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(Application.StartupPath + "/DM上位机校准软件说明.pdf");
        }
    }
}
