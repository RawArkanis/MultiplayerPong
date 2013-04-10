#include "WindowManager.h"

namespace RGL {

	bool WindowManager::_isInitialized = false;

    WindowManager::WindowManager()
        : _window(std::unique_ptr<SDL_Window, void (*)(SDL_Window *)>(nullptr, SDL_DestroyWindow)),
        _renderer(std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)>(nullptr, SDL_DestroyRenderer)),
        _box(SDL_Rect())
    {}

    WindowManager::~WindowManager()
    {}

    int WindowManager::Initialize(std::string title, unsigned int width, unsigned int height)
    {
        if (_isInitialized)
            return 0;

        if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
            return 1;

        _window.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, 
            height, SDL_WINDOW_SHOWN));
        if (_window == nullptr)
            return 2;

        _renderer.reset(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
        if (_renderer == nullptr)
            return 3;

		SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, 255);

        SDL_Rect box = { 0, 0, width, height };
        _box = box;

        _isInitialized = true;

        return 0;
    }

    void WindowManager::Finish()
    {
        if (!_isInitialized)
            return;

        _renderer.~unique_ptr();
        _window.~unique_ptr();

        SDL_Quit();

        _isInitialized = false;
    }

    void WindowManager::Draw(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destRect)
    {
        SDL_RenderCopy(_renderer.get(), texture, &sourceRect, &destRect);
    }
    
    void WindowManager::Clear()
    {
        SDL_RenderClear(_renderer.get());
    }

    void WindowManager::Present()
    {
        SDL_RenderPresent(_renderer.get());
    }

    SDL_Rect WindowManager::Box()
    {
        return _box;
    }

}
