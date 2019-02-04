#ifndef PLAYER_H
#define PLAYER_H

#include "Vector2.h"
#include "Entity.h"

class Player : public Entity
{
public:
    Player(Vector2 pos);
    void Update(char input) override final;
    EType GetType() const override final { return EType::ePlayer; };
    void DisplayStats();
    void Attack(Entity* target, Vector2 mapSize) override final;

private:

};

#endif
