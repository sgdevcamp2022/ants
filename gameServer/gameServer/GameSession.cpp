#include "pch.h"
#include "GameSession.h"

#include "PacketHandler.h"

GameSession::GameSession(unsigned sessionID, boost::asio::io_context& io_context, Server* server): Session(sessionID,io_context,server)
{
    
}

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
    PacketHandler& packetHandler = PacketHandler::GetPacketHandler();
    packetHandler.HandlePacket(this, buffer, numberOfBytes);

}
