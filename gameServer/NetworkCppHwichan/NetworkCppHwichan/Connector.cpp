#include "pch.h"
#include "Connector.h"


Connector::Connector(const char* ipAddress, const int portNumber)
    : _socket(io_context), endpoint(boost::asio::ip::address::from_string(ipAddress), portNumber)
{
    //별도의 스레드로 빼도 안전할까??
    io_context.run();
}

Connector::~Connector()
{
}

void Connector::Init(const char* ipAddress, const int portNumber)
{
}

void Connector::Start()
{
    Connect();
}

void Connector::Connect()
{
    _socket.async_connect(endpoint, [this](const boost::system::error_code error) {AfterConnect(error); });
}

void Connector::AfterConnect(const boost::system::error_code& error)
{
    if (error)
    {
        std::cout << "connect failed : " << error.message() << std::endl;
    }
    else
    {
        std::cout << "connected" << std::endl;
        RegisterReceive();
    }
}

void Connector::RegisterReceive()
{
    _socket.async_read_some(
        boost::asio::buffer(_receiveBuffer),
        [this](boost::system::error_code error, size_t transferedBytes) { AfterReceive(error, transferedBytes); }
    );
}


void Connector::RegisterSend(char* buffer)
{
   
    const int size = reinterpret_cast<PacketHeader*>(buffer)->size;
    boost::asio::async_write(
        _socket,
        boost::asio::buffer(buffer, size),
        [this, buffer](boost::system::error_code error, size_t transferredBytes) {AfterSend(error, transferredBytes, buffer); }
    );
}



void Connector::AfterSend(const boost::system::error_code& error, size_t transferredBytes, char* sendBuffer)
{
    if (sendBuffer != nullptr)
    {
        delete[] sendBuffer;
        sendBuffer = nullptr;
    }
}

void Connector::AfterReceive(const boost::system::error_code& error, size_t length)
{
    if (error)
    {
        if (error == boost::asio::error::eof)
        {
        }
        else
        {
            
            std::cout << "error No: " << error.value() << " error Message: " << error.message() << std::endl;
        }

        _socket.close();
        return;
    }
    else
    {
        // 패킷 길이 검증 하고 고성능 RecvBuffer 만들어서 관리
        RegisterReceive();
    }
}


/*
 * EXPORT
 */

Connector* CreateClient(const char* ipAddress, const int portNumber)
{
    return new Connector(ipAddress, portNumber);
}
void FreeClient(Connector* instance)
{
    delete instance;
}

void Connect(Connector* instance)
{
    instance->Connect();
}

void Send(Connector* instance, char* buffer, int bufferSize)
{
    char* packet = new char[bufferSize];
    memcpy(packet, buffer, bufferSize);
    instance->RegisterSend(packet);
}

void Receive(Connector* instance, char* buffer, int bufferSize)
{

}


int Test(Connector* instance)
{
    return 911;
}
