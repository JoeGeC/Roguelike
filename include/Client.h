#ifndef CLIENT_H
#define CLIENT_H

#include <World.h>


class Client : public World
{
    public:
        Client();
        void Run() override final;

    protected:

    private:
};

#endif // CLIENT_H
