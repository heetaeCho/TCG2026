// File: parse_ull_tests_282.cc
#include <gtest/gtest.h>
#include <climits>
#include <cstddef>

// Forward declare just the tested interface (no internal details).
namespace re2 {
namespace re2_internal {
bool Parse(const char* str, size_t n, unsigned long long* dest, int radix);
}  // namespace re2_internal
}  // namespace re2

using re2::re2_internal::Parse;

// -------------------------------
// Normal operation
// -------------------------------

TEST(ParseUnsignedLongLong_282, ValidDecimal_SetsValueAndReturnsTrue_282) {
  const char* s = "12345";
  unsigned long long out = 0;
  EXPECT_TRUE(Parse(s, 5, &out, 10));
  EXPECT_EQ(out, 12345ULL);
}

TEST(ParseUnsignedLongLong_282, NShorterThanString_ParsesExactPrefix_282) {
  const char* s = "12345";
  unsigned long long out = 0;
  // Ask to parse only the first 3 characters: "123"
  EXPECT_TRUE(Parse(s, 3, &out, 10));
  EXPECT_EQ(out, 123ULL);
}

TEST(ParseUnsignedLongLong_282, ValidHexBase16_SetsValueAndReturnsTrue_282) {
  const char* s = "ff";
  unsigned long long out = 0;
  EXPECT_TRUE(Parse(s, 2, &out, 16));
  EXPECT_EQ(out, 255ULL);
}

TEST(ParseUnsignedLongLong_282, AutoDetectBase0_With0xPrefix_ParsesHex_282) {
  const char* s = "0x10";
  unsigned long long out = 0;
  // radix 0 allows auto-detection (e.g., 0x for hex)
  EXPECT_TRUE(Parse(s, 4, &out, 0));
  EXPECT_EQ(out, 16ULL);
}

// -------------------------------
// Boundary conditions
// -------------------------------

TEST(ParseUnsignedLongLong_282, EmptyInput_ReturnsFalse_282) {
  const char* s = "";
  unsigned long long out = 123ULL;  // should remain unchanged if function fails
  EXPECT_FALSE(Parse(s, 0, &out, 10));
}

TEST(ParseUnsignedLongLong_282, NegativeSignIsRejected_ReturnsFalse_282) {
  const char* s = "-1";
  unsigned long long out = 0;
  EXPECT_FALSE(Parse(s, 2, &out, 10));
}

TEST(ParseUnsignedLongLong_282, MaxUnsignedLongLong_Succeeds_282) {
  // ULLONG_MAX in base 10 for 64-bit platforms is 18446744073709551615
  const char* s = "18446744073709551615";
  unsigned long long out = 0;
  EXPECT_TRUE(Parse(s, 20, &out, 10));
  EXPECT_EQ(out, ULLONG_MAX);
}

// -------------------------------
// Error / exceptional cases (observable)
// -------------------------------

TEST(ParseUnsignedLongLong_282, LeftoverJunkCausesFailure_282) {
  const char* s = "123abc";  // trailing junk
  unsigned long long out = 0;
  EXPECT_FALSE(Parse(s, 6, &out, 10));
}

TEST(ParseUnsignedLongLong_282, InvalidDigitForRadixCausesFailure_282) {
  const char* s = "2";  // invalid in base 2
  unsigned long long out = 0;
  EXPECT_FALSE(Parse(s, 1, &out, 2));
}

TEST(ParseUnsignedLongLong_282, OverflowReturnsFalse_282) {
  // One more than ULLONG_MAX in base 10: 18446744073709551616
  const char* s = "18446744073709551616";
  unsigned long long out = 0;
  EXPECT_FALSE(Parse(s, 20, &out, 10));
}

TEST(ParseUnsignedLongLong_282, DestNullOnSuccess_ReturnsTrue_282) {
  const char* s = "42";
  // When dest == nullptr, success should still return true (no write observable)
  EXPECT_TRUE(Parse(s, 2, /*dest=*/nullptr, 10));
}
