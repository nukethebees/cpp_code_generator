#pragma once

#include <string>

#include "gtest/gtest.h"

auto get_test_out_file_path(::testing::UnitTest const* inst) -> std::string;
