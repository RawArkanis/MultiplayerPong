#include "Surface.h"

namespace RGL
{

    Surface::Surface()
        : _isCreated(false),
        _surface(std::unique_ptr<SDL_Surface, void (*)(SDL_Surface *)>(nullptr, SDL_FreeSurface))
    {
    }

    Surface::~Surface()
    {
    }

    ReturnValue Surface::CreateRGB(const SDL_Rect &rect)
    {
        if (_isCreated)
            return R_ERR_ALREADY_CREATED;

        _surface.reset(SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0));

        _isCreated = true;

        return R_OK;
    }

    ReturnValue Surface::Fill(const SDL_Rect &rect, const SDL_Color &color)
    {
        if (!_isCreated)
            return R_ERR_NOT_CREATED;

        SDL_Surface *surface = _surface.get();
        SDL_PixelFormat *format = surface->format;

        SDL_FillRect(surface, &rect, SDL_MapRGBA(format, color.r, color.g, color.b, color.a));

        return R_OK;
    }

    SDL_Surface *Surface::SDLSurface() const
    {
        return _surface.get();
    }

}
