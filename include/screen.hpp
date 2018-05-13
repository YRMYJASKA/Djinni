/* include/screen.hpp
 *
 * The screen.cpp file is responsible for defining all the functions necessary to handle
 * user input and output to the screen. This file is (almost) the core of the whole 
 * editor.
 *
 * The source can be found in 'src/screen.cpp'
 */
#pragma once

#include <ncurses.h>
#include <string>

#include <file.hpp>

namespace Djinni {
namespace Screen {

    // Important variables
    extern unsigned int MAX_X, MAX_Y;
    extern File* current_buffer;

    extern void update_screen();
    extern void handle_keypress(int key);
    extern void echo_print(std::string text, int mode = 0);
    extern void echo_clear();
}
}
