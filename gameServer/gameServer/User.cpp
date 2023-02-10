#include "pch.h"
#include "User.h"

User::User(unsigned userID, string name, GameSession* session):_userID(userID),_name(name),_session(session)
{
    userInfo = new Protocol::UserInfo;

    userInfo->set_userid(userID);
    userInfo->set_name(name);

    Protocol::MoveInfo* moveInfo = new Protocol::MoveInfo;

    moveInfo->set_state(Protocol::IDLE);
    moveInfo->set_direction(Protocol::DOWN);
    moveInfo->set_positionx(0);
    moveInfo->set_positiony(0);

}

Protocol::UserInfo& User::GetUserInfo()
{
    return *userInfo;
}




