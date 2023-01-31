#pragma once

class User;
class Room;
class GameSession;
class RoomManager
{
public:
    //UserID를 준다면?

    Room* MakeRoom(unsigned int roomID);

    Room* GetRoomByRoomID(unsigned int roomID);

    void DeleteRoom(Room* room);


private:
    map<unsigned int, Room*> _rooms;
    mutex mutexLock;
};

