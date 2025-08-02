#include "gtest/gtest.h"

#include "cpp_code_generator/compile_file.hpp"

#include "test_no_fail.hpp"
#include "gtest_printing.hpp"

using namespace std::string_view_literals;

TEST_P(NoFailTest, compile_file) {
    init_file_if_null(::testing::UnitTest::GetInstance());
    auto const& param{GetParam()};

    auto result{ccg::compile_file(param.test_name, param.file_input)};

    if (result) {
        auto const case_name{::testing::UnitTest::GetInstance()->current_test_case()->name()};
        auto const test_name{::testing::UnitTest::GetInstance()->current_test_info()->name()};
        static constexpr auto line1{"--------------------------------------------------------"sv};
        static constexpr auto line2{"########################################################"sv};

        *out_file << std::format(R"(
Test: {0} {1}
{5}
[START_OF_INPUT]
{3}[END_OF_INPUT]
{2}
[START_OF_OUTPUT]
{4}[END_OF_OUTPUT]
{2}
)",
                                 case_name,
                                 test_name,
                                 line1,
                                 param.file_input,
                                 result->file(),
                                 line2);
    }

    ASSERT_TRUE(result) << result.error().message();
}
