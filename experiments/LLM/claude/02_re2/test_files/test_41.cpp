#include <gtest/gtest.h>
#include <string>
#include <cstdint>
#include "re2/re2.h"

namespace re2 {
namespace re2_internal {

// Test Parse with absl::optional<int> destination
class ParseOptionalTest_41 : public ::testing::Test {
protected:
};

// Test: Null string with non-null destination resets optional
TEST_F(ParseOptionalTest_41, NullStringResetsOptional_41) {
  absl::optional<int> dest = 42;
  bool result = Parse<int>(nullptr, 0, &dest, 10);
  EXPECT_TRUE(result);
  EXPECT_FALSE(dest.has_value());
}

// Test: Null string with null destination returns true
TEST_F(ParseOptionalTest_41, NullStringNullDestReturnsTrue_41) {
  bool result = Parse<int>(nullptr, 0, static_cast<absl::optional<int>*>(nullptr), 10);
  EXPECT_TRUE(result);
}

// Test: Valid integer string parses correctly into optional
TEST_F(ParseOptionalTest_41, ValidIntStringParsesIntoOptional_41) {
  absl::optional<int> dest;
  const char* str = "123";
  bool result = Parse<int>(str, 3, &dest, 10);
  EXPECT_TRUE(result);
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest.value(), 123);
}

// Test: Valid integer string with null optional destination still returns true
TEST_F(ParseOptionalTest_41, ValidIntStringNullOptionalDest_41) {
  const char* str = "456";
  bool result = Parse<int>(str, 3, static_cast<absl::optional<int>*>(nullptr), 10);
  EXPECT_TRUE(result);
}

// Test: Invalid string fails to parse
TEST_F(ParseOptionalTest_41, InvalidStringFailsToParse_41) {
  absl::optional<int> dest;
  const char* str = "abc";
  bool result = Parse<int>(str, 3, &dest, 10);
  EXPECT_FALSE(result);
  EXPECT_FALSE(dest.has_value());
}

// Test: Hex radix parsing
TEST_F(ParseOptionalTest_41, HexRadixParsing_41) {
  absl::optional<int> dest;
  const char* str = "ff";
  bool result = Parse<int>(str, 2, &dest, 16);
  EXPECT_TRUE(result);
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest.value(), 255);
}

// Test: Negative number parsing
TEST_F(ParseOptionalTest_41, NegativeNumberParsing_41) {
  absl::optional<int> dest;
  const char* str = "-42";
  bool result = Parse<int>(str, 3, &dest, 10);
  EXPECT_TRUE(result);
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest.value(), -42);
}

// Test: Zero length string
TEST_F(ParseOptionalTest_41, ZeroLengthString_41) {
  absl::optional<int> dest;
  const char* str = "123";
  bool result = Parse<int>(str, 0, &dest, 10);
  // Empty string likely fails to parse as int
  EXPECT_FALSE(result);
}

// Test: Partial string parsing (length < actual string length)
TEST_F(ParseOptionalTest_41, PartialStringParsing_41) {
  absl::optional<int> dest;
  const char* str = "12345";
  bool result = Parse<int>(str, 3, &dest, 10);
  EXPECT_TRUE(result);
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest.value(), 123);
}

// Test: Parse with optional<long long>
TEST_F(ParseOptionalTest_41, ParseLongLong_41) {
  absl::optional<long long> dest;
  const char* str = "9999999999";
  bool result = Parse<long long>(str, 10, &dest, 10);
  EXPECT_TRUE(result);
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest.value(), 9999999999LL);
}

// Test: String with leading whitespace may fail
TEST_F(ParseOptionalTest_41, LeadingWhitespace_41) {
  absl::optional<int> dest;
  const char* str = " 42";
  bool result = Parse<int>(str, 3, &dest, 10);
  // Leading whitespace typically causes parse failure
  EXPECT_FALSE(result);
}

// Test: Null string with already-empty optional
TEST_F(ParseOptionalTest_41, NullStringAlreadyEmptyOptional_41) {
  absl::optional<int> dest;
  EXPECT_FALSE(dest.has_value());
  bool result = Parse<int>(nullptr, 0, &dest, 10);
  EXPECT_TRUE(result);
  EXPECT_FALSE(dest.has_value());
}

// Test: Parse unsigned int
TEST_F(ParseOptionalTest_41, ParseUnsignedInt_41) {
  absl::optional<unsigned int> dest;
  const char* str = "4294967295";
  bool result = Parse<unsigned int>(str, 10, &dest, 10);
  EXPECT_TRUE(result);
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest.value(), 4294967295U);
}

// Test: Overflow for int
TEST_F(ParseOptionalTest_41, OverflowForInt_41) {
  absl::optional<int> dest;
  const char* str = "99999999999999999999";
  bool result = Parse<int>(str, 20, &dest, 10);
  EXPECT_FALSE(result);
  EXPECT_FALSE(dest.has_value());
}

}  // namespace re2_internal
}  // namespace re2
