/* include/miscellaneous.hpp
 * 
 * This namespace is for some misc. functions and scraps that 
 * don't fit anywhere else.
 *
 * The source can be found in 'include/miscellaneous.hpp'
 */
#pragma once

#include <string>

namespace Djinni {
namespace Miscellaneous {
    extern int digit_num(int x);
    extern void print_help();
    extern bool file_exists(const std::string& filename);
}
}
