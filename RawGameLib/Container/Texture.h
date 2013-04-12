#ifndef __RGL_TEXTURE_H__
#define __RGL_TEXTURE_H__

#include "../Common.h"

namespace RGL
{

    class Texture
    {
    public:
        Texture();
        ~Texture();

        ReturnValue Create(SDL_Texture *texture);

        SDL_Texture *SDLTexture() const;

    private:
        bool _isCreated;

        std::unique_ptr<SDL_Texture, void (*)(SDL_Texture *)> _texture;

    };

}

#endif
