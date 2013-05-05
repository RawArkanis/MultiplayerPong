#ifndef _WS_UTILS_
#define _WS_UTILS_

#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

const char PACKAGE_HEAD = 123;
const char PACKAGE_TAIL = 125;

const char PACKAGE_TYPE_INIT = 65; // [player.id, ball.x, ball.y, ball.vx, ball.vy]
const char PACKAGE_TYPE_BALL_COLLISION = 66; // [ball.vx, ball.vy]
const char PACKAGE_TYPE_PLAYER_MOVE = 67; // [player.id, player.x, player.y]
const char PACKAGE_TYPE_PLAYER_SCORE = 68; // [player.id, ball.x, ball.y, ball.vx, ball.vy]
const char PACKAGE_TYPE_END = 69; // [player.id]

const int PACKAGE_DATA_MAX_SIZE = 15;

inline std::string PrintPackage(const std::vector<char> &package)
{
	std::stringstream ss;
	std::string result;

	for (unsigned int i = 0; i < package.size(); i++)
	{
		ss << (int)package[i];
        ss << " ";
	}

	ss >> result;

	return result;
}

void Bufferize(const std::vector<char> &package, std::vector<char> &buffer)
{
	if (package.size() == 0)
		return;

	buffer.insert(buffer.end(), package.begin(), package.end());
}

void ProcessBuffer(std::vector<char> &buffer, std::vector<char> &package)
{
	std::vector<char> temp;

	if (buffer.size() == 0)
		return;

	unsigned int i = 0;
	while (i < buffer.size())
	{
		temp.push_back(buffer[i]);
		++i;

		if (temp[temp.size() - 1] == PACKAGE_TAIL)
			break;
	}

	if (temp[temp.size() - 1] == PACKAGE_TAIL)
	{
		package.swap(temp);
		buffer.erase(buffer.begin(), buffer.begin() + i);
	}
}

inline std::vector<char> MakeInitPackage(int player, int ballx, int bally, int ballvx, int ballvy)
{
    std::vector<char> package;

	package.push_back(PACKAGE_HEAD);
    package.push_back(PACKAGE_TYPE_INIT);
    package.push_back((char)5);
    package.push_back((char)player);
    package.push_back((char)ballx);
    package.push_back((char)bally);
    package.push_back((char)(ballvx + 2));
    package.push_back((char)(ballvy + 2));
    package.push_back(PACKAGE_TAIL);

    return package;
}

inline std::vector<char> MakeBallPackage(int ballx, int bally, int ballvx, int ballvy)
{
    std::vector<char> package;

    package.push_back(PACKAGE_HEAD);
    package.push_back(PACKAGE_TYPE_BALL_COLLISION);
    package.push_back((char)4);
    package.push_back((char)ballx);
    package.push_back((char)bally);
    package.push_back((char)(ballvx + 2));
	package.push_back((char)(ballvy + 2));
    package.push_back(PACKAGE_TAIL);

    return package;
}

inline std::vector<char> MakeMovePackage(int player, int playerx, int playery)
{
    std::vector<char> package;

    package.push_back(PACKAGE_HEAD);
    package.push_back(PACKAGE_TYPE_PLAYER_MOVE);
    package.push_back((char)3);
    package.push_back(player);
    package.push_back(playerx);
    package.push_back(playery);
    package.push_back(PACKAGE_TAIL);

    return package;
}

inline std::vector<char> MakeScorePackage(int player, int ballx, int bally, int ballvx, int ballvy)
{
    std::vector<char> package;

	package.push_back(PACKAGE_HEAD);
    package.push_back(PACKAGE_TYPE_PLAYER_SCORE);
    package.push_back((char)5);
    package.push_back((char)player);
    package.push_back((char)ballx);
    package.push_back((char)bally);
    package.push_back((char)(ballvx + 2));
    package.push_back((char)(ballvy + 2));
    package.push_back(PACKAGE_TAIL);

    return package;
}

inline std::vector<char> MakeEndPackage(int player)
{
    std::vector<char> package;

	package.push_back(PACKAGE_HEAD);
    package.push_back(PACKAGE_TYPE_END);
    package.push_back((char)1);
    package.push_back((char)player);
    package.push_back(PACKAGE_TAIL);

    return package;
}

inline int ParsePackage(const std::vector<char> &package, std::vector<char> &data)
{
    if (package[0] != PACKAGE_HEAD || package[package.size() - 1] != PACKAGE_TAIL ||
        package.size() != (int)package[2] + 4)
        return 0;

    int size;

    switch (package[1])
    {
    case PACKAGE_TYPE_INIT: // [player.id, ball.x, ball.y, ball.vx, ball.vy]
        if (package[2] != 5)
            return 0;
        size = 5;
        break;
    case PACKAGE_TYPE_BALL_COLLISION: // [ball.x, ball.y, ball.vx, ball.vy]
        if (package[2] != 4)
            return 0;
        size = 4;
        break;
    case PACKAGE_TYPE_PLAYER_MOVE: // [player.id, player.x, player.y]
        if (package[2] != 3)
            return 0;
        size = 3;
        break;
    case PACKAGE_TYPE_PLAYER_SCORE: // [player.id, ball.x, ball.y, ball.vx, ball.vy]
        if (package[2] != 5)
            return 0;
        size = 5;
        break;
    case PACKAGE_TYPE_END: // [player.id]
        if (package[2] != 1)
            return 0;
        size = 1;
        break;
    default:
        return 0;
        break;
    }

    for (int i = 3; i < size + 3; i++)
		data.push_back(package[i]);

    return (int)package[1];
}

inline void ParseInitData(const std::vector<char> &data, int &player, int &ballX, int &ballY, int &ballVX, int &ballVY)
{
    player = (int)data[0];
    ballX = (int)data[1];
    ballY = (int)data[2];
    ballVX = (int)data[3] - 2;
    ballVY = (int)data[4] - 2;
}

inline void ParseBallData(const std::vector<char> &data, int &ballx, int&bally, int &ballvx, int &ballvy)
{
    ballx = (int)data[0];
    bally = (int)data[1];
    ballvx = (int)data[2] - 2;
	ballvy = (int)data[3] - 2;
}

inline void ParseMoveData(const std::vector<char> &data, int &player, int&playerx, int &playery)
{
    player = (int)data[0];
    playerx = (int)data[1];
    playery = (int)data[2];
}

inline void ParseScoreData(const std::vector<char> &data, int &player, int &ballX, int &ballY, int &ballVX, int &ballVY)
{
    player = (int)data[0];
    ballX = (int)data[1];
    ballY = (int)data[2];
    ballVX = (int)data[3] - 2;
    ballVY = (int)data[4] - 2;
}

inline void ParseEndData(const std::vector<char> &data, int &player)
{
    player = (int)data[0];
}

#endif
