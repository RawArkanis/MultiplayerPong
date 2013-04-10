#include "SceneManager.h"

namespace RGL {

    SceneManager::SceneManager(void)
        : _currentSceneName("")
    {
    }

    SceneManager::~SceneManager(void)
    {
    }

    void SceneManager::AddScene(std::shared_ptr<Scene> scene)
    {
        _sceneList[scene->Name()] = scene;
    }

    void SceneManager::RemoveScene(const std::string &name)
    {
        _sceneList.erase(name);
    }

    bool SceneManager::ChangeCurrentScene(const std::string &name)
    {
		if (!SceneExists(name))
			return false;

		_currentSceneName = name;
			
		return true;
    }

    std::shared_ptr<Scene> SceneManager::CurrentScene()
    {
        return _sceneList[_currentSceneName];
    }

    std::shared_ptr<Scene> SceneManager::GetScene(const std::string &name)
    {
		if (!SceneExists(name))
			return nullptr;

        return _sceneList[name];
    }

	bool SceneManager::SceneExists(const std::string &name)
	{
		return _sceneList.find(name) != _sceneList.end();
	}

    void SceneManager::Update(float delta)
    {
	    if (!_currentSceneName.empty())
        {
            _sceneList[_currentSceneName]->Update(delta);
        }
    }

    void SceneManager::Draw()
    {
        if (!_currentSceneName.empty())
        {
            _sceneList[_currentSceneName]->Draw();
        }
    }

}
