#include "WindowManager.h"

namespace RGL
{

    WindowManager::WindowManager()
        : _isInitialized(false),
        _window(std::unique_ptr<SDL_Window, void (*)(SDL_Window *)>(nullptr, SDL_DestroyWindow))
    {}

    WindowManager::~WindowManager()
    {}

    ReturnValue WindowManager::Initialize(std::string title, unsigned int width, unsigned int height)
    {
        if (_isInitialized)
            return R_ERR_ALREADY_INITIALIZED;

        _window.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, 
            height, SDL_WINDOW_SHOWN));
        if (_window == nullptr)
            return R_ERR_SDL_CREATE_WINDOW;

        SDL_Rect box = { 0, 0, width, height };
        _box = box;

        _isInitialized = true;

        return R_OK;
    }

    ReturnValue WindowManager::Finish()
    {
        if (!_isInitialized)
            return R_ERR_NOT_INITIALIZAED;

        _window.~unique_ptr();

        _box = SDL_Rect();

        _isInitialized = false;

        return R_OK;
    }

    SDL_Window *WindowManager::Window()
    {
        return _window.get();
    }

    SDL_Rect WindowManager::WindowBox()
    {
        return _box;
    }

}
