#include "Scene.h"

namespace RGL {

    Scene::Scene(const std::string &name)
        : _name(name)
    {
    }

    Scene::~Scene()
    {
    }

    std::string Scene::getName() const
    {
        return _name;
    }

}
