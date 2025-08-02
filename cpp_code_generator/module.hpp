#pragma once

#include <string_view>
#include <utility>

#include "tokens.hpp"
#include "ast_type.hpp"
#include "tagged_union.hpp"
#include "named_array.hpp"

namespace ccg {
class Module {
  public:
    Module() = delete;
    Module(std::string_view name)
        : name_{name} {}

    // Member Access
    template <typename Self>
    auto&& name(this Self&& self) {
        return std::forward<Self>(self).name_;
    }
    template <typename Self>
    auto&& tokens(this Self&& self) {
        return std::forward<Self>(self).tokens_;
    }
    template <typename Self>
    auto&& unions(this Self&& self) {
        return std::forward<Self>(self).unions_;
    }
    template <typename Self>
    auto&& named_arrays(this Self&& self) {
        return std::forward<Self>(self).named_arrays_;
    }
    template <typename Self>
    auto&& types(this Self&& self) {
        return std::forward<Self>(self).types_;
    }
  private:
    std::string_view name_;
    Tokens tokens_;
    Types types_;
    TaggedUnions unions_;
    NamedArrays named_arrays_;
};
}
