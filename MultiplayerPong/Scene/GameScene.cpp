#include "GameScene.h"

GameScene::GameScene(std::weak_ptr<WindowManager> window, const std::string &name)
	: Scene(window, name)
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
}
