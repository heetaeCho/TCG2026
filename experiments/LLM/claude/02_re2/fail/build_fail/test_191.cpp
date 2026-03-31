#include "gtest/gtest.h"
#include "util/pcre.h"
#include <string>

namespace re2 {

// Test fixture for PCRE ConsumeFunctor tests
class PCREConsumeFunctorTest_191 : public ::testing::Test {
 protected:
  PCRE::ConsumeFunctor consume_;
};

// Test fixture for general PCRE tests
class PCRETest_191 : public ::testing::Test {
};

// Test fixture for PCRE::Arg tests
class PCREArgTest_191 : public ::testing::Test {
};

// ==================== PCRE Construction Tests ====================

TEST_F(PCRETest_191, ConstructFromCString_191) {
  PCRE re("hello");
  EXPECT_EQ("hello", re.pattern());
}

TEST_F(PCRETest_191, ConstructFromStdString_191) {
  std::string pat = "world";
  PCRE re(pat);
  EXPECT_EQ("world", re.pattern());
}

TEST_F(PCRETest_191, ConstructWithSimplePattern_191) {
  PCRE re("(\\d+)");
  EXPECT_EQ("(\\d+)", re.pattern());
}

TEST_F(PCRETest_191, InvalidPatternReportsError_191) {
  PCRE re("[invalid");
  EXPECT_FALSE(re.error().empty());
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST_F(PCRETest_191, NumberOfCapturingGroupsZero_191) {
  PCRE re("hello");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST_F(PCRETest_191, NumberOfCapturingGroupsOne_191) {
  PCRE re("(hello)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST_F(PCRETest_191, NumberOfCapturingGroupsMultiple_191) {
  PCRE re("(a)(b)(c)");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

// ==================== DoMatch Tests ====================

TEST_F(PCRETest_191, DoMatchFullAnchorMatch_191) {
  PCRE re("hello");
  absl::string_view text("hello");
  EXPECT_TRUE(re.DoMatch(text, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST_F(PCRETest_191, DoMatchFullAnchorNoMatch_191) {
  PCRE re("hello");
  absl::string_view text("hello world");
  EXPECT_FALSE(re.DoMatch(text, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST_F(PCRETest_191, DoMatchStartAnchor_191) {
  PCRE re("hello");
  absl::string_view text("hello world");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch(text, PCRE::ANCHOR_START, &consumed, nullptr, 0));
  EXPECT_EQ(5u, consumed);
}

TEST_F(PCRETest_191, DoMatchUnanchoredMatch_191) {
  PCRE re("world");
  absl::string_view text("hello world");
  EXPECT_TRUE(re.DoMatch(text, PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST_F(PCRETest_191, DoMatchUnanchoredNoMatch_191) {
  PCRE re("xyz");
  absl::string_view text("hello world");
  EXPECT_FALSE(re.DoMatch(text, PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST_F(PCRETest_191, DoMatchWithCapture_191) {
  PCRE re("(\\d+)");
  absl::string_view text("abc123def");
  int value = 0;
  PCRE::Arg arg(&value);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch(text, PCRE::UNANCHORED, nullptr, args, 1));
  EXPECT_EQ(123, value);
}

TEST_F(PCRETest_191, DoMatchWithStringCapture_191) {
  PCRE re("(\\w+)");
  absl::string_view text("hello world");
  std::string captured;
  PCRE::Arg arg(&captured);
  const PCRE::Arg* args[] = {&arg};
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch(text, PCRE::ANCHOR_START, &consumed, args, 1));
  EXPECT_EQ("hello", captured);
}

TEST_F(PCRETest_191, DoMatchEmptyString_191) {
  PCRE re("");
  absl::string_view text("");
  EXPECT_TRUE(re.DoMatch(text, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST_F(PCRETest_191, DoMatchEmptyPattern_191) {
  PCRE re("");
  absl::string_view text("nonempty");
  EXPECT_TRUE(re.DoMatch(text, PCRE::UNANCHORED, nullptr, nullptr, 0));
}

// ==================== Replace Tests ====================

TEST_F(PCRETest_191, ReplaceSimple_191) {
  std::string str = "hello world";
  EXPECT_TRUE(PCRE::Replace(&str, PCRE("world"), "there"));
  EXPECT_EQ("hello there", str);
}

TEST_F(PCRETest_191, ReplaceNoMatch_191) {
  std::string str = "hello world";
  EXPECT_FALSE(PCRE::Replace(&str, PCRE("xyz"), "there"));
  EXPECT_EQ("hello world", str);
}

TEST_F(PCRETest_191, ReplaceWithBackreference_191) {
  std::string str = "hello world";
  EXPECT_TRUE(PCRE::Replace(&str, PCRE("(\\w+)"), "\\1!"));
  EXPECT_EQ("hello! world", str);
}

// ==================== GlobalReplace Tests ====================

TEST_F(PCRETest_191, GlobalReplaceMultipleMatches_191) {
  std::string str = "aaa";
  int count = PCRE::GlobalReplace(&str, PCRE("a"), "b");
  EXPECT_EQ(3, count);
  EXPECT_EQ("bbb", str);
}

TEST_F(PCRETest_191, GlobalReplaceNoMatch_191) {
  std::string str = "hello";
  int count = PCRE::GlobalReplace(&str, PCRE("x"), "y");
  EXPECT_EQ(0, count);
  EXPECT_EQ("hello", str);
}

TEST_F(PCRETest_191, GlobalReplaceEmptyMatch_191) {
  std::string str = "abc";
  int count = PCRE::GlobalReplace(&str, PCRE("b"), "");
  EXPECT_EQ(1, count);
  EXPECT_EQ("ac", str);
}

// ==================== Extract Tests ====================

TEST_F(PCRETest_191, ExtractSimple_191) {
  std::string out;
  EXPECT_TRUE(PCRE::Extract("boris@kremlin.ru", PCRE("(.*)@([^.]*)"), "\\2!\\1", &out));
  EXPECT_EQ("kremlin!boris", out);
}

TEST_F(PCRETest_191, ExtractNoMatch_191) {
  std::string out;
  EXPECT_FALSE(PCRE::Extract("no match here", PCRE("(\\d+)@(\\d+)"), "\\1-\\2", &out));
}

// ==================== QuoteMeta Tests ====================

TEST_F(PCRETest_191, QuoteMetaSimple_191) {
  std::string quoted = PCRE::QuoteMeta("hello");
  EXPECT_EQ("hello", quoted);
}

TEST_F(PCRETest_191, QuoteMetaSpecialChars_191) {
  std::string quoted = PCRE::QuoteMeta("a.b");
  // The dot should be escaped
  PCRE re(quoted);
  absl::string_view text("a.b");
  EXPECT_TRUE(re.DoMatch(text, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  absl::string_view text2("axb");
  EXPECT_FALSE(re.DoMatch(text2, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST_F(PCRETest_191, QuoteMetaBrackets_191) {
  std::string quoted = PCRE::QuoteMeta("[a]");
  PCRE re(quoted);
  absl::string_view text("[a]");
  EXPECT_TRUE(re.DoMatch(text, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST_F(PCRETest_191, QuoteMetaEmptyString_191) {
  std::string quoted = PCRE::QuoteMeta("");
  EXPECT_EQ("", quoted);
}

// ==================== CheckRewriteString Tests ====================

TEST_F(PCRETest_191, CheckRewriteStringValid_191) {
  PCRE re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST_F(PCRETest_191, CheckRewriteStringInvalidBackref_191) {
  PCRE re("(\\w+)");
  std::string error;
  // \\2 references a non-existent group
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

TEST_F(PCRETest_191, CheckRewriteStringNoBackref_191) {
  PCRE re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("replacement", &error));
}

// ==================== HitLimit Tests ====================

TEST_F(PCRETest_191, HitLimitInitiallyFalse_191) {
  PCRE re("a");
  EXPECT_FALSE(re.HitLimit());
}

TEST_F(PCRETest_191, ClearHitLimit_191) {
  PCRE re("a");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// ==================== ConsumeFunctor Tests ====================

TEST_F(PCREConsumeFunctorTest_191, ConsumeNoArgs_191) {
  PCRE re("\\w+");
  absl::string_view input("hello world");
  EXPECT_TRUE(consume_(&input, re));
  EXPECT_EQ(" world", input);
}

TEST_F(PCREConsumeFunctorTest_191, ConsumeWithOneArg_191) {
  PCRE re("(\\w+)");
  absl::string_view input("hello world");
  std::string word;
  PCRE::Arg arg(&word);
  EXPECT_TRUE(consume_(&input, re, arg));
  EXPECT_EQ("hello", word);
  EXPECT_EQ(" world", input);
}

TEST_F(PCREConsumeFunctorTest_191, ConsumeNoMatch_191) {
  PCRE re("\\d+");
  absl::string_view input("hello");
  EXPECT_FALSE(consume_(&input, re));
  EXPECT_EQ("hello", input);
}

TEST_F(PCREConsumeFunctorTest_191, ConsumeMultipleCalls_191) {
  PCRE re("(\\w+)\\s*");
  absl::string_view input("hello world foo");
  std::string word;
  PCRE::Arg arg(&word);

  EXPECT_TRUE(consume_(&input, re, arg));
  EXPECT_EQ("hello", word);

  EXPECT_TRUE(consume_(&input, re, arg));
  EXPECT_EQ("world", word);

  EXPECT_TRUE(consume_(&input, re, arg));
  EXPECT_EQ("foo", word);
}

TEST_F(PCREConsumeFunctorTest_191, ConsumeWithIntArg_191) {
  PCRE re("(\\d+)");
  absl::string_view input("42abc");
  int value = 0;
  PCRE::Arg arg(&value);
  EXPECT_TRUE(consume_(&input, re, arg));
  EXPECT_EQ(42, value);
  EXPECT_EQ("abc", input);
}

TEST_F(PCREConsumeFunctorTest_191, ConsumeWithTwoArgs_191) {
  PCRE re("(\\w+)=(\\d+)");
  absl::string_view input("key=42 rest");
  std::string key;
  int val = 0;
  PCRE::Arg arg0(&key);
  PCRE::Arg arg1(&val);
  EXPECT_TRUE(consume_(&input, re, arg0, arg1));
  EXPECT_EQ("key", key);
  EXPECT_EQ(42, val);
  EXPECT_EQ(" rest", input);
}

TEST_F(PCREConsumeFunctorTest_191, ConsumeEmptyInput_191) {
  PCRE re("\\w+");
  absl::string_view input("");
  EXPECT_FALSE(consume_(&input, re));
}

TEST_F(PCREConsumeFunctorTest_191, ConsumeEmptyPattern_191) {
  PCRE re("");
  absl::string_view input("hello");
  EXPECT_TRUE(consume_(&input, re));
  // Empty pattern matches at the start, consuming 0 characters
  EXPECT_EQ("hello", input);
}

// ==================== PCRE::Arg Tests ====================

TEST_F(PCREArgTest_191, DefaultArgParse_191) {
  PCRE::Arg arg;
  EXPECT_TRUE(arg.Parse("anything", 8));
}

TEST_F(PCREArgTest_191, IntArgParse_191) {
  int val = 0;
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("123", 3));
  EXPECT_EQ(123, val);
}

TEST_F(PCREArgTest_191, IntArgParseInvalid_191) {
  int val = 0;
  PCRE::Arg arg(&val);
  EXPECT_FALSE(arg.Parse("abc", 3));
}

TEST_F(PCREArgTest_191, StringArgParse_191) {
  std::string val;
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("hello", 5));
  EXPECT_EQ("hello", val);
}

TEST_F(PCREArgTest_191, DoubleArgParse_191) {
  double val = 0.0;
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("3.14", 4));
  EXPECT_DOUBLE_EQ(3.14, val);
}

TEST_F(PCREArgTest_191, FloatArgParse_191) {
  float val = 0.0f;
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("2.5", 3));
  EXPECT_FLOAT_EQ(2.5f, val);
}

TEST_F(PCREArgTest_191, CharArgParse_191) {
  char val = '\0';
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("A", 1));
  EXPECT_EQ('A', val);
}

TEST_F(PCREArgTest_191, StringViewArgParse_191) {
  absl::string_view val;
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("hello", 5));
  EXPECT_EQ("hello", val);
}

TEST_F(PCREArgTest_191, VoidArgParse_191) {
  PCRE::Arg arg(static_cast<void*>(nullptr));
  EXPECT_TRUE(arg.Parse("anything", 8));
}

TEST_F(PCREArgTest_191, IntArgParseNegative_191) {
  int val = 0;
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("-42", 3));
  EXPECT_EQ(-42, val);
}

TEST_F(PCREArgTest_191, IntArgParseOverflow_191) {
  int val = 0;
  PCRE::Arg arg(&val);
  // Very large number that might overflow int
  EXPECT_FALSE(arg.Parse("99999999999999999999", 20));
}

TEST_F(PCREArgTest_191, EmptyStringParse_191) {
  int val = 0;
  PCRE::Arg arg(&val);
  EXPECT_FALSE(arg.Parse("", 0));
}

// ==================== Multiple Capture Groups DoMatch ====================

TEST_F(PCRETest_191, DoMatchMultipleCaptures_191) {
  PCRE re("(\\w+)\\s+(\\w+)");
  absl::string_view text("hello world");
  std::string s1, s2;
  PCRE::Arg a1(&s1), a2(&s2);
  const PCRE::Arg* args[] = {&a1, &a2};
  EXPECT_TRUE(re.DoMatch(text, PCRE::ANCHOR_BOTH, nullptr, args, 2));
  EXPECT_EQ("hello", s1);
  EXPECT_EQ("world", s2);
}

TEST_F(PCRETest_191, DoMatchPartialCapture_191) {
  PCRE re("(\\d+)-(\\d+)-(\\d+)");
  absl::string_view text("2023-01-15");
  int year = 0, month = 0, day = 0;
  PCRE::Arg a1(&year), a2(&month), a3(&day);
  const PCRE::Arg* args[] = {&a1, &a2, &a3};
  EXPECT_TRUE(re.DoMatch(text, PCRE::ANCHOR_BOTH, nullptr, args, 3));
  EXPECT_EQ(2023, year);
  EXPECT_EQ(1, month);
  EXPECT_EQ(15, day);
}

// ==================== ConsumeFunctor with multiple captures ====================

TEST_F(PCREConsumeFunctorTest_191, ConsumeThreeArgs_191) {
  PCRE re("(\\d+)/(\\d+)/(\\d+)");
  absl::string_view input("12/25/2023 rest");
  int m = 0, d = 0, y = 0;
  PCRE::Arg a0(&m), a1(&d), a2(&y);
  EXPECT_TRUE(consume_(&input, re, a0, a1, a2));
  EXPECT_EQ(12, m);
  EXPECT_EQ(25, d);
  EXPECT_EQ(2023, y);
  EXPECT_EQ(" rest", input);
}

// ==================== Pattern edge cases ====================

TEST_F(PCRETest_191, PatternWithAnchors_191) {
  PCRE re("^hello$");
  absl::string_view text("hello");
  EXPECT_TRUE(re.DoMatch(text, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST_F(PCRETest_191, PatternWithSpecialChars_191) {
  PCRE re("a\\.b");
  absl::string_view text1("a.b");
  EXPECT_TRUE(re.DoMatch(text1, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  absl::string_view text2("axb");
  EXPECT_FALSE(re.DoMatch(text2, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST_F(PCRETest_191, ReplaceFirstOccurrenceOnly_191) {
  std::string str = "aaa";
  EXPECT_TRUE(PCRE::Replace(&str, PCRE("a"), "b"));
  EXPECT_EQ("baa", str);
}

}  // namespace re2
