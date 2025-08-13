# C++ Code Generator

A C++ code generator utility for generating code that would be awkward or impossible with templates.

## Named Array

An array with named accessors for each element.
Essentially a single-type struct with iterable members.

### Input

```
named_array IntNamedArray : int {
    fields: foo, bar, baz;
}

```

### Output

```cpp
#pragma once

#include <array>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

class IntNamedArray {
  public:
    using ArrayT = std::array<int, 3>;
    
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

    enum class Field : uint8_t {
        foo,
        bar,
        baz,
    };
    
    // Constructors
    constexpr IntNamedArray() = default;
    template <typename... Args>
        requires ((sizeof...(Args) == 3) && (std::constructible_from<int, Args> && ...))
    constexpr IntNamedArray(Args&&... args) 
        : data_{{std::forward<Args>(args)...}}
        {}
    explicit constexpr IntNamedArray(ArrayT&& arr) 
        : data_{std::move(arr)}
        {}
    explicit constexpr IntNamedArray(ArrayT const& arr) 
        : data_{arr}
        {}

    // Accessors
    template <typename Self>
    constexpr auto&& foo(this Self&& self) {
        return std::forward<Self>(self).data_[0];
    }
    template <typename Self>
    constexpr auto&& bar(this Self&& self) {
        return std::forward<Self>(self).data_[1];
    }
    template <typename Self>
    constexpr auto&& baz(this Self&& self) {
        return std::forward<Self>(self).data_[2];
    }
    // Compile time indexing
    template <std::size_t I, typename Self>
    constexpr auto&& get(this Self&& self) {
        static_assert(I < 3, "Index out of bounds");
        return std::forward<Self>(self).data_[I];
    }
    template <Field field, typename Self>
    constexpr auto&& get(this Self&& self) {
        constexpr std::size_t I{static_cast<std::size_t>(field)};
        static_assert(I < 3, "Index out of bounds");
        return std::forward<Self>(self).data_[I];
    }
    // Runtime indexing
    template <typename Self>
    auto&& at(this Self&& self, std::size_t i) {
        return std::forward<Self>(self).data_.at(i);
    }
    template <typename Self>
    auto&& at(this Self&& self, Field field) {
        return std::forward<Self>(self).data_.at(static_cast<std::size_t>(field));
    }

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
    // Iterators
    template <typename Self>
    auto begin(this Self&& self) {
        return std::forward<Self>(self).data_.begin();
    }
    template <typename Self>
    auto end(this Self&& self) {
        return std::forward<Self>(self).data_.end();
    }
    template <typename Self>
    auto cbegin(this Self&& self) {
        return std::forward<Self>(self).data_.cbegin();
    }
    template <typename Self>
    auto cend(this Self&& self) {
        return std::forward<Self>(self).data_.cend();
    }
    template <typename Self>
    auto rbegin(this Self&& self) {
        return std::forward<Self>(self).data_.rbegin();
    }
    template <typename Self>
    auto rend(this Self&& self) {
        return std::forward<Self>(self).data_.rend();
    }
    template <typename Self>
    auto crbegin(this Self&& self) {
        return std::forward<Self>(self).data_.crbegin();
    }
    template <typename Self>
    auto crend(this Self&& self) {
        return std::forward<Self>(self).data_.crend();
    }

    template <typename Self>
    constexpr auto&& operator[](this Self&& self, std::size_t const i) {
        return std::forward<Self>(self).data_[i];
    }

    // Comparison
    auto operator<=>(IntNamedArray const&) const = default;
    auto operator==(IntNamedArray const& other) const {
        return data_ == other.data_;
    }

    friend auto operator<=>(IntNamedArray const& lhs, ArrayT const& rhs) {
        return lhs.data_ <=> rhs;
    }
    friend bool operator==(IntNamedArray const& lhs, ArrayT const& rhs) {
        return lhs.data_ == rhs;
    }


  private:
    ArrayT data_{};
};


```
