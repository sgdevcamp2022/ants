#pragma once
#include "Session.h"


const unsigned short PORT_NUMBER = 10006;

class Server
{
public:
	Server(boost::asio::io_context& io_context);

		
	~Server();
	
	void Init(const int maxSessionCount);
	void Start();

	void CloseSession(const unsigned int sessionID);

private:

	bool RegisterAccept();

	void AfterAccept(Session* session, const boost::system::error_code& error);
	


	boost::asio::ip::tcp::acceptor _acceptor;
	
    vector<Session*> sessions;
	deque<unsigned int> unusedSessions;

	bool isAccepting;
	
};

