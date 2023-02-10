#pragma once
#include "GameSession.h"
#include "Protocol.pb.h"
#include "Room.h"
#include "RoomManager.h"
#include "User.h"

#define PARSE(packet) if(!packet.ParseFromArray(data + sizeof(PacketHeader), length - sizeof(PacketHeader))) {return;}

class GameSession;

struct PacketHeader
{
    unsigned __int16 size;
    unsigned __int16 id; 
};

enum :unsigned int
{
    M_InitRoom = 1000,
    S_RoomCompleted = 1001,

    M_TEST = 1999,

    C_EnterRoom = 2000,
    C_UserInfo=2001,
    S_UserInfo=2002,

    C_Move = 2003,
    S_Move = 2004,

    C_Attack = 2005,
    S_Attack = 2006,

    C_Attacked = 2007,
    S_Attacked = 2008,
    
    C_TEST = 2999,

};



class PacketHandler
{
private:
    PacketHandler() = default;
    ~PacketHandler() = default;
    PacketHandler(const PacketHandler& ref) = delete;
    PacketHandler& operator=(const PacketHandler& ref) = delete;

public:
    static PacketHandler& GetPacketHandler()
    {
        static PacketHandler ph;
        return ph;
    }


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

        case C_EnterRoom:
            Handle_C_EnterRoom(session, data, length);
            break;

        case C_Move:
            Handle_C_Move(session, data, length);
            break;

        case C_Attack:
            Handle_C_Attack(session, data, length);
            break;
        case C_Attacked:
            Handle_C_Attacked(session, data, length);
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

        if(roomManager.GetRoomByRoomID(roomID)!=nullptr)
        {
            Protocol::S_RoomCompleted sendPacket;
            sendPacket.set_roomid(roomID);
            sendPacket.set_iscompleted(false);

            auto buffer = MakeBuffer(sendPacket, S_RoomCompleted);
            session->RegisterSend(buffer);
            return;
        }

        Room* room = roomManager.MakeRoom(roomID);
        room->SetMaxUserCount(packet.userid_size());

        for (auto i = 0; i< packet.userid_size(); ++i)
        {
            room->AddUserID(packet.userid(i));
        }

        Protocol::S_RoomCompleted sendPacket;
        sendPacket.set_roomid(roomID);
        sendPacket.set_iscompleted(true);

        auto buffer = MakeBuffer(sendPacket, S_RoomCompleted);
        session->RegisterSend(buffer);
       
    }

    void Handle_C_EnterRoom(GameSession* session, char* data, int length)
    {
        Protocol::C_EnterRoom packet;
        PARSE(packet);
        RoomManager& roomManager = RoomManager::GetRoomManager();

        Room* room = roomManager.GetRoomByRoomID(packet.roomid());

        session->room = room;

        if(room == nullptr)
        {
            //없는 방 접근
            return;
        }
        if(!room->HasUserID(packet.userid()))
        {
            //잘못된 방 접근
            return;
        }

        User* user = new User(packet.userid(),packet.name(),session);
        session->user = user;

        room->Enter(user);

        if(/*room->CanStart()*/true)
        {
            //시작
            room->InitGame();
            
        }
    }

    void Handle_C_Move(GameSession* session, char* data, int length)
    {
        PacketHeader* header = reinterpret_cast<PacketHeader*>(data);

        Protocol::C_Move packet;
        PARSE(packet);

        Protocol::UserInfo& userInfo = session->user->GetUserInfo();
        *(userInfo.mutable_moveinfo()) = packet.moveinfo();

        Protocol::S_Move sendPacket;
        sendPacket.set_userid(userInfo.userid());
        *(sendPacket.mutable_moveinfo()) = packet.moveinfo();

        auto buffer = MakeBuffer_sharedPtr(sendPacket, S_Move);
        session->room->Broadcast(buffer);
    }

    void Handle_C_Attack(GameSession* session, char* data, int length)
    {
        Protocol::C_Attack packet;
        PARSE(packet);

        Protocol::UserInfo& userInfo = session->user->GetUserInfo();
        //필요시 유저 상태 공격으로 변경
        Protocol::S_Attack sendPacket;
        sendPacket.set_userid(userInfo.userid());
        sendPacket.set_directionx(packet.directionx());
        sendPacket.set_directiony(packet.directiony());

        auto buffer = MakeBuffer_sharedPtr(sendPacket, S_Attack);
        session->room->Broadcast(buffer);
    }

    void Handle_C_Attacked(GameSession* session, char* data, int length)
    {
        Protocol::C_Attacked packet;
        PARSE(packet);

        Protocol::UserInfo& userInfo = session->user->GetUserInfo();
        Protocol::S_Attacked sendPacket;
        sendPacket.set_userid(userInfo.userid());

        auto buffer = MakeBuffer_sharedPtr(sendPacket, S_Attacked);
        session->room->Broadcast(buffer);

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

    template<typename T>
    std::shared_ptr<char> MakeBuffer_sharedPtr(T& packet, unsigned int pakcetID)
    {
        const unsigned __int16 dataLength = packet.ByteSizeLong();
        const unsigned __int16 packetLength = dataLength + sizeof(PacketHeader);


        std::shared_ptr<char> sendBuffer(new char[packetLength], std::default_delete<char[]>());
        PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer.get());
        header->size = packetLength;
        header->id = pakcetID;
        packet.SerializeToArray(&header[1], dataLength);

        return sendBuffer;
    }
};
