/**
 * @file bitfun.hpp
 * @brief A collection of bit-manipulation functions.
 */

#pragma once

#include <cstring>

#include "mtl/common.hpp"

namespace mtl::utility {

/**
 * @brief Computes the size, in bits, of the type \a T.
 *
 * @tparam T The type to compute the bit-width of.
 * @return usize
 */
template <class T>
constexpr auto bit_width() noexcept -> usize {
  return CHAR_BIT * sizeof(T);
}

/**
 * @brief Computes the size, in bits, of the type of the passed parameter.
 *
 * @tparam T (inferred) The type of the passed parameter.
 * @param t The parameter whose type will be used to compute the bit-width.
 * @return usize
 */
template <class T>
constexpr auto bit_width([[maybe_unused]] T t) noexcept -> usize {
  return bit_width<T>();
}

/**
 * @brief A standard-compliant bit-cast between two types.
 *
 * An alternative to typical type punning methods (reinterpret_casts and unions) that is
 * standard-compliant and portable. This function requires that both the source and destination
 * types are the same size and trivially copyable.
 *
 * @tparam To The destination type of the bit-cast.
 * @tparam From (inferred) The source type of the bit-cast.
 * @param from The source value.
 * @return To
 */
template <class To, class From,
          std::enable_if_t<((sizeof(To) == sizeof(From)) && std::is_trivial_v<To> &&
                            std::is_trivially_copyable_v<From>)>>
auto bit_cast(From from) noexcept -> To {
  To to;
  std::memcpy(&to, &from, sizeof(to));
  return to;
}

/**
 * @brief Performs a bitwise rotation to the left.
 *
 * @tparam T (inferred) The type of the parameter to be rotated.
 * @param t The value to be rotated.
 * @param k The number of bits to rotate.
 * @return T
 */
template <class T>
constexpr auto rotl(T t, usize k) noexcept -> T {
  return (t << k) | (t >> (bit_width(t) - k));
}

/**
 * @brief Performs a bitwise rotation to the right.
 *
 * @tparam T (inferred) The type of the parameter to be rotated.
 * @param t The value to be rotated.
 * @param k The number of bits to rotate.
 * @return T
 */
template <class T>
constexpr auto rotr(T t, usize k) noexcept -> T {
  return (t >> k) | (t << (bit_width(t) - k));
}

}  // namespace mtl::utility