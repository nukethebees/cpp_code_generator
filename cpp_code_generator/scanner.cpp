#include "scanner.hpp"

namespace ccg {
auto Scanner::scan(std::string_view file) -> ErrorOr<Tokens> {
    auto scanner{Scanner(file)};
    return scanner.scan();
}

auto Scanner::scan() -> ErrorOr<Tokens> {
    Tokens tokens;
    return tokens;
}
}
