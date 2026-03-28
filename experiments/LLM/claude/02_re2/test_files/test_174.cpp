#include "util/pcre.h"
#include <string>
#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

namespace re2 {

// ============================================================
// Construction Tests
// ============================================================

TEST(PCREConstructionTest_174, ConstructFromCString_174) {
  PCRE re("hello");
  EXPECT_EQ(re.pattern(), "hello");
  EXPECT_EQ(re.error(), "");
}

TEST(PCREConstructionTest_174, ConstructFromStdString_174) {
  std::string pat = "world";
  PCRE re(pat);
  EXPECT_EQ(re.pattern(), "world");
  EXPECT_EQ(re.error(), "");
}

TEST(PCREConstructionTest_174, ConstructWithOption_174) {
  PCRE re("test", PCRE::UNANCHORED);
  EXPECT_EQ(re.pattern(), "test");
  EXPECT_EQ(re.error(), "");
}

TEST(PCREConstructionTest_174, ConstructFromStdStringWithOption_174) {
  std::string pat = "test2";
  PCRE re(pat, PCRE::UNANCHORED);
  EXPECT_EQ(re.pattern(), "test2");
  EXPECT_EQ(re.error(), "");
}

TEST(PCREConstructionTest_174, InvalidPatternReportsError_174) {
  PCRE re("[invalid");
  EXPECT_FALSE(re.error().empty());
}

// ============================================================
// Pattern and Error Tests
// ============================================================

TEST(PCREPatternTest_174, PatternReturnsOriginalPattern_174) {
  PCRE re("(\\d+)-(\\w+)");
  EXPECT_EQ(re.pattern(), "(\\d+)-(\\w+)");
}

TEST(PCREPatternTest_174, EmptyPattern_174) {
  PCRE re("");
  EXPECT_EQ(re.pattern(), "");
  EXPECT_EQ(re.error(), "");
}

// ============================================================
// NumberOfCapturingGroups Tests
// ============================================================

TEST(PCRECapturingGroupsTest_174, NoCapturingGroups_174) {
  PCRE re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(PCRECapturingGroupsTest_174, OneCapturingGroup_174) {
  PCRE re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(PCRECapturingGroupsTest_174, MultipleCapturingGroups_174) {
  PCRE re("(\\d+)-(\\w+)-(\\S+)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(PCRECapturingGroupsTest_174, NonCapturingGroupNotCounted_174) {
  PCRE re("(?:hello)(world)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

// ============================================================
// DoMatch Tests
// ============================================================

TEST(PCREDoMatchTest_174, SimpleFullMatch_174) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_174, SimpleFullMatchFails_174) {
  PCRE re("hello");
  EXPECT_FALSE(re.DoMatch("world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_174, UnanchoredMatch_174) {
  PCRE re("ell");
  EXPECT_TRUE(re.DoMatch("hello", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_174, AnchorStartMatch_174) {
  PCRE re("hel");
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_174, AnchorStartMatchFails_174) {
  PCRE re("ell");
  EXPECT_FALSE(re.DoMatch("hello", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_174, MatchWithConsumed_174) {
  PCRE re("hel");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_START, &consumed, nullptr, 0));
  EXPECT_EQ(consumed, 3u);
}

TEST(PCREDoMatchTest_174, MatchWithCapturingArg_174) {
  PCRE re("(\\d+)");
  int value = 0;
  PCRE::Arg arg(&value);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch("12345", PCRE::ANCHOR_BOTH, nullptr, args, 1));
  EXPECT_EQ(value, 12345);
}

TEST(PCREDoMatchTest_174, MatchWithStringArg_174) {
  PCRE re("(\\w+)");
  std::string value;
  PCRE::Arg arg(&value);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, args, 1));
  EXPECT_EQ(value, "hello");
}

TEST(PCREDoMatchTest_174, EmptyTextEmptyPattern_174) {
  PCRE re("");
  EXPECT_TRUE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_174, EmptyTextNonEmptyPattern_174) {
  PCRE re("hello");
  EXPECT_FALSE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

// ============================================================
// Replace Tests
// ============================================================

TEST(PCREReplaceTest_174, SimpleReplace_174) {
  std::string str = "hello world";
  PCRE re("world");
  EXPECT_TRUE(PCRE::Replace(&str, re, "there"));
  EXPECT_EQ(str, "hello there");
}

TEST(PCREReplaceTest_174, ReplaceWithCapture_174) {
  std::string str = "hello world";
  PCRE re("(\\w+) (\\w+)");
  EXPECT_TRUE(PCRE::Replace(&str, re, "\\2 \\1"));
  EXPECT_EQ(str, "world hello");
}

TEST(PCREReplaceTest_174, ReplaceNoMatch_174) {
  std::string str = "hello world";
  PCRE re("xyz");
  EXPECT_FALSE(PCRE::Replace(&str, re, "abc"));
  EXPECT_EQ(str, "hello world");
}

TEST(PCREReplaceTest_174, ReplaceFirstOccurrenceOnly_174) {
  std::string str = "aaa";
  PCRE re("a");
  EXPECT_TRUE(PCRE::Replace(&str, re, "b"));
  EXPECT_EQ(str, "baa");
}

// ============================================================
// GlobalReplace Tests
// ============================================================

TEST(PCREGlobalReplaceTest_174, ReplaceAllOccurrences_174) {
  std::string str = "aaa";
  PCRE re("a");
  int count = PCRE::GlobalReplace(&str, re, "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "bbb");
}

TEST(PCREGlobalReplaceTest_174, GlobalReplaceNoMatch_174) {
  std::string str = "hello";
  PCRE re("xyz");
  int count = PCRE::GlobalReplace(&str, re, "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

TEST(PCREGlobalReplaceTest_174, GlobalReplaceWithCapture_174) {
  std::string str = "abc def ghi";
  PCRE re("(\\w+)");
  int count = PCRE::GlobalReplace(&str, re, "[\\1]");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "[abc] [def] [ghi]");
}

// ============================================================
// Extract Tests
// ============================================================

TEST(PCREExtractTest_174, SimpleExtract_174) {
  std::string out;
  PCRE re("(\\w+)@(\\w+)");
  EXPECT_TRUE(PCRE::Extract("user@host", re, "\\1 at \\2", &out));
  EXPECT_EQ(out, "user at host");
}

TEST(PCREExtractTest_174, ExtractNoMatch_174) {
  std::string out;
  PCRE re("(\\d+)");
  EXPECT_FALSE(PCRE::Extract("hello", re, "\\1", &out));
}

TEST(PCREExtractTest_174, ExtractEntireMatch_174) {
  std::string out;
  PCRE re("\\d+");
  EXPECT_TRUE(PCRE::Extract("abc123def", re, "\\0", &out));
  EXPECT_EQ(out, "123");
}

// ============================================================
// QuoteMeta Tests
// ============================================================

TEST(PCREQuoteMetaTest_174, PlainString_174) {
  std::string quoted = PCRE::QuoteMeta("hello");
  EXPECT_EQ(quoted, "hello");
}

TEST(PCREQuoteMetaTest_174, SpecialCharacters_174) {
  std::string quoted = PCRE::QuoteMeta("a.b*c+d?e");
  // The quoted string should match literally
  PCRE re(quoted);
  EXPECT_TRUE(re.DoMatch("a.b*c+d?e", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREQuoteMetaTest_174, EmptyString_174) {
  std::string quoted = PCRE::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

TEST(PCREQuoteMetaTest_174, AllSpecialChars_174) {
  std::string special = "[](){}.*+?|^$\\";
  std::string quoted = PCRE::QuoteMeta(special);
  PCRE re(quoted);
  EXPECT_TRUE(re.DoMatch(special, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

// ============================================================
// CheckRewriteString Tests
// ============================================================

TEST(PCRECheckRewriteTest_174, ValidRewriteString_174) {
  PCRE re("(\\w+) (\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1-\\2", &error));
  EXPECT_EQ(error, "");
}

TEST(PCRECheckRewriteTest_174, RewriteStringWithTooHighBackref_174) {
  PCRE re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

TEST(PCRECheckRewriteTest_174, RewriteStringNoBackrefs_174) {
  PCRE re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("replacement", &error));
}

// ============================================================
// HitLimit / ClearHitLimit Tests
// ============================================================

TEST(PCREHitLimitTest_174, InitiallyNoHitLimit_174) {
  PCRE re("hello");
  EXPECT_FALSE(re.HitLimit());
}

TEST(PCREHitLimitTest_174, ClearHitLimitOnFreshObject_174) {
  PCRE re("hello");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// ============================================================
// Boundary / Edge Cases
// ============================================================

TEST(PCREEdgeCaseTest_174, VeryLongPattern_174) {
  std::string long_pattern(1000, 'a');
  PCRE re(long_pattern);
  EXPECT_EQ(re.error(), "");
  std::string long_text(1000, 'a');
  EXPECT_TRUE(re.DoMatch(long_text, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREEdgeCaseTest_174, PatternWithNewlines_174) {
  PCRE re("hello\nworld");
  EXPECT_TRUE(re.DoMatch("hello\nworld", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREEdgeCaseTest_174, UnicodeInPattern_174) {
  PCRE re("café");
  EXPECT_TRUE(re.DoMatch("café", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREEdgeCaseTest_174, MultipleCapturingGroupsExtraction_174) {
  PCRE re("(\\d{4})-(\\d{2})-(\\d{2})");
  int year = 0, month = 0, day = 0;
  PCRE::Arg arg1(&year), arg2(&month), arg3(&day);
  const PCRE::Arg* args[] = {&arg1, &arg2, &arg3};
  EXPECT_TRUE(re.DoMatch("2024-01-15", PCRE::ANCHOR_BOTH, nullptr, args, 3));
  EXPECT_EQ(year, 2024);
  EXPECT_EQ(month, 1);
  EXPECT_EQ(day, 15);
}

TEST(PCREEdgeCaseTest_174, PartialMatchWithConsumed_174) {
  PCRE re("\\d+");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch("123abc", PCRE::ANCHOR_START, &consumed, nullptr, 0));
  EXPECT_EQ(consumed, 3u);
}

TEST(PCREEdgeCaseTest_174, GlobalReplaceEmptyMatch_174) {
  std::string str = "abc";
  PCRE re("b*");
  // Empty matches can be tricky; just ensure it doesn't crash
  PCRE::GlobalReplace(&str, re, "x");
  // The result depends on implementation, but it should not crash
}

TEST(PCREEdgeCaseTest_174, ReplaceWithEmptyRewrite_174) {
  std::string str = "hello world";
  PCRE re("world");
  EXPECT_TRUE(PCRE::Replace(&str, re, ""));
  EXPECT_EQ(str, "hello ");
}

TEST(PCREEdgeCaseTest_174, FullMatchAnchored_174) {
  PCRE re("abc");
  EXPECT_FALSE(re.DoMatch("abcd", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch("abc", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

}  // namespace re2
