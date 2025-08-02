#include <algorithm>
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

static constexpr IntNamedArray int_input{10, 20, 30};

// Empty array
TEST(named_array, construct_empty) {
    EmptyIntNamedArray const foo{};
    EXPECT_EQ(foo.size(), 0);
}

// Int array
TEST(named_array, default_construct) {
    IntNamedArray const foo{};
    EXPECT_EQ(foo.size(), 3);
}
TEST(named_array, construct_from_array_copy) {
    IntNamedArray::ArrayT ip;
    IntNamedArray const foo{ip};
    EXPECT_EQ(foo.size(), 3);
}
TEST(named_array, construct_from_array_move) {
    IntNamedArray const foo{IntNamedArray::ArrayT{1, 2, 3}};
    EXPECT_EQ(foo.size(), 3);
}
TEST(named_array, use_accessors) {
    EXPECT_EQ(int_input.foo() + int_input.bar() + int_input.baz(), 60);
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
TEST(named_array, indexing) {
    IntNamedArray foo{0, 1, 2};

    EXPECT_EQ(foo[1], 1);
}
TEST(named_array, constexpr_int_array) {
    static constexpr IntNamedArray foo{0, 1, 2};
    static_assert(foo.size() == 3);
    static_assert(!foo.empty());
    EXPECT_EQ(foo[1], 1);
}

// Iterator tests
TEST(named_array, iterator_forward) {
    std::vector<int> result;
    for (auto it = int_input.begin(); it != int_input.end(); ++it) {
        result.push_back(*it);
    }
    EXPECT_EQ(result, std::vector<int>({10, 20, 30}));
}

TEST(named_array, iterator_backward) {
    std::vector<int> result;
    for (auto it = int_input.end(); it != int_input.begin();) {
        --it;
        result.push_back(*it);
    }
    EXPECT_EQ(result, std::vector<int>({30, 20, 10}));
}

TEST(named_array, const_iterator_forward) {
    std::vector<int> result;
    for (auto it = int_input.cbegin(); it != int_input.cend(); ++it) {
        result.push_back(*it);
    }
    EXPECT_EQ(result, std::vector<int>({10, 20, 30}));
}

TEST(named_array, const_iterator_backward) {
    std::vector<int> result;
    for (auto it = int_input.cend(); it != int_input.cbegin();) {
        --it;
        result.push_back(*it);
    }
    EXPECT_EQ(result, std::vector<int>({30, 20, 10}));
}

TEST(named_array, range_for_nonconst) {
    std::vector<int> result;
    for (int v : int_input) {
        result.push_back(v);
    }
    EXPECT_EQ(result, std::vector<int>({10, 20, 30}));
}

TEST(named_array, range_for_const) {
    std::vector<int> result;
    for (int v : int_input) {
        result.push_back(v);
    }
    EXPECT_EQ(result, std::vector<int>({10, 20, 30}));
}

// Some <algorithm> tests
TEST(named_array, algorithm_reverse) {
    IntNamedArray arr{10, 20, 30};
    std::reverse(arr.begin(), arr.end());
    EXPECT_EQ(arr[0], 30);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 10);
}

TEST(named_array, algorithm_sort) {
    IntNamedArray arr{30, 10, 20};
    std::sort(arr.begin(), arr.end());
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(named_array, algorithm_find) {
    auto it = std::find(int_input.begin(), int_input.end(), 20);
    EXPECT_NE(it, int_input.end());
    EXPECT_EQ(*it, 20);
    auto not_found = std::find(int_input.begin(), int_input.end(), 99);
    EXPECT_EQ(not_found, int_input.end());
}

TEST(named_array, algorithm_count) {
    auto count_10 = static_cast<int>(std::count(int_input.begin(), int_input.end(), 10));
    auto count_99 = static_cast<int>(std::count(int_input.begin(), int_input.end(), 99));
    EXPECT_EQ(count_10, 1);
    EXPECT_EQ(count_99, 0);
}
