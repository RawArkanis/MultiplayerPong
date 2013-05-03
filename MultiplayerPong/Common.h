#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>
#include <sstream>

const std::string GAME_NAME = "MultiplayerPong";

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const unsigned int FPS = 15;

const unsigned int ROWS = 100;
const unsigned int COLS = 75;

const unsigned int PORT = 1111;

const char PACKAGE_HEAD = 123;
const char PACKAGE_TAIL = 125;

const char PACKAGE_TYPE_INIT = 65; // [player.id, ball.x, ball.y, ball.vx, ball.vy]
const char PACKAGE_TYPE_BALL_COLLISION = 66; // [ball.vx, ball.vy]
const char PACKAGE_TYPE_PLAYER_MOVE = 67; // [player.x, player.y]
const char PACKAGE_TYPE_PLAYER_SCORE = 68; // [player.id, ball.x, ball.y, ball.vx, ball.vy]
const char PACKAGE_TYPE_END = 69; // [player.id]

const int PACKAGE_DATA_MAX_SIZE = 15;

#endif
