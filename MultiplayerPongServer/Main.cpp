#include <cmath>

#include <TCPSock.h>
#include <Utils.h>

#include "Entity/Entity.h"
#include "Map/Map.h"

enum GameState
{
    GS_READY,
    GS_WAIT,
    GS_PLAY
};

void ProcessPackage(std::vector<char> &buffer, std::vector<char> &package);

void ProcessMovement(const std::vector<char> &data, Entity &player, TCPSock *sock);

void ProcessBallMovement(Entity &ball, Map &map, Entity &p1, Entity &p2, int &ballVX, int &ballVY, int &scoreP1, int &scoreP2, TCPSock *sock_c1, TCPSock *sock_c2);

int main(int argc, char **argv)
{
    TCPSock sconn;
    TCPSock *sc1, *sc2;

    GameState state = GS_READY;

	std::vector<char> buffer1, buffer2;

    if(sconn.Open() != WS_OK)
    {
		std::cerr << "Error open sock c1: " << sconn.GetLastError() << std::endl;
        return 1;
    }

    if(sconn.SetOption(SOL_SOCKET, SO_REUSEADDR, 1, 4) != WS_OK)
    {
		std::cerr << "Error setopt sock c1: " << sconn.GetLastError() << std::endl;
        return 1;
    }

	if(sconn.Bind(1111) != WS_OK)
    {
		std::cerr << "Error bind sock c1: " << sconn.GetLastError() << std::endl;
        return 1;
    }

    if(sconn.Listen() != WS_OK)
    {
        std::cerr << "Error listen sock c1: " << sconn.GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Waiting for Client 1..." << std::endl;

    sc1 = sconn.Accept();

    if(sc1 == nullptr)
    {
        std::cerr << "Error accept sock c1: " << sconn.GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Waiting for Client 2..." << std::endl;

    sc2 = sconn.Accept();

    if(sc2 == nullptr)
    {
        std::cerr << "Error accept sock c2: " << sconn.GetLastError() << std::endl;
        return 1;
    }

	sc1->SetIOMode(FIONBIO, 1);
    sc2->SetIOMode(FIONBIO, 1);

    srand(GetTickCount());

	Map map;

    Entity ball(0, 0, 0, BALL_SIZE, BALL_SIZE);

    Entity player1(1, 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT);
    Entity player2(2, 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT);

    int ballVX = 0;
    int ballVY = 0;

    int scoreP1 = 0;
    int scoreP2 = 0;

    bool p1Ready = false;
    bool p2Ready = false; 

    int lastTime = 0;
	int currentTime = 0, deltaTime = 0;

    bool ended = false;

    while (true)
    {
		currentTime = GetTickCount();
		deltaTime += currentTime - lastTime;
		lastTime = currentTime;

        std::vector<char> pack_c1;
        std::vector<char> pack_c2;

	    sc1->Receive(pack_c1);
        sc2->Receive(pack_c2);

		Bufferize(pack_c1, buffer1);
		Bufferize(pack_c2, buffer2);

		pack_c1.clear();
		pack_c2.clear();

		ProcessBuffer(buffer1, pack_c1);
		ProcessBuffer(buffer2, pack_c2);

        if (pack_c1.size() > 0)
        {
			std::vector<char> data;

            std::cout << "Received data from C1: " << PrintPackage(pack_c1) << std::endl;

            switch (ParsePackage(pack_c1, data))
            {
            case PACKAGE_TYPE_PLAYER_MOVE:
                if (state == GS_PLAY)
                    ProcessMovement(data, player1, sc2);
                break;
            
            case PACKAGE_TYPE_READY:
                if (state == GS_READY)
                    p1Ready = true;
                break;
            }
        }

        if (pack_c2.size() > 0)
        {
			std::vector<char> data;

            std::cout << "Received data from C2: " << PrintPackage(pack_c2) << std::endl;

            switch (ParsePackage(pack_c2, data))
            {
            case PACKAGE_TYPE_PLAYER_MOVE:
                if (state == GS_PLAY)
                    ProcessMovement(data, player2, sc1);
                break;

            case PACKAGE_TYPE_READY:
                if (state == GS_READY)
                    p2Ready = true;
                break;
            }
        }

        if (state == GS_READY && p1Ready && p2Ready)
        {
            ball.SetPosition(BALL_X, BALL_Y);

            player1.SetPosition(PLAYER1_X, PLAYER1_Y);
            player2.SetPosition(PLAYER2_X, PLAYER2_Y);

            ballVX = rand() % 2 == 0 ? -2 : 2;
            ballVY = rand() % 5 - 2;

            scoreP1 = 0;
            scoreP2 = 0;

            int ballX, ballY;
            ball.GetPosition(ballX, ballY);

            std::vector<char> package_p1(MakeInitPackage(1, ballX, ballY));
            std::vector<char> package_p2(MakeInitPackage(2, ballX, ballY));

            std::cout << "Sending INIT pack to C1: " << PrintPackage(package_p1) << std::endl;
            std::cout << "Sending INIT pack to C2: " << PrintPackage(package_p2) << std::endl;

            sc1->Send(package_p1);
            sc2->Send(package_p2);

            p1Ready = false;
            p2Ready = false;

            state = GS_PLAY;
        }

		if (deltaTime >= 1000/FPS)
		{
			if (state == GS_PLAY)
                ProcessBallMovement(ball, map, player1, player2, ballVX, ballVY, scoreP1, scoreP2, sc1, sc2);

            if (scoreP1 >= MAX_SCORE || scoreP2 >= MAX_SCORE)
                state = GS_READY;

			deltaTime = 0;
		}
    }

    return 0;
}

void ProcessMovement(const std::vector<char> &data, Entity &player, TCPSock *sock)
{
    int id, x, y;
    ParseMoveData(data, id, x, y);

    if (id != player.GetID())
        std::cout << "WARN: C" << player.GetID() << " send a move package as another player!" << std::endl;
    else
    {
        player.SetPosition(x, y);

        std::vector<char> msg(MakeMovePackage(id, x, y));

        std::cout << "Sending MOVE pack to C2: " << PrintPackage(msg) << std::endl;

        sock->Send(msg);
    }
}

void ProcessBallMovement(Entity &ball, Map &map, Entity &p1, Entity &p2, int &ballVX, int &ballVY, int &scoreP1, int &scoreP2, TCPSock *sock_c1, TCPSock *sock_c2)
{
	int x, y;
	ball.GetPosition(x, y);

    int xSignal = ballVX == 0 ? 0 : ballVX > 0 ? 1 : -1;
    int ySignal = ballVY == 0 ? 0 : ballVY > 0 ? 1 : -1;

    int xSteps = abs(ballVX);
    int ySteps = abs(ballVY);
    int steps = max(xSteps, ySteps);

    int score = 0;

    for (int i = 0; i < steps; i++)
    {
        int x0 = x;
        int y0 = y;

        int ix = xSteps > i ? 1 : 0;
        int iy = ySteps > i ? 1 : 0;

        x += ix * xSignal;
        y += iy * ySignal;

        switch (map.GetTile(x, y)) // check if collided
		{
		case TT_TopWall:
		case TT_BottomWall:
			ballVY = -ballVY;
            x += ix * xSignal;
            y = y0;
			break;

		case TT_LeftWall:
            score = 2;
            ballVX = -ballVX;
            x = x0;
            y += iy * ySignal;
			break;

		case TT_RightWall:
            score = 1;
			ballVX = -ballVX;
            x = x0;
            y += iy * ySignal;
			break;
        
        default:
            int val1 = p1.CheckBallCollision(x, y);
            int val2 =  p2.CheckBallCollision(x, y);
            int val = -3;

            if (val1 != -3)
                val = val1;
            else if (val2 != -3)
                val = val2;
                
            if (val != -3)         
            {
                ballVX = -ballVX;
                x = x0;
                y += iy * ySignal;

                int vy = ballVY + val;
                if (vy < -2)
                    vy = -2;
                else if (vy > 2)
                    vy = 2;
                ballVY = vy;
            }
            break;
		}

        xSignal = ballVX == 0 ? 0 : ballVX > 0 ? 1 : -1;
        ySignal = ballVY == 0 ? 0 : ballVY > 0 ? 1 : -1;
    }

	ball.SetPosition(x, y);

	if(score == 0)
	{
		std::vector<char> msg(MakeBallPackage(x, y));

        std::cout << "Sending BALL pack to C1 and C2: " << PrintPackage(msg) << std::endl;

        sock_c1->Send(msg);
		sock_c2->Send(msg);
	}
    else
    {
        int s;

        if (score == 1)
        {
            scoreP1++;
            s = scoreP1;
        }
        else
        {
            scoreP2++;
            s = scoreP2;
        }

        if (s < MAX_SCORE)
        {
            int bx = BALL_X;
            int by = BALL_Y;
            ballVX = rand() % 2 == 0 ? -2 : 2;
            ballVY = rand() % 5 -2;

            ball.SetPosition(bx, by);

            std::vector<char> msg(MakeScorePackage(score, bx, by));

            std::cout << "Sending SCORE pack to C1 and C2: " << PrintPackage(msg) << std::endl;

            sock_c1->Send(msg);
		    sock_c2->Send(msg);
        }
        else
        {
            std::vector<char> msg(MakeEndPackage(score));

            std::cout << "Sending END pack to C1 and C2: " << PrintPackage(msg) << std::endl;

            sock_c1->Send(msg);
		    sock_c2->Send(msg);
        }
    }
}
