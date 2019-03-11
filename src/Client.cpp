#include "Client.h"

Client::Client()
{
    //ctor
}

void Client::Run()
{
    sf::UdpSocket socket;

    sf::IpAddress recipient = "127.0.0.1"
    unsigned short port = 13000;
    if (socket.send(data, 256, recipient, port) != sf::Socket::Done)
    {
        PushNotification("Data not sent.");
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
