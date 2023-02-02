#pragma once
#include "GameSession.h"
#include "Protocol.pb.h"
#include "Room.h"
#include "RoomManager.h"

#define PARSE(packet) packet.ParseFromArray(data + sizeof(PacketHeader), length - sizeof(PacketHeader))

class GameSession;

struct PacketHeader
{
    unsigned __int16 size;
    unsigned __int16 id; // 프로토콜ID (ex. 1=로그인, 2=이동요청)
};

enum :unsigned int
{
    M_InitRoom = 1000,
    S_RoomCompleted = 1001,

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
        
        switch (header->id)
        {
        case M_TEST:
            Handle_M_TEST(session, data, length);
            break;
            
        case C_TEST:
            //Handle_C_TEST(session, data, length);
            break;

        case M_InitRoom:
            Handle_M_InitRoom(session,data,length);
            break;
        }
    }
    
    void Handle_M_TEST(GameSession* session, char* data, int length)
    {
        Protocol::M_TEST packet;
        /*PARSE(packet);
        cout << packet.msg() << endl;*/

        packet.set_msg("I'm GameServer.");

        session->RegisterSend(MakeBuffer(packet, M_TEST));
    }

    void Handle_M_InitRoom(GameSession* session, char* data, int length)
    {
        Protocol::M_InitRoom packet;
        PARSE(packet);

        const unsigned int roomID = packet.roomid();

        RoomManager& roomManager = RoomManager::GetRoomManager();
        Room* room = roomManager.MakeRoom(roomID);
   
        for (auto i = 0; i< packet.user_size(); ++i)
        {
            room->AddUserID(packet.user(i).userid());
        }

        Protocol::S_RoomCompleted sendPacket;
        sendPacket.set_roomid(roomID);
        sendPacket.set_iscompleted(false);

        session->RegisterSend(MakeBuffer(sendPacket, S_RoomCompleted));
       
    }

    template<typename T>
    char* MakeBuffer(T& packet,unsigned int pakcetID )
    {
        const unsigned __int16 dataLength = packet.ByteSizeLong();
        const unsigned __int16 packetLength = dataLength + sizeof(PacketHeader);

        char* sendBuffer = new char[packetLength];
        PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer);
        header->size = packetLength;
        header->id = pakcetID;
        packet.SerializeToArray(&header[1], dataLength);

        return sendBuffer;
    }
    
};
