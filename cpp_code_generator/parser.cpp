#include "parser.hpp"

namespace ccg {
auto Parser::parse(Tokens const & tokens) -> ErrorOr<ParserOutput> {
    auto parser{Parser(tokens)};
    return parser.parse();
}

auto Parser::parse() -> ErrorOr<ParserOutput> {
    return std::unexpected(Error::placeholder_error());
}
}
