#ifndef __RGL_WINDOW_MANAGER_H__
#define __RGL_WINDOW_MANAGER_H__

#include "../Common.h"

namespace RGL
{

    class InputManager;

    class WindowManager
    {
    public:
        WindowManager();
        ~WindowManager();

        ReturnValue Initialize(const std::string title, unsigned int width, unsigned int height);
        ReturnValue Finish();

        SDL_Window *Window();

        SDL_Rect WindowBox();

    private:
        bool _isInitialized;

        std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> _window;

        SDL_Rect _box;
    };

}

#endif
