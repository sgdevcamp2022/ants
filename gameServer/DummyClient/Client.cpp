#include "pch.h"
#include "Client.h"

#include "Protocol.pb.h"


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

    ++_seqNumber;
    if (_seqNumber > 10)
    {
        _socket.close();
        return;
    }
    for (int i = 0; i < 10; i++)
    {


        char* buffer = nullptr;
        if (_seqNumber == 1)
        {
            Protocol::M_InitRoom packet;
            packet.set_roomid(ROOM_ID);
            packet.add_userid(USER_ID);
            buffer = MakeBuffer(packet, M_InitRoom);

        }
        else if (_seqNumber == 2)
        {
            Protocol::C_EnterRoom packet;
            packet.set_userid(USER_ID);
            packet.set_name("hwichan");
            packet.set_roomid(ROOM_ID);
            buffer = MakeBuffer(packet, C_EnterRoom);
        }
        else if (_seqNumber == 3)
        {
            Protocol::C_Move packet;
            Protocol::MoveInfo* moveInfo = new Protocol::MoveInfo();
            moveInfo->set_direction(Protocol::DOWN);
            moveInfo->set_positionx(_seqNumber + 1);
            moveInfo->set_positiony(_seqNumber + 1);
            moveInfo->set_state(Protocol::MOVE);
            packet.set_allocated_moveinfo(moveInfo);
            //packet.mutable_moveinfo()->set_positionx(1);
            buffer = MakeBuffer(packet, C_Move);
        }
        else if (_seqNumber == 4)
        {
            Protocol::C_Attack packet;
            packet.set_directionx(3.0f);
            packet.set_directiony(2.0f);

            buffer = MakeBuffer(packet, C_Attack);
        }
        else if (_seqNumber == 5)
        {
            Protocol::C_Attacked packet;
            packet.set_userid(USER_ID);

            buffer = MakeBuffer(packet, C_Attacked);
        }
        else
        {
            return;
        }

        const int size = reinterpret_cast<PacketHeader*>(buffer)->size;

        boost::asio::async_write(_socket, boost::asio::buffer(buffer, size),
            [this, buffer](boost::system::error_code error, size_t transferredBytes) {AfterSend(error, transferredBytes, buffer); });
    }
}


void Client::AfterSend(const boost::system::error_code& error, size_t transferredBytes, char* sendBuffer)
{
    if (sendBuffer != nullptr)
    {
        delete[] sendBuffer;
        sendBuffer = nullptr;
    }

    RegisterReceive();
}

void Client::AfterReceive(const boost::system::error_code& error, size_t length)
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
        auto data = _receiveBuffer.data();
        if(_seqNumber==1)
        {
            Protocol::S_RoomCompleted packet;
            PARSE(packet);
            cout<<"roomid: " << packet.roomid() << "  ,  is completed: " << packet.iscompleted() << endl;
        }
        else if(_seqNumber==2)
        {
            Protocol::UserInfo packet;
            PARSE(packet);
            cout << "userid: " << packet.userid()<< " , direction:" << packet.mutable_moveinfo()->direction() << " , state: " << packet.mutable_moveinfo()->state() << endl;
        }
        else if(_seqNumber==3)
        {
            Protocol::S_Move packet;
            PARSE(packet);
            cout << "userID: " << packet.userid() << " , position: " << packet.moveinfo().positionx() << " , " << packet.moveinfo().positiony() << endl;
        }
        else if(_seqNumber==4)
        {
            Protocol::S_Attack packet;
            PARSE(packet);
            cout << packet.userid() << packet.directionx() << packet.directiony() << endl;
        }
        else if (_seqNumber==5)
        {
            Protocol::S_Attacked packet;
            PARSE(packet);
            cout << "user id: " << packet.userid() << " in attacked" << endl;
        }
        else
        {
            ;
        }
        RegisterSend();
    }
}