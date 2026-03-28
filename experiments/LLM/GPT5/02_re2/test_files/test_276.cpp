// File: parse_unsigned_long_parse_tests_276.cc

#include <gtest/gtest.h>
#include <limits>
#include <cstring>

// Forward declaration of the function under test (already implemented elsewhere).
namespace re2 {
namespace re2_internal {
bool Parse(const char* str, size_t n, unsigned long* dest, int radix);
}  // namespace re2_internal
}  // namespace re2

using re2::re2_internal::Parse;

namespace {

//---------------- Normal operation ----------------//

TEST(ParseUnsignedLongTest_276, ParsesDecimalNumber_276) {
  const char* s = "12345";
  unsigned long out = 0;
  ASSERT_TRUE(Parse(s, 5, &out, 10));
  EXPECT_EQ(out, 12345ul);
}

TEST(ParseUnsignedLongTest_276, ParsesHexWithExplicitRadix16_276) {
  const char* s = "ff";
  unsigned long out = 0;
  ASSERT_TRUE(Parse(s, 2, &out, 16));
  EXPECT_EQ(out, 255ul);
}

TEST(ParseUnsignedLongTest_276, ParsesPrefixOfLongerBufferUsingN_276) {
  const char* s = "12345junk";
  unsigned long out = 0;
  ASSERT_TRUE(Parse(s, 5, &out, 10));  // only first 5 chars considered
  EXPECT_EQ(out, 12345ul);
}

TEST(ParseUnsignedLongTest_276, ReturnsTrueWithNullDestOnSuccess_276) {
  const char* s = "42";
  // Should not crash and should report success even with dest == nullptr.
  EXPECT_TRUE(Parse(s, 2, /*dest=*/nullptr, 10));
}

//---------------- Boundary conditions ----------------//

TEST(ParseUnsignedLongTest_276, ZeroLengthInputReturnsFalse_276) {
  const char* s = "";
  unsigned long out = 777ul;  // sentinel
  EXPECT_FALSE(Parse(s, 0, &out, 10));
  // No guarantee about dest on failure; ensure it wasn't changed by success path.
  EXPECT_EQ(out, 777ul);
}

TEST(ParseUnsignedLongTest_276, LeadingMinusIsRejected_276) {
  const char* s = "-1";
  unsigned long out = 999ul;  // sentinel
  EXPECT_FALSE(Parse(s, 2, &out, 10));
  EXPECT_EQ(out, 999ul);
}

//---------------- Error/exceptional cases (observable) ----------------//

TEST(ParseUnsignedLongTest_276, LeftoverJunkCausesFailure_276) {
  const char* s = "12x";
  unsigned long out = 111ul;  // sentinel
  EXPECT_FALSE(Parse(s, 3, &out, 10));  // non-digit in base 10
  EXPECT_EQ(out, 111ul);
}

TEST(ParseUnsignedLongTest_276, OverflowSetsErrnoAndCausesFailure_276) {
  // A far-too-large number for any typical unsigned long width.
  // Using many digits to reliably overflow across platforms.
  const char* s = "99999999999999999999999999999999999999999999";
  const size_t n = std::strlen(s);
  unsigned long out = 222ul;  // sentinel
  EXPECT_FALSE(Parse(s, n, &out, 10));
  EXPECT_EQ(out, 222ul);
}

}  // namespace
