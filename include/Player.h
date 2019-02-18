#ifndef PLAYER_H
#define PLAYER_H

#include "Vector2.h"
#include "Entity.h"
#include "Map.h"

#include <deque>

class Player : public Entity
{
public:
    Player(Vector2 pos, std::string name);
    void Update(char input) override final;
    EType GetType() const override final { return EType::ePlayer; };
    std::deque<string> Attack(Entity* target, Vector2 mapSize) override final;
    std::deque<string> GainExperience(int exp);
    void LevelUp();
    void DisplayStats();

private:
    int m_level { 1 };
    int m_experience { 0 };

};

#endif
