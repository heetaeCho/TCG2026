// File: rune_to_string_test_550.cc

#include <gtest/gtest.h>

//
// We rely only on the public/observable behavior of RuneToString.
// Because RuneToString is 'static' in the .cc (internal linkage),
// include the implementation so the symbol is available in this TU.
//
#include "re2/prefilter.cc"      // brings re2::RuneToString into scope
#include "re2/util/utf.h"        // for Rune constants like UTFmax, Runeerror, Runemax, etc.

namespace {

using re2::RuneToString;

TEST(RuneToStringTest_550, AsciiSingleByte_550) {
  // Normal operation: ASCII should encode as a single byte, identical to its char.
  std::string s = RuneToString('A');  // U+0041
  ASSERT_EQ(s.size(), 1u);
  EXPECT_EQ(s[0], 'A');
}

TEST(RuneToStringTest_550, NulCodePoint_IsSingleByte_550) {
  // Boundary: U+0000 must round-trip as a single 0x00 byte in std::string.
  std::string s = RuneToString(0);  // U+0000
  ASSERT_EQ(s.size(), 1u);
  EXPECT_EQ(static_cast<unsigned char>(s[0]), 0x00);
}

TEST(RuneToStringTest_550, TwoByte_U0080Boundary_550) {
  // Boundary around Runeself (0x80): U+0080 encodes to two bytes.
  std::string s = RuneToString(0x0080);
  ASSERT_EQ(s.size(), 2u);
  // Exact bytes for U+0080 are 0xC2 0x80.
  EXPECT_EQ(static_cast<unsigned char>(s[0]), 0xC2);
  EXPECT_EQ(static_cast<unsigned char>(s[1]), 0x80);
}

TEST(RuneToStringTest_550, TwoByte_Latin1Letter_550) {
  // Normal multi-byte (2-byte) example: U+00E9 ('é').
  std::string s = RuneToString(0x00E9);
  ASSERT_EQ(s.size(), 2u);
  EXPECT_EQ(static_cast<unsigned char>(s[0]), 0xC3);
  EXPECT_EQ(static_cast<unsigned char>(s[1]), 0xA9);
}

TEST(RuneToStringTest_550, ThreeByte_CommonSymbol_550) {
  // Normal multi-byte (3-byte) example: U+20AC (Euro sign).
  std::string s = RuneToString(0x20AC);
  ASSERT_EQ(s.size(), 3u);
  EXPECT_EQ(static_cast<unsigned char>(s[0]), 0xE2);
  EXPECT_EQ(static_cast<unsigned char>(s[1]), 0x82);
  EXPECT_EQ(static_cast<unsigned char>(s[2]), 0xAC);
}

TEST(RuneToStringTest_550, FourByte_Emoji_550) {
  // Normal multi-byte (4-byte) example: U+1F600 (GRINNING FACE).
  std::string s = RuneToString(0x1F600);
  ASSERT_EQ(s.size(), 4u);
  EXPECT_EQ(static_cast<unsigned char>(s[0]), 0xF0);
  EXPECT_EQ(static_cast<unsigned char>(s[1]), 0x9F);
  EXPECT_EQ(static_cast<unsigned char>(s[2]), 0x98);
  EXPECT_EQ(static_cast<unsigned char>(s[3]), 0x80);
}

TEST(RuneToStringTest_550, FourByte_Runemax_UpperBoundary_550) {
  // Boundary: maximum valid code point U+10FFFF should encode as 4 bytes.
  std::string s = RuneToString(re2::Runemax);
  ASSERT_EQ(s.size(), 4u);
  EXPECT_EQ(static_cast<unsigned char>(s[0]), 0xF4);
  EXPECT_EQ(static_cast<unsigned char>(s[1]), 0x8F);
  EXPECT_EQ(static_cast<unsigned char>(s[2]), 0xBF);
  EXPECT_EQ(static_cast<unsigned char>(s[3]), 0xBF);
}

TEST(RuneToStringTest_550, Runeerror_EncodesReplacementCharacter_550) {
  // Exceptional/observable case: explicitly encoding Runeerror should yield U+FFFD (EF BF BD).
  std::string s = RuneToString(re2::Runeerror);
  ASSERT_EQ(s.size(), 3u);
  EXPECT_EQ(static_cast<unsigned char>(s[0]), 0xEF);
  EXPECT_EQ(static_cast<unsigned char>(s[1]), 0xBF);
  EXPECT_EQ(static_cast<unsigned char>(s[2]), 0xBD);
}

TEST(RuneToStringTest_550, OutOfRange_YieldsSameAsRuneerror_550) {
  // Exceptional/observable case: values past Runemax should behave like Runeerror.
  std::string s_invalid = RuneToString(re2::Runemax + 1);
  std::string s_error   = RuneToString(re2::Runeerror);
  EXPECT_EQ(s_invalid, s_error);
}

TEST(RuneToStringTest_550, NeverExceedsUTFmaxBytes_550) {
  // Sanity check on the public contract: UTF-8 should be ≤ UTFmax bytes.
  // Use a set of representative inputs across byte lengths.
  const int inputs[] = {0x00, 0x7F, 0x80, 0x00E9, 0x20AC, 0x1F600, re2::Runemax};
  for (int r : inputs) {
    std::string s = RuneToString(r);
    EXPECT_LE(s.size(), static_cast<size_t>(re2::UTFmax));
  }
}

}  // namespace
