#ifndef __MPS_ENTITY_H__
#define __MPS_ENTITY_H__

class Entity
{
public:
    Entity(int id, int x, int y, int w, int h);
    ~Entity();

    int GetID();

    void SetPosition(int x, int y);
    void GetPosition(int &x, int &y);

    void SetSize(int w, int h);
    void GetSize(int &w, int &h);

private:
    int _id;
    int _x;
    int _y;
    int _w;
    int _h;
};

#endif
