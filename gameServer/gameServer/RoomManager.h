#pragma once


class Room;
class RoomManager
{
public:
    //UserID를 준다면?
    int GetRoomID(unsigned int userID);
    bool MakeRoom(unsigned int RoomID);

private:
    map<unsigned int, Room*> _rooms;
};

