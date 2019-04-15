#include <ncurses/curses.h>
#include <iostream>
#include "Server.h"
#include "World.h"

int main(void)
{
    char input;
    while (input != 's' && input != 'c')
    {
        std::cout << "(s)erver or (c)lient?" << std::endl;
        std::cin >> input;
    }

    if(input == 's')
    {
        Server server;
        server.Run();
    }
    else
    {
        // Screen initialisation
        initscr();
        cbreak();
        curs_set(0);
        noecho();

        World world;
        world.RunClient();
    }

    /*sf::UdpSocket socket;
    if(socket.bind(4300) != sf::Socket::Done)
    {
        std::cout << "Socket not bound" << std::endl;
    }

    char data[1] = {'J'};
    sf::IpAddress recipient = "152.105.67.142";
    unsigned short remote_port {4300};
    if (socket.send(data, sizeof(data), recipient, remote_port) != sf::Socket::Done)
    {
        std::cout << "data not sent" << std::endl;
    }

    std::size_t received;

    if (socket.receive(data, 1, received, recipient, remote_port) != sf::Socket::Done)
    {
        std::cout << "data not received" << std::endl;
    }

    switch (data[1])
    {
        case 'm':
        break;
        case 'a': // "aes"
        // ... look at other parts of the message
        break;
    }*/

    // Finishing the session with ncurses.
    endwin();
    return(0);
}
