#include "pch.h"
#include "Server.h"


Server::Server(boost::asio::io_context& io_context)
: _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT_NUMBER))
{
	isAccepting = false;
	
	work_guard = new work_guard_type(io_context.get_executor());
	
	for(int i=0; i< std::thread::hardware_concurrency(); i++)
	{
		workerThreads.emplace_back(thread([&]() {io_context.run();}));
	}
}

Server::~Server()
{

	delete work_guard;

	for (size_t i = 0; i < sessions.size(); ++i)
	{
		if (sessions[i]->GetSocket().is_open())
		{
			sessions[i]->GetSocket().close();
		}

		delete sessions[i];
	}
	
}

void Server::Init(const int maxSessionCount)
{
	for(int i=0;i<maxSessionCount; ++i)
	{
		Session* session = new Session(i,static_cast<boost::asio::io_context&> (_acceptor.get_executor().context()),this);
		sessions.push_back(session);
		unusedSessions.push_back(i);
	}

}

void Server::Start()
{
	cout << "Start Server!" << endl;
	RegisterAccept();
}

void Server::CloseSession(const unsigned sessionID)
{
	std::cout << "Client Disconnected. ID: " << sessionID << endl;

	sessions[sessionID]->GetSocket().close();

	unusedSessions.push_back(sessionID);
	if(isAccepting == false)
	{
		RegisterAccept();
	}
}



bool Server::RegisterAccept()
{
	if(unusedSessions.empty())
	{
		isAccepting = false;
		return false;
	}

	isAccepting = true;
	unsigned int sessionID = unusedSessions.front();
	unusedSessions.pop_front();

	_acceptor.async_accept(sessions[sessionID]->GetSocket(),
		[this,sessionID](boost::system::error_code error) { AfterAccept(sessions[sessionID], error); }
	);


	return true;
}

void Server::AfterAccept(Session* session, const boost::system::error_code& error)
{
	if (!error)
	{
		std::cout << "SessionID: " << session->GetSessionID() << std::endl;

		session->AfterConnect();

		RegisterAccept();
	}
	else
	{
		std::cout << "error No: " << error.value() << " error Message: " << error.message() << std::endl;
	}
}
