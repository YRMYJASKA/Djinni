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

    Djinni::File buffer;

    if (argv[1]) {
        buffer.set_filename(argv[1]);
    } else {
        buffer.set_filename("Untitled");
    }

    // Initialize the line buffer for the file
    buffer.load_file(buffer.get_filename());
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
