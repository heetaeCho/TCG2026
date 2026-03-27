// TEST_ID: 322
// File: test_floor_log10_pow2_minus_log10_4_over_3_322.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

template <class Int>
long long ReferenceFloorLog10Pow2MinusLog10_4Over3(Int e) {
  // Independent mathematical reference:
  // floor( log10(2^e) - log10(4/3) ) = floor( e*log10(2) - log10(4/3) )
  const long double ee = static_cast<long double>(e);
  const long double v = ee * std::log10l(2.0L) - std::log10l(4.0L / 3.0L);
  return static_cast<long long>(std::floor(v));
}

}  // namespace

TEST(FloorLog10Pow2MinusLog104Over3Test_322, IsNoexcept_322) {
  using YAML::jkj::dragonbox::detail::log::floor_log10_pow2_minus_log10_4_over_3;

  static_assert(noexcept(floor_log10_pow2_minus_log10_4_over_3(0)),
                "floor_log10_pow2_minus_log10_4_over_3(e) must be noexcept");
  static_assert(noexcept(floor_log10_pow2_minus_log10_4_over_3<int>(-1)),
                "floor_log10_pow2_minus_log10_4_over_3<Int>(e) must be noexcept");
  SUCCEED();
}

TEST(FloorLog10Pow2MinusLog104Over3Test_322, IsUsableInConstexprContext_322) {
  using YAML::jkj::dragonbox::detail::log::floor_log10_pow2_minus_log10_4_over_3;

  constexpr auto v0 = floor_log10_pow2_minus_log10_4_over_3(0);
  constexpr auto v1 = floor_log10_pow2_minus_log10_4_over_3(1);
  static_assert(v0 == v0, "constexpr value must be well-formed");
  static_assert(v1 == v1, "constexpr value must be well-formed");

  // Also ensure we can use the value in a constant expression that requires integral-like behavior.
  // We don't assume the return type, but many implementations return an integer type.
  (void)v0;
  (void)v1;
  SUCCEED();
}

TEST(FloorLog10Pow2MinusLog104Over3Test_322, MatchesIndependentMathReferenceForTypicalValues_322) {
  using YAML::jkj::dragonbox::detail::log::floor_log10_pow2_minus_log10_4_over_3;

  const int test_es[] = {0, 1, -1, 2, -2, 10, -10, 123, -456, 789, -1000};

  for (int e : test_es) {
    const auto got = floor_log10_pow2_minus_log10_4_over_3(e);
    const long long ref = ReferenceFloorLog10Pow2MinusLog10_4Over3(e);

    // Compare via wide signed integer to avoid assumptions about ReturnType.
    const long long got_ll = static_cast<long long>(got);
    EXPECT_EQ(got_ll, ref) << "e=" << e;
  }
}

TEST(FloorLog10Pow2MinusLog104Over3Test_322, WorksAtDeclaredDefaultRangeEndpoints_322) {
  using YAML::jkj::dragonbox::detail::log::floor_log10_pow2_minus_log10_4_over_3;

  // Default template parameters are min_exponent=-2985, max_exponent=2936.
  constexpr int min_e = -2985;
  constexpr int max_e = 2936;

  const auto got_min = floor_log10_pow2_minus_log10_4_over_3(min_e);
  const auto got_max = floor_log10_pow2_minus_log10_4_over_3(max_e);

  const long long ref_min = ReferenceFloorLog10Pow2MinusLog10_4Over3(min_e);
  const long long ref_max = ReferenceFloorLog10Pow2MinusLog10_4Over3(max_e);

  EXPECT_EQ(static_cast<long long>(got_min), ref_min);
  EXPECT_EQ(static_cast<long long>(got_max), ref_max);
}

TEST(FloorLog10Pow2MinusLog104Over3Test_322, AcceptsDifferentIntegerInputTypes_322) {
  using YAML::jkj::dragonbox::detail::log::floor_log10_pow2_minus_log10_4_over_3;

  const std::int32_t e32 = 321;
  const std::int64_t e64 = -654;

  const auto got32 = floor_log10_pow2_minus_log10_4_over_3(e32);
  const auto got64 = floor_log10_pow2_minus_log10_4_over_3(e64);

  EXPECT_EQ(static_cast<long long>(got32), ReferenceFloorLog10Pow2MinusLog10_4Over3(e32));
  EXPECT_EQ(static_cast<long long>(got64), ReferenceFloorLog10Pow2MinusLog10_4Over3(e64));
}

TEST(FloorLog10Pow2MinusLog104Over3Test_322, ExplicitReturnTypeAgreesWithDefaultReturnTypeNumerically_322) {
  using YAML::jkj::dragonbox::detail::log::floor_log10_pow2_minus_log10_4_over_3;

  const int test_es[] = {0, 7, -7, 100, -100, 2936, -2985};

  for (int e : test_es) {
    const auto got_default = floor_log10_pow2_minus_log10_4_over_3(e);
    const auto got_i32 =
        floor_log10_pow2_minus_log10_4_over_3<-2985, 2936, std::int32_t>(e);
    const auto got_i64 =
        floor_log10_pow2_minus_log10_4_over_3<-2985, 2936, std::int64_t>(e);

    EXPECT_EQ(static_cast<long long>(got_default), static_cast<long long>(got_i32)) << "e=" << e;
    EXPECT_EQ(static_cast<long long>(got_default), static_cast<long long>(got_i64)) << "e=" << e;
  }
}

TEST(FloorLog10Pow2MinusLog104Over3Test_322, CustomExponentRangeTemplateParametersCompileAndBehave_322) {
  using YAML::jkj::dragonbox::detail::log::floor_log10_pow2_minus_log10_4_over_3;

  // Instantiate with a smaller exponent window and validate within that window.
  const int test_es[] = {-10, -3, 0, 3, 10};
  for (int e : test_es) {
    const auto got_small =
        floor_log10_pow2_minus_log10_4_over_3<-10, 10, std::int64_t>(e);
    const long long ref = ReferenceFloorLog10Pow2MinusLog10_4Over3(e);
    EXPECT_EQ(static_cast<long long>(got_small), ref) << "e=" << e;
  }
}