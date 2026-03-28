#include <gtest/gtest.h>
#include <iostream>

// Include the enum definition and function declaration
namespace YAML {

enum UtfIntroCharType {
  uict00 = 0,
  uictBB = 1,
  uictBF = 2,
  uictEF = 3,
  uictFE = 4,
  uictFF = 5,
  uictAscii = 6,
  uictOther = 7,
  uictMax = 8
};

inline UtfIntroCharType IntroCharTypeOf(std::istream::int_type ch) {
  if (std::istream::traits_type::eof() == ch) {
    return uictOther;
  }
  switch (ch) {
    case 0:
      return uict00;
    case 0xBB:
      return uictBB;
    case 0xBF:
      return uictBF;
    case 0xEF:
      return uictEF;
    case 0xFE:
      return uictFE;
    case 0xFF:
      return uictFF;
  }
  if ((ch > 0) && (ch < 0xFF)) {
    return uictAscii;
  }
  return uictOther;
}

}  // namespace YAML

class IntroCharTypeOfTest_169 : public ::testing::Test {};

// Test EOF returns uictOther
TEST_F(IntroCharTypeOfTest_169, EofReturnsOther_169) {
  std::istream::int_type eof = std::istream::traits_type::eof();
  EXPECT_EQ(YAML::uictOther, YAML::IntroCharTypeOf(eof));
}

// Test that 0x00 returns uict00
TEST_F(IntroCharTypeOfTest_169, ZeroReturnsUict00_169) {
  EXPECT_EQ(YAML::uict00, YAML::IntroCharTypeOf(0));
}

// Test that 0xBB returns uictBB
TEST_F(IntroCharTypeOfTest_169, BBReturnsUictBB_169) {
  EXPECT_EQ(YAML::uictBB, YAML::IntroCharTypeOf(0xBB));
}

// Test that 0xBF returns uictBF
TEST_F(IntroCharTypeOfTest_169, BFReturnsUictBF_169) {
  EXPECT_EQ(YAML::uictBF, YAML::IntroCharTypeOf(0xBF));
}

// Test that 0xEF returns uictEF
TEST_F(IntroCharTypeOfTest_169, EFReturnsUictEF_169) {
  EXPECT_EQ(YAML::uictEF, YAML::IntroCharTypeOf(0xEF));
}

// Test that 0xFE returns uictFE
TEST_F(IntroCharTypeOfTest_169, FEReturnsUictFE_169) {
  EXPECT_EQ(YAML::uictFE, YAML::IntroCharTypeOf(0xFE));
}

// Test that 0xFF returns uictFF
TEST_F(IntroCharTypeOfTest_169, FFReturnsUictFF_169) {
  EXPECT_EQ(YAML::uictFF, YAML::IntroCharTypeOf(0xFF));
}

// Test regular ASCII character 'A' (0x41) returns uictAscii
TEST_F(IntroCharTypeOfTest_169, AsciiLetterAReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf('A'));
}

// Test ASCII character 1 (minimum non-zero in ASCII range) returns uictAscii
TEST_F(IntroCharTypeOfTest_169, AsciiChar1ReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(1));
}

// Test ASCII character 0xFE-1 = 0xFD returns uictAscii (just below 0xFE which is special)
TEST_F(IntroCharTypeOfTest_169, AsciiFDReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(0xFD));
}

// Test boundary: character just above 0 (ch=1) returns uictAscii
TEST_F(IntroCharTypeOfTest_169, BoundaryChar1ReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(1));
}

// Test boundary: character 0xFE - 1 = 0xFD (just below 0xFE)
TEST_F(IntroCharTypeOfTest_169, BoundaryBeforeFEReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(0xFD));
}

// Test space character returns uictAscii
TEST_F(IntroCharTypeOfTest_169, SpaceReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(' '));
}

// Test tab character returns uictAscii
TEST_F(IntroCharTypeOfTest_169, TabReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf('\t'));
}

// Test newline character returns uictAscii
TEST_F(IntroCharTypeOfTest_169, NewlineReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf('\n'));
}

// Test value > 0xFF returns uictOther
TEST_F(IntroCharTypeOfTest_169, ValueAboveFFReturnsOther_169) {
  EXPECT_EQ(YAML::uictOther, YAML::IntroCharTypeOf(0x100));
}

// Test large value returns uictOther
TEST_F(IntroCharTypeOfTest_169, LargeValueReturnsOther_169) {
  EXPECT_EQ(YAML::uictOther, YAML::IntroCharTypeOf(0x1000));
}

// Test negative value (not EOF) returns uictOther
TEST_F(IntroCharTypeOfTest_169, NegativeNonEofReturnsOther_169) {
  std::istream::int_type eof = std::istream::traits_type::eof();
  std::istream::int_type neg = -2;
  // Only test if -2 is not EOF
  if (neg != eof) {
    EXPECT_EQ(YAML::uictOther, YAML::IntroCharTypeOf(neg));
  }
}

// Test various ASCII characters in the middle range
TEST_F(IntroCharTypeOfTest_169, MidRangeAsciiReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(0x50));
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(0x7F));
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(0x80));
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(0xAA));
}

// Test that 0xBA (just before 0xBB) returns uictAscii
TEST_F(IntroCharTypeOfTest_169, BoundaryBeforeBBReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(0xBA));
}

// Test that 0xBC (just after 0xBB) returns uictAscii
TEST_F(IntroCharTypeOfTest_169, BoundaryAfterBBReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(0xBC));
}

// Test that 0xBE (between 0xBB special values and 0xBF) returns uictAscii
TEST_F(IntroCharTypeOfTest_169, BetweenBBAndBFReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(0xBE));
}

// Test that 0xC0 (just after 0xBF) returns uictAscii
TEST_F(IntroCharTypeOfTest_169, BoundaryAfterBFReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(0xC0));
}

// Test that 0xEE (just before 0xEF) returns uictAscii
TEST_F(IntroCharTypeOfTest_169, BoundaryBeforeEFReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(0xEE));
}

// Test that 0xF0 (just after 0xEF) returns uictAscii
TEST_F(IntroCharTypeOfTest_169, BoundaryAfterEFReturnsAscii_169) {
  EXPECT_EQ(YAML::uictAscii, YAML::IntroCharTypeOf(0xF0));
}

// Test all special values are distinct from uictAscii
TEST_F(IntroCharTypeOfTest_169, AllSpecialValuesAreDistinct_169) {
  EXPECT_NE(YAML::uictAscii, YAML::IntroCharTypeOf(0));
  EXPECT_NE(YAML::uictAscii, YAML::IntroCharTypeOf(0xBB));
  EXPECT_NE(YAML::uictAscii, YAML::IntroCharTypeOf(0xBF));
  EXPECT_NE(YAML::uictAscii, YAML::IntroCharTypeOf(0xEF));
  EXPECT_NE(YAML::uictAscii, YAML::IntroCharTypeOf(0xFE));
  EXPECT_NE(YAML::uictAscii, YAML::IntroCharTypeOf(0xFF));
}
