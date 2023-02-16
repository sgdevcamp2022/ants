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
        Protocol::S_GameEnd packet;
        packet.set_userid(it.first);
        auto buffer = PacketHandler::MakeBufferSharedPtr(packet, S_GameEnd);
        _room->Broadcast(buffer);

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
    _deadPacket.clear_userid();

    {
        LOCK_GUARD;
        for (auto& it : _users) {
            CalculateUserPosition(it.second);
        }
    }
    

    ProjectileTick();

}

void Game::ProjectileTick()
{
    LOCK_GUARD;
    for( auto it =_projectiles.begin(); it!= _projectiles.end();)
    {
        it->Tick();

        User* hitUser = CheckCollision(*it);

        if(it->CanErase() || hitUser)
        {
            if(hitUser !=nullptr)
            {
                hitUser->UserAttacked(10);
                _attackedPacket.add_userid(hitUser->GetUserId());
                //사망 감지
                if(hitUser->GetHp()<0)
                {
                    //사망처리
                    Dead(it->GetOwnerId());
                }

            }
            
            it = _projectiles.erase(it);
            
            cout << "projectile delete" << endl;
        }
        else
        {
            ++it;
        }
    }
}

User* Game::CheckCollision(Projectile& projectile)
{
    
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

void Game::CalculateUserPosition(User* user)
{
       
    float x = user->GetX();
    float y = user->GetY();
    float distance = 0.0666f;
    Protocol::Direction direction = user->GetDirection();


    float dx = 0.0f;
    float dy = 0.0f;
    switch (direction) {
    case Protocol::UP:
        dy = distance;
        break;
    case Protocol::DOWN:
        dy = -distance;
        break;
    case Protocol::LEFT:
        dx = -distance;
        break;
    case Protocol::RIGHT:
        dx = distance;
        break;
    case Protocol::UP_LEFT:
        dx = -distance * 0.707;
        dy = distance * 0.707;
        break;
    case Protocol::UP_RIGHT:
        dx = distance * 0.707;
        dy = distance* 0.707;
        break;
    case Protocol::DOWN_LEFT:
        dx = -distance* 0.707;
        dy = -distance * 0.707;
        break;
    case Protocol::DOWN_RIGHT:
        dx = distance * 0.707;
        dy = -distance * 0.707;
        break;
    case Protocol::NONE:
        // do nothing
        break;
    default:
        // invalid direction
        break;
    }

    // Update the user's position based on the change in position
    x += dx;
    y += dy;
    user->SetPosition(x, y);

    std::cout << user->GetX() << " , " << user->GetY() << endl;
}

void Game::AddUser(unsigned userID, string name)
{
    LOCK_GUARD;
    User* user = new User(userID, name);
    _users.insert(make_pair(userID, user));
}


void Game::AddProjectile(int ownerId, float speed, float directionX, float directionY, float damage)
{
    LOCK_GUARD;
    auto user = _users[ownerId];
    Projectile projectile(ownerId,user->GetX(), user->GetY(), speed, directionX, directionY,damage);
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

    auto user = _users[userID];

    // 방향이 같고 차이가 크지 않으면 무시
    if (user->GetDirection() == packet.moveinfo().direction() && user->GetDistance(packet.moveinfo().positionx(), packet.moveinfo().positiony()) < 0.00666f)
    {
        return;
    }
    // 너무 값이 다르다면 핵으로 판단 하고 처리
    
    float x = packet.moveinfo().positionx()*0.5 + user->GetX()*0.5;
    float y = packet.moveinfo().positiony() * 0.5 + user->GetY() * 0.5;

    user->SetPosition(x, y);
    user->SetDirection(packet.moveinfo().direction());

   
   

    Protocol::S_Move sendPacket;
    sendPacket.set_userid(userID);
    sendPacket.mutable_moveinfo()->CopyFrom(user->GetReferenceMoveInfo());

    _movePacket.add_move()->Swap(&sendPacket);
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
}

void Game::AttackedBroadcast()
{
    LOCK_GUARD;
    if (_attackedPacket.userid_size() < 1)
    {
        return;
    }
    auto buffer = PacketHandler::MakeBufferSharedPtr(_attackedPacket, S_Attacked);
    _room->Broadcast(buffer);
}

void Game::DeadBroadcast()
{
    LOCK_GUARD;
    if (_deadPacket.userid_size() < 1)
    {
        return;
    }
    auto buffer = PacketHandler::MakeBufferSharedPtr(_deadPacket, S_Dead);
    _room->Broadcast(buffer);
}

void Game::Dead(unsigned userID)
{
    auto it = _users.find(userID);
    if (it != _users.end()) {
        delete it->second;
        _users.erase(it);
    }
    _deadPacket.add_userid(userID);
    if(_users.size()<=1)
    {
        End();
    }
}
