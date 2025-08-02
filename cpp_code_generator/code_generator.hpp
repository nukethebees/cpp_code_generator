#pragma once

#include "compiler_output.hpp"
#include "error.hpp"

namespace ccg {
class Module;

class CodeGenerator {
  private:
    CodeGenerator() = delete;
    CodeGenerator(Module const& mod)
        : mod_{mod} {}

    auto generate() -> ErrorOr<void>;
    auto named_arrays() -> ErrorOr<void>;
  public:
    static auto generate(Module const& mod) -> ErrorOr<CompilerOutput>;
    template <typename Self>
    auto&& output(this Self&& self) {
        return std::forward<Self>(self).output_;
    }
  private:
    Module const& mod_;
    CompilerOutput output_;
};
}
