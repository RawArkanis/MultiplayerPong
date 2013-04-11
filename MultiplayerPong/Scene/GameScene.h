#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <Scene/Scene.h>

#include "../Common.h"
#include "../Entity/Square.h"

class GameScene : public RGL::Scene
{
public:
	GameScene(std::weak_ptr<RGL::RenderManager> render, const std::string &name);
	~GameScene();

	void Update(float delta);
    void Draw();

private:
    Square *_square;
};

#endif
