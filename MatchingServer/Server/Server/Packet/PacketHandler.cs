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
}
