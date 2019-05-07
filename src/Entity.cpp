#include "Entity.h"

Entity::Entity(Vector2 pos, std::string name) : m_pos(pos), m_name(name)
{
    //ctor
}

Entity::~Entity()
{

}

void Entity::Move(char input, char symbol)
{
    switch (input)
    {
    case '7':
        if (mvinch(m_pos.x - 1, m_pos.y) == ' ' && mvinch(m_pos.x, m_pos.y - 1) == ' ' && mvinch(m_pos.x - 1, m_pos.y - 1) == ' ')
        {
            m_pos.x--;
            m_pos.y--;
        }
        break;
    case '9':
        if (mvinch(m_pos.x - 1, m_pos.y) == ' ' && mvinch(m_pos.x, m_pos.y + 1) == ' ' && mvinch(m_pos.x - 1, m_pos.y + 1) == ' ')
        {
            m_pos.x--;
            m_pos.y++;
        }
        break;
    case '1':
        if (mvinch(m_pos.x + 1, m_pos.y) == ' ' && mvinch(m_pos.x, m_pos.y - 1) == ' ' && mvinch(m_pos.x + 1, m_pos.y - 1) == ' ')
        {
            m_pos.x++;
            m_pos.y--;
        }
        break;
    case '3':
        if (mvinch(m_pos.x + 1, m_pos.y) == ' ' && mvinch(m_pos.x, m_pos.y + 1) == ' ' && mvinch(m_pos.x + 1, m_pos.y + 1) == ' ')
        {
            m_pos.x++;
            m_pos.y++;
        }
        break;
    case '8':
        if (mvinch(m_pos.x - 1, m_pos.y) == ' ')
            m_pos.x--;
        break;
    case '6':
        if (mvinch(m_pos.x, m_pos.y + 1) == ' ')
            m_pos.y++;
        break;
    case '2':
        if (mvinch(m_pos.x + 1, m_pos.y) == ' ')
            m_pos.x++;
        break;
    case '4':
        if (mvinch(m_pos.x, m_pos.y - 1) == ' ')
            m_pos.y--;
        break;
    default:
        break;
    }

    DisplayEntity(symbol);

}

void Entity::DisplayEntity(char symbol)
{
    mvaddch(m_pos.x, m_pos.y, symbol);
}

bool Entity::CheckAlive()
{
    if (m_health <= 0)
    {
        m_health = 0;
        m_alive = false;
        return false;
    }
    else
        return true;
}

std::deque<string> Entity::Die(Entity* killer)
{
    std::deque<string> notifications;

    m_alive = false;

    std::deque<string> expStrings = killer->GainExperience(m_defeatExp);
    for (auto s : expStrings)
    {
        notifications.push_front(s);
    }

    string deathString = m_name + " has died!";
    notifications.push_front(deathString);

    return notifications;
}
