#include "pch.h"
#include "CircularBuffer.h"

bool CircularBuffer::Enqueue(char* data, int dataLength)
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

char* CircularBuffer::PopPacket()
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

char* CircularBuffer::GetHeader()
{
    int remainSpace = BUFFER_SIZE - _popPoint;
    char* header = nullptr;

    if (remainSpace < sizeof(PacketHeader))
    {
        header = new char[sizeof(PacketHeader)];
        memcpy(header, &_buffer[_popPoint], remainSpace);
        memcpy(header + remainSpace, (_buffer).data(), sizeof(PacketHeader) - remainSpace);
        remainedHeader = std::shared_ptr<char>(header, std::default_delete<char[]>());
    }
    else
    {
        header = &_buffer[_popPoint];
    }

    return header;
}

char* CircularBuffer::Dequeue(int packetLength)
{
    int remainSpace = BUFFER_SIZE - _popPoint;

    char* packet = nullptr;

    if (remainSpace < packetLength)
    {
        packet = new char[packetLength];
        memcpy(packet, &_buffer[_popPoint], remainSpace);
        memcpy(packet + remainSpace, (_buffer).data(), packetLength - remainSpace);
        remainedPacket = std::shared_ptr<char>(packet, std::default_delete<char[]>());
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

int CircularBuffer::GetBufferSize()
{
    return _usingSpace;
}

void CircularBuffer::DataCopy(char* data, int dataLength)
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
