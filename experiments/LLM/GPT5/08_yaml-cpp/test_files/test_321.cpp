// TEST_ID: 321
#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {
using YAML::jkj::dragonbox::detail::log::floor_log2_pow10;

// A small helper oracle using long double for a safe, moderate exponent range.
// We intentionally keep the range small to avoid long-double precision pitfalls.
static inline std::int64_t OracleFloorLog2Pow10_LongDouble(int e) {
  const long double v = std::log2l(std::powl(10.0L, static_cast<long double>(e)));
  // Add a tiny positive bias to reduce risk of borderline round-down due to FP error.
  // This is not re-implementing dragonbox; it's an external math oracle.
  const long double biased = v + 1e-18L;
  return static_cast<std::int64_t>(std::floor(biased));
}
}  // namespace

TEST(DragonboxFloorLog2Pow10Test_321, IsNoexceptForCommonIntegerTypes_321) {
  EXPECT_TRUE((noexcept(floor_log2_pow10(0))));
  EXPECT_TRUE((noexcept(floor_log2_pow10(std::int32_t{0}))));
  EXPECT_TRUE((noexcept(floor_log2_pow10(std::int64_t{0}))));
  EXPECT_TRUE((noexcept(floor_log2_pow10(std::uint32_t{0}))));
  EXPECT_TRUE((noexcept(floor_log2_pow10(std::uint64_t{0}))));
}

TEST(DragonboxFloorLog2Pow10Test_321, ReturnTypeIsIntegralByDefault_321) {
  using R = decltype(floor_log2_pow10(0));
  static_assert(std::is_integral<R>::value, "Default ReturnType should be integral.");
  static_assert(std::is_signed<R>::value, "Default ReturnType should be signed (log2 can be negative).");
  SUCCEED();
}

TEST(DragonboxFloorLog2Pow10Test_321, SupportsExplicitReturnTypeAndRangeParameters_321) {
  // Just verify the template is usable with explicit ReturnType and custom exponent bounds.
  // We avoid out-of-range inputs since behavior is not specified through the interface.
  using Ret = int;
  constexpr int min_e = -10;
  constexpr int max_e = 10;

  const Ret r0 = floor_log2_pow10<min_e, max_e, Ret>(0);
  const Ret r1 = floor_log2_pow10<min_e, max_e, Ret>(1);
  const Ret r_1 = floor_log2_pow10<min_e, max_e, Ret>(-1);

  (void)r0;
  (void)r1;
  (void)r_1;
  SUCCEED();
}

TEST(DragonboxFloorLog2Pow10Test_321, ConstevalKnownValues_321) {
  // These are mathematically unambiguous reference points.
  static_assert(floor_log2_pow10(0) == 0, "log2(10^0)=0 -> floor=0");
  static_assert(floor_log2_pow10(1) == 3, "log2(10)=~3.3219 -> floor=3");
  static_assert(floor_log2_pow10(2) == 6, "log2(100)=~6.6438 -> floor=6");
  static_assert(floor_log2_pow10(-1) == -4, "log2(0.1)=~ -3.3219 -> floor=-4");
  SUCCEED();
}

TEST(DragonboxFloorLog2Pow10Test_321, MatchesMathOracleForModerateExponentRange_321) {
  // Moderate range where long double oracle is reliable on typical platforms.
  for (int e = -20; e <= 20; ++e) {
    const auto got = static_cast<std::int64_t>(floor_log2_pow10(e));
    const auto expect = OracleFloorLog2Pow10_LongDouble(e);
    EXPECT_EQ(got, expect) << "e=" << e;
  }
}

TEST(DragonboxFloorLog2Pow10Test_321, IsMonotonicNonDecreasing_321) {
  // floor(log2(10^e)) should be non-decreasing as e increases.
  std::int64_t prev = static_cast<std::int64_t>(floor_log2_pow10(-60));
  for (int e = -59; e <= 60; ++e) {
    const std::int64_t cur = static_cast<std::int64_t>(floor_log2_pow10(e));
    EXPECT_LE(prev, cur) << "e=" << e;
    prev = cur;
  }
}

TEST(DragonboxFloorLog2Pow10Test_321, StepBetweenConsecutiveExponentsIsThreeOrFour_321) {
  // Since log2(10) ~ 3.3219, increasing e by 1 increases the value by ~3.3219,
  // so the floor should jump by either 3 or 4.
  std::int64_t prev = static_cast<std::int64_t>(floor_log2_pow10(-60));
  for (int e = -59; e <= 60; ++e) {
    const std::int64_t cur = static_cast<std::int64_t>(floor_log2_pow10(e));
    const std::int64_t diff = cur - prev;
    EXPECT_TRUE(diff == 3 || diff == 4) << "e=" << e << " diff=" << diff;
    prev = cur;
  }
}

TEST(DragonboxFloorLog2Pow10Test_321, AcceptsVariousIntegerInputTypes_321) {
  // Verify it can be called with different Int types and produces consistent results.
  const int ei = 7;
  const std::int64_t el = 7;
  const std::uint64_t eu = 7;

  const auto ri = static_cast<std::int64_t>(floor_log2_pow10(ei));
  const auto rl = static_cast<std::int64_t>(floor_log2_pow10(el));
  const auto ru = static_cast<std::int64_t>(floor_log2_pow10(eu));

  EXPECT_EQ(ri, rl);
  EXPECT_EQ(ri, ru);
}