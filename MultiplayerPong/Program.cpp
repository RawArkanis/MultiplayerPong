#include "Program.h"

#include <Window/WindowManager.h>
#include <Scene/SceneManager.h>

#include "Scene/GameScene.h"

using namespace RGL;

int Program::Main(const std::vector<std::string> &args)
{
	int exit = false;
    std::shared_ptr<WindowManager> window(new WindowManager());

    window->Initialize(GAME_NAME, SCREEN_WIDTH, SCREEN_WIDTH);

	std::shared_ptr<Scene> gameScene(new GameScene(std::weak_ptr<WindowManager>(window), "GameScene")); 

	SceneManager sceneManager;
	sceneManager.AddScene(gameScene);

	while (!exit)
	{
		sceneManager.Update(0.0f);

		sceneManager.Draw();

		_sleep(1000);
	}

    window->Finish();

    return 0;
}

int main(int argc, char** argv)
{
    std::vector<std::string> args(argv, argv + argc);

    Program prog;
    return prog.Main(args);
}
