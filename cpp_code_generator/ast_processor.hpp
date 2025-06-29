#pragma once

#include "types.hpp"

namespace ccg {
class AstProcessor {
  private:
    AstProcessor() = delete;
    AstProcessor(ParserOutput const& parser_output)
        : parser_output_{parser_output} {}
  public:
    static auto process(ParserOutput const& parser_output) -> ErrorOr<void>;
  private:
    ParserOutput parser_output_;
};
}
