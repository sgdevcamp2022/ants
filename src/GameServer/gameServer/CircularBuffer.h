#pragma once
#include "PacketHandler.h"


const int BUFFER_SIZE = 4096;

#define CalcLength(point)  firstLength = BUFFER_SIZE - point; secondLength = dataLength - firstLength;
class CircularBuffer
{
public:

    CircularBuffer(int size = BUFFER_SIZE) : _pushPoint(0), _popPoint(0), _usingSpace(0), _freeSpace(size) { _buffer.resize(size); }

    bool Enqueue(char* data, int dataLength);

    //패킷 하나 빼오기
    char* PopPacket();

    char* GetHeader();

    char* Dequeue(int packetLength);

    int GetBufferSize();
private:
    void DataCopy(char* data, int dataLength);


    //읽는 위치 쓰는 위치는?
    int _pushPoint = 0;
    int _popPoint = 0;

    //여유 공간은? 사용 공간은? 끄트머리는??
    int _freeSpace = 0;
    int _usingSpace = 0;

    vector<char> _buffer;
    shared_ptr<char> remainedPacket;
    shared_ptr<char> remainedHeader;
};