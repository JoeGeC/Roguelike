#ifndef WORLD_H
#define WORLD_H

#include <ncurses/curses.h>
#include "LocalPlayer.h"
#include "Map.h"
#include "Vector2.h"
#include "Enemy.h"
#include <vector>
#include <deque>
#include <SFML/Network.hpp>

class World
{
public:
    World();
    ~World();
    void Run();

protected:
    void DisplayStats();
    bool CheckCollision(Entity* p);
    void PrintNotifications();
    void PushNotification(string notification);
    void PushNotifications(std::deque<string> notifications);

    std::deque<string> m_notifications;
    std::vector<Entity*> m_entityVector;
    LocalPlayer *m_player;
    Map m_map;

    bool m_gameOver { false };
    char input { ' ' };

    sf::UdpSocket m_socket;
    sf::IpAddress m_serverIp;
    unsigned short m_port { 13000 };
};

#endif //WORLD_H
