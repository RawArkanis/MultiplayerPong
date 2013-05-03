#ifndef __RGL_SCENE_H__
#define __RGL_SCENE_H__

#include "../Common.h"

namespace RGL {

    class SceneManager;
	class RenderManager;
    class InputManager;

    class Scene
    {
    public:
        Scene(std::weak_ptr<SceneManager> manager, std::weak_ptr<RenderManager> render, std::weak_ptr<InputManager> input, const std::string &name);
        ~Scene();

        std::string Name() const;

        virtual void Update(float delta) = 0;
        virtual void Draw() = 0;

    protected:
        std::weak_ptr<SceneManager> _manager;
		std::weak_ptr<RenderManager> _render;
        std::weak_ptr<InputManager> _input;

        std::string _name;
    };

}

#endif
