/* src/cmdline.cpp
 *
 * The header can be found in 'include/cmdline.hpp'
 */

#include <ncurses.h>
#include <string.h>
#include <tuple>
#include <vector>

#include <cmdline.hpp>
#include <commands.hpp>
#include <runtime.hpp>
#include <screen.hpp>
#include <settings.hpp>

namespace Djinni {
namespace Commandline {
    // Variables for the command line
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

    // Set all the variables to default values
    Djinni::Runtime::echo = "";

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
    const char* command = user_input().c_str();
    if (strcmp(command, "\n")) {
        process_command(command);
    }
}

std::string Djinni::Commandline::user_input(const char* prompt)
{
    std::string input = "";
    unsigned int cmdline_cursor_pos = strlen(prompt);
    unsigned int input_pos = 0;

    while (true) {
        Djinni::Screen::update_screen();
        cmdline_cursor_pos = strlen(prompt) + input_pos;

        // Draw the current status of the command line (AKA user's input)
        attron(COLOR_PAIR(CMD_PROMPT)); // Appropriate colour for the command prompt
        mvprintw(Djinni::Screen::MAX_Y - 2, 0, prompt);
        mvprintw(Djinni::Screen::MAX_Y - 2, strlen(prompt), ">");
        attroff(COLOR_PAIR(CMD_PROMPT));
        mvprintw(Djinni::Screen::MAX_Y - 2, strlen(prompt) + 1, input.c_str());

        // Do an additional move to show the cursor in the proper location
        move(Djinni::Screen::MAX_Y - 2, cmdline_cursor_pos + 1);

        // Get user's input and process it
        int k = getch();
        switch (k) {
        // ESC || Ctrl-B -> close command line
        case 2:
        case 27:
            // return a non printable character to indicate that the input has been exited
            return "\n";
            break;
        // Enter key -> return the user's input
        case int('\n'):
            return input;
            break;
        // Backspace -> delete letter before
        case 127:
        case KEY_BACKSPACE:
            if (input_pos > 0) {
                input.erase(input_pos - 1, 1);
                input_pos--;
            }
            break;
        // Arrow keys -> move to that direction
        case KEY_LEFT:
            if (input_pos > 0) {
                input_pos--;
            }
            break;
        case KEY_RIGHT:
            if (input_pos < input.length()) {
                input_pos++;
            }
            break;
        default:
            // Ignore non-printable characters
            if (k < 32) {
                break;
            }

            // Otherwise append to input string
            input.insert(input_pos, 1, k);
            input_pos++;
        }
    }
}
