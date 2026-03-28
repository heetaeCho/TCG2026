#include "re2/re2.h"

#include <string>
#include <map>
#include <vector>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

// ============================================================
// FindAndConsume tests
// ============================================================

class FindAndConsumeTest_10 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

TEST_F(FindAndConsumeTest_10, BasicFindAndConsume_10) {
  absl::string_view input("one two three");
  std::string word;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\w+)", &word));
  EXPECT_EQ(word, "one");
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\w+)", &word));
  EXPECT_EQ(word, "two");
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\w+)", &word));
  EXPECT_EQ(word, "three");
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\w+)", &word));
}

TEST_F(FindAndConsumeTest_10, FindAndConsumeNoCapture_10) {
  absl::string_view input("abc123def456");
  EXPECT_TRUE(RE2::FindAndConsume(&input, "[a-z]+"));
  // After consuming "abc", input should start at "123def456"
  EXPECT_TRUE(RE2::FindAndConsume(&input, "\\d+"));
  // After consuming "123", input should start at "def456"
  EXPECT_TRUE(RE2::FindAndConsume(&input, "[a-z]+"));
  EXPECT_TRUE(RE2::FindAndConsume(&input, "\\d+"));
  EXPECT_FALSE(RE2::FindAndConsume(&input, "\\d+"));
}

TEST_F(FindAndConsumeTest_10, FindAndConsumeInteger_10) {
  absl::string_view input("x = 42, y = 13");
  int val;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &val));
  EXPECT_EQ(val, 42);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &val));
  EXPECT_EQ(val, 13);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &val));
}

TEST_F(FindAndConsumeTest_10, FindAndConsumeEmptyInput_10) {
  absl::string_view input("");
  std::string word;
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\w+)", &word));
}

TEST_F(FindAndConsumeTest_10, FindAndConsumeNoMatch_10) {
  absl::string_view input("hello world");
  int val;
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &val));
}

TEST_F(FindAndConsumeTest_10, FindAndConsumeMultipleCaptures_10) {
  absl::string_view input("key=value foo=bar");
  std::string key, value;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\w+)=(\\w+)", &key, &value));
  EXPECT_EQ(key, "key");
  EXPECT_EQ(value, "value");
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\w+)=(\\w+)", &key, &value));
  EXPECT_EQ(key, "foo");
  EXPECT_EQ(value, "bar");
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\w+)=(\\w+)", &key, &value));
}

TEST_F(FindAndConsumeTest_10, FindAndConsumeAdvancesInput_10) {
  absl::string_view input("---abc---def---");
  std::string word;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "([a-z]+)", &word));
  EXPECT_EQ(word, "abc");
  EXPECT_TRUE(RE2::FindAndConsume(&input, "([a-z]+)", &word));
  EXPECT_EQ(word, "def");
  EXPECT_FALSE(RE2::FindAndConsume(&input, "([a-z]+)", &word));
}

TEST_F(FindAndConsumeTest_10, FindAndConsumeWithInvalidRegex_10) {
  absl::string_view input("hello");
  RE2 re("[invalid");
  EXPECT_FALSE(re.ok());
  std::string word;
  EXPECT_FALSE(RE2::FindAndConsume(&input, re, &word));
}

// ============================================================
// FullMatch tests
// ============================================================

class FullMatchTest_10 : public ::testing::Test {};

TEST_F(FullMatchTest_10, BasicFullMatch_10) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
  EXPECT_TRUE(RE2::FullMatch("hello", "h.*o"));
  EXPECT_FALSE(RE2::FullMatch("hello", "hell"));
}

TEST_F(FullMatchTest_10, FullMatchWithCapture_10) {
  std::string s;
  EXPECT_TRUE(RE2::FullMatch("ruby:1234", "(\\w+):(\\d+)", &s));
  // With only one capture arg, only first group captured
  int n;
  EXPECT_TRUE(RE2::FullMatch("ruby:1234", "(\\w+):(\\d+)", &s, &n));
  EXPECT_EQ(s, "ruby");
  EXPECT_EQ(n, 1234);
}

TEST_F(FullMatchTest_10, FullMatchEmptyPattern_10) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_FALSE(RE2::FullMatch("a", ""));
}

