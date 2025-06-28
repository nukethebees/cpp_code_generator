#pragma once

#include "code_generator.hpp"
#include "compile_file.hpp"
#include "parser.hpp"
#include "scanner.hpp"

namespace ccg {
auto compile_file(std::string_view name, std::string_view file) -> ErrorOr<CompilerOutput> {
    Module mod{name};

    auto scan{Scanner::scan(file)};
    if (!scan) {
        return std::unexpected(std::move(scan.error()));
    }

    mod.tokens() = std::move(*scan);

    auto parse{Parser::parse(mod.tokens())};
    if (!parse) {
        return std::unexpected(std::move(parse.error()));
    }

    mod.named_arrays() = std::move(parse->named_arrays());
    mod.unions() = std::move(parse->unions());

    return CodeGenerator::generate(mod);
}
}
