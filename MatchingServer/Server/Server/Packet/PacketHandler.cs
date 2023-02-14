using Google.Protobuf;
using Google.Protobuf.Protocol;
using Server;
using ServerCore;
using System;
using System.Collections.Generic;
using System.Text;

class PacketHandler
{
	public static void C_TestHandler(PacketSession session, IMessage packet)
	{
		C_Test chatPacket = packet as C_Test;
		ClientSession serverSession = session as ClientSession;

		Console.WriteLine(chatPacket.Msg);
		
		Program._matching.Enter(serverSession);

	}

	public static void S_RoomcompletedHandler(PacketSession session, IMessage packet)
	{
		S_Roomcompleted chatPacket = packet as S_Roomcompleted;
		ClientSession serverSession = session as ClientSession;
        
		Console.WriteLine(chatPacket.RoomID+" status is "+chatPacket.IsCompleted);

		Program._matching.Enter(serverSession);

	}
}