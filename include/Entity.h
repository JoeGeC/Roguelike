#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2.h"
#include "Map.h"
#include <vector>

enum class EType
{
    ePlayer,
    eEnemy
};

class Map;

class Entity
{
public:
    Entity(Vector2 pos);
    virtual ~Entity();
    virtual void Update(char input) = 0;
    virtual void Attack(Entity* target, Vector2 mapSize) = 0;
    virtual EType GetType() const = 0;
    void Move(char input, char symbol);
    void DisplayEntity(char symbol);
    bool CheckAlive();
    void Die();

    Vector2 GetPos(){ return m_pos; }
    int GetHealth(){ return m_health; }
    bool GetAlive(){ return m_alive; }

    void SetHealth(int addHealth) { m_health += addHealth; }

protected:
    Vector2 m_pos;
    int m_health { 10 };
    bool m_alive { true };
};

#endif // ENTITY_H
