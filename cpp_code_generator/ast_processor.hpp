#pragma once

#include "types.hpp"
#include "error.hpp"

namespace ccg {
class AstProcessor {
  private:
    AstProcessor() = delete;
    AstProcessor(ParserOutput const& parser_output, Module& mod)
        : parser_output_{parser_output}
        , mod_{mod} {}
    auto process() -> ErrorOr<void>;
    auto named_arrays() -> ErrorOr<void>;
  public:
    static auto process(ParserOutput const& parser_output, Module& mod) -> ErrorOr<void>;
  private:
    ParserOutput const& parser_output_;
    Module& mod_;
};
}
