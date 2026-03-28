#include <gtest/gtest.h>
#include <string>
#include "util/pcre.h"

namespace re2 {

// ==================== Construction Tests ====================

TEST(PCRETest_590, ConstructFromCString_590) {
  PCRE re("hello");
  EXPECT_EQ(re.pattern(), "hello");
  EXPECT_EQ(re.error(), "");
}

TEST(PCRETest_590, ConstructFromStdString_590) {
  std::string pattern = "world";
  PCRE re(pattern);
  EXPECT_EQ(re.pattern(), "world");
  EXPECT_EQ(re.error(), "");
}

TEST(PCRETest_590, ConstructWithOption_590) {
  PCRE re("test", PCRE::CASELESS);
  EXPECT_EQ(re.pattern(), "test");
}

TEST(PCRETest_590, ConstructFromStdStringWithOption_590) {
  std::string pattern = "test";
  PCRE re(pattern, PCRE::CASELESS);
  EXPECT_EQ(re.pattern(), "test");
}

TEST(PCRETest_590, ConstructWithPCREOptions_590) {
  PCRE_Options opts;
  opts.set_option(PCRE::CASELESS);
  opts.set_match_limit(1000);
  opts.set_stack_limit(1000);
  opts.set_report_errors(false);
  PCRE re("abc", opts);
  EXPECT_EQ(re.pattern(), "abc");
}

TEST(PCRETest_590, ConstructFromStdStringWithPCREOptions_590) {
  PCRE_Options opts;
  opts.set_option(PCRE::MULTILINE);
  std::string pattern = "xyz";
  PCRE re(pattern, opts);
  EXPECT_EQ(re.pattern(), "xyz");
}

TEST(PCRETest_590, EmptyPattern_590) {
  PCRE re("");
  EXPECT_EQ(re.pattern(), "");
}

TEST(PCRETest_590, InvalidPattern_590) {
  PCRE re("[invalid");
  // An invalid regex should have a non-empty error
  EXPECT_FALSE(re.error().empty());
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST(PCRETest_590, NumberOfCapturingGroupsNone_590) {
  PCRE re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(PCRETest_590, NumberOfCapturingGroupsOne_590) {
  PCRE re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(PCRETest_590, NumberOfCapturingGroupsMultiple_590) {
  PCRE re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(PCRETest_590, NumberOfCapturingGroupsNested_590) {
  PCRE re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

// ==================== HitLimit / ClearHitLimit Tests ====================

TEST(PCRETest_590, HitLimitInitiallyFalse_590) {
  PCRE re("abc");
  EXPECT_FALSE(re.HitLimit());
}

TEST(PCRETest_590, ClearHitLimit_590) {
  PCRE re("abc");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// ==================== QuoteMeta Tests ====================

TEST(PCRETest_590, QuoteMetaNoSpecialChars_590) {
  std::string result = PCRE::QuoteMeta("hello");
  EXPECT_EQ(result, "hello");
}

TEST(PCRETest_590, QuoteMetaWithSpecialChars_590) {
  std::string result = PCRE::QuoteMeta("a.b*c+d?e");
  // Each special char should be escaped with backslash
  EXPECT_NE(result.find("\\"), std::string::npos);
}

TEST(PCRETest_590, QuoteMetaEmptyString_590) {
  std::string result = PCRE::QuoteMeta("");
  EXPECT_EQ(result, "");
}

TEST(PCRETest_590, QuoteMetaDot_590) {
  std::string result = PCRE::QuoteMeta(".");
  EXPECT_EQ(result, "\\.");
}

TEST(PCRETest_590, QuoteMetaBackslash_590) {
  std::string result = PCRE::QuoteMeta("\\");
  EXPECT_EQ(result, "\\\\");
}

TEST(PCRETest_590, QuoteMetaAllSpecial_590) {
  std::string result = PCRE::QuoteMeta("[](){}.*+?|^$\\");
  // The result should be longer due to escaping
  EXPECT_GT(result.size(), strlen("[](){}.*+?|^$\\"));
}

// ==================== DoMatch Tests ====================

TEST(PCRETest_590, DoMatchFullMatch_590) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_590, DoMatchFullMatchFails_590) {
  PCRE re("hello");
  EXPECT_FALSE(re.DoMatch("hello world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_590, DoMatchPartialMatch_590) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCRETest_590, DoMatchNoMatch_590) {
  PCRE re("hello");
  EXPECT_FALSE(re.DoMatch("world", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCRETest_590, DoMatchAnchorStart_590) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCRETest_590, DoMatchAnchorStartFails_590) {
  PCRE re("world");
  EXPECT_FALSE(re.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCRETest_590, DoMatchWithConsumed_590) {
  PCRE re("hel+o");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_START, &consumed, nullptr, 0));
  EXPECT_EQ(consumed, 5u);
}

TEST(PCRETest_590, DoMatchWithCapture_590) {
  PCRE re("(\\w+)\\s+(\\w+)");
  std::string word1, word2;
  const PCRE::Arg arg1(&word1);
  const PCRE::Arg arg2(&word2);
  const PCRE::Arg* args[] = {&arg1, &arg2};
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_BOTH, nullptr, args, 2));
  EXPECT_EQ(word1, "hello");
  EXPECT_EQ(word2, "world");
}

TEST(PCRETest_590, DoMatchEmptyPattern_590) {
  PCRE re("");
  EXPECT_TRUE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_590, DoMatchEmptyText_590) {
  PCRE re("a*");
  EXPECT_TRUE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_590, DoMatchEmptyTextNonEmptyPattern_590) {
  PCRE re("a+");
  EXPECT_FALSE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_590, DoMatchCaptureInt_590) {
  PCRE re("(\\d+)");
  int value = 0;
  const PCRE::Arg arg(&value);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch("12345", PCRE::ANCHOR_BOTH, nullptr, args, 1));
  EXPECT_EQ(value, 12345);
}

// ==================== Replace Tests ====================

TEST(PCRETest_590, ReplaceSimple_590) {
  std::string str = "hello world";
  EXPECT_TRUE(PCRE::Replace(&str, PCRE("world"), "there"));
  EXPECT_EQ(str, "hello there");
}

TEST(PCRETest_590, ReplaceNoMatch_590) {
  std::string str = "hello world";
  EXPECT_FALSE(PCRE::Replace(&str, PCRE("xyz"), "there"));
  EXPECT_EQ(str, "hello world");
}

TEST(PCRETest_590, ReplaceWithBackreference_590) {
  std::string str = "hello world";
  EXPECT_TRUE(PCRE::Replace(&str, PCRE("(\\w+)"), "\\1!"));
  EXPECT_EQ(str, "hello! world");
}

TEST(PCRETest_590, ReplaceEmpty_590) {
  std::string str = "hello";
  EXPECT_TRUE(PCRE::Replace(&str, PCRE("hello"), ""));
  EXPECT_EQ(str, "");
}

// ==================== GlobalReplace Tests ====================

TEST(PCRETest_590, GlobalReplaceMultiple_590) {
  std::string str = "aaa";
  int count = PCRE::GlobalReplace(&str, PCRE("a"), "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "bbb");
}

TEST(PCRETest_590, GlobalReplaceNoMatch_590) {
  std::string str = "hello";
  int count = PCRE::GlobalReplace(&str, PCRE("xyz"), "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

TEST(PCRETest_590, GlobalReplaceSingle_590) {
  std::string str = "hello";
  int count = PCRE::GlobalReplace(&str, PCRE("hello"), "world");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(str, "world");
}

// ==================== Extract Tests ====================

TEST(PCRETest_590, ExtractSimple_590) {
  std::string out;
  EXPECT_TRUE(PCRE::Extract("boris@kremlin.ru", PCRE("(.*)@([^.]*)"), "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST(PCRETest_590, ExtractNoMatch_590) {
  std::string out;
  EXPECT_FALSE(PCRE::Extract("no match here", PCRE("(\\d+)"), "\\1", &out));
}

// ==================== CheckRewriteString Tests ====================

TEST(PCRETest_590, CheckRewriteStringValid_590) {
  PCRE re("(\\w+)\\s+(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1-\\2", &error));
  EXPECT_EQ(error, "");
}

TEST(PCRETest_590, CheckRewriteStringInvalidGroup_590) {
  PCRE re("(\\w+)");
  std::string error;
  // Referencing group 5 when there's only 1 group should fail
  EXPECT_FALSE(re.CheckRewriteString("\\5", &error));
  EXPECT_FALSE(error.empty());
}

TEST(PCRETest_590, CheckRewriteStringNoGroups_590) {
  PCRE re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("world", &error));
}

// ==================== PCRE_Options Tests ====================

TEST(PCREOptionsTest_590, DefaultValues_590) {
  PCRE_Options opts;
  EXPECT_EQ(opts.option(), PCRE::None);
  EXPECT_EQ(opts.match_limit(), 0);
  EXPECT_EQ(opts.stack_limit(), 0);
  EXPECT_TRUE(opts.report_errors());
}

TEST(PCREOptionsTest_590, SetOption_590) {
  PCRE_Options opts;
  opts.set_option(PCRE::CASELESS);
  EXPECT_EQ(opts.option(), PCRE::CASELESS);
}

TEST(PCREOptionsTest_590, SetMatchLimit_590) {
  PCRE_Options opts;
  opts.set_match_limit(500);
  EXPECT_EQ(opts.match_limit(), 500);
}

TEST(PCREOptionsTest_590, SetStackLimit_590) {
  PCRE_Options opts;
  opts.set_stack_limit(1000);
  EXPECT_EQ(opts.stack_limit(), 1000);
}

TEST(PCREOptionsTest_590, SetReportErrors_590) {
  PCRE_Options opts;
  opts.set_report_errors(false);
  EXPECT_FALSE(opts.report_errors());
  opts.set_report_errors(true);
  EXPECT_TRUE(opts.report_errors());
}

// ==================== Complex Pattern Tests ====================

TEST(PCRETest_590, ComplexPattern_590) {
  PCRE re("^(\\d{4})-(\\d{2})-(\\d{2})$");
  std::string year, month, day;
  const PCRE::Arg arg1(&year);
  const PCRE::Arg arg2(&month);
  const PCRE::Arg arg3(&day);
  const PCRE::Arg* args[] = {&arg1, &arg2, &arg3};
  EXPECT_TRUE(re.DoMatch("2023-10-15", PCRE::ANCHOR_BOTH, nullptr, args, 3));
  EXPECT_EQ(year, "2023");
  EXPECT_EQ(month, "10");
  EXPECT_EQ(day, "15");
}

TEST(PCRETest_590, CaselessMatch_590) {
  PCRE re("hello", PCRE::CASELESS);
  EXPECT_TRUE(re.DoMatch("HELLO", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch("Hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch("hElLo", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_590, PatternAccessor_590) {
  PCRE re("my_pattern");
  EXPECT_EQ(re.pattern(), "my_pattern");
}

TEST(PCRETest_590, ErrorOnInvalidRegex_590) {
  PCRE re("(unclosed");
  EXPECT_FALSE(re.error().empty());
}

TEST(PCRETest_590, MultilineMatch_590) {
  PCRE re("^hello$", PCRE::MULTILINE);
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

}  // namespace re2
