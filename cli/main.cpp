#include <cstddef>
#include <filesystem>
#include <fstream>
#include <print>
#include <string>
#include <string_view>

#include <CLI/CLI.hpp>

#include <ml_cpp_utils/file_io.hpp>

#include "cpp_code_generator/compile_file.hpp"

auto main(int argc, char* argv[]) -> int {
    CLI::App app{
        std::format("C++ code generator.\nBuild date (time): {} ({})\n", __DATE__, __TIME__)};

    std::string input_file_name{""};
    app.add_option("input_filename", input_file_name, "The input file path")->required();

    CLI11_PARSE(app, argc, argv);

    if (!std::filesystem::exists(input_file_name)) {
        std::print("Invalid input file.");
        return -1;
    }
    auto const in_path{std::filesystem::path(input_file_name)};
    auto const stem{in_path.stem()};
    auto const out_path{in_path.parent_path() / stem / ".hpp"};

    auto const file{ml::read_file(in_path)};
    auto const result{ccg::compile_file("PLACEHOLDER_MODULE_NAME", file)};
    if (!result) {
        std::print("{}\n", result.error().message());
        return -1;
    }

    if (std::filesystem::exists(out_path)) {
        auto const existing_out_file{ml::read_file(in_path)};
        if (existing_out_file == result->file()) {
            return 0;
        }
    }

    ml::write_file(out_path, result->file());

    return 0;
}
