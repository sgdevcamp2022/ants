#pragma once
#include "PacketHandler.h"


const int BUFFER_SIZE = 4096;

#define CalcLength(point)  firstLength = BUFFER_SIZE - point; secondLength = dataLength - firstLength;
class CircularBuffer
{
public:
    //재밌겠다 원형 버퍼!
    CircularBuffer(int size = BUFFER_SIZE) : _pushPoint(0), _popPoint(0), _usingSpace(0), _freeSpace(size) { _buffer.resize(size); }

    //띵킹1
    //기본적으로 큐에 필요하 것은?

    bool Enqueue(char* data, int dataLength)
    {
        if (dataLength > _freeSpace)
        {
            return false;
        }

        DataCopy(data, dataLength);

        _pushPoint = (_pushPoint + dataLength) % BUFFER_SIZE;

        _freeSpace -= dataLength;
        _usingSpace += dataLength;
        return true;
    }

    //패킷 하나 빼오기
    char* PopPacket()
    {
        if (_usingSpace < sizeof(PacketHeader))
        {
            //little than header
            return nullptr;
        }

        PacketHeader* header = reinterpret_cast<PacketHeader*>(GetHeader());

        if (_usingSpace < header->size)
        {
            return nullptr;
        }

        char* packet = Dequeue(header->size);

        return packet;
    }

    char* GetHeader()
    {
        int remainSpace = BUFFER_SIZE - _popPoint;
        char* header = nullptr;

        if (remainSpace < sizeof(PacketHeader))
        {
            header = new char[sizeof(PacketHeader)];
            memcpy(header, &_buffer[_popPoint], remainSpace);
            memcpy(header + remainSpace, (_buffer).data(), sizeof(PacketHeader) - remainSpace);
        }
        else
        {
            header = &_buffer[_popPoint];
        }

        return header;
    }

    char* Dequeue(int packetLength)
    {
        int remainSpace = BUFFER_SIZE - _popPoint;

        char* packet = nullptr;

        if (remainSpace < packetLength)
        {
            packet = new char[packetLength];
            memcpy(packet, &_buffer[_popPoint], remainSpace);
            memcpy(packet + remainSpace, (_buffer).data(), packetLength - remainSpace);
        }
        else
        {
            packet = &_buffer[_popPoint];
        }

        _popPoint = (_popPoint + packetLength) % BUFFER_SIZE;

        _usingSpace -= packetLength;
        _freeSpace += packetLength;
        if (_usingSpace == 0)
        {
            _popPoint = 0;
            _pushPoint = 0;
        }

        return packet;
    }

    int GetBufferSize() { return _usingSpace; }
private:
    void DataCopy(char* data, int dataLength)
    {
        int remainSpace = BUFFER_SIZE - _pushPoint;

        if (BUFFER_SIZE - _pushPoint < dataLength)
        {
            memcpy(&_buffer[_pushPoint], data, remainSpace);
            memcpy(_buffer.data(), data + remainSpace, dataLength - remainSpace);
        }
        else
        {
            memcpy(&_buffer[_pushPoint], data, dataLength);
        }
    }


    //읽는 위치 쓰는 위치는?
    int _pushPoint = 0;
    int _popPoint = 0;

    //여유 공간은? 사용 공간은? 끄트머리는??
    int _freeSpace = 0;
    int _usingSpace = 0;

    vector<char> _buffer;
};