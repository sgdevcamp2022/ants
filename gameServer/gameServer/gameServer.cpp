#include "pch.h"

#include "Server.h"

#include "Protocol.pb.h"


int main()
{
	boost::asio::io_context io_context;

    Server server(io_context);
    server.Init(MAX_SESSION_COUNT);

    server.Start();

    Protocol::S_TEST pkt;
    pkt.set_id(1000);
    pkt.set_hp(100);
    pkt.set_attack(1);

    Protocol::BuffData* buf = pkt.add_buffs();
    buf->set_buffid(100);
    buf->set_remaintime(10.1f);
    buf->add_victims(12);



    // 패킷 구조체에 데이터 넣고 버퍼에 넣어주기, 앞 쪽에 헤더 넣고
    // 그리고 센드
    

    getchar();
    
    
    
}
