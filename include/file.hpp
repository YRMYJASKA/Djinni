#pragma once

#include <string>

#include <vector>

namespace Djinni {
class File {
    public:
    File(std::string filename);

    std::vector<std::string> line_buffer;
    unsigned int cursor_x, cursor_y;

    std::string get_filename();
    void set_filename(std::string filename);

    private:
    std::string filename;
};
}
