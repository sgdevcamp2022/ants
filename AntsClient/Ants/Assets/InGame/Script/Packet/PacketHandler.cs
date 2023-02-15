using Google.Protobuf;
using Google.Protobuf.Protocol;
using ServerCore;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

class PacketHandler : MonoBehaviour
{
	static public GameObject player;

    private void Awake()
    {
		player = GameObject.FindGameObjectWithTag("Player2");
	}
    private void Start()
    {
		Debug.Log(player);
    }
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

	public static void S_MoveHandler(PacketSession session, IMessage packet)
	{
		S_Move movePacket = packet as S_Move;
		ServerSession serverSession = session as ServerSession;

		DatabaseManager.X = movePacket.MoveInfo.PositionX;
		DatabaseManager.Y = movePacket.MoveInfo.PositionY;
	}
}
