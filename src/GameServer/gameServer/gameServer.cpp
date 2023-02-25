#include "pch.h"

#include "LobbySession.h"
#include "PacketHandler.h"
#include "Server.h"

#include "Protocol.pb.h"
#include "RoomManager.h"
boost::asio::io_context io_context;
LobbySession g_lobbySession(io_context);

int main()
{
	

    RoomManager::GetRoomManager();
    PacketHandler::GetPacketHandler();

    
    
    

    Server server(io_context);
    server.Init(MAX_SESSION_COUNT);

    server.Start();
    g_lobbySession.Start();

    Protocol::S_GameEnd packet;
    packet.set_messagetype(7);
    packet.set_winnerid("2");
    
    packet.add_userid("1");
    packet.add_userid("2");
    packet.add_userid("3");
    

    g_lobbySession.RegisterSend(packet);
 
    this_thread::sleep_for(1s);
    g_lobbySession.RegisterSend(packet);
    // 패킷 구조체에 데이터 넣고 버퍼에 넣어주기, 앞 쪽에 헤더 넣고
    // 그리고 센드
    

    getchar();
    
    
    
}
