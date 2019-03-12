#include "World.h"
#include <iostream>

World::World()
{
    m_player = new LocalPlayer(Vector2(20, 50), "Joe");
    m_entityVector.push_back(m_player);

    Enemy *enemy = new Enemy(Vector2(20, 40), "Enemy");
    m_entityVector.push_back(enemy);
    Enemy *enemy1 = new Enemy(Vector2(25, 40), "Enemy");
    m_entityVector.push_back(enemy);
}

World::~World()
{
    for (auto p : m_entityVector)
        delete p;
}

void World::Run()
{
    // Screen initialisation
    initscr();
    cbreak();
    curs_set(0);
    noecho();

    clear();

    //Connect with server and obtain its IP address
    m_serverIp = sf::IpAddress::Broadcast;
    char broadcastMsg[] = "Broadcast Message";

    if (m_socket.send(broadcastMsg, 256, m_serverIp, m_port) != sf::Socket::Done)
    {
        PushNotification("Data not sent to server.");
    }
    else
    {
        PushNotification("Data sent to server.");
    }

    size_t received;

    if(m_socket.receive(broadcastMsg, 256, received, m_serverIp, m_port) != sf::Socket::Done)
    {
        PushNotification("Data not received from server.");
    }
    else
    {
        PushNotification(broadcastMsg);
    }

    while ((input = getch()) != 'q')
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
                PushNotifications(p->Update(input, m_socket));

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
            break;
        }

        PrintNotifications();
    }

    do
    {
        std::string gameOverString = "GAME OVER!";
        mvprintw(m_map.GetMapSize().x / 2, m_map.GetMapSize().y / 2, "%s", gameOverString.c_str());
    } while ((input = getch()) != 'q');
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
