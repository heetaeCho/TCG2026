#include "gtest/gtest.h"
#include "util/pcre.h"
#include <string>

namespace re2 {

// Test fixture for PCRE tests
class PCRETest_189 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(PCRETest_189, ConstructFromCString_189) {
  PCRE re("hello");
  EXPECT_EQ("hello", re.pattern());
}

TEST_F(PCRETest_189, ConstructFromStdString_189) {
  std::string pattern = "world";
  PCRE re(pattern);
  EXPECT_EQ("world", re.pattern());
}

TEST_F(PCRETest_189, ConstructWithEmptyPattern_189) {
  PCRE re("");
  EXPECT_EQ("", re.pattern());
}

// ==================== FullMatch Tests ====================

TEST_F(PCRETest_189, FullMatchSimpleString_189) {
  PCRE re("hello");
  EXPECT_TRUE(PCRE::FullMatch("hello", re));
}

TEST_F(PCRETest_189, FullMatchFailsOnPartial_189) {
  PCRE re("hello");
  EXPECT_FALSE(PCRE::FullMatch("hello world", re));
}

TEST_F(PCRETest_189, FullMatchFailsOnMismatch_189) {
  PCRE re("hello");
  EXPECT_FALSE(PCRE::FullMatch("world", re));
}

TEST_F(PCRETest_189, FullMatchEmptyPatternEmptyString_189) {
  PCRE re("");
  EXPECT_TRUE(PCRE::FullMatch("", re));
}

TEST_F(PCRETest_189, FullMatchEmptyPatternNonEmptyString_189) {
  PCRE re("");
  EXPECT_FALSE(PCRE::FullMatch("abc", re));
}

TEST_F(PCRETest_189, FullMatchWithCapturingGroup_189) {
  PCRE re("(\\w+)");
  std::string captured;
  EXPECT_TRUE(PCRE::FullMatch("hello", re, &captured));
  EXPECT_EQ("hello", captured);
}

TEST_F(PCRETest_189, FullMatchWithMultipleCaptures_189) {
  PCRE re("(\\w+)\\s(\\w+)");
  std::string s1, s2;
  EXPECT_TRUE(PCRE::FullMatch("hello world", re, &s1, &s2));
  EXPECT_EQ("hello", s1);
  EXPECT_EQ("world", s2);
}

TEST_F(PCRETest_189, FullMatchWithIntCapture_189) {
  PCRE re("(\\d+)");
  int val = 0;
  EXPECT_TRUE(PCRE::FullMatch("12345", re, &val));
  EXPECT_EQ(12345, val);
}

TEST_F(PCRETest_189, FullMatchWithDoubleCapture_189) {
  PCRE re("([\\d.]+)");
  double val = 0.0;
  EXPECT_TRUE(PCRE::FullMatch("3.14", re, &val));
  EXPECT_DOUBLE_EQ(3.14, val);
}

TEST_F(PCRETest_189, FullMatchWithFloatCapture_189) {
  PCRE re("([\\d.]+)");
  float val = 0.0f;
  EXPECT_TRUE(PCRE::FullMatch("2.5", re, &val));
  EXPECT_FLOAT_EQ(2.5f, val);
}

TEST_F(PCRETest_189, FullMatchNoArgsNeeded_189) {
  PCRE re("abc");
  EXPECT_TRUE(PCRE::FullMatch("abc", re));
}

TEST_F(PCRETest_189, FullMatchRegexWithSpecialChars_189) {
  PCRE re("a\\.b");
  EXPECT_TRUE(PCRE::FullMatch("a.b", re));
  EXPECT_FALSE(PCRE::FullMatch("axb", re));
}

// ==================== PartialMatch Tests ====================

TEST_F(PCRETest_189, PartialMatchSimple_189) {
  PCRE re("hello");
  EXPECT_TRUE(PCRE::PartialMatch("say hello world", re));
}

TEST_F(PCRETest_189, PartialMatchFails_189) {
  PCRE re("xyz");
  EXPECT_FALSE(PCRE::PartialMatch("hello world", re));
}

TEST_F(PCRETest_189, PartialMatchWithCapture_189) {
  PCRE re("(\\d+)");
  int val = 0;
  EXPECT_TRUE(PCRE::PartialMatch("abc 42 def", re, &val));
  EXPECT_EQ(42, val);
}

TEST_F(PCRETest_189, PartialMatchEmptyPattern_189) {
  PCRE re("");
  EXPECT_TRUE(PCRE::PartialMatch("anything", re));
}

// ==================== Replace Tests ====================

TEST_F(PCRETest_189, ReplaceSimple_189) {
  std::string str = "hello world";
  PCRE re("world");
  EXPECT_TRUE(PCRE::Replace(&str, re, "there"));
  EXPECT_EQ("hello there", str);
}

TEST_F(PCRETest_189, ReplaceNoMatch_189) {
  std::string str = "hello world";
  PCRE re("xyz");
  EXPECT_FALSE(PCRE::Replace(&str, re, "abc"));
  EXPECT_EQ("hello world", str);
}

TEST_F(PCRETest_189, ReplaceWithBackreference_189) {
  std::string str = "hello world";
  PCRE re("(\\w+) (\\w+)");
  EXPECT_TRUE(PCRE::Replace(&str, re, "\\2 \\1"));
  EXPECT_EQ("world hello", str);
}

// ==================== GlobalReplace Tests ====================

TEST_F(PCRETest_189, GlobalReplaceMultiple_189) {
  std::string str = "aaa";
  PCRE re("a");
  int count = PCRE::GlobalReplace(&str, re, "b");
  EXPECT_EQ(3, count);
  EXPECT_EQ("bbb", str);
}

TEST_F(PCRETest_189, GlobalReplaceNone_189) {
  std::string str = "hello";
  PCRE re("x");
  int count = PCRE::GlobalReplace(&str, re, "y");
  EXPECT_EQ(0, count);
  EXPECT_EQ("hello", str);
}

TEST_F(PCRETest_189, GlobalReplaceSingle_189) {
  std::string str = "hello";
  PCRE re("ello");
  int count = PCRE::GlobalReplace(&str, re, "i");
  EXPECT_EQ(1, count);
  EXPECT_EQ("hi", str);
}

// ==================== Extract Tests ====================

TEST_F(PCRETest_189, ExtractSimple_189) {
  std::string out;
  PCRE re("(\\w+)@(\\w+)");
  EXPECT_TRUE(PCRE::Extract("user@host", re, "\\1 at \\2", &out));
  EXPECT_EQ("user at host", out);
}

TEST_F(PCRETest_189, ExtractNoMatch_189) {
  std::string out;
  PCRE re("(\\d+)");
  EXPECT_FALSE(PCRE::Extract("no digits here", re, "\\1", &out));
}

// ==================== QuoteMeta Tests ====================

TEST_F(PCRETest_189, QuoteMetaNoSpecialChars_189) {
  std::string result = PCRE::QuoteMeta("hello");
  PCRE re(result);
  EXPECT_TRUE(PCRE::FullMatch("hello", re));
}

TEST_F(PCRETest_189, QuoteMetaWithSpecialChars_189) {
  std::string result = PCRE::QuoteMeta("a.b+c*d");
  PCRE re(result);
  EXPECT_TRUE(PCRE::FullMatch("a.b+c*d", re));
  EXPECT_FALSE(PCRE::FullMatch("axbyczdw", re));
}

TEST_F(PCRETest_189, QuoteMetaEmpty_189) {
  std::string result = PCRE::QuoteMeta("");
  EXPECT_EQ("", result);
}

TEST_F(PCRETest_189, QuoteMetaParentheses_189) {
  std::string result = PCRE::QuoteMeta("(foo)");
  PCRE re(result);
  EXPECT_TRUE(PCRE::FullMatch("(foo)", re));
}

// ==================== CheckRewriteString Tests ====================

TEST_F(PCRETest_189, CheckRewriteStringValid_189) {
  PCRE re("(\\w+) (\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1-\\2", &error));
}

