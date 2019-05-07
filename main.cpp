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

    // Finishing the session with ncurses.
    endwin();
    return(0);
}
