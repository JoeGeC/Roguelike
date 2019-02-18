#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <deque>

class Enemy : public Entity
{
public:
    Enemy(Vector2 pos, std::string name);
    void Update(char input) override final;
    EType GetType() const override final { return EType::eEnemy; };
    std::deque<string> Attack(Entity* target, Vector2 mapSize) override final;
    std::deque<string> GainExperience(int exp) override final;

private:
};

#endif // ENEMY_H
