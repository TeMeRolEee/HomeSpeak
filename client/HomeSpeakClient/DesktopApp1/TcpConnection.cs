using Newtonsoft.Json;
using System;
using System.Diagnostics;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Text;
using System.Threading;
using System.Windows.Forms;
namespace DesktopApp1
{
    public class TcpConnection
    {
        
        private TcpClient client;
        private NetworkStream networkStream;
        private Thread clientReceiveThread;
        Form1 form;
        int roomId = 0;
        int userId = 1;

        public TcpConnection(Form1 tmpform)
        {
            form = tmpform;
            try
            {
                client = IpconnectionData.Instance.client;
                networkStream = IpconnectionData.Instance.NetworkStream;
                Console.Write("Connected to server");
                form.AddChatTextBox("Connected to server\n");
                clientReceiveThread = new Thread(() => readMessage());
                clientReceiveThread.IsBackground = true;
                clientReceiveThread.Start();
                roomId = 0;
                userId = LoginDataReplay.Instance.getUserID();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                MessageBox.Show("Could not connect to server!");
            }
        }
        ~TcpConnection()
        {
            try
            {
                client.Close();
            }
            catch (Exception E)
            {
                Console.WriteLine("Could not Close Client");
            }
        }
        public void readMessage()
        {

            int i = 0;
            try
            {
                
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
                            Console.WriteLine("Msg from server");
                            var incommingData = new byte[length];
                            Array.Copy(bytes, 0, incommingData, 0, length);
                            // Convert byte array to string message. 						
                            string serverMessage = Encoding.ASCII.GetString(incommingData);
                            Message Msg = JsonConvert.DeserializeObject<Message>(serverMessage);
                            Console.WriteLine(i + ".Message:" + "server message received as: " + serverMessage);
                            foreach (Data Msgs in Msg.data)
                            {
                                form.AddChatTextBox(LoginDataReplay.Instance.getUserName(Msgs.userID) + ": " + Msgs.message + Msgs.timestamp);
                            }
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

        public void SendChatMessage(string Msg)
        {
            Message Message = new Message();
            Message.type = 2;
            Message.token = "256";
            Data newData = new Data();
            newData.message = Msg;
            newData.roomID = roomId;                //elkell tárolni meyik  roomban vagy
            newData.userID = userId;
            newData.timestamp = DateTime.Now.ToString("yyyy.MM.dd. HH:mm:ss");
            string jsonMessage = JsonConvert.SerializeObject(Message);
            NetworkStream networkStream = client.GetStream();
            byte[] bytes = new byte[1024];
            byte[] bytesToSend = ASCIIEncoding.ASCII.GetBytes(jsonMessage);
            Console.WriteLine("Sending : " + Msg);
            networkStream.Write(bytesToSend, 0, bytesToSend.Length);
        }

        public void SendLoginMessage()
        {

            LoginData.Instance.type = 11;
            
            string jsonMessage = JsonConvert.SerializeObject(LoginData.Instance);
            networkStream = client.GetStream();
            byte[] bytes = new byte[1024];
            byte[] bytesToSend = ASCIIEncoding.ASCII.GetBytes(jsonMessage);
            Console.WriteLine("Sending : " + jsonMessage);
            networkStream.Write(bytesToSend, 0, bytesToSend.Length);
        }

        public static string GetSha256FromString(string strData)
        {
            var message = Encoding.ASCII.GetBytes(strData);
            SHA256Managed hashString = new SHA256Managed();
            string hex = "";

            var hashValue = hashString.ComputeHash(message);
            foreach (byte x in hashValue)
            {
                hex += String.Format("{0:x2}", x);
            }
            return hex;
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
