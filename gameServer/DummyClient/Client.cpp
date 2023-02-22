#include "pch.h"
#include "Client.h"

#include "Protocol.pb.h"


Client::Client(boost::asio::io_context& io_context, int number)
: _seqNumber(0),_socket(io_context), endpoint(boost::asio::ip::address::from_string(SERVER_IP), PORT_NUMBER)
{
    a = number;
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
    this_thread::sleep_for(100ms);
    ++_seqNumber;

   /* Protocol::S_GameEnd packet;

    packet.set_messagetype(7);
    packet.set_winnerid("2");
    packet.add_userid("1");
    packet.add_userid("2");
    packet.add_userid("3");


    unsigned int size = packet.ByteSizeLong();

    char* buffer = new char[packet.ByteSizeLong()];

    packet.SerializeToArray(buffer,size );*/


    /*****************************************************************/


    
    if (_seqNumber > 10)
    {
        _socket.close();
        return;
    }

        char* buffer = nullptr;
        if (_seqNumber == 1)
        {
            Protocol::M_InitRoom packet;
            packet.set_roomid(ROOM_ID);

            for(int i= 0; i <2;  i++)
            {
                packet.add_userid(USER_ID + i);
            }
            
            
            buffer = MakeBuffer(packet, M_InitRoom);

        }
        else if (_seqNumber == 2)
        {
            return;
            this_thread::sleep_for(1s);
            Protocol::C_EnterRoom packet;
            packet.set_userid(USER_ID+a+1);
            packet.set_name("hwichan");
            packet.set_roomid(ROOM_ID+a);
            buffer = MakeBuffer(packet, C_EnterRoom);
            
        }
        else if (_seqNumber == 3)
        {
            this_thread::sleep_for(1s);
            Protocol::C_Move packet;
            Protocol::MoveInfo* moveInfo = new Protocol::MoveInfo();
            moveInfo->set_direction(Protocol::NONE);
            moveInfo->set_positionx(-462.23);
            moveInfo->set_positiony(-347.3);
            packet.set_allocated_moveinfo(moveInfo);
            //packet.mutable_moveinfo()->set_positionx(1);
            buffer = MakeBuffer(packet, C_Move);

        }
        else if(_seqNumber==4)
        {
            this_thread::sleep_for(1s);
            Protocol::C_Move packet;
            Protocol::MoveInfo* moveInfo = new Protocol::MoveInfo();
            moveInfo->set_direction(Protocol::RIGHT);
            moveInfo->set_positionx(-462.23);
            moveInfo->set_positiony(-347.3);
            packet.set_allocated_moveinfo(moveInfo);
            //packet.mutable_moveinfo()->set_positionx(1);
            buffer = MakeBuffer(packet, C_Move);
        }
        else if(_seqNumber==5)
        {
            this_thread::sleep_for(1s);
            Protocol::C_Move packet;
            Protocol::MoveInfo* moveInfo = new Protocol::MoveInfo();
            moveInfo->set_direction(Protocol::NONE);
            moveInfo->set_positionx(-459.23);
            moveInfo->set_positiony(-347.3);
            packet.set_allocated_moveinfo(moveInfo);
            //packet.mutable_moveinfo()->set_positionx(1);
            buffer = MakeBuffer(packet, C_Move);
        }
        else if(_seqNumber==6)
        {
            this_thread::sleep_for(1s);
            Protocol::C_Move packet;
            Protocol::MoveInfo* moveInfo = new Protocol::MoveInfo();
            moveInfo->set_direction(Protocol::UP);
            moveInfo->set_positionx(-459.23);
            moveInfo->set_positiony(-347.3);
            packet.set_allocated_moveinfo(moveInfo);
            //packet.mutable_moveinfo()->set_positionx(1);
            buffer = MakeBuffer(packet, C_Move);
        }
        else if(_seqNumber==7)
        {
            this_thread::sleep_for(1s);
            Protocol::C_Move packet;
            Protocol::MoveInfo* moveInfo = new Protocol::MoveInfo();
            moveInfo->set_direction(Protocol::NONE);
            moveInfo->set_positionx(-459.23);
            moveInfo->set_positiony(-344.3);
            packet.set_allocated_moveinfo(moveInfo);
            //packet.mutable_moveinfo()->set_positionx(1);
            buffer = MakeBuffer(packet, C_Move);
        }
        else if(_seqNumber==8)
        {
            this_thread::sleep_for(1s);
            Protocol::C_Move packet;
            Protocol::MoveInfo* moveInfo = new Protocol::MoveInfo();
            moveInfo->set_direction(Protocol::LEFT);
            moveInfo->set_positionx(-462.23);
            moveInfo->set_positiony(-344.3);
            packet.set_allocated_moveinfo(moveInfo);
            //packet.mutable_moveinfo()->set_positionx(1);
            buffer = MakeBuffer(packet, C_Move);
        }
        else if(_seqNumber==9)
        {
            this_thread::sleep_for(1s);
            Protocol::C_Move packet;
            Protocol::MoveInfo* moveInfo = new Protocol::MoveInfo();
            moveInfo->set_direction(Protocol::NONE);
            moveInfo->set_positionx(-462.23);
            moveInfo->set_positiony(-344.3);
            packet.set_allocated_moveinfo(moveInfo);
            //packet.mutable_moveinfo()->set_positionx(1);
            buffer = MakeBuffer(packet, C_Move);
        }
        else if(_seqNumber==10)
        {
            this_thread::sleep_for(1s);
            Protocol::C_Move packet;
            Protocol::MoveInfo* moveInfo = new Protocol::MoveInfo();
            moveInfo->set_direction(Protocol::DOWN);
            moveInfo->set_positionx(-462.23);
            moveInfo->set_positiony(-344.3);
            packet.set_allocated_moveinfo(moveInfo);
            //packet.mutable_moveinfo()->set_positionx(1);
            buffer = MakeBuffer(packet, C_Move);
            _seqNumber = 2;
        }
        else if(_seqNumber==11){}
        else if (_seqNumber == 12)
        {
            Protocol::C_Attack packet;
            packet.set_directionx(1.0f);
            packet.set_directiony(0.0f);
            cout << "attack" << endl;
            return ;
            buffer = MakeBuffer(packet, C_Attack);
            _seqNumber = 2;
        }
        else
        {
            return;
        }

        if(buffer==nullptr)
        {
            return;
        }
        const int size = reinterpret_cast<PacketHeader*>(buffer)->size;

        boost::asio::async_write(_socket, boost::asio::buffer(buffer, size),
            [this, buffer](boost::system::error_code error, size_t transferredBytes) {AfterSend(error, transferredBytes, buffer); });

        
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
        auto data = reinterpret_cast<PacketHeader*>( _receiveBuffer.data());
        if(data->id==S_RoomCompleted)
        {
            Protocol::S_RoomCompleted packet;
            PARSE(packet);
            cout<<"roomid: " << packet.roomid() << "  ,  is completed: " << packet.iscompleted() << endl;
        }
        else if(data->id == S_StartGame)
        {
            Protocol::UserInfo packet;
            PARSE(packet);
            cout << "userid: " << packet.userid()<< " , direction:" << packet.mutable_moveinfo()->direction() << " , state: " << packet.state() << endl;
        }
        else if(data->id == S_Move)
        {
            Protocol::S_Move packet;
            PARSE(packet);
            cout << "userID: " << packet.userid() << " , position: " << packet.moveinfo().positionx() << " , " << packet.moveinfo().positiony() << endl;
        }
        else if (data->id == S_MoveAdvanced)
        {
            Protocol::S_MoveAdvanced packet;
            PARSE(packet);
            cout << "userID: " << packet.move(0).userid() << " , position: " << packet.move(0).moveinfo().positionx() << " , " << packet.move(0).moveinfo().positionx() << endl;
            
        }
        else if(data->id == S_AttackAdvanced)
        {
           /* Protocol::S_AttackAdvanced packet;
            PARSE(packet);
            cout <<"Some Attack : " << packet.attack(0).userid() << packet.attack(0).directionx() << packet.attack(0).directiony() << endl;
            */
        }
        else if (data->id == S_Attacked)
        {
            Protocol::S_Attacked packet;
            PARSE(packet);
            cout << "user id: " << packet.userid(0) << " in attacked" << endl;
           

        }
        else if (data->id == S_Dead)
        {
            Protocol::S_Dead packet;
            PARSE(packet);
            cout << "userid: " << packet.userid(0) << " Dead!"  << endl;
            return;
        }
        else
        {
            return;
        }
        RegisterSend();
        RegisterReceive();
    }
}