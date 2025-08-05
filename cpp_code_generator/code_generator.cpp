#include <algorithm>
#include <array>
#include <format>
#include <span>
#include <string>
#include <string_view>
#include <unordered_set>

#include "code_generator.hpp"
#include "module.hpp"
#include "tokens.hpp"
#include "type_expr.hpp"

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
        output_.file() += R"(    
    // ArrayT typedefs
    using value_type = typename ArrayT::value_type;
    using size_type = typename ArrayT::size_type;
    using difference_type = typename ArrayT::difference_type;
    using reference = typename ArrayT::reference;
    using const_reference = typename ArrayT::const_reference;
    using pointer = typename ArrayT::pointer;
    using const_pointer = typename ArrayT::const_pointer;
    using iterator = typename ArrayT::iterator;
    using const_iterator = typename ArrayT::const_iterator;
    using reverse_iterator = typename ArrayT::reverse_iterator;
    using const_reverse_iterator = typename ArrayT::const_reverse_iterator;
)";

        if (n_indexes) {
            output_.file() += std::format(R"(    
    // Constructors
    constexpr {0}() = default;
    template <typename... Args>
        requires ((sizeof...(Args) == {1}) && (std::constructible_from<{2}, Args> && ...))
    constexpr {0}(Args&&... args) 
        : data_{{{{std::forward<Args>(args)...}}}}
        {{}}
    explicit constexpr {0}(ArrayT&& arr) 
        : data_{{std::move(arr)}}
        {{}}
    explicit constexpr {0}(ArrayT const& arr) 
        : data_{{arr}}
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
    constexpr auto&& {}(this Self&& self) {{
        return std::forward<Self>(self).data_[{}];
    }}
)",
                                              field_name,
                                              array_idx);
                array_idx++;
            }

            output_.file() += std::format(R"(    // Compile time indexing
    template <std::size_t I, typename Self>
    constexpr auto&& get(this Self&& self) {{
        static_assert(I < {}, "Index out of bounds");
        return std::forward<Self>(self).data_[I];
    }}
    // Runtime indexing
    template <typename Self>
    auto&& at(this Self&& self, std::size_t i) {{
        return std::forward<Self>(self).data_.at(i);
    }}
)",
                                          n_indexes);
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
    [[nodiscard]] constexpr auto size() const {
        return data_.size();
    }
    [[nodiscard]] constexpr auto empty() const {
        return data_.empty();
    }
    [[nodiscard]] constexpr auto max_size() const {
        return data_.max_size();
    }
)";

        // Add iterators
        static constexpr std::array<std::string_view, 8> iter_names{
            {"begin", "end", "cbegin", "cend", "rbegin", "rend", "crbegin", "crend"}};
        output_.file() += "    // Iterators\n";
        for (auto in : iter_names) {
            output_.file() += std::format(R"(    template <typename Self>
    auto {0}(this Self&& self) {{
        return std::forward<Self>(self).data_.{0}();
    }}
)",
                                          in);
        }

        // Add indexing, comparison, and the data member
        output_.file() += std::format(R"(
    template <typename Self>
    constexpr auto&& operator[](this Self&& self, std::size_t const i) {{
        return std::forward<Self>(self).data_[i];
    }}

    // Comparison
    auto operator<=>({0} const&) const = default;
    auto operator==({0} const& other) const {{
        return data_ == other.data_;
    }}

    friend auto operator<=>({0} const& lhs, {1} const& rhs) {{
        return lhs.data_ <=> rhs;
    }}
    friend bool operator==({0} const& lhs, {1} const& rhs) {{
        return lhs.data_ == rhs;
    }}


  private:
    {1} data_{{}};
)",
                                      name,
                                      "ArrayT");

        output_.file() += "};\n";
    }
    return {};
}

auto CodeGenerator::type_expr(ParsedTypeExpr const& expr) -> ErrorOr<void> {
    return token_range(expr.tokens());
}
auto CodeGenerator::token_range(TokenRange const& expr) -> ErrorOr<void> {
    auto const start{expr.offset};
    auto const end{start + expr.n};

    for (auto i{expr.offset}; i < end; ++i) {
        output_.file() += this->mod_.tokens().lexeme(i);
    }

    return {};
}
}
