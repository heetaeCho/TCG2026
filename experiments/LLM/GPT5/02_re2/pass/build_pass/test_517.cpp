// File: re2_ishex_test_517.cc
#include <gtest/gtest.h>

// Include the actual implementation so the internal-linkage function is available
// Adjust the path as needed for your project layout.
#include "../TestProjects/re2/re2/parse.cc"

namespace {

using re2::IsHex;

TEST(IsHexTest_517, AcceptsDigits_517) {
  for (int c = '0'; c <= '9'; ++c) {
    EXPECT_TRUE(IsHex(c)) << "Expected digit to be hex: char(" << static_cast<char>(c) << ")";
  }
}

TEST(IsHexTest_517, AcceptsUppercaseHex_517) {
  for (int c = 'A'; c <= 'F'; ++c) {
    EXPECT_TRUE(IsHex(c)) << "Expected uppercase hex to be accepted: " << static_cast<char>(c);
  }
}

TEST(IsHexTest_517, AcceptsLowercaseHex_517) {
  for (int c = 'a'; c <= 'f'; ++c) {
    EXPECT_TRUE(IsHex(c)) << "Expected lowercase hex to be accepted: " << static_cast<char>(c);
  }
}

TEST(IsHexTest_517, RejectsNearbyNonHexBoundaries_517) {
  // Just below/above each valid range
  EXPECT_FALSE(IsHex('/')) << "Slash '/' should not be hex";
  EXPECT_TRUE(IsHex('0'));
  EXPECT_TRUE(IsHex('9'));
  EXPECT_FALSE(IsHex(':')) << "Colon ':' should not be hex";

  EXPECT_FALSE(IsHex('@')) << "'@' should not be hex";
  EXPECT_TRUE(IsHex('A'));
  EXPECT_TRUE(IsHex('F'));
  EXPECT_FALSE(IsHex('G')) << "'G' should not be hex";

  EXPECT_FALSE(IsHex('`')) << "'`' should not be hex";
  EXPECT_TRUE(IsHex('a'));
  EXPECT_TRUE(IsHex('f'));
  EXPECT_FALSE(IsHex('g')) << "'g' should not be hex";
}

TEST(IsHexTest_517, RejectsClearNonHexCharacters_517) {
  const char* non_hex = "xzZ! \n\t/";
  for (const char* p = non_hex; *p; ++p) {
    EXPECT_FALSE(IsHex(static_cast<unsigned char>(*p))) << "Unexpectedly accepted: " << *p;
  }
}

TEST(IsHexTest_517, HandlesNonAsciiAndNegativeInputs_517) {
  EXPECT_FALSE(IsHex(-1)) << "Negative codepoint should not be hex";
  EXPECT_FALSE(IsHex(0x0100)) << "Non-ASCII 256 should not be hex";
  EXPECT_FALSE(IsHex(0x00E9)) << "Non-ASCII 'é' (233) should not be hex";
}

}  // namespace
