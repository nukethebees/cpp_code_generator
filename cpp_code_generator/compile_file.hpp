#pragma once

#include <string_view>

#include "types.hpp"

namespace ccg {
auto compile_file(std::string_view module_name, std::string_view file) -> ErrorOr<CompilerOutput>;
}
