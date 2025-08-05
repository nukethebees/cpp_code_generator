#include <format>
#include <ostream>

#include "cpp_code_generator/compiler_output.hpp"

#include "gtest_printing.hpp"
#include "testp_passing_file.hpp"
#include "testp_no_fail.hpp"

void PrintTo(PassTestFileInput const& input, std::ostream* os) {
    *os << std::format(R"(Test: {}
Input:
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
{}[END_OF_FILE]
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Expected output:
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
{}[END_OF_FILE]
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
)",
                       input.test_name,
                       input.file_input,
                       input.expected_output.file());
}
void PrintTo(NoFailTestFileInput const& input, std::ostream* os) {
    *os << std::format(R"(Test: {}
Input:
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
{}[END_OF_FILE]
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
)",
                       input.test_name,
                       input.file_input);
}

namespace ccg {
void PrintTo(CompilerOutput const & output, std::ostream * os) {
    *os << std::format(R"(Compiler output:
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
{}[END_OF_FILE]
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
)",
output.file());
}
}