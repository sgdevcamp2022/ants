#include "pch.h"
#include "Room.h"

#include"User.h"
#include "GameSession.h"
#include "PacketHandler.h"

Room::Room(unsigned roomID) : _roomID(roomID),userCount(0), _maxUserCount(0), isStart(false)
{
}

Room::~Room()
{
    for(auto i=_users.begin(); i!=_users.end(); ++i)
    {
        if(i->second==nullptr)
        {
            continue;
        }
        //i->second->session->room=nullptr;
        delete i->second;
        i->second = nullptr;
    }
}

void Room::Enter(User* user)
{
    userCount.fetch_add(1);
    LOCK_GUARD
    _users[user->_userID] = user;
}

void Room::Leave(User* user)
{
    userCount.fetch_sub(1);
    LOCK_GUARD
    _users.erase(user->_userID);
}

void Room::Broadcast(shared_ptr<char>& buffer)
{
    LOCK_GUARD

    for (auto& user : _users)
    {

        user.second->_session->RegisterSend(buffer);

    }
}

void Room::SetMaxUserCount(unsigned number)
{
    _maxUserCount = number;
}

void Room::AddUserID(unsigned int userID)
{
    _userList.push_back(userID);
}

bool Room::HasUser(unsigned userID)
{
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
    return _maxUserCount == userCount;
}

void Room::InitGame()
{

    for(auto it = _users.begin(); it!= _users.end(); ++it)
    {
        Protocol::UserInfo& userInfo = it->second->GetUserInfo();
        userInfo.mutable_moveinfo()->set_positionx(0);
        userInfo.mutable_moveinfo()->set_positiony(0);

        PacketHandler& ph= PacketHandler::GetPacketHandler();

        auto buffer = ph.MakeBuffer_sharedPtr(userInfo, S_UserInfo);

        Broadcast(buffer);
    }
}
