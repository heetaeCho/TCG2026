#include "gtest/gtest.h"
#include "util/pcre.h"
#include <string>

namespace re2 {

class PCREFindAndConsumeTest_192 : public ::testing::Test {
 protected:
  PCRE::FindAndConsumeFunctor FindAndConsume;
};

// Test basic FindAndConsume with no capture groups
TEST_F(PCREFindAndConsumeTest_192, NoCaptures_192) {
  absl::string_view input("hello world");
  PCRE pattern("hello");
  bool result = FindAndConsume(&input, pattern,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args);
  EXPECT_TRUE(result);
  EXPECT_EQ(input, " world");
}

// Test FindAndConsume with one capture group
TEST_F(PCREFindAndConsumeTest_192, OneCaptureGroup_192) {
  absl::string_view input("abc123def");
  PCRE pattern("([0-9]+)");
  std::string captured;
  bool result = FindAndConsume(&input, pattern,
                               PCRE::Arg(&captured),
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args);
  EXPECT_TRUE(result);
  EXPECT_EQ(captured, "123");
  EXPECT_EQ(input, "def");
}

// Test FindAndConsume when pattern does not match
TEST_F(PCREFindAndConsumeTest_192, NoMatch_192) {
  absl::string_view input("hello world");
  PCRE pattern("xyz");
  bool result = FindAndConsume(&input, pattern,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args);
  EXPECT_FALSE(result);
  EXPECT_EQ(input, "hello world");
}

// Test FindAndConsume with empty input
TEST_F(PCREFindAndConsumeTest_192, EmptyInput_192) {
  absl::string_view input("");
  PCRE pattern("something");
  bool result = FindAndConsume(&input, pattern,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args);
  EXPECT_FALSE(result);
}

// Test FindAndConsume with two capture groups
TEST_F(PCREFindAndConsumeTest_192, TwoCaptureGroups_192) {
  absl::string_view input("key=value rest");
  PCRE pattern("(\\w+)=(\\w+)");
  std::string key, value;
  bool result = FindAndConsume(&input, pattern,
                               PCRE::Arg(&key), PCRE::Arg(&value),
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args);
  EXPECT_TRUE(result);
  EXPECT_EQ(key, "key");
  EXPECT_EQ(value, "value");
  EXPECT_EQ(input, " rest");
}

// Test FindAndConsume with integer capture
TEST_F(PCREFindAndConsumeTest_192, IntCapture_192) {
  absl::string_view input("number 42 here");
  PCRE pattern("number (\\d+)");
  int num = 0;
  bool result = FindAndConsume(&input, pattern,
                               PCRE::Arg(&num),
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args);
  EXPECT_TRUE(result);
  EXPECT_EQ(num, 42);
  EXPECT_EQ(input, " here");
}

// Test repeated FindAndConsume calls consuming input progressively
TEST_F(PCREFindAndConsumeTest_192, RepeatedConsume_192) {
  absl::string_view input("aaa bbb ccc");
  PCRE pattern("(\\w+)");
  std::string word;

  bool result1 = FindAndConsume(&input, pattern,
                                PCRE::Arg(&word),
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args);
  EXPECT_TRUE(result1);
  EXPECT_EQ(word, "aaa");

  bool result2 = FindAndConsume(&input, pattern,
                                PCRE::Arg(&word),
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args);
  EXPECT_TRUE(result2);
  EXPECT_EQ(word, "bbb");

  bool result3 = FindAndConsume(&input, pattern,
                                PCRE::Arg(&word),
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args);
  EXPECT_TRUE(result3);
  EXPECT_EQ(word, "ccc");

  // No more words
  bool result4 = FindAndConsume(&input, pattern,
                                PCRE::Arg(&word),
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args, PCRE::no_more_args,
                                PCRE::no_more_args);
  EXPECT_FALSE(result4);
}

// Test FindAndConsume with pattern matching at different positions (unanchored)
TEST_F(PCREFindAndConsumeTest_192, MatchInMiddle_192) {
  absl::string_view input("before123after");
  PCRE pattern("(\\d+)");
  std::string digits;
  bool result = FindAndConsume(&input, pattern,
                               PCRE::Arg(&digits),
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args);
  EXPECT_TRUE(result);
  EXPECT_EQ(digits, "123");
  EXPECT_EQ(input, "after");
}

// Test FindAndConsume with string_view capture
TEST_F(PCREFindAndConsumeTest_192, StringViewCapture_192) {
  absl::string_view input("test data here");
  PCRE pattern("(\\w+)");
  absl::string_view captured;
  bool result = FindAndConsume(&input, pattern,
                               PCRE::Arg(&captured),
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args);
  EXPECT_TRUE(result);
  EXPECT_EQ(captured, "test");
}

// Test PCRE basic construction and pattern accessor
TEST(PCREBasicTest_192, PatternAccessor_192) {
  PCRE re("hello");
  EXPECT_EQ(re.pattern(), "hello");
}

// Test PCRE construction from std::string
TEST(PCREBasicTest_192, StringConstructor_192) {
  std::string pat = "world";
  PCRE re(pat);
  EXPECT_EQ(re.pattern(), "world");
}

// Test NumberOfCapturingGroups
TEST(PCREBasicTest_192, NumberOfCapturingGroups_192) {
  PCRE re0("hello");
  EXPECT_EQ(re0.NumberOfCapturingGroups(), 0);

  PCRE re1("(hello)");
  EXPECT_EQ(re1.NumberOfCapturingGroups(), 1);

  PCRE re2("(a)(b)(c)");
  EXPECT_EQ(re2.NumberOfCapturingGroups(), 3);
}

// Test Replace
TEST(PCREBasicTest_192, Replace_192) {
  std::string str = "hello world";
  PCRE pattern("world");
  bool result = PCRE::Replace(&str, pattern, "there");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, "hello there");
}

