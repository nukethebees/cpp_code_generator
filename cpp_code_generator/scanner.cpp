#include <format>
#include <string>
#include <string_view>

#include "scanner.hpp"
#include "token_type.hpp"

namespace ccg {
auto Scanner::scan(std::string_view file) -> ErrorOr<Tokens> {
    auto scanner{Scanner(file)};
    return scanner.scan();
}

#define TOKEN_CASE(CHAR, TOKEN_TYPE) \
    case CHAR: {                     \
        add_token(TOKEN_TYPE);       \
        break;                       \
    }

auto Scanner::scan() -> ErrorOr<Tokens> {
    Tokens tokens;
    TokenPosition base{0};
    TokenLength offset{0};

    auto update_base{[&]() -> void {
        base += offset;
        offset = 0;
    }};
    auto current_position{[&]() -> TokenPosition { return base + offset; }};
    auto is_eof{[&]() -> bool { return current_position() >= file_.size(); }};
    auto check_position_eof{
        [&](TokenPosition position) -> bool { return position >= file_.size(); }};
    auto get_char_at{
        [&](TokenPosition pos) -> char { return check_position_eof(pos) ? '\0' : file_[pos]; }};
    auto get_char{[&]() -> char { return get_char_at(current_position()); }};
    auto get_lexeme{[&]() -> std::string_view { return file_.substr(base, offset); }};
    auto peek{[&]() -> char { return get_char_at(current_position() + 1); }};

    auto add_token{[&](TokenType type) -> void { tokens.add(get_lexeme(), base, type); }};

    while (true) {
        using enum TokenType;

        auto c{get_char()};
        offset++;

        switch (c) {
            case '/': {
                if (get_char() == '/') {
                    auto next{peek()};
                    while ((next != '\n') && (next != '\0')) {
                        offset++;
                        next = peek();
                    }
                    offset++;
                } else {
                    add_token(SLASH);
                }
                break;
            }
                TOKEN_CASE(':', COLON)
                TOKEN_CASE('[', LEFT_BRACKET)
                TOKEN_CASE(']', RIGHT_BRACKET)
                TOKEN_CASE('(', LEFT_PAREN)
                TOKEN_CASE(')', RIGHT_PAREN)
                TOKEN_CASE('{', LEFT_BRACE)
                TOKEN_CASE('}', RIGHT_BRACE)
                TOKEN_CASE(',', COMMA)
                TOKEN_CASE('.', DOT)
                TOKEN_CASE(';', SEMICOLON)
            case '\t':
                [[fallthrough]];
            case ' ': {
                break;
            }
            case '\n': {
                break;
            }
            case '\0': {
                add_token(END_OF_FILE);
                goto end;
            }
            default: {
                if (is_identifier_char(c)) {
                    auto cur{get_char()};
                    while (is_inner_identifier_char(cur)) {
                        offset++;
                        cur = get_char();
                    }
                    add_token(IDENTIFIER);
                    break;
                }

                return std::unexpected(
                    Error(std::format("Unexpected token in scanner: \"{}\"\n", get_lexeme()),
                          base,
                          offset,
                          ErrorType::UNEXPECTED_SCANNER_TOKEN));
            }
        }
        update_base();
    }

end:
    return tokens;
}
}
