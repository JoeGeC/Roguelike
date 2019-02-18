#include "Player.h"
#include "Map.h"
#include <ncurses/curses.h>

Player::Player(Vector2 pos, std::string name) : Entity(pos, name)
{
    //ctor
}

void Player::Update(char input)
{
    Move(input, '@');
}

std::deque<string> Player::Attack(Entity* target, Vector2 mapSize)
{
    std::deque<string> notifications;

    int damage = -1;
    target->SetHealth(damage);

    std::string enemyHealthString = "Enemy health: " + std::to_string(target->GetHealth());
    mvprintw(mapSize.x + 2, 1, "%s", enemyHealthString.c_str());

    std::string playerAttackString = "Player dealt " + std::to_string(damage) + " damage!";
    notifications.push_front(playerAttackString);

    if (target->GetHealth() <= 0)
    {
        std::deque<string> dieStrings = target->Die(this);
        for (auto s : dieStrings)
        {
            notifications.push_back(s);
        }
    }

    return notifications;
}

std::deque<string> Player::GainExperience(int exp)
{
    std::deque<string> notifications;

    m_experience += exp;
    std::string expString = m_name + " gained " + std::to_string(exp) + " exp!";
    notifications.push_front(expString);

    if (m_experience / m_level >= 10)
    {
        m_level = m_experience / 10;
        std::string levelUpString = m_name + " has reached lvl " + std::to_string(m_level) + "!";
        notifications.push_front(levelUpString);
    }
    return notifications;
}
