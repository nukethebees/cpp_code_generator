#include <format>
#include <ostream>
#include <string_view>
#include <vector>

#include "gtest/gtest.h"

#include "cpp_code_generator/compile_file.hpp"
#include "cpp_code_generator/types.hpp"

using namespace std::string_literals;

struct PassTestFileInput {
    std::string_view test_name;
    std::string_view file_input;
    ccg::CompilerOutput expected_output;
    PassTestFileInput(std::string_view name_,
                      std::string_view input_,
                      ccg::CompilerOutput&& exp_out)
        : test_name{name_}
        , file_input{input_}
        , expected_output{std::move(exp_out)} {}
};
inline void PrintTo(PassTestFileInput input, std::ostream* os) {
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

class PassFileTest : public testing::TestWithParam<PassTestFileInput> {};

TEST_P(PassFileTest, compile_file) {
    auto const& param{GetParam()};

#if 1
    if (param.test_name == "comment_file_eof") {
        auto x{1};
    }
#endif

    auto result{ccg::compile_file(param.test_name, param.file_input)};

    ASSERT_TRUE(result) << result.error().message();
    EXPECT_EQ(*result, param.expected_output);
}

static auto create_pass_inputs() -> std::vector<PassTestFileInput> {
    std::vector<PassTestFileInput> inputs;
    inputs.emplace_back("empty_file", "", "\n"s);
    inputs.emplace_back("comment_file_eof", "// This is a comment", "\n"s);
    inputs.emplace_back("comment_file", "// This is a comment\n", "\n"s);
    inputs.emplace_back("comment_file_2", "//Foo\n//Bar\n", "\n"s);
    return inputs;
}

static auto pass_inputs{create_pass_inputs()};

INSTANTIATE_TEST_SUITE_P(PassFileTests,
                         PassFileTest,
                         testing::ValuesIn(pass_inputs),
                         [](auto const& info) { return std::string(info.param.test_name); });
