#include "gtest/gtest.h"
#include "util/pcre.h"
#include <string>

namespace re2 {

class PCRECheckRewriteStringTest_200 : public ::testing::Test {
protected:
};

// Test: Simple rewrite string with no backslash references should succeed
TEST_F(PCRECheckRewriteStringTest_200, SimpleStringNoBackslash_200) {
  PCRE re("(.*)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("hello world", &error));
  EXPECT_TRUE(error.empty());
}

// Test: Empty rewrite string should succeed
TEST_F(PCRECheckRewriteStringTest_200, EmptyRewriteString_200) {
  PCRE re("(.*)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("", &error));
  EXPECT_TRUE(error.empty());
}

// Test: Rewrite string with valid back-reference \1 and one capturing group
TEST_F(PCRECheckRewriteStringTest_200, ValidSingleBackReference_200) {
  PCRE re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
  EXPECT_TRUE(error.empty());
}

// Test: Rewrite string with \0 should always succeed (match group 0)
TEST_F(PCRECheckRewriteStringTest_200, BackReferenceZero_200) {
  PCRE re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\0", &error));
  EXPECT_TRUE(error.empty());
}

// Test: Escaped backslash \\ should be valid
TEST_F(PCRECheckRewriteStringTest_200, EscapedBackslash_200) {
  PCRE re("(.*)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\\\", &error));
  EXPECT_TRUE(error.empty());
}

// Test: Backslash at end of string should fail
TEST_F(PCRECheckRewriteStringTest_200, BackslashAtEnd_200) {
  PCRE re("(.*)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("hello\\", &error));
  EXPECT_EQ(error, "Rewrite schema error: '\\' not allowed at end.");
}

// Test: Backslash followed by non-digit, non-backslash character should fail
TEST_F(PCRECheckRewriteStringTest_200, BackslashFollowedByNonDigit_200) {
  PCRE re("(.*)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\a", &error));
  EXPECT_EQ(error, "Rewrite schema error: '\\' must be followed by a digit or '\\'.");
}

// Test: Back-reference exceeds number of capturing groups should fail
TEST_F(PCRECheckRewriteStringTest_200, BackReferenceExceedsGroups_200) {
  PCRE re("hello");  // No capturing groups
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\1", &error));
  EXPECT_FALSE(error.empty());
}

// Test: Multiple valid back-references
TEST_F(PCRECheckRewriteStringTest_200, MultipleValidBackReferences_200) {
  PCRE re("(\\w+) (\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1 and \\2", &error));
  EXPECT_TRUE(error.empty());
}

// Test: Back-reference \2 with only one capturing group should fail
TEST_F(PCRECheckRewriteStringTest_200, BackReferenceTwoWithOneGroup_200) {
  PCRE re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// Test: Mix of escaped backslash and valid back-references
TEST_F(PCRECheckRewriteStringTest_200, MixEscapedBackslashAndBackRef_200) {
  PCRE re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\\\\\1", &error));
  EXPECT_TRUE(error.empty());
}

// Test: Backslash followed by a letter (not digit, not backslash) in middle of string
TEST_F(PCRECheckRewriteStringTest_200, BackslashFollowedByLetterMiddle_200) {
  PCRE re("(.*)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("hello\\xworld", &error));
  EXPECT_EQ(error, "Rewrite schema error: '\\' must be followed by a digit or '\\'.");
}

// Test: Only a single backslash
TEST_F(PCRECheckRewriteStringTest_200, SingleBackslashOnly_200) {
  PCRE re("(.*)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\", &error));
  EXPECT_EQ(error, "Rewrite schema error: '\\' not allowed at end.");
}

// Test: \9 with enough capturing groups should succeed
TEST_F(PCRECheckRewriteStringTest_200, BackReferenceNine_200) {
  // Pattern with 9 capturing groups
  PCRE re("(a)(b)(c)(d)(e)(f)(g)(h)(i)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\9", &error));
  EXPECT_TRUE(error.empty());
}

// Test: \9 with fewer than 9 capturing groups should fail
TEST_F(PCRECheckRewriteStringTest_200, BackReferenceNineInsufficientGroups_200) {
  PCRE re("(a)(b)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\9", &error));
  EXPECT_FALSE(error.empty());
}

// Test: Rewrite string with no special characters, just plain text
TEST_F(PCRECheckRewriteStringTest_200, PlainTextRewrite_200) {
  PCRE re("abc");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("replacement text", &error));
  EXPECT_TRUE(error.empty());
}

// Test: Multiple escaped backslashes
TEST_F(PCRECheckRewriteStringTest_200, MultipleEscapedBackslashes_200) {
  PCRE re("abc");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\\\\\\\", &error));
  EXPECT_TRUE(error.empty());
}

// Test: Back-reference \0 is always valid regardless of capturing groups
TEST_F(PCRECheckRewriteStringTest_200, BackRefZeroNoCapturingGroups_200) {
  PCRE re("abc");  // 0 capturing groups
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\0", &error));
  EXPECT_TRUE(error.empty());
}

// Test: pattern() returns the pattern string
TEST_F(PCRECheckRewriteStringTest_200, PatternAccessor_200) {
  PCRE re("(\\w+)");
  EXPECT_EQ(re.pattern(), "(\\w+)");
}

// Test: NumberOfCapturingGroups returns correct count
TEST_F(PCRECheckRewriteStringTest_200, NumberOfCapturingGroupsZero_200) {
  PCRE re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(PCRECheckRewriteStringTest_200, NumberOfCapturingGroupsOne_200) {
  PCRE re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST_F(PCRECheckRewriteStringTest_200, NumberOfCapturingGroupsMultiple_200) {
  PCRE re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

// Test: Backslash followed by space should fail
TEST_F(PCRECheckRewriteStringTest_200, BackslashFollowedBySpace_200) {
  PCRE re("(.*)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\ ", &error));
  EXPECT_EQ(error, "Rewrite schema error: '\\' must be followed by a digit or '\\'.");
}

// Test: QuoteMeta with special characters
TEST_F(PCRECheckRewriteStringTest_200, QuoteMetaSpecialChars_200) {
  std::string quoted = PCRE::QuoteMeta("a.b*c+d");
  // The result should be a pattern that matches the literal string
  PCRE re(quoted);
  EXPECT_TRUE(re.DoMatch("a.b*c+d", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

// Test: QuoteMeta with empty string
TEST_F(PCRECheckRewriteStringTest_200, QuoteMetaEmpty_200) {
  std::string quoted = PCRE::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

// Test: Replace basic functionality
TEST_F(PCRECheckRewriteStringTest_200, ReplaceBasic_200) {
  std::string str = "hello world";
  PCRE re("world");
  bool result = PCRE::Replace(&str, re, "there");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, "hello there");
}

// Test: Replace with no match
TEST_F(PCRECheckRewriteStringTest_200, ReplaceNoMatch_200) {
  std::string str = "hello world";
  PCRE re("xyz");
  bool result = PCRE::Replace(&str, re, "there");
  EXPECT_FALSE(result);
  EXPECT_EQ(str, "hello world");
}

// Test: GlobalReplace replaces all occurrences
TEST_F(PCRECheckRewriteStringTest_200, GlobalReplaceMultiple_200) {
  std::string str = "aaa";
  PCRE re("a");
  int count = PCRE::GlobalReplace(&str, re, "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "bbb");
}

// Test: GlobalReplace with no match
TEST_F(PCRECheckRewriteStringTest_200, GlobalReplaceNoMatch_200) {
  std::string str = "hello";
  PCRE re("xyz");
  int count = PCRE::GlobalReplace(&str, re, "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

// Test: Extract basic functionality
TEST_F(PCRECheckRewriteStringTest_200, ExtractBasic_200) {
  std::string out;
  PCRE re("(\\w+)@(\\w+)");
  bool result = PCRE::Extract("user@host", re, "\\1 at \\2", &out);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "user at host");
}

// Test: Extract with no match
TEST_F(PCRECheckRewriteStringTest_200, ExtractNoMatch_200) {
  std::string out;
  PCRE re("(\\w+)@(\\w+)");
  bool result = PCRE::Extract("noatsign", re, "\\1 at \\2", &out);
  EXPECT_FALSE(result);
}

// Test: HitLimit and ClearHitLimit
TEST_F(PCRECheckRewriteStringTest_200, HitLimitInitiallyFalse_200) {
  PCRE re("(.*)");
  EXPECT_FALSE(re.HitLimit());
}

TEST_F(PCRECheckRewriteStringTest_200, ClearHitLimit_200) {
  PCRE re("(.*)");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

}  // namespace re2
