#include "gtest/gtest.h"
#include "util/pcre.h"
#include <string>

namespace re2 {

// Test fixture for PCRE tests
class PCRETest_591 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(PCRETest_591, ConstructFromCString_591) {
  PCRE re("hello");
  EXPECT_EQ(re.pattern(), "hello");
  EXPECT_TRUE(re.error().empty());
}

TEST_F(PCRETest_591, ConstructFromStdString_591) {
  std::string pattern = "world";
  PCRE re(pattern);
  EXPECT_EQ(re.pattern(), "world");
  EXPECT_TRUE(re.error().empty());
}

TEST_F(PCRETest_591, ConstructWithOption_591) {
  PCRE re("test", PCRE::UTF8);
  EXPECT_EQ(re.pattern(), "test");
}

TEST_F(PCRETest_591, ConstructWithStdStringAndOption_591) {
  std::string pattern = "test";
  PCRE re(pattern, PCRE::UTF8);
  EXPECT_EQ(re.pattern(), "test");
}

TEST_F(PCRETest_591, ConstructWithPCREOptions_591) {
  PCRE_Options opts;
  opts.set_option(PCRE::UTF8);
  opts.set_match_limit(1000);
  opts.set_stack_limit(1000);
  opts.set_report_errors(false);
  PCRE re("abc", opts);
  EXPECT_EQ(re.pattern(), "abc");
}

TEST_F(PCRETest_591, ConstructWithStdStringAndPCREOptions_591) {
  PCRE_Options opts;
  std::string pattern = "abc";
  PCRE re(pattern, opts);
  EXPECT_EQ(re.pattern(), "abc");
}

TEST_F(PCRETest_591, ConstructEmptyPattern_591) {
  PCRE re("");
  EXPECT_EQ(re.pattern(), "");
}

TEST_F(PCRETest_591, ConstructInvalidPattern_591) {
  PCRE_Options opts;
  opts.set_report_errors(false);
  PCRE re("[invalid", opts);
  EXPECT_FALSE(re.error().empty());
}

// ==================== PCRE_Options Tests ====================

TEST_F(PCRETest_591, PCREOptionsDefaultValues_591) {
  PCRE_Options opts;
  EXPECT_EQ(opts.option(), PCRE::None);
  EXPECT_EQ(opts.match_limit(), 0);
  EXPECT_EQ(opts.stack_limit(), 0);
  EXPECT_TRUE(opts.report_errors());
}

TEST_F(PCRETest_591, PCREOptionsSetOption_591) {
  PCRE_Options opts;
  opts.set_option(PCRE::UTF8);
  EXPECT_EQ(opts.option(), PCRE::UTF8);
}

TEST_F(PCRETest_591, PCREOptionsSetMatchLimit_591) {
  PCRE_Options opts;
  opts.set_match_limit(500);
  EXPECT_EQ(opts.match_limit(), 500);
}

TEST_F(PCRETest_591, PCREOptionsSetStackLimit_591) {
  PCRE_Options opts;
  opts.set_stack_limit(1024);
  EXPECT_EQ(opts.stack_limit(), 1024);
}

TEST_F(PCRETest_591, PCREOptionsSetReportErrors_591) {
  PCRE_Options opts;
  opts.set_report_errors(false);
  EXPECT_FALSE(opts.report_errors());
  opts.set_report_errors(true);
  EXPECT_TRUE(opts.report_errors());
}

// ==================== Pattern and Error Tests ====================

TEST_F(PCRETest_591, PatternReturnsOriginal_591) {
  PCRE re("(\\d+)-(\\w+)");
  EXPECT_EQ(re.pattern(), "(\\d+)-(\\w+)");
}

TEST_F(PCRETest_591, ErrorEmptyForValidPattern_591) {
  PCRE re("abc");
  EXPECT_TRUE(re.error().empty());
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST_F(PCRETest_591, NoCapturingGroups_591) {
  PCRE re("abc");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(PCRETest_591, OneCapturingGroup_591) {
  PCRE re("(abc)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST_F(PCRETest_591, MultipleCapturingGroups_591) {
  PCRE re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(PCRETest_591, NestedCapturingGroups_591) {
  PCRE re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

// ==================== HitLimit Tests ====================

TEST_F(PCRETest_591, HitLimitInitiallyFalse_591) {
  PCRE re("abc");
  EXPECT_FALSE(re.HitLimit());
}

TEST_F(PCRETest_591, ClearHitLimit_591) {
  PCRE re("abc");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// ==================== QuoteMeta Tests ====================

TEST_F(PCRETest_591, QuoteMetaNoSpecialChars_591) {
  std::string result = PCRE::QuoteMeta("hello");
  EXPECT_EQ(result, "hello");
}

TEST_F(PCRETest_591, QuoteMetaWithSpecialChars_591) {
  std::string result = PCRE::QuoteMeta("a.b");
  EXPECT_EQ(result, "a\\.b");
}

TEST_F(PCRETest_591, QuoteMetaEmptyString_591) {
  std::string result = PCRE::QuoteMeta("");
  EXPECT_EQ(result, "");
}

TEST_F(PCRETest_591, QuoteMetaAllSpecial_591) {
  std::string result = PCRE::QuoteMeta(".*+?[]{}()\\|^$");
  // Each special character should be escaped
  EXPECT_NE(result, ".*+?[]{}()\\|^$");
  // The quoted version should be usable as a literal pattern
  PCRE re(result);
  EXPECT_TRUE(re.error().empty());
}

TEST_F(PCRETest_591, QuoteMetaWithNullByte_591) {
  std::string input("a\0b", 3);
  std::string result = PCRE::QuoteMeta(input);
  EXPECT_FALSE(result.empty());
}

// ==================== DoMatch Tests ====================

TEST_F(PCRETest_591, DoMatchSimpleFullMatch_591) {
  PCRE re("hello");
  bool matched = re.DoMatch(absl::string_view("hello"),
                            PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_TRUE(matched);
}

TEST_F(PCRETest_591, DoMatchSimpleNoMatch_591) {
  PCRE re("hello");
  bool matched = re.DoMatch(absl::string_view("world"),
                            PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_FALSE(matched);
}

TEST_F(PCRETest_591, DoMatchPartialMatch_591) {
  PCRE re("ell");
  bool matched = re.DoMatch(absl::string_view("hello"),
                            PCRE::UNANCHORED, nullptr, nullptr, 0);
  EXPECT_TRUE(matched);
}

TEST_F(PCRETest_591, DoMatchAnchorStart_591) {
  PCRE re("hel");
  bool matched = re.DoMatch(absl::string_view("hello"),
                            PCRE::ANCHOR_START, nullptr, nullptr, 0);
  EXPECT_TRUE(matched);
}

TEST_F(PCRETest_591, DoMatchAnchorStartNoMatch_591) {
  PCRE re("llo");
  bool matched = re.DoMatch(absl::string_view("hello"),
                            PCRE::ANCHOR_START, nullptr, nullptr, 0);
  EXPECT_FALSE(matched);
}

TEST_F(PCRETest_591, DoMatchWithConsumed_591) {
  PCRE re("hel");
  size_t consumed = 0;
  bool matched = re.DoMatch(absl::string_view("hello"),
                            PCRE::ANCHOR_START, &consumed, nullptr, 0);
  EXPECT_TRUE(matched);
  EXPECT_EQ(consumed, 3u);
}

TEST_F(PCRETest_591, DoMatchEmptyPattern_591) {
  PCRE re("");
  bool matched = re.DoMatch(absl::string_view("hello"),
                            PCRE::UNANCHORED, nullptr, nullptr, 0);
  EXPECT_TRUE(matched);
}

TEST_F(PCRETest_591, DoMatchEmptyText_591) {
  PCRE re("");
  bool matched = re.DoMatch(absl::string_view(""),
                            PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_TRUE(matched);
}

TEST_F(PCRETest_591, DoMatchEmptyTextNonEmptyPattern_591) {
  PCRE re("abc");
  bool matched = re.DoMatch(absl::string_view(""),
                            PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_FALSE(matched);
}

TEST_F(PCRETest_591, DoMatchWithCapturingGroup_591) {
  PCRE re("(\\d+)");
  int value;
  const PCRE::Arg* args[] = {new PCRE::Arg(&value)};
  bool matched = re.DoMatch(absl::string_view("123"),
                            PCRE::ANCHOR_BOTH, nullptr, args, 1);
  EXPECT_TRUE(matched);
  EXPECT_EQ(value, 123);
  delete args[0];
}

TEST_F(PCRETest_591, DoMatchWithStringCapture_591) {
  PCRE re("(\\w+)");
  std::string captured;
  const PCRE::Arg* args[] = {new PCRE::Arg(&captured)};
  bool matched = re.DoMatch(absl::string_view("hello"),
                            PCRE::ANCHOR_BOTH, nullptr, args, 1);
  EXPECT_TRUE(matched);
  EXPECT_EQ(captured, "hello");
  delete args[0];
}

// ==================== Replace Tests ====================

TEST_F(PCRETest_591, ReplaceSimple_591) {
  std::string str = "hello world";
  PCRE re("world");
  bool replaced = PCRE::Replace(&str, re, "earth");
  EXPECT_TRUE(replaced);
  EXPECT_EQ(str, "hello earth");
}

TEST_F(PCRETest_591, ReplaceNoMatch_591) {
  std::string str = "hello world";
  PCRE re("xyz");
  bool replaced = PCRE::Replace(&str, re, "abc");
  EXPECT_FALSE(replaced);
  EXPECT_EQ(str, "hello world");
}

TEST_F(PCRETest_591, ReplaceWithCapturingGroup_591) {
  std::string str = "hello world";
  PCRE re("(\\w+) (\\w+)");
  bool replaced = PCRE::Replace(&str, re, "\\2 \\1");
  EXPECT_TRUE(replaced);
  EXPECT_EQ(str, "world hello");
}

TEST_F(PCRETest_591, ReplaceEmptyMatch_591) {
  std::string str = "abc";
  PCRE re("b");
  bool replaced = PCRE::Replace(&str, re, "");
  EXPECT_TRUE(replaced);
  EXPECT_EQ(str, "ac");
}

// ==================== GlobalReplace Tests ====================

TEST_F(PCRETest_591, GlobalReplaceMultiple_591) {
  std::string str = "aaa";
  PCRE re("a");
  int count = PCRE::GlobalReplace(&str, re, "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "bbb");
}

TEST_F(PCRETest_591, GlobalReplaceNoMatch_591) {
  std::string str = "hello";
  PCRE re("xyz");
  int count = PCRE::GlobalReplace(&str, re, "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

TEST_F(PCRETest_591, GlobalReplaceSingleOccurrence_591) {
  std::string str = "hello";
  PCRE re("ell");
  int count = PCRE::GlobalReplace(&str, re, "ELL");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(str, "hELLo");
}

// ==================== Extract Tests ====================

TEST_F(PCRETest_591, ExtractSimple_591) {
  std::string out;
  PCRE re("(\\w+)@(\\w+)");
  bool extracted = PCRE::Extract("user@host", re, "\\1 at \\2", &out);
  EXPECT_TRUE(extracted);
  EXPECT_EQ(out, "user at host");
}

TEST_F(PCRETest_591, ExtractNoMatch_591) {
  std::string out;
  PCRE re("(\\d+)");
  bool extracted = PCRE::Extract("hello", re, "\\1", &out);
  EXPECT_FALSE(extracted);
}

TEST_F(PCRETest_591, ExtractWholeMatch_591) {
  std::string out;
  PCRE re("h(ell)o");
  bool extracted = PCRE::Extract("hello", re, "\\1", &out);
  EXPECT_TRUE(extracted);
  EXPECT_EQ(out, "ell");
}

// ==================== CheckRewriteString Tests ====================

TEST_F(PCRETest_591, CheckRewriteStringValid_591) {
  PCRE re("(\\w+) (\\w+)");
  std::string error;
  bool valid = re.CheckRewriteString("\\1-\\2", &error);
  EXPECT_TRUE(valid);
  EXPECT_TRUE(error.empty());
}

TEST_F(PCRETest_591, CheckRewriteStringInvalidBackref_591) {
  PCRE re("(\\w+)");
  std::string error;
  bool valid = re.CheckRewriteString("\\2", &error);
  EXPECT_FALSE(valid);
  EXPECT_FALSE(error.empty());
}

TEST_F(PCRETest_591, CheckRewriteStringNoBackrefs_591) {
  PCRE re("hello");
  std::string error;
  bool valid = re.CheckRewriteString("replacement", &error);
  EXPECT_TRUE(valid);
}

// ==================== Complex Pattern Tests ====================

TEST_F(PCRETest_591, ComplexPatternDigits_591) {
  PCRE re("\\d{3}-\\d{4}");
  bool matched = re.DoMatch(absl::string_view("123-4567"),
                            PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_TRUE(matched);
}

TEST_F(PCRETest_591, ComplexPatternDigitsNoMatch_591) {
  PCRE re("\\d{3}-\\d{4}");
  bool matched = re.DoMatch(absl::string_view("12-4567"),
                            PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_FALSE(matched);
}

TEST_F(PCRETest_591, AlternationPattern_591) {
  PCRE re("cat|dog");
  EXPECT_TRUE(re.DoMatch(absl::string_view("cat"),
                          PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch(absl::string_view("dog"),
                          PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch(absl::string_view("bird"),
                           PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST_F(PCRETest_591, OptionalGroup_591) {
  PCRE re("colou?r");
  EXPECT_TRUE(re.DoMatch(absl::string_view("color"),
                          PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch(absl::string_view("colour"),
                          PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

// ==================== Boundary Tests ====================

TEST_F(PCRETest_591, VeryLongPattern_591) {
  std::string long_pattern(1000, 'a');
  PCRE re(long_pattern);
  EXPECT_TRUE(re.error().empty());
  
  std::string long_text(1000, 'a');
  bool matched = re.DoMatch(absl::string_view(long_text),
                            PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_TRUE(matched);
}

TEST_F(PCRETest_591, SingleCharPattern_591) {
  PCRE re("a");
  EXPECT_TRUE(re.DoMatch(absl::string_view("a"),
                          PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch(absl::string_view("b"),
                           PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

}  // namespace re2
