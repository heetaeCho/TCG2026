#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

class ParseFlagsBitwiseAndTest_170 : public ::testing::Test {
 protected:
};

// Test that AND-ing a flag with itself returns the same flag
TEST_F(ParseFlagsBitwiseAndTest_170, SameFlagAndReturnsSameFlag_170) {
  Regexp::ParseFlags flags = Regexp::FoldCase;
  Regexp::ParseFlags result = flags & flags;
  EXPECT_EQ(result, Regexp::FoldCase);
}

// Test that AND-ing with zero (NoParseFlags) returns zero
TEST_F(ParseFlagsBitwiseAndTest_170, AndWithZeroReturnsZero_170) {
  Regexp::ParseFlags flags = Regexp::FoldCase;
  Regexp::ParseFlags zero = static_cast<Regexp::ParseFlags>(0);
  Regexp::ParseFlags result = flags & zero;
  EXPECT_EQ(static_cast<int>(result), 0);
}

// Test that AND-ing two different flags with no common bits returns zero
TEST_F(ParseFlagsBitwiseAndTest_170, DifferentFlagsNoCommonBitsReturnsZero_170) {
  // FoldCase = 0x01, Literal = 0x02 — these have no common bits
  Regexp::ParseFlags a = Regexp::FoldCase;
  Regexp::ParseFlags b = Regexp::Literal;
  Regexp::ParseFlags result = a & b;
  EXPECT_EQ(static_cast<int>(result), 0);
}

// Test that AND-ing combined flags extracts common bits
TEST_F(ParseFlagsBitwiseAndTest_170, CombinedFlagsExtractsCommonBits_170) {
  Regexp::ParseFlags combined = static_cast<Regexp::ParseFlags>(
      static_cast<int>(Regexp::FoldCase) | static_cast<int>(Regexp::Literal));
  Regexp::ParseFlags mask = Regexp::FoldCase;
  Regexp::ParseFlags result = combined & mask;
  EXPECT_EQ(result, Regexp::FoldCase);
}

// Test AND with all bits set (0xFFFF)
TEST_F(ParseFlagsBitwiseAndTest_170, AndWithAllBitsSetReturnsOriginal_170) {
  Regexp::ParseFlags flags = Regexp::FoldCase;
  Regexp::ParseFlags allBits = static_cast<Regexp::ParseFlags>(0xFFFFFFFF);
  Regexp::ParseFlags result = flags & allBits;
  EXPECT_EQ(result, Regexp::FoldCase);
}

// Test AND-ing two combined flag sets
TEST_F(ParseFlagsBitwiseAndTest_170, AndOfCombinedFlagSets_170) {
  Regexp::ParseFlags a = static_cast<Regexp::ParseFlags>(
      static_cast<int>(Regexp::FoldCase) | static_cast<int>(Regexp::Literal) |
      static_cast<int>(Regexp::ClassNL));
  Regexp::ParseFlags b = static_cast<Regexp::ParseFlags>(
      static_cast<int>(Regexp::Literal) | static_cast<int>(Regexp::ClassNL) |
      static_cast<int>(Regexp::DotNL));
  Regexp::ParseFlags result = a & b;
  Regexp::ParseFlags expected = static_cast<Regexp::ParseFlags>(
      static_cast<int>(Regexp::Literal) | static_cast<int>(Regexp::ClassNL));
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(expected));
}

// Test commutativity: a & b == b & a
TEST_F(ParseFlagsBitwiseAndTest_170, Commutativity_170) {
  Regexp::ParseFlags a = static_cast<Regexp::ParseFlags>(
      static_cast<int>(Regexp::FoldCase) | static_cast<int>(Regexp::Literal));
  Regexp::ParseFlags b = static_cast<Regexp::ParseFlags>(
      static_cast<int>(Regexp::Literal) | static_cast<int>(Regexp::DotNL));
  EXPECT_EQ(static_cast<int>(a & b), static_cast<int>(b & a));
}

// Test with MatchNL and WasDollar flags
TEST_F(ParseFlagsBitwiseAndTest_170, MatchNLAndWasDollar_170) {
  Regexp::ParseFlags a = Regexp::MatchNL;
  Regexp::ParseFlags b = Regexp::WasDollar;
  Regexp::ParseFlags result = a & b;
  EXPECT_EQ(static_cast<int>(result), 
            static_cast<int>(Regexp::MatchNL) & static_cast<int>(Regexp::WasDollar));
}

// Test that zero AND zero is zero
TEST_F(ParseFlagsBitwiseAndTest_170, ZeroAndZeroIsZero_170) {
  Regexp::ParseFlags zero = static_cast<Regexp::ParseFlags>(0);
  Regexp::ParseFlags result = zero & zero;
  EXPECT_EQ(static_cast<int>(result), 0);
}

}  // namespace re2
