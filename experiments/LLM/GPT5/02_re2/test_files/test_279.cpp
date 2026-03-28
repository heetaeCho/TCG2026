// File: parse_int_tests_279.cc
#include <gtest/gtest.h>
#include <climits>
#include <cstddef>

namespace re2 {
namespace re2_internal {
// Forward declaration of the function under test (already implemented elsewhere).
bool Parse(const char* str, size_t n, int* dest, int radix);
}  // namespace re2_internal
}  // namespace re2

using re2::re2_internal::Parse;

// Fixture (kept minimal since there’s no shared state to set up/tear down).
class ParseIntTest_279 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(ParseIntTest_279, ParsesDecimalWithinRange_279) {
  int out = 0;
  const char* s = "12345";
  ASSERT_TRUE(Parse(s, 5, &out, 10));
  EXPECT_EQ(out, 12345);
}

TEST_F(ParseIntTest_279, ParsesNegativeDecimalWithinRange_279) {
  int out = 0;
  const char* s = "-42";
  ASSERT_TRUE(Parse(s, 3, &out, 10));
  EXPECT_EQ(out, -42);
}

TEST_F(ParseIntTest_279, ParsesHexWithinRange_279) {
  int out = 0;
  const char* s = "FF";
  ASSERT_TRUE(Parse(s, 2, &out, 16));
  EXPECT_EQ(out, 255);
}

// --- Boundary conditions ---

TEST_F(ParseIntTest_279, ParsesIntMaxBoundaryDecimal_279) {
  int out = 0;
  const char* s = "2147483647";  // INT_MAX in decimal
  ASSERT_TRUE(Parse(s, 10, &out, 10));
  EXPECT_EQ(out, INT_MAX);
}

TEST_F(ParseIntTest_279, ParsesIntMinBoundaryDecimal_279) {
  int out = 0;
  const char* s = "-2147483648";  // INT_MIN in decimal
  ASSERT_TRUE(Parse(s, 11, &out, 10));
  EXPECT_EQ(out, INT_MIN);
}

TEST_F(ParseIntTest_279, FailsOnOverflowDecimal_279) {
  // One above INT_MAX
  int out = 0xdeadbeef;
  const char* s = "2147483648";
  EXPECT_FALSE(Parse(s, 10, &out, 10));
  // Output is unspecified on failure; we do NOT assert on 'out'.
}

TEST_F(ParseIntTest_279, FailsOnUnderflowDecimal_279) {
  // One below INT_MIN
  int out = 0xdeadbeef;
  const char* s = "-2147483649";
  EXPECT_FALSE(Parse(s, 11, &out, 10));
  // Output is unspecified on failure; do not check 'out'.
}

TEST_F(ParseIntTest_279, HexMaxBoundaryAndOverflow_279) {
  // INT_MAX in hex and one above
  int out = 0;
  const char* max_hex = "7fffffff";
  ASSERT_TRUE(Parse(max_hex, 8, &out, 16));
  EXPECT_EQ(out, INT_MAX);

  const char* overflow_hex = "80000000";
  EXPECT_FALSE(Parse(overflow_hex, 8, &out, 16));
}

// --- Length handling via 'n' ---

TEST_F(ParseIntTest_279, RespectsLengthParameter_DropsSuffix_279) {
  // Only the first 3 characters are considered.
  int out = 0;
  const char* s = "123abc";
  ASSERT_TRUE(Parse(s, 3, &out, 10));
  EXPECT_EQ(out, 123);
}

TEST_F(ParseIntTest_279, RespectsLengthParameter_FailsWhenIncludingNonDigits_279) {
  int out = 0x1234;
  const char* s = "123abc";
  EXPECT_FALSE(Parse(s, 6, &out, 10));
}

// --- Null destination handling ---

TEST_F(ParseIntTest_279, ReturnsTrueWithNullDestOnSuccess_279) {
  // When dest == nullptr and parsing succeeds & is in-range, return true.
  const char* s = "456";
  EXPECT_TRUE(Parse(s, 3, /*dest=*/nullptr, 10));
}

TEST_F(ParseIntTest_279, ReturnsFalseWithNullDestOnFailure_279) {
  const char* s = "not-a-number";
  EXPECT_FALSE(Parse(s, 12, /*dest=*/nullptr, 10));
}

// --- Parse failures ---

TEST_F(ParseIntTest_279, FailsOnNonNumericInput_279) {
  int out = 0x7f;
  const char* s = "abc";
  EXPECT_FALSE(Parse(s, 3, &out, 10));
}

