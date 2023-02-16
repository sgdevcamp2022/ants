#include "pch.h"
#include "PacketHandler.h"

#include "Game.h"

void PacketHandler::HandlePacket(GameSession* session, char* data, int length)
{
    
    PacketHeader* header = reinterpret_cast<PacketHeader*>(data);

    switch (header->id)
    {
    case M_TEST:
        HandleMatchingTest(session, data, length);
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
        //HandleClientMove(session, data, length);
        HandleClientMoveAdvanced(session, data, length);
        break;

    case C_Attack:
        HandleClientAttack(session, data, length);
        break;
    case C_Attacked:
        HandleClientAttacked(session, data, length);
    }
    
}

void PacketHandler::HandleMatchingTest(GameSession* session, char* data, int length)
{
    Protocol::M_TEST packet;
    /*PARSE(packet);
    cout << packet.msg() << endl;*/

    packet.set_msg("I'm GameServer.");

    session->RegisterSend(MakeBuffer(packet, M_TEST));
}

void PacketHandler::HandleMatchingInitRoom(GameSession* session, char* data, int length)
{
    //키를 받아와 서 검증, 서버가 아니면 반환
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

    auto room = roomManager.MakeRoom(roomID);
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

    auto room = roomManager.GetRoomByRoomID(packet.roomid());

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
    
    
    room->Enter(session,packet.userid(),packet.name());

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

    session->game->UserMove(session->userId, packet);
    

    Protocol::S_Move sendPacket;
    sendPacket.set_userid(session->userId);
    sendPacket.mutable_moveinfo()->CopyFrom(packet.moveinfo());

    auto buffer = MakeBufferSharedPtr(sendPacket, S_Move);
    session->room->Broadcast(buffer);
}

void PacketHandler::HandleClientMoveAdvanced(GameSession* session, char* data, int length)
{
    if (ValidateUser(session) == false)
    {
        return;
    }
    Protocol::C_Move packet;
    PARSE(packet);
    session->game->UserMove(session->userId, packet);
}

void PacketHandler::HandleClientAttack(GameSession* session, char* data, int length)
{
    ValidateUser(session);

    Protocol::C_Attack packet;
    PARSE(packet);

    //나중에 쿨타임 같은 거 추가하려면 게임에 함수 추가
    Protocol::S_Attack sendPacket;
    sendPacket.set_userid(session->userId);
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

    
    Protocol::S_Attacked sendPacket;
    //sendPacket.set_userid(session->user->GetUserId());



    //체력 깎기 (user info에 체력 두고 관리해야할 듯, 수정필요)
    //int& hp = session->user->hp -= 10;
    //userInfo.set_hp(hp);

    ////죽으면 상태 변경
    //if (hp <= 0)
    //{
    //    userInfo.mutable_moveinfo()->set_state(Protocol::DEAD);
    //    session->room->Dead();
    //    if (session->room->CanEnd())
    //    {
    //        session->room->EndGame();

    //        //DB 접근 최후 승자만 승리+1

    //        //room 제거

    //        //return;
    //    }

    //    auto buffer = MakeBufferSharedPtr(userInfo, S_Dead);
    //    session->room->Broadcast(buffer);
    //    return;
    //}


    //auto buffer = MakeBufferSharedPtr(sendPacket, S_Attacked);
    //session->room->Broadcast(buffer);
}

bool PacketHandler::ValidateUser(GameSession* session)
{
    if (session->game == nullptr)
    {
        return false;
    }

    if(session->userId==NULL)
    {
        return false;
    }
    return true;
}
