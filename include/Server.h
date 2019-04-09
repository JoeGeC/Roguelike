#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <SFML/Network.hpp>
#include "ClientInfo.h"
#include <thread>
#include <list>


class Server
{
    public:
        Server();
        ~Server();
        void Run();

    protected:

    private:
        void Accepter();
        Queue<std::string> queue;
        std::list<sf::TcpSocket*> sockets;
        std::mutex m;
        sf::TcpListener listener;
};

#endif // SERVER_H
