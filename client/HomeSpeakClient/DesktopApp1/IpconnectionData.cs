using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;


    class IpconnectionData
    {

        public int portNumber = 8086;
        public string hostName = "172.21.29.106";
        public TcpClient client;
        private NetworkStream networkStream;
        private static IpconnectionData instance = null;
        public static IpconnectionData Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new IpconnectionData();
                }
                return instance;
            }
        }

        public NetworkStream NetworkStream { get => networkStream; set => networkStream = value; }
    }
