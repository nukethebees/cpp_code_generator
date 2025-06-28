#include <format>

#include "parser.hpp"

namespace ccg {
auto Parser::parse(Tokens const& tokens) -> ErrorOr<ParserOutput> {
    auto parser{Parser(tokens)};
    auto res{parser.parse()};
    if (!res) {
        return std::unexpected(std::move(res.error()));
    }
    return std::move(parser.output);
}

auto Parser::parse() -> ErrorOr<void> {
    return module_item();
}
auto Parser::module_item() -> ErrorOr<void> {
    auto type{cur_type()};

    switch (type) {
        using enum TokenType;
        case END_OF_FILE: {
            break;
        }
        default: {
            auto lex{cur_lexeme()};
            return std::unexpected(
                Error(std::format("Unexpected token while parsing module item: {}", lex),
                      cur_position(),
                      cur_length(),
                      ErrorType::UNEXPECTED_PARSER_TOKEN));
        }
    }

    return {};
}
}
