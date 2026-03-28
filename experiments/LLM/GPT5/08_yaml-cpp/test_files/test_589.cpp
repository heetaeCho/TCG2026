// File: ./TestProjects/yaml-cpp/test/null_string_test.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <string>

namespace YAML {
// Forward declaration for the function under test (implemented in src/null.cpp).
bool IsNullString(const char* str, std::size_t size);
}  // namespace YAML

class IsNullStringTest_589 : public ::testing::Test {};

TEST_F(IsNullStringTest_589, EmptySizeReturnsTrueEvenWithNullptr_589) {
  EXPECT_TRUE(YAML::IsNullString(nullptr, 0u));

  const char* any = "anything";
  EXPECT_TRUE(YAML::IsNullString(any, 0u));
}

TEST_F(IsNullStringTest_589, TildeReturnsTrueOnlyWhenExactSize_589) {
  const char* s = "~";
  EXPECT_TRUE(YAML::IsNullString(s, 1u));

  // Wrong size should not match
  EXPECT_FALSE(YAML::IsNullString(s, 0u));  // size==0 => true, but already covered above
  EXPECT_FALSE(YAML::IsNullString(s, 2u));
}

TEST_F(IsNullStringTest_589, NullLowercaseReturnsTrueOnlyWhenExactSize_589) {
  const char* s = "null";
  EXPECT_TRUE(YAML::IsNullString(s, 4u));

  // Boundary: partial sizes should not match
  EXPECT_FALSE(YAML::IsNullString(s, 1u));
  EXPECT_FALSE(YAML::IsNullString(s, 2u));
  EXPECT_FALSE(YAML::IsNullString(s, 3u));

  // Boundary: larger size should not match exact token
  EXPECT_FALSE(YAML::IsNullString(s, 5u));
}

TEST_F(IsNullStringTest_589, NullCapitalizedReturnsTrueOnlyWhenExactSize_589) {
  const char* s = "Null";
  EXPECT_TRUE(YAML::IsNullString(s, 4u));

  EXPECT_FALSE(YAML::IsNullString(s, 3u));
  EXPECT_FALSE(YAML::IsNullString(s, 5u));
}

TEST_F(IsNullStringTest_589, NullUppercaseReturnsTrueOnlyWhenExactSize_589) {
  const char* s = "NULL";
  EXPECT_TRUE(YAML::IsNullString(s, 4u));

  EXPECT_FALSE(YAML::IsNullString(s, 3u));
  EXPECT_FALSE(YAML::IsNullString(s, 5u));
}

TEST_F(IsNullStringTest_589, NonNullStringsReturnFalse_589) {
  EXPECT_FALSE(YAML::IsNullString("nUll", 4u));     // mixed case (not listed)
  EXPECT_FALSE(YAML::IsNullString("nil", 3u));      // different token
  EXPECT_FALSE(YAML::IsNullString("~ ", 2u));       // trailing space
  EXPECT_FALSE(YAML::IsNullString(" ~", 2u));       // leading space
  EXPECT_FALSE(YAML::IsNullString("null ", 5u));    // trailing space
  EXPECT_FALSE(YAML::IsNullString(" null", 5u));    // leading space
  EXPECT_FALSE(YAML::IsNullString("NULL!", 5u));    // extra punctuation
  EXPECT_FALSE(YAML::IsNullString("nul", 3u));      // prefix
  EXPECT_FALSE(YAML::IsNullString("nulls", 5u));    // token plus extra char
}

TEST_F(IsNullStringTest_589, EmbeddedNullByteDoesNotAccidentallyMatch_589) {
  // Explicit byte buffer: {'n','u','l','l','\0'} with size 5.
  // Should not match the exact 4-byte "null" token.
  const char buf[] = {'n', 'u', 'l', 'l', '\0'};
  EXPECT_FALSE(YAML::IsNullString(buf, 5u));

  // But if size is exactly 4, it should match "null".
  EXPECT_TRUE(YAML::IsNullString(buf, 4u));
}

TEST_F(IsNullStringTest_589, EmptyStringPointerWithZeroSizeIsNull_589) {
  const char empty[] = "";
  EXPECT_TRUE(YAML::IsNullString(empty, 0u));
}