#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"

// Test ID: 268

class RE2Test_268 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// =============================================================================
// Tests for the Parse<absl::string_view> specialization
// =============================================================================

TEST_F(RE2Test_268, ParseStringViewNullDest_268) {
  // When dest is NULL, Parse should return true without crashing
  const char* str = "hello";
  bool result = re2::re2_internal::Parse(str, 5, static_cast<absl::string_view*>(nullptr));
  EXPECT_TRUE(result);
}

TEST_F(RE2Test_268, ParseStringViewValidDest_268) {
  // When dest is valid, Parse should set *dest to the string_view of (str, n)
  const char* str = "hello world";
  absl::string_view dest;
  bool result = re2::re2_internal::Parse(str, 5, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ(dest, "hello");
  EXPECT_EQ(dest.data(), str);
  EXPECT_EQ(dest.size(), 5u);
}

TEST_F(RE2Test_268, ParseStringViewEmptyString_268) {
  // Parse with n=0 should produce an empty string_view
  const char* str = "hello";
  absl::string_view dest("initial");
  bool result = re2::re2_internal::Parse(str, 0, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ(dest.size(), 0u);
  EXPECT_EQ(dest.data(), str);
}

TEST_F(RE2Test_268, ParseStringViewFullString_268) {
  // Parse with full length should capture the entire string
  const char* str = "complete string";
  size_t len = strlen(str);
  absl::string_view dest;
  bool result = re2::re2_internal::Parse(str, len, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ(dest, "complete string");
  EXPECT_EQ(dest.size(), len);
}

TEST_F(RE2Test_268, ParseStringViewPartialString_268) {
  // Parse with partial length
  const char* str = "abcdef";
  absl::string_view dest;
  bool result = re2::re2_internal::Parse(str, 3, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ(dest, "abc");
  EXPECT_EQ(dest.size(), 3u);
}

TEST_F(RE2Test_268, ParseStringViewWithEmbeddedNull_268) {
  // Parse should handle embedded null bytes (since it uses size, not strlen)
  const char str[] = "ab\0cd";
  absl::string_view dest;
  bool result = re2::re2_internal::Parse(str, 5, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ(dest.size(), 5u);
  EXPECT_EQ(dest[0], 'a');
  EXPECT_EQ(dest[1], 'b');
  EXPECT_EQ(dest[2], '\0');
  EXPECT_EQ(dest[3], 'c');
  EXPECT_EQ(dest[4], 'd');
}

// =============================================================================
// Tests for RE2 basic matching functionality
// =============================================================================

TEST_F(RE2Test_268, FullMatchSimple_268) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
  EXPECT_FALSE(RE2::FullMatch("hello", "world"));
}

TEST_F(RE2Test_268, FullMatchWithCapture_268) {
  std::string captured;
  EXPECT_TRUE(RE2::FullMatch("hello123", "hello(\\d+)", &captured));
  EXPECT_EQ(captured, "123");
}

TEST_F(RE2Test_268, FullMatchFailsOnPartial_268) {
  // FullMatch should not match a partial string
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST_F(RE2Test_268, PartialMatchSimple_268) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "hello"));
  EXPECT_TRUE(RE2::PartialMatch("hello world", "world"));
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST_F(RE2Test_268, PartialMatchWithCapture_268) {
  int value;
  EXPECT_TRUE(RE2::PartialMatch("x = 42", "(\\d+)", &value));
  EXPECT_EQ(value, 42);
}

TEST_F(RE2Test_268, PartialMatchStringViewCapture_268) {
  absl::string_view captured;
  EXPECT_TRUE(RE2::PartialMatch("foo bar baz", "(bar)", &captured));
  EXPECT_EQ(captured, "bar");
}

TEST_F(RE2Test_268, EmptyPattern_268) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

TEST_F(RE2Test_268, EmptyInput_268) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_FALSE(RE2::FullMatch("", "notempty"));
  EXPECT_TRUE(RE2::PartialMatch("", ""));
}

TEST_F(RE2Test_268, InvalidPattern_268) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
}

TEST_F(RE2Test_268, ValidPattern_268) {
  RE2 re("valid(pattern)?");
  EXPECT_TRUE(re.ok());
}

TEST_F(RE2Test_268, ReplaceFirst_268) {
  std::string s = "hello world hello";
  EXPECT_TRUE(RE2::Replace(&s, "hello", "hi"));
  EXPECT_EQ(s, "hi world hello");
}

TEST_F(RE2Test_268, ReplaceGlobal_268) {
  std::string s = "hello world hello";
  int count = RE2::GlobalReplace(&s, "hello", "hi");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(s, "hi world hi");
}

TEST_F(RE2Test_268, ReplaceNoMatch_268) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ(s, "hello world");
}

