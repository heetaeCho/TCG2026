#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using Traits = YAML::jkj::dragonbox::ieee754::binary::traits;

// NOTE: The implementation is constexpr and noexcept; tests focus on observable return values
// for a variety of representative inputs (normal, boundary, and extreme).
class HasEvenSignificandBitsTest_280 : public ::testing::Test {};

TEST_F(HasEvenSignificandBitsTest_280, ReturnsTrueForZero_280) {
  EXPECT_TRUE(Traits::has_even_significand_bits(0u));
}

TEST_F(HasEvenSignificandBitsTest_280, ReturnsFalseForOne_280) {
  EXPECT_FALSE(Traits::has_even_significand_bits(1u));
}

TEST_F(HasEvenSignificandBitsTest_280, ReturnsTrueForSmallEvenNumbers_280) {
  EXPECT_TRUE(Traits::has_even_significand_bits(2u));
  EXPECT_TRUE(Traits::has_even_significand_bits(4u));
  EXPECT_TRUE(Traits::has_even_significand_bits(10u));
}

TEST_F(HasEvenSignificandBitsTest_280, ReturnsFalseForSmallOddNumbers_280) {
  EXPECT_FALSE(Traits::has_even_significand_bits(3u));
  EXPECT_FALSE(Traits::has_even_significand_bits(5u));
  EXPECT_FALSE(Traits::has_even_significand_bits(11u));
}

TEST_F(HasEvenSignificandBitsTest_280, AlternatesWithLeastSignificantBit_280) {
  // Boundary around a power-of-two and adjacent values.
  EXPECT_FALSE(Traits::has_even_significand_bits(7u));
  EXPECT_TRUE(Traits::has_even_significand_bits(8u));
  EXPECT_FALSE(Traits::has_even_significand_bits(9u));
}

TEST_F(HasEvenSignificandBitsTest_280, WorksForHighBitPatterns_280) {
  // Explicit patterns to ensure behavior doesn't depend on magnitude.
  EXPECT_TRUE(Traits::has_even_significand_bits(0xFFFFFFFFFFFFFFFEULL));
  EXPECT_FALSE(Traits::has_even_significand_bits(0xFFFFFFFFFFFFFFFFULL));
  EXPECT_TRUE(Traits::has_even_significand_bits(0x8000000000000000ULL));
  EXPECT_FALSE(Traits::has_even_significand_bits(0x8000000000000001ULL));
}

TEST_F(HasEvenSignificandBitsTest_280, HandlesMaxUnsignedValue_280) {
  // Boundary / extreme value case.
  const auto max_u64 = std::numeric_limits<std::uint64_t>::max();
  EXPECT_FALSE(Traits::has_even_significand_bits(max_u64));
  EXPECT_TRUE(Traits::has_even_significand_bits(max_u64 - 1u));
}

TEST_F(HasEvenSignificandBitsTest_280, IsCallableInConstantExpressionContext_280) {
  // Observable property: can be evaluated at compile-time for representative values.
  static_assert(Traits::has_even_significand_bits(0u), "0 should be even");
  static_assert(!Traits::has_even_significand_bits(1u), "1 should be odd");
  static_assert(Traits::has_even_significand_bits(42u), "42 should be even");
  static_assert(!Traits::has_even_significand_bits(43u), "43 should be odd");
  SUCCEED();
}

}  // namespace