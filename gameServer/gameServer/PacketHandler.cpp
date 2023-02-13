#include "pch.h"
#include "PacketHandler.h"

void PacketHandler::HandlePacket(GameSession* session, char* data, int length)
{
    
    PacketHeader* header = reinterpret_cast<PacketHeader*>(data);

    switch (header->id)
    {
    case M_TEST:
        HandleMatcingTest(session, data, length);
        break;

    case C_TEST:
        //Handle_C_TEST(session, data, length);
        break;

    case M_InitRoom:
        HandleMatchingInitRoom(session, data, length);
        break;

    case C_EnterRoom:
        HandleClientEnterRoom(session, data, length);
        break;

    case C_Move:
        HandleClientMove(session, data, length);
        break;

    case C_Attack:
        HandleClientAttack(session, data, length);
        break;
    case C_Attacked:
        HandleClientAttacked(session, data, length);
    }
    
}

void PacketHandler::HandleMatcingTest(GameSession* session, char* data, int length)
{
    Protocol::M_TEST packet;
    /*PARSE(packet);
    cout << packet.msg() << endl;*/

    packet.set_msg("I'm GameServer.");

    session->RegisterSend(MakeBuffer(packet, M_TEST));
}

void PacketHandler::HandleMatchingInitRoom(GameSession* session, char* data, int length)
{
    Protocol::M_InitRoom packet;
    PARSE(packet);

    const unsigned int roomID = packet.roomid();

    RoomManager& roomManager = RoomManager::GetRoomManager();

    if (roomManager.GetRoomByRoomID(roomID) != nullptr)
    {
        Protocol::S_RoomCompleted sendPacket;
        sendPacket.set_roomid(roomID);
        sendPacket.set_iscompleted(false);

        auto buffer = MakeBufferSharedPtr(sendPacket, S_RoomCompleted);
        session->RegisterSend(buffer);
        return;
    }

    Room* room = roomManager.MakeRoom(roomID);
    room->SetMaxUserCount(packet.userid_size());

    for (auto i = 0; i < packet.userid_size(); ++i)
    {
        room->AddUserID(packet.userid(i));
    }

    Protocol::S_RoomCompleted sendPacket;
    sendPacket.set_roomid(roomID);
    sendPacket.set_iscompleted(true);

    auto buffer = MakeBufferSharedPtr(sendPacket, S_RoomCompleted);
    session->RegisterSend(buffer);
}

void PacketHandler::HandleClientEnterRoom(GameSession* session, char* data, int length)
{
    Protocol::C_EnterRoom packet;
    PARSE(packet);
    RoomManager& roomManager = RoomManager::GetRoomManager();

    Room* room = roomManager.GetRoomByRoomID(packet.roomid());



    if (room == nullptr)
    {
        //없는 방 접근
        return;
    }
    if (!room->HasUserID(packet.userid()))
    {
        //잘못된 방 접근
        return;
    }
    if (room->HasUser(packet.userid()))
    {
        //또 접근
        return;
    }
    session->room = room;

    Protocol::UserInfo& userInfo = session->user->GetUserInfo();

    userInfo.set_userid(packet.userid());
    userInfo.set_name(packet.name());

    // Room에서 Init 후 게임 스레드 만들고 거기서 관리해야함
    room->Enter(session->user);

    if (room->CanStart())
    {
        //시작
        room->InitGame();

    }
}

void PacketHandler::HandleClientMove(GameSession* session, char* data, int length)
{
    if (ValidateUser(session) == false)
    {
        return;
    }
    Protocol::C_Move packet;
    PARSE(packet);


    Protocol::UserInfo& userInfo = session->user->GetUserInfo();


    *(userInfo.mutable_moveinfo()) = packet.moveinfo();

    Protocol::S_Move sendPacket;
    sendPacket.set_userid(userInfo.userid());
    *(sendPacket.mutable_moveinfo()) = packet.moveinfo();

    auto buffer = MakeBufferSharedPtr(sendPacket, S_Move);
    session->room->Broadcast(buffer);
}

void PacketHandler::HandleClientAttack(GameSession* session, char* data, int length)
{
    ValidateUser(session);

    Protocol::C_Attack packet;
    PARSE(packet);

    Protocol::UserInfo& userInfo = session->user->GetUserInfo();
    //필요시 유저 상태 공격으로 변경
    Protocol::S_Attack sendPacket;
    sendPacket.set_userid(userInfo.userid());
    sendPacket.set_directionx(packet.directionx());
    sendPacket.set_directiony(packet.directiony());

    auto buffer = MakeBufferSharedPtr(sendPacket, S_Attack);
    session->room->Broadcast(buffer);
}

void PacketHandler::HandleClientAttacked(GameSession* session, char* data, int length)
{
    if (ValidateUser(session) == false)
    {
        return;
    }

    //나중에 공격력 있을 수도 있으니
    Protocol::C_Attacked packet;
    PARSE(packet);

    Protocol::UserInfo& userInfo = session->user->GetUserInfo();
    Protocol::S_Attacked sendPacket;
    sendPacket.set_userid(userInfo.userid());

    //체력 깎기 (user info에 체력 두고 관리해야할 듯, 수정필요)
    int& hp = session->user->hp -= 10;
    userInfo.set_hp(hp);

    //죽으면 상태 변경
    if (hp <= 0)
    {
        userInfo.mutable_moveinfo()->set_state(Protocol::DEAD);
        session->room->Dead();
        if (session->room->CanEnd())
        {
            session->room->EndGame();

            //DB 접근 최후 승자만 승리+1

            //room 제거

            //return;
        }

        auto buffer = MakeBufferSharedPtr(userInfo, S_Dead);
        session->room->Broadcast(buffer);
        return;
    }


    auto buffer = MakeBufferSharedPtr(sendPacket, S_Attacked);
    session->room->Broadcast(buffer);
}

bool PacketHandler::ValidateUser(GameSession* session)
{
    if (session->user == nullptr)
    {
        return false;
    }
    Protocol::UserInfo& userInfo = session->user->GetUserInfo();
    if (userInfo.moveinfo().state() == Protocol::DEAD)
    {
        return false;
    }
    return true;
}
