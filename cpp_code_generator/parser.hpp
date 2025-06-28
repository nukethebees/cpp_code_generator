#pragma once

#include "types.hpp"

namespace ccg {
class Parser {
  private:
    Parser() = delete;
    Parser(Tokens const& tokens)
        : tokens_{tokens} {}

    auto parse() -> ErrorOr<ParserOutput>;
  public:
    static auto parse(Tokens const& tokens) -> ErrorOr<ParserOutput>;
  public:
    Tokens const& tokens_{};
};
}
