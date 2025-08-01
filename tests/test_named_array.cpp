#include <format>
#include <ostream>
#include <string_view>
#include <vector>

#include "gtest/gtest.h"

#include "cpp_code_generator/compile_file.hpp"
#include "cpp_code_generator/types.hpp"

#include "gtest_printing.hpp"
#include "test_input.hpp"

TEST(named_array, construct) {
    Foo const foo{};
    SUCCEED();
}
