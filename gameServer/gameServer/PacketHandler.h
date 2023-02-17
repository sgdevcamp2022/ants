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
    S_StartGame = 2001,

    C_UserInfo=2002,
    S_UserInfo=2003,

    C_Move = 2004,
    S_Move = 2005,
    S_MoveAdvanced=2105,

    C_Attack = 2006,
    S_Attack = 2007,

    C_Attacked = 2008,
    S_Attacked = 2009,

    S_Dead = 2010,

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


    void HandlePacket(GameSession* session, char* data, int length);
    
    void HandleMatchingTest(GameSession* session, char* data, int length);

    void HandleMatchingInitRoom(GameSession* session, char* data, int length);

    void HandleClientEnterRoom(GameSession* session, char* data, int length);

    void HandleClientMove(GameSession* session, char* data, int length);
    void HandleClientMoveAdvanced(GameSession* session, char* data, int length);

    void HandleClientAttack(GameSession* session, char* data, int length);

    void HandleClientAttacked(GameSession* session, char* data, int length);

    bool ValidateUser(GameSession* session);

    template<typename T>
    static char* MakeBuffer(T& packet,unsigned int pakcetID )
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
    static std::shared_ptr<char> MakeBufferSharedPtr(T& packet, unsigned int pakcetID)
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
