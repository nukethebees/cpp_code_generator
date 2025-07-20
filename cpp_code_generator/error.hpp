#pragma once

#include <cstdint>
#include <expected>
#include <string>

#include "token_types.hpp"

namespace ccg {
enum class ErrorType : uint8_t {
    UNKNOWN,
    COMPILER_BUG,
    PLACEHOLDER,
    UNEXPECTED_PARSER_TOKEN,
    UNEXPECTED_SCANNER_TOKEN
};


class Error {
public:
    Error() = delete;
    Error(std::string const & message,
          TokenPosition source_position,
          TokenLength source_length,
          ErrorType type)
        : message_(message)
        , source_position_(source_position)
        , source_length_(source_length)
        , type_(type) {}

    // Member Access
    template <typename Self>
    auto && message(this Self && self) {
        return std::forward<Self>(self).message_;
    }
    template <typename Self>
    auto && source_position(this Self && self) {
        return std::forward<Self>(self).source_position_;
    }
    template <typename Self>
    auto && source_length(this Self && self) {
        return std::forward<Self>(self).source_length_;
    }
    template <typename Self>
    auto && type(this Self && self) {
        return std::forward<Self>(self).type_;
    }

    static auto placeholder_error() { return Error("Placeholder", 0, 0, ErrorType::PLACEHOLDER); }
private:
    std::string message_;
    TokenPosition source_position_;
    TokenLength source_length_;
    ErrorType type_;
};

template <typename T>
using ErrorOr = std::expected<T, Error>;
}