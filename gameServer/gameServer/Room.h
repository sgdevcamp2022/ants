#pragma once

class GameSession;
class Room;
class User;
#define LOCK_GUARD lock_guard<mutex> lock{mutexLock};

class Room
{
public:
    Room(unsigned int roomID);
    void Enter(User* user);
    void Leave(User* user);
    void Broadcast();

    friend class RoomManager;
private:
    unsigned int _roomID;
    mutex mutexLock;
    map<unsigned int, User*> _users;

    std::deque< char* > sendDataQueue;
};

