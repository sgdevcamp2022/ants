using ServerCore;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using UnityEngine;
using Google.Protobuf;
using Google.Protobuf.Protocol;
public class NetworkManager_packet : MonoBehaviour
{
	public GameObject player;
	ServerSession _session = new ServerSession();
	public void requestMatching()
	{
		C_Test chat = new C_Test()
		{
			Msg = $"simple UserID : {_session}"
		};
		Send(chat);
	}
	public void MyPlace()
	{
		C_Move move = new C_Move()
		{
			MoveInfo = new MoveInfo { State = UserState.Move, Direction = Direction.Down, PositionX = player.transform.position.x, PositionY = player.transform.position.y }
		};
		Send(move);
	}

	public void myButton()
    {
		InvokeRepeating("MyPlace", 0.33f, 0.33f);
	}
    private void Start()
    {

    }


    public void Connect()
	{
		Init("172.30.1.36", 10006);
	}
	public void EnterRoom()
    {
		C_Enterroom enterRoom = new C_Enterroom()
		{
			RoomID = 220,
			UserID = 100,
			Name = "yaho"
		};
		Send(enterRoom);

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
	public void Init() // for local
	{
		// DNS (Domain Name System)
		string host = Dns.GetHostName();
		IPHostEntry ipHost = Dns.GetHostEntry(host);
		IPAddress ipAddr = ipHost.AddressList[0];
		IPEndPoint endPoint = new IPEndPoint(ipAddr, 10006);

		Connector connector = new Connector();
		connector.Connect(endPoint,
			() => { return _session; },
			1);
	}
	public void Init(string ipAddrString, int portNumber)
	{
		IPAddress ipAddr = IPAddress.Parse(ipAddrString);
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