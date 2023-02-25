#pragma once

#include "Session.h"

class GameSession : public Session
{
public:
    GameSession(unsigned int sessionID, boost::asio::io_context& io_context, Server* server);
    virtual ~GameSession() override;
    void OnConnect() override;
    void OnDisconnect() override;
    void OnSend() override;
    void OnReceive(int numberOfBytes, char* buffer) override;
    unsigned int userId;
    shared_ptr<class Room> room;
    class Game* game;
    class PacketHandler& packetHandler;
private:

    class CircularBuffer* _buffer = nullptr;
};
