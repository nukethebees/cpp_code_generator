#pragma once

#include "types.hpp"

namespace ccg {
class CodeGenerator {
  private:
    CodeGenerator() = delete;
    CodeGenerator(Module const& mod)
        : mod_{mod} {}

    auto generate() -> ErrorOr<CompilerOutput>;
  public:
    static auto generate(Module const& mod) -> ErrorOr<CompilerOutput>;
  private:
    Module const& mod_;
};
}
