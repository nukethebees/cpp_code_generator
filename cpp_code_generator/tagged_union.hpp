#pragma once

#include <vector>
#include <cstdint>
#include <utility>

#include "token_types.hpp"
#include "member.hpp"

namespace ccg {
class UnionHeader {
  public:
    UnionHeader() = delete;
    UnionHeader(uint16_t members_offset, uint8_t members_length, TokenIndex name)
        : members_offset_(members_offset)
        , members_length_(members_length)
        , name_(name) {}

    // Member Access
    template <typename Self>
    auto&& members_offset(this Self&& self) {
        return std::forward<Self>(self).members_offset_;
    }
    template <typename Self>
    auto&& members_length(this Self&& self) {
        return std::forward<Self>(self).members_length_;
    }
    template <typename Self>
    auto&& name(this Self&& self) {
        return std::forward<Self>(self).name_;
    }
  private:
    uint16_t members_offset_;
    uint8_t members_length_;
    TokenIndex name_;
};

class TaggedUnions {
  public:
    TaggedUnions() = default;

    // Member Access
    template <typename Self>
    auto&& headers(this Self&& self) {
        return std::forward<Self>(self).headers_;
    }
    template <typename Self>
    auto&& members(this Self&& self) {
        return std::forward<Self>(self).members_;
    }
  private:
    std::vector<UnionHeader> headers_;
    std::vector<Member> members_;
};
}
