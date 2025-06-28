#pragma once

#include <string_view>
#include <vector>

#include "types.hpp"

namespace ccg {
inline auto is_digit(char c) -> bool {
    return (c >= 48) && (c <= 57);
}
inline auto is_upper_alpha(char c) -> bool {
    return (c >= 65) && (c <= 90);
}
inline auto is_lower_alpha(char c) -> bool {
    return (c >= 97) && (c <= 122);
}
inline auto is_alpha(char c) -> bool {
    return is_upper_alpha(c) || is_lower_alpha(c);
}
inline auto is_alphanum(char c) -> bool {
    return is_digit(c) || is_alpha(c);
}
inline auto is_identifier_char(char c) -> bool {
    return is_alpha(c) || (c == '_');
}
inline auto is_inner_identifier_char(char c) noexcept -> bool {
    return is_identifier_char(c) || is_digit(c);
}

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
