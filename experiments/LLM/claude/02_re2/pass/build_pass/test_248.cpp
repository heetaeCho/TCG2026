#include "re2/re2.h"

#include <string>
#include <vector>
#include <map>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

namespace re2 {

// ============================================================
// ProgramFanout tests
// ============================================================

TEST(RE2ProgramFanoutTest_248, ValidPatternReturnsFanout_248) {
  RE2 re("(a|b)c");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
  EXPECT_FALSE(histogram.empty());
}

TEST(RE2ProgramFanoutTest_248, SimplePatternFanout_248) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ProgramFanoutTest_248, InvalidPatternReturnsNegative_248) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("(abc", opts);
  EXPECT_FALSE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_EQ(result, -1);
}

TEST(RE2ProgramFanoutTest_248, EmptyPattern_248) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ProgramFanoutTest_248, ComplexPattern_248) {
  RE2 re("[a-z]+[0-9]*\\.?");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ProgramFanoutTest_248, AlternationPattern_248) {
  RE2 re("(foo|bar|baz|qux)");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ============================================================
// ReverseProgramFanout tests
// ============================================================

TEST(RE2ReverseProgramFanoutTest_248, ValidPattern_248) {
  RE2 re("(a|b)c");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ReverseProgramFanoutTest_248, InvalidPattern_248) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("(abc", opts);
  EXPECT_FALSE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_EQ(result, -1);
}

// ============================================================
// ProgramSize / ReverseProgramSize tests
// ============================================================

TEST(RE2ProgramSizeTest_248, ValidPattern_248) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_248, InvalidPattern_248) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("(abc", opts);
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.ProgramSize(), -1);
}

TEST(RE2ReverseProgramSizeTest_248, ValidPattern_248) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ============================================================
// Construction / ok() tests
// ============================================================

TEST(RE2ConstructorTest_248, FromCString_248) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "hello");
}

TEST(RE2ConstructorTest_248, FromStdString_248) {
  std::string pat = "world";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "world");
}

TEST(RE2ConstructorTest_248, FromStringView_248) {
  absl::string_view pat = "test";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "test");
}

TEST(RE2ConstructorTest_248, InvalidPattern_248) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("[invalid", opts);
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(re.error().empty());
}

// ============================================================
// FullMatch tests
// ============================================================

TEST(RE2FullMatchTest_248, SimpleMatch_248) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2FullMatchTest_248, NoMatch_248) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatchTest_248, WithCapture_248) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &n));
  EXPECT_EQ(n, 12345);
}

TEST(RE2FullMatchTest_248, StringCapture_248) {
  std::string s;
  EXPECT_TRUE(RE2::FullMatch("abc", "(\\w+)", &s));
  EXPECT_EQ(s, "abc");
}

// ============================================================
// PartialMatch tests
// ============================================================

TEST(RE2PartialMatchTest_248, SimpleMatch_248) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "hello"));
}

TEST(RE2PartialMatchTest_248, NoMatch_248) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2PartialMatchTest_248, WithCapture_248) {
  std::string s;
  EXPECT_TRUE(RE2::PartialMatch("foo123bar", "(\\d+)", &s));
  EXPECT_EQ(s, "123");
}

// ============================================================
// Consume tests
// ============================================================

TEST(RE2ConsumeTest_248, BasicConsume_248) {
  absl::string_view input("abc123def");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ(word, "abc");
  EXPECT_EQ(input, "123def");
}

TEST(RE2ConsumeTest_248, ConsumeNoMatch_248) {
  absl::string_view input("123abc");
  std::string word;
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &word));
}

// ============================================================
// FindAndConsume tests
// ============================================================

TEST(RE2FindAndConsumeTest_248, Basic_248) {
  absl::string_view input("abc123def456");
  std::string digits;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &digits));
  EXPECT_EQ(digits, "123");
}

// ============================================================
// Replace tests
// ============================================================

TEST(RE2ReplaceTest_248, BasicReplace_248) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "world", "there"));
  EXPECT_EQ(s, "hello there");
}

TEST(RE2ReplaceTest_248, NoMatch_248) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "there"));
  EXPECT_EQ(s, "hello world");
}

TEST(RE2ReplaceTest_248, WithBackreference_248) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "<<\\1>>"));
  EXPECT_EQ(s, "<<hello>> world");
}

// ============================================================
// GlobalReplace tests
// ============================================================

TEST(RE2GlobalReplaceTest_248, ReplaceAll_248) {
  std::string s = "aaa bbb aaa";
  int count = RE2::GlobalReplace(&s, "aaa", "ccc");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(s, "ccc bbb ccc");
}

TEST(RE2GlobalReplaceTest_248, NoMatch_248) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello");
}

// ============================================================
// Extract tests
// ============================================================

TEST(RE2ExtractTest_248, BasicExtract_248) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST(RE2ExtractTest_248, NoMatch_248) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-at-sign", "(.*)@(.*)", "\\1", &out));
}

// ============================================================
// QuoteMeta tests
// ============================================================

