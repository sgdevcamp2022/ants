using Google.Protobuf.Protocol;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using UnityEngine;
using Google.Protobuf;
using Microsoft.Unity.VisualStudio.Editor;

public class SendInventInfo : MonoBehaviour
{
    GameObject slot1;
    GameObject slot2;
    GameObject slot3;
    GameObject slot4;
    GameObject slot5;
    Image potion;
    Image equip;

    private TcpClient socketConnection;
    public void ConnectToTcpServer()
    {
        try
        {
            socketConnection = new TcpClient();
            socketConnection.Connect("0.tcp.jp.ngrok.io", 19816);

           // for (int i = 1; i < 6; i++) {
                Inventory inventory = new Inventory
                {
                    Function = 4,
                    Nickname = DatabaseManager.nickname,
                    Type = "I",
                    SlotNum = $"",
                    ItemCode = ""
                };
           // }

           byte[] StrByte = inventory.ToByteArray();
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
}
