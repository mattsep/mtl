#pragma once

#include <type_traits>

namespace mtl {

#if __cplusplus <= 201703L
template <class T>
using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;
#else
template <class T>
using remove_cvref_t = std::remove_cvref_t<T>;
#endif

template <class Iter>
using iterator_category_t = typename std::iterator_traits<Iter>::iterator_category;

template <class Iter>
using iterator_value_t = typename std::iterator_traits<Iter>::value_type;

template <class Iter>
using iterator_reference_t = typename std::iterator_traits<Iter>::reference;

template <class Iter>
using iterator_pointer_t = typename std::iterator_traits<Iter>::pointer;

}  // namespace mtl