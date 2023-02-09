#pragma once
#include "PacketHandler.h"



const int BUFFER_SIZE = 4096;

class CircularBuffer
{
    //재밌겠다 원형 버퍼!
    CircularBuffer(int size = BUFFER_SIZE) : _pushPoint(0), _popPoint(0), _usingSpace(0), _freeSpace(size) { _buffer.reserve(size); }

    //띵킹1
    //기본적으로 큐에 필요하 것은?

    bool Enqueue(const char* data, int dataLength)
    {
        if(dataLength>_freeSpace)
        {
            return false;
        }

        _freeSpace -= dataLength;
        _usingSpace += dataLength;

        if (dataLength>BUFFER_SIZE-_pushPoint)
        {
            int firstLength = BUFFER_SIZE - _pushPoint;
            int secondLength = dataLength - firstLength;

            memcpy(&_buffer[_pushPoint], data, firstLength);
            memcpy(&_buffer[0], data + firstLength, secondLength);
        }
        else
        {
            memcpy(&_buffer[_pushPoint], data, dataLength);
        }

        return true;
    }

    struct PacketHeader
    {
        unsigned __int16 size;
        unsigned __int16 id; 
    };
    
    //패킷 하나 빼오기
    void PopPacket()
    {
        if(_usingSpace<sizeof(PacketHeader))
        {
            //little than header
            return;
        }
        PacketHeader* header = PopHeader();

        int length = header->size;

        if(_usingSpace<length)
        {
            // completed packet is not arrive
            return;
        }

        delete header;
        Dequeue(length);
    }

    PacketHeader* PopHeader()
    {
        PacketHeader* header = new PacketHeader();
        if(BUFFER_SIZE-_popPoint<sizeof(PacketHeader))
        {
            int firstLength = BUFFER_SIZE - _popPoint;
            int secondLength = sizeof(PacketHeader) - firstLength;

            memcpy(header, &_buffer[_popPoint], firstLength);
            memcpy(header + BUFFER_SIZE - _popPoint, &_buffer[0], secondLength);
        }
        else
        {
            memcpy(&_buffer[_popPoint], header, sizeof(PacketHeader));
        }

        return header;
    }

    char* Dequeue(int packetLength)
    {
        //dequeue
        _usingSpace -= packetLength;
        //패킷 처리 끝나면 삭제하자 after receive 나 onreceive에서 ^^[][][][][][pop][][]
        char* data = new char[packetLength];

        if(BUFFER_SIZE-_popPoint<packetLength)
        {
            int firstLength = BUFFER_SIZE - _popPoint;
            int secondLength = packetLength - firstLength;

            memcpy(data, &_buffer[_popPoint], firstLength);
            memcpy(data + BUFFER_SIZE - _popPoint, &_buffer[0], secondLength);
        }
        else
        {
            memcpy(data, &_buffer[_popPoint], packetLength);
        }
        _popPoint = (_popPoint + packetLength) % BUFFER_SIZE;

        return data;
    }

    int GetBufferSize() { return _usingSpace; }
private:
    //읽는 위치 쓰는 위치는?
    int _pushPoint=0;
    int _popPoint=0;

    //여유 공간은? 사용 공간은? 끄트머리는??
    int _freeSpace = 0;
    int _usingSpace = 0;

    vector<char> _buffer;
};

