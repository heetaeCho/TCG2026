// File: ./TestProjects/yaml-cpp/test/floor_log10_pow2_test_320.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include <boost/multiprecision/cpp_dec_float.hpp>

#include "contrib/dragonbox.h"

namespace {

using boost::multiprecision::cpp_dec_float_100;

// A high-precision mathematical reference for floor(log10(2^e)).
// This is intentionally NOT an implementation of dragonbox internals; it’s an
// independent numeric check based on the function name/intent.
template <class Int>
long long ExpectedFloorLog10Pow2(Int e) {
  cpp_dec_float_100 ee = cpp_dec_float_100(e);
  cpp_dec_float_100 v = ee * log10(cpp_dec_float_100(2));

  // floor() is available for cpp_dec_float via ADL in boost::multiprecision.
  cpp_dec_float_100 f = floor(v);

  // Values in our tested exponent range are small (hundreds), so long long is safe.
  return static_cast<long long>(f);
}

}  // namespace

class FloorLog10Pow2Test_320 : public ::testing::Test {};

TEST_F(FloorLog10Pow2Test_320, NoexceptAndConstexpr_320) {
  using YAML::jkj::dragonbox::detail::log::floor_log10_pow2;

  static_assert(noexcept(floor_log10_pow2(0)), "floor_log10_pow2 must be noexcept");

  // Ensure it is usable in constant evaluation.
  constexpr auto v0 = floor_log10_pow2(0);
  constexpr auto v4 = floor_log10_pow2(4);
  (void)v0;
  (void)v4;

  // Also validate the constexpr values at runtime (portable with gtest).
  EXPECT_EQ(v0, floor_log10_pow2(0));
  EXPECT_EQ(v4, floor_log10_pow2(4));
}

TEST_F(FloorLog10Pow2Test_320, BasicKnownValues_320) {
  using YAML::jkj::dragonbox::detail::log::floor_log10_pow2;

  // A few small exponents (including negatives) compared to a high-precision reference.
  for (int e : {0, 1, 2, 3, 4, 9, 10, -1, -2, -3, -4, -9, -10}) {
    const auto got = floor_log10_pow2(e);
    const auto expected = ExpectedFloorLog10Pow2(e);
    EXPECT_EQ(static_cast<long long>(got), expected) << "e=" << e;
  }
}

TEST_F(FloorLog10Pow2Test_320, DefaultRangeEndpoints_320) {
  using YAML::jkj::dragonbox::detail::log::floor_log10_pow2;

  // Default template parameters indicate a supported exponent range; test extremes and near-extremes.
  for (int e : {-2620, -2619, -1, 0, 1, 2619, 2620}) {
    const auto got = floor_log10_pow2(e);
    const auto expected = ExpectedFloorLog10Pow2(e);
    EXPECT_EQ(static_cast<long long>(got), expected) << "e=" << e;
  }
}

TEST_F(FloorLog10Pow2Test_320, WorksWithDifferentIntTypes_320) {
  using YAML::jkj::dragonbox::detail::log::floor_log10_pow2;

  const std::int32_t e32 = 2620;
  const std::int64_t e64 = -2620;

  const auto got32 = floor_log10_pow2(e32);
  const auto got64 = floor_log10_pow2(e64);

  EXPECT_EQ(static_cast<long long>(got32), ExpectedFloorLog10Pow2(e32));
  EXPECT_EQ(static_cast<long long>(got64), ExpectedFloorLog10Pow2(e64));
}

TEST_F(FloorLog10Pow2Test_320, CustomReturnType_320) {
  using YAML::jkj::dragonbox::detail::log::floor_log10_pow2;

  // Verify ReturnType customization is honored (at least in type) and value matches reference.
  for (int e : {-2620, -123, -4, -1, 0, 1, 4, 123, 2620}) {
    const auto got_default = floor_log10_pow2(e);

    const auto got_i32 =
        floor_log10_pow2<-2620, 2620, std::int32_t>(e);
    const auto got_i64 =
        floor_log10_pow2<-2620, 2620, std::int64_t>(e);

    static_assert(std::is_same_v<decltype(got_i32), std::int32_t>);
    static_assert(std::is_same_v<decltype(got_i64), std::int64_t>);

    const auto expected = ExpectedFloorLog10Pow2(e);
    EXPECT_EQ(static_cast<long long>(got_default), expected) << "e=" << e;
    EXPECT_EQ(static_cast<long long>(got_i32), expected) << "e=" << e;
    EXPECT_EQ(static_cast<long long>(got_i64), expected) << "e=" << e;
  }
}

TEST_F(FloorLog10Pow2Test_320, CustomExponentBoundsInstantiation_320) {
  using YAML::jkj::dragonbox::detail::log::floor_log10_pow2;

  // Instantiate with narrower bounds and test values within those bounds.
  for (int e : {-10, -9, -1, 0, 1, 9, 10}) {
    const auto got = floor_log10_pow2<-10, 10>(e);
    const auto expected = ExpectedFloorLog10Pow2(e);
    EXPECT_EQ(static_cast<long long>(got), expected) << "e=" << e;
  }
}