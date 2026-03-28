// File: parse_unsigned_short_test_278.cc
#include <gtest/gtest.h>
#include <climits>
#include <cstddef>

namespace re2 { namespace re2_internal {
// Forward declaration based on the provided interface
template <>
bool Parse(const char* str, size_t n, unsigned short* dest, int radix);
}} // namespace re2::re2_internal

using re2::re2_internal::Parse;

class ParseUnsignedShortTest_278 : public ::testing::Test {};

// Normal operation: decimal parse
TEST_F(ParseUnsignedShortTest_278, ParsesDecimalNormal_278) {
  const char* s = "12345";
  unsigned short out = 0;
  ASSERT_TRUE(Parse(s, 5, &out, 10));
  EXPECT_EQ(out, static_cast<unsigned short>(12345));
}

// Normal operation: hexadecimal parse
TEST_F(ParseUnsignedShortTest_278, ParsesHexNormal_278) {
  const char* s = "FF";
  unsigned short out = 0;
  ASSERT_TRUE(Parse(s, 2, &out, 16));
  EXPECT_EQ(out, static_cast<unsigned short>(255));
}

// Honors the 'n' parameter (only first n chars are considered)
TEST_F(ParseUnsignedShortTest_278, HonorsLengthParameter_278) {
  const char* s = "12345garbage";
  unsigned short out = 0;
  ASSERT_TRUE(Parse(s, 5, &out, 10));  // Only "12345"
  EXPECT_EQ(out, static_cast<unsigned short>(12345));
}

// Null destination: succeeds without writing (cannot verify write; only success)
TEST_F(ParseUnsignedShortTest_278, NullDest_ReportsSuccessWithoutWrite_278) {
  const char* s = "42";
  // Expect success when input is valid and in-range, even with nullptr dest
  EXPECT_TRUE(Parse(s, 2, /*dest=*/nullptr, 10));
}

// Boundary: minimum (0)
TEST_F(ParseUnsignedShortTest_278, Boundary_MinZero_278) {
  const char* s = "0";
  unsigned short out = 123;  // sentinel
  ASSERT_TRUE(Parse(s, 1, &out, 10));
  EXPECT_EQ(out, static_cast<unsigned short>(0));
}

// Boundary: maximum (65535)
TEST_F(ParseUnsignedShortTest_278, Boundary_MaxUShort_278) {
  const char* s = "65535";
  unsigned short out = 0;
  ASSERT_TRUE(Parse(s, 5, &out, 10));
  EXPECT_EQ(out, static_cast<unsigned short>(65535));
}

// Out of range (decimal): 65536 should fail for unsigned short
TEST_F(ParseUnsignedShortTest_278, OutOfRange_Decimal_278) {
  const char* s = "65536";
  unsigned short out = 7;
  EXPECT_FALSE(Parse(s, 5, &out, 10));
}

// Out of range (hex): 0x10000 == 65536 should fail
TEST_F(ParseUnsignedShortTest_278, OutOfRange_Hex_278) {
  const char* s = "10000"; // 0x10000
  unsigned short out = 7;
  EXPECT_FALSE(Parse(s, 5, &out, 16));
}

// Invalid input: non-digit for the given radix should fail
TEST_F(ParseUnsignedShortTest_278, InvalidInput_ReturnsFalse_278) {
  const char* s = "xyz";
  unsigned short out = 7;
  EXPECT_FALSE(Parse(s, 3, &out, 10));
}

// Radix handling: same lexeme "10" is value 2 in base 2
TEST_F(ParseUnsignedShortTest_278, RadixMatters_278) {
  const char* s = "10";
  unsigned short out = 0;
  ASSERT_TRUE(Parse(s, 2, &out, 2));
  EXPECT_EQ(out, static_cast<unsigned short>(2));
}
