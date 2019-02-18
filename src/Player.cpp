#include "Player.h"
#include "Map.h"
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
    target->SetHealth(-1);

    int enemyHealthPos = mapSize.x + 2;

    move(enemyHealthPos, 0);
    clrtoeol();

    std::string enemyHealthString = "Enemy health: " + std::to_string(target->GetHealth());
    mvprintw(enemyHealthPos, 1, "%s", enemyHealthString.c_str());
}
