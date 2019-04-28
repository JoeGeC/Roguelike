#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2.h"
#include "Map.h"
#include <deque>
#include <SFML/Network.hpp>

enum class EType
{
    ePlayer,
    eEnemy
};

class Map;

class Entity
{
public:
    Entity(Vector2 pos, std::string name);
    virtual ~Entity();
    virtual std::deque<string> Update(char input) = 0;
    virtual std::deque<string> Attack(Entity* target, Vector2 mapSize) = 0;
    virtual EType GetType() const = 0;
    virtual std::deque<string> GainExperience(int exp) = 0;
    void Move(char input, char symbol);
    void DisplayEntity(char symbol);
    bool CheckAlive();
    std::deque<string> Die(Entity* killer);

    int GetId(){ return m_id; }
    Vector2 GetPos(){ return m_pos; }
    int GetHealth(){ return m_health; }
    bool GetAlive(){ return m_alive; }
    string GetName(){ return m_name; }

    void SetId(int id) { m_id = id; }
    void SetHealth(int addHealth) { m_health += addHealth; }
    void SetNextMove(int direction) { m_move = direction; }
    void SetPos(Vector2 pos) { m_pos = pos; }

protected:
    Vector2 m_pos;
    int m_id { 9 };
    int m_move { 1 };
    int m_health { 100 };
    bool m_alive { true };
    int m_defeatExp { 10 };
    string m_name;

};

#endif // ENTITY_H
