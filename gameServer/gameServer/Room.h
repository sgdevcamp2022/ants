#pragma once

class GameSession;
class Room;
class User;


class Room
{
public:
    Room(unsigned int roomID);
    ~Room();
    void Enter(GameSession* session, unsigned int userId, string userName);
    void Leave(unsigned int userId);
    void Broadcast(shared_ptr<char>& buffer);
    unsigned int GetRoomID();
    void SetMaxUserCount(unsigned int number);
    void AddUserID(unsigned int userID);
    bool HasUser(unsigned userID);
    bool HasUserID(unsigned userID);
    bool CanStart();
    bool CanEnd();
    
    void InitGame();
    void EndGame();

    void AddProjectile(int ownerId, float x, float y, float speed, float direction, float damage);

private:
    friend class Game;
    void GameLoop();
    unsigned int _roomID;
    vector<unsigned int> _userList;
    unordered_map<unsigned int, GameSession*> _gameSessions;
    shared_ptr<Game> _game;

    int _maxUserCount;
    atomic<int> userCount;
    //필요 없을 시 삭제
    bool isStart;
    mutex mutexLock;
    

};

