#include <ncurses.h>
#include <version.h>

#include <file.hpp>
#include <runtime.hpp>
#include <screen.hpp>

int main(int argc, char* argv[])
{
    // Initialize the program with the correct ncurses commands
    initscr();
    noecho();
    raw();
    keypad(stdscr, TRUE);
	start_color();

    // Initialize the line buffer for the file
    Djinni::File buffer = Djinni::File("Untitled");
    Djinni::Screen::current_buffer = &buffer;

	// The main loop
    while (Djinni::Runtime::running) {

        Djinni::Screen::update_screen();

        int keypress = getch();
        Djinni::Screen::handle_keypress(keypress);
    }

    // End the program
    endwin();
}
