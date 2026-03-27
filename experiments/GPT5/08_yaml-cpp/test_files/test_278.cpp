// TEST_ID: 278
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "contrib/dragonbox.h"

namespace {

struct FormatExp8 {
  static constexpr int exponent_bits = 8;
};

struct FormatExp11 {
  static constexpr int exponent_bits = 11;
};

struct FormatExp0 {
  static constexpr int exponent_bits = 0;
};

template <class Format, class ExpInt>
constexpr ExpInt MaxAllOnesExponent() {
  // This mirrors the observable boundary implied by the public API:
  // "all exponent bits set" is the sentinel for non-finite in IEEE-754 encodings.
  return static_cast<ExpInt>((static_cast<ExpInt>(1) << Format::exponent_bits) - 1);
}

}  // namespace

TEST(Ieee754BinaryTraitsTest_278, IsFiniteReturnsFalseForAllOnesExponent_278) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatExp8, std::uint32_t, std::int32_t>;
  const auto all_ones = MaxAllOnesExponent<FormatExp8, std::int32_t>();

  EXPECT_FALSE(Traits::is_finite(all_ones));
}

TEST(Ieee754BinaryTraitsTest_278, IsFiniteReturnsTrueForZeroExponent_278) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatExp8, std::uint32_t, std::int32_t>;
  EXPECT_TRUE(Traits::is_finite(0));
}

TEST(Ieee754BinaryTraitsTest_278, IsFiniteReturnsTrueForMaxMinusOneExponent_278) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatExp8, std::uint32_t, std::int32_t>;
  const auto all_ones = MaxAllOnesExponent<FormatExp8, std::int32_t>();

  ASSERT_GT(all_ones, 0);
  EXPECT_TRUE(Traits::is_finite(all_ones - 1));
}

TEST(Ieee754BinaryTraitsTest_278, IsFiniteReturnsTrueForArbitraryNonMaxExponent_278) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatExp11, std::uint64_t, std::int32_t>;
  const auto all_ones = MaxAllOnesExponent<FormatExp11, std::int32_t>();

  // Pick a value clearly not equal to the all-ones sentinel.
  const std::int32_t exponent_bits = 123;
  ASSERT_NE(exponent_bits, all_ones);

  EXPECT_TRUE(Traits::is_finite(exponent_bits));
}

TEST(Ieee754BinaryTraitsTest_278, IsFiniteTreatsNegativeExponentBitsAsFinite_278) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatExp8, std::uint32_t, std::int32_t>;
  const auto all_ones = MaxAllOnesExponent<FormatExp8, std::int32_t>();

  // Observable behavior: only equality with the all-ones sentinel makes it non-finite.
  // For signed exponent_int, negative values are therefore finite.
  ASSERT_NE(-1, all_ones);
  EXPECT_TRUE(Traits::is_finite(-1));
}

TEST(Ieee754BinaryTraitsTest_278, IsFiniteWithZeroExponentWidthOnlyZeroIsNonFinite_278) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatExp0, std::uint32_t, std::int32_t>;
  const auto all_ones = MaxAllOnesExponent<FormatExp0, std::int32_t>();

  // With exponent_bits == 0, the computed "all ones" value is 0.
  EXPECT_EQ(all_ones, 0);
  EXPECT_FALSE(Traits::is_finite(0));
  EXPECT_TRUE(Traits::is_finite(1));
}

TEST(Ieee754BinaryTraitsTest_278, IsFiniteIsConstexprUsable_278) {
  using Traits = YAML::jkj::dragonbox::ieee754_binary_traits<FormatExp8, std::uint32_t, std::int32_t>;
  constexpr auto all_ones = MaxAllOnesExponent<FormatExp8, std::int32_t>();

  static_assert(Traits::is_finite(0), "is_finite should be usable in constant expressions.");
  static_assert(!Traits::is_finite(all_ones), "All-ones exponent should be non-finite.");
}