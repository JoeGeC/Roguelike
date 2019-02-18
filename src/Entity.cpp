#include <ncurses/curses.h>
#include "Entity.h"

Entity::Entity(Vector2 pos) : m_pos(pos)
{
    //ctor
}

Entity::~Entity()
{

}

void Entity::Move(char input, char symbol)
{
    mvaddch(m_pos.x, m_pos.y, '.');
    switch (input)
    {
    case '7':
        if (mvinch(m_pos.x - 1, m_pos.y) != 'W' && mvinch(m_pos.x, m_pos.y - 1) != 'W' && mvinch(m_pos.x - 1, m_pos.y - 1) != 'W')
        {
            m_pos.x--;
            m_pos.y--;
        }
        break;
    case '9':
        if (mvinch(m_pos.x - 1, m_pos.y) != 'W' && mvinch(m_pos.x, m_pos.y + 1) != 'W' && mvinch(m_pos.x - 1, m_pos.y + 1) != 'W')
        {
            m_pos.x--;
            m_pos.y++;
        }
        break;
    case '1':
        if (mvinch(m_pos.x + 1, m_pos.y) != 'W' && mvinch(m_pos.x, m_pos.y - 1) != 'W' && mvinch(m_pos.x + 1, m_pos.y - 1) != 'W')
        {
            m_pos.x++;
            m_pos.y--;
        }
        break;
    case '3':
        if (mvinch(m_pos.x + 1, m_pos.y) != 'W' && mvinch(m_pos.x, m_pos.y + 1) != 'W' && mvinch(m_pos.x + 1, m_pos.y + 1) != 'W')
        {
            m_pos.x++;
            m_pos.y++;
        }
        break;
    case '8':
        if (mvinch(m_pos.x - 1, m_pos.y) != 'W')
            m_pos.x--;
        break;
    case '6':
        if (mvinch(m_pos.x, m_pos.y + 1) != 'W')
            m_pos.y++;
        break;
    case '2':
        if (mvinch(m_pos.x + 1, m_pos.y) != 'W')
            m_pos.x++;
        break;
    case '4':
        if (mvinch(m_pos.x, m_pos.y - 1) != 'W')
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
        Die();
        return false;
    }
    else
        return true;
}

void Entity::Die()
{

}
