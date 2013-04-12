#include "GameScene.h"

#include <Render/RenderManager.h>

using namespace RGL;

GameScene::GameScene(std::weak_ptr<RenderManager> render, const std::string &name)
	: Scene(render, name),
    _render(render),
    _map(nullptr)
{
    SDL_Rect rect = { 0, 0, 8, 8 };
    SDL_Color color = { 255, 0, 0, 0 };

    _map.reset(new TileMap(render, 100, 75));
}

GameScene::~GameScene()
{
}

void GameScene::Update(float delta)
{
}

void GameScene::Draw()
{
	auto render = _render.lock();

	render->Clear();

    _map->Draw();

	render->Present();
}
