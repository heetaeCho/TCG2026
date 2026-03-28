#include "gtest/gtest.h"
#include "util/pcre.h"
#include <string>

namespace re2 {

class PCRETest_198 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test construction with a simple pattern (const char*)
TEST_F(PCRETest_198, ConstructFromCString_198) {
  PCRE re("hello");
  EXPECT_EQ(re.pattern(), "hello");
  EXPECT_EQ(re.error(), "");
}

// Test construction with std::string
TEST_F(PCRETest_198, ConstructFromString_198) {
  std::string pattern = "world";
  PCRE re(pattern);
  EXPECT_EQ(re.pattern(), "world");
}

// Test pattern() returns the original pattern
TEST_F(PCRETest_198, PatternReturnsOriginal_198) {
  PCRE re("foo.*bar");
  EXPECT_EQ(re.pattern(), "foo.*bar");
}

// Test ClearHitLimit and HitLimit
TEST_F(PCRETest_198, ClearHitLimitResetsFlag_198) {
  PCRE re("test");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// Test HitLimit initially returns false
TEST_F(PCRETest_198, HitLimitInitiallyFalse_198) {
  PCRE re("abc");
  EXPECT_FALSE(re.HitLimit());
}

// Test NumberOfCapturingGroups with no groups
TEST_F(PCRETest_198, NumberOfCapturingGroupsNone_198) {
  PCRE re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

// Test NumberOfCapturingGroups with groups
TEST_F(PCRETest_198, NumberOfCapturingGroupsWithGroups_198) {
  PCRE re("(hello)(world)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 2);
}

// Test NumberOfCapturingGroups with nested groups
TEST_F(PCRETest_198, NumberOfCapturingGroupsNested_198) {
  PCRE re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

// Test QuoteMeta on simple string
TEST_F(PCRETest_198, QuoteMetaSimple_198) {
  std::string result = PCRE::QuoteMeta("hello");
  EXPECT_EQ(result, "hello");
}

// Test QuoteMeta on special characters
TEST_F(PCRETest_198, QuoteMetaSpecialChars_198) {
  std::string result = PCRE::QuoteMeta("hello.world");
  EXPECT_EQ(result, "hello\\.world");
}

// Test QuoteMeta on multiple special characters
TEST_F(PCRETest_198, QuoteMetaMultipleSpecialChars_198) {
  std::string result = PCRE::QuoteMeta("a+b*c?d");
  EXPECT_EQ(result, "a\\+b\\*c\\?d");
}

// Test QuoteMeta on empty string
TEST_F(PCRETest_198, QuoteMetaEmpty_198) {
  std::string result = PCRE::QuoteMeta("");
  EXPECT_EQ(result, "");
}

// Test QuoteMeta with brackets
TEST_F(PCRETest_198, QuoteMetaBrackets_198) {
  std::string result = PCRE::QuoteMeta("[abc]");
  EXPECT_EQ(result, "\\[abc\\]");
}

// Test Replace with simple substitution
TEST_F(PCRETest_198, ReplaceSimple_198) {
  std::string str = "hello world";
  PCRE re("world");
  EXPECT_TRUE(PCRE::Replace(&str, re, "there"));
  EXPECT_EQ(str, "hello there");
}

// Test Replace with no match
TEST_F(PCRETest_198, ReplaceNoMatch_198) {
  std::string str = "hello world";
  PCRE re("xyz");
  EXPECT_FALSE(PCRE::Replace(&str, re, "there"));
  EXPECT_EQ(str, "hello world");
}

// Test Replace with capture group
TEST_F(PCRETest_198, ReplaceWithCaptureGroup_198) {
  std::string str = "hello world";
  PCRE re("(world)");
  EXPECT_TRUE(PCRE::Replace(&str, re, "\\1!"));
  EXPECT_EQ(str, "hello world!");
}

// Test GlobalReplace replaces all occurrences
TEST_F(PCRETest_198, GlobalReplaceAll_198) {
  std::string str = "aaa";
  PCRE re("a");
  int count = PCRE::GlobalReplace(&str, re, "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "bbb");
}

// Test GlobalReplace with no match
TEST_F(PCRETest_198, GlobalReplaceNoMatch_198) {
  std::string str = "hello";
  PCRE re("xyz");
  int count = PCRE::GlobalReplace(&str, re, "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

// Test Extract
TEST_F(PCRETest_198, ExtractSimple_198) {
  std::string out;
  PCRE re("(\\w+)@(\\w+)");
  EXPECT_TRUE(PCRE::Extract("user@host", re, "\\1 at \\2", &out));
  EXPECT_EQ(out, "user at host");
}

// Test Extract with no match
TEST_F(PCRETest_198, ExtractNoMatch_198) {
  std::string out;
  PCRE re("(\\d+)");
  EXPECT_FALSE(PCRE::Extract("hello", re, "\\1", &out));
}

// Test CheckRewriteString with valid rewrite
TEST_F(PCRETest_198, CheckRewriteStringValid_198) {
  PCRE re("(hello)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

// Test CheckRewriteString with invalid rewrite (reference beyond groups)
TEST_F(PCRETest_198, CheckRewriteStringInvalid_198) {
  PCRE re("hello");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\1", &error));
  EXPECT_FALSE(error.empty());
}

// Test DoMatch with simple match (no capture)
TEST_F(PCRETest_198, DoMatchSimple_198) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

// Test DoMatch with no match
TEST_F(PCRETest_198, DoMatchNoMatch_198) {
  PCRE re("hello");
  EXPECT_FALSE(re.DoMatch("world", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

// Test DoMatch anchored at start
TEST_F(PCRETest_198, DoMatchAnchored_198) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

// Test DoMatch full anchor
TEST_F(PCRETest_198, DoMatchAnchorBoth_198) {
  PCRE re("hello");
  EXPECT_FALSE(re.DoMatch("hello world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

// Test construction with invalid pattern
TEST_F(PCRETest_198, InvalidPattern_198) {
  PCRE re("[invalid");
  EXPECT_FALSE(re.error().empty());
}

// Test empty pattern
TEST_F(PCRETest_198, EmptyPattern_198) {
  PCRE re("");
  EXPECT_EQ(re.pattern(), "");
  EXPECT_TRUE(re.DoMatch("anything", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

// Test empty pattern full match against empty string
TEST_F(PCRETest_198, EmptyPatternFullMatchEmptyString_198) {
  PCRE re("");
  EXPECT_TRUE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

// Test DoMatch with consumed parameter
TEST_F(PCRETest_198, DoMatchWithConsumed_198) {
  PCRE re("hel");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_START, &consumed, nullptr, 0));
  EXPECT_EQ(consumed, 3u);
}

// Test GlobalReplace with empty match
TEST_F(PCRETest_198, GlobalReplaceEmptyPattern_198) {
  std::string str = "abc";
  PCRE re("b");
  int count = PCRE::GlobalReplace(&str, re, "");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(str, "ac");
}

// Test Replace only replaces first occurrence
TEST_F(PCRETest_198, ReplaceOnlyFirst_198) {
  std::string str = "aaa";
  PCRE re("a");
  EXPECT_TRUE(PCRE::Replace(&str, re, "b"));
  EXPECT_EQ(str, "baa");
}

// Test QuoteMeta with backslash
TEST_F(PCRETest_198, QuoteMetaBackslash_198) {
  std::string result = PCRE::QuoteMeta("a\\b");
  EXPECT_EQ(result, "a\\\\b");
}

// Test pattern with special regex characters
TEST_F(PCRETest_198, PatternWithSpecialChars_198) {
  PCRE re("a.b");
  EXPECT_TRUE(re.DoMatch("acb", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch("ab", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

// Test NumberOfCapturingGroups with single group
TEST_F(PCRETest_198, NumberOfCapturingGroupsSingle_198) {
  PCRE re("(abc)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

// Test CheckRewriteString with no backslash references
TEST_F(PCRETest_198, CheckRewriteStringNoRefs_198) {
  PCRE re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("replacement", &error));
  EXPECT_TRUE(error.empty());
}

}  // namespace re2
