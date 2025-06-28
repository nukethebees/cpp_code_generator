#include "code_generator.hpp"

namespace ccg {
auto CodeGenerator::generate(Module const& mod) -> ErrorOr<CompilerOutput> {
    auto generator{CodeGenerator(mod)};
    return generator.generate();
}

auto CodeGenerator::generate() -> ErrorOr<CompilerOutput> {
    return std::unexpected(Error::placeholder_error());
}
}
