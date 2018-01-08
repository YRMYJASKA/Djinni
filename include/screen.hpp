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
}
}