TEST_F(FullMatchTest_10, FullMatchNoMatch_10) {
  EXPECT_FALSE(RE2::FullMatch("abc", "def"));
}

// ============================================================
// PartialMatch tests
// ============================================================

class PartialMatchTest_10 : public ::testing::Test {};

TEST_F(PartialMatchTest_10, BasicPartialMatch_10) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "llo"));
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST_F(PartialMatchTest_10, PartialMatchWithCapture_10) {
  int n;
  EXPECT_TRUE(RE2::PartialMatch("x]234 is a number", "(\\d+)", &n));
  EXPECT_EQ(n, 234);
}

TEST_F(PartialMatchTest_10, PartialMatchEmptyString_10) {
  EXPECT_TRUE(RE2::PartialMatch("", ""));
  EXPECT_TRUE(RE2::PartialMatch("abc", ""));
}

// ============================================================
// Consume tests
// ============================================================

class ConsumeTest_10 : public ::testing::Test {};

TEST_F(ConsumeTest_10, BasicConsume_10) {
  absl::string_view input("abc123def");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ(word, "abc");
  int num;
  EXPECT_TRUE(RE2::Consume(&input, "(\\d+)", &num));
  EXPECT_EQ(num, 123);
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ(word, "def");
}

TEST_F(ConsumeTest_10, ConsumeFailsAtNonMatchingStart_10) {
  absl::string_view input("123abc");
  std::string word;
  // Pattern requires letters at beginning
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &word));
}

// ============================================================
// Replace tests
// ============================================================

class ReplaceTest_10 : public ::testing::Test {};

TEST_F(ReplaceTest_10, BasicReplace_10) {
  std::string s = "yabba dabba doo";
  EXPECT_TRUE(RE2::Replace(&s, "b+", "d"));
  EXPECT_EQ(s, "yada dabba doo");
}

TEST_F(ReplaceTest_10, ReplaceNoMatch_10) {
  std::string s = "hello";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ(s, "hello");
}

TEST_F(ReplaceTest_10, ReplaceWithBackreference_10) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "[\\1]"));
  EXPECT_EQ(s, "[hello] world");
}

// ============================================================
// GlobalReplace tests
// ============================================================

class GlobalReplaceTest_10 : public ::testing::Test {};

TEST_F(GlobalReplaceTest_10, BasicGlobalReplace_10) {
  std::string s = "yabba dabba doo";
  int count = RE2::GlobalReplace(&s, "b+", "d");
  EXPECT_EQ(s, "yada dada doo");
  EXPECT_EQ(count, 2);
}

TEST_F(GlobalReplaceTest_10, GlobalReplaceNoMatch_10) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello");
}

// ============================================================
// Extract tests
// ============================================================

class ExtractTest_10 : public ::testing::Test {};

TEST_F(ExtractTest_10, BasicExtract_10) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST_F(ExtractTest_10, ExtractNoMatch_10) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("hello", "(\\d+)", "\\1", &out));
}

// ============================================================
// QuoteMeta tests
// ============================================================

class QuoteMetaTest_10 : public ::testing::Test {};

TEST_F(QuoteMetaTest_10, BasicQuoteMeta_10) {
  std::string quoted = RE2::QuoteMeta("1.5-2.0?");
  EXPECT_TRUE(RE2::FullMatch("1.5-2.0?", quoted));
}

TEST_F(QuoteMetaTest_10, QuoteMetaSpecialChars_10) {
  std::string quoted = RE2::QuoteMeta("a]b[c");
  EXPECT_TRUE(RE2::FullMatch("a]b[c", quoted));
}

TEST_F(QuoteMetaTest_10, QuoteMetaEmpty_10) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

// ============================================================
// Constructor / ok / pattern / error tests
// ============================================================

class RE2ConstructorTest_10 : public ::testing::Test {};

TEST_F(RE2ConstructorTest_10, ValidPattern_10) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "hello");
}

TEST_F(RE2ConstructorTest_10, InvalidPattern_10) {
  RE2 re("[invalid");
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(re.error().empty());
}

TEST_F(RE2ConstructorTest_10, ConstructFromString_10) {
  std::string pat = "(\\d+)";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "(\\d+)");
}

TEST_F(RE2ConstructorTest_10, ConstructFromStringView_10) {
  absl::string_view sv("(abc)");
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "(abc)");
}

