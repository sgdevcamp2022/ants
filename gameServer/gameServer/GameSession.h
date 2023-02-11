#pragma once

#include "Session.h"

class GameSession : public Session
{
public:
    GameSession(unsigned int sessionID, boost::asio::io_context& io_context, Server* server);
    ~GameSession() override{}
    void OnConnect() override;
    void OnDisconnect() override;
    void OnSend() override;
    void OnReceive(int numberOfBytes, char* buffer) override;
    //Room포인터 두는 것 고려, (있어야 락 최소화 가능)

    class User* user = nullptr;
    class Room* room=nullptr;
    class PacketHandler& packetHandler;
    class CircularBuffer* _buffer = nullptr;
};

