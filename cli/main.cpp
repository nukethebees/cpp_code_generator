#include <cstddef>
#include <filesystem>
#include <fstream>
#include <print>
#include <string>
#include <string_view>

#include <CLI/CLI.hpp>

#include <ml_cpp_utils/file_io.hpp>

#include "cpp_code_generator/compile_file.hpp"

auto main(int argc, char * argv[]) -> int {
    CLI::App app{
        std::format("C++ code generator.\nBuild date (time): {} ({})\n", __DATE__, __TIME__)};

    std::string input_file_name{""};
    app.add_option("input_filename", input_file_name, "The input file path")->required();

    CLI11_PARSE(app, argc, argv);

    if (!std::filesystem::exists(input_file_name)) {
        std::print("Invalid input file.");
        return -1;
    }
    auto in_path{std::filesystem::path(input_file_name)};
    auto out_path{in_path.parent_path() / in_path.stem()};
    out_path += ".hpp";

    auto file{ml::read_file(in_path)};
    auto result{ccg::compile_file("PLACEHOLDER_MODULE_NAME", file)};
    if (!result) {
        std::print("{}\n", result.error().message());
        return -1;
    }

    ml::write_file(out_path, result->file());

    return 0;
}
