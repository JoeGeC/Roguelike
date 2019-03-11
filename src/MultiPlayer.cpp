#include "MultiPlayer.h"

MultiPlayer::MultiPlayer(Vector2 pos, std::string name) : Player(pos, name)
{
    //ctor
}

std::deque<string> MultiPlayer::Update(char input, sf::UdpSocket &socket)
{
    std::deque<string> notifications;

    std::size_t received;

    char data[256];
    sf::IpAddress recipient;
    unsigned short remote_port;

    if (socket.receive(data, 1, received, recipient, remote_port) != sf::Socket::Done)
    {
        notifications.push_front("Data not received");
    }

    Move(input, '@');

    return notifications;
}
