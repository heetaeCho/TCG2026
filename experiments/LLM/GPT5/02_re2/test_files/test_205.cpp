// File: runetochar_test_205.cc

#include <gtest/gtest.h>
#include <initializer_list>
#include <cstring>

// Bring in Rune type if available; declare the function under test.
#include "util/utf.h"  // Provides re2::Rune in the real codebase.
namespace re2 {
  int runetochar(char* str, const Rune* rune);
}

namespace {

class RunetocharTest_205 : public ::testing::Test {
 protected:
  char buf[8];

  void SetUp() override { std::memset(buf, 0, sizeof(buf)); }

  // Helper to check that runetochar writes the expected bytes and returns the expected count.
  void ExpectEncode(re2::Rune r, std::initializer_list<unsigned int> expected_bytes) {
    int n = re2::runetochar(buf, &r);
    ASSERT_EQ(n, static_cast<int>(expected_bytes.size()))
        << "Returned length mismatch";
    int i = 0;
    for (unsigned int b : expected_bytes) {
      EXPECT_EQ(static_cast<unsigned char>(buf[i]),
                static_cast<unsigned char>(b))
          << "Mismatch at byte index " << i;
      ++i;
    }
  }
};

// ---------- Normal operation ----------

TEST_F(RunetocharTest_205, AsciiOneByte_205) {
  re2::Rune r = 0x41; // 'A'
  ExpectEncode(r, {0x41});
}

TEST_F(RunetocharTest_205, OneByteBoundary_7F_205) {
  re2::Rune r = 0x7F; // Max 1-byte
  ExpectEncode(r, {0x7F});
}

TEST_F(RunetocharTest_205, TwoByteLowerBound_0080_205) {
  re2::Rune r = 0x80; // Min 2-byte
  ExpectEncode(r, {0xC2, 0x80});
}

TEST_F(RunetocharTest_205, TwoByteUpperBound_07FF_205) {
  re2::Rune r = 0x07FF; // Max 2-byte
  ExpectEncode(r, {0xDF, 0xBF});
}

TEST_F(RunetocharTest_205, ThreeByteLowerBound_0800_205) {
  re2::Rune r = 0x0800; // Min 3-byte
  ExpectEncode(r, {0xE0, 0xA0, 0x80});
}

TEST_F(RunetocharTest_205, ThreeByte_CommonSymbol_Euro_205) {
  re2::Rune r = 0x20AC; // '€'
  ExpectEncode(r, {0xE2, 0x82, 0xAC});
}

TEST_F(RunetocharTest_205, ThreeByteUpperBound_FFFF_205) {
  re2::Rune r = 0xFFFF; // Max 3-byte (before 4-byte range)
  ExpectEncode(r, {0xEF, 0xBF, 0xBF});
}

TEST_F(RunetocharTest_205, FourByteLowerBound_10000_205) {
  re2::Rune r = 0x10000; // Min 4-byte
  ExpectEncode(r, {0xF0, 0x90, 0x80, 0x80});
}

TEST_F(RunetocharTest_205, FourByte_Emoji_1F600_205) {
  re2::Rune r = 0x1F600; // 😀
  ExpectEncode(r, {0xF0, 0x9F, 0x98, 0x80});
}

// ---------- Exceptional / error cases (observable via output) ----------

TEST_F(RunetocharTest_205, OutOfRangeBecomesErrorRune_AboveMax_205) {
  // Any code point > 0x10FFFF should encode as U+FFFD (EF BF BD).
  re2::Rune r = 0x110000; // Runemax + 1
  ExpectEncode(r, {0xEF, 0xBF, 0xBD});
}

TEST_F(RunetocharTest_205, NegativeInputBecomesErrorRune_205) {
  // Negative values are out of Unicode range and should encode as U+FFFD.
  re2::Rune r = -1;
  ExpectEncode(r, {0xEF, 0xBF, 0xBD});
}

} // namespace
