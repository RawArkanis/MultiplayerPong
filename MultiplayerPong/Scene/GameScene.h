#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <Scene/Scene.h>
#include <Text/TextDisplay.h>

#include "../Common.h"
#include "../Map/TileMap.h"

class TCPSock;

enum GameState {
    GS_Wait,
    GS_Play,
    GS_Win,
    GS_Lose
};

class GameScene : public RGL::Scene
{
public:
	GameScene(std::weak_ptr<RGL::SceneManager> manager, std::weak_ptr<RGL::RenderManager> render, std::weak_ptr<RGL::InputManager> input, const std::string &name, std::weak_ptr<TCPSock> sock);
	~GameScene();

	void Update(float delta);
    void Draw();

private:
    std::unique_ptr<TileMap> _map;

    std::unique_ptr<RGL::TextDisplay> _player1Score;
    std::unique_ptr<RGL::TextDisplay> _player2Score;

    std::unique_ptr<RGL::TextDisplay> _message;

    std::weak_ptr<TCPSock> _sock;

    GameState _state;

    int _id;
    int _ballVX;
    int _ballVY;

    bool _error;
};

#endif
