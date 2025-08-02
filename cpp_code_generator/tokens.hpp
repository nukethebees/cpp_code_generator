#pragma once

#include <vector>
#include <string_view>

#include "token_type.hpp"
#include "token_types.hpp"

namespace ccg {
class Tokens {
  public:
    Tokens() = default;

    void add(std::string_view lexeme, TokenPosition position, TokenType type) {
        string_positions_.push_back(token_chars_.size());
        token_chars_ += lexeme;
        source_positions_.push_back(position);
        token_lengths_.push_back(static_cast<TokenLength>(lexeme.size()));
        token_types_.push_back(type);
    }

    // Member Access
    template <typename Self>
    auto&& token_chars(this Self&& self) {
        return std::forward<Self>(self).token_chars_;
    }
    template <typename Self>
    auto&& source_positions(this Self&& self) {
        return std::forward<Self>(self).source_positions_;
    }
    template <typename Self>
    auto&& string_positions(this Self&& self) {
        return std::forward<Self>(self).string_positions_;
    }
    template <typename Self>
    auto&& token_lengths(this Self&& self) {
        return std::forward<Self>(self).token_lengths_;
    }
    template <typename Self>
    auto&& token_types(this Self&& self) {
        return std::forward<Self>(self).token_types_;
    }

    // Element access
    template <typename Self>
    auto&& type(this Self&& self, std::size_t i) {
        return std::forward<Self>(self).token_types_[i];
    }
    template <typename Self>
    auto lexeme(this Self&& self, std::size_t i) -> std::string_view {
        auto pos{self.string_positions_[i]};
        auto len{self.token_lengths_[i]};
        return std::string_view(std::forward<Self>(self).token_chars_).substr(pos, len);
    }
    template <typename Self>
    auto source_position(this Self&& self, std::size_t i) {
        return std::forward<Self>(self).source_positions_[i];
    }
    template <typename Self>
    auto string_position(this Self&& self, std::size_t i) {
        return std::forward<Self>(self).string_positions_[i];
    }
    template <typename Self>
    auto length(this Self&& self, std::size_t i) {
        return std::forward<Self>(self).token_lengths_[i];
    }
  private:
    std::string token_chars_{""};
    std::vector<TokenPosition> source_positions_;
    std::vector<std::size_t> string_positions_;
    std::vector<TokenLength> token_lengths_;
    std::vector<TokenType> token_types_;
};

}
