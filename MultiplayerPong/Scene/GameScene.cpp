#include "GameScene.h"

#include <Render/RenderManager.h>

using namespace RGL;

GameScene::GameScene(std::weak_ptr<RenderManager> render, const std::string &name)
	: Scene(render, name)
{
    SDL_Rect rect = { 0, 0, 8, 8 };
    SDL_Color color = { 255, 0, 0, 0 };

    _square = new Square(render, rect, color);
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

    _square->Draw();

	render->Present();
}
