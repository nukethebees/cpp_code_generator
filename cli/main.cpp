#include <cstddef>
#include <filesystem>
#include <fstream>
#include <print>
#include <string>
#include <string_view>

#include <CLI/CLI.hpp>

#include <ml_cpp_utils/file_io.hpp>

#include "cpp_code_generator/compile_file.hpp"
#include "cpp_code_generator/file_extension.hpp"

auto main(int argc, char* argv[]) -> int {
    CLI::App app{
        std::format("C++ code generator.\nBuild date (time): {} ({})\n", __DATE__, __TIME__)};

    std::string input_file_name{""};
    app.add_option("input_filename", input_file_name, "The input file path")->required();

    bool silent_on_success{false};
    app.add_flag("--silent_on_success",
                 silent_on_success,
                 "Suppress printing to the console if no errors occur.");

    CLI11_PARSE(app, argc, argv);

    if (!std::filesystem::exists(input_file_name)) {
        std::print("Invalid input file.");
        return -1;
    }
    auto const in_path{std::filesystem::path(input_file_name)};
    if (!in_path.has_extension()) {
        std::print("Input path has no extension.");
        return -1;
    }
    if (in_path.extension() != ccg::dot_file_extension) {
        std::print("Input path has no extension.");
        return -1;
    }

    auto const stem{in_path.stem()};
    auto out_path{in_path.parent_path() / stem};
    out_path += ".hpp";

    auto const file{ml::read_file(in_path)};
    auto const result{ccg::compile_file(stem.string(), file)};
    if (!result) {
        std::print("{}\n", result.error().message());
        return -1;
    }

    if (std::filesystem::exists(out_path)) {
        auto const existing_out_file{ml::read_file(out_path)};
        if (existing_out_file == result->file()) {
            if (!silent_on_success) {
                std::print("{} already exists with the same file contents.\n", out_path.string());
            }

            return 0;
        }
    }

    if (!silent_on_success) {
        std::print("Writing output to {}\n", out_path.string());
    }

    ml::write_file(out_path, result->file());

    return 0;
}
