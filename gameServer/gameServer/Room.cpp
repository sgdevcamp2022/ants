#include "pch.h"
#include "Room.h"

#include"User.h"
#include "GameSession.h"
#include "PacketHandler.h"
#include "Game.h"

Room::Room(unsigned roomID) : _roomID(roomID),userCount(0), _maxUserCount(0), isStart(false),_game(make_shared<Game>(this))
{
    
}

Room::~Room()
{
    _game = nullptr;
}

void Room::Enter(GameSession* session, unsigned int userId, string userName)
{
    if(isStart==true)
    {
        return;
    }
    userCount.fetch_add(1);
    {
        LOCK_GUARD;
        _gameSessions[userId] = session;
    }
    _game->AddUser(userId, userName);
    session->userId = userId;
    session->game = _game.get();
}

void Room::Leave(unsigned int userId)
{
    LOCK_GUARD
    auto count = _gameSessions.erase(userId);
    if (count)
    {
        userCount.fetch_sub(1);
    }
}


void Room::Broadcast(shared_ptr<char>& buffer)
{
    if (isStart == false)
    {
        return;
    }

    for (auto& session : _gameSessions)
    {
        session.second->RegisterSend(buffer);
    }
}

unsigned Room::GetRoomID()
{
    return _roomID;
}

void Room::SetMaxUserCount(unsigned number)
{
    _maxUserCount = number;
}

void Room::AddUserID(unsigned int userID)
{
    LOCK_GUARD
    _userList.push_back(userID);
}

bool Room::HasUser(unsigned userID)
{
    LOCK_GUARD
    return _gameSessions.count(userID) > 0;
}

bool Room::HasUserID(unsigned userID)
{
    auto it = find(_userList.begin(), _userList.end(), userID);
    if (it != _userList.end()) {
        return true;
    }
    return false;
}

bool Room::CanStart()
{
    return (_maxUserCount == userCount.load())&&(isStart==false);
}

bool Room::CanEnd()
{
    return userCount.load() < 1 && isStart==true;
}

void Room::InitGame()
{
    {
        LOCK_GUARD;
        isStart = true;
    }
    
    
    _game->Init(_maxUserCount);

    thread gamethread([this](){
        GameLoop();
        EndGame();
        //Broadcast(PacketHandler::MakeBufferSharedPtr(Protocol::S_GameEnd(), S_EndGame));
        RoomManager::DeleteRoom(_roomID);
    });
    gamethread.detach();
}

void Room::EndGame()
{
    LOCK_GUARD;
    isStart = false;

}

void Room::AddProjectile(int ownerId, float x, float y, float speed, float direction, float damage)
{
    _game->AddProjectile(ownerId,x,y,speed,direction,damage);
}

void Room::GameLoop()
{
    while (CanEnd()==false)
    {
        _game->Tick();
        //AddProjectile(1, 1, 1, 1, 1, 1);
        Protocol::S_Attacked packet = _game->GetAttackedPacket();
        if(packet.userid_size()>0)
        {
            auto buffer = PacketHandler::MakeBufferSharedPtr(packet, S_Attacked);
            Broadcast(buffer);
        }


        this_thread::sleep_for(100ms);
    }
}
