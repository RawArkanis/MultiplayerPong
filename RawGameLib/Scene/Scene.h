#ifndef __RGL_SCENE_H__
#define __RGL_SCENE_H__

#include "../Common.h"

namespace RGL {

	class WindowManager;

    class Scene
    {
    public:
        Scene(std::weak_ptr<WindowManager> window, const std::string &name);
        ~Scene();

        std::string Name() const;

        virtual void Update(float delta) = 0;
        virtual void Draw() = 0;

    protected:
		std::weak_ptr<WindowManager> _window;

        std::string _name;
    };

}

#endif
