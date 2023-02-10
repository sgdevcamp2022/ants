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

        _freeSpace -= dataLength;
        _usingSpace += dataLength;

        DataCopy(data, dataLength, true);
        _pushPoint = (_pushPoint + dataLength) % BUFFER_SIZE;
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
        PacketHeader* header = PopHeader();
        if(header==nullptr)
        {
            return nullptr;
        }
        int length = header->size;

        if (_usingSpace < length)
        {
            delete header;
            return nullptr;
        }

        delete header;
        char* packet = Dequeue(length);

        return packet;
    }

    PacketHeader* PopHeader()
    {
        if (_usingSpace<sizeof(PacketHeader))
        {
            return nullptr;
        }
        PacketHeader* header = new PacketHeader();

        DataCopy(reinterpret_cast<char*>(header), sizeof(PacketHeader), false);

        return header;
    }

    char* Dequeue(int packetLength)
    {
        _usingSpace -= packetLength;
        _freeSpace += packetLength;

        //패킷 처리 끝나면 삭제하자 after receive 나 onreceive에서 ^^[][][][][][pop][][]
        char* data = new char[packetLength];

        DataCopy(data, packetLength, false);



        _popPoint = (_popPoint + packetLength) % BUFFER_SIZE;

        if (_usingSpace == 0)
        {
            _popPoint = 0;
            _pushPoint = 0;
        }
        return data;
    }

    int GetBufferSize() { return _usingSpace; }
private:
    void DataCopy(char* data, int dataLength, bool isPush)
    {
        int firstLength;
        int secondLength;

        if (isPush)
        {
            CalcLength(_pushPoint)

                if (BUFFER_SIZE - _pushPoint < dataLength)
                {
                    memcpy(&_buffer[_pushPoint], data, firstLength);
                    memcpy(_buffer.data(), data + firstLength, secondLength);
                }
                else
                {
                    memcpy(&_buffer[_pushPoint], data, dataLength);
                }
        }
        else
        {
            CalcLength(_popPoint)

                if (BUFFER_SIZE - _popPoint < dataLength)
                {
                    memcpy(data, &_buffer[_popPoint], firstLength);
                    memcpy((char*)data + firstLength, (_buffer).data(), secondLength);
                }
                else
                {
                    memcpy(data, &_buffer[_popPoint], dataLength);
                }
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