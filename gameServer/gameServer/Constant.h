#pragma once

const char LOBBY_SERVER_IP[] = "172.30.1.10";
const unsigned short LOBBY_PORT_NUMBER = 8005;
const int MAX_SESSION_COUNT = 3000;

const unsigned short PORT_NUMBER = 10006;

const int MAX_RECEIVE_BUFFER_LEN = 512;

const int MAX_PACKET_COUNT = 3000;

const int TICK_IN_A_SECOND = 30;
const float PROJECTILE_SPEED = 0.399;

#define HANDLE_EXCEPTION \
    catch (const std::exception& exception) { \
        std::cerr << "Error: " << exception.what() << std::endl; \
        exit(1); \
    }