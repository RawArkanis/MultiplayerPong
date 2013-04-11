/*#ifndef __DMP_TILEMAP_H__
#define __DMP_TILEMAP_H__

#include <vector>

#include "Tile.h"

DMP_BEGIN_NAMESPACE

class TileMap
{
public:
    TileMap(CL_Point pos, uint cols, uint rows);
    ~TileMap();

	CL_Point generate();

	TileType getTileType(CL_Point pos);
	uint getCols();
	uint getRows();
	CL_Point getPlayerPosition();

	void movePlayerUp();
	void movePlayerDown();
	void movePlayerLeft();
	void movePlayerRight();

	void reveal();

    void update(float delta);
    void draw();

private:
	std::vector<std::vector<Tile *> > _tiles;
    std::vector<CL_Point> _avaliableTiles;
    
	CL_Point _pos;
	CL_Point _playerPos;
	uint _width;
	uint _height;
	uint _tileWidth;
	uint _tileHeight;
	uint _cols;
	uint _rows;

	Kernel *_kernel;

	CL_Sprite _tilesSprite;
};

DMP_END_NAMESPACE

#endif*/
