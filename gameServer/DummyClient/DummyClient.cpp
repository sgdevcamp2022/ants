#include "pch.h"
#include <iostream>
#include "PacketHandler.h"
#include "Client.h"

#include "Protocol.pb.h"
#include "RoomManager.h"

int main()
{
    this_thread::sleep_for(1s);
    boost::asio::io_context io_context;

    RoomManager::GetRoomManager();
    PacketHandler::GetPacketHandler();

    Client client(io_context);

    client.Start();
    io_context.run();

    getchar();

    

}
