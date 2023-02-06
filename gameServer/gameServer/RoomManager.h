#pragma once

class User;
class Room;
class GameSession;
class RoomManager
{
private:
    RoomManager() = default;
    ~RoomManager();
    RoomManager(const RoomManager& ref) = delete;
    RoomManager& operator=(const RoomManager& ref) = delete;

public:
    static RoomManager& GetRoomManager()
    {
        static RoomManager rm;
        return rm;
    }
    //UserID를 준다면?

    static Room* MakeRoom(unsigned int roomID);

    static Room* GetRoomByRoomID(unsigned int roomID);

    static void DeleteRoom(Room* room);
    
private:
    static map<unsigned int, Room*> _rooms;
    static mutex mutexLock;
};

