#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include "Vector2.h"
#include <vector>

class Entity;

class Map
{
public:
    Map();
    char GetMapLoc(int posx, int posy) { return m_map[posx][posy]; }
    Vector2 GetMapSize() { return Vector2(sizeof(m_map) / sizeof(m_map[0]), sizeof(m_map[0])); }
    Entity* GetEntityAtLoc(Vector2 pos, std::vector<Entity*> entityVector);

private:
    char m_map[30][80];
};

#endif //MAP_H
