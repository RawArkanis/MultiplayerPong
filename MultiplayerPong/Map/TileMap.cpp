#include "TileMap.h"

using namespace RGL;

TileMap::TileMap(std::weak_ptr<RenderManager> render, int cols, int rows)
    : _render(render),
    _tileWidth(8),
    _tileHeight(8),
    _cols(cols),
    _rows(rows)
{
    generate();
    buildSquares();
}

TileMap::~TileMap()
{}

void TileMap::generate()
{
    /*_tiles.reserve(_cols);
    for (int i = 0; i < _cols; i++)
        _tiles[i].reserve(_rows);*/

	for (int i = 0; i < _cols; i++)
    {
        _tiles.push_back(std::vector<std::shared_ptr<Tile> >());
    
        for (int j = 0; j < _rows; j++)
        {
            if (j == 0 || j == _rows - 1 || i == 0 || i == _cols - 1)
                _tiles[i].push_back(std::make_shared<Tile>(TT_WallBrick));
            else
                _tiles[i].push_back(std::make_shared<Tile>(TT_VoidBrick));
        }
    }
}

void TileMap::buildSquares()
{
    SDL_Color wallColor = { 255, 0, 0, 255 };
    SDL_Color player1Color = { 0, 255, 0, 255 };
    SDL_Color player2Color = { 0, 0, 255, 255 };
    SDL_Color ballColor = { 255, 255 , 0, 255 };

    SDL_Rect rect = { 0, 0, _tileWidth, _tileHeight };

    _squares[TT_VoidBrick] = nullptr;
    _squares[TT_WallBrick] = std::make_shared<Square>(_render, rect, wallColor);
    _squares[TT_Player1Brick] = std::make_shared<Square>(_render, rect, player1Color);;
    _squares[TT_Player2Brick] = std::make_shared<Square>(_render, rect, player2Color);;
    _squares[TT_BallBrick] = std::make_shared<Square>(_render, rect, ballColor);;
}

TileType TileMap::GetTileType(const SDL_Point &pos)
{
	return _tiles[pos.x][pos.y]->GetTileType();
}

int TileMap::GetCols()
{
	return _cols;
}

int TileMap::GetRows()
{
	return _rows;
}

void TileMap::MoveEntity(std::string name, MoveType type)
{

}

void TileMap::Update(float delta)
{

}

void TileMap::Draw()
{
	for(int y = 0; y < _rows; y++)
	{
		for(int x = 0; x < _cols; x++)
		{
            if (_tiles[x][y]->GetTileType() == TT_VoidBrick)
                continue;
            
            SDL_Rect rect = { x * _tileWidth, y * _tileHeight, _tileWidth, _tileHeight };

            _squares[_tiles[x][y]->GetTileType()]->Draw(rect);
		}
	}
}
