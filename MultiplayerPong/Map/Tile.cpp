#include "Tile.h"

Tile::Tile(TileType type)
: _tileType(type)
{
}

Tile::~Tile()
{}

TileType Tile::GetTileType() const
{
	return _tileType;
}

void Tile::SetTileType(TileType type)
{
	_tileType = type;
}
