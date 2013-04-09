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

        void addScene(std::shared_ptr<Scene> scene);
        void removeScene(const std::string &name);

        void changeCurrentScene(const std::string &name);
        std::shared_ptr<Scene> getCurrentScene();
        std::shared_ptr<Scene> getScene(const std::string &name);

        void update(float delta);
        void draw();

    private:
        std::map<std::string, std::shared_ptr<Scene> > _sceneList;
        std::string _currentSceneName;
    };

}

#endif
