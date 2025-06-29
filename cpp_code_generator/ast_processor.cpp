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
    for (auto const& na : parser_output_.named_arrays()) {}
    return {};
}
}
