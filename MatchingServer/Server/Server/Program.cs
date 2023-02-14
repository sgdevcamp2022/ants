using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Google.Protobuf;
using Google.Protobuf.Protocol;
using Google.Protobuf.WellKnownTypes;
using ServerCore;

namespace Server
{
	class Program
	{
		static Listener _listener = new Listener();
		public static Matching _matching = new Matching();
		public static ClientSession _gamerServerSession = new ClientSession();
		
		static void FlushRoom()
		{
			_matching.Push(() => _matching.Flush());
			JobTimer.Instance.Push(FlushRoom, 250);
		}



		static void Main(string[] args)
		{
			// Client Listener
			string host = Dns.GetHostName();
			IPHostEntry ipHost = Dns.GetHostEntry(host);
			IPAddress ipAddr = ipHost.AddressList[0];
			IPEndPoint endPoint = new IPEndPoint(ipAddr, 10005);
			_listener.Init(endPoint, () => { return SessionManager.Instance.Generate(); });
			Console.WriteLine("ClientListening...");

			// Game Server Connect //서버가 연결되지 않으면 발생하는 오류수정 필요
			Console.WriteLine("GameServerConnecting...");
			Connector connector = new Connector();
			string host2 = "0.tcp.jp.ngrok.io";
			IPHostEntry ipHost2 = Dns.GetHostEntry(host2);
			IPAddress ipAddr2 = ipHost2.AddressList[0];
			IPEndPoint gameServer = new IPEndPoint(ipAddr2, 10913);
			connector.Connect(gameServer,
				() => { return _gamerServerSession; },
				1);

			M_Initroom packet = new M_Initroom
			{
				RoomID = 220,
				
			};
			packet.UserID.Add(100);
			packet.UserID.Add(101);
			packet.UserID.Add(102);


			_gamerServerSession.Send(packet);


			//FlushRoom();
			JobTimer.Instance.Push(FlushRoom);

			while (true)
			{
				JobTimer.Instance.Flush();
				_matching.checkAwaiter();
			}
		}
	}
}
