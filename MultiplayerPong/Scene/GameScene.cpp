#include "GameScene.h"

#include <Render/RenderManager.h>

GameScene::GameScene(std::weak_ptr<RenderManager> render, const std::string &name)
	: Scene(render, name)
{
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

	render->Present();
}
