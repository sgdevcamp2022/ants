#include "pch.h"
#include "User.h"

User::User(unsigned userID, string name)
:_userID(userID),_name(name),_hp(100),_positionX(0),_positionY(0),_isMoved(false)
{

    _userInfo.set_userid(userID);
    _userInfo.set_name(name);
    _userInfo.set_hp(100);
    _userInfo.set_state(Protocol::IDLE);

    _moveInfo.set_direction(Protocol::NONE);
    _moveInfo.set_positionx(0.f);
    _moveInfo.set_positiony(0.f);
    

}

User::~User()
{

}

const Protocol::UserInfo& User::GetUserInfo()
{
    *_userInfo.mutable_moveinfo() = _moveInfo;
    return _userInfo;
}

Protocol::UserInfo User::CopyUserInfo()
{
    return _userInfo;
}


unsigned int User::GetUserId()
{
    return _userInfo.userid();
}

string User::GetName()
{
    return _userInfo.name();
}

int User::GetHp()
{
    return _userInfo.hp();
}

const Protocol::MoveInfo& User::GetReferenceMoveInfo()
{
    return _moveInfo;
}

float User::GetDistance(float x, float y)
{
    return (_moveInfo.positionx() - x) * (_moveInfo.positionx() - x) + (_moveInfo.positiony()- y) * (_moveInfo.positiony() - y);
}

void User::SetUserId(const unsigned int id)
{
    _userInfo.set_userid(id);
}

void User::SetName(const string name)
{

    _userInfo.set_name(name);
}

void User::SetPosition(const float& x, const float& y)
{
    _moveInfo.set_positionx(x);
    _moveInfo.set_positiony(y);
    //*_userInfo.mutable_moveinfo() = _moveInfo;
}

void User::SetDirection(Protocol::Direction direction)
{
    _moveInfo.set_direction(direction);
}

void User::SetMoveInfo(const Protocol::MoveInfo moveInfo)
{
    _isMoved = true;
    _moveInfo.CopyFrom(moveInfo);
    //*_userInfo.mutable_moveinfo() = _moveInfo;
}

void User::SetHp(unsigned int& hp)
{
    _userInfo.set_hp(hp);
}

void User::UserAttacked(unsigned int damage)
{
    unsigned int hp = _userInfo.hp() - damage;
    SetHp(hp);
}





