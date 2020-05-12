#pragma once

#include <type_traits>

namespace mtl::meta {

template <class...>
struct always_false : std::false_type {};

template <class...>
struct always_true : std::true_type {};

template <class T>
struct identity {
  using type = T;
};

}  // namespace mtl::meta
