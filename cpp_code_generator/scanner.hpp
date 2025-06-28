#pragma once

#include <string_view>
#include <vector>

#include "types.hpp"

namespace ccg {
class Scanner {
  private:
    Scanner() = delete;
    Scanner(std::string_view file)
        : file_{file} {}
  public:
    static auto scan(std::string_view file) -> ErrorOr<Tokens>;
  private:
    std::string_view file_;
};
}
