#pragma once

#include "ast_processor.hpp"
#include "code_generator.hpp"
#include "compile_file.hpp"
#include "parser.hpp"
#include "scanner.hpp"

#include "result_macros.hpp"

namespace ccg {
auto compile_file(std::string_view module_name, std::string_view file) -> ErrorOr<CompilerOutput> {
    Module mod{module_name};

    TRY_ASSIGN(scan, Scanner::scan(file));
    mod.tokens() = std::move(*scan);

    TRY_ASSIGN(parse, Parser::parse(mod.tokens()));
    TRY_ASSIGN(proc, AstProcessor::process(*parse, mod));

    return CodeGenerator::generate(mod);
}
}
