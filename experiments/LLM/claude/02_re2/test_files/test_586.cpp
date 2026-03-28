#include <string>
#include "gtest/gtest.h"
#include "util/pcre.h"

namespace re2 {

// Test fixture for PCRE tests
class PCRETest_586 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(PCRETest_586, ConstructWithCString_586) {
  PCRE re("hello");
  EXPECT_EQ(re.pattern(), "hello");
  EXPECT_EQ(re.error(), "");
}

TEST_F(PCRETest_586, ConstructWithStdString_586) {
  std::string pat = "world";
  PCRE re(pat);
  EXPECT_EQ(re.pattern(), "world");
  EXPECT_EQ(re.error(), "");
}

TEST_F(PCRETest_586, ConstructWithOption_586) {
  PCRE re("test", PCRE::UTF8);
  EXPECT_EQ(re.pattern(), "test");
}

TEST_F(PCRETest_586, ConstructWithStdStringAndOption_586) {
  std::string pat = "test2";
  PCRE re(pat, PCRE::None);
  EXPECT_EQ(re.pattern(), "test2");
}

TEST_F(PCRETest_586, ConstructEmptyPattern_586) {
  PCRE re("");
  EXPECT_EQ(re.pattern(), "");
}

// ==================== Pattern and Error Tests ====================

TEST_F(PCRETest_586, PatternReturnsCorrectValue_586) {
  PCRE re("abc.*def");
  EXPECT_EQ(re.pattern(), "abc.*def");
}

TEST_F(PCRETest_586, InvalidPatternSetsError_586) {
  // Unbalanced parenthesis - should produce an error
  PCRE re("(abc");
  EXPECT_FALSE(re.error().empty());
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST_F(PCRETest_586, NoCapturingGroups_586) {
  PCRE re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(PCRETest_586, OneCapturingGroup_586) {
  PCRE re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST_F(PCRETest_586, MultipleCapturingGroups_586) {
  PCRE re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(PCRETest_586, NestedCapturingGroups_586) {
  PCRE re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

// ==================== HitLimit and ClearHitLimit Tests ====================

TEST_F(PCRETest_586, HitLimitInitiallyFalse_586) {
  PCRE re("test");
  EXPECT_FALSE(re.HitLimit());
}

TEST_F(PCRETest_586, ClearHitLimitDoesNotCrash_586) {
  PCRE re("test");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// ==================== QuoteMeta Tests ====================

TEST_F(PCRETest_586, QuoteMetaPlainString_586) {
  std::string result = PCRE::QuoteMeta("hello");
  EXPECT_EQ(result, "hello");
}

TEST_F(PCRETest_586, QuoteMetaWithSpecialChars_586) {
  std::string result = PCRE::QuoteMeta("hello.world");
  EXPECT_EQ(result, "hello\\.world");
}

TEST_F(PCRETest_586, QuoteMetaWithMultipleSpecialChars_586) {
  std::string result = PCRE::QuoteMeta("a+b*c?");
  EXPECT_EQ(result, "a\\+b\\*c\\?");
}

TEST_F(PCRETest_586, QuoteMetaEmptyString_586) {
  std::string result = PCRE::QuoteMeta("");
  EXPECT_EQ(result, "");
}

TEST_F(PCRETest_586, QuoteMetaWithParens_586) {
  std::string result = PCRE::QuoteMeta("(a)");
  EXPECT_EQ(result, "\\(a\\)");
}

TEST_F(PCRETest_586, QuoteMetaWithBackslash_586) {
  std::string result = PCRE::QuoteMeta("a\\b");
  EXPECT_EQ(result, "a\\\\b");
}

TEST_F(PCRETest_586, QuoteMetaWithBrackets_586) {
  std::string result = PCRE::QuoteMeta("[abc]");
  EXPECT_EQ(result, "\\[abc\\]");
}

// ==================== DoMatch Tests ====================

TEST_F(PCRETest_586, DoMatchSimpleFullMatch_586) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch(absl::string_view("hello"), PCRE::ANCHOR_BOTH,
                          nullptr, nullptr, 0));
}

TEST_F(PCRETest_586, DoMatchSimpleFullMatchFails_586) {
  PCRE re("hello");
  EXPECT_FALSE(re.DoMatch(absl::string_view("world"), PCRE::ANCHOR_BOTH,
                           nullptr, nullptr, 0));
}

TEST_F(PCRETest_586, DoMatchPartialMatch_586) {
  PCRE re("ell");
  EXPECT_TRUE(re.DoMatch(absl::string_view("hello"), PCRE::UNANCHORED,
                          nullptr, nullptr, 0));
}

TEST_F(PCRETest_586, DoMatchPartialMatchFails_586) {
  PCRE re("xyz");
  EXPECT_FALSE(re.DoMatch(absl::string_view("hello"), PCRE::UNANCHORED,
                           nullptr, nullptr, 0));
}

TEST_F(PCRETest_586, DoMatchAnchorStart_586) {
  PCRE re("hel");
  EXPECT_TRUE(re.DoMatch(absl::string_view("hello"), PCRE::ANCHOR_START,
                          nullptr, nullptr, 0));
}

TEST_F(PCRETest_586, DoMatchAnchorStartFails_586) {
  PCRE re("llo");
  EXPECT_FALSE(re.DoMatch(absl::string_view("hello"), PCRE::ANCHOR_START,
                           nullptr, nullptr, 0));
}

TEST_F(PCRETest_586, DoMatchEmptyPattern_586) {
  PCRE re("");
  EXPECT_TRUE(re.DoMatch(absl::string_view("hello"), PCRE::UNANCHORED,
                          nullptr, nullptr, 0));
}

TEST_F(PCRETest_586, DoMatchEmptyText_586) {
  PCRE re("");
  EXPECT_TRUE(re.DoMatch(absl::string_view(""), PCRE::ANCHOR_BOTH,
                          nullptr, nullptr, 0));
}

TEST_F(PCRETest_586, DoMatchWithConsumed_586) {
  PCRE re("hel");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch(absl::string_view("hello"), PCRE::ANCHOR_START,
                          &consumed, nullptr, 0));
  EXPECT_EQ(consumed, 3u);
}

// ==================== Replace Tests ====================

TEST_F(PCRETest_586, ReplaceSimple_586) {
  std::string str = "hello world";
  PCRE re("world");
  EXPECT_TRUE(PCRE::Replace(&str, re, "there"));
  EXPECT_EQ(str, "hello there");
}

TEST_F(PCRETest_586, ReplaceNoMatch_586) {
  std::string str = "hello world";
  PCRE re("xyz");
  EXPECT_FALSE(PCRE::Replace(&str, re, "there"));
  EXPECT_EQ(str, "hello world");
}

TEST_F(PCRETest_586, ReplaceWithCapture_586) {
  std::string str = "hello world";
  PCRE re("(\\w+) (\\w+)");
  EXPECT_TRUE(PCRE::Replace(&str, re, "\\2 \\1"));
  EXPECT_EQ(str, "world hello");
}

TEST_F(PCRETest_586, ReplaceFirstOccurrenceOnly_586) {
  std::string str = "aaa";
  PCRE re("a");
  EXPECT_TRUE(PCRE::Replace(&str, re, "b"));
  EXPECT_EQ(str, "baa");
}

// ==================== GlobalReplace Tests ====================

TEST_F(PCRETest_586, GlobalReplaceAll_586) {
  std::string str = "aaa";
  PCRE re("a");
  int count = PCRE::GlobalReplace(&str, re, "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "bbb");
}

TEST_F(PCRETest_586, GlobalReplaceNoMatch_586) {
  std::string str = "hello";
  PCRE re("x");
  int count = PCRE::GlobalReplace(&str, re, "y");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

TEST_F(PCRETest_586, GlobalReplaceMultipleOccurrences_586) {
  std::string str = "abcabc";
  PCRE re("abc");
  int count = PCRE::GlobalReplace(&str, re, "X");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(str, "XX");
}

// ==================== Extract Tests ====================

TEST_F(PCRETest_586, ExtractSimple_586) {
  std::string out;
  PCRE re("(\\w+)@(\\w+)");
  EXPECT_TRUE(PCRE::Extract("user@host", re, "\\1 at \\2", &out));
  EXPECT_EQ(out, "user at host");
}

TEST_F(PCRETest_586, ExtractNoMatch_586) {
  std::string out;
  PCRE re("(\\d+)");
  EXPECT_FALSE(PCRE::Extract("abc", re, "\\1", &out));
}

TEST_F(PCRETest_586, ExtractWholeMatch_586) {
  std::string out;
  PCRE re("hello");
  EXPECT_TRUE(PCRE::Extract("say hello now", re, "\\0", &out));
  EXPECT_EQ(out, "hello");
}

// ==================== CheckRewriteString Tests ====================

TEST_F(PCRETest_586, CheckRewriteStringValid_586) {
  PCRE re("(a)(b)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1-\\2", &error));
  EXPECT_EQ(error, "");
}

TEST_F(PCRETest_586, CheckRewriteStringInvalidBackref_586) {
  PCRE re("(a)");
  std::string error;
  // Referencing group 5 when only 1 exists
  EXPECT_FALSE(re.CheckRewriteString("\\5", &error));
  EXPECT_FALSE(error.empty());
}

TEST_F(PCRETest_586, CheckRewriteStringNoGroups_586) {
  PCRE re("abc");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\0", &error));
}

// ==================== Complex Pattern Tests ====================

TEST_F(PCRETest_586, ComplexPatternMatching_586) {
  PCRE re("\\d{3}-\\d{4}");
  EXPECT_TRUE(re.DoMatch(absl::string_view("123-4567"), PCRE::ANCHOR_BOTH,
                          nullptr, nullptr, 0));
}

TEST_F(PCRETest_586, ComplexPatternNoMatch_586) {
  PCRE re("\\d{3}-\\d{4}");
  EXPECT_FALSE(re.DoMatch(absl::string_view("12-4567"), PCRE::ANCHOR_BOTH,
                           nullptr, nullptr, 0));
}

TEST_F(PCRETest_586, DotMatchesAnyChar_586) {
  PCRE re("a.c");
  EXPECT_TRUE(re.DoMatch(absl::string_view("abc"), PCRE::ANCHOR_BOTH,
                          nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch(absl::string_view("axc"), PCRE::ANCHOR_BOTH,
                          nullptr, nullptr, 0));
}

TEST_F(PCRETest_586, StarQuantifier_586) {
  PCRE re("ab*c");
  EXPECT_TRUE(re.DoMatch(absl::string_view("ac"), PCRE::ANCHOR_BOTH,
                          nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch(absl::string_view("abc"), PCRE::ANCHOR_BOTH,
                          nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch(absl::string_view("abbbbc"), PCRE::ANCHOR_BOTH,
                          nullptr, nullptr, 0));
}

TEST_F(PCRETest_586, PlusQuantifier_586) {
  PCRE re("ab+c");
  EXPECT_FALSE(re.DoMatch(absl::string_view("ac"), PCRE::ANCHOR_BOTH,
                           nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch(absl::string_view("abc"), PCRE::ANCHOR_BOTH,
                          nullptr, nullptr, 0));
}

TEST_F(PCRETest_586, AlternationPattern_586) {
  PCRE re("cat|dog");
  EXPECT_TRUE(re.DoMatch(absl::string_view("cat"), PCRE::ANCHOR_BOTH,
                          nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch(absl::string_view("dog"), PCRE::ANCHOR_BOTH,
                          nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch(absl::string_view("bird"), PCRE::ANCHOR_BOTH,
                           nullptr, nullptr, 0));
}

// ==================== DoMatch with Arg Tests ====================

TEST_F(PCRETest_586, DoMatchWithIntArg_586) {
  PCRE re("(\\d+)");
  int value;
  const PCRE::Arg arg(&value);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch(absl::string_view("12345"), PCRE::ANCHOR_BOTH,
                          nullptr, args, 1));
  EXPECT_EQ(value, 12345);
}

TEST_F(PCRETest_586, DoMatchWithStringArg_586) {
  PCRE re("(\\w+)");
  std::string value;
  const PCRE::Arg arg(&value);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch(absl::string_view("hello"), PCRE::ANCHOR_BOTH,
                          nullptr, args, 1));
  EXPECT_EQ(value, "hello");
}

TEST_F(PCRETest_586, DoMatchWithMultipleArgs_586) {
  PCRE re("(\\w+)=(\\d+)");
  std::string key;
  int val;
  const PCRE::Arg arg1(&key);
  const PCRE::Arg arg2(&val);
  const PCRE::Arg* args[] = {&arg1, &arg2};
  EXPECT_TRUE(re.DoMatch(absl::string_view("abc=42"), PCRE::ANCHOR_BOTH,
                          nullptr, args, 2));
  EXPECT_EQ(key, "abc");
  EXPECT_EQ(val, 42);
}

}  // namespace re2
