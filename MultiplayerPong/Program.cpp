#include "Program.h"

#include <Window/WindowManager.h>
#include <Input/InputManager.h>
#include <Scene/SceneManager.h>

#include "Scene/GameScene.h"

using namespace RGL;

int Program::Main(const std::vector<std::string> &args)
{
	int exit = false;
    std::shared_ptr<WindowManager> window(new WindowManager());

    window->Initialize(GAME_NAME, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	InputManager input;

	std::shared_ptr<Scene> gameScene(new GameScene(std::weak_ptr<WindowManager>(window), "GameScene")); 

	SceneManager sceneManager;
	sceneManager.AddScene(gameScene);
	sceneManager.ChangeCurrentScene("GameScene");

	while (!input.MustQuit())
	{
		input.Update();
		sceneManager.Update(0.0f);

		sceneManager.Draw();

		SDL_Delay(500);
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
