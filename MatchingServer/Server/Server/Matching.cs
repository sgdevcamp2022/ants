using Google.Protobuf;
using Google.Protobuf.Protocol;
using ServerCore;
using System;
using System.Collections.Generic;
using System.Text;

namespace Server
{
    
    class Matching
    {
		List<ClientSession> _sessions = new List<ClientSession>();

		//참고
		JobQueue _jobQueue = new JobQueue();
		List<ArraySegment<byte>> _pendingList = new List<ArraySegment<byte>>();

		public void Push(Action job)
		{
			_jobQueue.Push(job);
		}

		public void Flush()
		{
			foreach (ClientSession s in _sessions)
				s.Send(_pendingList);
			//Console.WriteLine($"Flushed {_pendingList.Count} items");
			_pendingList.Clear();
		}


		public void Broadcast(ArraySegment<byte> segment)
		{
			_pendingList.Add(segment);
		}

		public void Enter(ClientSession session)
		{
			// 플레이어 추가하고
			_sessions.Add(session);
			session.matching = this;

			//메세지 보내기
			S_Chat chat = new S_Chat()
			{
				Context = $"{session.SessionId} is enter the matching Sever\nCurrent waiter is {_sessions.Count}"
			};
			session.Send(chat);
			//_pendingList.Add(new ArraySegment<byte>(sendBuffer));
		}

        public void Leave(ClientSession session)
        {
            // 플레이어 제거하고
            _sessions.Remove(session);
        }

		public void checkAwaiter()
        {
            if (_sessions.Count==5)
            {
                Console.WriteLine("jackPot");
            }
		}

        //public void Move(ClientSession session, C_Move packet)
        //{
        //	// 좌표 바꿔주고
        //	session.PosX = packet.posX;
        //	session.PosY = packet.posY;
        //	session.PosZ = packet.posZ;

        //	// 모두에게 알린다
        //	S_BroadcastMove move = new S_BroadcastMove();
        //	move.playerId = session.SessionId;
        //	move.posX = session.PosX;
        //	move.posY = session.PosY;
        //	move.posZ = session.PosZ;
        //	Broadcast(move.Write());
        //}
    }


}
