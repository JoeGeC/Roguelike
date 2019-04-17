#include "Server.h"

Server::Server()
{
    //ctor
}

Server::~Server()
{
    listener.close();
}

void Server::Accepter()
{
    sf::Socket::Status status = listener.listen(4300);
    if (status != sf::Socket::Done)
    {
        std::cerr << "Listen: " << status << std::endl;
        return;
    }

    while (1)
    {
        ClientInfo *client = new ClientInfo(queue);
        status = listener.accept(*client->GetTSocket());
        { // New!
            std::unique_lock<std::mutex> l(m);
            client->id = clients.size();
            clients.push_back(client);
            client->tSend(std::to_string(client->id));
            for(auto c : clients)
            {
                if(c->id != client->id)
                {
                    std::string newClient = "n" + std::to_string(client->id);
                    c->tSend(newClient);
                    std::string existingClient = "n" + std::to_string(c->id);
                    client->tSend(existingClient);
                }
            }
        }
        if (status != sf::Socket::Done)
        {
            std::cerr << "Accept: " << status << std::endl;
            delete client;
            return;
        }
        std::thread([client]{client->tRecvLoop();}).detach();
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
            for (auto client : clients)
            {
                if(client->id != (unsigned short)s[0] - 48)
                {
                    sf::Socket::Status status = client->GetTSocket()->send(s.c_str(), s.size());
                    if (status != sf::Socket::Done) {
                        std::cout << "Sending failed: " << status << std::endl;
                    }
                }
            }
        }
    }
}


