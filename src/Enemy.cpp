#include "Enemy.h"
#include <ncurses/curses.h>

Enemy::Enemy(Vector2 pos, std::string name) : Entity(pos, name)
{
    m_health = 2;
}

std::deque<string> Enemy::Update(char input)
{
    std::deque<string> notifications;

    char randDir = rand() % 9 + 48;
    Move(randDir, 'E');

    return notifications;
}

std::deque<string> Enemy::Attack(Entity* target, Vector2 mapSize)
{
    std::deque<string> notifications;

    int damage = -1;
    target->SetHealth(damage);

    std::string enemyAttackString = "Enemy dealt " + std::to_string(damage) + " damage!";
    notifications.push_front(enemyAttackString);
    return notifications;
}

std::deque<string> Enemy::GainExperience(int exp)
{

}
