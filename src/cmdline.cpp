/* src/cmdline.cpp
 *
 * The header can be found in 'include/cmdline.hpp'
 */

#include <ncurses.h>
#include <string.h>
#include <tuple>
#include <vector>

#include <cmdline.hpp>
#include <runtime.hpp>
#include <screen.hpp>

// TODO: remove test_func which was for debugging purposes 
void test_func(std::vector<std::string>& x) { Djinni::Runtime::echo = x[1]; }

namespace Djinni {
namespace Commandline {
    // Variables for the command line
    std::string command = "";
    unsigned int cmdline_cursor_pos = 0;
    bool cmdline_running = true;
    // command_list: List containing all the possible commands using function pointers
    std::vector<std::tuple<const char*, void (*)(std::vector<std::string>&)>> command_list;

    // Functions of the command line feature
    void init_commandline();
    void commandline_routine();
    void process_command(const char* cmd);
    void exec_command(std::vector<std::string>& args);
}
}

// Initialize the command line session
void Djinni::Commandline::init_commandline()
{
    // TODO: remove the temp. test command
    Djinni::Commandline::command_list.push_back(std::make_tuple("test", &test_func));

    // Set all the variables to default values
    command = "";
    Djinni::Runtime::echo = "";
    cmdline_cursor_pos = 0;
    cmdline_running = true;

    // Enter the command line routine
    Djinni::Commandline::commandline_routine();
}

// Tokenize raw string given by the user into arguments
void Djinni::Commandline::process_command(const char* cmd)
{
    // Temporary output buffer
    std::vector<std::string> tokens;

    // Split the command into tokens
    std::string buffer = "";

    // Parse the string given by the user
    for (int i = 0; cmd[i] != '\0'; i++) {
        // Split if whitespace
        if (cmd[i] == ' ') {
            // Check that the buffer isn't empty to prevent empty arguments
            if (buffer != "") {
                tokens.push_back(buffer);
            }
            buffer = "";
        } else {
            // Add character to the temp. buffer
            buffer += cmd[i];
        }
    }
	// Append the final token 
    tokens.push_back(buffer);

    // Check if command was empty and if so: do nothing
    if (!(tokens[0] == "")) {
        // Execute the command given
        exec_command(tokens);
    } 
	
	// Finally quit the command line routine and return to basic Djinni
    cmdline_running = false;
}

// Execute the given command by using the command_list vector
void Djinni::Commandline::exec_command(std::vector<std::string>& args)
{
    // Search through the command list to see if a valid command was passed.
    for (unsigned int i = 0; i < Djinni::Commandline::command_list.size(); i++) {
        if (strcmp(args[0].c_str(), std::get<0>(Djinni::Commandline::command_list[i])) == 0) {
            // Execute the command and pass arguments with function pointer magic
            std::get<1>(Djinni::Commandline::command_list[i])(args);
            break;
        }
    }
}

// The loop that handles keypresses while the command line is open
void Djinni::Commandline::commandline_routine()
{
    while (cmdline_running) {
        // Update the screen continiously
        Djinni::Screen::update_screen();

        // Draw the current status of the command line (AKA user's input)
        mvprintw(Djinni::Screen::MAX_Y - 2, 0, ">");
        mvprintw(Djinni::Screen::MAX_Y - 2, 1, command.c_str());

        // Do an additional move to show the cursor in the proper location
        move(Djinni::Screen::MAX_Y - 2, cmdline_cursor_pos + 1);

        // Get user's input and process it
        int k = getch();
        switch (k) {
        // ESC || Ctrl-B -> close command line
        case 2:
        case 27:
            cmdline_running = false;
            break;
        // Enter key -> process command
        case int('\n'):
            process_command(command.c_str());
            break;
        // Backspace -> delete letter before
        case 127:
        case KEY_BACKSPACE:
            if (cmdline_cursor_pos > 0) {
                command.erase(cmdline_cursor_pos - 1, 1);
                cmdline_cursor_pos--;
            }
            break;
        // Arrow keys -> move to that direction
        case KEY_LEFT:
            if (cmdline_cursor_pos > 0) {
                cmdline_cursor_pos--;
            }
            break;
        case KEY_RIGHT:
            if (cmdline_cursor_pos < command.length()) {
                cmdline_cursor_pos++;
            }
            break;
        default:
            // Ignore non-printable characters
            if (k < 32) {
                break;
            }

            // Otherwise append to command string
            command.insert(cmdline_cursor_pos, 1, k);
            cmdline_cursor_pos++;
        }
    }
}
