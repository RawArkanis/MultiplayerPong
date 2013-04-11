#include "RGLManager.h"

#include "Window/WindowManager.h"
#include "Render/RenderManager.h"
#include "Input/InputManager.h"

namespace RGL
{

    RGLManager::RGLManager()
        : _isInitialized(false)
    {
    }

    RGLManager::~RGLManager()
    {
    }

    ReturnValue RGLManager::Initialize()
    {
        if (_isInitialized)
            return R_ERR_ALREADY_INITIALIZED;

        if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
            return R_ERR_SDL_INIT;

        _isInitialized = true;

        return R_OK;
    }

    ReturnValue RGLManager::Finish()
    {
        if (!_isInitialized)
            return R_ERR_NOT_INITIALIZAED;

        SDL_Quit();

        _isInitialized = false;

        return R_OK;
    }

    bool RGLManager::IsInitialized()
    {
        return _isInitialized;
    }

}
