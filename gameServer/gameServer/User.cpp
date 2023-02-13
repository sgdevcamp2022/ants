#include "pch.h"
#include "User.h"

User::User(unsigned userID, string name, GameSession* session):_userID(userID),_name(name),_session(session),hp(100)
{
    userInfo = new Protocol::UserInfo;

    userInfo->set_userid(userID);
    userInfo->set_name(name);
    userInfo->set_hp(100);
    Protocol::MoveInfo* moveInfo = new Protocol::MoveInfo;

    moveInfo->set_state(Protocol::IDLE);
    moveInfo->set_direction(Protocol::DOWN);
    moveInfo->set_positionx(0.f);
    moveInfo->set_positiony(0.f);

    userInfo->set_allocated_moveinfo(moveInfo);

}

User::~User()
{
    delete userInfo;
    userInfo = nullptr;

}

const Protocol::UserInfo& User::GetUserInfo()
{
    return *userInfo;
}

Protocol::UserInfo User::CopyUserInfo()
{
    return *userInfo;
}


unsigned int User::GetUserId()
{
    return userInfo->userid();
}

string User::GetName()
{
    return userInfo->name();
}

const Protocol::MoveInfo& User::GetReferenceMoveInfo()
{
    return userInfo->moveinfo();
}

void User::SetUserId(const unsigned int id)
{
    LOCK_GUARD
    userInfo->set_userid(id);
}

void User::SetName(const string name)
{
    LOCK_GUARD
    userInfo->set_name(name);
}

void User::SetPosition(const float& x, const float& y)
{
    LOCK_GUARD
    userInfo->mutable_moveinfo()->set_positionx(x);
    userInfo->mutable_moveinfo()->set_positiony(y);
}

void User::SetMoveInfo(const Protocol::MoveInfo& moveInfo)
{
    LOCK_GUARD
    userInfo->mutable_moveinfo()->CopyFrom(moveInfo);
}

void User::SetHp(const int& hp)
{
    LOCK_GUARD
    userInfo->set_hp(hp);
}





