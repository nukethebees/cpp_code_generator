#pragma once

#include <cstdint>
#include <expected>
#include <string>
#include <vector>
#include <utility>

// todo: enum + enum to string[_view]
// todo: array with types as keys
// e.g. container of Foo<U...>. foo.get<int> to get Foo<int> instance
// todo: string-enum pair generation (for things like tokens)
// todo: struct of vectors
// todo: struct of arrays
// todo: tagged union

namespace ccg {
using TokenPosition = uint32_t;
using TokenLength = uint16_t;
using TokenIndex = uint32_t;

enum class TokenType : uint8_t { END_OF_FILE };

class Tokens {
  public:
    Tokens() = default;

    // Member Access
    template <typename Self>
    auto&& token_chars(this Self&& self) {
        return std::forward<Self>(self).token_chars_;
    }
    template <typename Self>
    auto&& token_positions(this Self&& self) {
        return std::forward<Self>(self).token_positions_;
    }
    template <typename Self>
    auto&& token_lengths(this Self&& self) {
        return std::forward<Self>(self).token_lengths_;
    }
    template <typename Self>
    auto&& token_types(this Self&& self) {
        return std::forward<Self>(self).token_types_;
    }
  private:
    std::string token_chars_{""};
    std::vector<TokenPosition> token_positions_;
    std::vector<TokenLength> token_lengths_;
    std::vector<TokenType> token_types_;
};

using TypeIndex = uint32_t;

class Type {
  public:
    Type() = delete;
    Type(TokenIndex name, TypeIndex parameters, TypeIndex parameter_vec_index)
        : name_(name)
        , parameters_(parameters)
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
    TokenIndex name_;
    TypeIndex parameters_;
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
  private:
    std::vector<Types> types_;
    std::vector<TypeIndex> indexes_;
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

class NamedArrayHeader {
  public:
    NamedArrayHeader() = delete;
    NamedArrayHeader(TokenIndex name, uint16_t type_index)
        : name_(name)
        , type_index_(type_index) {}

    // Member Access
    template <typename Self>
    auto&& name(this Self&& self) {
        return std::forward<Self>(self).name_;
    }
    template <typename Self>
    auto&& type_index(this Self&& self) {
        return std::forward<Self>(self).type_index_;
    }
  private:
    TokenIndex name_;
    uint16_t type_index_;
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
    auto&& types(this Self&& self) {
        return std::forward<Self>(self).types_;
    }
    template <typename Self>
    auto&& headers(this Self&& self) {
        return std::forward<Self>(self).headers_;
    }
    template <typename Self>
    auto&& fields(this Self&& self) {
        return std::forward<Self>(self).fields_;
    }
  private:
    std::vector<Type> types_;
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

class Module {
  public:
    Module() = default;

    // Member Access
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
  private:
    Tokens tokens_;
    TaggedUnions unions_;
    NamedArrays named_arrays_;
};

enum class ErrorType : uint8_t { UNKNOWN, COMPILER_BUG };

class Error {
  public:
    Error() = delete;
    Error(std::string const& message,
          TokenPosition source_position,
          TokenLength source_length,
          ErrorType type)
        : message_(message)
        , source_position_(source_position)
        , source_length_(source_length)
        , type_(type) {}

    // Member Access
    template <typename Self>
    auto&& message(this Self&& self) {
        return std::forward<Self>(self).message_;
    }
    template <typename Self>
    auto&& source_position(this Self&& self) {
        return std::forward<Self>(self).source_position_;
    }
    template <typename Self>
    auto&& source_length(this Self&& self) {
        return std::forward<Self>(self).source_length_;
    }
    template <typename Self>
    auto&& type(this Self&& self) {
        return std::forward<Self>(self).type_;
    }
  private:
    std::string message_;
    TokenPosition source_position_;
    TokenLength source_length_;
    ErrorType type_;
};

template <typename T>
using ErrorOr = std::expected<T, Error>;
}
