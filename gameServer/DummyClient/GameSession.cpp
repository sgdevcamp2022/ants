#include "pch.h"
#include "GameSession.h"

#include "PacketHandler.h"

GameSession::GameSession(unsigned sessionID, boost::asio::io_context& io_context, Server* server): Session(sessionID,io_context,server)
{
    
}

void GameSession::OnConnect()
{
    Session::OnConnect();

    //세션 관리하는 곳에 this 추가
}

void GameSession::OnSend()
{
    Session::OnSend();
    //없어도 될 것 같음
}

void GameSession::OnReceive(int numberOfBytes, char* buffer)
{
    Session::OnReceive(numberOfBytes, buffer);
    PacketHandler& packetHandler= PacketHandler::GetPacketHandler();
    packetHandler.HandlePacket(this, buffer, numberOfBytes);
    
    //패킷 유효성 검사 길이가 짧 거나 잘못됐으면 그냥 무시 
    //패킷 처리

    // /*test*/
    //PacketHandler& temp = PacketHandler::GetPacketHandler();
    ///*cout << _receiveBuffer.data() << endl;

    //temp.Handle_M_TEST( static_cast<GameSession*>(this), nullptr, 0);*/

    ///*test end*/
    //RoomManager& roomManager = RoomManager::GetRoomManager();
    //Room* room = roomManager.MakeRoom(11);

    //User* user = new User(123, "hwichan", this);
    //this->user = user;
    //room->Enter(user);
    //room->AddUserID(123);

    ////Handle_C_EnterRoom test
    //Protocol::C_Move packet;

    //Protocol::MoveInfo moveinfo;
    //moveinfo.set_positionx(2);
    //moveinfo.set_positiony(2);
    //moveinfo.set_state(Protocol::MOVE);
    //*(packet.mutable_moveinfo()) = moveinfo;

    //this->room = room;
    //auto tempbuffer = temp.MakeBuffer_sharedPtr(packet, C_Move);

    //const int size = reinterpret_cast<PacketHeader*>(tempbuffer.get())->size;

    //temp.Handle_C_Move(this, tempbuffer.get(), size);
    //test end

}
