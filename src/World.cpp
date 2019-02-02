#include "World.h"

#include <iostream>

World::World(): m_player(Vector2(20, 50)), m_enemy(Vector2(2, 2))
{

}

void World::Run()
{
    mvaddch(m_player.GetPos().x, m_player.GetPos().y, '@');

    while ((input = getch()) != 'q')
    {
        //print map
        for (int x = 0; x < m_map.GetMapSize().x; x++)
        {
            for (int y = 0; y < m_map.GetMapSize().y; y++)
            {
                if(m_map.GetMapLoc(x, y) != ' ')
                    mvaddch(x, y, m_map.GetMapLoc(x, y));
            }
        }

        //print player health
        std::string playerHealthString = "Health: " + std::to_string(m_player.GetHealth());
        mvprintw(m_map.GetMapSize().x, 1, "%s", playerHealthString.c_str());

        //move and print player
        m_player.Move(input, '@');

        //TODO:: NOT WORKING - passes in char code not symbol
        char randDir = 2;
        m_enemy.Move(randDir, 'E');

        // Displaying
        refresh();
    }

}
