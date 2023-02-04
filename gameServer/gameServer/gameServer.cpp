#include "pch.h"

#include "Server.h"



int main()
{
	boost::asio::io_context io_context;

    Server server(io_context);
    server.Init(MAX_SESSION_COUNT);

    server.Start();


    getchar();
    
    
    
}
