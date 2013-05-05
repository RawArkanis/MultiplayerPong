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

int Entity::CheckBallCollision(int ballx, int bally)
{
    int x = ballx, y = bally;

    if ((x >= _x && x <= _x + _w - 1) &&
        (y >= _y && y <= _y + _h - 1))
    {
        if (y >= _y && y <= _y + 1)
            return -2;
        else if (y >= _y + 2 && y <= _y + 3)
            return -1;
        else if (y >= _y + 4 && y <= _y + 7)
            return 0;
        else if (y >= _y + 8 && y <= _y + 9)
            return -2;
        else if (y >= _y + 10 && y <= _y + 11)
            return -2;
    }

    return -3;
}
