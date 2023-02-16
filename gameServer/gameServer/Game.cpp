#include "pch.h"
#include "Game.h"
#include "PacketHandler.h"
#include "User.h"
#include "Room.h"

Game::Game(Room* room) : _room(room)
{
}

Game::~Game()
{
    for (auto& it : _users) {
        if (it.second == nullptr)
        {
            continue;
        }
        delete it.second;
    }
    _users.clear();
    _room = nullptr;
}


void Game::Init(int maxUserCount)
{
 
    if (!_room)
    {
        return;
    }
    Protocol::S_GameStart packet;

    float position = 3.0f;
    for (auto it = _users.begin(); it != _users.end(); ++it) {
        auto& user = it->second;
        user->SetPosition(position, position);
        position += 3;

        packet.add_user()->CopyFrom(it->second->GetUserInfo());
    }

    auto buffer = PacketHandler::MakeBufferSharedPtr(packet, S_StartGame);
    _room->Broadcast(buffer);
}

void Game::End()
{
    LOCK_GUARD;
    for (auto& it : _users) {
        if(it.second==nullptr)
        {
            continue;
        }
        delete it.second;
    }
    _users.clear();
    _projectiles.clear();
}

void Game::Tick()
{
    UserMoveBroadcast();
    _movePacket.clear_move();
    _attackedPacket.clear_userid();
    ProjectileTick();

}

void Game::ProjectileTick()
{
    for( auto it =_projectiles.begin(); it!= _projectiles.end();)
    {
        it->Tick();

        User* hitUser = CheckCollision(*it);

        if(it->CanErase() || hitUser)
        {
            if(hitUser !=nullptr)
            {
                hitUser->UserAttacked(10);
                //사망 감지

                _attackedPacket.add_userid(hitUser->GetUserId());
            }
            {
                LOCK_GUARD;
                it = _projectiles.erase(it);
            }
            
        }
        else
        {
            ++it;
        }
    }
}

User* Game::CheckCollision(Projectile& projectile)
{
    LOCK_GUARD;
    for (auto it = _users.begin(); it!=_users.end(); ++it)
    {
        if(projectile.GetOwnerId()==it->second->GetUserId())
        {
            continue;
        }

        float distance = it->second->GetDistance(projectile.GetX(), projectile.GetY());
        if(distance<1.0f)
        {
            return it->second;
        }
    }
    
    return nullptr;
}

void Game::AddUser(unsigned userID, string name)
{
    LOCK_GUARD;
    User* user = new User(userID, name);
    _users.insert(make_pair(userID, user));
}


void Game::AddProjectile(int ownerId,float x, float y, float speed, float direction, float damage)
{
    LOCK_GUARD;
    Projectile projectile(ownerId,x, y, speed, direction, damage);
    _projectiles.push_back(projectile);
}

void Game::Remove(unsigned userID)
{
    LOCK_GUARD;
    auto it = _users.find(userID);
    if (it != _users.end()) {
        delete it->second;
        _users.erase(it);
    }
}

void Game::UserMove(unsigned int userID, Protocol::C_Move& packet)
{
    LOCK_GUARD;
    _users[userID]->SetMoveInfo(packet.moveinfo());

    Protocol::S_Move sendPacket;
    sendPacket.set_userid(userID);
    sendPacket.mutable_moveinfo()->CopyFrom(packet.moveinfo());

    _movePacket.add_move()->Swap(&sendPacket);

    cout << "add to packet" << endl;
}

Protocol::S_Attacked Game::GetAttackedPacket()
{
    LOCK_GUARD;
    return _attackedPacket;
}

void Game::UserMoveBroadcast()
{
    LOCK_GUARD;
    if(_movePacket.move_size()<1)
    {
        return;
    }
    auto buffer = PacketHandler::MakeBufferSharedPtr(_movePacket, S_MoveAdvanced);
    _room->Broadcast(buffer);
    cout << "boradcast packet" << endl;
}