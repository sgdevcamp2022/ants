#include "pch.h"
#include "GameSession.h"

void GameSession::OnConnect()
{
    Session::OnConnect();

    //세션 관리하는 곳에 this 추가
}

void GameSession::OnSend()
{
    Session::OnSend();
    //없어도 될 것 같음
}

void GameSession::OnReceive(int numberOfBytes, char* buffer)
{
    Session::OnReceive(numberOfBytes, buffer);
    //패킷 유효성 검사 길이가 짧 거나 잘못됐으면 그냥 무시 
    //패킷 처리
    

}
