#include "SceneManager.h"

namespace RGL {

    SceneManager::SceneManager(void)
        : _currentSceneName("")
    {
    }

    SceneManager::~SceneManager(void)
    {
    }

    void SceneManager::addScene(std::shared_ptr<Scene> scene)
    {
        _sceneList[scene->getName()] = scene;
    }

    void SceneManager::removeScene(const std::string &name)
    {
        _sceneList.erase(name);
    }

    void SceneManager::changeCurrentScene(const std::string &name)
    {
	    _currentSceneName = name;
    }

    std::shared_ptr<Scene> SceneManager::getCurrentScene()
    {
        return _sceneList[_currentSceneName];
    }

    std::shared_ptr<Scene> SceneManager::getScene(const std::string &name)
    {
        return _sceneList[name];
    }

    void SceneManager::update(float delta)
    {
	    if (!_currentSceneName.empty())
        {
            _sceneList[_currentSceneName]->update(delta);
        }
    }

    void SceneManager::draw()
    {
        if (!_currentSceneName.empty())
        {
            _sceneList[_currentSceneName]->draw();
        }
    }

}
