#include "pch.h"
#include "LobbySession.h"

LobbySession::LobbySession(boost::asio::io_context& io_context)
    : _socket(io_context), endpoint(boost::asio::ip::address::from_string(LOBBY_SERVER_IP), LOBBY_PORT_NUMBER), _io_context(io_context)
{
   
}

LobbySession::~LobbySession()
{
    if (_socket.is_open())
    {
        _socket.close();
    }
}


void LobbySession::Start()
{
    Connect();
}


void LobbySession::Connect()
{
    _socket.async_connect(endpoint, [this](const boost::system::error_code error) {AfterConnect(error); });
}

void LobbySession::AfterConnect(const boost::system::error_code& error)
{
    if (error)
    {
        std::cout << "connect failed : " << error.message() << std::endl;
    }
    else
    {
        std::cout << "connected" << std::endl;

        //RegisterSend();
    }
}

void LobbySession::RegisterReceive()
{
    _socket.async_read_some(
        boost::asio::buffer(_receiveBuffer),
        [this](boost::system::error_code error, size_t transferedBytes) { AfterReceive(error, transferedBytes); }
    );
}
void LobbySession::RegisterSend(Protocol::S_GameEnd& packet)
{

    LOCK_GUARD;
    unsigned int size = packet.ByteSizeLong();

    char* buffer = new char[packet.ByteSizeLong()];

    packet.SerializeToArray(buffer,size );

    boost::asio::async_write(_socket, boost::asio::buffer(buffer, size),
        [this, buffer](boost::system::error_code error, size_t transferredBytes) {AfterSend(error, transferredBytes, buffer); });

    cout << "send!" << endl;
}


void LobbySession::AfterSend(const boost::system::error_code& error, size_t transferredBytes, char* sendBuffer)
{
    if (sendBuffer != nullptr)
    {
        delete[] sendBuffer;
        sendBuffer = nullptr;
    }


}

void LobbySession::AfterReceive(const boost::system::error_code& error, size_t length)
{
    if (error)
    {
        if (error == boost::asio::error::eof)
        {
            // 접속 종료, 대기 상태의 패킷도 보내게 한다면 필요 있는데 흠..
        }
        else
        {
            //또다른 에러 발생
            std::cout << "error No: " << error.value() << " error Message: " << error.message() << std::endl;
        }

        _socket.close();
        return;
    }
    else
    {
    }
        
}