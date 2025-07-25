#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <optional>

#include "string_hasher.hpp"

enum class TokenType : uint8_t {
    // Numeric Operators
    PLUS,
    MINUS,
    STAR,
    SLASH,
    PERCENT,
    PLUS_PLUS,
    MINUS_MINUS,

    // Bitwise Operators
    AMPERSAND,
    BAR,
    CARET,
    TILDE,
    LESS_LESS,
    GREATER_GREATER,

    // Logical Operators
    EQUAL_EQUAL,
    BANG_EQUAL,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,
    EQUAL,
    BANG,
    AMPERSAND_AMPERSAND,
    BAR_BAR,

    // Delimiters & Misc
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    DOUBLE_QUOTE,
    SINGLE_QUOTE,
    BACKSLASH_BACKSLASH,
    QUESTION,
    COLON,
    COLON_COLON,
    SEMICOLON,
    COMMA,
    DOT,
    ARROW,
    SLASH_SLASH,

    // Literals
    NUMBER,
    IDENTIFIER,
    STRING,
    CHAR,

    // Keywords
    NAMED_ARRAY,

    // Special
    END_OF_FILE,

    // Sentinel
    TOKEN_TYPE_COUNT
};

inline std::string_view to_string_view(TokenType type) {
    using enum TokenType;
    switch (type) {
        case PLUS:
            return "PLUS";
        case MINUS:
            return "MINUS";
        case STAR:
            return "STAR";
        case SLASH:
            return "SLASH";
        case PERCENT:
            return "PERCENT";
        case PLUS_PLUS:
            return "PLUS_PLUS";
        case MINUS_MINUS:
            return "MINUS_MINUS";
        case AMPERSAND:
            return "AMPERSAND";
        case BAR:
            return "BAR";
        case CARET:
            return "CARET";
        case TILDE:
            return "TILDE";
        case LESS_LESS:
            return "LESS_LESS";
        case GREATER_GREATER:
            return "GREATER_GREATER";
        case EQUAL_EQUAL:
            return "EQUAL_EQUAL";
        case BANG_EQUAL:
            return "BANG_EQUAL";
        case LESS:
            return "LESS";
        case LESS_EQUAL:
            return "LESS_EQUAL";
        case GREATER:
            return "GREATER";
        case GREATER_EQUAL:
            return "GREATER_EQUAL";
        case EQUAL:
            return "EQUAL";
        case BANG:
            return "BANG";
        case AMPERSAND_AMPERSAND:
            return "AMPERSAND_AMPERSAND";
        case BAR_BAR:
            return "BAR_BAR";
        case LEFT_PAREN:
            return "LEFT_PAREN";
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
        case LEFT_BRACE:
            return "LEFT_BRACE";
        case RIGHT_BRACE:
            return "RIGHT_BRACE";
        case LEFT_BRACKET:
            return "LEFT_BRACKET";
        case RIGHT_BRACKET:
            return "RIGHT_BRACKET";
        case DOUBLE_QUOTE:
            return "DOUBLE_QUOTE";
        case SINGLE_QUOTE:
            return "SINGLE_QUOTE";
        case BACKSLASH_BACKSLASH:
            return "BACKSLASH_BACKSLASH";
        case QUESTION:
            return "QUESTION";
        case COLON:
            return "COLON";
        case COLON_COLON:
            return "COLON_COLON";
        case SEMICOLON:
            return "SEMICOLON";
        case COMMA:
            return "COMMA";
        case DOT:
            return "DOT";
        case ARROW:
            return "ARROW";
        case NUMBER:
            return "NUMBER";
        case IDENTIFIER:
            return "IDENTIFIER";
        case STRING:
            return "STRING";
        case CHAR:
            return "CHAR";
        case NAMED_ARRAY:
            return "NAMED_ARRAY";
        case SLASH_SLASH:
            return "SLASH_SLASH";
        case END_OF_FILE:
            return "END_OF_FILE";
        default:
            return "UNKNOWN";
    }
}

inline std::string to_string(TokenType type) {
    return std::string(to_string_view(type));
}

inline std::string_view token_string_view(TokenType type) {
    using enum TokenType;
    switch (type) {
        case PLUS:
            return "+";
        case MINUS:
            return "-";
        case STAR:
            return "*";
        case SLASH:
            return "/";
        case PERCENT:
            return "%";
        case PLUS_PLUS:
            return "++";
        case MINUS_MINUS:
            return "--";
        case AMPERSAND:
            return "&";
        case BAR:
            return "|";
        case CARET:
            return "^";
        case TILDE:
            return "~";
        case LESS_LESS:
            return "<<";
        case GREATER_GREATER:
            return ">>";
        case EQUAL_EQUAL:
            return "==";
        case BANG_EQUAL:
            return "!=";
        case LESS:
            return "<";
        case LESS_EQUAL:
            return "<=";
        case GREATER:
            return ">";
        case GREATER_EQUAL:
            return ">=";
        case EQUAL:
            return "=";
        case BANG:
            return "!";
        case AMPERSAND_AMPERSAND:
            return "&&";
        case BAR_BAR:
            return "||";
        case LEFT_PAREN:
            return "(";
        case RIGHT_PAREN:
            return ")";
        case LEFT_BRACE:
            return "{";
        case RIGHT_BRACE:
            return "}";
        case LEFT_BRACKET:
            return "[";
        case RIGHT_BRACKET:
            return "]";
        case DOUBLE_QUOTE:
            return "\"";
        case SINGLE_QUOTE:
            return "'";
        case BACKSLASH_BACKSLASH:
            return "\\";
        case QUESTION:
            return "?";
        case COLON:
            return ":";
        case COLON_COLON:
            return "::";
        case SEMICOLON:
            return ";";
        case COMMA:
            return ",";
        case DOT:
            return ".";
        case ARROW:
            return "->";
        case NUMBER:
            return "number";
        case IDENTIFIER:
            return "identifier";
        case STRING:
            return "string";
        case CHAR:
            return "char";
        case NAMED_ARRAY:
            return "named_array";
        case SLASH_SLASH:
            return "//";
        case END_OF_FILE:
            return "\\0";
        default:
            return "";
    }
}

inline std::string token_string(TokenType type) {
    return std::string(token_string_view(type));
}

inline std::optional<TokenType> module_keyword_lookup(std::string_view str) {
    static const ccg::StringMap<TokenType> keyword_map = {
        {"named_array", TokenType::NAMED_ARRAY}
    };
    auto it = keyword_map.find(str);
    if (it != keyword_map.end()) {
        return it->second;
    }
    return std::nullopt;
}
