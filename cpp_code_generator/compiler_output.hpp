#pragma once

#include <string>

namespace ccg {
class CompilerOutput {
  public:
    CompilerOutput() = default;
    CompilerOutput(std::string&& file)
        : file_{std::move(file)} {}

    template <typename Self>
    auto&& file(this Self&& self) {
        return std::forward<Self>(self).file_;
    }

    auto operator<=>(CompilerOutput const&) const = default;
  private:
    std::string file_;
};
}
