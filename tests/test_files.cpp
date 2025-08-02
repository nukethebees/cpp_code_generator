#include "gtest/gtest.h"

#include "gtest_printing.hpp"
#include "test_passing_file.hpp"
#include "test_no_fail.hpp"

static auto create_pass_inputs() -> std::vector<PassTestFileInput> {
    std::vector<PassTestFileInput> inputs;
    inputs.emplace_back("empty_file", "", "\n"s);
    inputs.emplace_back("comment_file_eof", "// This is a comment", "\n"s);
    inputs.emplace_back("comment_file", "// This is a comment\n", "\n"s);
    inputs.emplace_back("comment_file_2", "//Foo\n//Bar\n", "\n"s);

    return inputs;
}

INSTANTIATE_TEST_SUITE_P(PassFileTests,
                         PassFileTest,
                         testing::ValuesIn(create_pass_inputs()),
                         [](auto const& info) { return std::string(info.param.test_name); });

static auto create_no_fail_inputs() -> std::vector<NoFailTestFileInput> {
    std::vector<NoFailTestFileInput> inputs;

    inputs.emplace_back("named_array_int",
                        R"(
named_array Foo : int {
    fields: foo, bar, baz;
}
)");

    return inputs;
}

INSTANTIATE_TEST_SUITE_P(NoFailTests,
                         NoFailTest,
                         testing::ValuesIn(create_no_fail_inputs()),
                         [](auto const& info) { return std::string(info.param.test_name); });
