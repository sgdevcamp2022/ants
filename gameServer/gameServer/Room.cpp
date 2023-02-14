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

   for (auto i = _users.begin(); i != _users.end(); ++i)
   {
       if (i->second == nullptr)
       {
           continue;
       }
       Leave(i->second);
       i->second = nullptr;
   }
}

void Room::Enter(User* user)
{
    if(isStart==true)
    {
        return;
    }
    userCount.fetch_add(1);
    LOCK_GUARD
    _users[user->GetUserId()] = user;
    _game->AddUser(user);
}

void Room::Leave(User* user)
{
    if(user==nullptr)
    {
        return;
    }
    LOCK_GUARD
    auto it = _users.find(user->GetUserId());
    if (it == _users.end())
    {
        return;
    }
    it->second = nullptr;
    userCount.fetch_sub(1);
    
    delete user;
}

void Room::Broadcast(shared_ptr<char>& buffer)
{
    if (isStart == false)
    {
        return;
    }

    for (auto& user : _users)
    {
        user.second->_session->RegisterSend(buffer);
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
    if(isStart==true)
    {
        return true;
    }

    LOCK_GUARD
    auto it=_users.find(userID);
    if(it!=_users.end())
    {
        return true;
    }
    return false;
}

bool Room::HasUserID(unsigned userID)
{
    for(auto it =_userList.begin(); it!=_userList.end(); ++it)
    {
        if(*it==userID)
        {
            return true;
        }
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

void Room::Dead()
{
    userCount.fetch_sub(1);
}

void Room::InitGame()
{
    {
        LOCK_GUARD;
        isStart = true;
    }
    Protocol::S_GameStart packet;
    
    _game->Init(_maxUserCount);

    for (auto it = _users.begin(); it != _users.end(); ++it)
    {
        packet.add_user()->CopyFrom(it->second->GetUserInfo());
    }


    auto buffer = PacketHandler::MakeBufferSharedPtr(packet, S_StartGame);
    Broadcast(buffer);

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

void Room::GameLoop()
{
    while (CanEnd()==false)
    {
        _game->Tick();
        this_thread::sleep_for(100ms);
    }
}
