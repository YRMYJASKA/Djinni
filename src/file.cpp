#include <fstream>
#include <iostream>
#include <string>

#include <file.hpp>

Djinni::File::File()
{
    this->line_buffer.resize(1);
    this->line_buffer[0] = "";

    this->cursor_x = 0;
    this->cursor_y = 0;
}

std::string Djinni::File::get_filename() { return this->filename; }

void Djinni::File::set_filename(std::string filename) { this->filename = filename; }

// Load all the lines from a file into the file buffer
void Djinni::File::load_file(std::string filename)
{
    std::ifstream _file;
    std::string _line;

    _file.open(filename);

    this->line_buffer.resize(0); // To avoid one extra empty line

    // Check if file opened
    if (!_file.is_open()) {
        // If the file couldn't be opened or it doesn't exist, make an empty file
        this->line_buffer.push_back("");
    } else {
        // Read the file line by line into the line buffer
        while (!_file.eof()) {
            std::getline(_file, _line);
            this->line_buffer.push_back(_line);
        }
    }
    this->set_filename(filename);
    _file.close();
}

// Write the current line buffer into a file
void Djinni::File::save_file(std::string filename)
{
    std::ofstream _file;

    _file.open(filename);

    if (!_file.is_open()) {
        // TODO: Erro handling for not being ale to write to file
    } else {
        for (int i = 0; i < this->line_buffer.size(); i++) {
            _file << this->line_buffer[i] << '\n';
        }
    }
}
