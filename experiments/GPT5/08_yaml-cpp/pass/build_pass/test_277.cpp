// TEST_ID: 277
#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::ieee754_binary32;
using YAML::jkj::dragonbox::ieee754_binary64;
using YAML::jkj::dragonbox::ieee754_binary_traits;

class Ieee754BinaryTraitsIsNegativeTest_277 : public ::testing::Test {};

TEST_F(Ieee754BinaryTraitsIsNegativeTest_277, IsNegativeIsLogicalNotOfIsPositive_Binary32_277) {
  using Traits = ieee754_binary_traits<ieee754_binary32, std::uint32_t, int>;

  const std::uint32_t threshold =
      (std::uint32_t{1} << (ieee754_binary32::significand_bits + ieee754_binary32::exponent_bits));

  const std::uint32_t cases[] = {
      0u,
      1u,
      threshold - 1u,
      threshold,
      threshold + 1u,
      0x7fffffffu,
      0x80000000u,
      0xffffffffu,
  };

  for (std::uint32_t u : cases) {
    EXPECT_EQ(Traits::is_negative(u), !Traits::is_positive(u)) << "u=" << u;
  }
}

TEST_F(Ieee754BinaryTraitsIsNegativeTest_277, IsNegativeIsLogicalNotOfIsPositive_Binary64_277) {
  using Traits = ieee754_binary_traits<ieee754_binary64, std::uint64_t, int>;

  const std::uint64_t threshold =
      (std::uint64_t{1} << (ieee754_binary64::significand_bits + ieee754_binary64::exponent_bits));

  const std::uint64_t cases[] = {
      0ull,
      1ull,
      threshold - 1ull,
      threshold,
      threshold + 1ull,
      0x7fffffffffffffffull,
      0x8000000000000000ull,
      0xffffffffffffffffull,
  };

  for (std::uint64_t u : cases) {
    EXPECT_EQ(Traits::is_negative(u), !Traits::is_positive(u)) << "u=" << u;
  }
}

TEST_F(Ieee754BinaryTraitsIsNegativeTest_277, BoundaryAtThreshold_Binary32_277) {
  using Traits = ieee754_binary_traits<ieee754_binary32, std::uint32_t, int>;
  const std::uint32_t threshold =
      (std::uint32_t{1} << (ieee754_binary32::significand_bits + ieee754_binary32::exponent_bits));

  EXPECT_TRUE(Traits::is_positive(threshold - 1u));
  EXPECT_FALSE(Traits::is_negative(threshold - 1u));

  EXPECT_FALSE(Traits::is_positive(threshold));
  EXPECT_TRUE(Traits::is_negative(threshold));
}

TEST_F(Ieee754BinaryTraitsIsNegativeTest_277, BoundaryAtThreshold_Binary64_277) {
  using Traits = ieee754_binary_traits<ieee754_binary64, std::uint64_t, int>;
  const std::uint64_t threshold =
      (std::uint64_t{1} << (ieee754_binary64::significand_bits + ieee754_binary64::exponent_bits));

  EXPECT_TRUE(Traits::is_positive(threshold - 1ull));
  EXPECT_FALSE(Traits::is_negative(threshold - 1ull));

  EXPECT_FALSE(Traits::is_positive(threshold));
  EXPECT_TRUE(Traits::is_negative(threshold));
}

TEST_F(Ieee754BinaryTraitsIsNegativeTest_277, IsNegativeIsNoexceptAndConstexprEvaluable_277) {
  using Traits32 = ieee754_binary_traits<ieee754_binary32, std::uint32_t, int>;
  using Traits64 = ieee754_binary_traits<ieee754_binary64, std::uint64_t, int>;

  static_assert(noexcept(Traits32::is_negative(std::uint32_t{0})), "is_negative must be noexcept");
  static_assert(noexcept(Traits64::is_negative(std::uint64_t{0})), "is_negative must be noexcept");

  constexpr bool neg32 = Traits32::is_negative(std::uint32_t{0});
  constexpr bool neg64 = Traits64::is_negative(std::uint64_t{0});
  (void)neg32;
  (void)neg64;

  SUCCEED();
}

}  // namespace