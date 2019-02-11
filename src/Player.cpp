#include "Player.h"
#include <ncurses/curses.h>

Player::Player(Vector2 pos) : Entity(pos)
{
    //ctor
}

void Player::Update(char input)
{
    Move(input, '@');
}

//TODO:: NOT WORKING
void Player::Attack(Entity* target, Vector2 mapSize)
{
    std::string playerOptionString = "(A)ttack or (1-9)Flee?";
    mvprintw(3, mapSize.y + 1, "%s", playerOptionString.c_str());

    int enemyHealthPos = mapSize.x + 2;

    move(enemyHealthPos, 0);
    clrtoeol();

    std::string enemyHealthString = "Enemy health: " + std::to_string(target->GetHealth());
    mvprintw(enemyHealthPos, 1, "%s", enemyHealthString.c_str());

    DisplayEntity('@');

    char input;
    input = getch();

    if (input == 'a')
    {
        std::string debugString = "a";
        mvprintw(10, mapSize.y + 1, "%s", debugString.c_str());

        target->SetHealth(-1);

    }
    else if (input == '1' || input == '2' || input == '3' || input == '4' || input == '5' || input == '6' || input == '7' || input == '8' || input == '9')
        Move(input, '@');
}
