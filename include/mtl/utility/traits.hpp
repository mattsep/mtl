#pragma once

#include <iterator>
#include <type_traits>

namespace mtl::utility {

#if __cplusplus <= 201703L
template <class T>
using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;
#else
template <class T>
using remove_cvref_t = std::remove_cvref_t<T>;
#endif

/**
 * @brief The iterator category of the input iterator type.
 *
 * @tparam Iter An iterator type.
 */
template <class Iter>
using iterator_category_t = typename std::iterator_traits<Iter>::iterator_category;

/**
 * @brief The iterator value type of the input iterator type.
 *
 * @tparam Iter An iterator type.
 */
template <class Iter>
using iterator_value_t = typename std::iterator_traits<Iter>::value_type;

/**
 * @brief The iterator reference type of the input iterator type.
 *
 * @tparam Iter An iterator type.
 */
template <class Iter>
using iterator_reference_t = typename std::iterator_traits<Iter>::reference;

/**
 * @brief The iterator pointer type of the input iterator type.
 *
 * @tparam Iter An iterator type.
 */
template <class Iter>
using iterator_pointer_t = typename std::iterator_traits<Iter>::pointer;

}  // namespace mtl