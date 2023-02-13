#include "pch.h"
#include <iostream>
#include "Client.h"

#include "Protocol.pb.h"

int main()
{
    vector<thread> workerThreads;

    for (int i = 0; i < 1000; i++)
    {
        workerThreads.emplace_back(thread([&,i]() {this_thread::sleep_for(1s);
        boost::asio::io_context io_context;

        Client client(io_context, i);

        client.Start();
        io_context.run();
            }));
    }
    
    getchar();


}
