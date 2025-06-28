#pragma once

#include <cstdint>
#include <expected>
#include <string>
#include <vector>

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

enum class TokenType : uint8_t {
    END_OF_FILE
};

class Tokens {
    Tokens() = default;
private:
    std::string token_chars_{""};
    std::vector<TokenPosition> token_positions_;
    std::vector<TokenLength> token_lengths_;
    std::vector<TokenType> token_types_;
};

using TypeIndex = uint32_t;

class Type {
    TokenIndex name;
    TypeIndex parameters_;
    TypeIndex parameter_vec_index_;
};

class Types {
    std::vector<Types> types_;
    std::vector<TypeIndex> indexes_;
};

class Member {
    TokenIndex name;
    Type type;
};

class NamedArrayHeader {
    TokenIndex name;
    uint16_t type_index;
};

class NamedArrayField {
    TokenIndex name;
};

class NamedArrays {
    std::vector<Type> types;
    std::vector<NamedArrayHeader> headers;
    std::vector<NamedArrayField> fields;
};

struct UnionHeader {
    uint16_t members_offset;
    uint8_t members_length;
    TokenIndex name;
};

class TaggedUnions {
    std::vector<UnionHeader> headers_;
    std::vector<Member> members_;
};

// All vectors have the same length instead of tracking separately
class StructOfVectors {};

class Module {
private:
    Tokens tokens_;
    TaggedUnions unions_;
    NamedArrays named_arrays_;
};

enum class ErrorType : uint8_t {
    UNKNOWN, COMPILER_BUG
};

class Error {
    std::string message;
    TokenPosition source_position;
    TokenLength source_length;
    ErrorType type;
};

template <typename T>
using ErrorOr = std::expected<T, Error>;
}