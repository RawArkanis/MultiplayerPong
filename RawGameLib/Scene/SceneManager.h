#ifndef __RGL_SCENE_MANAGER_H__
#define __RGL_SCENE_MANAGER_H__

#include <map>

#include "Scene.h"

namespace RGL {

    class SceneManager
    {
    public:
        SceneManager();
        ~SceneManager();

        void AddScene(std::shared_ptr<Scene> scene);
        void RemoveScene(const std::string &name);

        bool ChangeCurrentScene(const std::string &name);
        std::shared_ptr<Scene> CurrentScene();
        std::shared_ptr<Scene> GetScene(const std::string &name);

		bool SceneExists(const std::string &name);

        void Update(float delta);
        void Draw();

    private:
        std::map<std::string, std::shared_ptr<Scene> > _sceneList;

        std::string _currentSceneName;
    };

}

#endif
