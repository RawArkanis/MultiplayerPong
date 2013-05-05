#include "Map.h"

Map::Map()
	: _width(100),
	_height(75)
{
	for (int x = 0; x < _width; x++)
	{
		_map.push_back(std::vector<TileType>());

		for (int y = 0; y < _height; y++)
		{
			if (x == 0)
				_map[x].push_back(TT_LeftWall);
			else if (x == 99)
				_map[x].push_back(TT_RightWall);
			else if (y == 0)
				_map[x].push_back(TT_TopWall);
			else if (y == 74)
				_map[x].push_back(TT_BottomWall);
			else
				_map[x].push_back(TT_Void);
		}
	}
}

Map::~Map()
{
}

TileType Map::GetTile(int x, int y)
{
	return _map[x][y];
}
