#pragma once
#include "Protocol.pb.h"

class GameSession;

class User
{
public:
    User(unsigned int _userID, string _name);
    ~User();
    const Protocol::UserInfo& GetUserInfo();
    Protocol::UserInfo CopyUserInfo();


    
    unsigned int GetUserId();
    string GetName();
    const Protocol::MoveInfo& GetReferenceMoveInfo();
    float GetDistance(float x, float y);

    void SetUserId(const unsigned int id);
    void SetName(const string name);
    void SetPosition(const float& x, const float& y);
    void SetMoveInfo(const Protocol::MoveInfo moveInfo);
    void SetHp(unsigned  int& hp);

    void UserAttacked(unsigned int damage);
private:

    Protocol::UserInfo _userInfo;
    Protocol::MoveInfo _moveInfo;
    mutex mutexLock;
    //임시로 남겨둠, 아니면 이 아래는 맵에서 관리?
    unsigned int _userID;
    string _name;
    int _hp;
    float _positionX;
    float _positionY;
};

