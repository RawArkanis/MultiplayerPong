#include "Scene.h"

namespace RGL {

    Scene::Scene(std::weak_ptr<RenderManager> render, const std::string &name)
        : _render(render),
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
