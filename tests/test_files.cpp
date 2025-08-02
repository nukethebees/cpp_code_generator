#include "gtest/gtest.h"

#include "gtest_printing.hpp"
#include "test_passing_file.hpp"
#include "test_no_fail.hpp"

static auto create_pass_inputs() -> std::vector<PassTestFileInput> {
    std::vector<PassTestFileInput> inputs;
    return inputs;
}

// INSTANTIATE_TEST_SUITE_P(PassFileTests,
//                          PassFileTest,
//                          testing::ValuesIn(create_pass_inputs()),
//                          [](auto const& info) { return std::string(info.param.test_name); });
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(PassFileTest);

static auto create_no_fail_inputs() -> std::vector<NoFailTestFileInput> {
    std::vector<NoFailTestFileInput> inputs;

    inputs.emplace_back("empty_file", "");
    inputs.emplace_back("comment_file_eof", "// This is a comment");
    inputs.emplace_back("comment_file", "// This is a comment\n");
    inputs.emplace_back("comment_file_2", "//Foo\n//Bar\n");
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
