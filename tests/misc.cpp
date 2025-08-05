#include "misc.hpp"

auto get_test_out_file_path(::testing::UnitTest const * inst) -> std::string {
    auto const case_name{inst->current_test_case()->name()};

    auto out_path{std::format("{}.txt", case_name)};
    for (auto & c : out_path) {
        if (c == '/') {
            c = '_';
        }
    }
    return out_path;
}
