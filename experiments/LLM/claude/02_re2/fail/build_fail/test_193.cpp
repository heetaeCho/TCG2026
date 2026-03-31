#include <string>
#include "gtest/gtest.h"
#include "util/pcre.h"

namespace re2 {

// ==================== Replace Tests ====================

TEST(PCREReplace_193, BasicReplacement_193) {
  std::string s = "hello world";
  EXPECT_TRUE(PCRE::Replace(&s, PCRE("world"), "there"));
  EXPECT_EQ(s, "hello there");
}

TEST(PCREReplace_193, NoMatch_193) {
  std::string s = "hello world";
  EXPECT_FALSE(PCRE::Replace(&s, PCRE("xyz"), "replaced"));
  EXPECT_EQ(s, "hello world");
}

TEST(PCREReplace_193, ReplaceFirstOccurrenceOnly_193) {
  std::string s = "aaa";
  EXPECT_TRUE(PCRE::Replace(&s, PCRE("a"), "b"));
  EXPECT_EQ(s, "baa");
}

TEST(PCREReplace_193, ReplaceWithEmptyString_193) {
  std::string s = "hello world";
  EXPECT_TRUE(PCRE::Replace(&s, PCRE("world"), ""));
  EXPECT_EQ(s, "hello ");
}

TEST(PCREReplace_193, ReplaceEmptyPattern_193) {
  std::string s = "hello";
  // Empty pattern matches at the beginning
  EXPECT_TRUE(PCRE::Replace(&s, PCRE(""), "X"));
  EXPECT_EQ(s, "Xhello");
}

TEST(PCREReplace_193, ReplaceWithBackreference_193) {
  std::string s = "hello world";
  EXPECT_TRUE(PCRE::Replace(&s, PCRE("(\\w+)\\s(\\w+)"), "\\2 \\1"));
  EXPECT_EQ(s, "world hello");
}

TEST(PCREReplace_193, ReplaceOnEmptyString_193) {
  std::string s = "";
  EXPECT_TRUE(PCRE::Replace(&s, PCRE(""), "X"));
  EXPECT_EQ(s, "X");
}

TEST(PCREReplace_193, ReplacePartialMatch_193) {
  std::string s = "abc123def";
  EXPECT_TRUE(PCRE::Replace(&s, PCRE("\\d+"), "NUM"));
  EXPECT_EQ(s, "abcNUMdef");
}

// ==================== GlobalReplace Tests ====================

TEST(PCREGlobalReplace_193, ReplaceAll_193) {
  std::string s = "aaa";
  int count = PCRE::GlobalReplace(&s, PCRE("a"), "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "bbb");
}

TEST(PCREGlobalReplace_193, NoMatchGlobal_193) {
  std::string s = "hello";
  int count = PCRE::GlobalReplace(&s, PCRE("xyz"), "replaced");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello");
}

TEST(PCREGlobalReplace_193, ReplaceAllDigits_193) {
  std::string s = "a1b2c3";
  int count = PCRE::GlobalReplace(&s, PCRE("\\d"), "X");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "aXbXcX");
}

TEST(PCREGlobalReplace_193, GlobalReplaceWithEmptyReplacement_193) {
  std::string s = "a1b2c3";
  int count = PCRE::GlobalReplace(&s, PCRE("\\d"), "");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "abc");
}

// ==================== Extract Tests ====================

