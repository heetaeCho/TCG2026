#include "util/pcre.h"
#include <string>
#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

namespace re2 {

// ========== Construction and Pattern Access Tests ==========

TEST(PCRETest_173, ConstructFromCString_173) {
  PCRE re("hello");
  EXPECT_EQ("hello", re.pattern());
}

TEST(PCRETest_173, ConstructFromStdString_173) {
  std::string pat = "world";
  PCRE re(pat);
  EXPECT_EQ("world", re.pattern());
}

TEST(PCRETest_173, ConstructWithOption_173) {
  PCRE re("test", PCRE::UTF8);
  EXPECT_EQ("test", re.pattern());
}

TEST(PCRETest_173, ConstructFromStdStringWithOption_173) {
  std::string pat = "foo";
  PCRE re(pat, PCRE::UTF8);
  EXPECT_EQ("foo", re.pattern());
}

TEST(PCRETest_173, EmptyPattern_173) {
  PCRE re("");
  EXPECT_EQ("", re.pattern());
}

// ========== QuoteMeta Tests ==========

TEST(PCRETest_173, QuoteMetaSimple_173) {
  std::string result = PCRE::QuoteMeta("hello");
  EXPECT_EQ("hello", result);
}

TEST(PCRETest_173, QuoteMetaSpecialChars_173) {
  std::string result = PCRE::QuoteMeta("a.b*c+d?e");
  // Each special character should be escaped
  EXPECT_NE(std::string::npos, result.find("\\.")); 
  EXPECT_NE(std::string::npos, result.find("\\*"));
  EXPECT_NE(std::string::npos, result.find("\\+"));
  EXPECT_NE(std::string::npos, result.find("\\?"));
}

TEST(PCRETest_173, QuoteMetaEmpty_173) {
  std::string result = PCRE::QuoteMeta("");
  EXPECT_EQ("", result);
}

TEST(PCRETest_173, QuoteMetaBrackets_173) {
  std::string result = PCRE::QuoteMeta("[a]");
  EXPECT_NE(std::string::npos, result.find("\\["));
  EXPECT_NE(std::string::npos, result.find("\\]"));
}

// ========== DoMatch Tests ==========

TEST(PCRETest_173, DoMatchFullMatch_173) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_173, DoMatchFullMatchFail_173) {
  PCRE re("hello");
  EXPECT_FALSE(re.DoMatch("world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_173, DoMatchPartialMatch_173) {
  PCRE re("ell");
  EXPECT_TRUE(re.DoMatch("hello", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCRETest_173, DoMatchAnchorStart_173) {
  PCRE re("hel");
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCRETest_173, DoMatchAnchorStartFail_173) {
  PCRE re("llo");
  EXPECT_FALSE(re.DoMatch("hello", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCRETest_173, DoMatchWithConsumed_173) {
  PCRE re("hel");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_START, &consumed, nullptr, 0));
  EXPECT_EQ(3u, consumed);
}

TEST(PCRETest_173, DoMatchWithCapture_173) {
  PCRE re("(\\w+)@(\\w+)");
  std::string user, domain;
  const PCRE::Arg arg1(&user);
  const PCRE::Arg arg2(&domain);
  const PCRE::Arg* args[] = {&arg1, &arg2};
  EXPECT_TRUE(re.DoMatch("user@host", PCRE::ANCHOR_BOTH, nullptr, args, 2));
  EXPECT_EQ("user", user);
  EXPECT_EQ("host", domain);
}

TEST(PCRETest_173, DoMatchWithIntCapture_173) {
  PCRE re("(\\d+)");
  int value = 0;
  const PCRE::Arg arg1(&value);
  const PCRE::Arg* args[] = {&arg1};
  EXPECT_TRUE(re.DoMatch("12345", PCRE::ANCHOR_BOTH, nullptr, args, 1));
  EXPECT_EQ(12345, value);
}

TEST(PCRETest_173, DoMatchEmptyText_173) {
  PCRE re("");
  EXPECT_TRUE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_173, DoMatchEmptyPatternNonEmptyText_173) {
  PCRE re("");
  EXPECT_FALSE(re.DoMatch("abc", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

// ========== Replace Tests ==========

TEST(PCRETest_173, ReplaceSimple_173) {
  std::string s = "hello world";
  EXPECT_TRUE(PCRE::Replace(&s, PCRE("world"), "there"));
  EXPECT_EQ("hello there", s);
}

TEST(PCRETest_173, ReplaceNoMatch_173) {
  std::string s = "hello world";
  EXPECT_FALSE(PCRE::Replace(&s, PCRE("xyz"), "there"));
  EXPECT_EQ("hello world", s);
}

TEST(PCRETest_173, ReplaceWithBackreference_173) {
  std::string s = "hello world";
  EXPECT_TRUE(PCRE::Replace(&s, PCRE("(\\w+) (\\w+)"), "\\2 \\1"));
  EXPECT_EQ("world hello", s);
}

TEST(PCRETest_173, ReplaceFirstOccurrenceOnly_173) {
  std::string s = "aaa";
  EXPECT_TRUE(PCRE::Replace(&s, PCRE("a"), "b"));
  EXPECT_EQ("baa", s);
}

// ========== GlobalReplace Tests ==========

TEST(PCRETest_173, GlobalReplaceAll_173) {
  std::string s = "aaa";
  int count = PCRE::GlobalReplace(&s, PCRE("a"), "b");
  EXPECT_EQ(3, count);
  EXPECT_EQ("bbb", s);
}

TEST(PCRETest_173, GlobalReplaceNone_173) {
  std::string s = "aaa";
  int count = PCRE::GlobalReplace(&s, PCRE("x"), "b");
  EXPECT_EQ(0, count);
  EXPECT_EQ("aaa", s);
}

TEST(PCRETest_173, GlobalReplaceComplex_173) {
  std::string s = "abc 123 def 456";
  int count = PCRE::GlobalReplace(&s, PCRE("\\d+"), "NUM");
  EXPECT_EQ(2, count);
  EXPECT_EQ("abc NUM def NUM", s);
}

// ========== Extract Tests ==========

TEST(PCRETest_173, ExtractSimple_173) {
  std::string out;
  EXPECT_TRUE(PCRE::Extract("boris@kremlin.ru", PCRE("(.*)@([^.]*)"), "\\2!\\1", &out));
  EXPECT_EQ("kremlin!boris", out);
}

TEST(PCRETest_173, ExtractNoMatch_173) {
  std::string out;
  EXPECT_FALSE(PCRE::Extract("no match here", PCRE("(\\d+)@(\\d+)"), "\\1-\\2", &out));
}

// ========== CheckRewriteString Tests ==========

TEST(PCRETest_173, CheckRewriteStringValid_173) {
  PCRE re("(\\w+) (\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1-\\2", &error));
}

TEST(PCRETest_173, CheckRewriteStringInvalidBackref_173) {
  PCRE re("(\\w+)");
  std::string error;
  // \\2 references a non-existent group
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

TEST(PCRETest_173, CheckRewriteStringNoGroups_173) {
  PCRE re("\\w+");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\1", &error));
}

// ========== NumberOfCapturingGroups Tests ==========

TEST(PCRETest_173, NumberOfCapturingGroupsNone_173) {
  PCRE re("hello");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(PCRETest_173, NumberOfCapturingGroupsOne_173) {
  PCRE re("(hello)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(PCRETest_173, NumberOfCapturingGroupsMultiple_173) {
  PCRE re("(a)(b)(c)");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(PCRETest_173, NumberOfCapturingGroupsNested_173) {
  PCRE re("((a)(b))");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

// ========== HitLimit / ClearHitLimit Tests ==========

TEST(PCRETest_173, HitLimitInitiallyFalse_173) {
  PCRE re("test");
  EXPECT_FALSE(re.HitLimit());
}

TEST(PCRETest_173, ClearHitLimit_173) {
  PCRE re("test");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// ========== Error Tests ==========

TEST(PCRETest_173, ErrorOnValidPattern_173) {
  PCRE re("hello");
  EXPECT_TRUE(re.error().empty());
}

TEST(PCRETest_173, ErrorOnInvalidPattern_173) {
  PCRE re("[invalid");
  EXPECT_FALSE(re.error().empty());
}

// ========== Complex Pattern Tests ==========

TEST(PCRETest_173, ComplexPatternMatch_173) {
  PCRE re("^(\\d{4})-(\\d{2})-(\\d{2})$");
  std::string year, month, day;
  const PCRE::Arg arg1(&year);
  const PCRE::Arg arg2(&month);
  const PCRE::Arg arg3(&day);
  const PCRE::Arg* args[] = {&arg1, &arg2, &arg3};
  EXPECT_TRUE(re.DoMatch("2023-12-25", PCRE::ANCHOR_BOTH, nullptr, args, 3));
  EXPECT_EQ("2023", year);
  EXPECT_EQ("12", month);
  EXPECT_EQ("25", day);
}

TEST(PCRETest_173, UnanchoredMatchInMiddle_173) {
  PCRE re("(\\d+)");
  std::string num;
  const PCRE::Arg arg1(&num);
  const PCRE::Arg* args[] = {&arg1};
  EXPECT_TRUE(re.DoMatch("abc123def", PCRE::UNANCHORED, nullptr, args, 1));
  EXPECT_EQ("123", num);
}

TEST(PCRETest_173, SpecialCharactersInPattern_173) {
  PCRE re("a\\.b");
  EXPECT_TRUE(re.DoMatch("a.b", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch("axb", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

// ========== Replace with empty string ==========

TEST(PCRETest_173, ReplaceWithEmptyString_173) {
  std::string s = "hello world";
  EXPECT_TRUE(PCRE::Replace(&s, PCRE("world"), ""));
  EXPECT_EQ("hello ", s);
}

TEST(PCRETest_173, GlobalReplaceWithEmptyString_173) {
  std::string s = "aXbXc";
  int count = PCRE::GlobalReplace(&s, PCRE("X"), "");
  EXPECT_EQ(2, count);
  EXPECT_EQ("abc", s);
}

}  // namespace re2
