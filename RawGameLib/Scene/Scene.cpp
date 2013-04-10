#include "Scene.h"

namespace RGL {

    Scene::Scene(std::weak_ptr<WindowManager> window, const std::string &name)
        : _window(window),
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
