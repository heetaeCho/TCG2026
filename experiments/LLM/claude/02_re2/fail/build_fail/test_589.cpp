#include <string>
#include "gtest/gtest.h"
#include "util/pcre.h"

namespace re2 {

// ============================================================
// Construction Tests
// ============================================================

TEST(PCREConstructionTest_589, ConstructFromCString_589) {
  PCRE re("hello");
  EXPECT_EQ(re.pattern(), "hello");
  EXPECT_EQ(re.error(), "");
}

TEST(PCREConstructionTest_589, ConstructFromStdString_589) {
  std::string pat = "world";
  PCRE re(pat);
  EXPECT_EQ(re.pattern(), "world");
  EXPECT_EQ(re.error(), "");
}

TEST(PCREConstructionTest_589, ConstructWithOption_589) {
  PCRE re("test", PCRE::UTF8);
  EXPECT_EQ(re.pattern(), "test");
}

TEST(PCREConstructionTest_589, ConstructFromStdStringWithOption_589) {
  std::string pat = "abc";
  PCRE re(pat, PCRE::UTF8);
  EXPECT_EQ(re.pattern(), "abc");
}

TEST(PCREConstructionTest_589, EmptyPattern_589) {
  PCRE re("");
  EXPECT_EQ(re.pattern(), "");
}

// ============================================================
// Pattern and Error Tests
// ============================================================

TEST(PCREPatternTest_589, PatternReturnsOriginal_589) {
  PCRE re("(\\d+)-(\\w+)");
  EXPECT_EQ(re.pattern(), "(\\d+)-(\\w+)");
}

TEST(PCREPatternTest_589, InvalidPatternSetsError_589) {
  // Unmatched parenthesis should produce an error
  PCRE re("(abc");
  EXPECT_FALSE(re.error().empty());
}

// ============================================================
// NumberOfCapturingGroups Tests
// ============================================================

TEST(PCRECapturingGroupsTest_589, NoCapturingGroups_589) {
  PCRE re("abc");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(PCRECapturingGroupsTest_589, OneCapturingGroup_589) {
  PCRE re("(abc)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(PCRECapturingGroupsTest_589, MultipleCapturingGroups_589) {
  PCRE re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(PCRECapturingGroupsTest_589, NestedCapturingGroups_589) {
  PCRE re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(PCRECapturingGroupsTest_589, InvalidPatternReturnsNegative_589) {
  PCRE re("(abc");
  // Invalid pattern should return a negative value or error indicator
  EXPECT_LE(re.NumberOfCapturingGroups(), 0);
}

// ============================================================
// DoMatch Tests
// ============================================================

TEST(PCREDoMatchTest_589, SimpleMatchUnanchored_589) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_589, SimpleMatchAnchBoth_589) {
  PCRE re("hello");
  EXPECT_FALSE(re.DoMatch("hello world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_589, FullMatchAnchBoth_589) {
  PCRE re("hello world");
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_589, AnchorStart_589) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_589, AnchorStartFails_589) {
  PCRE re("world");
  EXPECT_FALSE(re.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_589, NoMatch_589) {
  PCRE re("xyz");
  EXPECT_FALSE(re.DoMatch("hello world", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_589, EmptyPatternMatchesEmpty_589) {
  PCRE re("");
  EXPECT_TRUE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_589, EmptyPatternMatchesNonEmpty_589) {
  PCRE re("");
  EXPECT_TRUE(re.DoMatch("abc", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_589, MatchWithConsumed_589) {
  PCRE re("hel+o");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_START, &consumed, nullptr, 0));
  EXPECT_EQ(consumed, 5u);
}

TEST(PCREDoMatchTest_589, MatchWithCapturingArg_589) {
  PCRE re("(\\d+)");
  int value = 0;
  PCRE::Arg arg(&value);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch("abc 123 def", PCRE::UNANCHORED, nullptr, args, 1));
  EXPECT_EQ(value, 123);
}

TEST(PCREDoMatchTest_589, MatchWithStringCapture_589) {
  PCRE re("(\\w+)");
  std::string captured;
  PCRE::Arg arg(&captured);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::UNANCHORED, nullptr, args, 1));
  EXPECT_EQ(captured, "hello");
}

TEST(PCREDoMatchTest_589, MatchWithMultipleCaptures_589) {
  PCRE re("(\\w+)\\s+(\\w+)");
  std::string s1, s2;
  PCRE::Arg arg1(&s1);
  PCRE::Arg arg2(&s2);
  const PCRE::Arg* args[] = {&arg1, &arg2};
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_BOTH, nullptr, args, 2));
  EXPECT_EQ(s1, "hello");
  EXPECT_EQ(s2, "world");
}

// ============================================================
// Replace Tests
// ============================================================

TEST(PCREReplaceTest_589, SimpleReplace_589) {
  std::string str = "hello world";
  PCRE re("world");
  EXPECT_TRUE(PCRE::Replace(&str, re, "there"));
  EXPECT_EQ(str, "hello there");
}

TEST(PCREReplaceTest_589, ReplaceNoMatch_589) {
  std::string str = "hello world";
  PCRE re("xyz");
  EXPECT_FALSE(PCRE::Replace(&str, re, "there"));
  EXPECT_EQ(str, "hello world");
}

TEST(PCREReplaceTest_589, ReplaceWithBackreference_589) {
  std::string str = "hello world";
  PCRE re("(\\w+) (\\w+)");
  EXPECT_TRUE(PCRE::Replace(&str, re, "\\2 \\1"));
  EXPECT_EQ(str, "world hello");
}

TEST(PCREReplaceTest_589, ReplaceFirstOnly_589) {
  std::string str = "aaa";
  PCRE re("a");
  EXPECT_TRUE(PCRE::Replace(&str, re, "b"));
  EXPECT_EQ(str, "baa");
}

// ============================================================
// GlobalReplace Tests
// ============================================================

TEST(PCREGlobalReplaceTest_589, ReplaceAll_589) {
  std::string str = "aaa";
  PCRE re("a");
  int count = PCRE::GlobalReplace(&str, re, "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "bbb");
}

TEST(PCREGlobalReplaceTest_589, GlobalReplaceNoMatch_589) {
  std::string str = "hello";
  PCRE re("xyz");
  int count = PCRE::GlobalReplace(&str, re, "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

TEST(PCREGlobalReplaceTest_589, GlobalReplaceMultiple_589) {
  std::string str = "a1b2c3";
  PCRE re("\\d");
  int count = PCRE::GlobalReplace(&str, re, "X");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "aXbXcX");
}

// ============================================================
// Extract Tests
// ============================================================

TEST(PCREExtractTest_589, SimpleExtract_589) {
  std::string out;
  PCRE re("(\\w+)@(\\w+)");
  EXPECT_TRUE(PCRE::Extract("user@host", re, "\\1 at \\2", &out));
  EXPECT_EQ(out, "user at host");
}

TEST(PCREExtractTest_589, ExtractNoMatch_589) {
  std::string out;
  PCRE re("(\\d+)");
  EXPECT_FALSE(PCRE::Extract("no digits here", re, "\\1", &out));
}

TEST(PCREExtractTest_589, ExtractWholeMatch_589) {
  std::string out;
  PCRE re("\\d+");
  EXPECT_TRUE(PCRE::Extract("abc 123 def", re, "\\0", &out));
  EXPECT_EQ(out, "123");
}

// ============================================================
// QuoteMeta Tests
// ============================================================

TEST(PCREQuoteMetaTest_589, NoSpecialCharacters_589) {
  std::string result = PCRE::QuoteMeta("hello");
  EXPECT_EQ(result, "hello");
}

TEST(PCREQuoteMetaTest_589, SpecialCharactersEscaped_589) {
  std::string result = PCRE::QuoteMeta("a.b");
  // The dot should be escaped
  PCRE re(result);
  EXPECT_TRUE(re.DoMatch("a.b", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch("axb", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREQuoteMetaTest_589, EmptyString_589) {
  std::string result = PCRE::QuoteMeta("");
  EXPECT_EQ(result, "");
}

TEST(PCREQuoteMetaTest_589, AllSpecialChars_589) {
  std::string input = "[](){}.*+?|^$\\";
  std::string result = PCRE::QuoteMeta(input);
  PCRE re(result);
  EXPECT_TRUE(re.DoMatch(input, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

// ============================================================
// CheckRewriteString Tests
// ============================================================

TEST(PCRECheckRewriteTest_589, ValidRewrite_589) {
  PCRE re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(PCRECheckRewriteTest_589, RewriteWithNoBackref_589) {
  PCRE re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("literal", &error));
}

TEST(PCRECheckRewriteTest_589, InvalidBackref_589) {
  PCRE re("(\\w+)");
  std::string error;
  // \\2 references a group that doesn't exist (only 1 group)
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

TEST(PCRECheckRewriteTest_589, ZeroBackref_589) {
  PCRE re("\\w+");
  std::string error;
  // \\0 refers to the whole match, should be valid
  EXPECT_TRUE(re.CheckRewriteString("\\0", &error));
}

// ============================================================
// HitLimit and ClearHitLimit Tests
// ============================================================

TEST(PCREHitLimitTest_589, InitiallyNoHitLimit_589) {
  PCRE re("abc");
  EXPECT_FALSE(re.HitLimit());
}

TEST(PCREHitLimitTest_589, ClearHitLimitWhenNotSet_589) {
  PCRE re("abc");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// ============================================================
// Edge Cases
// ============================================================

TEST(PCREEdgeCaseTest_589, MatchEmptyText_589) {
  PCRE re(".*");
  EXPECT_TRUE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREEdgeCaseTest_589, ComplexPattern_589) {
  PCRE re("^(\\d{4})-(\\d{2})-(\\d{2})$");
  std::string year, month, day;
  PCRE::Arg arg1(&year);
  PCRE::Arg arg2(&month);
  PCRE::Arg arg3(&day);
  const PCRE::Arg* args[] = {&arg1, &arg2, &arg3};
  EXPECT_TRUE(re.DoMatch("2023-01-15", PCRE::ANCHOR_BOTH, nullptr, args, 3));
  EXPECT_EQ(year, "2023");
  EXPECT_EQ(month, "01");
  EXPECT_EQ(day, "15");
}

TEST(PCREEdgeCaseTest_589, PatternWithSpecialChars_589) {
  PCRE re("\\d+\\.\\d+");
  EXPECT_TRUE(re.DoMatch("3.14", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch("3x14", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREEdgeCaseTest_589, LongString_589) {
  std::string longStr(10000, 'a');
  PCRE re("a+");
  EXPECT_TRUE(re.DoMatch(longStr, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREEdgeCaseTest_589, UnicodeInPattern_589) {
  // Test basic non-ascii handling
  PCRE re("café");
  EXPECT_TRUE(re.DoMatch("café", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

}  // namespace re2
