#pragma once

#include <cstddef>

#include "types.hpp"

namespace ccg {
class Parser {
  private:
    Parser() = delete;
    Parser(Tokens const& tokens)
        : tokens_{tokens} {}

    auto parse() -> ErrorOr<void>;
    auto module_item() -> ErrorOr<void>;

    void advance() { i++; }

    // Token access
    auto cur_type() const { return tokens_.type(i); }
    auto cur_lexeme() const { return tokens_.lexeme(i); }
    auto cur_position() const { return tokens_.source_position(i); }
    auto cur_length() const { return tokens_.length(i); }
  public:
    static auto parse(Tokens const& tokens) -> ErrorOr<ParserOutput>;
  private:
    ParserOutput output;
    Tokens const& tokens_{};
    std::size_t i{0};
};
}
