#include <gtest/gtest.h>

// Replicate the function under test from the provided code
namespace re2_python {
static inline int OneCharLen(const char* ptr) {
  return "\1\1\1\1\1\1\1\1\1\1\1\1\2\2\3\4"[(*ptr & 0xFF) >> 4];
}
}  // namespace re2_python

class OneCharLenTest_50 : public ::testing::Test {};

// ASCII characters (0x00 - 0x7F) should return 1
TEST_F(OneCharLenTest_50, AsciiNullByte_50) {
  const char c = '\x00';
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, AsciiLowRange_50) {
  const char c = '\x01';
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, AsciiSpace_50) {
  const char c = ' ';  // 0x20
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, AsciiLetterA_50) {
  const char c = 'A';  // 0x41
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, AsciiLetterZ_50) {
  const char c = 'z';  // 0x7A
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, AsciiMaxValue_50) {
  const char c = '\x7F';
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, AsciiDigit_50) {
  const char c = '0';  // 0x30
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, AsciiNewline_50) {
  const char c = '\n';  // 0x0A
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

// Continuation bytes (0x80 - 0xBF) should return 1
// These bytes have high nibble 0x8, 0x9, 0xA, 0xB -> index 8,9,10,11 -> all 1
TEST_F(OneCharLenTest_50, ContinuationByte0x80_50) {
  const char c = '\x80';
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, ContinuationByte0x9F_50) {
  const char c = '\x9F';
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, ContinuationByte0xA0_50) {
  const char c = '\xA0';
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, ContinuationByte0xBF_50) {
  const char c = '\xBF';
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

// Two-byte UTF-8 lead bytes (0xC0 - 0xDF) should return 2
// High nibble 0xC -> index 12 -> 2, high nibble 0xD -> index 13 -> 2
TEST_F(OneCharLenTest_50, TwoByteLeadLow0xC0_50) {
  const char c = '\xC0';
  EXPECT_EQ(2, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, TwoByteLeadMid0xC8_50) {
  const char c = '\xC8';
  EXPECT_EQ(2, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, TwoByteLeadHigh0xDF_50) {
  const char c = '\xDF';
  EXPECT_EQ(2, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, TwoByteLeadD0_50) {
  const char c = '\xD0';
  EXPECT_EQ(2, re2_python::OneCharLen(&c));
}

// Three-byte UTF-8 lead bytes (0xE0 - 0xEF) should return 3
// High nibble 0xE -> index 14 -> 3
TEST_F(OneCharLenTest_50, ThreeByteLeadLow0xE0_50) {
  const char c = '\xE0';
  EXPECT_EQ(3, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, ThreeByteLeadMid0xE8_50) {
  const char c = '\xE8';
  EXPECT_EQ(3, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, ThreeByteLeadHigh0xEF_50) {
  const char c = '\xEF';
  EXPECT_EQ(3, re2_python::OneCharLen(&c));
}

// Four-byte UTF-8 lead bytes (0xF0 - 0xFF) should return 4
// High nibble 0xF -> index 15 -> 4
TEST_F(OneCharLenTest_50, FourByteLeadLow0xF0_50) {
  const char c = '\xF0';
  EXPECT_EQ(4, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, FourByteLeadMid0xF4_50) {
  const char c = '\xF4';
  EXPECT_EQ(4, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, FourByteLeadHigh0xFF_50) {
  const char c = '\xFF';
  EXPECT_EQ(4, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, FourByteLeadF7_50) {
  const char c = '\xF7';
  EXPECT_EQ(4, re2_python::OneCharLen(&c));
}

// Boundary: exact nibble transitions
TEST_F(OneCharLenTest_50, BoundaryBetweenAsciiAndContinuation0x0F_50) {
  const char c = '\x0F';  // nibble 0 -> index 0 -> 1
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, BoundaryNibble1_0x10_50) {
  const char c = '\x10';  // nibble 1 -> index 1 -> 1
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

TEST_F(OneCharLenTest_50, BoundaryNibble7_0x70_50) {
  const char c = '\x70';  // nibble 7 -> index 7 -> 1
  EXPECT_EQ(1, re2_python::OneCharLen(&c));
}

// Test all 16 possible high nibble values systematically
TEST_F(OneCharLenTest_50, AllHighNibbles_50) {
  // Expected: nibbles 0-11 -> 1, nibble 12-13 -> 2, nibble 14 -> 3, nibble 15 -> 4
  int expected[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 4};
  for (int nibble = 0; nibble < 16; ++nibble) {
    char c = static_cast<char>(nibble << 4);
    EXPECT_EQ(expected[nibble], re2_python::OneCharLen(&c))
        << "Failed for high nibble " << nibble << " (byte 0x" << std::hex
        << (nibble << 4) << ")";
  }
}

// Test pointer to middle of a string (ensure it reads the pointed-to byte)
TEST_F(OneCharLenTest_50, PointerToMiddleOfString_50) {
  const char str[] = "A\xC0\xE0\xF0";
  EXPECT_EQ(1, re2_python::OneCharLen(&str[0]));  // 'A' -> 1
  EXPECT_EQ(2, re2_python::OneCharLen(&str[1]));  // 0xC0 -> 2
  EXPECT_EQ(3, re2_python::OneCharLen(&str[2]));  // 0xE0 -> 3
  EXPECT_EQ(4, re2_python::OneCharLen(&str[3]));  // 0xF0 -> 4
}