// ============================================================
// NumberOfCapturingGroups tests
// ============================================================

class CapturingGroupsTest_10 : public ::testing::Test {};

TEST_F(CapturingGroupsTest_10, NoGroups_10) {
  RE2 re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(CapturingGroupsTest_10, OneGroup_10) {
  RE2 re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST_F(CapturingGroupsTest_10, MultipleGroups_10) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(CapturingGroupsTest_10, NestedGroups_10) {
  RE2 re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

// ============================================================
// NamedCapturingGroups tests
// ============================================================

class NamedCapturingGroupsTest_10 : public ::testing::Test {};

TEST_F(NamedCapturingGroupsTest_10, NoNamedGroups_10) {
  RE2 re("(\\d+)");
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST_F(NamedCapturingGroupsTest_10, WithNamedGroups_10) {
  RE2 re("(?P<name>\\w+)=(?P<value>\\d+)");
  EXPECT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 2);
  EXPECT_EQ(groups.at("name"), 1);
  EXPECT_EQ(groups.at("value"), 2);
}

// ============================================================
// CapturingGroupNames tests
// ============================================================

class CapturingGroupNamesTest_10 : public ::testing::Test {};

TEST_F(CapturingGroupNamesTest_10, WithNamedGroups_10) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 2);
  EXPECT_EQ(names.at(1), "first");
  EXPECT_EQ(names.at(2), "second");
}

// ============================================================
// Match tests
// ============================================================

class MatchTest_10 : public ::testing::Test {};

TEST_F(MatchTest_10, BasicMatch_10) {
  RE2 re("(\\w+):(\\d+)");
  absl::string_view submatch[3];
  EXPECT_TRUE(re.Match("foo:1234bar", 0, 11, RE2::UNANCHORED, submatch, 3));
  EXPECT_EQ(submatch[0], "foo:1234");
  EXPECT_EQ(submatch[1], "foo");
  EXPECT_EQ(submatch[2], "1234");
}

TEST_F(MatchTest_10, MatchAnchored_10) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("abc123", 0, 6, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::ANCHOR_START, nullptr, 0));
}

TEST_F(MatchTest_10, MatchBothAnchored_10) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("123abc", 0, 6, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST_F(MatchTest_10, MatchSubrange_10) {
  RE2 re("\\d+");
  absl::string_view text = "abc123def";
  absl::string_view submatch[1];
  EXPECT_TRUE(re.Match(text, 3, 6, RE2::ANCHOR_BOTH, submatch, 1));
  EXPECT_EQ(submatch[0], "123");
}

// ============================================================
// ProgramSize / ReverseProgramSize tests
// ============================================================

class ProgramSizeTest_10 : public ::testing::Test {};

TEST_F(ProgramSizeTest_10, ProgramSizePositive_10) {
  RE2 re("hello");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST_F(ProgramSizeTest_10, ReverseProgramSizePositive_10) {
  RE2 re("hello");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

TEST_F(ProgramSizeTest_10, ComplexPatternLargerProgram_10) {
  RE2 simple("a");
  RE2 complex("(a|b|c|d)(e|f|g)(h|i)");
  EXPECT_GT(complex.ProgramSize(), simple.ProgramSize());
}

// ============================================================
// PossibleMatchRange tests
// ============================================================

class PossibleMatchRangeTest_10 : public ::testing::Test {};

TEST_F(PossibleMatchRangeTest_10, BasicRange_10) {
  RE2 re("hello");
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "hello");
  EXPECT_GE(max, "hello");
}

// ============================================================
// CheckRewriteString tests
// ============================================================

class CheckRewriteStringTest_10 : public ::testing::Test {};

TEST_F(CheckRewriteStringTest_10, ValidRewrite_10) {
  RE2 re("(\\w+):(\\d+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1-\\2", &error));
}

TEST_F(CheckRewriteStringTest_10, InvalidRewriteTooManyGroups_10) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\1-\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ============================================================
// MaxSubmatch tests
// ============================================================

class MaxSubmatchTest_10 : public ::testing::Test {};

TEST_F(MaxSubmatchTest_10, BasicMaxSubmatch_10) {
  EXPECT_EQ(RE2::MaxSubmatch("\\0"), 0);
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
  EXPECT_EQ(RE2::MaxSubmatch("\\1 \\2 \\3"), 3);
}

TEST_F(MaxSubmatchTest_10, NoSubmatch_10) {
  EXPECT_EQ(RE2::MaxSubmatch("no backrefs"), 0);
}

// ============================================================
// Options tests
// ============================================================

class RE2OptionsTest_10 : public ::testing::Test {};

TEST_F(RE2OptionsTest_10, CaseSensitiveByDefault_10) {
  RE2 re("hello");
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
}

TEST_F(RE2OptionsTest_10, CaseInsensitiveOption_10) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HeLLo", re));
}

