#ifndef __TILE_H__
#define __TILE_H__

enum TileType {
	TT_VoidBrick,
	TT_WallBrick,
	TT_Player1Brick,
	TT_Player2Brick,
	TT_BallBrick
};

class Tile
{
public:
	Tile(TileType type);
	~Tile();

	TileType GetTileType() const;
	void SetTileType(TileType type);

private:
	TileType _tileType;
};

#endif
