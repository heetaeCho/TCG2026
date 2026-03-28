#include <gtest/gtest.h>
#include <string>
#include <cstddef>
#include "re2/re2.h"

namespace re2 {
namespace re2_internal {

// Test parsing with null string and non-null dest resets the optional
TEST(ParseOptionalTest_40, NullStrResetsOptional_40) {
  absl::optional<int> dest(42);
  bool result = Parse<int>(nullptr, 0, &dest);
  EXPECT_TRUE(result);
  EXPECT_FALSE(dest.has_value());
}

// Test parsing with null string and null dest returns true
TEST(ParseOptionalTest_40, NullStrNullDestReturnsTrue_40) {
  bool result = Parse<int>(nullptr, 0, static_cast<absl::optional<int>*>(nullptr));
  EXPECT_TRUE(result);
}

// Test parsing a valid integer string into an optional<int>
TEST(ParseOptionalTest_40, ValidIntStringParsesSuccessfully_40) {
  absl::optional<int> dest;
  const char* str = "123";
  bool result = Parse<int>(str, 3, &dest);
  EXPECT_TRUE(result);
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest.value(), 123);
}

// Test parsing a valid integer with null dest (just checks return value)
TEST(ParseOptionalTest_40, ValidIntStringNullDestReturnsTrue_40) {
  const char* str = "456";
  bool result = Parse<int>(str, 3, static_cast<absl::optional<int>*>(nullptr));
  EXPECT_TRUE(result);
}

// Test parsing an invalid string returns false
TEST(ParseOptionalTest_40, InvalidStringReturnsFalse_40) {
  absl::optional<int> dest;
  const char* str = "abc";
  bool result = Parse<int>(str, 3, &dest);
  EXPECT_FALSE(result);
  EXPECT_FALSE(dest.has_value());
}

// Test parsing a negative integer
TEST(ParseOptionalTest_40, NegativeIntParsesSuccessfully_40) {
  absl::optional<int> dest;
  const char* str = "-99";
  bool result = Parse<int>(str, 3, &dest);
  EXPECT_TRUE(result);
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest.value(), -99);
}

// Test parsing zero
TEST(ParseOptionalTest_40, ZeroParsesSuccessfully_40) {
  absl::optional<int> dest;
  const char* str = "0";
  bool result = Parse<int>(str, 1, &dest);
  EXPECT_TRUE(result);
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest.value(), 0);
}

// Test parsing an empty string (non-null but zero length)
TEST(ParseOptionalTest_40, EmptyStringReturnsFalse_40) {
  absl::optional<int> dest;
  const char* str = "";
  bool result = Parse<int>(str, 0, &dest);
  EXPECT_FALSE(result);
  EXPECT_FALSE(dest.has_value());
}

// Test parsing a float string into optional<double>
TEST(ParseOptionalTest_40, ValidDoubleStringParsesSuccessfully_40) {
  absl::optional<double> dest;
  const char* str = "3.14";
  bool result = Parse<double>(str, 4, &dest);
  EXPECT_TRUE(result);
  ASSERT_TRUE(dest.has_value());
  EXPECT_DOUBLE_EQ(dest.value(), 3.14);
}

// Test parsing a string with partial length (truncated)
TEST(ParseOptionalTest_40, PartialLengthParsesCorrectly_40) {
  absl::optional<int> dest;
  const char* str = "12345";
  // Only parse first 3 chars "123"
  bool result = Parse<int>(str, 3, &dest);
  EXPECT_TRUE(result);
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest.value(), 123);
}

// Test that a previously set optional gets overwritten on successful parse
TEST(ParseOptionalTest_40, OverwritesPreviousValue_40) {
  absl::optional<int> dest(999);
  const char* str = "42";
  bool result = Parse<int>(str, 2, &dest);
  EXPECT_TRUE(result);
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest.value(), 42);
}

// Test that a previously set optional is not modified on failed parse
TEST(ParseOptionalTest_40, FailedParseDoesNotModifyDest_40) {
  absl::optional<int> dest(999);
  const char* str = "notanumber";
  bool result = Parse<int>(str, 10, &dest);
  EXPECT_FALSE(result);
  // dest should remain unchanged on failure
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest.value(), 999);
}

// Test parsing a string into optional<std::string>
TEST(ParseOptionalTest_40, StringTypeParsesSuccessfully_40) {
  absl::optional<std::string> dest;
  const char* str = "hello";
  bool result = Parse<std::string>(str, 5, &dest);
  EXPECT_TRUE(result);
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest.value(), "hello");
}

// Test null string with zero length resets optional
TEST(ParseOptionalTest_40, NullStrZeroLengthResetsOptional_40) {
  absl::optional<std::string> dest("existing");
  bool result = Parse<std::string>(nullptr, 0, &dest);
  EXPECT_TRUE(result);
  EXPECT_FALSE(dest.has_value());
}

// Test parsing with long value
TEST(ParseOptionalTest_40, ValidLongParsesSuccessfully_40) {
  absl::optional<long> dest;
  const char* str = "1000000";
  bool result = Parse<long>(str, 7, &dest);
  EXPECT_TRUE(result);
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest.value(), 1000000L);
}

// Test parsing float string as int fails
TEST(ParseOptionalTest_40, FloatStringAsIntFails_40) {
  absl::optional<int> dest;
  const char* str = "3.14";
  bool result = Parse<int>(str, 4, &dest);
  EXPECT_FALSE(result);
  EXPECT_FALSE(dest.has_value());
}

}  // namespace re2_internal
}  // namespace re2
