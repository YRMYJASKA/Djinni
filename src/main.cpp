#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <string.h>

#include <file.hpp>
#include <miscellaneous.hpp>
#include <runtime.hpp>
#include <screen.hpp>
#include <version.h>

int main(int argc, char* argv[])
{
    // Create the buffer for the text.
    Djinni::File buffer;

    // Handle the command line arguments (not final)
    if (argv[1]) {
        if (!strcmp("--help", argv[1])) {
            Djinni::Miscellaneous::print_help();
            return 0;
        } else if (!strcmp("--version", argv[1])) {
            std::cout << "Djinni " << VERSION_STRING << '\n';
            return 0;
        } else {
            buffer.set_filename(argv[1]);
            buffer.load_file(buffer.get_filename());
        }
    } else {
        buffer.set_filename("Untitled");
    }

    // Initialize the program with the correct ncurses commands
    initscr();
    noecho();
    raw();
    keypad(stdscr, TRUE);
    start_color();

    // Initialize the line buffer for the file
    Djinni::Screen::current_buffer = &buffer;

    // The main loop
    while (Djinni::Runtime::running) {
		// Refresh the screen
        Djinni::Screen::update_screen();

		// Get and handle any key press from the user
        int keypress = getch();
        Djinni::Screen::handle_keypress(keypress);
    }

    // End the program
    endwin();
}
