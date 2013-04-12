#ifndef __RGL_RENDER_MANAGER_H__
#define __RGL_RENDER_MANAGER_H__

#include "../Common.h"

namespace RGL
{
    
    class WindowManager;
    class Surface;
    class Texture;

    class RenderManager
    {
    public:
        RenderManager();
        ~RenderManager();

        ReturnValue Initialize(std::shared_ptr<WindowManager> window);
        ReturnValue Finish();

        std::shared_ptr<Texture> CreateTextureFromSurface(std::weak_ptr<Surface> surface);

        ReturnValue Draw(std::weak_ptr<Texture> texture, const SDL_Rect &sourceRect, const SDL_Rect &destRect);
    
        ReturnValue Clear();
        ReturnValue Present();

    private:
        bool _isInitialized;

        std::unique_ptr<SDL_Renderer,  void (*)(SDL_Renderer *)> _renderer;

    };

}

#endif
