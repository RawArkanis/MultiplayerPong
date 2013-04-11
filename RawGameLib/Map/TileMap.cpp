/*#include "TileMap.h"

DMP_BEGIN_NAMESPACE

TileMap::TileMap(CL_Point pos, uint cols, uint rows)
: _pos(pos), _cols(cols), _rows(rows)
{
	_kernel = Kernel::getInstance();

	_tiles.reserve(cols);
    for (uint i = 0; i < _cols; i++)
        _tiles[i].reserve(rows);
    _avaliableTiles.reserve(cols*rows);

	_tilesSprite = CL_Sprite(_kernel->getGraphicContext(), "tileset", &_kernel->getResourceManager());

	_tileWidth = _tilesSprite.get_width();
	_tileHeight = _tilesSprite.get_height();
	_width = cols * _tileWidth;
	_height = rows * _tileHeight;

	_playerPos = CL_Point(0,0);
}

TileMap::~TileMap()
{}

CL_Point TileMap::generate()
{
	for (uint i = 0; i < _cols; i++)
    {
        _tiles.push_back(std::vector<Tile *>());
    
        for (uint j = 0; j < _rows; j++)
        {
            _tiles[i].push_back(new Tile(Ground));
            _avaliableTiles.push_back(CL_Point(i, j));
        }
    }

	_playerPos = CL_Point(1,1);

	reveal();

	return getPlayerPosition();
}

TileType TileMap::getTileType(CL_Point pos)
{
	return _tiles[pos.x][pos.y]->getTileType();
}

uint TileMap::getCols()
{
	return _cols;
}

uint TileMap::getRows()
{
	return _rows;
}

CL_Point TileMap::getPlayerPosition()
{
	return CL_Point(_playerPos.x*_tileWidth+_pos.x,_playerPos.y*_tileHeight+_pos.y);
}

void TileMap::movePlayerUp()
{
	if (_playerPos.y - 1 >= 0)
	{
		_playerPos.y--;
		reveal();
	} // TODO terminar de colocar os reveals
}

void TileMap::movePlayerDown()
{
	if (_playerPos.y + 1 < _cols)
		_playerPos.y++;
}

void TileMap::movePlayerLeft()
{
	if (_playerPos.x - 1 >= 0)
		_playerPos.x--;
}

void TileMap::movePlayerRight()
{
	if (_playerPos.x + 1 < _rows)
		_playerPos.x++;
}

void TileMap::reveal()
{
	for (int i = -1; i < 2; i++) // TODO, arrumar de acordo com a posição do player e se existir a posição player
		for (int j = -1; j < 2; j++)
			_tiles[i][j]->setVisited(true);
}

void TileMap::update(float delta)
{}

void TileMap::draw()
{
	for(uint y = 0; y < _rows; y++)
	{
		for(uint x = 0; x < _cols; x++)
		{
			uint spriteIndex = (int)(_tiles[x][y]->isVisited() ? _tiles[x][y]->getTileType() : Void);

			int xPositionScreen = _pos.x + x * _tileWidth;
			int yPositionScreen = _pos.y + y * _tileHeight;

			_tilesSprite.set_frame(spriteIndex);
			_tilesSprite.draw(_kernel->getGraphicContext(), xPositionScreen, yPositionScreen); 
		}
	}
}

DMP_END_NAMESPACE*/
