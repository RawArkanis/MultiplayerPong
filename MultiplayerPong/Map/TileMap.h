#ifndef __DMP_TILEMAP_H__
#define __DMP_TILEMAP_H__

#include <vector>
#include <map>

#include <Render/RenderManager.h>

#include "Tile.h"
#include "../Entity/Square.h"

enum MoveType
{
    MT_UP,
    MT_RIGHT,
    MT_DOWN,
    MT_LEFT
};

class TileMap
{
public:
    TileMap(std::weak_ptr<RGL::RenderManager> render, int cols, int rows);
    ~TileMap();

	TileType GetTileType(const SDL_Point &pos);
	int GetCols();
	int GetRows();

    void SetEntityPosition(std::string name, SDL_Point point);
	SDL_Point GetEntityPosition(std::string name);

	void MoveEntity(std::string name, MoveType type);

    void SetInit(bool value);

    void Update(float delta);
    void Draw();

private:
    std::weak_ptr<RGL::RenderManager> _render;

	int _tileWidth;
	int _tileHeight;
	int _cols;
	int _rows;

    std::vector<std::vector<std::shared_ptr<Tile> > > _tiles;
    std::map<TileType, std::shared_ptr<Square> > _squares;
    std::map<std::string, SDL_Point> _entityPosition;

    bool _init;

    void generate();
    void buildSquares();
	void buildPlayerAndBall();

};

#endif
