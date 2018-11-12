using Newtonsoft.Json;
using System;
using System.Diagnostics;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;
namespace DesktopApp1
{
    public class TcpConnection
    {
        private int portNumber = 8085;
        private string hostName = "127.0.0.1";
        private TcpClient client;
        private NetworkStream networkStream;
        public Boolean getMsg = false;
        private string readedJsonMessage;
        private Thread clientReceiveThread;
        Form1 form;

        public TcpConnection(Form1 tmpform)
        {
            form = tmpform;
            Console.Write("asd");
            client = new TcpClient(hostName, portNumber);
            clientReceiveThread = new Thread(() => readMessage());
            clientReceiveThread.IsBackground = true;
            clientReceiveThread.Start();
        }



        ~TcpConnection()
        {
            client.Close();
        }



        public void sendMessage(String Msg)
        {
            NetworkStream networkStream = client.GetStream();
            byte[] bytes = new byte[1024];
            byte[] bytesToSend = ASCIIEncoding.ASCII.GetBytes(Msg);
            Console.WriteLine("Sending : " + Msg);
            networkStream.Write(bytesToSend, 0, bytesToSend.Length);


        }
        public void readMessage() {

            int i = 0;
                try
                {
                Console.WriteLine("Msg from server");
                    Byte[] bytes = new Byte[1024];
                    while (true)
                    {
                        // Get a stream object for reading 				
                        using (NetworkStream stream = client.GetStream())
                        {
                            int length;
                            // Read incomming stream into byte arrary. 					
                            while ((length = stream.Read(bytes, 0, bytes.Length)) != 0)
                            {
                                var incommingData = new byte[length];
                                Array.Copy(bytes, 0, incommingData, 0, length);
                                // Convert byte array to string message. 						
                                string serverMessage = Encoding.ASCII.GetString(incommingData);
                                Console.WriteLine(i+".Message:" + "server message received as: " + serverMessage);
                            form.AddChatTextBox(serverMessage + "\n");
                            Thread.Sleep(100);
                            i++;
                            }
                        }
                    }
                }
                catch (SocketException socketException)
                {
                    Console.WriteLine("Socket exception: " + socketException);
                }
            }
       
          /*  if (client == null)
            {
                return;
            }
            NetworkStream stream = client.GetStream();
            form.AddChatTextBox("kilehet iratni");
            Console.WriteLine("Ez mukodik");
            byte[] bytesToRead = null;
            int bytesRead = 0;
            string readedJsonMessage = null;
            int i = 0;
            Byte[] bytes = new Byte[1024];
            try
             NetworkStream stream = client.GetStream();
            {
                {
                    int length;
                    while (true)
                    {
                        // Read incomming stream into byte arrary. 					
                        while ((length = stream.Read(bytes, 0, bytes.Length)) != 0)
                        {
                            var incommingData = new byte[length];
                            Array.Copy(bytes, 0, incommingData, 0, length);
                            // Convert byte array to string message. 						

                            // readedJsonMessage = "\"" + Encoding.ASCII.GetString(incommingData) + "\"";
                            readedJsonMessage = "\n" + Encoding.ASCII.GetString(incommingData);
                            Console.WriteLine(i + "edik" + readedJsonMessage);
                            i++;
                            ReadedMessage m = JsonConvert.DeserializeObject<ReadedMessage>(readedJsonMessage);
                            Msg.Data.Add(m);
                            m = null;
                            getMsg = true;
                        }
                    }

                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }

        }*/

    }
}
