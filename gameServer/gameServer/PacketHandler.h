#pragma once
#include "GameSession.h"
#include "Protocol.pb.h"

class GameSession;



struct PacketHeader
{
    unsigned __int16 size;
    unsigned __int16 id; // 프로토콜ID (ex. 1=로그인, 2=이동요청)
};

enum :unsigned int
{
    M_TEST = 1999,

    C_TEST = 2999,

};


class PacketHandler
{
public:
    // 길이에 따라 데이터 더 받고 오게 하는 기능 필요
    // 일다 패킷이 온전하게 도착했다는 가정 (온전하게 오지 않았다면 어떻게?)
    void HandlePacket(GameSession* session, char* data, int length)
    {
        PacketHeader* header = reinterpret_cast<PacketHeader*>(data);

        // Dispatch the packet to the appropriate handler function
        switch (header->id)
        {
        case M_TEST:
            Handle_M_TEST(session,data,length);
            break;

        case C_TEST:
            ;
            break;

            // Add more cases for each type of packet that the server can receive
        }
    }
    
    void Handle_M_TEST(GameSession* session, char* data, int length)
    {
        // Perform actions based on the contents of the login request packet
        Protocol::M_TEST packet;
        /*packet.ParseFromArray(data + sizeof(PacketHeader), length - sizeof(PacketHeader));
        cout << packet.msg() << endl;*/

        packet.set_msg("I'm GameServer.");

        const unsigned __int16 dataLength = packet.ByteSizeLong();
        const unsigned __int16 packetLength = dataLength + sizeof(PacketHeader);

        char* sendBuffer = new char[packetLength];
        PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer);
        header->size = packetLength;
        header->id = M_TEST;
        packet.SerializeToArray(& header[1],dataLength);

        session->RegisterSend(packetLength, sendBuffer);
    }
    
};
