#include "pch.h"
#include <iostream>
#include "Client.h"

#include "Protocol.pb.h"

int main()
{
    this_thread::sleep_for(1s);
    boost::asio::io_context io_context;

    Client client(io_context);

    client.Start();
    io_context.run();

    getchar();

    

}
