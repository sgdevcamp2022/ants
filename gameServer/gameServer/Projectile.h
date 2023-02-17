#pragma once

class Projectile {
public:
    Projectile(int ownerId,float x, float y, float speed, float direction, float damage = 10);

    void Tick();

    bool CanErase();

    float GetX();
    float GetY();
    int GetOwnerId();

private:
    float _x;
    float _y;
    float _speed;
    float _direction;
    float _damage;
    int _lifeTick;
    int _maxLifeTick;
    
    int _ownerId;
};