TEST_F(PCRETest_189, CheckRewriteStringInvalidBackref_189) {
  PCRE re("(\\w+)");
  std::string error;
  // \2 references a non-existent group
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST_F(PCRETest_189, NumberOfCapturingGroupsNone_189) {
  PCRE re("hello");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST_F(PCRETest_189, NumberOfCapturingGroupsOne_189) {
  PCRE re("(hello)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST_F(PCRETest_189, NumberOfCapturingGroupsMultiple_189) {
  PCRE re("(a)(b)(c)");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST_F(PCRETest_189, NumberOfCapturingGroupsNested_189) {
  PCRE re("((a)(b))");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

// ==================== HitLimit / ClearHitLimit Tests ====================

TEST_F(PCRETest_189, HitLimitInitiallyFalse_189) {
  PCRE re("abc");
  EXPECT_FALSE(re.HitLimit());
}

TEST_F(PCRETest_189, ClearHitLimit_189) {
  PCRE re("abc");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// ==================== Error Tests ====================

TEST_F(PCRETest_189, InvalidPatternHasError_189) {
  PCRE re("[invalid");
  EXPECT_FALSE(re.error().empty());
}

TEST_F(PCRETest_189, ValidPatternNoError_189) {
  PCRE re("valid");
  EXPECT_TRUE(re.error().empty());
}

// ==================== Pattern Tests ====================

TEST_F(PCRETest_189, PatternReturnsOriginal_189) {
  PCRE re("my_pattern");
  EXPECT_EQ("my_pattern", re.pattern());
}

// ==================== DoMatch Tests ====================

TEST_F(PCRETest_189, DoMatchAnchorBoth_189) {
  PCRE re("hello");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, &consumed, nullptr, 0));
}

TEST_F(PCRETest_189, DoMatchAnchorBothFails_189) {
  PCRE re("hello");
  size_t consumed = 0;
  EXPECT_FALSE(re.DoMatch("hello world", PCRE::ANCHOR_BOTH, &consumed, nullptr, 0));
}

TEST_F(PCRETest_189, DoMatchAnchorStart_189) {
  PCRE re("hello");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_START, &consumed, nullptr, 0));
}

TEST_F(PCRETest_189, DoMatchUnanchored_189) {
  PCRE re("world");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::UNANCHORED, &consumed, nullptr, 0));
}

