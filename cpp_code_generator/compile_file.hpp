#pragma once

#include <string_view>

#include "compiler_output.hpp"
#include "error.hpp"

namespace ccg {
auto compile_file(std::string_view module_name, std::string_view file) -> ErrorOr<CompilerOutput>;
}
