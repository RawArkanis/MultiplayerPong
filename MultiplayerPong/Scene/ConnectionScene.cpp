#include "ConnectionScene.h"

#include <Render/RenderManager.h>
#include <Input/InputManager.h>
#include <Scene/SceneManager.h>
#include <Text/TextDisplay.h>

#include <TCPSock.h>

using namespace RGL;

ConnectionScene::ConnectionScene(std::weak_ptr<SceneManager> manager, std::weak_ptr<RGL::RenderManager> render,  std::weak_ptr<InputManager> input,
        const std::string &name, std::weak_ptr<TCPSock> sock)
    : Scene(manager, render, input, name),
    _text(nullptr),
    _sock(sock),
    _ip(HOST),
    _port(PORT),
    _state(CS_Waiting)
{
    SDL_Color white = { 255, 255, 255, 255 };

    _text.reset(new TextDisplay(render, "PRESS 'SPACE' TO CONNECT!", "font.ttf", white, 16));
}

ConnectionScene::~ConnectionScene()
{
}

void ConnectionScene::Update(float delta)
{
    if (_state == CS_Waiting)
    {
        auto input = _input.lock();

        if (input->KeyPress(SDL_SCANCODE_SPACE))
        {
            _text->Text("Connecting...");
            _state = CS_Connecting;
        }
    }
    else if (_state == CS_Connecting)
    {
        auto sock = _sock.lock();

        if (!sock->IsOpen())
        {
            if(sock->Open() != WS_OK)
            {
		        std::cerr << "Error open sock: " << sock->GetLastError() << std::endl;
                _state = CS_Done;
                _text->Text("Erro opening socket!");
            }
        }
        else
        {
            if(sock->Connect(_ip, _port) != WS_OK)
            {
		        std::cerr << "Error connect sock: " << sock->GetLastError() << std::endl;
                _text->Text("Erro connecting to server! [" + _ip + ":" +  std::to_string(_port) + "]");
                _state = CS_Done;
            }
            else
            {
                sock->SetIOMode(FIONBIO, 1);

                auto manager = _manager.lock();
                manager->ChangeCurrentScene("GameScene");
            }
        }
    }
}

void ConnectionScene::Draw()
{
    SDL_Rect m_rect = _text->Rect();
    m_rect.x = SCREEN_WIDTH / 2 - m_rect.w / 2;
    m_rect.y = SCREEN_HEIGHT / 2 - m_rect.h / 2;

    _text->Draw(m_rect);
}

void ConnectionScene::SetIP(const std::string &ip)
{
    _ip = ip;
}

void ConnectionScene::SetPortt(int port)
{
    _port = port;
}
