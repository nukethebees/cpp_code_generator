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
        headers.insert("compare");
        headers.insert("utility");
        headers.insert("array");
        headers.insert("cstddef");
        headers.insert("type_traits");
    }
    std::vector<std::string> sorted_headers;
    sorted_headers.reserve(headers.size());
    for (auto& header : headers) {
        sorted_headers.push_back(header);
    }
    std::sort(sorted_headers.begin(), sorted_headers.end());

    output_.file() += "#pragma once\n\n";

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

        auto const array_type{std::format("std::array<{}, {}>", field_type_name, n_indexes)};

        output_.file() += "  public:\n";
        output_.file() += std::format("    using ArrayT = {};\n", array_type);

        if (n_indexes) {
            output_.file() += std::format(R"(    // Constructors
    constexpr {0}() = default;
    template <typename... Args>
        requires ((sizeof...(Args) == {1}) && (std::constructible_from<{2}, Args> && ...))
    constexpr {0}(Args&&... args) 
        : elems_{{{{std::forward<Args>(args)...}}}}
        {{}}
    explicit constexpr {0}(ArrayT&& arr) 
        : elems_{{std::move(arr)}}
        {{}}
    explicit constexpr {0}(ArrayT const& arr) 
        : elems_{{arr}}
        {{}}
)",
                                          name,
                                          n_indexes,
                                          field_type_name);

            auto indexes{std::span(na.fields()).subspan(header.field_index_start(), n_indexes)};
            auto array_idx{0};

            output_.file() += "\n    // Accessors\n";
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
        } else {
            output_.file() += std::format(R"(  public:
    // Constructors
    constexpr {0}() = default;
)",
                                          name);
        }

        // Capacity
        output_.file() += R"(
    // Capacity
    auto size() const {
        return elems_.size();
    }
    auto empty() const {
        return elems_.empty();
    }
    auto max_size() const {
        return elems_.max_size();
    }
)";

        // Add iterators
        static constexpr std::array<std::string_view, 8> iter_names{
            {"begin", "end", "cbegin", "cend", "rbegin", "rend", "crbegin", "crend"}};
        output_.file() += "    // Iterators\n";
        for (auto in : iter_names) {
            output_.file() += std::format(R"(    template <typename Self>
    auto {0}(this Self&& self) {{
        return std::forward<Self>(self).elems_.{0}();
    }}
)",
                                          in);
        }

        // Add indexing, comparison, and the data member
        output_.file() += std::format(R"(
    template <typename Self>
    auto&& operator[](this Self&& self, std::size_t const i) {{
        return std::forward<Self>(self).elems_[i];
    }}

    // Comparison
    auto operator<=>({0} const&) const = default;
    auto operator==({0} const& other) const {{
        return elems_ == other.elems_;
    }}

    friend auto operator<=>({0} const& lhs, {1} const& rhs) {{
        return lhs.elems_ <=> rhs;
    }}
    friend bool operator==({0} const& lhs, {1} const& rhs) {{
        return lhs.elems_ == rhs;
    }}


  private:
    {1} elems_{{}};
)",
                                      name,
                                      "ArrayT");

        output_.file() += "};\n";
    }
    return {};
}
}
