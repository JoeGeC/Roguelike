#include "MultiPlayer.h"

MultiPlayer::MultiPlayer(Vector2 pos, std::string name) : Player(pos, name)
{
    //ctor
}

std::deque<string> MultiPlayer::Update(char input)
{
    std::deque<string> notifications;

    mvaddch(m_pos.x, m_pos.y, '@');

    return notifications;
}
