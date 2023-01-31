#include "pch.h"
#include "RoomManager.h"
#include "Room.h"

int RoomManager::GetRoomID(unsigned int userID)
{

    for (auto& room : _rooms)
    {
        auto it = room.second->_users.find(userID);
        if(it != room.second->_users.end())
        {
            //찾음
            return room.first;
        }
    }

    //못찾음
    return 0;
}

Room* RoomManager::MakeRoom(unsigned RoomID)
{

}