// ============================================================
// Hex / Octal / CRadix tests
// ============================================================

class RadixTest_10 : public ::testing::Test {};

TEST_F(RadixTest_10, HexParse_10) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("100", "(.*)", RE2::Hex(&v)));
  EXPECT_EQ(v, 256);
}

TEST_F(RadixTest_10, OctalParse_10) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("100", "(.*)", RE2::Octal(&v)));
  EXPECT_EQ(v, 64);
}

TEST_F(RadixTest_10, CRadixHex_10) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("0x100", "(.*)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 256);
}

TEST_F(RadixTest_10, CRadixOctal_10) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("0100", "(.*)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 64);
}

TEST_F(RadixTest_10, CRadixDecimal_10) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("100", "(.*)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 100);
}

// ============================================================
// ProgramFanout tests
// ============================================================

class ProgramFanoutTest_10 : public ::testing::Test {};

TEST_F(ProgramFanoutTest_10, BasicFanout_10) {
  RE2 re("(a|b|c)");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST_F(ProgramFanoutTest_10, ReverseFanout_10) {
  RE2 re("(a|b|c)");
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ============================================================
// Rewrite tests
// ============================================================

class RewriteTest_10 : public ::testing::Test {};

TEST_F(RewriteTest_10, BasicRewrite_10) {
  RE2 re("(\\w+):(\\d+)");
  absl::string_view text = "foo:1234";
  absl::string_view submatch[3];
  ASSERT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, submatch, 3));
  std::string out;
  EXPECT_TRUE(re.Rewrite(&out, "\\2-\\1", submatch, 3));
  EXPECT_EQ(out, "1234-foo");
}

// ============================================================
// Error code tests
// ============================================================

class ErrorCodeTest_10 : public ::testing::Test {};

TEST_F(ErrorCodeTest_10, NoError_10) {
  RE2 re("hello");
  EXPECT_EQ(re.error_code(), RE2::NoError);
  EXPECT_TRUE(re.error().empty());
}

TEST_F(ErrorCodeTest_10, ErrorOnBadPattern_10) {
  RE2 re("[");
  EXPECT_NE(re.error_code(), RE2::NoError);
  EXPECT_FALSE(re.error().empty());
}

// ============================================================
// FindAndConsume edge cases
// ============================================================

class FindAndConsumeEdgeTest_10 : public ::testing::Test {};

TEST_F(FindAndConsumeEdgeTest_10, FindAndConsumeMatchingEmpty_10) {
  // A pattern that can match empty string — FindAndConsume should still advance
  absl::string_view input("abc");
  // With empty regex and no capture, it should match at position 0
  EXPECT_TRUE(RE2::FindAndConsume(&input, ""));
}

TEST_F(FindAndConsumeEdgeTest_10, FindAndConsumeStringViewCapture_10) {
  absl::string_view input("hello=world foo=bar");
  absl::string_view key, value;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\w+)=(\\w+)", &key, &value));
  EXPECT_EQ(key, "hello");
  EXPECT_EQ(value, "world");
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\w+)=(\\w+)", &key, &value));
  EXPECT_EQ(key, "foo");
  EXPECT_EQ(value, "bar");
}

TEST_F(FindAndConsumeEdgeTest_10, FindAndConsumeFloatingPoint_10) {
  absl::string_view input("pi is 3.14159 and e is 2.71828");
  double val;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "([0-9]+\\.[0-9]+)", &val));
  EXPECT_NEAR(val, 3.14159, 0.00001);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "([0-9]+\\.[0-9]+)", &val));
  EXPECT_NEAR(val, 2.71828, 0.00001);
}
