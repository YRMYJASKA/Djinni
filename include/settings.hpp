/* src/settings.hpp
 * 
 * This source file gives the default values for the settings in Djinni.
 *
 * TODO: complete the whole feature. See trello board for more information
 * 
 * The source can be found in 'src/settings.cpp'
 */

#pragma once

// Macroes for the correct text colours
#define CLEAN_TEXT 0
#define ERROR_TEXT 1
#define SUCCESS_TEXT 2
#define WARNING_TEXT 3
#define CMD_PROMPT 4

namespace Djinni {
namespace Settings {
    extern bool line_numbers;
    extern bool cursorxy;
	
	extern void init_settings();
	extern void load_settings(const char* file);
}
}
