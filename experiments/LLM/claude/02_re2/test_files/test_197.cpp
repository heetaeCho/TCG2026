#include "gtest/gtest.h"
#include "util/pcre.h"
#include <string>

namespace re2 {

class PCRETest_197 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// =============================================================================
// Constructor Tests
// =============================================================================

TEST_F(PCRETest_197, ConstructFromCString_197) {
  PCRE re("hello");
  EXPECT_EQ(re.pattern(), "hello");
  EXPECT_TRUE(re.error().empty());
}

TEST_F(PCRETest_197, ConstructFromStdString_197) {
  std::string pat = "world";
  PCRE re(pat);
  EXPECT_EQ(re.pattern(), "world");
}

TEST_F(PCRETest_197, ConstructWithSimplePattern_197) {
  PCRE re("a+b*c?");
  EXPECT_EQ(re.pattern(), "a+b*c?");
}

TEST_F(PCRETest_197, ConstructWithEmptyPattern_197) {
  PCRE re("");
  EXPECT_EQ(re.pattern(), "");
}

// =============================================================================
// HitLimit / ClearHitLimit Tests
// =============================================================================

TEST_F(PCRETest_197, HitLimitInitiallyFalse_197) {
  PCRE re("test");
  EXPECT_FALSE(re.HitLimit());
}

TEST_F(PCRETest_197, ClearHitLimitOnFresh_197) {
  PCRE re("test");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// =============================================================================
// NumberOfCapturingGroups Tests
// =============================================================================

TEST_F(PCRETest_197, NoCapturingGroups_197) {
  PCRE re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(PCRETest_197, OneCapturingGroup_197) {
  PCRE re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST_F(PCRETest_197, MultipleCapturingGroups_197) {
  PCRE re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(PCRETest_197, NestedCapturingGroups_197) {
  PCRE re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

// =============================================================================
// QuoteMeta Tests
// =============================================================================

TEST_F(PCRETest_197, QuoteMetaSimpleString_197) {
  std::string result = PCRE::QuoteMeta("hello");
  EXPECT_EQ(result, "hello");
}

TEST_F(PCRETest_197, QuoteMetaSpecialChars_197) {
  std::string result = PCRE::QuoteMeta("a.b");
  EXPECT_NE(result, "a.b");  // dot should be escaped
}

TEST_F(PCRETest_197, QuoteMetaEmpty_197) {
  std::string result = PCRE::QuoteMeta("");
  EXPECT_EQ(result, "");
}

TEST_F(PCRETest_197, QuoteMetaBrackets_197) {
  std::string result = PCRE::QuoteMeta("[abc]");
  // Brackets should be escaped
  EXPECT_NE(result, "[abc]");
}

TEST_F(PCRETest_197, QuoteMetaBackslash_197) {
  std::string result = PCRE::QuoteMeta("a\\b");
  EXPECT_NE(result, "a\\b");
}

// =============================================================================
// DoMatch Tests
// =============================================================================

TEST_F(PCRETest_197, DoMatchSimpleFullMatch_197) {
  PCRE re("hello");
  bool matched = re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_TRUE(matched);
}

TEST_F(PCRETest_197, DoMatchSimpleFullMatchFails_197) {
  PCRE re("hello");
  bool matched = re.DoMatch("world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_FALSE(matched);
}

TEST_F(PCRETest_197, DoMatchUnanchored_197) {
  PCRE re("ell");
  bool matched = re.DoMatch("hello", PCRE::UNANCHORED, nullptr, nullptr, 0);
  EXPECT_TRUE(matched);
}

TEST_F(PCRETest_197, DoMatchAnchorStart_197) {
  PCRE re("hel");
  bool matched = re.DoMatch("hello", PCRE::ANCHOR_START, nullptr, nullptr, 0);
  EXPECT_TRUE(matched);
}

TEST_F(PCRETest_197, DoMatchAnchorStartFails_197) {
  PCRE re("ell");
  bool matched = re.DoMatch("hello", PCRE::ANCHOR_START, nullptr, nullptr, 0);
  EXPECT_FALSE(matched);
}

TEST_F(PCRETest_197, DoMatchAnchorBothPartialFails_197) {
  PCRE re("hel");
  bool matched = re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_FALSE(matched);
}

TEST_F(PCRETest_197, DoMatchEmptyPatternEmptyText_197) {
  PCRE re("");
  bool matched = re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_TRUE(matched);
}

TEST_F(PCRETest_197, DoMatchWithConsumed_197) {
  PCRE re("hel");
  size_t consumed = 0;
  bool matched = re.DoMatch("hello", PCRE::ANCHOR_START, &consumed, nullptr, 0);
  EXPECT_TRUE(matched);
  EXPECT_EQ(consumed, 3u);
}

// =============================================================================
// Replace Tests
// =============================================================================

TEST_F(PCRETest_197, ReplaceSimple_197) {
  std::string str = "hello world";
  PCRE re("world");
  bool replaced = PCRE::Replace(&str, re, "there");
  EXPECT_TRUE(replaced);
  EXPECT_EQ(str, "hello there");
}

TEST_F(PCRETest_197, ReplaceNoMatch_197) {
  std::string str = "hello world";
  PCRE re("xyz");
  bool replaced = PCRE::Replace(&str, re, "there");
  EXPECT_FALSE(replaced);
  EXPECT_EQ(str, "hello world");
}

TEST_F(PCRETest_197, ReplaceWithCapture_197) {
  std::string str = "hello world";
  PCRE re("(world)");
  bool replaced = PCRE::Replace(&str, re, "\\1!");
  EXPECT_TRUE(replaced);
  EXPECT_EQ(str, "hello world!");
}

TEST_F(PCRETest_197, ReplaceEmptyMatch_197) {
  std::string str = "hello";
  PCRE re("");
  bool replaced = PCRE::Replace(&str, re, "x");
  // Empty pattern matches at the beginning
  EXPECT_TRUE(replaced);
}

// =============================================================================
// GlobalReplace Tests
// =============================================================================

TEST_F(PCRETest_197, GlobalReplaceSimple_197) {
  std::string str = "aaa";
  PCRE re("a");
  int count = PCRE::GlobalReplace(&str, re, "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "bbb");
}

TEST_F(PCRETest_197, GlobalReplaceNoMatch_197) {
  std::string str = "hello";
  PCRE re("xyz");
  int count = PCRE::GlobalReplace(&str, re, "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

TEST_F(PCRETest_197, GlobalReplaceSingleMatch_197) {
  std::string str = "hello world";
  PCRE re("world");
  int count = PCRE::GlobalReplace(&str, re, "there");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(str, "hello there");
}

// =============================================================================
// Extract Tests
// =============================================================================

TEST_F(PCRETest_197, ExtractSimple_197) {
  std::string out;
  PCRE re("(\\w+)@(\\w+)");
  bool extracted = PCRE::Extract("user@host", re, "\\1 at \\2", &out);
  EXPECT_TRUE(extracted);
  EXPECT_EQ(out, "user at host");
}

TEST_F(PCRETest_197, ExtractNoMatch_197) {
  std::string out;
  PCRE re("(\\d+)");
  bool extracted = PCRE::Extract("hello", re, "\\1", &out);
  EXPECT_FALSE(extracted);
}

TEST_F(PCRETest_197, ExtractWholeMatch_197) {
  std::string out;
  PCRE re("hello");
  bool extracted = PCRE::Extract("hello world", re, "\\0", &out);
  EXPECT_TRUE(extracted);
  EXPECT_EQ(out, "hello");
}

// =============================================================================
// CheckRewriteString Tests
// =============================================================================

TEST_F(PCRETest_197, CheckRewriteStringValid_197) {
  PCRE re("(a)(b)");
  std::string error;
  bool valid = re.CheckRewriteString("\\1-\\2", &error);
  EXPECT_TRUE(valid);
}

TEST_F(PCRETest_197, CheckRewriteStringInvalidBackref_197) {
  PCRE re("(a)");
  std::string error;
  bool valid = re.CheckRewriteString("\\3", &error);
  EXPECT_FALSE(valid);
  EXPECT_FALSE(error.empty());
}

TEST_F(PCRETest_197, CheckRewriteStringNoBackref_197) {
  PCRE re("hello");
  std::string error;
  bool valid = re.CheckRewriteString("replacement", &error);
  EXPECT_TRUE(valid);
}

// =============================================================================
// Pattern and Error accessors
// =============================================================================

TEST_F(PCRETest_197, PatternAccessor_197) {
  PCRE re("foo.*bar");
  EXPECT_EQ(re.pattern(), "foo.*bar");
}

TEST_F(PCRETest_197, ErrorEmptyForValidPattern_197) {
  PCRE re("valid");
  EXPECT_TRUE(re.error().empty());
}

TEST_F(PCRETest_197, ErrorNonEmptyForInvalidPattern_197) {
  PCRE re("[invalid");
  // An unclosed bracket should produce an error
  EXPECT_FALSE(re.error().empty());
}

// =============================================================================
// Invalid Pattern Tests
// =============================================================================

TEST_F(PCRETest_197, InvalidPatternDoMatchReturnsFalse_197) {
  PCRE re("[invalid");
  bool matched = re.DoMatch("test", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_FALSE(matched);
}

TEST_F(PCRETest_197, InvalidPatternNumberOfCapturingGroups_197) {
  PCRE re("[invalid");
  // Invalid pattern should return 0 or -1 capturing groups
  int groups = re.NumberOfCapturingGroups();
  EXPECT_LE(groups, 0);
}

// =============================================================================
// Complex Pattern Tests
// =============================================================================

TEST_F(PCRETest_197, DoMatchWithDigitPattern_197) {
  PCRE re("\\d+");
  bool matched = re.DoMatch("12345", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_TRUE(matched);
}

TEST_F(PCRETest_197, DoMatchWithDigitPatternFails_197) {
  PCRE re("\\d+");
  bool matched = re.DoMatch("abcde", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_FALSE(matched);
}

TEST_F(PCRETest_197, GlobalReplaceMultipleOccurrences_197) {
  std::string str = "the cat sat on the mat";
  PCRE re("the");
  int count = PCRE::GlobalReplace(&str, re, "a");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(str, "a cat sat on a mat");
}

TEST_F(PCRETest_197, ReplaceFirstOccurrenceOnly_197) {
  std::string str = "aabaa";
  PCRE re("a");
  bool replaced = PCRE::Replace(&str, re, "x");
  EXPECT_TRUE(replaced);
  EXPECT_EQ(str, "xabaa");
}

// =============================================================================
// QuoteMeta Roundtrip Tests
// =============================================================================

TEST_F(PCRETest_197, QuoteMetaRoundtrip_197) {
  std::string special = "a.b+c*d?e[f]g{h}i(j)k|l^m$n\\o";
  std::string quoted = PCRE::QuoteMeta(special);
  PCRE re(quoted);
  bool matched = re.DoMatch(special, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_TRUE(matched);
}

TEST_F(PCRETest_197, QuoteMetaRoundtripSimple_197) {
  std::string text = "hello.world";
  std::string quoted = PCRE::QuoteMeta(text);
  PCRE re(quoted);
  bool matched = re.DoMatch(text, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_TRUE(matched);
  // Should NOT match without the dot being literal
  bool wrong_match = re.DoMatch("helloXworld", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_FALSE(wrong_match);
}

}  // namespace re2
