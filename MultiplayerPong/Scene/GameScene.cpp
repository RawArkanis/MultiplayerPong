#include "GameScene.h"
#include "../Utils.h"

#include <Render/RenderManager.h>
#include <Input/InputManager.h>

#include <TCPSock.h>

using namespace RGL;

GameScene::GameScene(std::weak_ptr<SceneManager> manager, std::weak_ptr<RenderManager> render, std::weak_ptr<InputManager> input,
    const std::string &name, std::weak_ptr<TCPSock> sock)
	: Scene(manager, render, input, name),
    _map(nullptr),
    _player1Score(nullptr),
    _player2Score(nullptr),
    _message(nullptr),
    _sock(sock),
    _state(GS_Wait),
    _id(0),
    _ballVX(0),
    _ballVY(0),
    _error(false)
{
    _map.reset(new TileMap(render, ROWS, COLS));

    SDL_Color white = { 255, 255, 255, 255 };

    _player1Score.reset(new TextDisplay(render, "Score: 0", "font.ttf", white, 12));
    _player2Score.reset(new TextDisplay(render, "Score: 0", "font.ttf", white, 12));

    _message.reset(new TextDisplay(render, "Waiting for another player...", "font.ttf", white, 16));
}

GameScene::~GameScene()
{
}

void GameScene::Update(float delta)
{
    std::string package;
    std::string data;
    auto sock = _sock.lock();

    if (_state == GS_Wait)
    {
        sock->Receive(package);
        if (package.length() > 0)
        {
            int ballx, bally;

            if (ParsePackage(package, data) != PACKAGE_TYPE_INIT)
            {
                _message->Text("Invalid package received! [" + package + "]");
                _error = true;
                return;
            }

            ParseInitData(data, _id, ballx, bally, _ballVX, _ballVY);

            SDL_Point ball = { ballx, bally };
            _map->SetEntityPosition("Ball", ball);

            _map->SetInit(true);
            _state = GS_Play;
        }
    }
    else if (_state == GS_Play)
    {
        auto input = _input.lock();

        sock->Receive(package);
        if (package.length() > 0)
        {
            if (ParsePackage(package, data) == PACKAGE_TYPE_PLAYER_MOVE)
            {
                int id, x, y;
                ParseMoveData(data, id, x, y);
                if (id == _id)
                {
                    _message->Text("Receive a move package that belong to another player! [" + package + "]");
                    _error = true;
                }
                else
                {
                    SDL_Point pos = { x, y };

                    _map->SetEntityPosition(id == 1 ? "Player1" : "Player2", pos);
                }
            }
            else
            {
                _message->Text("Invalid package received! [" + package + "]");
                _error = true;
            }
        }

        std::string player;
        int keyUP;
        int keyDOWN;

        if (_id == 1)
        {
            player = "Player1";
            keyUP = SDL_SCANCODE_W;
            keyDOWN = SDL_SCANCODE_S;
        }
        else
        {
            player = "Player2";
            keyUP = SDL_SCANCODE_I;
            keyDOWN = SDL_SCANCODE_K;
        }

        SDL_Point pos = _map->GetEntityPosition(player);
        
        bool keyPressed = false;

        if(input->KeyPress(keyUP))
        {
            _map->MoveEntity(player, MT_UP);
            keyPressed = true;
        }
        else if (input->KeyPress(keyDOWN))
        {
            _map->MoveEntity(player, MT_DOWN);
            keyPressed = true;
        }

        if (keyPressed)
        {
            SDL_Point pos2 = _map->GetEntityPosition(player);
            if (pos.y != pos2.y)
            {
                package = MakeMovePackage(_id, pos2.x, pos2.y);

                _message->Text(string_to_hex(package));
                _error = true;

                sock->Send(package);
            }
        }
    }
}

void GameScene::Draw()
{
    _map->Draw();

    SDL_Rect p1_rect = _player1Score->Rect();
    p1_rect.x += 10;
    p1_rect.y += 10;

    _player1Score->Draw(p1_rect);

    SDL_Rect p2_rect = _player2Score->Rect();
    p2_rect.x += SCREEN_WIDTH - 10 - p2_rect.w;
    p2_rect.y += 10;

    _player2Score->Draw(p2_rect);

    if (_state == GS_Wait || _error)
    {
        SDL_Rect m_rect = _message->Rect();
        m_rect.x = SCREEN_WIDTH / 2 - m_rect.w / 2;
        m_rect.y = SCREEN_HEIGHT / 2 - m_rect.h / 2;

        _message->Draw(m_rect);
    }
}
