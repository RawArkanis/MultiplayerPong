#pragma once
#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <Entity/Entity.h>
#include <Container/Texture.h>

#include "../Common.h"

class Square : public RGL::Entity
{
public:
    Square(std::weak_ptr<RGL::RenderManager> render, const SDL_Rect &rect, const SDL_Color &color);
	~Square();

	void Update(double delta);
	void Draw(const SDL_Rect &rect);

private:
    std::shared_ptr<RGL::Texture> _texture;

};

#endif
