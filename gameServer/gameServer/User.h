#pragma once

class GameSession;

class User
{
public:
    User(unsigned int userID, string name);
    unsigned int _userID;
    string _name;
    GameSession* _session;
};

