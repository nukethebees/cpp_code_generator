#include "code_generator.hpp"

namespace ccg {
auto CodeGenerator::generate(Module const& mod) -> ErrorOr<CompilerOutput> {
    auto generator{CodeGenerator(mod)};
    return generator.generate();
}

auto CodeGenerator::generate() -> ErrorOr<CompilerOutput> {
    CompilerOutput output;
    output.file() += "\n";
    return output;
}
}
