#include <ncurses.h>

#include <runtime.hpp>
#include <screen.hpp>

namespace Djinni::Screen {
int MAX_X = 0;
int MAX_Y = 0;
File* current_buffer = NULL;
}
using namespace Djinni::Screen;

void Djinni::Screen::update_screen()
{
    erase();
    getmaxyx(stdscr, MAX_Y, MAX_X);
	// Debugging purposes
    // mvprintw(20, 20, "x:%d, y:%d", current_buffer->cursor_x, current_buffer->cursor_y);
    for (unsigned int i = 0; i < current_buffer->line_buffer.size(); i++) {
        mvprintw(i, 0, "%s", current_buffer->line_buffer[i].c_str());
    }
    // Move the cursor to it's correct place and refresh the screen
    move(current_buffer->cursor_y, current_buffer->cursor_x);
    refresh();
}

void Djinni::Screen::handle_keypress(int key)
{
    switch (key) {
    case 27: // ESC key
        Djinni::Runtime::running = false;
        break;

    case int('\n'): // Enter key
        // Insert a new line
        current_buffer->line_buffer.insert(current_buffer->line_buffer.begin() + 1 + current_buffer->cursor_y, "");

        // Copy over any 'leftovers' from the previous line
        current_buffer->line_buffer[current_buffer->cursor_y + 1] = current_buffer->line_buffer[current_buffer->cursor_y].substr(current_buffer->cursor_x);
        current_buffer->line_buffer[current_buffer->cursor_y].erase(current_buffer->cursor_x);

        // Set the correct cursor values
        current_buffer->cursor_x = 0;
        current_buffer->cursor_y++;
        break;

    case KEY_BACKSPACE:
    case 127:
        // Delete the character behind the cursor
        if (current_buffer->cursor_x > 0) {
            current_buffer->line_buffer[current_buffer->cursor_y].erase(current_buffer->cursor_x - 1, 1);
            current_buffer->cursor_x--;

        } else if (current_buffer->cursor_x == 0 && current_buffer->cursor_y > 0) {
            // The cursor is at the end of the line so delete this line
            current_buffer->cursor_x = current_buffer->line_buffer[current_buffer->cursor_y - 1].size();
            current_buffer->line_buffer[current_buffer->cursor_y - 1] += current_buffer->line_buffer[current_buffer->cursor_y];
            current_buffer->line_buffer.erase(current_buffer->line_buffer.begin() + current_buffer->cursor_y);
            current_buffer->cursor_y--;
        }
        break;

    case KEY_LEFT: // Left arrow
        if (current_buffer->cursor_x > 0) {
            current_buffer->cursor_x--;
        }
        break;

    case KEY_UP: // Up arrow
        if (current_buffer->cursor_y > 0) {
            if (current_buffer->cursor_x > current_buffer->line_buffer[current_buffer->cursor_y - 1].size()) {
                current_buffer->cursor_x = current_buffer->line_buffer[current_buffer->cursor_y - 1].size();
            }
            current_buffer->cursor_y--;
        }
        break;

    case KEY_RIGHT: // Right arrow
        if (current_buffer->cursor_x < current_buffer->line_buffer.at(current_buffer->cursor_y).size()) {
            current_buffer->cursor_x++;
        }
        break;

    case KEY_DOWN: // Down arrow
        if (current_buffer->cursor_y < current_buffer->line_buffer.size() - 1) {
            if (current_buffer->cursor_x > current_buffer->line_buffer[current_buffer->cursor_y + 1].size()) {
                current_buffer->cursor_x = current_buffer->line_buffer[current_buffer->cursor_y + 1].size();
            }
            current_buffer->cursor_y++;
        }
        break;

    default:
        // Insert the pressed key into the correct position on the line
        current_buffer->line_buffer.at(current_buffer->cursor_y).insert(current_buffer->cursor_x, 1, key);
        current_buffer->cursor_x++;
    }
}
