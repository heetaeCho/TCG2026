// File: re2_parse_ll_tests_281.cc
#include <gtest/gtest.h>
#include <climits>
#include <cstring>

namespace re2 { namespace re2_internal {
  // Bring the specialization into scope for tests.
  template <> bool Parse(const char* str, size_t n, long long* dest, int radix);
}}

using re2::re2_internal::Parse;

// --- Normal operation ---

TEST(ParseTest_281, DecimalSuccess_SetsDest_281) {
  const char* s = "123";
  long long out = -1;
  ASSERT_TRUE(Parse(s, std::strlen(s), &out, 10));
  EXPECT_EQ(out, 123);
}

TEST(ParseTest_281, NegativeDecimal_SetsDest_281) {
  const char* s = "-7";
  long long out = 0;
  ASSERT_TRUE(Parse(s, std::strlen(s), &out, 10));
  EXPECT_EQ(out, -7);
}

TEST(ParseTest_281, Hexadecimal_Radix16_SetsDest_281) {
  const char* s = "ff";
  long long out = 0;
  ASSERT_TRUE(Parse(s, std::strlen(s), &out, 16));
  EXPECT_EQ(out, 255);
}

// Parse only the first n characters even if the buffer is longer.
TEST(ParseTest_281, ParsesOnlyFirstNBytes_WhenNShorterThanString_281) {
  const char* s = "12345";
  long long out = 0;
  ASSERT_TRUE(Parse(s, /*n=*/3, &out, 10));
  EXPECT_EQ(out, 123);
}

// --- Boundary conditions ---

TEST(ParseTest_281, EmptyInput_ReturnsFalse_281) {
  const char* s = "";
  long long out = 42;  // should remain unchanged on failure
  EXPECT_FALSE(Parse(s, /*n=*/0, &out, 10));
  EXPECT_EQ(out, 42);
}

// Trailing space is leftover junk relative to n bytes.
TEST(ParseTest_281, TrailingWhitespace_IsLeftoverJunk_ReturnsFalse_281) {
  const char* s = "123 ";
  long long out = -1;
  EXPECT_FALSE(Parse(s, std::strlen(s), &out, 10));
  EXPECT_EQ(out, -1);
}

// Any non-digit junk within the n-byte window should fail.
TEST(ParseTest_281, LeftoverJunkInsideWindow_ReturnsFalse_281) {
  const char* s = "12x";
  long long out = 777;
  EXPECT_FALSE(Parse(s, std::strlen(s), &out, 10));
  EXPECT_EQ(out, 777);
}

// --- Exceptional / error cases ---

// Overflow should cause strtoll to set errno and Parse to return false.
TEST(ParseTest_281, OverflowDecimal_ReturnsFalse_281) {
  // One greater than LLONG_MAX in base 10
  const char* s = "9223372036854775808";
  long long out = 5;
  EXPECT_FALSE(Parse(s, std::strlen(s), &out, 10));
  EXPECT_EQ(out, 5);
}

// --- External interaction surface: dest may be null ---

TEST(ParseTest_281, NullDestination_StillParsesAndReturnsTrue_281) {
  const char* s = "42";
  // Should succeed without writing through dest.
  EXPECT_TRUE(Parse(s, std::strlen(s), /*dest=*/nullptr, /*radix=*/10));
}