TEST_F(RE2Test_268, NumberOfCapturingGroups_268) {
  RE2 re("(\\d+)-(\\w+)-(.)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(RE2Test_268, NumberOfCapturingGroupsZero_268) {
  RE2 re("no groups here");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2Test_268, PatternAccessor_268) {
  RE2 re("test_pattern");
  EXPECT_EQ(re.pattern(), "test_pattern");
}

TEST_F(RE2Test_268, FullMatchMultipleCaptures_268) {
  std::string s1, s2;
  EXPECT_TRUE(RE2::FullMatch("abc-def", "(\\w+)-(\\w+)", &s1, &s2));
  EXPECT_EQ(s1, "abc");
  EXPECT_EQ(s2, "def");
}

TEST_F(RE2Test_268, FullMatchIntegerCapture_268) {
  int val;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &val));
  EXPECT_EQ(val, 12345);
}

TEST_F(RE2Test_268, FullMatchNoCaptureArg_268) {
  // Match without extracting captures
  EXPECT_TRUE(RE2::FullMatch("12345", "\\d+"));
}

TEST_F(RE2Test_268, ConsumeBasic_268) {
  absl::string_view input("one1two2three3");
  std::string word;
  int number;
  EXPECT_TRUE(RE2::Consume(&input, "(\\w+?)(\\d)", &word, &number));
  EXPECT_EQ(word, "one");
  EXPECT_EQ(number, 1);
}

TEST_F(RE2Test_268, FindAndConsumeBasic_268) {
  absl::string_view input("skip to 42 and 100");
  int number;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &number));
  EXPECT_EQ(number, 42);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &number));
  EXPECT_EQ(number, 100);
}

TEST_F(RE2Test_268, QuoteMetaSimple_268) {
  std::string quoted = RE2::QuoteMeta("hello.world");
  // The quoted version should match the literal string
  EXPECT_TRUE(RE2::FullMatch("hello.world", quoted));
  EXPECT_FALSE(RE2::FullMatch("helloXworld", quoted));
}

TEST_F(RE2Test_268, QuoteMetaSpecialChars_268) {
  std::string quoted = RE2::QuoteMeta("[test]");
  EXPECT_TRUE(RE2::FullMatch("[test]", quoted));
}

TEST_F(RE2Test_268, MatchWithAnchoring_268) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.ok());
  absl::string_view input("abc123def");
  absl::string_view match;
  
  // UNANCHORED should find the match anywhere
  EXPECT_TRUE(re.Match(input, 0, input.size(), RE2::UNANCHORED, &match, 1));
  EXPECT_EQ(match, "123");
  
  // ANCHOR_START should fail since input doesn't start with digits
  EXPECT_FALSE(re.Match(input, 0, input.size(), RE2::ANCHOR_START, &match, 1));
  
  // ANCHOR_BOTH should fail for same reason
  EXPECT_FALSE(re.Match(input, 0, input.size(), RE2::ANCHOR_BOTH, &match, 1));
}

TEST_F(RE2Test_268, MatchAnchorBothSuccess_268) {
  RE2 re("\\d+");
  absl::string_view input("12345");
  absl::string_view match;
  EXPECT_TRUE(re.Match(input, 0, input.size(), RE2::ANCHOR_BOTH, &match, 1));
  EXPECT_EQ(match, "12345");
}

TEST_F(RE2Test_268, MatchWithSubrange_268) {
  RE2 re("\\d+");
  absl::string_view input("abc123def456");
  absl::string_view match;
  // Search starting from position 3
  EXPECT_TRUE(re.Match(input, 3, input.size(), RE2::ANCHOR_START, &match, 1));
  EXPECT_EQ(match, "123");
}
