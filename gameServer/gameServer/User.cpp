#include "pch.h"
#include "User.h"

User::User(unsigned userID, string name)
:_userID(userID),_name(name),_hp(100),_positionX(0),_positionY(0),_isMoved(false)
{

    _userInfo.set_userid(userID);
    _userInfo.set_name(name);
    _userInfo.set_hp(100);
    _userInfo.set_state(Protocol::IDLE);

    _moveInfo.set_direction(Protocol::DOWN);
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

float User::GetDistance(float x, float y)
{
    return (_positionX - x) * (_positionX - x) + (_positionY - y) * (_positionY - y);
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

    _userInfo.mutable_moveinfo()->set_positionx(x);
    _userInfo.mutable_moveinfo()->set_positiony(y);
}

void User::SetMoveInfo(const Protocol::MoveInfo moveInfo)
{

    _userInfo.mutable_moveinfo()->CopyFrom(moveInfo);
}

void User::SetHp(unsigned int& hp)
{
    LOCK_GUARD
    _userInfo.set_hp(hp);
}

void User::UserAttacked(unsigned int damage)
{
    unsigned int hp = _userInfo.hp() - 10;
    SetHp(hp);
}





