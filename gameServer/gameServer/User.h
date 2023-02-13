#pragma once
#include "Protocol.pb.h"

class GameSession;


class User
{
public:
    User(unsigned int _userID, string _name, GameSession* _session);
    ~User();
    Protocol::UserInfo& GetUserInfo();


    //임시로 남겨둠, 아니면 이 아래는 맵에서 관리?
    unsigned int _userID;
    string _name;
    GameSession* _session;
    Protocol::UserState _state;
    Protocol::Direction _direction;
    int _positionX;
    int _positionY;
    int hp;

private:

    Protocol::UserInfo* userInfo;

};

