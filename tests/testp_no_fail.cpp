#include "gtest/gtest.h"

#include "cpp_code_generator/compile_file.hpp"

#include "testp_no_fail.hpp"
#include "gtest_printing.hpp"

using namespace std::string_view_literals;

TEST_P(NoFailTest, compile_file) {
    init_file_if_null(::testing::UnitTest::GetInstance());
    auto const& param{GetParam()};

    auto result{ccg::compile_file(param.test_name, param.file_input)};

    auto const case_name{::testing::UnitTest::GetInstance()->current_test_case()->name()};
    auto const test_name{::testing::UnitTest::GetInstance()->current_test_info()->name()};
    static constexpr auto line_dash{"--------------------------------------------------------"sv};
    static constexpr auto line_hash{"########################################################"sv};

    *out_file << std::format(R"(
Test: {0} {1}
{2}
[START_OF_INPUT]
{4}[END_OF_INPUT]
{3}
)",
                             case_name,
                             test_name,
                             line_dash,
                             line_hash,
                             param.file_input);

    if (result) {
        *out_file << std::format(R"(
[START_OF_OUTPUT]
{}[END_OF_OUTPUT]
{}
)",
                                 result->file(),
                                 line_dash);
    } else {
        *out_file << std::format(R"(
[START_OF_OUTPUT_ERROR]
{}[END_OF_OUTPUT_ERROR]
{}
)",
                                 result.error().message(),
                                 line_dash);
    }

    ASSERT_TRUE(result) << result.error().message();
}
