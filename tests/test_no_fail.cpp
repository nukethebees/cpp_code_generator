#include "gtest/gtest.h"

#include "cpp_code_generator/compile_file.hpp"

#include "test_no_fail.hpp"
#include "gtest_printing.hpp"

TEST_P(NoFailTest, compile_file) {
    auto const& param{GetParam()};

    auto result{ccg::compile_file(param.test_name, param.file_input)};

    ASSERT_TRUE(result) << result.error().message();
}
