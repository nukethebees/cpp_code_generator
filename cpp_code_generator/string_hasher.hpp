#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace ccg {
struct string_hasher {
    using is_transparent = void;

    auto operator()(char const* txt) const -> std::size_t {
        return std::hash<std::string_view>{}(txt);
    }
    auto operator()(std::string_view txt) const -> std::size_t {
        return std::hash<std::string_view>{}(txt);
    }
    auto operator()(std::string const& txt) const -> std::size_t {
        return std::hash<std::string>{}(txt);
    }
};

using StringSet = std::unordered_set<std::string, string_hasher, std::equal_to<>>;

template <typename T>
using StringMap = std::unordered_map<std::string, T, string_hasher, std::equal_to<>>;
}