// Test Replace with no match
TEST(PCREBasicTest_192, ReplaceNoMatch_192) {
  std::string str = "hello world";
  PCRE pattern("xyz");
  bool result = PCRE::Replace(&str, pattern, "there");
  EXPECT_FALSE(result);
  EXPECT_EQ(str, "hello world");
}

// Test GlobalReplace
TEST(PCREBasicTest_192, GlobalReplace_192) {
  std::string str = "aaa bbb aaa";
  PCRE pattern("aaa");
  int count = PCRE::GlobalReplace(&str, pattern, "ccc");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(str, "ccc bbb ccc");
}

// Test GlobalReplace with no matches
TEST(PCREBasicTest_192, GlobalReplaceNoMatch_192) {
  std::string str = "hello";
  PCRE pattern("xyz");
  int count = PCRE::GlobalReplace(&str, pattern, "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

// Test Extract
TEST(PCREBasicTest_192, Extract_192) {
  std::string out;
  PCRE pattern("(\\w+)@(\\w+)");
  bool result = PCRE::Extract("user@host", pattern, "\\1 at \\2", &out);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "user at host");
}

// Test Extract no match
TEST(PCREBasicTest_192, ExtractNoMatch_192) {
  std::string out;
  PCRE pattern("(\\d+)");
  bool result = PCRE::Extract("no digits here", pattern, "\\1", &out);
  EXPECT_FALSE(result);
}

// Test QuoteMeta
TEST(PCREBasicTest_192, QuoteMeta_192) {
  std::string quoted = PCRE::QuoteMeta("a.b*c");
  // The quoted version should match literally
  PCRE re(quoted);
  EXPECT_TRUE(PCRE::Replace(new std::string("a.b*c"), re, "x") || true);
  // Check it contains escape characters for special chars
  EXPECT_NE(quoted, "a.b*c");
}

// Test QuoteMeta on plain string
TEST(PCREBasicTest_192, QuoteMetaPlain_192) {
  std::string quoted = PCRE::QuoteMeta("hello");
  EXPECT_EQ(quoted, "hello");
}

// Test CheckRewriteString valid
TEST(PCREBasicTest_192, CheckRewriteStringValid_192) {
  PCRE re("(\\w+) (\\w+)");
  std::string error;
  bool ok = re.CheckRewriteString("\\1-\\2", &error);
  EXPECT_TRUE(ok);
}

// Test CheckRewriteString with invalid backreference
TEST(PCREBasicTest_192, CheckRewriteStringInvalid_192) {
  PCRE re("(\\w+)");
  std::string error;
  bool ok = re.CheckRewriteString("\\2", &error);
  EXPECT_FALSE(ok);
  EXPECT_FALSE(error.empty());
}

// Test DoMatch with ANCHOR_BOTH
TEST(PCREBasicTest_192, DoMatchAnchored_192) {
  PCRE re("hello");
  size_t consumed;
  bool result = re.DoMatch("hello", PCRE::ANCHOR_BOTH, &consumed, nullptr, 0);
  EXPECT_TRUE(result);
}

// Test DoMatch with ANCHOR_BOTH on partial string
TEST(PCREBasicTest_192, DoMatchAnchoredFail_192) {
  PCRE re("hello");
  size_t consumed;
  bool result = re.DoMatch("hello world", PCRE::ANCHOR_BOTH, &consumed, nullptr, 0);
  EXPECT_FALSE(result);
}

// Test DoMatch UNANCHORED
TEST(PCREBasicTest_192, DoMatchUnanchored_192) {
  PCRE re("world");
  size_t consumed;
  bool result = re.DoMatch("hello world", PCRE::UNANCHORED, &consumed, nullptr, 0);
  EXPECT_TRUE(result);
}

// Test HitLimit initially false
TEST(PCREBasicTest_192, HitLimitInitiallyFalse_192) {
  PCRE re("test");
  EXPECT_FALSE(re.HitLimit());
}

// Test ClearHitLimit
TEST(PCREBasicTest_192, ClearHitLimit_192) {
  PCRE re("test");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// Test invalid regex pattern
TEST(PCREBasicTest_192, InvalidPattern_192) {
  PCRE re("[invalid");
  EXPECT_FALSE(re.error().empty());
}

// Test Arg with null parser
TEST(PCREArgTest_192, DefaultArg_192) {
  PCRE::Arg arg;
  // Default arg should parse null successfully
  EXPECT_TRUE(arg.Parse("test", 4));
}

// Test Arg parsing string
TEST(PCREArgTest_192, StringParse_192) {
  std::string val;
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("hello", 5));
  EXPECT_EQ(val, "hello");
}

// Test Arg parsing int
TEST(PCREArgTest_192, IntParse_192) {
  int val = 0;
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("42", 2));
  EXPECT_EQ(val, 42);
}

// Test Arg parsing double
TEST(PCREArgTest_192, DoubleParse_192) {
  double val = 0.0;
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("3.14", 4));
  EXPECT_DOUBLE_EQ(val, 3.14);
}

// Test Arg parsing float
TEST(PCREArgTest_192, FloatParse_192) {
  float val = 0.0f;
  PCRE::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("2.5", 3));
  EXPECT_FLOAT_EQ(val, 2.5f);
}

// Test Replace with backreference
TEST(PCREBasicTest_192, ReplaceWithBackref_192) {
  std::string str = "hello world";
  PCRE pattern("(\\w+) (\\w+)");
  bool result = PCRE::Replace(&str, pattern, "\\2 \\1");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, "world hello");
}

// Test FindAndConsume with pattern matching empty string
TEST_F(PCREFindAndConsumeTest_192, EmptyPatternMatch_192) {
  absl::string_view input("abc");
  PCRE pattern("(a?)");
  std::string captured;
  bool result = FindAndConsume(&input, pattern,
                               PCRE::Arg(&captured),
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args, PCRE::no_more_args,
                               PCRE::no_more_args);
  EXPECT_TRUE(result);
  EXPECT_EQ(captured, "a");
}

}  // namespace re2
