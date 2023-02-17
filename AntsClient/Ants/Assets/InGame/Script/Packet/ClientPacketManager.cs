using Google.Protobuf;
using Google.Protobuf.Protocol;
using ServerCore;
using System;
using System.Collections.Generic;

class PacketManager
{
	#region Singleton
	static PacketManager _instance = new PacketManager();
	public static PacketManager Instance { get { return _instance; } }
	#endregion
	
	PacketManager()
	{
		Register();
	}


	Dictionary<ushort, Action<PacketSession, ArraySegment<byte>, ushort>> _onRecv = new Dictionary<ushort, Action<PacketSession, ArraySegment<byte>, ushort>>();
	Dictionary<ushort, Action<PacketSession, IMessage>> _handler = new Dictionary<ushort, Action<PacketSession, IMessage>>();

	public void Register()
	{
		_onRecv.Add((ushort)MsgId.MInitroom, MakePacket<M_Initroom>);
		_handler.Add((ushort)MsgId.MInitroom, PacketHandler.M_InitroomHandler);
		_onRecv.Add((ushort)MsgId.SRoomcompleted, MakePacket<S_Roomcompleted>);
		//_handler.Add((ushort)MsgId.SRoomcompleted, PacketHandler.S_RoomcompletedHandler);
		_onRecv.Add((ushort)MsgId.MTest, MakePacket<M_Test>);
		_handler.Add((ushort)MsgId.MTest, PacketHandler.M_TestHandler);
		_onRecv.Add((ushort)MsgId.SStartgame, MakePacket<S_Startgame>);
		//_handler.Add((ushort)MsgId.SStartgame, PacketHandler.S_StartgameHandler);
		_onRecv.Add((ushort)MsgId.SUserinfo, MakePacket<S_Userinfo>);
		//_handler.Add((ushort)MsgId.SUserinfo, PacketHandler.S_UserinfoHandler);
		_onRecv.Add((ushort)MsgId.SMove, MakePacket<S_Move>);
		_handler.Add((ushort)MsgId.SMove, PacketHandler.S_MoveHandler);
		_onRecv.Add((ushort)MsgId.SMoveadvanced, MakePacket<S_Moveadvanced>);
		_handler.Add((ushort)MsgId.SMoveadvanced, PacketHandler.S_MoveadvancedHandler);
		_onRecv.Add((ushort)MsgId.SAttack, MakePacket<S_Attack>);
		//_handler.Add((ushort)MsgId.SAttack, PacketHandler.S_AttackHandler);
		_onRecv.Add((ushort)MsgId.SAttacked, MakePacket<S_Attacked>);
		//_handler.Add((ushort)MsgId.SAttacked, PacketHandler.S_AttackedHandler);
		_onRecv.Add((ushort)MsgId.SDead, MakePacket<S_Dead>);
		//_handler.Add((ushort)MsgId.SDead, PacketHandler.S_DeadHandler);
		_onRecv.Add((ushort)MsgId.SGameend, MakePacket<S_Gameend>);
		//_handler.Add((ushort)MsgId.SGameend, PacketHandler.S_GameendHandler);
	}
	
	public void OnRecvPacket(PacketSession session, ArraySegment<byte> buffer)
	{
		ushort count = 0;
		
		ushort size = BitConverter.ToUInt16(buffer.Array, buffer.Offset);
		count += 2;
		ushort id = BitConverter.ToUInt16(buffer.Array, buffer.Offset + count);
		count += 2;
		
		Action<PacketSession, ArraySegment<byte>, ushort> action = null;
		if (_onRecv.TryGetValue(id, out action))
			action.Invoke(session, buffer, id);
	}
	
	void MakePacket<T>(PacketSession session, ArraySegment<byte> buffer, ushort id) where T : IMessage, new()
	{
		T pkt = new T();
		pkt.MergeFrom(buffer.Array, buffer.Offset + 4, buffer.Count - 4);
		Action<PacketSession, IMessage> action = null;
		if (_handler.TryGetValue(id, out action))
			action.Invoke(session, pkt);
	}
	
	public Action<PacketSession, IMessage> GetPacketHandler(ushort id)
	{
		Action<PacketSession, IMessage> action = null;
		if (_handler.TryGetValue(id, out action))
			return action;
		return null;
	}
}