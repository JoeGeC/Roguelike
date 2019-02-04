#include <ncurses/curses.h>
#include "Player.h"
#include "Map.h"
#include "Vector2.h"
#include "Enemy.h"
#include <vector>

class World
{
public:
    World();
    ~World();
    void Run();

private:
    void DisplayStats();
    bool CheckCollision(Entity* p);

    std::vector<Entity*> m_entityVector;
    Map m_map;

    bool m_gameOver { false };
    char input { ' ' };
};
