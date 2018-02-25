#include <ncurses.h>
#include <string>
#include <vector>

#include <cmdline.hpp>
#include <screen.hpp>
#include <runtime.hpp>

namespace Djinni {
namespace Commandline {
    // Variables for the command line
    std::string command = "";
    unsigned int cmdline_cursor_pos = 0;
    bool cmdline_running = true;

    // Functions for the command line
    void init_commandline();
    void commandline_routine();
    void process_command(const char* cmd);
    void exec_command(std::string* args, int size);
}
}

// Initialize the command line session
void Djinni::Commandline::init_commandline()
{
    // Set all the variables to default values
    command = "";
	Djinni::Runtime::echo = "";
    cmdline_cursor_pos = 0;
    cmdline_running = true;

    // Enter the command line routine
    Djinni::Commandline::commandline_routine();
}

void Djinni::Commandline::process_command(const char* cmd)
{
    // TODO
    std::vector<std::string> tokens;

    // Split the command into tokens
    std::string buffer = "";

    for (int i = 0; cmd[i] != '\0'; i++) {
        if (cmd[i] == ' ') {
            // Split if whitespace

            // Check that the buffer isn't empty to prevent empty arguments
            if (buffer != "") {
                tokens.push_back(buffer);
            }
            buffer = "";
        } else {
            // Otherwise, add buffer
            buffer += cmd[i];
        }
    }
    tokens.push_back(buffer);

    if (tokens[0] == "") {
        // Command was empty and do nothing
    } else {
        // Execute the command given
        exec_command(&tokens[0], tokens.size());
    }
    cmdline_running = false;
}

void Djinni::Commandline::exec_command(std::string* args, int size)
{
    // TODO
}

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
