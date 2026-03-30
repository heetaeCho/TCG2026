// File: ./TestProjects/yaml-cpp/test/dragonbox_count_factors_test_314.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

template <class UInt>
constexpr int CountFactors2(UInt n) noexcept {
  return YAML::jkj::dragonbox::detail::count_factors<2, UInt>(n);
}

template <class UInt>
constexpr int CountFactors5(UInt n) noexcept {
  return YAML::jkj::dragonbox::detail::count_factors<5, UInt>(n);
}

}  // namespace

TEST(CountFactorsTest_314, IsNoexcept_314) {
  static_assert(noexcept(YAML::jkj::dragonbox::detail::count_factors<2, std::uint32_t>(1u)),
                "count_factors should be noexcept");
  static_assert(noexcept(YAML::jkj::dragonbox::detail::count_factors<10, std::uint64_t>(1ull)),
                "count_factors should be noexcept");
  SUCCEED();
}

TEST(CountFactorsTest_314, ReturnsZeroForOne_314) {
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<2, std::uint32_t>(1u)), 0);
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<3, std::uint64_t>(1ull)), 0);
}

TEST(CountFactorsTest_314, ReturnsZeroWhenNotDivisible_314) {
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<2, std::uint32_t>(3u)), 0);
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<5, std::uint64_t>(14ull)), 0);
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<7, std::uint64_t>(48ull)), 0);
}

TEST(CountFactorsTest_314, CountsRepeatedFactorForPowerOfTwo_314) {
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<2, std::uint32_t>(2u)), 1);
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<2, std::uint32_t>(4u)), 2);
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<2, std::uint32_t>(8u)), 3);
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<2, std::uint32_t>(16u)), 4);
}

TEST(CountFactorsTest_314, CountsRepeatedFactorForPowerOfFive_314) {
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<5, std::uint32_t>(5u)), 1);
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<5, std::uint32_t>(25u)), 2);
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<5, std::uint32_t>(125u)), 3);
}

TEST(CountFactorsTest_314, CountsFactorForCompositeNumbers_314) {
  // 12 = 2^2 * 3
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<2, std::uint32_t>(12u)), 2);
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<3, std::uint32_t>(12u)), 1);

  // 1000 = 2^3 * 5^3
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<2, std::uint32_t>(1000u)), 3);
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<5, std::uint32_t>(1000u)), 3);
}

TEST(CountFactorsTest_314, WorksForDifferentUnsignedIntegerTypes_314) {
  // Same numeric value, different UInt types.
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<2, std::uint8_t>(static_cast<std::uint8_t>(8))), 3);
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<2, std::uint16_t>(static_cast<std::uint16_t>(8))), 3);
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<2, std::uint32_t>(8u)), 3);
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<2, std::uint64_t>(8ull)), 3);
}

TEST(CountFactorsTest_314, CanBeEvaluatedAtCompileTime_314) {
  // If the function is truly usable in constant evaluation contexts, these should compile.
  static_assert(CountFactors2<std::uint32_t>(1u) == 0, "constexpr evaluation failed");
  static_assert(CountFactors2<std::uint32_t>(8u) == 3, "constexpr evaluation failed");
  static_assert(CountFactors5<std::uint64_t>(125ull) == 3, "constexpr evaluation failed");
  static_assert((YAML::jkj::dragonbox::detail::count_factors<10, std::uint64_t>(1000ull) == 3),
                "constexpr evaluation failed");

  // Also assert at runtime (observable behavior remains consistent).
  constexpr int c1 = CountFactors2<std::uint32_t>(8u);
  constexpr int c2 = CountFactors5<std::uint64_t>(125ull);
  EXPECT_EQ(c1, 3);
  EXPECT_EQ(c2, 3);
}

TEST(CountFactorsTest_314, HandlesLargeValuesWithinTypeRange_314) {
  // 2^60 fits in uint64_t
  const std::uint64_t n = (1ull << 60);
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<2, std::uint64_t>(n)), 60);

  // (2^20) * 3: still has 20 factors of 2
  const std::uint64_t m = (1ull << 20) * 3ull;
  EXPECT_EQ((YAML::jkj::dragonbox::detail::count_factors<2, std::uint64_t>(m)), 20);
}