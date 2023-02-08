#pragma once
#include "Session.h"


using work_guard_type = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;


class Client
{
public:
	Client(boost::asio::io_context& io_context);
		
	~Client();
	
	void Init(const int maxSessionCount);
	void Start();

	void Connect();
	void AfterConnect(const boost::system::error_code& error);


	void RegisterReceive();

	void RegisterSend();
	//void RegisterSend();

	void AfterSend(const boost::system::error_code& error, size_t bytes_transferred, char* sendBuffer);

	void AfterSend(const boost::system::error_code& error, size_t transferredBytes, const shared_ptr<char>& sendBuffer);

	void AfterReceive(const boost::system::error_code& error, size_t length);
	
private:
	boost::asio::ip::tcp::endpoint endpoint;
	int _seqNumber;
	boost::asio::ip::tcp::socket _socket;
	array<char, MAX_RECEIVE_BUFFER_LEN> _receiveBuffer;
};

