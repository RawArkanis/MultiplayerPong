#ifndef __MPS_MAP_H__
#define __MPS_MAP_H__

#include <vector>

#include "../Common.h"

enum TileType
{
	TT_Void,
	TT_TopWall,
	TT_LeftWall,
	TT_BottomWall,
	TT_RightWall
};

class Map
{
public:
	Map();
	~Map();

	TileType GetTile(int x, int y);

private:
	int _width;
	int _height;

	std::vector<std::vector<TileType> > _map;
};

#endif
