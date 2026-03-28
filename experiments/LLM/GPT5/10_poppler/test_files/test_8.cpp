// GooCheckedOps_safeAverage_test.cpp
// Unit tests for ./TestProjects/poppler/goo/GooCheckedOps.h
//
// The TEST_ID is 8
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "TestProjects/poppler/goo/GooCheckedOps.h"

namespace {

template <typename T>
class SafeAverageTest_8 : public ::testing::Test {};
using TestedTypes_8 = ::testing::Types<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t>;
TYPED_TEST_SUITE(SafeAverageTest_8, TestedTypes_8);

TYPED_TEST(SafeAverageTest_8, SymmetricInputs_ReturnsSameValue_8) {
  const TypeParam v = static_cast<TypeParam>(0);
  EXPECT_EQ(v, safeAverage<TypeParam>(v, v));
}

TYPED_TEST(SafeAverageTest_8, ZeroAndZero_ReturnsZero_8) {
  const TypeParam z = static_cast<TypeParam>(0);
  EXPECT_EQ(z, safeAverage<TypeParam>(z, z));
}

TYPED_TEST(SafeAverageTest_8, OneAndZero_EqualsIntegerDivisionByTwo_8) {
  const TypeParam one = static_cast<TypeParam>(1);
  const TypeParam zero = static_cast<TypeParam>(0);

  // Observable behavior: returned value equals (a+b)/2 in integer arithmetic.
  EXPECT_EQ(static_cast<TypeParam>((static_cast<long long>(one) + static_cast<long long>(zero)) / 2),
            safeAverage<TypeParam>(one, zero));
  EXPECT_EQ(safeAverage<TypeParam>(one, zero), safeAverage<TypeParam>(zero, one));  // commutative
}

TYPED_TEST(SafeAverageTest_8, PositivePair_MatchesLongLongComputation_8) {
  // Choose values representable across all tested integer types.
  const TypeParam a = static_cast<TypeParam>(10);
  const TypeParam b = static_cast<TypeParam>(6);

  const auto expected =
      static_cast<TypeParam>((static_cast<long long>(a) + static_cast<long long>(b)) / 2);

  EXPECT_EQ(expected, safeAverage<TypeParam>(a, b));
}

TYPED_TEST(SafeAverageTest_8, MixedSignsOrWrapFreePair_MatchesLongLongComputation_8) {
  // For unsigned types this is just a normal pair; for signed it is mixed.
  const TypeParam a = static_cast<TypeParam>(-7);
  const TypeParam b = static_cast<TypeParam>(5);

  const auto expected =
      static_cast<TypeParam>((static_cast<long long>(a) + static_cast<long long>(b)) / 2);

  EXPECT_EQ(expected, safeAverage<TypeParam>(a, b));
}

TYPED_TEST(SafeAverageTest_8, Boundary_MaxAndMax_ReturnsMax_8) {
  const TypeParam mx = (std::numeric_limits<TypeParam>::max)();
  EXPECT_EQ(mx, safeAverage<TypeParam>(mx, mx));
}

TYPED_TEST(SafeAverageTest_8, Boundary_MinAndMin_ReturnsMin_8) {
  const TypeParam mn = (std::numeric_limits<TypeParam>::min)();
  EXPECT_EQ(mn, safeAverage<TypeParam>(mn, mn));
}

TYPED_TEST(SafeAverageTest_8, Boundary_MinAndMax_MatchesLongLongComputation_8) {
  const TypeParam mn = (std::numeric_limits<TypeParam>::min)();
  const TypeParam mx = (std::numeric_limits<TypeParam>::max)();

  const auto expected =
      static_cast<TypeParam>((static_cast<long long>(mn) + static_cast<long long>(mx)) / 2);

  EXPECT_EQ(expected, safeAverage<TypeParam>(mn, mx));
  EXPECT_EQ(expected, safeAverage<TypeParam>(mx, mn));  // commutative
}

TYPED_TEST(SafeAverageTest_8, AdjacentValues_FloorsTowardZeroAsIntegerDivisionDoes_8) {
  // Use a pair where sum is odd to exercise truncation behavior.
  const TypeParam a = static_cast<TypeParam>(5);
  const TypeParam b = static_cast<TypeParam>(6);

  const auto expected =
      static_cast<TypeParam>((static_cast<long long>(a) + static_cast<long long>(b)) / 2);

  EXPECT_EQ(expected, safeAverage<TypeParam>(a, b));
}

TEST(SafeAverageStandaloneTest_8, WorksForInt64WithinStaticAssertConstraints_8) {
  // This test is intentionally NOT using int64_t if the header's static_assert would reject it.
  // However, on typical platforms, T=int64_t would fail the "long long max must be larger" check.
  // We instead validate with a wide-but-safe signed type already covered by typed tests (int32_t)
  // and add a quick additional check for a larger *value* range via int32_t extremes.
  const int32_t a = (std::numeric_limits<int32_t>::max)();
  const int32_t b = (std::numeric_limits<int32_t>::min)();
  const auto expected =
      static_cast<int32_t>((static_cast<long long>(a) + static_cast<long long>(b)) / 2);
  EXPECT_EQ(expected, safeAverage<int32_t>(a, b));
}

}  // namespace