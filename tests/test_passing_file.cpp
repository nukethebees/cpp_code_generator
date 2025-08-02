#include "gtest/gtest.h"

#include "cpp_code_generator/compile_file.hpp"

#include "test_passing_file.hpp"
#include "gtest_printing.hpp"

TEST_P(PassFileTest, compile_file) {
    auto const& param{GetParam()};

#if 0
    if (param.test_name == "comment_file_eof") {
        auto x{1};
    }
#endif

    auto result{ccg::compile_file(param.test_name, param.file_input)};

    ASSERT_TRUE(result) << result.error().message();
    EXPECT_EQ(*result, param.expected_output);
}
