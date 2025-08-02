#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "token_types.hpp"
#include "string_hasher.hpp"
#include "tokens.hpp"

namespace ccg {
using TypeIndex = uint32_t;

class Type {
  public:
    Type() = delete;
    Type(TokenIndex name, std::size_t parameters, TypeIndex parameter_vec_index)
        : parameters_(parameters)
        , name_(name)
        , parameter_vec_index_(parameter_vec_index) {}

    // Member Access
    template <typename Self>
    auto&& name(this Self&& self) {
        return std::forward<Self>(self).name_;
    }
    template <typename Self>
    auto&& parameters(this Self&& self) {
        return std::forward<Self>(self).parameters_;
    }
    template <typename Self>
    auto&& parameter_vec_index(this Self&& self) {
        return std::forward<Self>(self).parameter_vec_index_;
    }
  private:
    std::size_t parameters_;
    TokenIndex name_;
    TypeIndex parameter_vec_index_;
};

class Types {
  public:
    Types() = default;

    // Member Access
    template <typename Self>
    auto&& types(this Self&& self) {
        return std::forward<Self>(self).types_;
    }
    template <typename Self>
    auto&& indexes(this Self&& self) {
        return std::forward<Self>(self).indexes_;
    }
    auto lookup_or_add(Tokens const& tokens, TokenIndex name_idx) -> TypeIndex {
        auto name{tokens.lexeme(name_idx)};
        auto lu{name_lookup_.find(name)};

        if (lu == name_lookup_.end()) {
            return add(tokens, name_idx);
        }
        return lu->second;
    }
    auto add(Tokens const& tokens, TokenIndex name_idx) -> TypeIndex {
        auto name{tokens.lexeme(name_idx)};
        types_.emplace_back(name_idx, 0, static_cast<TypeIndex>(indexes_.size()));
        return 0;
    }
  private:
    std::vector<Type> types_;
    std::vector<TypeIndex> indexes_;
    StringMap<TypeIndex> name_lookup_;
};

}
