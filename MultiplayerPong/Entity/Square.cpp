#include "Square.h"

#include <Render/RenderManager.h>
#include <Container/Surface.h>

using namespace RGL;

Square::Square(std::weak_ptr<RenderManager> render, const SDL_Rect &rect, const SDL_Color &color)
    : Entity(render, rect),
    texture(nullptr)
{
    SDL_Rect squareRect = rect;
    squareRect.x +=1;
    squareRect.y +=1;
    squareRect.w +=1;
    squareRect.w +=1;

    auto surface = std::make_shared<Surface>();
    surface->CreateRGB(rect);
    surface->Fill(squareRect, color);

    auto ren = _render.lock();
    texture = ren->CreateTextureFromSurface(std::weak_ptr<Surface>(surface));
}

Square::~Square()
{
}

void Square::Update(double delta)
{
}

void Square::Draw()
{
    auto ren = _render.lock();
    ren->Draw(texture, _rect, _rect);
}
