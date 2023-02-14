#pragma once

class GameSession;
class Room;
class User;


class Room :enable_shared_from_this<Room>
{
public:
    Room(unsigned int roomID);
    ~Room();
    void Enter(User* user);
    void Leave(User* user);
    void Broadcast(shared_ptr<char>& buffer);
    unsigned int GetRoomID();
    void SetMaxUserCount(unsigned int number);
    void AddUserID(unsigned int userID);
    bool HasUser(unsigned userID);
    bool HasUserID(unsigned userID);
    bool CanStart();
    bool CanEnd();

    void Dead();
    
    void InitGame();
    void EndGame();

private:
    void GameLoop();
    unsigned int _roomID;
    vector<unsigned int> _userList;
    unordered_map<unsigned int, User*> _users;

    int _maxUserCount;
    atomic<int> userCount;
    //필요 없을 시 삭제
    bool isStart;
    mutex mutexLock;
    

};

