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

    static shared_ptr<Room> MakeRoom(unsigned roomID);


    static shared_ptr<Room> GetRoomByRoomID(unsigned int roomID);

    static void DeleteRoom(int roomId);
    
private:
    static std::map<unsigned int, std::shared_ptr<Room>> _rooms;
    static mutex mutexLock;
};

