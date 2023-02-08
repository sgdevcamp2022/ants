#include "pch.h"
#include "Client.h"

#include "GameSession.h"
#include "PacketHandler.h"


Client::Client(boost::asio::io_context& io_context)
: _seqNumber(0),_socket(io_context), endpoint(boost::asio::ip::address::from_string(SERVER_IP), PORT_NUMBER)
{
	

	

}

Client::~Client()
{
	

		
}

void Client::Init(const int maxSessionCount)
{

}

void Client::Start()
{
	cout << "Start Client!" << endl;
    Connect();
}

void Client::Connect()
{
    _socket.async_connect(endpoint, [this](const boost::system::error_code error) {AfterConnect(error); });
}

void Client::AfterConnect(const boost::system::error_code& error)
{
	if (error)
	{
		std::cout << "connect failed : " << error.message() << std::endl;
	}
	else
	{
		std::cout << "connected" << std::endl;

        RegisterSend();
	}
}

void Client::RegisterReceive()
{


    _socket.async_read_some(
        boost::asio::buffer(_receiveBuffer),
        [this](boost::system::error_code error, size_t transferedBytes) { AfterReceive(error, transferedBytes); }

    );
}
void Client::RegisterSend()
{
    //네트워크에서 send는 보내는 것 뿐이야, 그렇다면 비즈니스 로직에서 어떠한 큐에 데이터를 넣고, 그 데이터를 꺼내서 전송을 하겠지 그러면 이 함수는 그냥 센드야

    ++_seqNumber;
    if (_seqNumber > 10)
    {
        _socket.close();
        return;
    }
    PacketHandler& ph = PacketHandler::GetPacketHandler();


    char* buffer = nullptr;
    if(_seqNumber ==1)
    {
        Protocol::M_InitRoom packet;
        packet.set_roomid(ROOM_ID);
        packet.add_userid(USER_ID);
        buffer = ph.MakeBuffer(packet,M_InitRoom);

    }
    else
    {
        Protocol::M_InitRoom packet;
        packet.set_roomid(ROOM_ID);
        packet.add_userid(USER_ID);
        buffer = ph.MakeBuffer(packet, M_InitRoom);
    }
    

    const int size = reinterpret_cast<PacketHeader*>(buffer)->size;
    /*boost::asio::async_write(
        socket,
        boost::asio::buffer(buffer, size),
        [this, buffer](boost::system::error_code error, size_t transferredBytes) {AfterSend(error, transferredBytes, buffer); }
    );*/

    boost::asio::async_write(_socket, boost::asio::buffer(buffer, size),
        [this, buffer](boost::system::error_code error, size_t transferredBytes) {AfterSend(error, transferredBytes, buffer); });
}

//
//void Client::RegisterSend()
//{
    
//
//    shared_ptr<char> buffer;
//
//
//    const int size = reinterpret_cast<PacketHeader*>(buffer.get())->size;
//    boost::asio::async_write(
//        socket,
//        boost::asio::buffer(buffer.get(), size),
//        [this, buffer](boost::system::error_code error, size_t transferredBytes) {AfterSend(error, transferredBytes, buffer); }
//    );
//}


void Client::AfterSend(const boost::system::error_code& error, size_t transferredBytes, char* sendBuffer)
{
    if (sendBuffer != nullptr)
    {
        delete[] sendBuffer;
        sendBuffer = nullptr;
    }

    RegisterReceive();
}

void Client::AfterReceive(const boost::system::error_code& error, size_t transferredBytes)
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
        cout << _receiveBuffer.data() << endl;
        //RegisterSend();
    }
}