#include "pch.h"

#include "PacketHandler.h"
#include "Server.h"

#include "Protocol.pb.h"
#include "RoomManager.h"


int main()
{
	boost::asio::io_context io_context;

    RoomManager::GetRoomManager();
    PacketHandler::GetPacketHandler();

    Server server(io_context);
    server.Init(MAX_SESSION_COUNT);

    server.Start();


    
    // 패킷 구조체에 데이터 넣고 버퍼에 넣어주기, 앞 쪽에 헤더 넣고
    // 그리고 센드
    

    getchar();
    
    
    
}
