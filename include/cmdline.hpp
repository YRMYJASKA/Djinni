/* include/cmdline.hpp
 *
 * Header for the command line in Djinni.
 * The command line is used by the user to pass commands that will be interpreted
 * inside Djinni. Commands can include e.g. 'save', 'open' or 'find'. These commands can take 
 * arguments after the command. e.g. '>find foo'
 *
 * The source can be found in 'src/cmdline.cpp'
 */

#pragma once

#include <string>
#include <tuple>
#include <vector>

namespace Djinni {
namespace Commandline {
    // Variables for the command line
    extern bool cmdline_running;

    // command_list: List containing all the possible commands using function pointers
    extern std::vector<std::tuple<const char*, void (*)(std::vector<std::string>&)>> command_list;

    // Functions of the command line feature
    extern void init_commandline();
    extern void commandline_routine();
    extern void process_command(const char* cmd);
    extern void exec_command(std::vector<std::string>& args);
    extern std::string user_input(const char* prompt = "");
}
}
