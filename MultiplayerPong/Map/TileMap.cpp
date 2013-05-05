#include "TileMap.h"

using namespace RGL;

TileMap::TileMap(std::weak_ptr<RenderManager> render, int cols, int rows)
    : _render(render),
    _tileWidth(8),
    _tileHeight(8),
    _cols(cols),
    _rows(rows),
    _init(false)
{
    generate();
    buildSquares();
	buildPlayerAndBall();
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

void TileMap::buildPlayerAndBall()
{
	SDL_Point player1 = { 2, 2 };
	_entityPosition["Player1"] = player1;

	SDL_Point player2 = { 97, 61 };
	_entityPosition["Player2"] = player2;

	SDL_Point ball = { 0, 0 };
	_entityPosition["Ball"] = ball;
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

void TileMap::SetEntityPosition(std::string name, SDL_Point point)
{
    _entityPosition[name] = point;
}

SDL_Point TileMap::GetEntityPosition(std::string name)
{
    return _entityPosition[name];
}

void TileMap::MoveEntity(std::string name, MoveType type)
{
    int bottom = 73;
    if (name == "Player1" || name == "Player2")
        bottom -= 11;

	switch (type)
	{
	case MT_UP:
		_entityPosition[name].y = _entityPosition[name].y - 1 >= 1 ? _entityPosition[name].y - 1 : _entityPosition[name].y;
		break;
	case MT_LEFT:
		_entityPosition[name].x = _entityPosition[name].x - 1 >= 1 ? _entityPosition[name].x - 1 : _entityPosition[name].x;
		break;
	case MT_DOWN:
		_entityPosition[name].y = _entityPosition[name].y + 1 <= bottom ? _entityPosition[name].y + 1 : _entityPosition[name].y;
		break;
	case MT_RIGHT:
		_entityPosition[name].x = _entityPosition[name].x + 1 <= 98 ? _entityPosition[name].x + 1 : _entityPosition[name].x;
		break;
	}
}

void TileMap::SetInit(bool value)
{
    _init = value;
}

void TileMap::Update(float delta)
{

}

void TileMap::Draw()
{
	SDL_Point ball = _entityPosition["Ball"];
	SDL_Rect rect = { ball.x * _tileWidth, ball.y * _tileHeight, _tileWidth, _tileHeight };
	_squares[TT_BallBrick]->Draw(rect);

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

    if (_init)
    {
	    SDL_Point player1 = _entityPosition["Player1"];
	    for (int i = player1.y; i < player1.y + 12; i++)
	    {
		    SDL_Rect rect = { player1.x * _tileWidth, i * _tileHeight, _tileWidth, _tileHeight };
		    _squares[TT_Player1Brick]->Draw(rect);
	    }
	
	    SDL_Point player2 = _entityPosition["Player2"];
	    for (int i = player2.y; i < player2.y + 12; i++)
	    {
		    SDL_Rect rect = { player2.x * _tileWidth, i * _tileHeight, _tileWidth, _tileHeight };
		    _squares[TT_Player2Brick]->Draw(rect);
	    }
    }
}
