#include "Texture.h"

namespace RGL
{

    Texture::Texture()
        : _isCreated(false),
        _texture(std::unique_ptr<SDL_Texture, void (*)(SDL_Texture *)>(nullptr, SDL_DestroyTexture))
    {
    }

    Texture::~Texture()
    {
    }

    ReturnValue Texture::Create(SDL_Texture *texture)
    {
        if (_isCreated)
            return R_ERR_ALREADY_CREATED;

        _texture.reset(texture);

        _isCreated = true;

        return R_OK;
    }

    SDL_Texture *Texture::SDLTexture() const
    {
        return _texture.get();
    }

}
