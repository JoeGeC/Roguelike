#include "Map.h"

Map::Map()
{
    for (int x = 0; x < GetMapSize().x; x++)
    {
        for (int y = 0; y < GetMapSize().y; y++)
        {
            m_map[x][y] = ' ';
        }
    }
    for(int i = 0; i < GetMapSize().y; i++)
    {
        m_map[0][i] = 'W';
        m_map[(int)GetMapSize().x - 1][i] = 'W';
    }
    for(int i = 0; i < GetMapSize().x; i++)
    {
        m_map[i][0] = 'W';
        m_map[i][(int)GetMapSize().y - 1] = 'W';
    }
}

Entity* Map::GetEntityAtLoc(Vector2 pos, std::vector<Entity*> entityVector)
{
    for(auto p : entityVector)
    {
        if(p->GetPos() == pos)
        {
            return p;
        }
    }
}
