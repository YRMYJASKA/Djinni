// Definitions of all the core Djinni commands

#include <string.h>
#include <tuple>
#include <vector>

#include <commands.hpp>
#include <runtime.hpp>
#include <screen.hpp>
#include <version.h>

// Template function
// This is the form which ALL command line commands should be written in
void template_func(std::vector<std::string>& c_args)
{
}

// echo_func:
// 	Prints a string which is given as an argument
// usage: 'echo <string>'
void echo_func(std::vector<std::string>& c_args)
{
    if (c_args.size() > 1) {
        Djinni::Screen::echo_print(c_args[1]);
    }
}
// save_func:
// saves a buffer to a file
// usage: 'save' OR 'save <file name>'
void save_func(std::vector<std::string>& c_args)
{
    std::string name;
    if (c_args.size() < 2) {
        name = Djinni::Screen::current_buffer->get_filename();
    } else {
        name = c_args[1];
    }
    Djinni::Screen::current_buffer->save_file(name);
    Djinni::Screen::echo_print("Saved to file: \"" + name + "\"", 2);
}
// open_func:
// Opens a file into the current buffer
// Usage: 'open <file>'
void open_func(std::vector<std::string>& c_args)
{
    if (c_args.size() < 2) {
        Djinni::Screen::echo_print("open: Please pass a filename.", 1);
    } else {
        Djinni::Screen::current_buffer->load_file(c_args[1]);
        Djinni::Screen::echo_print("Opened: \"" + c_args[1] + "\"", 2);
    }
}

// quit_func:
// Exits the editor
// usage: 'quit'
void quit_func(std::vector<std::string>& c_args)
{
    Djinni::Runtime::running = false;
}

// rename_func:
// Change the current buffer's name
// usage: 'rename <new name>'
void rename_func(std::vector<std::string>& c_args)
{
    if (c_args.size() < 2) {
        Djinni::Screen::echo_print("rename: Please pass a new name", 1);
    } else {
        std::string old = Djinni::Screen::current_buffer->get_filename();
        Djinni::Screen::current_buffer->set_filename(c_args[1]);
        Djinni::Screen::echo_print("Renamed \"" + old + "\" -> \"" + c_args[1] + "\"", 2);
    }
}

void version_func(std::vector<std::string>& c_args)
{
    Djinni::Screen::echo_print(VERSION_STRING, 0);
}

namespace Djinni {
// The core commands of the Djinni editor which will be loaded to the
// 'command_list' on start up
std::vector<std::tuple<const char*, void (*)(std::vector<std::string>&)>> core_commands;

void init_core_commands()
{
    // Add all the commands to the list one-by-one
    // 										<call>	<function>
    core_commands.push_back(std::make_tuple("echo", &echo_func));
    core_commands.push_back(std::make_tuple("save", &save_func));
    core_commands.push_back(std::make_tuple("open", &open_func));
    core_commands.push_back(std::make_tuple("quit", &quit_func));
    core_commands.push_back(std::make_tuple("rename", &rename_func));
    core_commands.push_back(std::make_tuple("version", &version_func));
}
}
