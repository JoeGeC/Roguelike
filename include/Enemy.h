#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity
{
public:
    Enemy(Vector2 pos);
    void Update(char input) override final;
    EType GetType() const override final { return EType::eEnemy; };
    void Attack(Entity* target, Vector2 mapSize) override final;

private:

};

#endif // ENEMY_H
