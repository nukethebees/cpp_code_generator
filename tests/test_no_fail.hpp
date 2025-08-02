#include <string_view>

#include "gtest/gtest.h"

#include "gtest_printing.hpp"

using namespace std::string_literals;

struct NoFailTestFileInput {
    std::string_view test_name;
    std::string_view file_input;
    NoFailTestFileInput(std::string_view name_, std::string_view input_)
        : test_name{name_}
        , file_input{input_} {}
};

class NoFailTest : public testing::TestWithParam<NoFailTestFileInput> {};
