#include "Server.h"

Server::Server()
{
    //ctor
}

void Server::Run()
{
    sf::UdpSocket socket;
    sf::IpAddress sender;
    unsigned short port = 13000;
    char data[256];
    unsigned short sender_port;

    // bind the socket to a port - only on a server
    if (socket.bind(port) != sf::Socket::Done)
    {
        std::cout << "Socket not bound." << std::endl;
    }
    else
    {
        std::cout << "Socket bound to " << port << std::endl;
    }

    while (1)
    {
        std::cout << "Waiting to receive data." << std::endl;

        std::size_t received;

        if (socket.receive(data, 256, received, sender, sender_port) != sf::Socket::Done)
        {
            std::cout << "Data not received." << std::endl;
        }
        else
        {
            std::cout << data << std::endl;
        }
        // Echo back the data.
        if (socket.send(data, 256, sender, sender_port) != sf::Socket::Done)
        {
            std::cout << "Data not sent." << std::endl;
        }
    }
}
