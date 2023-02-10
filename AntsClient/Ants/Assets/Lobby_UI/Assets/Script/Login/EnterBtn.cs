using GraphQlClient.Core;

using Newtonsoft.Json.Linq;
using System;
using System.Net.Sockets;
using TMPro;
using UnityEngine;
using UnityEngine.Networking;
using Google.Protobuf;
using Google.Protobuf.Protocol;


public class EnterBtn : MonoBehaviour
{
    public TMP_InputField idField;
    public TMP_InputField pwField;
    public GameObject lobby;
    public GameObject falseText;
    public GameObject login;
    public GraphApi api;
    public string Token;
    public async void Login()
    {
        GraphApi.Query loginUser = api.GetQueryByName("login", GraphApi.Query.Type.Mutation);

        loginUser.SetArgs(new { email = $"{idField.text}", psword = $"{pwField.text}" });
        UnityWebRequest request = await api.Post(loginUser);
        string data = request.downloadHandler.text;
        JObject obj = JObject.Parse(data);//파싱
        
        if (obj["errors"]!=null)
        {
            falseText.SetActive(true);
            Debug.Log(data);

        }
        else if(obj["data"]["login"].ToString()!=null)
        {
            Token = obj["data"]["login"].ToString();
            ConnectToTcpServer();
            lobby.SetActive(true);
            login.SetActive(false);

        }
    }

    private TcpClient socketConnection;


    public void ConnectToTcpServer()
    {
        try
        {
            socketConnection = new TcpClient();
            socketConnection.Connect("0.tcp.jp.ngrok.io", 19816);

            Login login = new Login
            {
                Function = 0,
                Token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6IndsZ25zdGxzMDQxM0BuYXZlci5jb20iLCJzdWIiOiJob25pIiwiaWF0IjoxNjc2MDM1ODM1LCJleHAiOjE2NzY2NDA2MzV9.dItYomh65B5I2-DeLxFDfEW-HVElcRlWy-j2KCtu9Rc"
            };
   
            byte[] StrByte = login.ToByteArray();
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
            // Get a stream object for writing.             
            NetworkStream stream = socketConnection.GetStream();
            if (stream.CanWrite)
            {
                // Write byte array to socketConnection stream.                 
                stream.Write(buffer, 0, buffer.Length);
                
                byte[] outbuf = new byte[1024];
                int a = stream.Read(outbuf, 0, buffer.Length);
                CustomerList list = CustomerList.Parser.ParseFrom(outbuf, 0, a);

                DatabaseManager.nickname = list.Nickname;
                DatabaseManager.level = list.Level;
                DatabaseManager.exp = list.Exp;
                DatabaseManager.cash = list.Cash;

                Debug.Log(DatabaseManager.nickname + "," +  DatabaseManager.level + "," + DatabaseManager.exp + "," + DatabaseManager.cash);
            }

        }
        catch (SocketException socketException)
        {
            Debug.Log("Socket exception: " + socketException);
        }
    }
 
}
 

