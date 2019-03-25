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

//    while (1)
//    {
//        std::cout << "Waiting to receive data." << std::endl;
//
//        std::size_t received;
//
//        if (socket.receive(data, 256, received, sender, sender_port) != sf::Socket::Done)
//        {
//            std::cout << "Data not received." << std::endl;
//        }
//        else
//        {
//            std::cout << data << std::endl;
//        }
//        // Echo back the data.
//        if (socket.send(data, 256, sender, sender_port) != sf::Socket::Done)
//        {
//            std::cout << "Data not sent." << std::endl;
//        }
//    }

    sf::TcpListener listener;
    unsigned short tcpPort = 1299;

    if(listener.listen(tcpPort) != sf::Socket::Done)
    {
        std::cout << "Failed to attach to the port." << std::endl;
    }

    sf::TcpSocket client;
    if (listener.accept(client) == sf::Socket::Done)
    {
        std::cout << "Client connected." << std::endl;

    }

    size_t tcpReceived;
    char buffer[256];
    if(client.receive(buffer, 256, tcpReceived) != sf::Socket::Done)
    {
        std::cout << "TCP data not received." << std::endl;
    }
    else
    {
        std::cout << "TCP data received: " << buffer << std::endl;
    }


    if(client.send(buffer, sizeof(buffer)) != sf::Socket::Done)
    {
        std::cout << "TCP data not sent." << std::endl;
    }
    else
    {
        std::cout << "TCP data sent." << std::endl;
    }
}
