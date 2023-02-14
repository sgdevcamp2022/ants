#include "pch.h"
#include "Game.h"
#include "PacketHandler.h"
#include "User.h"
#include "Room.h"

Game::Game(Room* room) : _room(room)
{
}


void Game::Init(int maxUserCount)
{
 
    if (!_room)
    {
        return;
    }

    int position = 10;
    for(int i=0; i<maxUserCount; ++i)
    {
        position += 10;
        _users[i]->SetPosition(position, position);
    }
    


}

void Game::End()
{
    
   
    
    _users.clear();
}

void Game::Tick()
{
    cout << "usesr num: " << _users.size() << endl;
}

void Game::AddUser(User* user)
{
    _users.push_back(user);
}
