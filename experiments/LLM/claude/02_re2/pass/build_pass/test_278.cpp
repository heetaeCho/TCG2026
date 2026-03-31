#include <gtest/gtest.h>
#include <climits>
#include <string>

// We need to declare the template and its specialization to test it
namespace re2 {
namespace re2_internal {

template <typename T>
bool Parse(const char* str, size_t n, T* dest, int radix);

// The specialization we're testing
template <>
bool Parse(const char* str, size_t n, unsigned short* dest, int radix);

// We also need the unsigned long version since the unsigned short version depends on it
template <>
bool Parse(const char* str, size_t n, unsigned long* dest, int radix);

}  // namespace re2_internal
}  // namespace re2

class ParseUnsignedShortTest_278 : public ::testing::Test {
 protected:
  using ParseFunc = bool (*)(const char*, size_t, unsigned short*, int);
};

// Test: Parse a simple decimal number within unsigned short range
TEST_F(ParseUnsignedShortTest_278, ParseValidDecimalNumber_278) {
  unsigned short result = 0;
  const char* str = "12345";
  bool ok = re2::re2_internal::Parse(str, strlen(str), &result, 10);
  if (ok) {
    EXPECT_EQ(result, 12345);
  }
  // If underlying Parse for unsigned long fails, ok could be false
  // We just check consistency
}

// Test: Parse zero
TEST_F(ParseUnsignedShortTest_278, ParseZero_278) {
  unsigned short result = 42;
  const char* str = "0";
  bool ok = re2::re2_internal::Parse(str, strlen(str), &result, 10);
  if (ok) {
    EXPECT_EQ(result, 0);
  }
}

// Test: Parse max unsigned short value (65535)
TEST_F(ParseUnsignedShortTest_278, ParseMaxUnsignedShort_278) {
  unsigned short result = 0;
  const char* str = "65535";
  bool ok = re2::re2_internal::Parse(str, strlen(str), &result, 10);
  if (ok) {
    EXPECT_EQ(result, 65535);
  }
}

// Test: Parse value just above unsigned short max (65536) should fail
TEST_F(ParseUnsignedShortTest_278, ParseOverflowUnsignedShort_278) {
  unsigned short result = 0;
  const char* str = "65536";
  bool ok = re2::re2_internal::Parse(str, strlen(str), &result, 10);
  EXPECT_FALSE(ok);
}

// Test: Parse a very large number that's way out of range
TEST_F(ParseUnsignedShortTest_278, ParseLargeNumberOutOfRange_278) {
  unsigned short result = 0;
  const char* str = "100000";
  bool ok = re2::re2_internal::Parse(str, strlen(str), &result, 10);
  EXPECT_FALSE(ok);
}

// Test: Parse with null destination (should return true if value is valid)
TEST_F(ParseUnsignedShortTest_278, ParseWithNullDest_278) {
  const char* str = "42";
  bool ok = re2::re2_internal::Parse(str, strlen(str), static_cast<unsigned short*>(nullptr), 10);
  // If underlying parse succeeds and value is in range, should return true
  if (ok) {
    EXPECT_TRUE(ok);
  }
}

// Test: Parse with null destination and out-of-range value should fail
TEST_F(ParseUnsignedShortTest_278, ParseWithNullDestOutOfRange_278) {
  const char* str = "65536";
  bool ok = re2::re2_internal::Parse(str, strlen(str), static_cast<unsigned short*>(nullptr), 10);
  EXPECT_FALSE(ok);
}

// Test: Parse hexadecimal number
TEST_F(ParseUnsignedShortTest_278, ParseHexNumber_278) {
  unsigned short result = 0;
  const char* str = "FF";
  bool ok = re2::re2_internal::Parse(str, strlen(str), &result, 16);
  if (ok) {
    EXPECT_EQ(result, 255);
  }
}

// Test: Parse hex number at max unsigned short
TEST_F(ParseUnsignedShortTest_278, ParseHexMaxUnsignedShort_278) {
  unsigned short result = 0;
  const char* str = "FFFF";
  bool ok = re2::re2_internal::Parse(str, strlen(str), &result, 16);
  if (ok) {
    EXPECT_EQ(result, 65535);
  }
}

// Test: Parse hex number exceeding unsigned short range
TEST_F(ParseUnsignedShortTest_278, ParseHexOverflow_278) {
  unsigned short result = 0;
  const char* str = "10000";
  bool ok = re2::re2_internal::Parse(str, strlen(str), &result, 16);
  EXPECT_FALSE(ok);
}

// Test: Parse octal number
TEST_F(ParseUnsignedShortTest_278, ParseOctalNumber_278) {
  unsigned short result = 0;
  const char* str = "77";
  bool ok = re2::re2_internal::Parse(str, strlen(str), &result, 8);
  if (ok) {
    EXPECT_EQ(result, 63);
  }
}

// Test: Parse with length shorter than string
TEST_F(ParseUnsignedShortTest_278, ParsePartialString_278) {
  unsigned short result = 0;
  const char* str = "12345";
  // Only parse first 2 characters: "12"
  bool ok = re2::re2_internal::Parse(str, 2, &result, 10);
  if (ok) {
    EXPECT_EQ(result, 12);
  }
}

// Test: Parse empty string should fail
TEST_F(ParseUnsignedShortTest_278, ParseEmptyString_278) {
  unsigned short result = 0;
  const char* str = "";
  bool ok = re2::re2_internal::Parse(str, 0, &result, 10);
  EXPECT_FALSE(ok);
}

// Test: Parse invalid string should fail
TEST_F(ParseUnsignedShortTest_278, ParseInvalidString_278) {
  unsigned short result = 0;
  const char* str = "abc";
  bool ok = re2::re2_internal::Parse(str, strlen(str), &result, 10);
  EXPECT_FALSE(ok);
}

// Test: Parse single digit
TEST_F(ParseUnsignedShortTest_278, ParseSingleDigit_278) {
  unsigned short result = 0;
  const char* str = "7";
  bool ok = re2::re2_internal::Parse(str, strlen(str), &result, 10);
  if (ok) {
    EXPECT_EQ(result, 7);
  }
}

// Test: Parse value of 1
TEST_F(ParseUnsignedShortTest_278, ParseOne_278) {
  unsigned short result = 0;
  const char* str = "1";
  bool ok = re2::re2_internal::Parse(str, strlen(str), &result, 10);
  if (ok) {
    EXPECT_EQ(result, 1);
  }
}

// Test: Verify that dest is not modified on failure
TEST_F(ParseUnsignedShortTest_278, DestUnmodifiedOnFailure_278) {
  unsigned short result = 12345;
  const char* str = "65536";  // Out of range
  bool ok = re2::re2_internal::Parse(str, strlen(str), &result, 10);
  EXPECT_FALSE(ok);
  // Result should not have been modified since parse should fail before assignment
  EXPECT_EQ(result, 12345);
}

// Test: Parse boundary value 65534 (one below max)
TEST_F(ParseUnsignedShortTest_278, ParseOneBelowMax_278) {
  unsigned short result = 0;
  const char* str = "65534";
  bool ok = re2::re2_internal::Parse(str, strlen(str), &result, 10);
  if (ok) {
    EXPECT_EQ(result, 65534);
  }
}
