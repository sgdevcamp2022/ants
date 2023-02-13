#pragma once

using work_guard_type = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;


#define PARSE(packet) if(!packet.ParseFromArray(&data[1], length - sizeof(PacketHeader))) {return;}

struct PacketHeader
{
	unsigned __int16 size;
	unsigned __int16 id; // 프로토콜ID (ex. 1=로그인, 2=이동요청)
};

enum :unsigned int
{
	M_InitRoom = 1000,
	S_RoomCompleted = 1001,

	M_TEST = 1999,

	C_EnterRoom = 2000,
	S_StartGame = 2001,

	C_UserInfo = 2002,
	S_UserInfo = 2003,

	C_Move = 2004,
	S_Move = 2005,

	C_Attack = 2006,
	S_Attack = 2007,

	C_Attacked = 2008,
	S_Attacked = 2009,

	S_Dead = 2010,

	C_TEST = 2999,

};



class Client
{
public:
	Client(boost::asio::io_context& io_context, int number);
		
	~Client();
	
	void Init(const int maxSessionCount);
	void Start();

	void Connect();
	void AfterConnect(const boost::system::error_code& error);


	void RegisterReceive();

	void RegisterSend();

	void AfterSend(const boost::system::error_code& error, size_t bytes_transferred, char* sendBuffer);

	void AfterReceive(const boost::system::error_code& error, size_t length);

	template<typename T>
	char* MakeBuffer(T& packet, unsigned int pakcetID)
	{
		const unsigned __int16 dataLength = packet.ByteSizeLong();
		const unsigned __int16 packetLength = dataLength + sizeof(PacketHeader);

		char* sendBuffer = new char[packetLength];
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer);
		header->size = packetLength;
		header->id = pakcetID;
		packet.SerializeToArray(&header[1], dataLength);

		return sendBuffer;
	}

private:
	boost::asio::ip::tcp::endpoint endpoint;
	int _seqNumber;
	boost::asio::ip::tcp::socket _socket;
	array<char, MAX_RECEIVE_BUFFER_LEN> _receiveBuffer;
	int a;
	bool test=false;
};

