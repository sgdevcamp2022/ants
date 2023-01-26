#pragma once

class Server;

const int MAX_RECEIVE_BUFFER_LEN = 512;

class Session
{
public:
	Session(unsigned int sessionID, boost::asio::io_context& io_context, Server* server);


	boost::asio::ip::tcp::socket& GetSocket() {	return socket; }

	unsigned int GetSessionID() {return _sessionID;}

	void Init() {}

	void RegisterReceive();

	void RegisterSend(const int nSize, char* pData);


	void AfterConnect();

	virtual void OnSend() {}
	virtual void OnReceive() {}
private:
	

	void AfterSend(const boost::system::error_code& error, size_t bytes_transferred);

	void AfterReceive(const boost::system::error_code& error, size_t bytes_transferred);



	boost::asio::ip::tcp::socket socket;
	
	std::array<char, MAX_RECEIVE_BUFFER_LEN> _receiveBuffer;

	std::deque< char* > m_SendDataQueue;


	unsigned int _sessionID;
	Server* _server;
};
