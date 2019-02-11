#include "Enemy.h"
#include <ncurses/curses.h>

Enemy::Enemy(Vector2 pos) : Entity(pos)
{
    //ctor
}

void Enemy::Update(char input)
{
    char randDir = rand() % 9 + 48;
    Move(randDir, 'E');
}

void Enemy::Attack(Entity* target, Vector2 mapSize)
{
    int damage = -1;
    target->SetHealth(damage);

    DisplayEntity('E');

    std::string enemyAttackString = "Enemy dealt " + std::to_string(damage) + " damage!";
    mvprintw(1, mapSize.y + 1, "%s", enemyAttackString.c_str());
}
