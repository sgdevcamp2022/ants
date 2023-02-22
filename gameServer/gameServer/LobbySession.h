#pragma once
#include "PacketHandler.h"

class LobbySession 
{

public:
	LobbySession(boost::asio::io_context& io_context);

	~LobbySession();

	
	void Start();

	void RegisterSend(Protocol::S_GameEnd& packet);

private:

	

	void Connect();
	void AfterConnect(const boost::system::error_code& error);

	void RegisterReceive();

	

	void AfterSend(const boost::system::error_code& error, size_t bytes_transferred, char* sendBuffer);

	void AfterReceive(const boost::system::error_code& error, size_t length);

	boost::asio::ip::tcp::endpoint endpoint;

	boost::asio::ip::tcp::socket _socket;
	array<char, MAX_RECEIVE_BUFFER_LEN> _receiveBuffer;
	
	mutex mutexLock;
	boost::asio::io_context& _io_context;
};

extern LobbySession g_lobbySession;