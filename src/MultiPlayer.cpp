#include "MultiPlayer.h"

MultiPlayer::MultiPlayer(Vector2 pos, std::string name) : Player(pos, name)
{
    //ctor
}

std::deque<string> MultiPlayer::Update(char input)
{
    std::deque<string> notifications;

    Move(m_move, '@');

    return notifications;
}
