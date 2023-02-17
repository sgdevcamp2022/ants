#pragma once
#include "Projectile.h"
#include "Protocol.pb.h"
class User;
class Room;
class Projectile;
class Game
{
public:
    Game(Room* room);
    ~Game();

    void Init(int maxUserCount);
    void End();
    void Tick();
    void ProjectileTick();
    User* CheckCollision(Projectile& projectile);
    void CalculateUserPosition(User* user);

    void AddUser(unsigned int userID, string name);
    void AddProjectile(int ownerId, float speed, float directionX, float directionY, float damage);
    void Remove(unsigned int userID);

    void UserMove(unsigned int userID,Protocol::C_Move& moveInfo);
    void UserMoveBroadcast();
    void UserMovedBroadcast();
    void AttackedBroadcast();
    void DeadBroadcast();

    void Dead(unsigned int userID);

    Protocol::S_Attacked GetAttackedPacket();

private:

    int test = 1;;

    Room*_room;
    unordered_map<unsigned int, User*> _users;
    list<Projectile> _projectiles;
    mutex mutexLock;
    Protocol::S_Attacked _attackedPacket;
    Protocol::S_Dead _deadPacket;
    Protocol::S_MoveAdvanced _movePacket;
    Protocol::S_MoveAdvanced packet;

    int moveSendTick = 0;
};


