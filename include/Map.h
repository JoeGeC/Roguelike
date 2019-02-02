#include "Vector2.h"

class Map
{
public:
    Map();
    char GetMapLoc(int posx, int posy) { return m_map[posx][posy]; }
    Vector2 GetMapSize() { return Vector2(sizeof(m_map) / sizeof(m_map[0]), sizeof(m_map[0])); }

private:
    char m_map[40][100];
};
