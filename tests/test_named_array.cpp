#include <array>
#include <format>
#include <ostream>
#include <string_view>
#include <vector>

#include "gtest/gtest.h"

#include "cpp_code_generator/compile_file.hpp"
#include "cpp_code_generator/types.hpp"

#include "gtest_printing.hpp"
#include "test_input.hpp"

TEST(named_array, default_construct) {
    Foo const foo{};
    SUCCEED();
}
TEST(named_array, compare_int_array) {
    Foo foo{};
    foo[0] = 0;
    foo[1] = 1;
    foo[2] = 2;

    std::array<int, 3> const is_eq{0, 1, 2};
    std::array<int, 3> const is_ne{2, 1, 0};

    EXPECT_EQ(foo, is_eq);
    EXPECT_NE(foo, is_ne);
}
