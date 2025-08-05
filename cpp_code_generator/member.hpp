#pragma once

#include "token_types.hpp"
#include "type_expr.hpp"

namespace ccg {
class Member {
  public:
    Member() = delete;
    Member(TokenIndex name, ParsedTypeExpr const& type)
        : name_(name)
        , type_(type) {}

    // Member Access
    template <typename Self>
    auto&& name(this Self&& self) {
        return std::forward<Self>(self).name_;
    }
    template <typename Self>
    auto&& type(this Self&& self) {
        return std::forward<Self>(self).type_;
    }
  private:
    TokenIndex name_;
    ParsedTypeExpr type_;
};
}
