#ifndef __UTILS_H__
#define __UTILS_H__

#include "Common.h"

#include <sstream>

std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

inline std::string MakeMovePackage(char player, char playerx, char playery)
{
    std::string package;
    std::stringstream ss;

    ss << PACKAGE_HEAD;
    ss << PACKAGE_TYPE_PLAYER_MOVE;
    ss << (char)3;
    ss << player;
    ss << playerx;
    ss << playery;
    ss << PACKAGE_TAIL;
    ss >> package;

    return package;
}

inline int ParsePackage(const std::string &package, std::string &data)
{
    if (package[0] != PACKAGE_HEAD || package[package.length() - 1] != PACKAGE_TAIL ||
        package.length() != (int)package[2] + 4)
        return 0;

    std::stringstream ss;
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
        ss << package[i];
    
    ss >> data;

    return (int)package[1];
}

inline void ParseInitData(const std::string &data, int &player, int &ballX, int &ballY, int &ballVX, int &ballVY)
{
    player = (int)data[0];
    ballX = (int)data[1];
    ballY = (int)data[2];
    ballVX = (int)data[3] - 3;
    ballVY = (int)data[4] - 3;
}

inline void ParseMoveData(const std::string &data, int &player, int&playerx, int &playery)
{
    player = (int)data[0];
    playerx = (int)data[1];
    playery = (int)data[2];
}

#endif
