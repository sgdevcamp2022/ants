#pragma once

class Server;

class Session
{
public:
    Session(unsigned int sessionID, boost::asio::io_context& io_context, Server* server);
	virtual ~Session() = default;

	boost::asio::ip::tcp::socket& GetSocket() {	return socket; }

	unsigned int GetSessionID() {return _sessionID;}

	void Init() {}

    void RegisterReceive();

	void RegisterSend(char* buffer);
	void RegisterSend(shared_ptr<char>& buffer);

	void AfterConnect();

	virtual void OnConnect() {}
	virtual void OnDisconnect(){}
	virtual void OnSend() {}
	virtual void OnReceive(int numberOfBytes, char* buffer) {}
private:
	void AfterSend(const boost::system::error_code& error, size_t bytes_transferred, char* sendBuffer);

	void AfterSend(const boost::system::error_code& error, size_t transferredBytes, const shared_ptr<char>& sendBuffer);

	void AfterReceive(const boost::system::error_code& error, size_t bytes_transferred);

	boost::asio::ip::tcp::socket socket;
	
	array<char, MAX_RECEIVE_BUFFER_LEN> _receiveBuffer;

	unsigned int _sessionID;
	Server* _server;
};
