#include <filesystem>
#include <print>
#include <string>
#include <string_view>

#include <ml_cpp_utils/file_io.hpp>

#include "cpp_code_generator/compile_file.hpp"

using namespace std::string_view_literals;

int main() {
    static constexpr auto int_array{R"(named_array IntNamedArray : int {
    fields: foo, bar, baz;
}
)"sv};

    auto const out{ccg::compile_file("int_array", int_array)};
    if (!out) {
        std::print("{}\n", out.error().message());
        return -1;
    }

    std::string readme{std::format(R"(# C++ Code Generator

A C++ code generator utility for generating code that would be awkward or impossible with templates.

## Named Array

An array with named accessors for each element.
Essentially a single-type struct with iterable members.

### Input

```
{}
```

### Output

```cpp
{}
```
)",
                                   int_array,
                                   out->file())};

    std::filesystem::path const out_path{"./README.md"};
    if (std::filesystem::exists(out_path)) {
        auto const existing_out_file{ml::read_file(out_path)};
        if (existing_out_file == out->file()) {
            return 0;
        }
    }
    ml::write_file(out_path, readme);

    return 0;
}
