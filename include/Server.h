#ifndef SERVER_H
#define SERVER_H

#include <World.h>


class Server : public World
{
    public:
        Server();
        void Run() override final;

    protected:

    private:
};

#endif // SERVER_H
