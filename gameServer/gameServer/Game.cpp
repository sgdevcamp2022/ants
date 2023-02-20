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
        user->SetPosition(-464.13, -351.64);
        position += 5;

        packet.add_user()->CopyFrom(it->second->GetUserInfo());
    }

    auto buffer = PacketHandler::MakeBufferSharedPtr(packet, S_StartGame);
    _room->Broadcast(buffer);
}

void Game::End()
{
    LOCK_GUARD;

    if (_users.size()<1)
    {
        winner = 0;
    }
    
    for (auto& it : _users) {
        if (it.second == nullptr)
        {
            continue;
        }

        if(it.second->GetHp()>0)
        {
            winner = it.first;
        }
        //Protocol::S_GameEnd packet;
        //packet.set_userid(it.first);
        //auto buffer = PacketHandler::MakeBufferSharedPtr(packet, S_GameEnd);
        //_room->Broadcast(buffer);
        
        delete it.second;
    }
    _users.clear();
    isEnd = true;
    //_projectiles.clear();


}

void Game::Tick()
{
    UserMoveBroadcast();
    AttackBroadcast();
    AttackedBroadcast();
    DeadBroadcast();

    _movePacket.clear_move();
    _attackPacket.clear_attack();
    _attackedPacket.clear_userid();
    _deadPacket.clear_userid();

    {
        LOCK_GUARD;
        for (auto& it : _users) {
            if(it.second==nullptr)
            {
                continue;
            }
            CalculateUserPosition(it.second);
        }
    }


    ProjectileTick();

}

void Game::ProjectileTick()
{
    list<Projectile>::iterator it = _projectiles.begin();
    while (it != _projectiles.end())
    {
        it->Tick();

        User* hitUser = CheckCollision(*it);

        if (it->CanErase() || hitUser)
        {
            if (hitUser != nullptr)
            {
                hitUser->UserAttacked(10);
                _attackedPacket.add_userid(hitUser->GetUserId());
                //사망 감지
                if (hitUser->GetHp() <= 0)
                {
                    //사망처리
                    Dead(hitUser->GetUserId());
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

    for (auto it = _users.begin(); it != _users.end(); ++it)
    {
        if (projectile.GetOwnerId() == it->second->GetUserId())
        {
            continue;
        }

        float distance = it->second->GetDistance(projectile.GetX(), projectile.GetY());

        cout << "distance : " << distance << endl;
        if (distance < 2.0f)
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
    float distance = 0.133;
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
        dy = distance * 0.707;
        break;
    case Protocol::DOWN_LEFT:
        dx = -distance * 0.707;
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
    //cout << x<<", " << y<<endl;
}

void Game::AddUser(unsigned userID, string name)
{
    LOCK_GUARD;
    User* user = new User(userID, name);
    _users.insert(make_pair(userID, user));
}


void Game::AddProjectile(int ownerId, float speed, float directionX, float directionY, float damage)
{
    if(this==nullptr)
    {
        return;
    }
    
    LOCK_GUARD;
    if (isEnd == true)
    {
        return;
    }
    auto user = _users[ownerId];
    Projectile projectile(ownerId, user->GetX(), user->GetY(), speed, directionX, directionY, damage);
    _projectiles.push_back(projectile);

    Protocol::S_Attack packet;
    packet.set_userid(ownerId);
    packet.set_directionx(directionX);
    packet.set_directiony(directionY);

    _attackPacket.add_attack()->Swap(&packet);
    cout << "Fire!"<<directionX<<", "<<directionY << "\n";
    
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
    if (this == nullptr)
    {
        return;
    }
    LOCK_GUARD;
    if (isEnd == true)
    {
        return;
    }
    _movePacket.clear_move();

    auto user = _users[userID];
    /*if (user->GetDirection() == packet.moveinfo().direction() && user->GetDistance(packet.moveinfo().positionx(), packet.moveinfo().positiony()) < 0.00666f)
    {
        return;
    }*/

    if(user== nullptr)
    {
        return;
    }
    user->SetMoveInfo(packet.moveinfo());
    //user->SetDirection(packet.moveinfo().direction());

    //cout<<" UserID "<<userID << "Direction:" <<user->GetDirection() << user->GetX() << " , " << user->GetY() << endl;

    Protocol::S_Move sendPacket;
    sendPacket.set_userid(userID);
    sendPacket.mutable_moveinfo()->CopyFrom(user->GetReferenceMoveInfo());
    //_movePacket.add_move()->Swap(&sendPacket);
    auto buf = PacketHandler::MakeBufferSharedPtr(sendPacket, S_Move);
    _room->Broadcast(buf);
}

Protocol::S_Attacked Game::GetAttackedPacket()
{
    LOCK_GUARD;
    return _attackedPacket;
}

void Game::UserMoveBroadcast()
{
    LOCK_GUARD;
    if (_movePacket.move_size() < 1)
    {
        return;
    }
    auto buffer = PacketHandler::MakeBufferSharedPtr(_movePacket, S_MoveAdvanced);
    _room->Broadcast(buffer);
}

void Game::UserMovedBroadcast()
{
    
}


void Game::AttackedBroadcast()
{
    LOCK_GUARD;
    if (_attackedPacket.userid_size() < 1)
    {
        return;
    }
    auto buffer = PacketHandler::MakeBufferSharedPtr(_attackedPacket, 2009);
    _room->Broadcast(buffer);
}

void Game::AttackBroadcast()
{
    LOCK_GUARD;
    if (_attackPacket.attack_size() < 1)
    {
        return;
    }
    cout << "send Fire\n";
    auto buffer = PacketHandler::MakeBufferSharedPtr(_attackPacket, S_AttackAdvanced);
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
        //버그위치
        _users.erase(it);
    }
    cout << "Dead : " << userID << endl;
    _deadPacket.add_userid(userID);
    if (_users.size() <= 1)
    {
        End();
    }
}