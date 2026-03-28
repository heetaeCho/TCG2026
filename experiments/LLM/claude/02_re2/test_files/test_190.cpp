#include "gtest/gtest.h"
#include "util/pcre.h"
#include <string>

namespace re2 {

// Test fixture for PCRE tests
class PCRETest_190 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(PCRETest_190, ConstructFromCString_190) {
  PCRE re("hello");
  EXPECT_EQ(re.pattern(), "hello");
}

TEST_F(PCRETest_190, ConstructFromStdString_190) {
  std::string pattern = "world";
  PCRE re(pattern);
  EXPECT_EQ(re.pattern(), "world");
}

TEST_F(PCRETest_190, ConstructWithOption_190) {
  PCRE re("test", PCRE::UNANCHORED);
  EXPECT_EQ(re.pattern(), "test");
}

TEST_F(PCRETest_190, ConstructFromStdStringWithOption_190) {
  std::string pattern = "foo";
  PCRE re(pattern, PCRE::UNANCHORED);
  EXPECT_EQ(re.pattern(), "foo");
}

// ==================== Pattern and Error Tests ====================

TEST_F(PCRETest_190, PatternReturnsCorrectValue_190) {
  PCRE re("abc.*def");
  EXPECT_EQ(re.pattern(), "abc.*def");
}

TEST_F(PCRETest_190, ValidPatternHasNoError_190) {
  PCRE re("hello");
  EXPECT_TRUE(re.error().empty());
}

TEST_F(PCRETest_190, InvalidPatternHasError_190) {
  PCRE re("[invalid");
  EXPECT_FALSE(re.error().empty());
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST_F(PCRETest_190, NoCapturingGroups_190) {
  PCRE re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(PCRETest_190, OneCapturingGroup_190) {
  PCRE re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST_F(PCRETest_190, MultipleCapturingGroups_190) {
  PCRE re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(PCRETest_190, InvalidPatternCapturingGroups_190) {
  PCRE re("[invalid");
  // Invalid pattern should return -1 or some error indicator
  EXPECT_LE(re.NumberOfCapturingGroups(), 0);
}

// ==================== PartialMatch Tests ====================

TEST_F(PCRETest_190, PartialMatchSimple_190) {
  PCRE re("ell");
  EXPECT_TRUE(PCRE::PartialMatch("hello", re));
}

TEST_F(PCRETest_190, PartialMatchNoMatch_190) {
  PCRE re("xyz");
  EXPECT_FALSE(PCRE::PartialMatch("hello", re));
}

TEST_F(PCRETest_190, PartialMatchEmptyPattern_190) {
  PCRE re("");
  EXPECT_TRUE(PCRE::PartialMatch("hello", re));
}

TEST_F(PCRETest_190, PartialMatchEmptyText_190) {
  PCRE re("hello");
  EXPECT_FALSE(PCRE::PartialMatch("", re));
}

TEST_F(PCRETest_190, PartialMatchEmptyTextEmptyPattern_190) {
  PCRE re("");
  EXPECT_TRUE(PCRE::PartialMatch("", re));
}

TEST_F(PCRETest_190, PartialMatchWithCapture_190) {
  PCRE re("(\\w+)@(\\w+)");
  std::string user, domain;
  EXPECT_TRUE(PCRE::PartialMatch("user@domain", re, &user, &domain));
  EXPECT_EQ(user, "user");
  EXPECT_EQ(domain, "domain");
}

TEST_F(PCRETest_190, PartialMatchWithIntCapture_190) {
  PCRE re("(\\d+)");
  int value;
  EXPECT_TRUE(PCRE::PartialMatch("abc123def", re, &value));
  EXPECT_EQ(value, 123);
}

TEST_F(PCRETest_190, PartialMatchWithStringViewCapture_190) {
  PCRE re("(\\w+)");
  absl::string_view sv;
  EXPECT_TRUE(PCRE::PartialMatch("hello world", re, &sv));
  EXPECT_EQ(sv, "hello");
}

// ==================== FullMatch Tests ====================

TEST_F(PCRETest_190, FullMatchSimple_190) {
  PCRE re("hello");
  EXPECT_TRUE(PCRE::FullMatch("hello", re));
}

TEST_F(PCRETest_190, FullMatchFails_190) {
  PCRE re("hello");
  EXPECT_FALSE(PCRE::FullMatch("hello world", re));
}

TEST_F(PCRETest_190, FullMatchWithCapture_190) {
  PCRE re("(\\d+)-(\\d+)");
  int a, b;
  EXPECT_TRUE(PCRE::FullMatch("123-456", re, &a, &b));
  EXPECT_EQ(a, 123);
  EXPECT_EQ(b, 456);
}

TEST_F(PCRETest_190, FullMatchEmptyStringEmptyPattern_190) {
  PCRE re("");
  EXPECT_TRUE(PCRE::FullMatch("", re));
}

TEST_F(PCRETest_190, FullMatchEmptyStringNonEmptyPattern_190) {
  PCRE re("hello");
  EXPECT_FALSE(PCRE::FullMatch("", re));
}

// ==================== DoMatch Tests ====================

TEST_F(PCRETest_190, DoMatchAnchored_190) {
  PCRE re("hello");
  size_t consumed;
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, &consumed, nullptr, 0));
}

TEST_F(PCRETest_190, DoMatchUnanchored_190) {
  PCRE re("ell");
  size_t consumed;
  EXPECT_TRUE(re.DoMatch("hello", PCRE::UNANCHORED, &consumed, nullptr, 0));
}

TEST_F(PCRETest_190, DoMatchAnchorStart_190) {
  PCRE re("hel");
  size_t consumed;
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_START, &consumed, nullptr, 0));
}

TEST_F(PCRETest_190, DoMatchAnchorStartFails_190) {
  PCRE re("ell");
  size_t consumed;
  EXPECT_FALSE(re.DoMatch("hello", PCRE::ANCHOR_START, &consumed, nullptr, 0));
}

// ==================== Replace Tests ====================

TEST_F(PCRETest_190, ReplaceSimple_190) {
  std::string str = "hello world";
  PCRE re("world");
  EXPECT_TRUE(PCRE::Replace(&str, re, "there"));
  EXPECT_EQ(str, "hello there");
}

TEST_F(PCRETest_190, ReplaceNoMatch_190) {
  std::string str = "hello world";
  PCRE re("xyz");
  EXPECT_FALSE(PCRE::Replace(&str, re, "there"));
  EXPECT_EQ(str, "hello world");
}

TEST_F(PCRETest_190, ReplaceWithBackreference_190) {
  std::string str = "hello world";
  PCRE re("(\\w+) (\\w+)");
  EXPECT_TRUE(PCRE::Replace(&str, re, "\\2 \\1"));
  EXPECT_EQ(str, "world hello");
}

// ==================== GlobalReplace Tests ====================

TEST_F(PCRETest_190, GlobalReplaceSimple_190) {
  std::string str = "aaa";
  PCRE re("a");
  int count = PCRE::GlobalReplace(&str, re, "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "bbb");
}

TEST_F(PCRETest_190, GlobalReplaceNoMatch_190) {
  std::string str = "hello";
  PCRE re("xyz");
  int count = PCRE::GlobalReplace(&str, re, "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

TEST_F(PCRETest_190, GlobalReplaceMultiple_190) {
  std::string str = "foo bar foo";
  PCRE re("foo");
  int count = PCRE::GlobalReplace(&str, re, "baz");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(str, "baz bar baz");
}

// ==================== Extract Tests ====================

TEST_F(PCRETest_190, ExtractSimple_190) {
  std::string out;
  PCRE re("(\\w+)@(\\w+)");
  EXPECT_TRUE(PCRE::Extract("user@host", re, "\\1 at \\2", &out));
  EXPECT_EQ(out, "user at host");
}

TEST_F(PCRETest_190, ExtractNoMatch_190) {
  std::string out;
  PCRE re("(\\d+)");
  EXPECT_FALSE(PCRE::Extract("hello", re, "\\1", &out));
}

// ==================== QuoteMeta Tests ====================

TEST_F(PCRETest_190, QuoteMetaSimple_190) {
  std::string quoted = PCRE::QuoteMeta("hello");
  EXPECT_EQ(quoted, "hello");
}

TEST_F(PCRETest_190, QuoteMetaSpecialChars_190) {
  std::string quoted = PCRE::QuoteMeta("a.b");
  PCRE re(quoted);
  EXPECT_TRUE(PCRE::FullMatch("a.b", re));
  EXPECT_FALSE(PCRE::FullMatch("axb", re));
}

TEST_F(PCRETest_190, QuoteMetaEmpty_190) {
  std::string quoted = PCRE::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

TEST_F(PCRETest_190, QuoteMetaBrackets_190) {
  std::string quoted = PCRE::QuoteMeta("[hello]");
  PCRE re(quoted);
  EXPECT_TRUE(PCRE::FullMatch("[hello]", re));
}

TEST_F(PCRETest_190, QuoteMetaParens_190) {
  std::string quoted = PCRE::QuoteMeta("(test)");
  PCRE re(quoted);
  EXPECT_TRUE(PCRE::FullMatch("(test)", re));
}

// ==================== CheckRewriteString Tests ====================

TEST_F(PCRETest_190, CheckRewriteStringValid_190) {
  PCRE re("(\\w+) (\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1-\\2", &error));
}

TEST_F(PCRETest_190, CheckRewriteStringInvalidBackref_190) {
  PCRE re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ==================== HitLimit Tests ====================

TEST_F(PCRETest_190, HitLimitInitiallyFalse_190) {
  PCRE re("hello");
  EXPECT_FALSE(re.HitLimit());
}

TEST_F(PCRETest_190, ClearHitLimit_190) {
  PCRE re("hello");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// ==================== Arg Tests ====================

TEST_F(PCRETest_190, ArgDefaultConstructor_190) {
  PCRE::Arg arg;
  // Default arg should parse null successfully
  EXPECT_TRUE(arg.Parse(nullptr, 0));
}

TEST_F(PCRETest_190, ArgWithVoidPtr_190) {
  PCRE::Arg arg(static_cast<void*>(nullptr));
  EXPECT_TRUE(arg.Parse(nullptr, 0));
}

TEST_F(PCRETest_190, ArgWithIntPtr_190) {
  int value = 0;
  PCRE::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("42", 2));
  EXPECT_EQ(value, 42);
}

TEST_F(PCRETest_190, ArgWithStringPtr_190) {
  std::string value;
  PCRE::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("hello", 5));
  EXPECT_EQ(value, "hello");
}

TEST_F(PCRETest_190, ArgWithDoublePtr_190) {
  double value = 0.0;
  PCRE::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("3.14", 4));
  EXPECT_DOUBLE_EQ(value, 3.14);
}

TEST_F(PCRETest_190, ArgWithFloatPtr_190) {
  float value = 0.0f;
  PCRE::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("2.5", 3));
  EXPECT_FLOAT_EQ(value, 2.5f);
}

TEST_F(PCRETest_190, ArgParseIntInvalid_190) {
  int value = 0;
  PCRE::Arg arg(&value);
  EXPECT_FALSE(arg.Parse("abc", 3));
}

TEST_F(PCRETest_190, ArgParseCharPtr_190) {
  char value = 0;
  PCRE::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("x", 1));
  EXPECT_EQ(value, 'x');
}

// ==================== Complex Pattern Tests ====================

TEST_F(PCRETest_190, PartialMatchComplexPattern_190) {
  PCRE re("(\\d{4})-(\\d{2})-(\\d{2})");
  std::string year, month, day;
  EXPECT_TRUE(PCRE::PartialMatch("Date: 2023-01-15", re, &year, &month, &day));
  EXPECT_EQ(year, "2023");
  EXPECT_EQ(month, "01");
  EXPECT_EQ(day, "15");
}

TEST_F(PCRETest_190, FullMatchWithMultipleIntCaptures_190) {
  PCRE re("(\\d+)\\+(\\d+)=(\\d+)");
  int a, b, c;
  EXPECT_TRUE(PCRE::FullMatch("1+2=3", re, &a, &b, &c));
  EXPECT_EQ(a, 1);
  EXPECT_EQ(b, 2);
  EXPECT_EQ(c, 3);
}

TEST_F(PCRETest_190, PartialMatchWithNoCaptures_190) {
  PCRE re("\\d+");
  EXPECT_TRUE(PCRE::PartialMatch("abc123", re));
}

TEST_F(PCRETest_190, FullMatchDotStar_190) {
  PCRE re(".*");
  EXPECT_TRUE(PCRE::FullMatch("anything goes here", re));
}

TEST_F(PCRETest_190, FullMatchDotStarEmpty_190) {
  PCRE re(".*");
  EXPECT_TRUE(PCRE::FullMatch("", re));
}

// ==================== PartialMatchFunctor specific tests ====================

TEST_F(PCRETest_190, PartialMatchFunctorNoArgs_190) {
  PCRE re("hello");
  PCRE::PartialMatchFunctor pmf;
  EXPECT_TRUE(pmf("hello world", re, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args));
}

TEST_F(PCRETest_190, PartialMatchFunctorWithOneArg_190) {
  PCRE re("(\\w+)");
  std::string captured;
  PCRE::Arg arg(&captured);
  PCRE::PartialMatchFunctor pmf;
  EXPECT_TRUE(pmf("hello", re, arg,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args));
  EXPECT_EQ(captured, "hello");
}

TEST_F(PCRETest_190, PartialMatchFunctorNoMatch_190) {
  PCRE re("xyz");
  PCRE::PartialMatchFunctor pmf;
  EXPECT_FALSE(pmf("hello", re, PCRE::no_more_args,
                    PCRE::no_more_args, PCRE::no_more_args,
                    PCRE::no_more_args, PCRE::no_more_args,
                    PCRE::no_more_args, PCRE::no_more_args,
                    PCRE::no_more_args, PCRE::no_more_args,
                    PCRE::no_more_args, PCRE::no_more_args,
                    PCRE::no_more_args, PCRE::no_more_args,
                    PCRE::no_more_args, PCRE::no_more_args,
                    PCRE::no_more_args));
}

TEST_F(PCRETest_190, PartialMatchFunctorWithTwoArgs_190) {
  PCRE re("(\\w+) (\\w+)");
  std::string first, second;
  PCRE::Arg arg0(&first);
  PCRE::Arg arg1(&second);
  PCRE::PartialMatchFunctor pmf;
  EXPECT_TRUE(pmf("hello world", re, arg0, arg1,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args,
                   PCRE::no_more_args, PCRE::no_more_args));
  EXPECT_EQ(first, "hello");
  EXPECT_EQ(second, "world");
}

// ==================== Boundary / Edge Cases ====================

TEST_F(PCRETest_190, ReplaceEmptyString_190) {
  std::string str = "";
  PCRE re(".*");
  EXPECT_TRUE(PCRE::Replace(&str, re, "replaced"));
  EXPECT_EQ(str, "replaced");
}

TEST_F(PCRETest_190, GlobalReplaceEmptyMatch_190) {
  std::string str = "abc";
  PCRE re("");
  int count = PCRE::GlobalReplace(&str, re, "x");
  // Empty pattern matches at every position
  EXPECT_GE(count, 1);
}

TEST_F(PCRETest_190, FullMatchSpecialRegexChars_190) {
  std::string quoted = PCRE::QuoteMeta("a+b*c?d");
  PCRE re(quoted);
  EXPECT_TRUE(PCRE::FullMatch("a+b*c?d", re));
  EXPECT_FALSE(PCRE::FullMatch("aabccd", re));
}

TEST_F(PCRETest_190, PartialMatchAtStart_190) {
  PCRE re("^hello");
  EXPECT_TRUE(PCRE::PartialMatch("hello world", re));
  EXPECT_FALSE(PCRE::PartialMatch("say hello", re));
}

TEST_F(PCRETest_190, PartialMatchAtEnd_190) {
  PCRE re("world$");
  EXPECT_TRUE(PCRE::PartialMatch("hello world", re));
  EXPECT_FALSE(PCRE::PartialMatch("world hello", re));
}

}  // namespace re2
