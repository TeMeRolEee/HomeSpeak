﻿using Newtonsoft.Json;
using System;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;

public class LoginData
{
    private static LoginData instance = null;

    public int type { get; set; }
    public string username { get; set; }
    public string email { get; set; }
    public string password { get; set; }

    private LoginData()
    {
        type = 0;
        
    }
    public static LoginData Instance
    {
        get
        {
            if (instance == null)
            {
                instance = new LoginData();
            }
            return instance;
        }
    }
    public Boolean Login()
    {
        try
        {
            IpconnectionData.Instance.client = new TcpClient(IpconnectionData.Instance.hostName, IpconnectionData.Instance.portNumber);
            string json = JsonConvert.SerializeObject(this);
            IpconnectionData.Instance.NetworkStream = IpconnectionData.Instance.client.GetStream();
            byte[] bytes = new byte[1024];
            byte[] bytesToSend = ASCIIEncoding.ASCII.GetBytes(json);
            Console.WriteLine("LoginMsg : " + json);
            IpconnectionData.Instance.NetworkStream.Write(bytesToSend, 0, bytesToSend.Length);
            LoginDataReplay Replay = null;
            using (NetworkStream stream = IpconnectionData.Instance.client.GetStream())
            {
                int length;
                // Read incomming stream into byte arrary. 					
                while ((length = stream.Read(bytes, 0, bytes.Length)) != 0)              //Replay Message
                {
                    var incommingData = new byte[length];
                    Array.Copy(bytes, 0, incommingData, 0, length);
                    // Convert byte array to string message. 						
                    string serverReplay = Encoding.ASCII.GetString(incommingData);
                    Console.WriteLine("Replay" + serverReplay);
                    Replay= JsonConvert.DeserializeObject<LoginDataReplay>(serverReplay);
                    Thread.Sleep(200);
                    break;
                }
            }
            if (Replay != null && Replay.type == 0 && Replay.status == 0)
            {
                
                return false;


            }
            else
            {
                Console.WriteLine("kilep a loginbol");
                
                return true;
            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e.ToString());
            MessageBox.Show("Could not connect to server!");
            return false;
        }
        }
    }
