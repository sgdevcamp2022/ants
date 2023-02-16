#include "pch.h"
#include "Projectile.h"

Projectile::Projectile(int ownerId,float x, float y, float speed, float directionX, float directionY, float damage)
    : _ownerId(ownerId),_x(x), _y(y), _speed(speed), _directionX(directionX),_directionY(directionY), _damage(damage), _maxLifeTick(TICK_IN_A_SECOND*2), _lifeTick(0)
{
}

void Projectile::Tick()
{
    //수명 계산
    ++_lifeTick;
    if(_lifeTick> _maxLifeTick)
    {
        return;
    }

    // 거리 계산 - 충돌은 Game에서
    _x += (_directionX * _speed);
    _y += (_directionY * _speed);
    
}

bool Projectile::CanErase()
{
    return  _lifeTick > _maxLifeTick;
}

float Projectile::GetX()
{
    return _x;
}

float Projectile::GetY()
{
    return _y;
}

int Projectile::GetOwnerId()
{
    return _ownerId;
}

