#pragma once

#include <vector>
#include <utility>

#include "token_types.hpp"
#include "type_expr.hpp"

namespace ccg {
class ParsedNamedArray {
  public:
    ParsedNamedArray() = default;
    ParsedNamedArray(TokenIndex name, ParsedTypeExpr type, std::vector<TokenIndex>&& field_indexes)
        : name_{name}
        , type_{type}
        , field_indexes_{std::move(field_indexes)} {}

    template <typename Self>
    auto&& name(this Self&& self) {
        return std::forward<Self>(self).name_;
    }
    template <typename Self>
    auto&& type(this Self&& self) {
        return std::forward<Self>(self).type_;
    }
    template <typename Self>
    auto&& field_indexes(this Self&& self) {
        return std::forward<Self>(self).field_indexes_;
    }
  private:
    TokenIndex name_;
    ParsedTypeExpr type_;
    std::vector<TokenIndex> field_indexes_;
};

using NamedArrayFieldIndex = uint16_t;
class NamedArrayHeader {
  public:
    NamedArrayHeader() = delete;
    NamedArrayHeader(TokenIndex name,
                     ParsedTypeExpr type_index,
                     NamedArrayFieldIndex field_index_start,
                     NamedArrayFieldIndex field_indexes)
        : name_(name)
        , type_index_(type_index)
        , field_index_start_{field_index_start}
        , field_indexes_{field_indexes} {}

    // Member Access
    template <typename Self>
    auto&& name(this Self&& self) {
        return std::forward<Self>(self).name_;
    }
    template <typename Self>
    auto&& type_index(this Self&& self) {
        return std::forward<Self>(self).type_index_;
    }
    template <typename Self>
    auto&& field_index_start(this Self&& self) {
        return std::forward<Self>(self).field_index_start_;
    }
    template <typename Self>
    auto&& field_indexes(this Self&& self) {
        return std::forward<Self>(self).field_indexes_;
    }
  private:
    TokenIndex name_;
    ParsedTypeExpr type_index_;
    NamedArrayFieldIndex field_index_start_;
    NamedArrayFieldIndex field_indexes_;
};

class NamedArrayField {
  public:
    NamedArrayField() = delete;
    NamedArrayField(TokenIndex name)
        : name_(name) {}

    // Member Access
    template <typename Self>
    auto&& name(this Self&& self) {
        return std::forward<Self>(self).name_;
    }
  private:
    TokenIndex name_{};
};

class NamedArrays {
  public:
    NamedArrays() = default;

    // Member Access
    template <typename Self>
    auto&& headers(this Self&& self) {
        return std::forward<Self>(self).headers_;
    }
    template <typename Self>
    auto&& fields(this Self&& self) {
        return std::forward<Self>(self).fields_;
    }
  private:
    std::vector<NamedArrayHeader> headers_;
    std::vector<NamedArrayField> fields_;
};

}
