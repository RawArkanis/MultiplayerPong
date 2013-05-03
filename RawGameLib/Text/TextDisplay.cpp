#include "TextDisplay.h"

#include <../Container/Surface.h>
#include <../Container/Texture.h>
#include <../Render/RenderManager.h>

namespace RGL
{

    TextDisplay::TextDisplay(std::weak_ptr<RenderManager> render, const std::string &text, const std::string &font, const SDL_Color &color, int size)
        : _render(render),
        _texture(nullptr),
        _text(text),
		_font(font),
		_size(size),
        _color(color)
    {
        UpdateTexture();
    }

    TextDisplay::~TextDisplay()
    {
    }

	void TextDisplay::UpdateTexture()
	{
		TTF_Font *f = TTF_OpenFont(_font.c_str(), _size);

        auto surface = std::make_shared<Surface>();
        surface->CreateText(f, _text.c_str(), _color);
        
        _rect = surface->SDLSurface()->clip_rect;

        auto ren = _render.lock();

        _texture = ren->CreateTextureFromSurface(std::weak_ptr<Surface>(surface));

		TTF_CloseFont(f);
	}

    void TextDisplay::Text(const std::string &text)
    {
        _text = text;

		UpdateTexture();
    }

    std::string TextDisplay::Text() const
    {
        return _text;
    }

    SDL_Rect TextDisplay::Rect() const
    {
        return _rect;
    }

    void TextDisplay::Draw(const SDL_Rect& rect)
    {
        auto render = _render.lock();

        auto tex = _texture->SDLTexture();

        render->Draw(std::weak_ptr<Texture>(_texture), _rect, rect);
    }

}
