#pragma once

class User;
class Room;

class Game
{
public:
    Game(Room* room);

    void Init(int maxUserCount);
    void End();
    void Tick();

    void AddUser(User* user);
private:

    Room*_room;
    vector<User*> _users;

};
