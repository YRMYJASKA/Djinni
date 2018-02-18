#pragma once

#include <string>

namespace Djinni {
namespace Commandline {
    // Variables for the command line
    extern std::string command;
    extern std::string echo;
    extern int cmdline_cursor_pos;
	extern bool cmdline_running;

    extern void init_commandline();
    extern void commandline_routine();
    extern void process_command(std::string cmd);
}
}
