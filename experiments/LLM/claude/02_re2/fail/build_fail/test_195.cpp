#include "gtest/gtest.h"
#include "util/pcre.h"
#include <string>

namespace re2 {

class PCRETest_195 : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Extract Tests ====================

TEST_F(PCRETest_195, ExtractSimpleMatch_195) {
  std::string out;
  bool result = PCRE::Extract("hello world", PCRE("(\\w+)\\s+(\\w+)"), "\\2 \\1", &out);
  EXPECT_TRUE(result);
  EXPECT_EQ("world hello", out);
}

TEST_F(PCRETest_195, ExtractNoMatch_195) {
  std::string out;
  bool result = PCRE::Extract("hello", PCRE("(\\d+)"), "\\1", &out);
  EXPECT_FALSE(result);
}

TEST_F(PCRETest_195, ExtractEmptyText_195) {
  std::string out;
  bool result = PCRE::Extract("", PCRE("(.+)"), "\\1", &out);
  EXPECT_FALSE(result);
}

TEST_F(PCRETest_195, ExtractFullMatch_195) {
  std::string out;
  bool result = PCRE::Extract("12345", PCRE("(\\d+)"), "number=\\1", &out);
  EXPECT_TRUE(result);
  EXPECT_EQ("number=12345", out);
}

TEST_F(PCRETest_195, ExtractWithLiteralRewrite_195) {
  std::string out;
  bool result = PCRE::Extract("abc", PCRE("(abc)"), "found", &out);
  EXPECT_TRUE(result);
  EXPECT_EQ("found", out);
}

TEST_F(PCRETest_195, ExtractPartialText_195) {
  std::string out;
  bool result = PCRE::Extract("foo123bar", PCRE("(\\d+)"), "digits=\\1", &out);
  EXPECT_TRUE(result);
  EXPECT_EQ("digits=123", out);
}

// ==================== Replace Tests ====================

TEST_F(PCRETest_195, ReplaceSimple_195) {
  std::string str = "hello world";
  bool result = PCRE::Replace(&str, PCRE("world"), "there");
  EXPECT_TRUE(result);
  EXPECT_EQ("hello there", str);
}

TEST_F(PCRETest_195, ReplaceNoMatch_195) {
  std::string str = "hello world";
  bool result = PCRE::Replace(&str, PCRE("xyz"), "replaced");
  EXPECT_FALSE(result);
  EXPECT_EQ("hello world", str);
}

TEST_F(PCRETest_195, ReplaceWithCapture_195) {
  std::string str = "hello world";
  bool result = PCRE::Replace(&str, PCRE("(\\w+)"), "[\\1]");
  EXPECT_TRUE(result);
  EXPECT_EQ("[hello] world", str);
}

TEST_F(PCRETest_195, ReplaceEmptyString_195) {
  std::string str = "";
  bool result = PCRE::Replace(&str, PCRE("(.+)"), "\\1");
  EXPECT_FALSE(result);
}

// ==================== GlobalReplace Tests ====================

TEST_F(PCRETest_195, GlobalReplaceAll_195) {
  std::string str = "aaa";
  int count = PCRE::GlobalReplace(&str, PCRE("a"), "b");
  EXPECT_EQ(3, count);
  EXPECT_EQ("bbb", str);
}

TEST_F(PCRETest_195, GlobalReplaceNone_195) {
  std::string str = "hello";
  int count = PCRE::GlobalReplace(&str, PCRE("\\d"), "x");
  EXPECT_EQ(0, count);
  EXPECT_EQ("hello", str);
}

TEST_F(PCRETest_195, GlobalReplaceMultiple_195) {
  std::string str = "a1b2c3";
  int count = PCRE::GlobalReplace(&str, PCRE("\\d"), "#");
  EXPECT_EQ(3, count);
  EXPECT_EQ("a#b#c#", str);
}

// ==================== QuoteMeta Tests ====================

TEST_F(PCRETest_195, QuoteMetaNoSpecialChars_195) {
  std::string result = PCRE::QuoteMeta("hello");
  EXPECT_EQ("hello", result);
}

TEST_F(PCRETest_195, QuoteMetaWithSpecialChars_195) {
  std::string result = PCRE::QuoteMeta("a.b");
  // The dot should be escaped
  PCRE pattern(result);
  std::string str = "axb";
  bool matched = PCRE::Replace(&str, pattern, "replaced");
  EXPECT_FALSE(matched);
}

TEST_F(PCRETest_195, QuoteMetaEmpty_195) {
  std::string result = PCRE::QuoteMeta("");
  EXPECT_EQ("", result);
}

TEST_F(PCRETest_195, QuoteMetaWithBackslash_195) {
  std::string result = PCRE::QuoteMeta("a\\b");
  // Backslash should be escaped
  EXPECT_NE(std::string::npos, result.find("\\\\"));
}

// ==================== CheckRewriteString Tests ====================

TEST_F(PCRETest_195, CheckRewriteStringValid_195) {
  PCRE pattern("(\\w+)\\s+(\\w+)");
  std::string error;
  bool valid = pattern.CheckRewriteString("\\1 and \\2", &error);
  EXPECT_TRUE(valid);
}

TEST_F(PCRETest_195, CheckRewriteStringInvalidRef_195) {
  PCRE pattern("(\\w+)");
  std::string error;
  bool valid = pattern.CheckRewriteString("\\2", &error);
  EXPECT_FALSE(valid);
}

TEST_F(PCRETest_195, CheckRewriteStringNoCaptures_195) {
  PCRE pattern("hello");
  std::string error;
  bool valid = pattern.CheckRewriteString("\\1", &error);
  EXPECT_FALSE(valid);
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST_F(PCRETest_195, NumberOfCapturingGroupsNone_195) {
  PCRE pattern("hello");
  EXPECT_EQ(0, pattern.NumberOfCapturingGroups());
}

TEST_F(PCRETest_195, NumberOfCapturingGroupsOne_195) {
  PCRE pattern("(hello)");
  EXPECT_EQ(1, pattern.NumberOfCapturingGroups());
}

TEST_F(PCRETest_195, NumberOfCapturingGroupsMultiple_195) {
  PCRE pattern("(a)(b)(c)");
  EXPECT_EQ(3, pattern.NumberOfCapturingGroups());
}

TEST_F(PCRETest_195, NumberOfCapturingGroupsNested_195) {
  PCRE pattern("((a)(b))");
  EXPECT_EQ(3, pattern.NumberOfCapturingGroups());
}

// ==================== pattern() and error() Tests ====================

TEST_F(PCRETest_195, PatternReturnsOriginal_195) {
  PCRE p("hello.*world");
  EXPECT_EQ("hello.*world", p.pattern());
}

TEST_F(PCRETest_195, PatternFromString_195) {
  std::string pat = "(\\d+)";
  PCRE p(pat);
  EXPECT_EQ(pat, p.pattern());
}

TEST_F(PCRETest_195, ErrorOnValidPattern_195) {
  PCRE p("hello");
  EXPECT_TRUE(p.error().empty());
}

// ==================== HitLimit and ClearHitLimit Tests ====================

TEST_F(PCRETest_195, HitLimitInitiallyFalse_195) {
  PCRE p("test");
  EXPECT_FALSE(p.HitLimit());
}

TEST_F(PCRETest_195, ClearHitLimitNoEffect_195) {
  PCRE p("test");
  p.ClearHitLimit();
  EXPECT_FALSE(p.HitLimit());
}

// ==================== DoMatch Tests ====================

TEST_F(PCRETest_195, DoMatchAnchored_195) {
  PCRE p("hello");
  bool result = p.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0);
  EXPECT_TRUE(result);
}

TEST_F(PCRETest_195, DoMatchUnanchored_195) {
  PCRE p("world");
  bool result = p.DoMatch("hello world", PCRE::UNANCHORED, nullptr, nullptr, 0);
  EXPECT_TRUE(result);
}

TEST_F(PCRETest_195, DoMatchAnchorBoth_195) {
  PCRE p("hello");
  bool result = p.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_TRUE(result);
}

TEST_F(PCRETest_195, DoMatchAnchorBothFails_195) {
  PCRE p("hello");
  bool result = p.DoMatch("hello world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_FALSE(result);
}

TEST_F(PCRETest_195, DoMatchNoMatch_195) {
  PCRE p("xyz");
  bool result = p.DoMatch("hello world", PCRE::UNANCHORED, nullptr, nullptr, 0);
  EXPECT_FALSE(result);
}

TEST_F(PCRETest_195, DoMatchWithConsumed_195) {
  PCRE p("hello");
  size_t consumed = 0;
  bool result = p.DoMatch("hello world", PCRE::ANCHOR_START, &consumed, nullptr, 0);
  EXPECT_TRUE(result);
  EXPECT_EQ(5u, consumed);
}

// ==================== Constructor Tests ====================

TEST_F(PCRETest_195, ConstructFromCString_195) {
  PCRE p("test");
  EXPECT_EQ("test", p.pattern());
}

TEST_F(PCRETest_195, ConstructFromStdString_195) {
  std::string pat = "test";
  PCRE p(pat);
  EXPECT_EQ("test", p.pattern());
}

// ==================== Extract with Multiple Captures ====================

TEST_F(PCRETest_195, ExtractMultipleCaptures_195) {
  std::string out;
  bool result = PCRE::Extract("2023-12-25", PCRE("(\\d+)-(\\d+)-(\\d+)"), "\\3/\\2/\\1", &out);
  EXPECT_TRUE(result);
  EXPECT_EQ("25/12/2023", out);
}

// ==================== Edge Cases ====================

TEST_F(PCRETest_195, ExtractSpecialCharactersInText_195) {
  std::string out;
  bool result = PCRE::Extract("price: $100", PCRE("\\$(\\d+)"), "\\1 dollars", &out);
  EXPECT_TRUE(result);
  EXPECT_EQ("100 dollars", out);
}

TEST_F(PCRETest_195, ReplaceOnlyFirst_195) {
  std::string str = "aaa";
  bool result = PCRE::Replace(&str, PCRE("a"), "b");
  EXPECT_TRUE(result);
  EXPECT_EQ("baa", str);
}

TEST_F(PCRETest_195, GlobalReplaceWithCapture_195) {
  std::string str = "cat dog bird";
  int count = PCRE::GlobalReplace(&str, PCRE("(\\w+)"), "[\\1]");
  EXPECT_EQ(3, count);
  EXPECT_EQ("[cat] [dog] [bird]", str);
}

}  // namespace re2
