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
    moveInfo->set_positionx(0);
    moveInfo->set_positiony(0);

    userInfo->set_allocated_moveinfo(moveInfo);

}

User::~User()
{
    delete userInfo;
    userInfo = nullptr;

}

Protocol::UserInfo& User::GetUserInfo()
{
    return *userInfo;
}




