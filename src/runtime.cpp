/* src/runtime.cpp
 *
 * The header can be found in 'include/runtime.hpp'
 */

#include <runtime.hpp>
#include <string>

namespace Djinni {
namespace Runtime {
    bool running = true;
    unsigned int line_digits;
    unsigned int line_offset = 0;
    std::string echo = "";
}
}
