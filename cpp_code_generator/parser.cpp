#include <format>

#include "parser.hpp"
#include "token_type.hpp"

#include "result_macros.hpp"

namespace ccg {
auto Parser::parse(Tokens const& tokens) -> ErrorOr<ParserOutput> {
    auto parser{Parser(tokens)};
    TRY(parser.parse());
    return std::move(parser.output);
}

auto Parser::parse() -> ErrorOr<void> {
    while (!is_eof()) {
        TRY(module_item());
    }
    return {};
}
auto Parser::module_item() -> ErrorOr<void> {
    auto type{cur_type()};

    switch (type) {
        using enum TokenType;
        case IDENTIFIER: {
            auto lex{cur_lexeme()};
            auto kw{module_keyword_lookup(lex)};

            if (!kw) {
                return make_error(
                    std::format("Unexpected identifier while parsing module item: {}", lex),
                    ErrorType::UNEXPECTED_PARSER_TOKEN);
            }

            advance();
            switch (*kw) {
                case NAMED_ARRAY: {
                    TRY(named_array());
                    break;
                }
                default: {
                    break;
                }
            }
            break;
        }
        case END_OF_FILE: {
            break;
        }
        default: {
            auto lex{cur_lexeme()};
            return make_error(std::format("Unexpected token while parsing module item: {}", lex),
                              ErrorType::UNEXPECTED_PARSER_TOKEN);
        }
    }

    return {};
}
auto Parser::named_array() -> ErrorOr<void> {
    TRY_ASSIGN(name, consume_index(TokenType::IDENTIFIER));
    TRY(consume(TokenType::COLON));
    TRY_ASSIGN(type, consume_index(TokenType::IDENTIFIER));
    TRY(consume(TokenType::LEFT_BRACE));

    std::vector<TokenIndex> field_indexes;
    if (match(TokenType::IDENTIFIER, "fields")) {
        TRY(consume(TokenType::COLON));

        bool first{true};
        while (!match(TokenType::SEMICOLON)) {
            if (!first) {
                TRY(consume(TokenType::COMMA));
            }
            first = false;
            TRY_ASSIGN(field_name, consume_index(TokenType::IDENTIFIER));
            field_indexes.push_back(*field_name);
        }
    }

    TRY(consume(TokenType::RIGHT_BRACE));
    output.named_arrays().emplace_back(*name, *type, std::move(field_indexes));

    return {};
}

auto Parser::type_expr() -> ErrorOr<ParsedTypeExpr> {
    TRY_ASSIGN(type, consume_index(TokenType::IDENTIFIER));
    auto end_idx{*type};

    if (match(TokenType::LESS)) {
        TRY_ASSIGN(type_expr_idx, type_expr_args());
        end_idx = *type_expr_idx;
    }

    return ParsedTypeExpr(TokenRange(*type, end_idx - *type));
}
auto Parser::type_expr_args() -> ErrorOr<TokenIndex> {
    using enum TokenType;

    auto end_idx{cur_index()};

    bool first{true};
    while (!match(GREATER)) {
        if (!first) {
            TRY(consume(COMMA));
        }
        TRY_ASSIGN(identifier_idx, consume_index(IDENTIFIER));
        end_idx = *identifier_idx;
        first = false;
    }

    return end_idx;
}
}
