#pragma once
#include "Protocol.pb.h"

class GameSession;

class User
{
public:
    User(unsigned int _userID, string _name, GameSession* _session);
    ~User();
    const Protocol::UserInfo& GetUserInfo();
    Protocol::UserInfo CopyUserInfo();


    //임시로 남겨둠, 아니면 이 아래는 맵에서 관리?
    unsigned int _userID;
    string _name;
    GameSession* _session;
    Protocol::UserState _state;
    Protocol::Direction _direction;
    int _positionX;
    int _positionY;
    int hp;
    unsigned int GetUserId();
    string GetName();
    const Protocol::MoveInfo& GetReferenceMoveInfo();

    void SetUserId(const unsigned int id);
    void SetName(const string name);
    void SetPosition(const float& x, const float& y);
    void SetMoveInfo(const Protocol::MoveInfo& moveInfo);
    void SetHp(const int& hp);
private:

    Protocol::UserInfo* userInfo;
    mutex mutexLock;

};

