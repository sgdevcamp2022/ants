#pragma once


class Room;
class Session;
class RoomManager
{
public:
    //UserID를 준다면?
    int GetRoomID(unsigned int userID);
    Room* MakeRoom(unsigned int RoomID);
    void BindSessionToUser(Session* session, unsigned int userID);

private:
    map<unsigned int, Room*> _rooms;
};

