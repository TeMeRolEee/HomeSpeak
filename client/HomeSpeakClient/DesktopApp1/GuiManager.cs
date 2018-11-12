using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DesktopApp1
{
    public class GuiManager
    {
        
        public void AddTextToChatBox(string s, Form1 f1)
        {
            f1.AddChatTextBox(s);
            Thread.Sleep(2000);
            f1.AddChatTextBox("random valami");
            Thread.Sleep(2000);
            f1.AddChatTextBox(s);
        }
    }
}
