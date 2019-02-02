#include <ncurses/curses.h>
#include "World.h"

int main(void)
{
    // Screen initialisation
    initscr();
    cbreak();
    curs_set(0);
    noecho();

    clear();

    World world;
    world.Run();

    // Finishing the session with ncurses.
    endwin();
    return(0);
}
