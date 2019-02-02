#include <ncurses/curses.h>
#include "Player.h"
#include "Map.h"
#include "Vector2.h"
#include "Enemy.h"

class World
{
public:
    World();
    void Run();

private:
    char input = ' ';

    Player m_player;
    Enemy m_enemy;
    Map m_map;
};
