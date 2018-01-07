#include <string>

#include <file.hpp>

Djinni::File::File(std::string filename)
{
    this->line_buffer.resize(1);
	this->line_buffer[0] = "";

    this->cursor_x = 0;
    this->cursor_y = 0;

    this->filename = filename;
}

std::string Djinni::File::get_filename() { return this->filename; }

void Djinni::File::set_filename(std::string filename) { this->filename = filename; }
