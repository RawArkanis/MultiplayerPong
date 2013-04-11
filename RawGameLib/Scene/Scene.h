#ifndef __RGL_SCENE_H__
#define __RGL_SCENE_H__

#include "../Common.h"

namespace RGL {

	class RenderManager;

    class Scene
    {
    public:
        Scene(std::weak_ptr<RenderManager> render, const std::string &name);
        ~Scene();

        std::string Name() const;

        virtual void Update(float delta) = 0;
        virtual void Draw() = 0;

    protected:
		std::weak_ptr<RenderManager> _render;

        std::string _name;
    };

}

#endif
