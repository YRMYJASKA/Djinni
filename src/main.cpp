#include <ncurses.h>
#include <version.h>

bool running = true;
int MAX_X, MAX_Y;
int CURR_X = 0, CURR_Y = 0;

int main(int argc, char* argv[])
{
    // Initialize the program with the correct ncurses commands
    initscr();
    noecho();
    raw();

    while (running) {
        char keypress = getch();

        switch (keypress) {
        case 27:
            running = false;
            break;
        default:
            continue;
        }
    }
    // End the program
    endwin();
}
