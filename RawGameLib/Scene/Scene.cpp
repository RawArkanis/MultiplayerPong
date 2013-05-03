#include "Scene.h"

namespace RGL {

    Scene::Scene(std::weak_ptr<SceneManager> manager, std::weak_ptr<RenderManager> render, std::weak_ptr<InputManager> input, const std::string &name)
        : _manager(manager), 
        _render(render),
        _input(input),
		_name(name)
    {
    }

    Scene::~Scene()
    {
    }

    std::string Scene::Name() const
    {
        return _name;
    }

}
