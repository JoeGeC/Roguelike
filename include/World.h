#ifndef WORLD_H
#define WORLD_H

#include <ncurses/curses.h>
#include "LocalPlayer.h"
#include "MultiPlayer.h"
#include "Map.h"
#include "Vector2.h"
#include "Enemy.h"
#include <vector>
#include <deque>
#include <SFML/Network.hpp>
#include "Queue.h"
#include "ClientInfo.h"
#include <thread>

class World
{
public:
    World();
    ~World();
    void RunClient();

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

    sf::UdpSocket m_udpSocket;
    sf::TcpSocket m_tcpSocket;
    sf::IpAddress m_serverIp;
    unsigned short m_port { 13000 };
    Queue<std::string> queue;
    std::string omsg;
    std::string rmsg;

private:
    void RunWorld();
};

#endif //WORLD_H
