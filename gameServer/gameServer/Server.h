#pragma once
#include "Session.h"


using work_guard_type = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;


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
	

	work_guard_type* work_guard=nullptr;

	boost::asio::ip::tcp::acceptor _acceptor;
	
    vector<Session*> sessions;
	deque<unsigned int> unusedSessions;

	bool isAccepting;

	vector<std::thread> workerThreads;
	
};

