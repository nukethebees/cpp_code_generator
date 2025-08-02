#include <string_view>

#include "gtest/gtest.h"
#include "cpp_code_generator/compiler_output.hpp"

#include "file_test.hpp"

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

using PassFileTest = FileTest<PassTestFileInput>;