TEST_F(PCRETest_189, DoMatchWithCapture_189) {
  PCRE re("(\\d+)");
  size_t consumed = 0;
  int val = 0;
  const PCRE::Arg* args[] = {new PCRE::Arg(&val)};
  EXPECT_TRUE(re.DoMatch("42", PCRE::ANCHOR_BOTH, &consumed, args, 1));
  EXPECT_EQ(42, val);
  delete args[0];
}

// ==================== Arg Tests ====================

TEST_F(PCRETest_189, ArgDefaultConstructor_189) {
  PCRE::Arg arg;
  // Default arg should parse null (accept anything)
  EXPECT_TRUE(arg.Parse("test", 4));
}

TEST_F(PCRETest_189, ArgParseInt_189) {
  int val = 0;
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("123", 3));
  EXPECT_EQ(123, val);
}

TEST_F(PCRETest_189, ArgParseString_189) {
  std::string val;
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("hello", 5));
  EXPECT_EQ("hello", val);
}

TEST_F(PCRETest_189, ArgParseDouble_189) {
  double val = 0.0;
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("3.14", 4));
  EXPECT_DOUBLE_EQ(3.14, val);
}

TEST_F(PCRETest_189, ArgParseFloat_189) {
  float val = 0.0f;
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("2.5", 3));
  EXPECT_FLOAT_EQ(2.5f, val);
}

TEST_F(PCRETest_189, ArgParseChar_189) {
  char val = '\0';
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("x", 1));
  EXPECT_EQ('x', val);
}

// ==================== FullMatchFunctor specific tests ====================

TEST_F(PCRETest_189, FullMatchFunctorNoArgs_189) {
  PCRE re("abc");
  EXPECT_TRUE(PCRE::FullMatch("abc", re));
}

TEST_F(PCRETest_189, FullMatchFunctorOneArg_189) {
  PCRE re("(\\d+)");
  int val = 0;
  EXPECT_TRUE(PCRE::FullMatch("999", re, &val));
  EXPECT_EQ(999, val);
}

TEST_F(PCRETest_189, FullMatchFunctorTwoArgs_189) {
  PCRE re("(\\w+)-(\\d+)");
  std::string s;
  int n = 0;
  EXPECT_TRUE(PCRE::FullMatch("abc-123", re, &s, &n));
  EXPECT_EQ("abc", s);
  EXPECT_EQ(123, n);
}

TEST_F(PCRETest_189, FullMatchFunctorThreeArgs_189) {
  PCRE re("(\\w+)-(\\w+)-(\\w+)");
  std::string s1, s2, s3;
  EXPECT_TRUE(PCRE::FullMatch("a-b-c", re, &s1, &s2, &s3));
  EXPECT_EQ("a", s1);
  EXPECT_EQ("b", s2);
  EXPECT_EQ("c", s3);
}

// ==================== Boundary / Edge Cases ====================

TEST_F(PCRETest_189, FullMatchLongString_189) {
  std::string long_str(10000, 'a');
  std::string pattern = "a+";
  PCRE re(pattern);
  EXPECT_TRUE(PCRE::FullMatch(long_str, re));
}

TEST_F(PCRETest_189, FullMatchNullCharInString_189) {
  // Test with a string containing embedded null
  std::string text("ab\0cd", 5);
  PCRE re("ab.cd");
  EXPECT_TRUE(PCRE::FullMatch(text, re));
}

TEST_F(PCRETest_189, PartialMatchAtStart_189) {
  PCRE re("^hello");
  EXPECT_TRUE(PCRE::PartialMatch("hello world", re));
  EXPECT_FALSE(PCRE::PartialMatch("say hello", re));
}

TEST_F(PCRETest_189, PartialMatchAtEnd_189) {
  PCRE re("world$");
  EXPECT_TRUE(PCRE::PartialMatch("hello world", re));
  EXPECT_FALSE(PCRE::PartialMatch("world hello", re));
}

TEST_F(PCRETest_189, ReplaceEmptyMatch_189) {
  std::string str = "abc";
  PCRE re("");
  EXPECT_TRUE(PCRE::Replace(&str, re, "X"));
  // Empty match at the beginning should insert X
  EXPECT_EQ("Xabc", str);
}

TEST_F(PCRETest_189, GlobalReplaceEmptyString_189) {
  std::string str = "";
  PCRE re("a");
  int count = PCRE::GlobalReplace(&str, re, "b");
  EXPECT_EQ(0, count);
  EXPECT_EQ("", str);
}

TEST_F(PCRETest_189, FullMatchStringViewCapture_189) {
  PCRE re("(\\w+)");
  absl::string_view sv;
  EXPECT_TRUE(PCRE::FullMatch("hello", re, &sv));
  EXPECT_EQ("hello", sv);
}

}  // namespace re2
