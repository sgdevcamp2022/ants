#pragma once

#include "Session.h"

class GameSession : public Session
{
public:
    ~GameSession() override {}
    void OnConnect() override;
    void OnSend() override;
    void OnReceive(int numberOfBytes, char* buffer) override;
};

