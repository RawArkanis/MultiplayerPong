#ifndef __RGL_COMMON_H__
#define __RGL_COMMON_H__

#include <iostream>
#include <string>
#include <memory>

#include <SDL2\SDL.h>

namespace RGL
{

    enum ReturnValue
    {
        R_OK,
        R_ERR_ALREADY_INITIALIZED,
        R_ERR_ALREADY_CREATED,
        R_ERR_NOT_INITIALIZAED,
        R_ERR_NOT_CREATED,
        R_ERR_SDL_INIT,
        R_ERR_SDL_CREATE_WINDOW,
        R_ERR_SDL_CREATE_RENDER
    };

}

#endif
