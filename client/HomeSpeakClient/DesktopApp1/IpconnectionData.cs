using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Net;

class IpconnectionData
{

    public int portNumber = 8086;
    public string hostName = "";
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

    /* well fuck.? for future use */
    public static string GetLocalIPAddress()
    {
        var host = Dns.GetHostEntry(Dns.GetHostName());
        foreach (var ip in host.AddressList)
        {
            if (ip.AddressFamily == AddressFamily.InterNetwork)
            {
                Console.WriteLine("{0}", ip.ToString());
                return ip.ToString();
            }
        }
        throw new Exception("No network adapters with an IPv4 address in the system!");
    }

    public NetworkStream NetworkStream { get => networkStream; set => networkStream = value; }
}
