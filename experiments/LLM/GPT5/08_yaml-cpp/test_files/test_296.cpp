// TEST_ID: 296
#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// Helper aliases (these concrete trait types are part of dragonbox in yaml-cpp’s contrib header).
using FloatBits  = float_bits<ieee754_binary32>;
using DoubleBits = float_bits<ieee754_binary64>;

TEST(FloatBitsIsPositiveTest_296, ReturnsTrueForPositiveZeroBitPattern_296) {
  constexpr FloatBits v(static_cast<std::uint32_t>(0x00000000u));  // +0.0f
  EXPECT_TRUE(v.is_positive());
}

TEST(FloatBitsIsPositiveTest_296, ReturnsFalseForNegativeZeroBitPattern_296) {
  constexpr FloatBits v(static_cast<std::uint32_t>(0x80000000u));  // -0.0f
  EXPECT_FALSE(v.is_positive());
}

TEST(FloatBitsIsPositiveTest_296, ReturnsTrueForPositiveNormalNumberBitPattern_296) {
  // 1.0f in IEEE-754 binary32.
  constexpr FloatBits v(static_cast<std::uint32_t>(0x3F800000u));
  EXPECT_TRUE(v.is_positive());
}

TEST(FloatBitsIsPositiveTest_296, ReturnsFalseWhenSignBitIsSetForNormalNumberBitPattern_296) {
  // -1.0f in IEEE-754 binary32.
  constexpr FloatBits v(static_cast<std::uint32_t>(0xBF800000u));
  EXPECT_FALSE(v.is_positive());
}

TEST(FloatBitsIsPositiveTest_296, MatchesNegativityForRepresentativePatterns_296) {
  constexpr FloatBits pos_one(static_cast<std::uint32_t>(0x3F800000u));
  constexpr FloatBits neg_one(static_cast<std::uint32_t>(0xBF800000u));

  // Observable relationship across the public interface (no internal assumptions beyond bit patterns).
  EXPECT_TRUE(pos_one.is_positive());
  EXPECT_FALSE(pos_one.is_negative());

  EXPECT_FALSE(neg_one.is_positive());
  EXPECT_TRUE(neg_one.is_negative());
}

TEST(FloatBitsIsPositiveTest_296, IsNoexcept_296) {
  constexpr FloatBits v(static_cast<std::uint32_t>(0x3F800000u));
  static_assert(noexcept(v.is_positive()), "is_positive() must be noexcept");
  (void)v;
  SUCCEED();
}

TEST(FloatBitsIsPositiveTest_296, IsUsableInConstantEvaluation_296) {
  constexpr FloatBits pos(static_cast<std::uint32_t>(0x3F800000u));  // +1.0f
  constexpr FloatBits neg(static_cast<std::uint32_t>(0xBF800000u));  // -1.0f
  static_assert(pos.is_positive(), "constexpr is_positive() should work for +1.0f");
  static_assert(!neg.is_positive(), "constexpr is_positive() should work for -1.0f");
  SUCCEED();
}

TEST(DoubleBitsIsPositiveTest_296, ReturnsTrueForPositiveZeroBitPattern_296) {
  constexpr DoubleBits v(static_cast<std::uint64_t>(0x0000000000000000ull));  // +0.0
  EXPECT_TRUE(v.is_positive());
}

TEST(DoubleBitsIsPositiveTest_296, ReturnsFalseForNegativeZeroBitPattern_296) {
  constexpr DoubleBits v(static_cast<std::uint64_t>(0x8000000000000000ull));  // -0.0
  EXPECT_FALSE(v.is_positive());
}

TEST(DoubleBitsIsPositiveTest_296, ReturnsTrueForPositiveNormalNumberBitPattern_296) {
  // 1.0 in IEEE-754 binary64.
  constexpr DoubleBits v(static_cast<std::uint64_t>(0x3FF0000000000000ull));
  EXPECT_TRUE(v.is_positive());
}

TEST(DoubleBitsIsPositiveTest_296, ReturnsFalseWhenSignBitIsSetForNormalNumberBitPattern_296) {
  // -1.0 in IEEE-754 binary64.
  constexpr DoubleBits v(static_cast<std::uint64_t>(0xBFF0000000000000ull));
  EXPECT_FALSE(v.is_positive());
}

TEST(DoubleBitsIsPositiveTest_296, MatchesNegativityForRepresentativePatterns_296) {
  constexpr DoubleBits pos_one(static_cast<std::uint64_t>(0x3FF0000000000000ull));
  constexpr DoubleBits neg_one(static_cast<std::uint64_t>(0xBFF0000000000000ull));

  EXPECT_TRUE(pos_one.is_positive());
  EXPECT_FALSE(pos_one.is_negative());

  EXPECT_FALSE(neg_one.is_positive());
  EXPECT_TRUE(neg_one.is_negative());
}

TEST(DoubleBitsIsPositiveTest_296, IsNoexcept_296) {
  constexpr DoubleBits v(static_cast<std::uint64_t>(0x3FF0000000000000ull));
  static_assert(noexcept(v.is_positive()), "is_positive() must be noexcept");
  (void)v;
  SUCCEED();
}

}  // namespace