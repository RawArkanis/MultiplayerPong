#ifndef __RGL_WINDOW_MANAGER_H__
#define __RGL_WINDOW_MANAGER_H__

#include "../Common.h"

namespace RGL {

    class WindowManager // TODO Corrigir os retornos, e criar o RGLManager
    {
    public:
        WindowManager();
        ~WindowManager();

        int Initialize(const std::string title, unsigned int width, unsigned int height);
        void Finish();

        void Draw(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destRect);
    
        void Clear();
        void Present();

        SDL_Rect Box();

    private:
        static bool _isInitialized;

        std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> _window;
        std::unique_ptr<SDL_Renderer,  void (*)(SDL_Renderer *)> _renderer;
        SDL_Rect _box;
    };

}

#endif
