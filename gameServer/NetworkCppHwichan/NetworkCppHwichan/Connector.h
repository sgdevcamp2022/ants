#pragma once
#ifdef DLLPROJECT_EXPORTS
#   define EXPORT __declspec(dllexport)
#else
#   define EXPORT __declspec(dllimport)
#endif

#pragma once

#include <boost/bind.hpp>
#include <boost/asio.hpp>

const int MAX_SESSION_COUNT = 100;

const char SERVER_IP[] = "127.0.0.1";
const unsigned short PORT_NUMBER = 10006;

const int MAX_RECEIVE_BUFFER_LEN = 512;

const int MAX_PACKET_COUNT = 3000;


const int ROOM_ID = 11;
const int USER_ID = 55;


using namespace std;
using work_guard_type = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;


#define PARSE(packet) if(!packet.ParseFromArray(data + sizeof(PacketHeader), length - sizeof(PacketHeader))) {return;}

struct PacketHeader
{
	unsigned __int16 size;
	unsigned __int16 id; // 프로토콜ID (ex. 1=로그인, 2=이동요청)
};


class Connector
{
public:
	Connector(const char* ipAddress, const int portNumber);

	~Connector();

	void Init(const char* ipAddress, const int portNumber);
	void Start();

	void Connect();
	void AfterConnect(const boost::system::error_code& error);


	void RegisterReceive();

	void RegisterSend(char* buffer);

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

	boost::asio::io_context io_context;
	boost::asio::ip::tcp::endpoint endpoint;
	boost::asio::ip::tcp::socket _socket;
	array<char, MAX_RECEIVE_BUFFER_LEN> _receiveBuffer;
};

extern "C" EXPORT Connector* CreateClient(const char* ipAddress, const int portNumber);
extern "C" EXPORT void FreeClient(Connector* instance);
extern "C" EXPORT void Connect(Connector* instance);

extern "C" EXPORT void Send(Connector* instance,char* buffer, int bufferSize);

extern "C" EXPORT void Receive(Connector* instance, char* buffer, int bufferSize);

extern "C" EXPORT int Test(Connector * instance);