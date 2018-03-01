/* include/runtime.cpp
 *
 * This namespace includes all the running time variables that are only
 * needed during runtime.
 *
 * The source can be found in 'src/runtime.cpp'
 */
#pragma once

#include <string>

namespace Djinni {
namespace Runtime {
    extern bool running;
    extern unsigned int line_digits;
    extern unsigned int line_offset;
    extern std::string echo;
}
}
