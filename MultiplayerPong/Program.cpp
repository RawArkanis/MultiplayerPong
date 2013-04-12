#include "Program.h"

#include <RGLManager.h>
#include <Window/WindowManager.h>
#include <Render/RenderManager.h>
#include <Input/InputManager.h>
#include <Scene/SceneManager.h>

#include "Scene/GameScene.h"

using namespace RGL;

int Program::Main(const std::vector<std::string> &args)
{
    RGLManager rgl;

    if (rgl.Initialize() != R_OK)
        return 1;

    auto window = std::make_shared<WindowManager>();
    window->Initialize(GAME_NAME, SCREEN_WIDTH, SCREEN_HEIGHT);

    auto render = std::make_shared<RenderManager>();
    render->Initialize(window);

    auto input = std::make_shared<InputManager>();
    input->Initialize();

	auto gameScene = std::make_shared<GameScene>(std::weak_ptr<RenderManager>(render), "GameScene"); 

	SceneManager sceneManager;
	sceneManager.AddScene(gameScene);
	sceneManager.ChangeCurrentScene("GameScene");

    while (!input->MustQuit())
	{
        input->Update();
		sceneManager.Update(0.0f);

		sceneManager.Draw();

		SDL_Delay(10);
	}

    render->Finish();
    window->Finish();
    rgl.Finish();

    return 0;
}

int main(int argc, char** argv)
{
    std::vector<std::string> args(argv, argv + argc);

    Program prog;
    return prog.Main(args);
}
