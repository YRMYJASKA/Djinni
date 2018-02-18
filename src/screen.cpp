#include <ncurses.h>

#include <cmdline.hpp>
#include <miscellaneous.hpp>
#include <runtime.hpp>
#include <screen.hpp>
#include <settings.hpp>

namespace Djinni {
namespace Screen {
    unsigned int MAX_X = 0;
    unsigned int MAX_Y = 0;
    File* current_buffer = NULL;
}
}
using namespace Djinni::Screen;

void Djinni::Screen::update_screen()
{
    // Clear screen before editing and get window size
    erase();
    getmaxyx(stdscr, MAX_Y, MAX_X);

    // Proper formatting so line numbers won't mess up the other text
    if (Djinni::Settings::line_numbers) {
        Djinni::Runtime::line_digits = Djinni::Miscellaneous::digit_num(current_buffer->line_buffer.size());
    }

    if (current_buffer->cursor_y - (MAX_Y - 3) > Djinni::Runtime::line_offset && current_buffer->cursor_y > MAX_Y - 3) {
        Djinni::Runtime::line_offset = current_buffer->cursor_y - (MAX_Y - 3);
    } else if (current_buffer->cursor_y < Djinni::Runtime::line_offset) {
        Djinni::Runtime::line_offset--;
    }

    // Print the lines in the bufffer onto the screen
    int x = Djinni::Runtime::line_offset;
    for (unsigned int i = 0; (i < MAX_Y - 2 && i + Djinni::Runtime::line_offset < current_buffer->line_buffer.size()); i++) {

        if (Djinni::Settings::line_numbers) {
            mvprintw(i, 1, "%d", i + Djinni::Runtime::line_offset + 1);
        }
        mvprintw(i, Djinni::Runtime::line_digits + 2, "%c", ' ');
        mvprintw(i, Djinni::Runtime::line_digits + 3, "%s", current_buffer->line_buffer[i + Djinni::Runtime::line_offset].c_str());
        x++;
    }

    // Print the bottom information screen (very minimal and not final)
    mvprintw(MAX_Y - 1, 0, "%s   ", current_buffer->get_filename().c_str());
    printw("%d, %d", current_buffer->cursor_x + 1, current_buffer->cursor_y + 1);

    // Print the last output of the command line
    mvprintw(MAX_Y - 2, 0, "%s", Djinni::Commandline::echo.c_str());

    // Move the cursor to it's correct place and refresh the screen
    move(current_buffer->cursor_y - Djinni::Runtime::line_offset, current_buffer->cursor_x + Djinni::Runtime::line_digits + 3);

    // Finally print all the changes onto the screen
    refresh();
}

// "Main" function the whole program
void Djinni::Screen::handle_keypress(int key)
{

    switch (key) {
    // Ctrl-B pressed -> close the program
    case 2:
        Djinni::Runtime::running = false;
        break;
    // Ctrl-S -> save the file
    case 19:
        current_buffer->save_file(current_buffer->get_filename());
        break;
    // Ctrl-D -> Open command line for Djinni
    case 4:
        Djinni::Commandline::init_commandline();
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
        // Quick fix to prevent non-printable characters from being printed
        if (key < 32) {
            break;
        }

        // Insert the pressed key into the correct position on the line
        current_buffer->line_buffer.at(current_buffer->cursor_y).insert(current_buffer->cursor_x, 1, key);
        current_buffer->cursor_x++;
    }
}
