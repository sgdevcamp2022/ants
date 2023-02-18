#pragma once


const int MAX_SESSION_COUNT = 3000;

const unsigned short PORT_NUMBER = 10006;

const int MAX_RECEIVE_BUFFER_LEN = 512;

const int MAX_PACKET_COUNT = 3000;

const int TICK_IN_A_SECOND = 30;
const float PROJECTILE_SPEED = 0.1999;

#define HANDLE_EXCEPTION \
    catch (const std::exception& exception) { \
        std::cerr << "Error: " << exception.what() << std::endl; \
        exit(1); \
    }