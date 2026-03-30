// File: parse_short_test_277.cc
#include <gtest/gtest.h>
#include <string>

// We only declare the function we are testing; the definition is provided by the production code.
namespace re2 { namespace re2_internal {
bool Parse(const char* str, size_t n, short* dest, int radix);
}}  // namespace re2::re2_internal

using re2::re2_internal::Parse;

class ParseShortTest_277 : public ::testing::Test {
protected:
  // Small helper to call the API with std::string.
  static bool Call(const std::string& s, short* out, int radix = 10) {
    return Parse(s.data(), s.size(), out, radix);
  }
  static bool CallWithLen(const std::string& s, size_t n, short* out, int radix = 10) {
    return Parse(s.data(), n, out, radix);
  }
};

// ---------- Normal operation ----------

TEST(ParseShortTest_277, ValidDecimalWithinRange_277) {
  short v = 0;
  ASSERT_TRUE(Call("12345", &v));           // observable: returns true
  EXPECT_EQ(12345, v);                      // observable: writes parsed value
}

TEST(ParseShortTest_277, NegativeWithinRange_277) {
  short v = 0;
  ASSERT_TRUE(Call("-123", &v));
  EXPECT_EQ(-123, v);
}

TEST(ParseShortTest_277, ValidHexWithRadix16_277) {
  short v = 0;
  ASSERT_TRUE(Call("7F", &v, /*radix=*/16));
  EXPECT_EQ(127, v);
}

// Using 'n' shorter than the buffer should consider only the first n chars.
TEST(ParseShortTest_277, IgnoresTrailingCharsBeyondN_277) {
  short v = 0;
  const std::string s = "123garbage";
  ASSERT_TRUE(CallWithLen(s, /*n=*/3, &v));
  EXPECT_EQ(123, v);
}

// ---------- Boundary conditions ----------

TEST(ParseShortTest_277, MaxShortBoundary_277) {
  short v = 0;
  ASSERT_TRUE(Call("32767", &v));  // SHRT_MAX
  EXPECT_EQ(32767, v);
}

TEST(ParseShortTest_277, MinShortBoundary_277) {
  short v = 1;
  ASSERT_TRUE(Call("-32768", &v)); // SHRT_MIN
  EXPECT_EQ(-32768, v);
}

TEST(ParseShortTest_277, AboveMaxShortIsOutOfRange_277) {
  short v = 0;
  EXPECT_FALSE(Call("32768", &v)); // Out of range must be observable as false
}

TEST(ParseShortTest_277, BelowMinShortIsOutOfRange_277) {
  short v = 0;
  EXPECT_FALSE(Call("-32769", &v)); // Out of range must be observable as false
}

TEST(ParseShortTest_277, HexValueOutOfRange_277) {
  short v = 0;
  // 0x8000 == 32768 (one more than SHRT_MAX for positive parsing), should be out of range
  EXPECT_FALSE(Call("8000", &v, /*radix=*/16));
}

// ---------- Exceptional / error cases ----------

TEST(ParseShortTest_277, InvalidStringReturnsFalse_277) {
  short v = 0;
  EXPECT_FALSE(Call("xyz", &v));
}

TEST(ParseShortTest_277, EmptyInputReturnsFalse_277) {
  short v = 0;
  EXPECT_FALSE(Call("", &v));
}

TEST(ParseShortTest_277, NullDestActsAsValidationOnly_Valid_277) {
  // When dest == NULL, success should still be reported (no write to observe).
  EXPECT_TRUE(Parse("42", /*n=*/2, /*dest=*/nullptr, /*radix=*/10));
}

TEST(ParseShortTest_277, NullDestActsAsValidationOnly_OutOfRange_277) {
  // Out-of-range should still be reported as failure even when dest == NULL.
  EXPECT_FALSE(Parse("32768", /*n=*/5, /*dest=*/nullptr, /*radix=*/10));
}

TEST(ParseShortTest_277, NullDestActsAsValidationOnly_Invalid_277) {
  EXPECT_FALSE(Parse("oops", /*n=*/4, /*dest=*/nullptr, /*radix=*/10));
}
