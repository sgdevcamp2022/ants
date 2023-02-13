
using System;
using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using UnityEngine;
using Google.Protobuf;
using Google.Protobuf.Protocol;


public class EndBtn : MonoBehaviour
{

    private TcpClient socketConnection;
    public void ConnectToTcpServer()
    {
        try
        {
            socketConnection = new TcpClient();
            socketConnection.Connect("0.tcp.jp.ngrok.io", 19816);

            LogOut logout = new LogOut
            {
                Function = 3,
                Nickname = DatabaseManager.nickname//닉네임
            };

            byte[] StrByte = logout.ToByteArray();
            SendMessage(StrByte);

        }
        catch (Exception e)
        {
            Debug.Log("On client connect exception " + e);
        }
    }

    private void SendMessage(Byte[] buffer)
    {
        if (socketConnection == null)
        {
            return;
        }
        try
        {
      
            NetworkStream stream = socketConnection.GetStream();
            if (stream.CanWrite)
            {
                
                stream.Write(buffer, 0, buffer.Length);

                //byte[] outbuf = new byte[1024];
                //int a = stream.Read(outbuf, 0, buffer.Length);
                //CustomerList list = CustomerList.Parser.ParseFrom(outbuf, 0, a);

                //string nickname = list.Nickname;
                //int level = list.Level;
                //int exp = list.Exp;
                //int cash = list.Cash;

                //Debug.Log(nickname + "," + level + "," + exp + "," + cash);
            }

        }
        catch (SocketException socketException)
        {
            Debug.Log("Socket exception: " + socketException);
        }
    }
    public void Quit()
    {
#if UNITY_EDITOR
        ConnectToTcpServer();
        UnityEditor.EditorApplication.isPlaying = false;
#else
        ConnectToTcpServer();
        Application.Quit();
#endif
    }
}
