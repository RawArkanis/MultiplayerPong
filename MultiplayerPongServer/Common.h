#ifndef __MPS_COMMON_H__
#define __MPS_COMMON_H__

const int FPS = 15;

const char PACKAGE_HEAD = 123;
const char PACKAGE_TAIL = 125;

const char PACKAGE_TYPE_INIT = 65; // [player.id, ball.x, ball.y, ball.vx, ball.vy]
const char PACKAGE_TYPE_BALL_COLLISION = 66; // [ball.vx, ball.vy]
const char PACKAGE_TYPE_PLAYER_MOVE = 67; // [player.id, player.x, player.y]
const char PACKAGE_TYPE_PLAYER_SCORE = 68; // [player.id, ball.x, ball.y, ball.vx, ball.vy]
const char PACKAGE_TYPE_END = 69; // [player.id]

const int PACKAGE_DATA_MAX_SIZE = 15;

#endif
