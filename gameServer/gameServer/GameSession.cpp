#include "pch.h"
#include "GameSession.h"

#include "CircularBuffer.h"
#include "PacketHandler.h"

GameSession::GameSession(unsigned sessionID, boost::asio::io_context& io_context, Server* server):
Session(sessionID,io_context,server), packetHandler(PacketHandler::GetPacketHandler())
{
    _buffer = new CircularBuffer();
}

GameSession::~GameSession()
{
    delete _buffer;
}

void GameSession::OnConnect()
{
    Session::OnConnect();


    //세션 관리하는 곳에 this 추가
}

void GameSession::OnDisconnect()
{
    Session::OnDisconnect();

    if(room==nullptr)
    {
        return;
    }
    room->Leave(userId);
    userId = NULL;
    game = nullptr;
    room = nullptr;
}

void GameSession::OnSend()
{
    Session::OnSend();
    //없어도 될 것 같음
}

void GameSession::OnReceive(int numberOfBytes, char* buffer)
{
    Session::OnReceive(numberOfBytes, buffer);

    _buffer->Enqueue(buffer, numberOfBytes);

    char* packet =_buffer->PopPacket();
    while(packet !=nullptr)
    {
        packetHandler.HandlePacket(this, buffer, numberOfBytes);
        packet = _buffer->PopPacket();
    }
    
    

}
