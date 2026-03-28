// TEST_ID: 304
// File: test_uint128_low_304.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::wuint::uint128;

// Compile-time interface checks (do not assume internal logic; only signature/attributes).
static_assert(std::is_same<decltype(std::declval<const uint128&>().low()), std::uint_least64_t>::value,
              "uint128::low() must return std::uint_least64_t");
static_assert(noexcept(std::declval<const uint128&>().low()),
              "uint128::low() must be noexcept");

// Verify constexpr-evaluability using the public constexpr constructor and low().
constexpr uint128 kConstexprValue_304{123u, 456u};
static_assert(kConstexprValue_304.low() == 456u, "uint128::low() must be constexpr-evaluable");

class Uint128LowTest_304 : public ::testing::Test {};

TEST_F(Uint128LowTest_304, ReturnsLowFromConstructor_304) {
  const std::uint_least64_t hi = 0x1122334455667788ULL;
  const std::uint_least64_t lo = 0x99AABBCCDDEEFF00ULL;

  const uint128 v{hi, lo};
  EXPECT_EQ(v.low(), lo);
}

TEST_F(Uint128LowTest_304, ReturnsZeroLow_304) {
  const uint128 v{0u, 0u};
  EXPECT_EQ(v.low(), 0u);
}

TEST_F(Uint128LowTest_304, ReturnsMaxLow_304) {
  const uint128 v{0u, std::numeric_limits<std::uint_least64_t>::max()};
  EXPECT_EQ(v.low(), std::numeric_limits<std::uint_least64_t>::max());
}

TEST_F(Uint128LowTest_304, ReflectsDirectLowFieldWrite_304) {
  // low_ is public per the provided interface; reading it via low() is observable behavior.
  uint128 v{0u, 1u};
  EXPECT_EQ(v.low(), 1u);

  v.low_ = 42u;
  EXPECT_EQ(v.low(), 42u);

  v.low_ = std::numeric_limits<std::uint_least64_t>::max();
  EXPECT_EQ(v.low(), std::numeric_limits<std::uint_least64_t>::max());
}

TEST_F(Uint128LowTest_304, ConstCorrectness_304) {
  const uint128 v{7u, 8u};
  EXPECT_EQ(v.low(), 8u);
}

}  // namespace