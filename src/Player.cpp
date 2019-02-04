#include "Player.h"
#include <ncurses/curses.h>

Player::Player(Vector2 pos) : Entity(pos)
{
    //ctor
}

void Player::Update(char input)
{
    if (m_health <= 0)
    {
        m_health = 0;
        m_alive = false;
    }
    Move(input, '@');
}

//TODO:: NOT WORKING
void Player::Attack(Entity* target, Vector2 mapSize)
{
    std::string playerOptionString = "(A)ttack or (1-9)Flee?";
    mvprintw(3, mapSize.y + 1, "%s", playerOptionString.c_str());

    char input;
    do
    {
        input = getch();
    }while (input != 'a' || input != '1' || input != '2' || input != '3' || input != '4' || input != '5' || input != '6' || input != '7' || input != '8' || input != '9');

    if (input == 'a')
        target->SetHealth(-1);
    else
        Move(input, '@');
}
