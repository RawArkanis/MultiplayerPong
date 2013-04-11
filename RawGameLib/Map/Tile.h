/*#ifndef __DMP_TILE_H__
#define __DMP_TILE_H__

#include "../Kernel.h"

DMP_BEGIN_NAMESPACE

enum TileType {
	Void = 0,
	Explored = 1,
	Ground = 2,
	Water = 3,
	Stone = 7
};

class Tile
{
public:
	Tile(TileType type);
	~Tile();

	TileType getTileType() const;
	void setTileType(TileType type);

	bool isVisited();
	void setVisited(bool val);

private:
	TileType _tileType;
	bool _isVisited;

	Kernel *_kernel;
};

DMP_END_NAMESPACE

#endif*/
