# C++ Code Generator

A C++ code generator utility for generating code that would be awkward or impossible with templates.

## Named Array

An array with named accessors for each element.
Essentially a single-type struct with iterable members.

### Input

```
named_array Foo : int {
    fields: foo, bar, baz;
}
```

### Output

```cpp
#include <array>
#include <utility>

class Foo {
  public:
    Foo() = default;
    // Accessors
    template <typename Self>
    auto&& foo(this Self&& self) {
        return std::forward<Self>(self).elems_[0];
    }
    template <typename Self>
    auto&& bar(this Self&& self) {
        return std::forward<Self>(self).elems_[1];
    }
    template <typename Self>
    auto&& baz(this Self&& self) {
        return std::forward<Self>(self).elems_[2];
    }
    // Iterators
    template <typename Self>
    auto begin(this Self&& self) {
        return std::forward<Self>(self).elems_.begin();
    }
    template <typename Self>
    auto end(this Self&& self) {
        return std::forward<Self>(self).elems_.end();
    }
    template <typename Self>
    auto cbegin(this Self&& self) {
        return std::forward<Self>(self).elems_.cbegin();
    }
    template <typename Self>
    auto cend(this Self&& self) {
        return std::forward<Self>(self).elems_.cend();
    }
    template <typename Self>
    auto rbegin(this Self&& self) {
        return std::forward<Self>(self).elems_.rbegin();
    }
    template <typename Self>
    auto rend(this Self&& self) {
        return std::forward<Self>(self).elems_.rend();
    }
    template <typename Self>
    auto crbegin(this Self&& self) {
        return std::forward<Self>(self).elems_.crbegin();
    }
    template <typename Self>
    auto crend(this Self&& self) {
        return std::forward<Self>(self).elems_.crend();
    }
  private:
    std::array<int, 3> elems_;
};
```