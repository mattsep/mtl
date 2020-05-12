#pragma once

#include "mtl/assert.hpp"
#include "mtl/common.hpp"
#include "mtl/random/jsf.hpp"
#include "mtl/utility/ints.hpp"

namespace mtl::random {

using default_random_engine = jsf64;

/**
 * @brief A basic random number generator that can produce numbers following some typical
 *        distributions.
 *
 * @tparam Engine The underlying random engine to use. Defaults to the Jsf64 engine.
 */
template <class Engine = default_random_engine>
class rng {
public:
  using engine_t = Engine;
  using output_t = decltype(engine_t::operator()());

  /**
   * @brief Construct a new rng object
   *
   * @param seed The seed to pass to the underlying random engine.
   */
  rng(u64 seed) noexcept : engine_{seed} {}

  /**
   * @brief Returns a random unsigned integer from the full range of the engine's output.
   *
   * @return engine_result_type
   */
  auto randu() noexcept { return engine_(); }

  /**
   * @brief Returns a random unsigned integer from the range [0, max).
   *
   * Generates a random unsigned integer from the range [0, max) via Lemire's method [1]. This a
   * fast, unbiased method that minimizes slow integer division. For 64-bit generation, this
   * requires the existence of a 128-bit integer type.
   *
   * [1] David Lemire, "Fast Random Integer Generation in an Interval", ACM Trans. Model. Comput.
   *     Simul., 29(1), 2019. (https://doi.org/10.1145/3230636)
   *
   * @param max The upper bound on the generated range.
   * @return engine_result_type
   */
  auto randu(u64 max) {
    using mtl::utility::bit_width;
    using mtl::utility::uint_bits_t;

    MTL_ASSERT(max > 0);
    static_assert(max <= engine_t::max(),
                  "Current random engine is unable to produce values large enough for requested "
                  "range");

    constexpr auto bits = bit_width<output_t>();
    using small_t = uint_bits_t<bits>;
    using big_t = uint_bits_t<2 * bits>;

    auto x = randu();
    auto m = static_cast<big_t>(x) * static_cast<big_t>(max);
    auto l = static_cast<small_t>(m);
    if (l < max) {
      auto t = static_cast<small_t>(-max) % max;
      while (l < t) {
        x = randu();
        m = static_cast<big_t>(x) * static_cast<big_t>(max);
        l = static_cast<small_t>(m);
      }
    }

    return static_cast<small_t>(m >> bits);
  }

  /**
   * @brief Returns a random unsigned integer in the range [min, max).
   *
   * @param min The lower bound of the generated range.
   * @param max The upper bound of the generated range.
   * @return integer_t
   */
  auto randu(u64 min, u64 max) {
    MTL_ASSERT(max > min);
    return min + randu(static_cast<u64>(max - min));
  }

  /**
   * @brief Returns a random integer within the full range of the engine's output.
   */
  auto randi() noexcept -> integer_t { return static_cast<integer_t>(engine_()); }

  /**
   * @brief Returns a random integer in the range [0, max).
   *
   * @param max The upper bound
   * @return integer_t
   */
  auto randi(integer_t max) noexcept -> integer_t {
    MTL_ASSERT(max > 0);
    return static_cast<integer_t>(randu(max));
  }

  /**
   * @brief Returns a random integer in the range [min, max).
   *
   * @param min The lower bound of the generated range.
   * @param max The upper bound of the generated range.
   * @return integer_t
   */
  auto randi(integer_t min, integer_t max) -> integer_t {
    MTL_ASSERT(max > min);
    return min + randi(max - min);
  }

  /**
   * @brief Returns a value sampled from a uniform distribution in the half-open interval [0, 1).
   *
   * @return real_t
   */
  auto uniform() noexcept -> real_t {
    using mtl::utility::bit_width;

    auto x = engine_();
    constexpr auto randbits = bit_width(x);
    constexpr auto realbits = bit_width<real_t>();
    constexpr auto significand_bits = (realbits == 64) ? 53 : 24;
    constexpr auto shift = (randbits >= realbits) ? (randbits - significand_bits) : 0;
    constexpr auto precision =
        (randbits >= realbits) ? (1ull << significand_bits) : (1ull << randbits);
    constexpr auto multiplier = 1.0 / precision;

    auto result = f64{(x >> shift) * multiplier};
    return static_cast<real_t>(result);
  }

  /**
   * @brief Returns a value sampled from a uniform distribution in the half-open interval [a, b).
   *
   * @param a The lower bound of the uniform sampling range.
   * @param b The upper bound of the uniform sampling range.
   * @return real_t
   */
  auto uniform(real_t a, real_t b) noexcept {
    MTL_ASSERT(b > a, "");
    return (b - a) * uniform() + a;
  }

  /**
   * @brief Returns a value sampled from a normal (Gaussian) distribution with a mean of 0 and a
   *        standard deviation of 1.
   *
   * @return real_t
   */
  auto normal() noexcept -> real_t {
    static auto cache = real_t{0};
    static auto has_cached_value = false;

    if (has_cached_value) {
      has_cached_value = false;
      return cache;
    } else {
      real_t u, v;
      real_t s = 0.0;
      while (s == 0.0 || s >= 1.0) {
        u = uniform(-1, 1);
        v = uniform(-1, 1);
        s = u * u + v * v;
      }

      s = std::sqrt(-2.0 * std::log(s) / s);

      has_cached_value = true;
      cache = v * s;

      return u * s;
    }
  }

  /**
   * @brief Returns a value sampled from a normal (Gaussian) distribution with a mean of @a m and
   *        a standard deviation of @a s.
   *
   * @param m The mean of the sampled normal distribution.
   * @param s The standard deviation of the sampled normal distribution.
   * @return real_t
   */
  auto normal(real_t m, real_t s) noexcept -> real_t { return s * normal() + m; }

private:
  Engine engine_;
};

}  // namespace mtl::random