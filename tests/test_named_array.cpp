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
    IntNamedArray const foo{};
    SUCCEED();
}
TEST(named_array, compare_int_array) {
    IntNamedArray foo{0, 1, 2};

    std::array<int, 3> const is_eq{0, 1, 2};
    std::array<int, 3> const is_ne{2, 1, 0};

    EXPECT_EQ(foo, is_eq);
    EXPECT_NE(foo, is_ne);
}
TEST(named_array, compare_other_instance) {
    IntNamedArray foo{0, 1, 2};
    IntNamedArray bar{2, 1, 0};

    EXPECT_EQ(foo, foo);
    EXPECT_NE(foo, bar);
}
