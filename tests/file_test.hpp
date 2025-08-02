#pragma once

#include <fstream>
#include <string>

#include "gtest/gtest.h"

auto get_test_out_file_path(::testing::UnitTest const* inst) -> std::string;

template <typename T>
class FileTest : public testing::TestWithParam<T> {
  public:
    inline static std::optional<std::ofstream> out_file{std::nullopt};

    static void SetUpTestSuite() { out_file = std::nullopt; }
    static void TearDownTestSuite() { out_file = std::nullopt; }
    void init_file_if_null(::testing::UnitTest const* inst) {
        if (!this->out_file) {
            auto const out_path{get_test_out_file_path(inst)};
            out_file = std::ofstream(out_path, std::ios_base::out);
        }
    }
};
