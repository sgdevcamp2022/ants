using Google.Protobuf;
using Google.Protobuf.Protocol;
using ServerCore;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

class PacketHandler
{
	public static void M_TestHandler(PacketSession session, IMessage packet)
	{
		M_Test chatPacket = packet as M_Test;
		ServerSession serverSession = session as ServerSession;

		Debug.Log(chatPacket.Msg);
	}

	public static void M_InitroomHandler(PacketSession session, IMessage packet)
	{
		M_Initroom enterGamePacket = packet as M_Initroom;
		ServerSession serverSession = session as ServerSession;
	}

	public static void S_DeadHandler(PacketSession session, IMessage packet)
	{
        
		M_Initroom enterGamePacket = packet as M_Initroom;
		ServerSession serverSession = session as ServerSession;
	}

	

		public static void S_MoveadvancedHandler(PacketSession session, IMessage packet)
	{
		S_Moveadvanced d = new S_Moveadvanced {  }
		d.Move.Add(new S_Move { MoveInfo =  , UserID = new MoveInfo { Direction =, PositionX } })
		M_Initroom enterGamePacket = packet as M_Initroom;
		ServerSession serverSession = session as ServerSession;
	}
}
