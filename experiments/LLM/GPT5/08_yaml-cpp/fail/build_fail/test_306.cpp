// File: ./TestProjects/yaml-cpp/test/dragonbox_umul64_test_306.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "contrib/dragonbox.h"

namespace {

using u32 = stdr::uint_least32_t;
using u64 = stdr::uint_least64_t;

constexpr u64 kConstexprProduct_306 =
    YAML::jkj::dragonbox::detail::wuint::umul64(u32{12345}, u32{6789});
static_assert(kConstexprProduct_306 == u64{12345} * u64{6789},
              "umul64 should be usable in constant evaluation and produce the expected result.");

static_assert(noexcept(YAML::jkj::dragonbox::detail::wuint::umul64(u32{1}, u32{2})),
              "umul64 must be noexcept.");

}  // namespace

TEST(Umul64Test_306, ReturnsZeroWhenLeftOperandZero_306) {
  const u64 result = YAML::jkj::dragonbox::detail::wuint::umul64(u32{0}, u32{98765});
  EXPECT_EQ(result, u64{0});
}

TEST(Umul64Test_306, ReturnsZeroWhenRightOperandZero_306) {
  const u64 result = YAML::jkj::dragonbox::detail::wuint::umul64(u32{98765}, u32{0});
  EXPECT_EQ(result, u64{0});
}

TEST(Umul64Test_306, ReturnsSameValueWhenMultiplyingByOne_306) {
  const u32 x = u32{0xDEADBEEF};
  const u64 result1 = YAML::jkj::dragonbox::detail::wuint::umul64(x, u32{1});
  const u64 result2 = YAML::jkj::dragonbox::detail::wuint::umul64(u32{1}, x);

  EXPECT_EQ(result1, u64{x});
  EXPECT_EQ(result2, u64{x});
}

TEST(Umul64Test_306, ComputesCorrectProductForTypicalValues_306) {
  const u32 x = u32{123456789};
  const u32 y = u32{40000};

  const u64 expected = u64{x} * u64{y};
  const u64 result = YAML::jkj::dragonbox::detail::wuint::umul64(x, y);

  EXPECT_EQ(result, expected);
}

TEST(Umul64Test_306, IsCommutativeForRepresentativeValues_306) {
  const u32 x = u32{314159265};
  const u32 y = u32{271828182};

  const u64 xy = YAML::jkj::dragonbox::detail::wuint::umul64(x, y);
  const u64 yx = YAML::jkj::dragonbox::detail::wuint::umul64(y, x);

  EXPECT_EQ(xy, yx);
}

TEST(Umul64Test_306, HandlesMax32BitOperandsWithoutOverflowIn64Bit_306) {
  const u32 max32 = (std::numeric_limits<u32>::max)();

  // Product of two 32-bit unsigned values always fits into 64 bits.
  const u64 expected = u64{max32} * u64{max32};
  const u64 result = YAML::jkj::dragonbox::detail::wuint::umul64(max32, max32);

  EXPECT_EQ(result, expected);
}

TEST(Umul64Test_306, ProducesExpectedValueForEdgePatternOperands_306) {
  const u32 x = u32{0xFFFFFFFFu};
  const u32 y = u32{0x00010001u};

  const u64 expected = u64{x} * u64{y};
  const u64 result = YAML::jkj::dragonbox::detail::wuint::umul64(x, y);

  EXPECT_EQ(result, expected);
}