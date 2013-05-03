#include "Utils.h"
#include "Entity/Entity.h"

#include <TCPSock.h>

enum GameState
{
    GS_WAIT,
    GS_PLAY
};

void ProcessMovement(const std::string &data, Entity &player, TCPSock *sock);

int main(int argc, char **argv)
{
    TCPSock sconn;
    TCPSock *sc1, *sc2;

    GameState state = GS_WAIT;

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

    Entity ball(0, 49, 37, 1, 1);

    int ballVX = rand() % 2 == 0 ? 1 : 5;
    int ballVY = rand() % 5 + 1;

    Entity player1(1, 2, 2, 1, 12);
    Entity player2(2, 97, 61, 1, 12);

    int ballX, ballY;
    ball.GetPosition(ballX, ballY);

    std::string package_p1(MakeInitPackage(1, ballX, ballY, ballVX, ballVY));
    std::string package_p2(MakeInitPackage(2, ballX, ballY, ballVX, ballVY));
    std::string data;

    std::cout << "Sending INIT pack to C1: " << string_to_hex(package_p1) << std::endl;
    std::cout << "Sending INIT pack to C2: " << string_to_hex(package_p2) << std::endl;

    sc1->Send(package_p1);
    sc2->Send(package_p2);

    int lastTime = GetTickCount();

    while (true)
    {
        std::string pack_c1;
        std::string pack_c2;

	    sc1->Receive(pack_c1);
        sc2->Receive(pack_c2);

        if (pack_c1.length() > 0)
        {
            std::cout << "Received data from C1: " << string_to_hex(pack_c1) << std::endl;
            if (ParsePackage(pack_c1, data) == PACKAGE_TYPE_PLAYER_MOVE)
            {
                ProcessMovement(data, player1, sc2);
            }
        }

        if (pack_c2.length() > 0)
        {
            std::cout << "Received data from C2: " << string_to_hex(pack_c2) << std::endl;
            if (ParsePackage(pack_c2, data) == PACKAGE_TYPE_PLAYER_MOVE)
            {
               ProcessMovement(data, player2, sc1);
            }
        }

        while (GetTickCount() - lastTime < 1000 / FPS)
            Sleep(0);
        lastTime = GetTickCount();
    }

    return 0;
}

void ProcessMovement(const std::string &data, Entity &player, TCPSock *sock)
{
    int id, x, y;
    ParseMoveData(data, id, x, y);

    if (id != player.GetID())
        std::cout << "WARN: C" << player.GetID() << " send a move package as another player!" << std::endl;
    else
    {
        player.SetPosition(x, y);

        std::string msg(MakeMovePackage(id, x, y));

        std::cout << "Sending MOVE pack to C2: " << string_to_hex(msg) << std::endl;

        sock->Send(msg);
    }
}
