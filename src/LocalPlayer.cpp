#include "LocalPlayer.h"

LocalPlayer::LocalPlayer(Vector2 pos, std::string name) : Player(pos, name)
{
    //ctor
}

std::deque<string> LocalPlayer::Update(char input, char rmsg, sf::UdpSocket &socket)
{
    std::deque<string> notifications;

    Move(input, '@');

    return notifications;
}
