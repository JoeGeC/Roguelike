#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include <Player.h>


class MultiPlayer : public Player
{
    public:
        MultiPlayer(Vector2 pos, std::string name);
        std::deque<string> Update(char input) override final;

    protected:

    private:
};

#endif // MULTIPLAYER_H
