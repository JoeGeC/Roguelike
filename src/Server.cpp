#include "Server.h"

Server::Server()
{
    //ctor
}

void Server::Accepter()
{
    sf::TcpListener listener;
    sf::Socket::Status status = listener.listen(4302);
    if (status != sf::Socket::Done)
    {
        std::cerr << "Listen: " << status << std::endl;
        return;
    }

    while (1)
    {
        sf::TcpSocket *socket = new sf::TcpSocket;
        status = listener.accept(*socket);
        { // New!
            std::unique_lock<std::mutex> l(m);
            sockets.push_back(socket);
        }
        if (status != sf::Socket::Done)
        {
            std::cerr << "Accept: " << status << std::endl;
            return;
        }
        ClientInfo *c = new ClientInfo(socket, queue);
        std::thread([c]{c->tRecvLoop();}).detach();
    }
}

void Server::Run()
{
    std::thread(&Server::Accepter, this).detach();

    while(1)
    {
        std::string s = queue.pop(); // Blocking!
        std::cout << "Main thread: '" << s << "' \n";
        {
            std::unique_lock<std::mutex> l(m);
            for (auto socket : sockets) {
                sf::Socket::Status status = socket->send(s.c_str(), s.size());
                if (status != sf::Socket::Done) {
                    std::cout << "Sending failed: " << status << std::endl;
                }
            }
        }
    }
}


