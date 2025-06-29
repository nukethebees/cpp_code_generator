#include <algorithm>
#include <array>
#include <format>
#include <span>
#include <string>
#include <string_view>
#include <unordered_set>

#include "code_generator.hpp"

#include "result_macros.hpp"

namespace ccg {
auto CodeGenerator::generate(Module const& mod) -> ErrorOr<CompilerOutput> {
    auto generator{CodeGenerator(mod)};
    TRY(generator.generate());
    return std::move(generator.output_);
}

auto CodeGenerator::generate() -> ErrorOr<void> {
    std::unordered_set<std::string> headers;
    if (mod_.named_arrays().headers().size()) {
        headers.insert("utility");
        headers.insert("array");
    }
    std::vector<std::string> sorted_headers;
    sorted_headers.reserve(headers.size());

    for (auto& header : headers) {
        sorted_headers.push_back(std::move(header));
    }
    std::sort(sorted_headers.begin(), sorted_headers.end());
    for (auto const& header : sorted_headers) {
        output_.file() += std::format("#include <{}>\n", header);
    }
    if (!headers.empty()) {
        output_.file() += "\n";
    }

    TRY(named_arrays());
    output_.file() += "\n";
    return {};
}
auto CodeGenerator::named_arrays() -> ErrorOr<void> {
    auto const& na{mod_.named_arrays()};
    for (auto const& header : na.headers()) {
        auto name{mod_.tokens().lexeme(header.name())};
        output_.file() += std::format("class {} {{\n", name);

        auto const& field_type{mod_.types().types()[header.type_index()]};
        auto field_type_name{mod_.tokens().lexeme(field_type.name())};
        auto n_indexes{header.field_indexes()};

        output_.file() += std::format("  public:\n    {}() = default;\n", name);

        if (n_indexes) {
            auto indexes{std::span(na.fields()).subspan(header.field_index_start(), n_indexes)};
            auto array_idx{0};

            output_.file() += "    // Accessors\n";
            for (auto index : indexes) {
                auto field_name{mod_.tokens().lexeme(index.name())};
                output_.file() += std::format(R"(    template <typename Self>
    auto&& {}(this Self&& self) {{
        return std::forward<Self>(self).elems_[{}];
    }}
)",
                                              field_name,
                                              array_idx);
                array_idx++;
            }
        }

        static constexpr std::array<std::string_view, 8> iter_names{
            {"begin", "end", "cbegin", "cend", "rbegin", "rend", "crbegin", "crend"}};
        output_.file() += "    // Iterators\n";
        for (auto in : iter_names) {
            output_.file() += std::format(R"(    template <typename Self>
    auto {0}(this Self&& self) {{
        return return std::forward<Self>(self).elems_.{0}();
    }}
)",
                                          in);
        }
        output_.file() +=
            std::format("  private:\n    std::array<{}, {}> elems_;\n", field_type_name, n_indexes);

        output_.file() += "};\n";
    }
    return {};
}
}
