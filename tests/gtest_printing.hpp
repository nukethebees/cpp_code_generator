#include <format>
#include <ostream>

#include "cpp_code_generator/types.hpp"

namespace ccg {
inline void PrintTo(CompilerOutput output, std::ostream* os) {
    *os << std::format(R"(Compiler output:
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
{}[END_OF_FILE]
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
)",
                       output.file());
}
}
