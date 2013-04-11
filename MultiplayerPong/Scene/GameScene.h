#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <Scene/Scene.h>

using namespace RGL;

class GameScene : public Scene
{
public:
	GameScene(std::weak_ptr<RenderManager> render, const std::string &name);
	~GameScene();

	void Update(float delta);
    void Draw();
};

#endif
