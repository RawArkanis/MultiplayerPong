#ifndef __RGL_SCENE_H__
#define __RGL_SCENE_H__

#include "../Common.h"

namespace RGL {

    class Scene
    {
    public:
        Scene(const std::string &name);
        ~Scene();

        std::string getName() const;

        virtual void update(float delta) = 0;
        virtual void draw() = 0;

    private:
        std::string _name;
    };

}

#endif
