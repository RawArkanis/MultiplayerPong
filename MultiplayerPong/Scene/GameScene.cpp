#include "GameScene.h"

#include <Render/RenderManager.h>
#include <Input/InputManager.h>

#include <TCPSock.h>
#include <Utils.h>

using namespace RGL;

GameScene::GameScene(std::weak_ptr<SceneManager> manager, std::weak_ptr<RenderManager> render, std::weak_ptr<InputManager> input,
    const std::string &name, std::weak_ptr<TCPSock> sock)
	: Scene(manager, render, input, name),
    _map(nullptr),
    _player1Score(nullptr),
    _player2Score(nullptr),
    _message(nullptr),
    _sock(sock),
    _state(GS_Ready),
    _id(0),
    _scoreP1(0),
    _scoreP2(0),
    _error(false)
{
    _map.reset(new TileMap(render, ROWS, COLS));

    SDL_Color white = { 255, 255, 255, 255 };

    _player1Score.reset(new TextDisplay(render, "Score: 0", "font.ttf", white, 12));
    _player2Score.reset(new TextDisplay(render, "Score: 0", "font.ttf", white, 12));

    _message.reset(new TextDisplay(render, "Press 'Space' if you're ready!", "font.ttf", white, 16));
}

GameScene::~GameScene()
{
}

void GameScene::Update(float delta)
{
    std::vector<char> package;
    std::vector<char> data;
    auto sock = _sock.lock();

    if (_state == GS_Ready)
    {
        auto input = _input.lock();

        if(input->KeyPress(SDL_SCANCODE_SPACE))
			{
                _message->Text("Waiting for the another player...");

                _id = 0;
                _scoreP1 = 0;
                _scoreP2 = 0;
                _error = false;

                _player1Score->Text("Score: " + std::to_string(_scoreP1));
                _player2Score->Text("Score: " + std::to_string(_scoreP2));

                SDL_Point p1pos = { PLAYER1_X, PLAYER1_Y };
                SDL_Point p2pos = { PLAYER2_X, PLAYER2_Y };

                _map->SetEntityPosition("Player1", p1pos);
                _map->SetEntityPosition("Player2", p2pos);

                package = MakeReadyPackage();

				sock->Send(package);

                _state = GS_Wait;    	
			}
    }
    else if (_state == GS_Wait)
    {
        sock->Receive(package);

		Bufferize(package, _buffer);
		package.clear();
		ProcessBuffer(_buffer, package);

        if (package.size() > 0)
        {
            int ballx, bally;

            if (ParsePackage(package, data) != PACKAGE_TYPE_INIT)
            {
				_message->Text("Invalid package received! [" + PrintPackage(package) + "] (2)");
                _error = true;
                return;
            }

            ParseInitData(data, _id, ballx, bally);

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

		Bufferize(package, _buffer);
		package.clear();
		ProcessBuffer(_buffer, package);

		if (package.size() > 0)
        {
            switch (ParsePackage(package, data))
            {
			case PACKAGE_TYPE_PLAYER_MOVE:
				{
					int id, x, y;
					ParseMoveData(data, id, x, y);
                
					if (id == _id)
					{
						_message->Text("Receive a move package that belong to another player! [" + PrintPackage(package) + "]");
						_error = true;
					}
					else
					{
						SDL_Point ppos = { x, y };

						_map->SetEntityPosition(id == 1 ? "Player1" : "Player2", ppos);
					}
					break;
				}

			case PACKAGE_TYPE_BALL:
				{
					int bx, by;
					ParseBallData(data, bx, by);

					SDL_Point bpos = { bx, by };
					_map->SetEntityPosition("Ball", bpos);

					break;
				}
			
            case PACKAGE_TYPE_PLAYER_SCORE:
            {
                int id, bx, by;

                ParseScoreData(data, id, bx, by);

                SDL_Point bpos = { bx, by };
                _map->SetEntityPosition("Ball", bpos);

                if (id == 1)
                {
                    _scoreP1++;
                    
                    _player1Score->Text("Score: " + std::to_string(_scoreP1));
                }
                else
                {
                    _scoreP2++;

                    _player2Score->Text("Score: " + std::to_string(_scoreP2));
                }

                break;
            }
            case PACKAGE_TYPE_END:
            {
                int id;

                ParseEndData(data, id);

                if (id == 1)
                {
                    _scoreP1++;
                    
                    _player1Score->Text("Score: " + std::to_string(_scoreP1));
                }
                else
                {
                    _scoreP2++;

                    _player2Score->Text("Score: " + std::to_string(_scoreP2));
                }

                if (id == _id)
                    _message->Text("You won!!!");
                else
                    _message->Text("You lose!!!");

                _state = GS_End;
                break;
            }

			default:
				{
					_message->Text("Invalid package received! [" + PrintPackage(package) + "] (1)");
					_error = true;
					break;
				}
            }
        }

		if (delta >= 1000/FPS/2)
		{
			std::string player;

			if (_id == 1)
				player = "Player1";
			else
				player = "Player2";

			SDL_Point pos = _map->GetEntityPosition(player);
        
			bool keyPressed = false;

			if(input->KeyPress(SDL_SCANCODE_W))
			{
				_map->MoveEntity(player, MT_UP);
				keyPressed = true;
			}
			else if (input->KeyPress(SDL_SCANCODE_S))
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

					sock->Send(package);
				}
			}
		}
    }
    else if (_state == GS_End)
    {
        auto input = _input.lock();

        if(input->KeyPress(SDL_SCANCODE_SPACE))
        {
            _message->Text("Press 'Space' if you're ready!");

            _state = GS_Ready;
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

    if (_state == GS_Ready || _state == GS_Wait || _state == GS_End || _error)
    {
        SDL_Rect m_rect = _message->Rect();
        m_rect.x = SCREEN_WIDTH / 2 - m_rect.w / 2;
        m_rect.y = SCREEN_HEIGHT / 2 - m_rect.h / 2;

        _message->Draw(m_rect);
    }
}
