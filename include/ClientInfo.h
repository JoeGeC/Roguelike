#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <SFML/Network.hpp>
#include "Queue.h"

struct Message
{
    enum class Type
    {
        Disconnect,
        Standard
        //could add position, attack, spell, etc...
    };

    Type type = Type::Standard;
    unsigned short senderID;
    char payload[];
};

class ClientInfo
{
    public:
        unsigned short id;
        std::string username;
        ClientInfo(Queue<std::string> &q);
        void setUdp(sf::UdpSocket *s, sf::IpAddress a, unsigned short p);
        bool connect(); //TCP
        bool tSend(std::string msg);
        bool tRecv(std::string &s); // optional
        bool tRecvLoop(); // thread
        bool uSend(std::string msg);
        bool uRecv(); // optional
        bool uRecvLoop(); //Runs in a thread
        void push(std::string &s); //Enqueues
        std::string pop(); //Dequeues
        sf::IpAddress address; //For TCP connect and UDP send

        sf::TcpSocket* GetTSocket() { return tSocket; }

    protected:

    private:

        sf::UdpSocket *uSocket;
        unsigned short uPort = 4303; //For UDP send
        sf::TcpSocket *tSocket; //Could use smart pointers
        unsigned short tPort = 4300; //For TCP connect
        Queue<std::string> &q; //Message to be defined
};

#endif // CLIENTINFO_H
