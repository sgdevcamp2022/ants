
using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Http;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using UnityEngine;

public class SoketManager : MonoBehaviour
{
    private TcpClient socketConnection;

    public void Start()
    {
        ConnectToTcpServer();
    }

    private void ConnectToTcpServer()
    {
        try
        {
            
            socketConnection = new TcpClient();
            socketConnection.Connect("0.tcp.jp.ngrok.io", 16144);
            string a = "hi";
            Debug.Log("connected");
            byte[] StrByte = Encoding.UTF8.GetBytes(a);
            SendMessage(StrByte);
            //socketConnection.send
        }
        catch (Exception e)
        {
            Debug.Log("On client connect exception " + e);
        }
    }

    /// Send message to server using socket connection.     
    private void SendMessage(Byte[] buffer)
    {
        if (socketConnection == null)
        {
            return;
        }
        try
        {
            // Get a stream object for writing.             
            NetworkStream stream = socketConnection.GetStream();
            if (stream.CanWrite)
            {
                // Write byte array to socketConnection stream.                 
                stream.Write(buffer, 0, buffer.Length);
            }
            Debug.Log("sended");
        }
        catch (SocketException socketException)
        {
            Debug.Log("Socket exception: " + socketException);
        }
    }
}





