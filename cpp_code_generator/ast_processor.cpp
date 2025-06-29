#include "ast_processor.hpp"

#include "result_macros.hpp"

namespace ccg {
auto AstProcessor::process(ParserOutput const& parser_output, Module& mod) -> ErrorOr<void> {
    auto processor{AstProcessor(parser_output, mod)};
    TRY(processor.process());
    return {};
}
auto AstProcessor::process() -> ErrorOr<void> {
    TRY(named_arrays());
    return {};
}
auto AstProcessor::named_arrays() -> ErrorOr<void> {
    auto const& tokens{mod_.tokens()};

    for (auto const& na : parser_output_.named_arrays()) {
        auto type_token{na.type()};
        auto type_index{mod_.types().lookup_or_add(tokens, type_token)};
        mod_.named_arrays().headers().emplace_back(na.name(), type_index);
    }

    return {};
}
}
