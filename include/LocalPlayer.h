#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

#include <Player.h>


class LocalPlayer : public Player
{
    public:
        LocalPlayer(Vector2 pos, std::string name);
        std::deque<string> Update(char input, char rmsg, sf::UdpSocket &socket) override final;

    protected:

    private:
};

#endif // LOCALPLAYER_H
