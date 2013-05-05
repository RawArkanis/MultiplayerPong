#include "Program.h"

#include <RGLManager.h>
#include <Window/WindowManager.h>
#include <Render/RenderManager.h>
#include <Input/InputManager.h>
#include <Scene/SceneManager.h>
#include <Text/TextDisplay.h>

#include <TCPSock.h>

#include "Scene/ConnectionScene.h"
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

    auto sceneManager = std::make_shared<SceneManager>();

    auto sock = std::make_shared<TCPSock>();

    auto connScene = std::make_shared<ConnectionScene>(std::weak_ptr<SceneManager>(sceneManager), std::weak_ptr<RenderManager>(render),
        std::weak_ptr<InputManager>(input), "ConnectionScene", std::weak_ptr<TCPSock>(sock));
    connScene->SerIP(args[1]);
	auto gameScene = std::make_shared<GameScene>(std::weak_ptr<SceneManager>(sceneManager), std::weak_ptr<RenderManager>(render),
        std::weak_ptr<InputManager>(input), "GameScene", std::weak_ptr<TCPSock>(sock)); 

    sceneManager->AddScene(connScene);
	sceneManager->AddScene(gameScene);
	sceneManager->ChangeCurrentScene("ConnectionScene");

    int currentTime = 0, lastTime = 0;
    int deltaTime = 0;

    while (!input->MustQuit())
	{
		currentTime = SDL_GetTicks();
		deltaTime += currentTime - lastTime;
		lastTime = currentTime;

        input->Update();
		sceneManager->Update(deltaTime);

        render->Clear();

		sceneManager->Draw();

        render->Present();

		if (deltaTime >= 1000/FPS)
			deltaTime = 0;
	}

    render->Finish();
    window->Finish();
    rgl.Finish();

    return 0;
}

int main(int argc, char** argv)
{
    std::vector<std::string> args(argv, argv + argc);
    if (args.size() <= 1)
    {
        std::cerr << "Use 'MultiplayerPong <IP_Address>'" << std::endl;
        return 1;
    }

    Program prog;
    return prog.Main(args);
}
