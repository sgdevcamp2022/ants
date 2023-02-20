using Google.Protobuf;
using Google.Protobuf.Protocol;
using ServerCore;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

class PacketHandler : MonoBehaviour
{
	static public GameObject player;
	static public GameObject player2;
	static public HealthPVP player2H;
	static public HealthPVP playerH;
	static public AdcNomalAttack_PVP pvp;

	private void Awake()
	{
		player= GameObject.FindGameObjectWithTag("Player");
		player2 = GameObject.FindGameObjectWithTag("Player2");
		playerH = player.GetComponent<HealthPVP>();
		player2H = player2.GetComponent<HealthPVP>();
		pvp = GameObject.FindGameObjectWithTag("attackPVP").GetComponent< AdcNomalAttack_PVP>();
	}
	private void Start()
	{
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
		if (movePacket.UserID == int.Parse(DatabaseManager.UserID))
		{
			DatabaseManager.X = movePacket.Moveinfo.PositionX;
			DatabaseManager.Y = movePacket.Moveinfo.PositionY;
			DatabaseManager.changeDir = (int)(movePacket.Moveinfo.Direction);
		}
		else
		{
			DatabaseManager.X2 = movePacket.Moveinfo.PositionX;
			DatabaseManager.Y2 = movePacket.Moveinfo.PositionY;
			DatabaseManager.changeDir2 = (int)(movePacket.Moveinfo.Direction);
		}

	}
	public static void S_MoveadvancedHandler(PacketSession session, IMessage packet)
	{
		S_Moveadvanced movePackets = packet as S_Moveadvanced;
		S_Move movePacket = movePackets.Move[0];
		ServerSession serverSession = session as ServerSession;
	}



	public static void S_AttackHandler(PacketSession session, IMessage packet)
	{

		S_Attack attackPacket = packet as S_Attack;
		ServerSession serverSession = session as ServerSession;
		//pvp.getAttack(attackPacket.DirectionX, attackPacket.DirectionY);


	}
	public static void S_AttackadvancedHandler(PacketSession session, IMessage packet)
	{
		Debug.Log("쐈다");
		S_Attackadvanced attackadvanced = packet as S_Attackadvanced;
		ServerSession serverSession = session as ServerSession;
		S_Attack attack = attackadvanced.Attack[0];


		if (attack.UserID == int.Parse(DatabaseManager.UserID))
		{
			DatabaseManager.ShootX = attack.DirectionX;
			DatabaseManager.ShootY = attack.DirectionY;
			DatabaseManager.isShoot = true;
		}
		else
		{
			DatabaseManager.ShootX2 = attack.DirectionX;
			DatabaseManager.ShootY2 = attack.DirectionY;
			DatabaseManager.isShoot2 = true;
		}


	}
	public static void S_AttackedHandler(PacketSession session, IMessage packet)
	{
		S_Attacked attacked = packet as S_Attacked;
		ServerSession serverSession = session as ServerSession;
		for(int i =0; i < attacked.UserID.Count; i++)
        {
			if (attacked.UserID[i] == int.Parse(DatabaseManager.UserID))
			{
				DatabaseManager.isHit = true;
			}
			else
			{
				DatabaseManager.isHit2 = true;
			}
		}


	}

	public static void S_DeadHandler(PacketSession session, IMessage packet)
	{

		S_Dead dead = packet as S_Dead;
		ServerSession serverSession = session as ServerSession;
		for (int i = 0; i < dead.UserID.Count; i++)
		{

		}

	}


	public static void S_StartgameHandler(PacketSession session, IMessage packet)
	{
		S_Startgame startPacket = packet as S_Startgame;
		S_Userinfo userinfo = startPacket.User[0];
		Moveinfo moveinfo = userinfo.MoveInfo;

		S_Userinfo userinfo2 = startPacket.User[1];
		Moveinfo moveinfo2 = userinfo.MoveInfo;

		ServerSession serverSession = session as ServerSession;
		if (userinfo.UserID == int.Parse(DatabaseManager.UserID))
		{
			DatabaseManager.X = moveinfo.PositionX;
			DatabaseManager.Y = moveinfo.PositionY;
			DatabaseManager.changeDir = (int)(moveinfo.Direction);
		}
		else
		{
			DatabaseManager.X2 = moveinfo2.PositionX;
			DatabaseManager.Y2 = moveinfo2.PositionY;
			DatabaseManager.changeDir2 = (int)(moveinfo2.Direction);
		}

	}
}

