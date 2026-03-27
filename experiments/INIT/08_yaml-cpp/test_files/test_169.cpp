// File: ./TestProjects/yaml-cpp/test/stream_test_169.cpp

#include <gtest/gtest.h>

#include <istream>
#include <limits>

#include "stream.h"  // Expected to declare YAML::IntroCharTypeOf and YAML::UtfIntroCharType

namespace {

using YAML::IntroCharTypeOf;
using YAML::UtfIntroCharType;

// Helper to avoid signed-char pitfalls when passing byte-ish values.
static std::istream::int_type AsIntType(unsigned int v) {
  return static_cast<std::istream::int_type>(v);
}

}  // namespace

// Covers explicit switch cases and EOF handling.
TEST(IntroCharTypeOfTest_169, ReturnsOtherForEof_169) {
  const std::istream::int_type eof = std::istream::traits_type::eof();
  EXPECT_EQ(YAML::uictOther, IntroCharTypeOf(eof));
}

TEST(IntroCharTypeOfTest_169, ReturnsUict00ForZero_169) {
  EXPECT_EQ(YAML::uict00, IntroCharTypeOf(AsIntType(0u)));
}

TEST(IntroCharTypeOfTest_169, ReturnsUictEFFor0xEF_169) {
  EXPECT_EQ(YAML::uictEF, IntroCharTypeOf(AsIntType(0xEFu)));
}

TEST(IntroCharTypeOfTest_169, ReturnsUictBBFor0xBB_169) {
  EXPECT_EQ(YAML::uictBB, IntroCharTypeOf(AsIntType(0xBBu)));
}

TEST(IntroCharTypeOfTest_169, ReturnsUictBFFor0xBF_169) {
  EXPECT_EQ(YAML::uictBF, IntroCharTypeOf(AsIntType(0xBFu)));
}

TEST(IntroCharTypeOfTest_169, ReturnsUictFEFor0xFE_169) {
  EXPECT_EQ(YAML::uictFE, IntroCharTypeOf(AsIntType(0xFEu)));
}

TEST(IntroCharTypeOfTest_169, ReturnsUictFFFor0xFF_169) {
  EXPECT_EQ(YAML::uictFF, IntroCharTypeOf(AsIntType(0xFFu)));
}

// Boundary conditions for the (ch > 0 && ch < 0xFF) ASCII bucket,
// while ensuring the explicit cases above still take precedence.
TEST(IntroCharTypeOfTest_169, ReturnsAsciiForLowestPositiveNonSpecial_169) {
  // 0x01 is > 0 and < 0xFF and not one of the explicit special cases.
  EXPECT_EQ(YAML::uictAscii, IntroCharTypeOf(AsIntType(0x01u)));
}

TEST(IntroCharTypeOfTest_169, ReturnsAsciiForTypicalAsciiChar_169) {
  EXPECT_EQ(YAML::uictAscii, IntroCharTypeOf(AsIntType(static_cast<unsigned int>('A'))));
}

TEST(IntroCharTypeOfTest_169, ReturnsAsciiFor0xFDUnder0xFF_169) {
  // 0xFD is the last value before the explicit 0xFE case (and still < 0xFF).
  EXPECT_EQ(YAML::uictAscii, IntroCharTypeOf(AsIntType(0xFDu)));
}

// Error-ish / unusual inputs: values outside 0..0xFF range should be uictOther.
TEST(IntroCharTypeOfTest_169, ReturnsOtherForNegativeNonEof_169) {
  // Use -2 to avoid EOF sentinel (commonly -1).
  const std::istream::int_type neg = static_cast<std::istream::int_type>(-2);
  EXPECT_EQ(YAML::uictOther, IntroCharTypeOf(neg));
}

TEST(IntroCharTypeOfTest_169, ReturnsOtherForAbove0xFF_169) {
  EXPECT_EQ(YAML::uictOther, IntroCharTypeOf(AsIntType(0x100u)));
}

TEST(IntroCharTypeOfTest_169, ReturnsOtherForVeryLargeValue_169) {
  const std::istream::int_type big =
      static_cast<std::istream::int_type>(std::numeric_limits<unsigned int>::max());
  EXPECT_EQ(YAML::uictOther, IntroCharTypeOf(big));
}

// Sanity check: returned value should always be a valid enum value.
TEST(IntroCharTypeOfTest_169, ResultIsWithinEnumRange_169) {
  const std::istream::int_type samples[] = {
      std::istream::traits_type::eof(), AsIntType(0u),     AsIntType(0x01u), AsIntType(0xBBu),
      AsIntType(0xBFu),               AsIntType(0xEFu),  AsIntType(0xFEu), AsIntType(0xFFu),
      AsIntType(0xFDu),               AsIntType(0x100u), static_cast<std::istream::int_type>(-2),
  };

  for (auto v : samples) {
    const UtfIntroCharType t = IntroCharTypeOf(v);
    EXPECT_GE(static_cast<int>(t), static_cast<int>(YAML::uict00));
    EXPECT_LT(static_cast<int>(t), static_cast<int>(YAML::uictMax));
  }
}