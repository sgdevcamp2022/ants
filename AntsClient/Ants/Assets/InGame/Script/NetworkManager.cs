using ServerCore;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using UnityEngine;
using Google.Protobuf;
using Google.Protobuf.Protocol;

public class NetworkManager : MonoBehaviour
{
	ServerSession _session = new ServerSession();
	public GameObject player;

    void Start()
	{

		//Init();
		InvokeRepeating("sendMyPlace",0,0.1f);

	}

	public void requestMatching()
	{
		C_Chat chat = new C_Chat() 
		{
			Context = $"simple UserID : {_session}"
		};

		Send(chat);

		
	}

	public void sendMyPlace()
	{
		
		Debug.Log(player.transform.position.x +"  " + player.transform.position.y);
		/*
		C_Chat chat = new C_Chat()
		{
			Context = $"1234"
		};

		Send(chat);
		*/
	}

	public void Connect()
    {
		Init();
	}
	public void Send(IMessage packet)
	{
		string msgName = packet.Descriptor.Name.Replace("_", string.Empty);
		MsgId msgId = (MsgId)Enum.Parse(typeof(MsgId), msgName);


		ushort size = (ushort)packet.CalculateSize();
		byte[] sendBuffer = new byte[size + 4];
		Array.Copy(BitConverter.GetBytes(size + 4), 0, sendBuffer, 0, sizeof(ushort));
		Array.Copy(BitConverter.GetBytes((ushort)msgId), 0, sendBuffer, 2, sizeof(ushort));
		Array.Copy(packet.ToByteArray(), 0, sendBuffer, 4, size);

		Send(new ArraySegment<byte>(sendBuffer));
	}
	public void Send(ArraySegment<byte> sendBuff)
	{
		_session.Send(sendBuff);
	}
	public void Disconnect()
    {
		_session.Disconnect();
    }

	public void Init()
	{
		// DNS (Domain Name System)
		string host = Dns.GetHostName();
		IPHostEntry ipHost = Dns.GetHostEntry(host);
		IPAddress ip = IPAddress.Parse("172.30.1.36");
		//IPAddress ipAddr = ipHost.AddressList[0];
		IPEndPoint endPoint = new IPEndPoint(ip, 10006);
		Connector connector = new Connector();

		connector.Connect(endPoint,
			() => { return _session; },
			1);

		
	}
	public void Init(IPAddress ipAddr, int portNumber)
	{
		IPEndPoint endPoint = new IPEndPoint(ipAddr, portNumber);

		Connector connector = new Connector();
		connector.Connect(endPoint,
			() => { return _session; },
			1);
	}



	public void Update()
	{
		List<PacketMessage> list = PacketQueue.Instance.PopAll();
		foreach (PacketMessage packet in list)
		{
			Action<PacketSession, IMessage> handler = PacketManager.Instance.GetPacketHandler(packet.Id);
			if (handler != null)
				handler.Invoke(_session, packet.Message);
		}	
	}

}
