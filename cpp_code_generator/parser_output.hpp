#pragma once

#include <vector>
#include <utility>

#include "named_array.hpp"

namespace ccg {
class ParserOutput {
  public:
    ParserOutput() = default;

    template <typename Self>
    auto&& named_arrays(this Self&& self) {
        return std::forward<Self>(self).named_arrays_;
    }
  private:
    std::vector<ParsedNamedArray> named_arrays_;
};
}
