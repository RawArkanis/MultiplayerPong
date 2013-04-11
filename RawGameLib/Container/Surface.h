#ifndef __RGL_SURFACE_H__
#define __RGL_SURFACE_H__

#include "../Common.h"

namespace RGL
{

    class Surface
    {
    public:
        Surface();
        ~Surface();

        ReturnValue CreateRGB(const SDL_Rect &rect);

        ReturnValue Fill(const SDL_Rect &rect, const SDL_Color &color);

        SDL_Surface *SDLSurface() const;
    
    private:
        bool _isCreated;

        std::unique_ptr<SDL_Surface, void (*)(SDL_Surface *)> _surface;

    };

}

#endif
