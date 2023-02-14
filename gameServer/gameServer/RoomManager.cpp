#include "pch.h"
#include "RoomManager.h"
#include "Room.h"
#include "User.h"

deque<thread*> RoomManager::_threads;
map<unsigned int, shared_ptr<Room>> RoomManager::_rooms;
mutex RoomManager::mutexLock;

RoomManager::~RoomManager()
{
    for(auto it = _rooms.begin(); it !=_rooms.end(); ++it)
    {
        DeleteRoom(it->second->GetRoomID());
    }
}

std::shared_ptr<Room> RoomManager::MakeRoom(unsigned roomID)
{
    std::shared_ptr<Room> room = std::make_shared<Room>(roomID);
    LOCK_GUARD;
    _rooms[roomID] = room;
    return room;
}

shared_ptr<Room> RoomManager::GetRoomByRoomID(unsigned roomID)
{
    LOCK_GUARD
        auto it = _rooms.find(roomID);
    if (it != _rooms.end())
    {
        return it->second;
    }
    return nullptr;
}

void RoomManager::DeleteRoom(int roomId)
{
    LOCK_GUARD;
    auto it = _rooms.find(roomId);
    if (it == _rooms.end())
    {
        return;
    }
    _rooms.erase(it);
}

void RoomManager::AddThread(thread* thread)
{
    LOCK_GUARD;
    _threads.push_back(thread);
}


void RoomManager::DeleteThread()
{
    LOCK_GUARD;

    for (auto it = _threads.begin(); it != _threads.end(); ++it)
    {
        if((*it)->joinable())
        {
            (*it)->join();
        }
        delete* it;

        it = _threads.erase(it) - 1;
    }
}