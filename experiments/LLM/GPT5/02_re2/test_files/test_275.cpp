// File: re2_parse_long_test_275.cc
#include <gtest/gtest.h>
#include <limits>
#include <string>

#include "re2/re2.h"          // if present in your tree; otherwise include the header that declares Parse
// If Parse is only available via a specific internal header, include that instead.
// The tests only rely on the exposed signature & observable behavior.

namespace {

using re2::re2_internal::Parse;

TEST(ParseLong_275, ReturnsFalseOnEmptyInput_275) {
  long out = 0;
  const char* s = "";
  EXPECT_FALSE(Parse(s, /*n=*/0, &out, /*radix=*/10));
}

TEST(ParseLong_275, ParsesDecimalPositive_275) {
  long out = 0;
  const std::string s = "12345";
  ASSERT_TRUE(Parse(s.c_str(), s.size(), &out, 10));
  EXPECT_EQ(out, 12345L);
}

TEST(ParseLong_275, ParsesNegative_275) {
  long out = 0;
  const std::string s = "-42";
  ASSERT_TRUE(Parse(s.c_str(), s.size(), &out, 10));
  EXPECT_EQ(out, -42L);
}

TEST(ParseLong_275, ParsesWithDestNull_275) {
  // Valid parse should succeed even when dest == nullptr.
  const std::string s = "777";
  ASSERT_TRUE(Parse(s.c_str(), s.size(), /*dest=*/nullptr, 10));
}

TEST(ParseLong_275, FailsOnTrailingJunk_275) {
  long out = 0;
  const std::string s = "123x";
  EXPECT_FALSE(Parse(s.c_str(), s.size(), &out, 10));
}

TEST(ParseLong_275, SucceedsWhenLengthCoversOnlyNumber_275) {
  long out = 0;
  const std::string s = "123x";
  // Only pass the numeric prefix via n; should succeed and consume exactly n chars.
  ASSERT_TRUE(Parse(s.c_str(), /*n=*/3, &out, 10));
  EXPECT_EQ(out, 123L);
}

TEST(ParseLong_275, ParsesHexWithRadix16_275) {
  long out = 0;
  const std::string s = "1f";
  ASSERT_TRUE(Parse(s.c_str(), s.size(), &out, 16));
  EXPECT_EQ(out, 31L);
}

TEST(ParseLong_275, AutoDetectRadix0WithPrefix_275) {
  long out = 0;
  const std::string s = "0x10";  // With base 0, strtol should honor the 0x prefix.
  ASSERT_TRUE(Parse(s.c_str(), s.size(), &out, 0));
  EXPECT_EQ(out, 16L);
}

TEST(ParseLong_275, LeadingSpacesAllowed_275) {
  long out = 0;
  const std::string s = "   256";
  ASSERT_TRUE(Parse(s.c_str(), s.size(), &out, 10));
  EXPECT_EQ(out, 256L);
}

TEST(ParseLong_275, OverflowReturnsFalse_275) {
  long out = 0;
  // Construct a clearly too-large decimal number to trigger ERANGE in strtol.
  // Using many digits avoids depending on exact LONG_MAX width.
  std::string huge(100, '9');  // "9999..."; far exceeds any reasonable long range in base 10
  EXPECT_FALSE(Parse(huge.c_str(), huge.size(), &out, 10));
}

}  // namespace
