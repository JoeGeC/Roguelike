#include "World.h"

#include <iostream>

World::World()
{
    Player *player = new Player(Vector2(20, 50));
    m_entityVector.push_back(player);

    Enemy *enemy = new Enemy(Vector2(20, 40));
    m_entityVector.push_back(enemy);
}

World::~World()
{
    for (auto p : m_entityVector)
        delete p;
}

void World::Run()
{
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

        //Updates all entities
        for(auto p : m_entityVector)
        {
            if (!CheckCollision(p))
                p->Update(input);

            if (p->GetType() == EType::ePlayer && p->GetAlive() == false)
            {
                m_gameOver = true;
            }
        }

        DisplayStats();

        // Displaying
        refresh();

        if (m_gameOver == true)
        {
            break;
        }
    }

    while ((input = getch()) != 'q')
    {
        std::string gameOverString = "GAME OVER!";
        mvprintw(m_map.GetMapSize().x / 2, m_map.GetMapSize().y / 2, "%s", gameOverString.c_str());
    }
}

bool World::CheckCollision(Entity* p)
{
    for (auto i : m_entityVector)
    {
        if ((p->GetPos().x - 1 == i->GetPos().x && p->GetPos().y == i->GetPos().y) || (p->GetPos().x + 1 == i->GetPos().x && p->GetPos().y == i->GetPos().y)
        || (p->GetPos().x == i->GetPos().x && p->GetPos().y - 1 == i->GetPos().y) || (p->GetPos().x == i->GetPos().x && p->GetPos().y + 1 == i->GetPos().y)
        || (p->GetPos().x - 1 == i->GetPos().x && p->GetPos().y - 1 == i->GetPos().y) || (p->GetPos().x - 1 == i->GetPos().x && p->GetPos().y + 1 == i->GetPos().y)
        || (p->GetPos().x + 1 == i->GetPos().x && p->GetPos().y - 1 == i->GetPos().y) || (p->GetPos().x + 1 == i->GetPos().x && p->GetPos().y + 1 == i->GetPos().y))
        {
            p->Attack(i, m_map.GetMapSize());
            return true;
        }
    }

    return false;
}

void World::DisplayStats()
{
    move(m_map.GetMapSize().x + 1, 0);
    clrtoeol();

    for (auto p : m_entityVector)
    {
        if (p->GetType() == EType::ePlayer)
        {
            //print player health
            std::string playerHealthString = "Health: " + std::to_string(p->GetHealth());
            mvprintw(m_map.GetMapSize().x, 1, "%s", playerHealthString.c_str());
        }
    }

}
