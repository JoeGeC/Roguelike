#include <ncurses/curses.h>
#include "Player.h"
#include "Map.h"
#include "Vector2.h"
#include "Enemy.h"
#include <vector>
#include <deque>

class World
{
public:
    World();
    ~World();
    void Run();

private:
    void DisplayStats();
    bool CheckCollision(Entity* p);
    void PrintNotifications();
    void PushNotification(string notification);

    std::deque<string> m_notifications;
    std::vector<Entity*> m_entityVector;
    Map m_map;

    bool m_gameOver { false };
    char input { ' ' };
};
