#pragma once

#include <ncurses.h>
#include <string>

#include <file.hpp>

namespace Djinni::Screen {

// Important variables
extern int MAX_X, MAX_Y;
extern File* current_buffer;

extern void update_screen();
extern void handle_keypress(int key);

}
