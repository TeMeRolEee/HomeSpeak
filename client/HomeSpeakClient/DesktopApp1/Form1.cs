using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;

// This is the code for your desktop app.
// Press Ctrl+F5 (or go to Debug > Start Without Debugging) to run your app.

namespace DesktopApp1
{
    public partial class Form1 : Form
    {
        public delegate void AddChatTextBoxDelegate(string txt);

        TcpConnection Tcpconnection;
        Messages Msgs;

        public Form1()
        {
            InitializeComponent();
            Console.WriteLine("itt volt az init component ");
            Tcpconnection = new TcpConnection(this);
            Msgs = new Messages();
        }
        public void AddChatBoxMethod(String myString)
        {
            ChatTextBox.Text += myString;
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }



        private void pictureBox3_Click(object sender, EventArgs e)
        {
           
                this.WindowState = FormWindowState.Minimized;
        }

        private void Form1_Load(object sender, System.EventArgs e)
        {
            Console.Write("its work");
            TreeNode treeNode = new TreeNode("Windows");
            RoomList.Nodes.Add(treeNode);
            UserNameLabel.Text = LoginData.Instance.username;
        }
        [DllImport("user32", EntryPoint = "ReleaseCapture")]
        private extern static void ReleaseCapture();
        [DllImport("user32", EntryPoint = "SendMessage")]
        private extern static void SendMessage(System.IntPtr hWnd, int wMsg, int wParam, int lParam);

        private void pictureBox4_Click(object sender, EventArgs e)
        {

        }

        private void RoomList_AfterSelect(object sender, TreeViewEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            
        }

        private void ChatBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void SendButton_Click(object sender, EventArgs e)
        {
            ChatTextBox.Text += SendTextBox.Text;
            SendTextBox.Text = null;
        }
        public void AddChatTextBox(string txt)
        {
            if (this.InvokeRequired)
            {
                this.BeginInvoke(new AddChatTextBoxDelegate(AddChatTextBox),
                                          new object[] { txt });

                return;
            }
            if (ChatTextBox.Text.Length == 0)
                ChatTextBox.Text = txt;
            else
                ChatTextBox.AppendText("\r\n" + txt);
        }

        private void ChatLabel_Click(object sender, EventArgs e)
        {

        }

        private void ChatTextBox_TextChanged(object sender, EventArgs e)
        {
            
        }

   

        private void SendTextBox_Enter(object sender, EventArgs e)
        {
            
        }

        private void SendTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                ChatTextBox.Text += SendTextBox.Text;
                SendTextBox.Text = null;
                //Thread SendMessage = new Thread(() => Tcpconnection.sendMessage());
                //SendMessage.IsBackground = true;
                //SendMessage.Start();
            }
        }

        private void panel2_Paint(object sender, PaintEventArgs e)
        {
            

        }

        private void ChatTextBox_TextChanged_1(object sender, EventArgs e)
        {
            SendTextBox.Text = null;
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            ReleaseCapture();
            SendMessage(this.Handle, 0x112, 0xf012,0);
        }
    }
}
