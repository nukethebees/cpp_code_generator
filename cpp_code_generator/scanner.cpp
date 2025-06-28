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

auto Scanner::scan() -> ErrorOr<Tokens> {
    Tokens tokens;
    TokenPosition base{0};
    TokenLength offset{0};
    std::string buffer;
    buffer.reserve(255);

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

        buffer.clear();
        auto cur_char{get_char()};
        offset++;

        switch (cur_char) {
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
            case '\n': {
                break;
            }
            case '\0': {
                add_token(END_OF_FILE);
                goto end;
            }
            default: {
                return std::unexpected(
                    Error(std::format("Unexpected token in scanner: {}\n", get_lexeme()),
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
