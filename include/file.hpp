#pragma once

#include <string>

#include <vector>

namespace Djinni {
class File {
    public:
    File();

    std::vector<std::string> line_buffer;
    unsigned int cursor_x, cursor_y;

    std::string get_filename();
    void set_filename(std::string filename);

	void load_file(std::string filename);
	void save_file(std::string fielname);

    private:
    std::string filename;
};
}
