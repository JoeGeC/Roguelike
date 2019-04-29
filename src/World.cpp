#include "World.h"
#include <iostream>

World::World()
{
    m_player = new LocalPlayer(Vector2(9, 25), "Joe");
    m_entityVector.push_back(m_player);

    Enemy *enemy = new Enemy(Vector2(20, 40), "Enemy1");
    m_entityVector.push_back(enemy);
    Enemy *enemy1 = new Enemy(Vector2(25, 50), "Enemy2");
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

    //Gets id of client from server and sets it clientside
    string id = "";
    id = queue.pop();
    PushNotification(id);
    c->id = std::atoi(id.c_str());
    m_player->SetId(std::atoi(id.c_str()));

    switch(c->id)
    {
    case 0:
        m_player->SetPos(Vector2(9, 25));
        break;
    case 1:
        m_player->SetPos(Vector2(9, 75));
        break;
    case 2:
        m_player->SetPos(Vector2(31, 25));
        break;
    case 3:
        m_player->SetPos(Vector2(31, 75));
        break;
    }

    while(1)
    {
        RunWorld();

        std::string msg = "";

        m_rmsg = "";

        queue.pop(msg);
        if (msg != "")
        {
            PushNotification(msg);
            m_rmsg = msg;
        }

        if(m_input != ' ')
        {
            m_omsg = std::to_string(c->id);
            m_omsg += m_input;
            c->tSend(m_omsg);
            m_input = ' ';
        }
    }
}

void World::RunWorld()
{
    if(m_rmsg[0] == 'n')
    {
        switch(m_rmsg[1])
        {
        case '0' :
        {
            MultiPlayer *player1 = new MultiPlayer(Vector2(9, 25), "Tom");
            player1->SetId(0);
            m_entityVector.push_back(player1);
            PushNotification("Player 1 joined!");
            m_numPlayers++;
            break;
        }
        case '1' :
        {
            MultiPlayer *player2 = new MultiPlayer(Vector2(9, 75), "Bob");
            player2->SetId(1);
            m_entityVector.push_back(player2);
            PushNotification("Player 2 joined!");
            m_numPlayers++;
            break;
        }
        case '2' :
        {
            MultiPlayer *player3 = new MultiPlayer(Vector2(31, 25), "Sarah");
            player3->SetId(2);
            m_entityVector.push_back(player3);
            PushNotification("Player 3 joined!");
            m_numPlayers++;
            break;
        }
        case '3' :
        {
            MultiPlayer *player4 = new MultiPlayer(Vector2(31, 75), "Paula");
            player4->SetId(3);
            m_entityVector.push_back(player4);
            PushNotification("Player 4 joined!");
            m_numPlayers++;
            break;
        }
        }
    }
    else if(m_rmsg != "")
    {
        for(auto &player : m_entityVector)
        {
            if(((char)player->GetId()) == m_rmsg[0] - 48)
            {
                player->SetNextMove(m_rmsg[1]);
            }
        }
    }

    DisplayStats();

    PrintNotifications();

    if(m_playerTurn == m_player->GetId())
    {
        if(m_input = getch())
        {
            Game();
            NextTurn();
        }

    }
    else if(m_rmsg != "" && m_rmsg[0] != 'n')
    {
        Game();
        NextTurn();
    }

    DisplayStats();

    PrintNotifications();
}

void World::Game()
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

    //Updates all entities
    for(auto &p : m_entityVector)
    {
        if(p->GetAlive())
        {
            PushNotifications(p->Update(m_input));

            CheckCollision(p);

            p->CheckAlive();
        }

        if (p->GetType() == EType::ePlayer && !p->GetAlive())
        {
            m_gameOver = true;
        }
    }

    // Displaying
    refresh();

    if (m_gameOver == true)
    {
        //endgame
    }
}


void World::NextTurn()
{
    m_playerTurn++;
    if(m_playerTurn >= m_numPlayers)
    {
        m_playerTurn = 0;
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
