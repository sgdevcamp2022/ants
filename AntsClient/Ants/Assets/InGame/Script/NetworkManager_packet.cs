using ServerCore;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using UnityEngine;
using Google.Protobuf;
using Google.Protobuf.Protocol;
using DG.Tweening;
public class NetworkManager_packet : MonoBehaviour
{
	public GameObject player;
	public GameObject player2;
	ServerSession _session = new ServerSession();
	[SerializeField] float time;
	[SerializeField] float distance;

	bool once;
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
		if(DatabaseManager.dir == DatabaseManager.changeDir)
        {
			DIR();
			return;
        }
        else
        {
			if (DatabaseManager.dir == 0)
			{
				C_Move move = new C_Move()
				{
					Moveinfo = new Moveinfo { Direction = Direction.Up, PositionX = player.transform.position.x, PositionY = player.transform.position.y }
				};
				Send(move);
			}
			else if (DatabaseManager.dir == 1)
			{
				C_Move move = new C_Move()
				{
					Moveinfo = new Moveinfo { Direction = Direction.Down, PositionX = player.transform.position.x, PositionY = player.transform.position.y }
				};
				Send(move);
			}
			else if (DatabaseManager.dir == 2)
			{
				C_Move move = new C_Move()
				{
					Moveinfo = new Moveinfo { Direction = Direction.Left, PositionX = player.transform.position.x, PositionY = player.transform.position.y }
				};
				Send(move);
			}
			else if (DatabaseManager.dir == 3)
			{
				C_Move move = new C_Move()
				{
					Moveinfo = new Moveinfo { Direction = Direction.Right, PositionX = player.transform.position.x, PositionY = player.transform.position.y }
				};
				Send(move);
			}
			else if (DatabaseManager.dir == 4)
			{
				C_Move move = new C_Move()
				{
					Moveinfo = new Moveinfo { Direction = Direction.UpLeft, PositionX = player.transform.position.x, PositionY = player.transform.position.y }
				};
				Send(move);
			}
			else if (DatabaseManager.dir == 5)
			{
				C_Move move = new C_Move()
				{
					Moveinfo = new Moveinfo { Direction = Direction.UpRight, PositionX = player.transform.position.x, PositionY = player.transform.position.y }
				};
				Send(move);
			}
			else if (DatabaseManager.dir == 6)
			{
				C_Move move = new C_Move()
				{
					Moveinfo = new Moveinfo { Direction = Direction.DownLeft, PositionX = player.transform.position.x, PositionY = player.transform.position.y }
				};
				Send(move);
			}
			else if (DatabaseManager.dir == 7)
			{
				C_Move move = new C_Move()
				{
					Moveinfo = new Moveinfo { Direction = Direction.DownRight, PositionX = player.transform.position.x, PositionY = player.transform.position.y }
				};
				Send(move);
			}
			else if ((DatabaseManager.dir == 8))
			{
				C_Move move = new C_Move()
				{
					Moveinfo = new Moveinfo { Direction = Direction.None, PositionX = player.transform.position.x, PositionY = player.transform.position.y }
				};
				Send(move);
			}

			DIR();
		}

	}

	int dirrr;
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

	
	private void Start()
    {
		EnterRoom();
		InvokeRepeating("MyPlace", 0, 0.05f);
	}
	private void Awake()
	{
	    Connect();
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
	/*
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
	*/
	public void Init(string ipAddrString, int portNumber)
	{

		IPAddress ipAddr = IPAddress.Parse(ipAddrString);
		IPEndPoint endPoint = new IPEndPoint(ipAddr, portNumber);
		Connector connector = new Connector();
		connector.Connect(endPoint,
			() => { return _session; },
			1);
	}


	public void Attack(float x, float y)
    {
		C_Attack attack = new C_Attack()
		{
			DirectionX = x,
			DirectionY = y
	};
		Send(attack);
	}

	void DIR()
	{
		if (DatabaseManager.changeDir == 0)
		{
			player2.transform.DOMove(new Vector2(player2.transform.position.x, player2.transform.position.y + distance), time).SetEase(Ease.Linear);
		}
		else if (DatabaseManager.changeDir == 1)
		{
			player2.transform.DOMove(new Vector2(player2.transform.position.x, player2.transform.position.y - distance), time).SetEase(Ease.Linear);
		}
		else if (DatabaseManager.changeDir == 2)
		{
			player2.transform.DOMove(new Vector2(player2.transform.position.x + distance, player2.transform.position.y), time).SetEase(Ease.Linear);
		}
		else if (DatabaseManager.changeDir == 3)
		{
			player2.transform.DOMove(new Vector2(player2.transform.position.x - distance, player2.transform.position.y), time).SetEase(Ease.Linear);
		}
		else if (DatabaseManager.changeDir == 4)
		{
			player2.transform.DOMove(new Vector2(player2.transform.position.x - distance, player2.transform.position.y + distance), time).SetEase(Ease.Linear);
		}
		else if (DatabaseManager.changeDir == 5)
		{
			player2.transform.DOMove(new Vector2(player2.transform.position.x + distance, player2.transform.position.y + distance), time).SetEase(Ease.Linear);
		}
		else if (DatabaseManager.changeDir == 6)
		{
			player2.transform.DOMove(new Vector2(player2.transform.position.x - distance, player2.transform.position.y - distance), time).SetEase(Ease.Linear);
		}
		else if (DatabaseManager.changeDir == 7)
		{
			player2.transform.DOMove(new Vector2(player2.transform.position.x + distance, player2.transform.position.y - distance), time).SetEase(Ease.Linear);
		}
		else if (DatabaseManager.changeDir == 8)
		{
			transform.DOPause();
			player2.transform.DOMove(new Vector2(DatabaseManager.X, DatabaseManager.Y), time).SetEase(Ease.Linear);
		}
	}


}