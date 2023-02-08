#pragma once
#include "Protocol.pb.h"

class GameSession;


class User
{
public:
    User(unsigned int _userID, string _name, GameSession* _session);

    Protocol::UserInfo& GetUserInfo();


    //임시로 남겨둠
    unsigned int _userID;
    string _name;
    GameSession* _session;
    Protocol::UserState _state;
    Protocol::Direction _direction;
    int _positionX;
    int _positionY;

private:

    Protocol::UserInfo* userInfo;

};

