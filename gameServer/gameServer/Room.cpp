#include "pch.h"
#include "Room.h"

#include "GameSession.h"

Room::Room(unsigned roomID) : _roomID(roomID)
{
}

void Room::Enter(User* user)
{
    LOCK_GUARD
    _users[user->userID] = user;
}

void Room::Leave(User* user)
{
    LOCK_GUARD
    _users.erase(user->userID);
}

void Room::Broadcast()
{
    LOCK_GUARD

    for (auto& user : _users)
    {
        auto buffer = sendDataQueue.front();

        sendDataQueue.pop_front();

        user.second->session->RegisterSend(sizeof(buffer), buffer);

    }
}
