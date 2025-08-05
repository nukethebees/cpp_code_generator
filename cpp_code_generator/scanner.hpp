#pragma once

#include <string_view>
#include <vector>

#include "error.hpp"
#include "tokens.hpp"

namespace ccg {
class Scanner {
  private:
    Scanner() = delete;
    Scanner(std::string_view file)
        : file_{file} {}

    auto scan() -> ErrorOr<Tokens>;
  public:
    static auto scan(std::string_view file) -> ErrorOr<Tokens>;
  private:
    std::string_view file_;
};
}
