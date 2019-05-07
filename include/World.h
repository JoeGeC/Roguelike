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
    void DisplayStats(); // Displays stats under map
    bool CheckCollision(Entity* p); // Checks for collisions against all entities
    void PrintNotifications(); // Prints notifications on side of map
    void PushNotification(string notification); // Push one notification to be displayed
    void PushNotifications(std::deque<string> notifications); // Push multiple notifications to be displayed
    void NextTurn(); // Call at end of turn to go onto next

    std::deque<string> m_notifications; //holds notifications to be displayed
    std::vector<Entity*> m_entityVector; // holds all entities
    LocalPlayer *m_player;
    Map m_map;

    bool m_gameOver { false };
    char m_input { ' ' };
    int m_numPlayers { 0 };
    int m_playerTurn { 0 };

    Queue<std::string> queue;
    std::string m_omsg; //outgoing message
    std::string m_rmsg; //received message

private:
    void RunWorld();
    void Game();
};

#endif //WORLD_H
