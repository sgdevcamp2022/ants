#include "pch.h"
#include "Room.h"

#include"User.h"
#include "GameSession.h"

Room::Room(unsigned roomID) : _roomID(roomID),userCount(0),isStart(false)
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
        //i->second->_session->room=nullptr;
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

void Room::Broadcast()
{
    LOCK_GUARD

    for (auto& user : _users)
    {
        //다른 방식으로 수정 필요, sendbuffer shared_ptr로 교체 필요
        auto buffer = sendDataQueue.front();

        sendDataQueue.pop_front();

        user.second->_session->RegisterSend(buffer);

    }
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
