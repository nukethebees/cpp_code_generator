#pragma once

#include <compare>
#include <cstdint>
#include <expected>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// todo: enum + enum to string[_view]
// todo: array with types as keys
// e.g. container of Foo<U...>. foo.get<int> to get Foo<int> instance
// todo: string-enum pair generation (for things like tokens)
// todo: struct of vectors
// todo: struct of arrays
// todo: tagged union

#include "token_type.hpp"
#include "string_hasher.hpp"
#include "token_types.hpp"

namespace ccg {
class Tokens {
  public:
    Tokens() = default;

    void add(std::string_view lexeme, TokenPosition position, TokenType type) {
        string_positions_.push_back(token_chars_.size());
        token_chars_ += lexeme;
        source_positions_.push_back(position);
        token_lengths_.push_back(static_cast<TokenLength>(lexeme.size()));
        token_types_.push_back(type);
    }

    // Member Access
    template <typename Self>
    auto&& token_chars(this Self&& self) {
        return std::forward<Self>(self).token_chars_;
    }
    template <typename Self>
    auto&& source_positions(this Self&& self) {
        return std::forward<Self>(self).source_positions_;
    }
    template <typename Self>
    auto&& string_positions(this Self&& self) {
        return std::forward<Self>(self).string_positions_;
    }
    template <typename Self>
    auto&& token_lengths(this Self&& self) {
        return std::forward<Self>(self).token_lengths_;
    }
    template <typename Self>
    auto&& token_types(this Self&& self) {
        return std::forward<Self>(self).token_types_;
    }

    // Element access
    template <typename Self>
    auto&& type(this Self&& self, std::size_t i) {
        return std::forward<Self>(self).token_types_[i];
    }
    template <typename Self>
    auto lexeme(this Self&& self, std::size_t i) -> std::string_view {
        auto pos{self.string_positions_[i]};
        auto len{self.token_lengths_[i]};
        return std::string_view(std::forward<Self>(self).token_chars_).substr(pos, len);
    }
    template <typename Self>
    auto source_position(this Self&& self, std::size_t i) {
        return std::forward<Self>(self).source_positions_[i];
    }
    template <typename Self>
    auto string_position(this Self&& self, std::size_t i) {
        return std::forward<Self>(self).string_positions_[i];
    }
    template <typename Self>
    auto length(this Self&& self, std::size_t i) {
        return std::forward<Self>(self).token_lengths_[i];
    }
  private:
    std::string token_chars_{""};
    std::vector<TokenPosition> source_positions_;
    std::vector<std::size_t> string_positions_;
    std::vector<TokenLength> token_lengths_;
    std::vector<TokenType> token_types_;
};

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

class Member {
  public:
    Member() = delete;
    Member(TokenIndex name, Type const& type)
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
    Type type_;
};

class ParsedNamedArray {
  public:
    ParsedNamedArray() = default;
    ParsedNamedArray(TokenIndex name, TokenIndex type, std::vector<TokenIndex>&& field_indexes)
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
    TokenIndex type_;
    std::vector<TokenIndex> field_indexes_;
};

using NamedArrayFieldIndex = uint16_t;
class NamedArrayHeader {
  public:
    NamedArrayHeader() = delete;
    NamedArrayHeader(TokenIndex name,
                     TypeIndex type_index,
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
    TypeIndex type_index_;
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

class UnionHeader {
  public:
    UnionHeader() = delete;
    UnionHeader(uint16_t members_offset, uint8_t members_length, TokenIndex name)
        : members_offset_(members_offset)
        , members_length_(members_length)
        , name_(name) {}

    // Member Access
    template <typename Self>
    auto&& members_offset(this Self&& self) {
        return std::forward<Self>(self).members_offset_;
    }
    template <typename Self>
    auto&& members_length(this Self&& self) {
        return std::forward<Self>(self).members_length_;
    }
    template <typename Self>
    auto&& name(this Self&& self) {
        return std::forward<Self>(self).name_;
    }
  private:
    uint16_t members_offset_;
    uint8_t members_length_;
    TokenIndex name_;
};

class TaggedUnions {
  public:
    TaggedUnions() = default;

    // Member Access
    template <typename Self>
    auto&& headers(this Self&& self) {
        return std::forward<Self>(self).headers_;
    }
    template <typename Self>
    auto&& members(this Self&& self) {
        return std::forward<Self>(self).members_;
    }
  private:
    std::vector<UnionHeader> headers_;
    std::vector<Member> members_;
};

// All vectors have the same length instead of tracking separately
class StructOfVectors {
  public:
    StructOfVectors() = default;
};

class ParserOutput {
  public:
    ParserOutput() = default;

    template <typename Self>
    auto&& named_arrays(this Self&& self) {
        return std::forward<Self>(self).named_arrays_;
    }
  private:
    std::vector<ParsedNamedArray> named_arrays_;
};

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
