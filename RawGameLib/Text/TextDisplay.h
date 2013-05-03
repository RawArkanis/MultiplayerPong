#ifndef __RGL_TEXT_DISPLAY_H__
#define __RGL_TEXT_DISPLAY_H__

#include "../Common.h"

namespace RGL
{

    class RenderManager;
    class Texture;

    class TextDisplay
    {
    public:
        TextDisplay(std::weak_ptr<RenderManager> render, const std::string &text, const std::string &font, const SDL_Color &color, int size);
        ~TextDisplay();

        void Text(const std::string &text);
        std::string Text() const;

        SDL_Rect Rect() const;

        void Draw(const SDL_Rect& rect);

    private:
        std::weak_ptr<RenderManager> _render;

        std::shared_ptr<Texture> _texture;

        std::string _text;
		std::string _font;
		int _size;
        SDL_Color _color;
        SDL_Rect _rect;

		void UpdateTexture();
    };

}

#endif
