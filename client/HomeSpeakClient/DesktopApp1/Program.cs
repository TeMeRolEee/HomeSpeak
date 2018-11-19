using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DesktopApp1
{
    static class Program
    {

        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Form2  Login = new Form2();
            Application.Run(Login);
            Form1 Client  = new Form1();
            Application.Run(Client);
            Console.ReadKey();
        }
    }
}
