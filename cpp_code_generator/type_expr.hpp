#pragma once

#include "tokens.hpp"

namespace ccg {
class ParsedTypeExpr {
    TokenRange tokens_;
  public:
    explicit ParsedTypeExpr(TokenRange tokens)
        : tokens_{tokens} {}

    auto const& tokens() const { return tokens_; }
};
}
