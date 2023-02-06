#pragma once

#include "Session.h"

class GameSession : public Session
{
public:
    ~GameSession() override {}
    void OnConnect() override;
    void OnSend() override;
    void OnReceive(int numberOfBytes, char* buffer) override;
    //Room포인터 두는 것 고려, (있어야 락 최소화 가능)
};

