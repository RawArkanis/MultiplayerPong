#include "Square.h"

#include <Render/RenderManager.h>
#include <Container/Surface.h>

using namespace RGL;

Square::Square(std::weak_ptr<RenderManager> render, const SDL_Rect &rect, const SDL_Color &color)
    : Entity(render, rect),
    _texture(nullptr)
{
    SDL_Rect squareRect = { rect.x + 1, rect.y + 1, rect.w - 2, rect.h - 2 };

    auto surface = std::make_shared<Surface>();
    surface->CreateRGB(rect);
    surface->Fill(squareRect, color);

    auto ren = _render.lock();
    _texture = ren->CreateTextureFromSurface(std::weak_ptr<Surface>(surface));
}

Square::~Square()
{
}

void Square::Update(double delta)
{
}

void Square::Draw(const SDL_Rect &rect)
{
    auto ren = _render.lock();
    ren->Draw(std::weak_ptr<Texture>(_texture), _rect, rect);
}
