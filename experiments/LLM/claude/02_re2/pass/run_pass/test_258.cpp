#include "gtest/gtest.h"
#include "re2/re2.h"
#include <string>

namespace {

// Test fixture for RE2::Extract tests
class RE2ExtractTest_258 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Normal operation: basic extraction with a simple capture group
TEST_F(RE2ExtractTest_258, BasicExtraction_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(\\w+)@([\\w.]+)", "\\1", &out));
  EXPECT_EQ(out, "boris");
}

// Normal operation: extract second capture group
TEST_F(RE2ExtractTest_258, ExtractSecondGroup_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(\\w+)@([\\w.]+)", "\\2", &out));
  EXPECT_EQ(out, "kremlin.ru");
}

// Normal operation: extract with rewrite combining multiple groups
TEST_F(RE2ExtractTest_258, ExtractCombinedGroups_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(\\w+)@([\\w.]+)", "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin.ru!boris");
}

// Normal operation: extract full match using \0
TEST_F(RE2ExtractTest_258, ExtractFullMatch_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("foo bar baz", "(bar)", "matched: \\0", &out));
  EXPECT_EQ(out, "matched: bar");
}

// Normal operation: rewrite with literal text only (no backreferences)
TEST_F(RE2ExtractTest_258, ExtractLiteralRewrite_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("hello world", "world", "planet", &out));
  EXPECT_EQ(out, "planet");
}

// Normal operation: pattern with no capture groups, rewrite without backreferences
TEST_F(RE2ExtractTest_258, NoCaptureGroupsLiteralRewrite_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("abc", "b", "X", &out));
  EXPECT_EQ(out, "X");
}

// Boundary: empty text with pattern that matches empty string
TEST_F(RE2ExtractTest_258, EmptyTextMatchingPattern_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("", "(.*)", "\\1", &out));
  EXPECT_EQ(out, "");
}

// Boundary: empty text with pattern that does not match empty string
TEST_F(RE2ExtractTest_258, EmptyTextNonMatchingPattern_258) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("", "\\w+", "\\0", &out));
}

// Error case: rewrite references more groups than available
TEST_F(RE2ExtractTest_258, RewriteReferencesTooManyGroups_258) {
  std::string out;
  // Pattern has 1 capture group, but rewrite references \2
  EXPECT_FALSE(RE2::Extract("hello", "(\\w+)", "\\2", &out));
}

// Error case: no match in text
TEST_F(RE2ExtractTest_258, NoMatch_258) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("hello", "xyz", "\\0", &out));
}

// Normal operation: extract with partial match in longer text
TEST_F(RE2ExtractTest_258, PartialMatchInLongerText_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("The quick brown fox", "(\\w+) fox", "\\1", &out));
  EXPECT_EQ(out, "brown");
}

// Normal: rewrite that uses \0 for the full match
TEST_F(RE2ExtractTest_258, FullMatchBackref_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("abc123def", "([0-9]+)", "[\\0]", &out));
  EXPECT_EQ(out, "[123]");
}

// Normal operation: multiple capture groups, reference only one
TEST_F(RE2ExtractTest_258, MultipleGroupsReferenceOne_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("2023-12-25", "(\\d{4})-(\\d{2})-(\\d{2})", "Year: \\1", &out));
  EXPECT_EQ(out, "Year: 2023");
}

// Normal operation: multiple capture groups, reference all
TEST_F(RE2ExtractTest_258, MultipleGroupsReferenceAll_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("2023-12-25", "(\\d{4})-(\\d{2})-(\\d{2})", "\\3/\\2/\\1", &out));
  EXPECT_EQ(out, "25/12/2023");
}

// Normal: out string is cleared before extraction
TEST_F(RE2ExtractTest_258, OutStringIsCleared_258) {
  std::string out = "old_value";
  EXPECT_TRUE(RE2::Extract("hello", "(\\w+)", "\\1", &out));
  EXPECT_EQ(out, "hello");
}

// Error case: invalid regex pattern
TEST_F(RE2ExtractTest_258, InvalidPattern_258) {
  std::string out;
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(RE2::Extract("text", re, "\\1", &out));
}

// Boundary: rewrite string is empty
TEST_F(RE2ExtractTest_258, EmptyRewrite_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("hello", "hello", "", &out));
  EXPECT_EQ(out, "");
}

// Normal: extract with text containing special regex characters
TEST_F(RE2ExtractTest_258, TextWithSpecialChars_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("price is $100.50", "\\$(\\d+\\.\\d+)", "USD \\1", &out));
  EXPECT_EQ(out, "USD 100.50");
}

// Boundary: very long text with match at end
TEST_F(RE2ExtractTest_258, LongTextMatchAtEnd_258) {
  std::string text(10000, 'a');
  text += "needle";
  std::string out;
  EXPECT_TRUE(RE2::Extract(text, "(needle)", "found: \\1", &out));
  EXPECT_EQ(out, "found: needle");
}

// Normal: nested groups
TEST_F(RE2ExtractTest_258, NestedGroups_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("abc", "((a)(b))(c)", "\\1-\\2-\\3-\\4", &out));
  EXPECT_EQ(out, "ab-a-b-c");
}

// Boundary: rewrite with backslash but no digit following
TEST_F(RE2ExtractTest_258, RewriteBackslashLiteral_258) {
  std::string out;
  // Testing rewrite with escaped backslash
  EXPECT_TRUE(RE2::Extract("hello", "(hello)", "\\\\\\1", &out));
  EXPECT_EQ(out, "\\hello");
}

// Error: text does not contain pattern
TEST_F(RE2ExtractTest_258, PatternNotFound_258) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("hello world", "xyz(\\d+)", "\\1", &out));
}

// Normal: extract with anchored-like behavior (unanchored search)
TEST_F(RE2ExtractTest_258, UnanchoredSearch_258) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("prefix 42 suffix", "(\\d+)", "num=\\1", &out));
  EXPECT_EQ(out, "num=42");
}

}  // namespace
