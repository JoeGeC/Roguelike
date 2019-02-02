#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2.h"

class Entity
{
public:
    Entity(Vector2 pos);
    void Move(char input, char symbol);

    Vector2 GetPos(){ return m_pos; }
    int GetHealth(){ return m_health; }

protected:
    Vector2 m_pos;
    int m_health = 10;
};

#endif // ENTITY_H
