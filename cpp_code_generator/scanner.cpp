#include "scanner.hpp"

namespace ccg {
auto Scanner::scan(std::string_view file) -> ErrorOr<Tokens> {
    return std::unexpected(Error("Foo", 0, 0, ErrorType::COMPILER_BUG));
}
}
