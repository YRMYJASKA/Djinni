/* src/settings.cpp
 *
 * The header can be found in 'include/settings.hpp'
 */

#include <fstream>
#include <ncurses.h>

#include <settings.hpp>

namespace Djinni {
namespace Settings {
    // Default settings
    bool line_numbers;
    bool cursorxy;
}
}

/* init_settings:
 * Sets the default settings for the Djinni editor.
 *
 * */
void Djinni::Settings::init_settings()
{
    // Init the default colours
    init_pair(ERROR_TEXT, COLOR_WHITE, COLOR_RED);
    init_pair(SUCCESS_TEXT, COLOR_GREEN, COLOR_BLACK);
    init_pair(WARNING_TEXT, COLOR_WHITE, COLOR_YELLOW);
    init_pair(CMD_PROMPT, COLOR_CYAN, COLOR_BLACK);

    // Other settings
    line_numbers = true;
    cursorxy = true;
}

/* load_settings:
 * Loads the configurations from the file located in ~/.djinnirc
 */
void Djinni::Settings::load_settings(const char* file)
{
}
