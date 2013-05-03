#include "Entity.h"

Entity::Entity(int id, int x, int y, int w, int h)
    : _id(id),
    _x(x),
    _y(y),
    _w(w),
    _h(h)
{
}

Entity::~Entity()
{
}

int Entity::GetID()
{
    return _id;
}

void Entity::SetPosition(int x, int y)
{
    _x = x;
    _y = y;
}

void Entity::GetPosition(int &x, int &y)
{
    x = _x;
    y = _y;
}

void Entity::SetSize(int w, int h)
{
    _w = w;
    _h = h;
}


void Entity::GetSize(int &w, int &h)
{
    w = _w;
    h = _h;
}
