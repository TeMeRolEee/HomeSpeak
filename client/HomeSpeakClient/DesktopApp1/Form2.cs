using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DesktopApp1
{
    public partial class Form2 : Form
    {
        
        public Form2()
        {
            InitializeComponent();
        }

        private void LoginButton_Click(object sender, EventArgs e)
        {
            LoginData.Instance.username = UsernameBox.Text.ToString();
            LoginData.Instance.password = passwordBox.Text.ToString();
            LoginData.Instance.email = EmailBox.Text.ToString();
            Boolean validLoginData = LoginData.Instance.Login();
            
            if (validLoginData == false)
            {
                MessageBox.Show("Invalid username or password");
            }
            else
            {
                this.Close();
            }
        }

        private void pictureBox7_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void pictureBox6_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        [DllImport("user32", EntryPoint = "ReleaseCapture")]
        private extern static void ReleaseCapture();
        [DllImport("user32", EntryPoint = "SendMessage")]
        private extern static void SendMessage(System.IntPtr hWnd, int wMsg, int wParam, int lParam);

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            ReleaseCapture();
            SendMessage(this.Handle, 0x112, 0xf012, 0);
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            this.UsernameBox.Enter += new EventHandler(UsernameBox_Enter);
            this.UsernameBox.Leave += new EventHandler(UsernameBox_Leave);
            UsernameBox_SetText();
            this.passwordBox.Enter += new EventHandler(passwordBox_Enter);
            this.passwordBox.Leave += new EventHandler(passwordBox_Leave);
            passwordBox_SetText();
            this.EmailBox.Enter += new EventHandler(EmailBox_Enter);
            this.EmailBox.Leave += new EventHandler(EmailBox_Leave);
            EmailBox_SetText();

        }
        protected void UsernameBox_SetText()
        {
            this.UsernameBox.Text = "Username";
            UsernameBox.ForeColor = Color.Gray;
        }
        protected void passwordBox_SetText()
        {
            this.passwordBox.Text = "Password";
            passwordBox.ForeColor = Color.Gray;
        }
        protected void EmailBox_SetText()
        {
            this.EmailBox.Text = "myemail@randomemail.com";
            EmailBox.ForeColor = Color.Gray;
        }
        private void UsernameBox_Leave(object sender, EventArgs e)
        {
            if (UsernameBox.Text.Trim() == "")
                UsernameBox_SetText();
        }
        private void passwordBox_Leave(object sender, EventArgs e)
        {
            if (passwordBox.Text.Trim() == "")
                passwordBox_SetText();
        }
        private void EmailBox_Leave(object sender, EventArgs e)
        {
            if (EmailBox.Text.Trim() == "")
                EmailBox_SetText();
        }
        private void UsernameBox_Enter(object sender, EventArgs e)
        {
            if (UsernameBox.ForeColor == Color.White)
                return;
            UsernameBox.Text = "";
            UsernameBox.ForeColor = Color.White;
        }
        private void passwordBox_Enter(object sender, EventArgs e)
        {
            if (passwordBox.ForeColor == Color.White)
                return;
            passwordBox.Text = "";
            passwordBox.ForeColor = Color.White;
        }
        private void EmailBox_Enter(object sender, EventArgs e)
        {
            if (EmailBox.ForeColor == Color.White)
                return;
            EmailBox.Text = "";
            EmailBox.ForeColor = Color.White;
        }
        private void SendLoginEnter(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                LoginData.Instance.username = UsernameBox.Text.ToString();
                LoginData.Instance.password = passwordBox.Text.ToString();
                LoginData.Instance.email = EmailBox.Text.ToString();
                Boolean validLoginData = LoginData.Instance.Login();

                if (validLoginData == false)
                {
                    MessageBox.Show("Invalid username or password");
                }
                else
                {
                    this.Close();
                }
         
            }
        }

    }
}
