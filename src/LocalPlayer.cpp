#include "LocalPlayer.h"

LocalPlayer::LocalPlayer(Vector2 pos, std::string name) : Player(pos, name)
{
    //ctor
}

std::deque<string> LocalPlayer::Update(char input, sf::UdpSocket &socket)
{
    std::deque<string> notifications;

    sf::IpAddress recipient = "127.0.0.1";
    unsigned short remote_port {4300};

    if (socket.send(&input, sizeof(input), recipient, remote_port) != sf::Socket::Done)
    {
        notifications.push_front("Could not send data.");
    }

    Move(input, '@');

    return notifications;
}
