#include "RenderManager.h"

#include "../Window/WindowManager.h"
#include "../Container/Surface.h"

namespace RGL
{

    RenderManager::RenderManager()
        : _isInitialized(false),
        _renderer(std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)>(nullptr, SDL_DestroyRenderer))
    {
    }

    RenderManager::~RenderManager()
    {
    }

    ReturnValue RenderManager::Initialize(std::shared_ptr<WindowManager> window)
    {
        if (_isInitialized)
            return R_ERR_ALREADY_INITIALIZED;

        _renderer.reset(SDL_CreateRenderer(window->Window(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
        if (_renderer == nullptr)
            return R_ERR_SDL_CREATE_RENDER;

		SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, 255);

        _isInitialized = true;

        return R_OK;
    }

    ReturnValue RenderManager::Finish()
    {
        if (!_isInitialized)
            return R_ERR_NOT_INITIALIZAED;

        _renderer.~unique_ptr();

        _isInitialized = false;

        return R_OK;
    }

    SDL_Texture *RenderManager::CreateTextureFromSurface(std::weak_ptr<Surface> surface)
    {
        auto surf = surface.lock();

        return SDL_CreateTextureFromSurface(_renderer.get(), surf.get()->SDLSurface());
    }

    ReturnValue RenderManager::Draw(SDL_Texture *texture, const SDL_Rect &sourceRect, const SDL_Rect &destRect)
    {
        if (!_isInitialized)
            return R_ERR_NOT_INITIALIZAED;

        SDL_RenderCopy(_renderer.get(), texture, &sourceRect, &destRect);

        return R_OK;
    }
    
    ReturnValue RenderManager::Clear()
    {
        if (!_isInitialized)
            return R_ERR_NOT_INITIALIZAED;

        SDL_RenderClear(_renderer.get());

        return R_OK;
    }

    ReturnValue RenderManager::Present()
    {
        if (!_isInitialized)
            return R_ERR_NOT_INITIALIZAED;

        SDL_RenderPresent(_renderer.get());

        return R_OK;
    }

}
