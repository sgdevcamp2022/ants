#pragma once

class GameSession;
class Room;
class User;


class Room
{
public:
    Room(unsigned int roomID);
    ~Room();
    void Enter(User* user);
    void Leave(User* user);
    void Broadcast();
    void AddUserID(unsigned int userID);
    bool HasUser(unsigned userID);
    bool HasUserID(unsigned userID);
    
private:
    unsigned int _roomID;
    vector<unsigned int> _userList;
    unordered_map<unsigned int, User*> _users;
    atomic<int> userCount;
    //필요 없을 시 삭제
    bool isStart;
    mutex mutexLock;
    //필요 없을 시 삭제
    std::deque< char* > sendDataQueue;
};

