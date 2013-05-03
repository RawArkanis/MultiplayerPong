#ifndef __CONNECTION_SCENE_H__
#define __CONNECTION_SCENE_H__

#include <Scene/Scene.h>

#include <Text/TextDisplay.h>

#include "../Common.h"

enum ConnectionState
{
    CS_Waiting,
    CS_Connecting,
    CS_Done
};

class TCPSock;

class ConnectionScene : public RGL::Scene
{
public:
    ConnectionScene(std::weak_ptr<RGL::SceneManager> manager, std::weak_ptr<RGL::RenderManager> render, std::weak_ptr<RGL::InputManager> input,
        const std::string &name, std::weak_ptr<TCPSock> sock);
	~ConnectionScene();

	void Update(float delta);
    void Draw();

    void SerIP(const std::string &ip);

private:
    std::unique_ptr<RGL::TextDisplay> _text;
    std::weak_ptr<TCPSock> _sock;

    std::string _ip;
    
    ConnectionState _state;
};

#endif
