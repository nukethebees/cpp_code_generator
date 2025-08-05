#include "gtest/gtest.h"

#include "gtest_printing.hpp"
#include "testp_passing_file.hpp"
#include "testp_no_fail.hpp"

static auto create_pass_inputs() -> std::vector<PassTestFileInput> {
    std::vector<PassTestFileInput> inputs;
    return inputs;
}
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
    inputs.emplace_back("empty_named_array_with_empty_fields",
                        R"(
named_array Foo : int {
    fields:;
}
)");
    inputs.emplace_back("empty_named_array_with_no_fields_token",
                        R"(
named_array Foo : int {}
)");
    inputs.emplace_back("two_empty_arrays",
                        R"(
named_array Foo : int {}
named_array Bar : int {}
)");

    inputs.emplace_back("template_type",
                        R"(
named_array Foo : Bar<int> {
    fields: a, b, c;
}
)");

    return inputs;
}

INSTANTIATE_TEST_SUITE_P(NoFailTests,
                         NoFailTest,
                         testing::ValuesIn(create_no_fail_inputs()),
                         [](auto const& info) { return std::string(info.param.test_name); });
