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
    ;
    delete _buffer;
}

void GameSession::OnConnect()
{
    Session::OnConnect();
    user = new User(0,"null",this);

    //세션 관리하는 곳에 this 추가
}

void GameSession::OnDisconnect()
{
    Session::OnDisconnect();

    /*if(user !=nullptr)
    {
        delete user;
    }*/
    User* user = nullptr;

    // 메모리 테스트용 Room 삭제
    if(room!=nullptr)
    {
        RoomManager::DeleteRoom(room);
    }
    
    Room* room = nullptr;
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
