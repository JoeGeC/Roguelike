#include "World.h"
#include <iostream>

World::World()
{
    m_player = new LocalPlayer(Vector2(20, 50), "Joe");
    m_entityVector.push_back(m_player);
    MultiPlayer *player2 = new MultiPlayer(Vector2(10, 50), "Bob");
    m_entityVector.push_back(player2);

    Enemy *enemy = new Enemy(Vector2(20, 40), "Enemy1");
    m_entityVector.push_back(enemy);
    Enemy *enemy1 = new Enemy(Vector2(25, 40), "Enemy2");
    m_entityVector.push_back(enemy1);
}

World::~World()
{
    for (auto p : m_entityVector)
        delete p;
}

void World::RunClient()
{
    ClientInfo *c = new ClientInfo(queue);
    c->address = sf::IpAddress::Broadcast;
    char broadcastMessage[] = "Broadcast";
    c->uSend(broadcastMessage);
    c->uRecv();

    // we need to know the address and port of the server
    c->connect();
    std::thread([c] {c->tRecvLoop();}).detach();

    while(1)
    {
        RunWorld();

        std::string msg = "";

        queue.pop(msg);
        if (msg != "")
        {
            PushNotification(msg);
            rmsg = msg;
        }
        else
        {
            rmsg = "";
        }
        omsg += std::to_string(c->id);
        c->tSend(omsg);
    }
}

void World::RunWorld()
{

    //while ((input = getch()) != 'q')
    //{
    if((input = getch()))
    {
        clear();

        //print map
        for (int x = 0; x < m_map.GetMapSize().x; x++)
        {
            for (int y = 0; y < m_map.GetMapSize().y; y++)
            {
                if(m_map.GetMapLoc(x, y) != ' ')
                    mvaddch(x, y, m_map.GetMapLoc(x, y));
            }
        }

        DisplayStats();

        //Updates all entities
        for(auto p : m_entityVector)
        {
            if(p->GetAlive())
            {
                PushNotifications(p->Update(input, rmsg[0], m_udpSocket));

                CheckCollision(p);

                p->CheckAlive();
            }

            if (p->GetType() == EType::ePlayer && !p->GetAlive())
            {
                m_gameOver = true;
            }
        }

        DisplayStats();

        // Displaying
        refresh();

        if (m_gameOver == true)
        {
            //endgame
        }

        PrintNotifications();
    //}

//    do
//    {
//        std::string gameOverString = "GAME OVER!";
//        mvprintw(m_map.GetMapSize().x / 2, m_map.GetMapSize().y / 2, "%s", gameOverString.c_str());
//    }
//    while ((input = getch()) != 'q');

    omsg = input;
    }
}

bool World::CheckCollision(Entity* p)
{
    for (auto i : m_entityVector)
    {
        if (i->GetAlive() &&
                ((p->GetPos().x - 1 == i->GetPos().x && p->GetPos().y == i->GetPos().y) || (p->GetPos().x + 1 == i->GetPos().x && p->GetPos().y == i->GetPos().y)
                 || (p->GetPos().x == i->GetPos().x && p->GetPos().y - 1 == i->GetPos().y) || (p->GetPos().x == i->GetPos().x && p->GetPos().y + 1 == i->GetPos().y)
                 || (p->GetPos().x - 1 == i->GetPos().x && p->GetPos().y - 1 == i->GetPos().y) || (p->GetPos().x - 1 == i->GetPos().x && p->GetPos().y + 1 == i->GetPos().y)
                 || (p->GetPos().x + 1 == i->GetPos().x && p->GetPos().y - 1 == i->GetPos().y) || (p->GetPos().x + 1 == i->GetPos().x && p->GetPos().y + 1 == i->GetPos().y)))
        {
            //attack automatically and send required notifications to list
            std::deque<string> notifications = p->Attack(i, m_map.GetMapSize());
            PushNotifications(notifications);
            return true;
        }
    }
    return false;
}

void World::DisplayStats()
{
    move(m_map.GetMapSize().x, 0);
    clrtoeol();

    //print player health
    std::string playerHealthString = "Health: " + std::to_string(m_player->GetHealth());
    mvprintw(m_map.GetMapSize().x, 1, "%s", playerHealthString.c_str());

}

void World::PrintNotifications()
{
    for(size_t i = 0; i < m_notifications.size(); i++)
    {
        mvprintw(i * 2 + 1, m_map.GetMapSize().y + 1, "%s", m_notifications.at(i).c_str());
    }
}

void World::PushNotification(string notification)
{
    m_notifications.push_front(notification);

    while (m_notifications.size() > 20)
    {
        m_notifications.pop_back();
    }
}

void World::PushNotifications(std::deque<string> notifications)
{
    for(auto s : notifications)
    {
        m_notifications.push_front(s);
    }

    while (m_notifications.size() > 20)
    {
        m_notifications.pop_back();
    }
}
