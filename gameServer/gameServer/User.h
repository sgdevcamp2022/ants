#pragma once

class GameSession;

class User
{
public:
    unsigned int userID = 0;
    string name;
    GameSession* session;
};

