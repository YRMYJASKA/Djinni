/*
 * MIT License
 * 
 * Copyright (c) 2018 Jyry Hjelt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <string.h>

#include <cmdline.hpp>
#include <commands.hpp>
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

    // Load all the commands into the command list
    Djinni::init_core_commands();
    Djinni::Commandline::command_list.insert(std::end(Djinni::Commandline::command_list), std::begin(Djinni::core_commands), std::end(Djinni::core_commands));

    // Initialize the program with the correct ncurses commands
    initscr();
    noecho();
    raw();
    keypad(stdscr, TRUE);
    start_color();

	// Initialize the colour pairs
	// id | Desc.
	// 0: 	Clean (white on black)
	// 1: 	Error
	// 2: 	Success
	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);

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