TEST(RE2QuoteMetaTest_248, NoSpecialChars_248) {
  EXPECT_EQ(RE2::QuoteMeta("hello"), "hello");
}

TEST(RE2QuoteMetaTest_248, SpecialChars_248) {
  std::string quoted = RE2::QuoteMeta("a.b+c*d");
  RE2 re(quoted);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a.b+c*d", re));
  EXPECT_FALSE(RE2::FullMatch("aXb+c*d", re));
}

TEST(RE2QuoteMetaTest_248, EmptyString_248) {
  EXPECT_EQ(RE2::QuoteMeta(""), "");
}

// ============================================================
// Match tests
// ============================================================

TEST(RE2MatchTest_248, BasicMatch_248) {
  RE2 re("(\\w+):(\\d+)");
  ASSERT_TRUE(re.ok());
  absl::string_view submatch[3];
  EXPECT_TRUE(re.Match("foo:123", 0, 7, RE2::UNANCHORED, submatch, 3));
  EXPECT_EQ(submatch[0], "foo:123");
  EXPECT_EQ(submatch[1], "foo");
  EXPECT_EQ(submatch[2], "123");
}

TEST(RE2MatchTest_248, NoMatch_248) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(re.Match("abcdef", 0, 6, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_248, AnchorStart_248) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_FALSE(re.Match("abc123", 0, 6, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_248, PartialRange_248) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  // Match in substring
  EXPECT_TRUE(re.Match("xxxabcxxx", 3, 6, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_FALSE(re.Match("xxxabcxxx", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

// ============================================================
// NumberOfCapturingGroups tests
// ============================================================

TEST(RE2NumberOfCapturingGroupsTest_248, NoGroups_248) {
  RE2 re("abc");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2NumberOfCapturingGroupsTest_248, TwoGroups_248) {
  RE2 re("(a)(b)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 2);
}

TEST(RE2NumberOfCapturingGroupsTest_248, NestedGroups_248) {
  RE2 re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

// ============================================================
// NamedCapturingGroups tests
// ============================================================

TEST(RE2NamedCapturingGroupsTest_248, NoNamedGroups_248) {
  RE2 re("(a)(b)");
  EXPECT_TRUE(re.NamedCapturingGroups().empty());
}

TEST(RE2NamedCapturingGroupsTest_248, WithNamedGroups_248) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  ASSERT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 2);
  auto it = groups.find("first");
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, 1);
  it = groups.find("second");
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, 2);
}

// ============================================================
// CapturingGroupNames tests
// ============================================================

TEST(RE2CapturingGroupNamesTest_248, WithNames_248) {
  RE2 re("(?P<name>\\w+):(?P<value>\\d+)");
  ASSERT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 2);
  auto it = names.find(1);
  ASSERT_NE(it, names.end());
  EXPECT_EQ(it->second, "name");
  it = names.find(2);
  ASSERT_NE(it, names.end());
  EXPECT_EQ(it->second, "value");
}

// ============================================================
// CheckRewriteString tests
// ============================================================

TEST(RE2CheckRewriteStringTest_248, ValidRewrite_248) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewriteStringTest_248, InvalidRewrite_248) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ============================================================
// MaxSubmatch tests
// ============================================================

TEST(RE2MaxSubmatchTest_248, NoSubmatch_248) {
  EXPECT_EQ(RE2::MaxSubmatch("no backrefs"), 0);
}

TEST(RE2MaxSubmatchTest_248, WithSubmatch_248) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1 and \\3"), 3);
}

// ============================================================
// PossibleMatchRange tests
// ============================================================

TEST(RE2PossibleMatchRangeTest_248, Basic_248) {
  RE2 re("abc.*");
  ASSERT_TRUE(re.ok());
  std::string min_s, max_s;
  EXPECT_TRUE(re.PossibleMatchRange(&min_s, &max_s, 10));
  EXPECT_LE(min_s, "abc");
  EXPECT_GE(max_s, "abc");
}

TEST(RE2PossibleMatchRangeTest_248, EmptyPattern_248) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  std::string min_s, max_s;
  EXPECT_TRUE(re.PossibleMatchRange(&min_s, &max_s, 10));
}

// ============================================================
// Error info tests
// ============================================================

TEST(RE2ErrorTest_248, ValidPatternNoError_248) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(re.error().empty());
}

TEST(RE2ErrorTest_248, InvalidPatternHasError_248) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("(abc", opts);
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(re.error().empty());
  EXPECT_NE(re.error_code(), RE2::NoError);
}

// ============================================================
// Rewrite tests
// ============================================================

TEST(RE2RewriteTest_248, BasicRewrite_248) {
  RE2 re("(\\w+):(\\d+)");
  ASSERT_TRUE(re.ok());
  absl::string_view vec[3] = {"foo:123", "foo", "123"};
  std::string out;
  EXPECT_TRUE(re.Rewrite(&out, "\\2-\\1", vec, 3));
  EXPECT_EQ(out, "123-foo");
}

}  // namespace re2