TEST(PCREExtract_193, BasicExtract_193) {
  std::string out;
  EXPECT_TRUE(PCRE::Extract("boris@kremlin.ru", PCRE("(.*)@([^.]*)"), "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST(PCREExtract_193, ExtractNoMatch_193) {
  std::string out;
  EXPECT_FALSE(PCRE::Extract("no match here", PCRE("(\\d+)"), "\\1", &out));
}

TEST(PCREExtract_193, ExtractWholeMatch_193) {
  std::string out;
  EXPECT_TRUE(PCRE::Extract("hello", PCRE("(h\\w+)"), "\\1", &out));
  EXPECT_EQ(out, "hello");
}

// ==================== QuoteMeta Tests ====================

TEST(PCREQuoteMeta_193, BasicQuote_193) {
  std::string quoted = PCRE::QuoteMeta("hello");
  EXPECT_EQ(quoted, "hello");
}

TEST(PCREQuoteMeta_193, QuoteSpecialChars_193) {
  std::string quoted = PCRE::QuoteMeta("a.b");
  // The dot should be escaped
  std::string s = "a.b";
  PCRE pattern(quoted);
  EXPECT_TRUE(PCRE::Replace(&s, pattern, "X"));
  EXPECT_EQ(s, "X");
}

TEST(PCREQuoteMeta_193, QuoteSpecialCharsDontMatchWrong_193) {
  std::string quoted = PCRE::QuoteMeta("a.b");
  std::string s = "axb";
  PCRE pattern(quoted);
  EXPECT_FALSE(PCRE::Replace(&s, pattern, "X"));
  EXPECT_EQ(s, "axb");
}

TEST(PCREQuoteMeta_193, EmptyString_193) {
  std::string quoted = PCRE::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

TEST(PCREQuoteMeta_193, AllSpecialChars_193) {
  std::string special = "[](){}.*+?|^$\\";
  std::string quoted = PCRE::QuoteMeta(special);
  // The quoted version should literally match the special string
  std::string s = special;
  PCRE pattern(quoted);
  EXPECT_TRUE(PCRE::Replace(&s, pattern, "MATCHED"));
  EXPECT_EQ(s, "MATCHED");
}

// ==================== CheckRewriteString Tests ====================

TEST(PCRECheckRewrite_193, ValidRewriteNoCaptures_193) {
  PCRE re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("world", &error));
}

TEST(PCRECheckRewrite_193, ValidRewriteWithCapture_193) {
  PCRE re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(PCRECheckRewrite_193, InvalidRewriteTooManyCaptures_193) {
  PCRE re("hello");
  std::string error;
  // Pattern has 0 capturing groups, but rewrite references \1
  EXPECT_FALSE(re.CheckRewriteString("\\1", &error));
  EXPECT_FALSE(error.empty());
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST(PCRECapturingGroups_193, NoGroups_193) {
  PCRE re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(PCRECapturingGroups_193, OneGroup_193) {
  PCRE re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(PCRECapturingGroups_193, MultipleGroups_193) {
  PCRE re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(PCRECapturingGroups_193, NestedGroups_193) {
  PCRE re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

// ==================== pattern() and error() Tests ====================

TEST(PCREPattern_193, PatternReturned_193) {
  PCRE re("hello.*world");
  EXPECT_EQ(re.pattern(), "hello.*world");
}

TEST(PCREPattern_193, StringConstructor_193) {
  std::string pat = "foo|bar";
  PCRE re(pat);
  EXPECT_EQ(re.pattern(), "foo|bar");
}

// ==================== HitLimit / ClearHitLimit Tests ====================

TEST(PCREHitLimit_193, InitiallyNoHitLimit_193) {
  PCRE re("test");
  EXPECT_FALSE(re.HitLimit());
}

TEST(PCREHitLimit_193, ClearHitLimit_193) {
  PCRE re("test");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// ==================== DoMatch Tests ====================

TEST(PCREDoMatch_193, SimpleMatch_193) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREDoMatch_193, SimpleNoMatch_193) {
  PCRE re("hello");
  EXPECT_FALSE(re.DoMatch("world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREDoMatch_193, UnanchoredMatch_193) {
  PCRE re("ell");
  EXPECT_TRUE(re.DoMatch("hello", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCREDoMatch_193, AnchoredStartMatch_193) {
  PCRE re("hel");
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCREDoMatch_193, AnchoredStartNoMatch_193) {
  PCRE re("ell");
  EXPECT_FALSE(re.DoMatch("hello", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCREDoMatch_193, AnchoredBothNoMatch_193) {
  PCRE re("hel");
  EXPECT_FALSE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREDoMatch_193, MatchWithConsumed_193) {
  PCRE re("hel");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_START, &consumed, nullptr, 0));
  EXPECT_EQ(consumed, 3u);
}

TEST(PCREDoMatch_193, MatchWithCapture_193) {
  PCRE re("(\\w+)@(\\w+)");
  std::string user, domain;
  const PCRE::Arg* args[] = {
    new PCRE::Arg(&user),
    new PCRE::Arg(&domain)
  };
  EXPECT_TRUE(re.DoMatch("test@example", PCRE::ANCHOR_BOTH, nullptr, args, 2));
  EXPECT_EQ(user, "test");
  EXPECT_EQ(domain, "example");
  delete args[0];
  delete args[1];
}

// ==================== Constructor with various options ====================

TEST(PCREConstructor_193, CStringConstructor_193) {
  PCRE re("test");
  EXPECT_EQ(re.pattern(), "test");
}

TEST(PCREConstructor_193, StdStringConstructor_193) {
  std::string pattern = "test";
  PCRE re(pattern);
  EXPECT_EQ(re.pattern(), "test");
}

// ==================== Edge Cases ====================

TEST(PCREEdge_193, ReplaceSpecialRegexChars_193) {
  std::string s = "price is $100";
  EXPECT_TRUE(PCRE::Replace(&s, PCRE("\\$(\\d+)"), "€\\1"));
  EXPECT_EQ(s, "price is €100");
}

TEST(PCREEdge_193, GlobalReplaceEmptyMatches_193) {
  std::string s = "abc";
  int count = PCRE::GlobalReplace(&s, PCRE(""), "X");
  // Each position (before a, between a-b, between b-c, after c) should get X
  EXPECT_GE(count, 4);
}

TEST(PCREEdge_193, ReplaceLongString_193) {
  std::string s(1000, 'a');
  EXPECT_TRUE(PCRE::Replace(&s, PCRE("a+"), "b"));
  EXPECT_EQ(s, "b");
}

TEST(PCREEdge_193, ExtractFromEmptyText_193) {
  std::string out;
  EXPECT_TRUE(PCRE::Extract("", PCRE("()"), "got:\\1", &out));
  EXPECT_EQ(out, "got:");
}

}  // namespace re2
