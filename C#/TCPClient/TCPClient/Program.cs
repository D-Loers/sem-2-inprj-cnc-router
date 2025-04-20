using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace SocketClient
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Console.WriteLine("Enter the IP address of the server: ");
                string serverIP = Console.ReadLine();

                const int port = 8888;
                TcpClient clientsock = new TcpClient();
                Console.WriteLine("connecting to server...");
                clientsock.Connect(IPAddress.Parse(serverIP), port);

                NetworkStream stream = clientsock.GetStream();

                while (true)
                {
                    Console.WriteLine("Enter Message (type quit to exit): ");
                    string message = Console.ReadLine();

                    byte[] data = Encoding.ASCII.GetBytes(message);
                    stream.Write(data, 0, data.Length);

                    if (message.ToLower() == "quit")
                    {
                        break; //command to stop
                    }

                    byte[] responseData = new byte[1024];
                    int bytesRead = stream.Read(responseData, 0, responseData.Length);
                    string responseMessage = Encoding.ASCII.GetString(responseData, 0, bytesRead);
                    Console.WriteLine("server response: " + responseMessage);

                }
                clientsock.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine("Exception: " + e.ToString());
            }

        }
    }
}
