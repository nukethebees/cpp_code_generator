#pragma once

#include <cstddef>
#include <format>

#include "error.hpp"
#include "types.hpp"

namespace ccg {
class Parser {
  private:
    Parser() = delete;
    Parser(Tokens const& tokens)
        : tokens_{tokens} {}

    auto parse() -> ErrorOr<void>;
    auto module_item() -> ErrorOr<void>;
    auto named_array() -> ErrorOr<void>;

    // Token access
    auto cur_type() const { return tokens_.type(i); }
    auto cur_lexeme() const { return tokens_.lexeme(i); }
    auto cur_position() const { return tokens_.source_position(i); }
    auto cur_length() const { return tokens_.length(i); }

    // Errors
    auto make_error(std::string&& msg, ErrorType type) const {
        return std::unexpected(Error(std::move(msg), cur_position(), cur_length(), type));
    }

    // Token advancement
    void advance() { i++; }
    auto consume(TokenType type) -> ErrorOr<void> {
        auto cur{cur_type()};
        if (cur != type) {
            return make_error(
                std::format("Expected {}, got {}.\n", to_string_view(type), to_string_view(cur)),
                ErrorType::UNEXPECTED_PARSER_TOKEN);
        }
        advance();
        return {};
    }
    auto consume(std::string_view lexeme) -> ErrorOr<void> {
        auto cur{cur_lexeme()};
        if (cur != lexeme) {
            return make_error(std::format("Expected {}, got {}.\n", lexeme, cur),
                              ErrorType::UNEXPECTED_PARSER_TOKEN);
        }
        advance();
        return {};
    }
    // Returns the index
    auto consume_index(TokenType type) -> ErrorOr<TokenIndex> {
        auto idx{i};
        auto cur{cur_type()};
        if (cur != type) {
            return make_error(
                std::format("Expected {}, got {}.\n", to_string_view(type), to_string_view(cur)),
                ErrorType::UNEXPECTED_PARSER_TOKEN);
        }
        advance();
        return idx;
    }
    auto match(TokenType type) -> bool {
        if (cur_type() == type) {
            advance();
            return true;
        }
        return false;
    }
    auto match(std::string_view str) -> bool {
        if (cur_lexeme() == str) {
            advance();
            return true;
        }
        return false;
    }
    auto match(TokenType type, std::string_view str) -> bool {
        if ((cur_type() == type) && (cur_lexeme() == str)) {
            advance();
            return true;
        }
        return false;
    }

    auto is_eof() const { return cur_type() == TokenType::END_OF_FILE; }
  public:
    static auto parse(Tokens const& tokens) -> ErrorOr<ParserOutput>;
  private:
    ParserOutput output;
    Tokens const& tokens_{};
    TokenIndex i{0};
};
}
