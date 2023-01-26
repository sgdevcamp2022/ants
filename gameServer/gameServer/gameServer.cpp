#include "pch.h"

#include "Server.h"

const int MAX_SESSION_COUNT = 100;


int main()
{
	boost::asio::io_context io_context;


    Server server(io_context);
    server.Init(MAX_SESSION_COUNT);
    
}
