#pragma once

namespace mtl {

struct version_t {
  int const major;
  int const minor;
  int const patch;
};

constexpr auto operator<(version_t lhs, version_t rhs) {
  if (lhs.major < rhs.major) {
    return true;
  } else if (lhs.major > rhs.major) {
    return false;
  } else if (lhs.minor < rhs.minor) {
    return true;
  } else if (lhs.minor > rhs.minor) {
    return false;
  } else if (lhs.patch < rhs.patch) {
    return true;
  } else if (lhs.patch > rhs.patch) {
    return false;
  } else {
    return false;
  }
}
constexpr auto operator>(version_t lhs, version_t rhs) { return rhs < lhs; }
constexpr auto operator<=(version_t lhs, version_t rhs) { return !(lhs > rhs); }
constexpr auto operator>=(version_t lhs, version_t rhs) { return !(lhs < rhs); }
constexpr auto operator==(version_t lhs, version_t rhs) { return (lhs <= rhs) && (lhs >= rhs); }
constexpr auto operator!=(version_t lhs, version_t rhs) { return !(lhs == rhs); }

constexpr auto version = version_t{0, 1, 0};

}  // namespace mtl