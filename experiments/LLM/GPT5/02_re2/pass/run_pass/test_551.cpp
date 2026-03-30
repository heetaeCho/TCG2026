// File: ./TestProjects/re2/re2/tests/rune_to_string_latin1_test_551.cc

#include <gtest/gtest.h>
#include <string>

// Include the implementation directly so the symbol is visible in this TU.
// (If a header exists in your tree, prefer including that instead.)
#include "re2/prefilter.cc"

using re2::RuneToStringLatin1;

namespace {

// Normal operation: ASCII input should round-trip to a single-byte string.
TEST(RuneToStringLatin1Test_551, ReturnsSingleByteForAscii_551) {
  std::string s = RuneToStringLatin1(static_cast<int>('A'));
  ASSERT_EQ(s.size(), 1u);
  EXPECT_EQ(s[0], 'A');
}

// Boundary: NUL (0) should produce a single-byte string containing 0.
TEST(RuneToStringLatin1Test_551, ReturnsSingleByteForNull_551) {
  std::string s = RuneToStringLatin1(0);
  ASSERT_EQ(s.size(), 1u);
  EXPECT_EQ(static_cast<unsigned char>(s[0]), 0u);
}

// Boundary: Highest Latin-1 value (255) should be represented as one byte.
TEST(RuneToStringLatin1Test_551, ReturnsSingleByteForMaxLatin1_551) {
  std::string s = RuneToStringLatin1(255);
  ASSERT_EQ(s.size(), 1u);
  EXPECT_EQ(static_cast<unsigned char>(s[0]), 255u);
}

// Normal operation: Extended Latin-1 (e.g., Ç = 199) should be one byte.
TEST(RuneToStringLatin1Test_551, ReturnsSingleByteForExtendedLatin1_551) {
  std::string s = RuneToStringLatin1(199);  // 'Ç' in Latin-1
  ASSERT_EQ(s.size(), 1u);
  EXPECT_EQ(static_cast<unsigned char>(s[0]), 199u);
}

// Exceptional/edge (out-of-range): Large positive value still yields a single byte.
// We only assert observable size here, not internal mapping behavior.
TEST(RuneToStringLatin1Test_551, LargeValueStillSingleByte_551) {
  std::string s = RuneToStringLatin1(0x1F600);  // 😀 code point value
  EXPECT_EQ(s.size(), 1u);
}

// Exceptional/edge: Negative input still yields a single byte (observable behavior).
TEST(RuneToStringLatin1Test_551, NegativeValueStillSingleByte_551) {
  std::string s = RuneToStringLatin1(-1);
  EXPECT_EQ(s.size(), 1u);
}

}  // namespace
