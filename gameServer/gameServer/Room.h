#pragma once

class GameSession;
class Room;

#define LOCK_GUARD lock_guard<mutex> lock{mutexLock};

struct User
{
    int userID = 0;
    string name;
    GameSession* session;
    
};

class Room
{
public:
    void Enter(User* user);
    void Leave(User* user);
    void Broadcast();

    friend class RoomManager;
private:
    mutex mutexLock;
    map<unsigned int, User*> _users;

    std::deque< char* > sendDataQueue;
};

