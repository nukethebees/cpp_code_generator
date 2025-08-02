#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

#include <ml_cpp_utils/string_hasher.hpp>

namespace ccg {
using StringSet = std::unordered_set<std::string, ml::StringHasher, std::equal_to<>>;

template <typename T>
using StringMap = std::unordered_map<std::string, T, ml::StringHasher, std::equal_to<>>;
}
