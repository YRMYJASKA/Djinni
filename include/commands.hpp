#pragma once

#include <string.h>
#include <tuple>
#include <vector>

namespace Djinni {
// The core commands of the Djinni editor which will be loaded to the
// 'command_list' on start up
	extern  std::vector<std::tuple<const char*, void (*)(std::vector<std::string>&)>> core_commands;
	extern void init_core_commands();
}

