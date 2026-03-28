// File: ./TestProjects/ninja/tests/string_piece_util_test_82.cc

#include "gtest/gtest.h"
#include "string_piece_util.h"  // Adjust include path if needed

// Basic behavior: uppercase ASCII letters are converted to lowercase.
TEST(StringPieceUtilTest_82, UppercaseLettersAreLowercased_82) {
  EXPECT_EQ('a', ToLowerASCII('A'));
  EXPECT_EQ('z', ToLowerASCII('Z'));
  EXPECT_EQ('m', ToLowerASCII('M'));
}

// Lowercase letters should remain unchanged.
TEST(StringPieceUtilTest_82, LowercaseLettersRemainUnchanged_82) {
  EXPECT_EQ('a', ToLowerASCII('a'));
  EXPECT_EQ('z', ToLowerASCII('z'));
  EXPECT_EQ('m', ToLowerASCII('m'));
}

// Digits should be unaffected.
TEST(StringPieceUtilTest_82, DigitsRemainUnchanged_82) {
  EXPECT_EQ('0', ToLowerASCII('0'));
  EXPECT_EQ('5', ToLowerASCII('5'));
  EXPECT_EQ('9', ToLowerASCII('9'));
}

// Punctuation and symbols should be unaffected.
TEST(StringPieceUtilTest_82, PunctuationAndSymbolsRemainUnchanged_82) {
  EXPECT_EQ('!', ToLowerASCII('!'));
  EXPECT_EQ('@', ToLowerASCII('@'));  // Directly before 'A'
  EXPECT_EQ('[', ToLowerASCII('['));  // Directly after 'Z'
  EXPECT_EQ('_', ToLowerASCII('_'));
}

// Boundary conditions around the 'A'–'Z' range.
TEST(StringPieceUtilTest_82, BoundaryAroundUppercaseRange_82) {
  // Just below 'A'
  EXPECT_EQ('@', ToLowerASCII('@'));
  // At boundaries
  EXPECT_EQ('a', ToLowerASCII('A'));
  EXPECT_EQ('z', ToLowerASCII('Z'));
  // Just above 'Z'
  EXPECT_EQ('[', ToLowerASCII('['));
}

// Null character should be preserved.
TEST(StringPieceUtilTest_82, NullCharacterPreserved_82) {
  EXPECT_EQ('\0', ToLowerASCII('\0'));
}

// Extended characters (outside standard ASCII letters) should be unchanged.
// This also covers potential signed-char cases.
TEST(StringPieceUtilTest_82, NonAsciiByteValuesRemainUnchanged_82) {
  signed char sc1 = static_cast<signed char>(0x80);
  signed char sc2 = static_cast<signed char>(0xFF);
  EXPECT_EQ(sc1, ToLowerASCII(sc1));
  EXPECT_EQ(sc2, ToLowerASCII(sc2));
}
