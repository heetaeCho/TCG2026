#include "gtest/gtest.h"
#include "re2/re2.h"
#include <string>
#include <vector>
#include <map>

namespace {

// ============================================================
// Basic Construction Tests
// ============================================================

TEST(RE2Test_236, ConstructFromCString_236) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("hello", re.pattern());
}

TEST(RE2Test_236, ConstructFromStdString_236) {
  std::string pat = "world";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("world", re.pattern());
}

TEST(RE2Test_236, ConstructFromStringView_236) {
  absl::string_view sv = "foo.*bar";
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("foo.*bar", re.pattern());
}

TEST(RE2Test_236, ConstructWithOptions_236) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("Hello", opts);
  EXPECT_TRUE(re.ok());
}

TEST(RE2Test_236, InvalidPattern_236) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2Test_236, EmptyPattern_236) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("", re.pattern());
}

// ============================================================
// FullMatch Tests
// ============================================================

TEST(RE2FullMatchTest_236, SimpleMatch_236) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2FullMatchTest_236, SimpleNoMatch_236) {
  EXPECT_FALSE(RE2::FullMatch("hello", "world"));
}

TEST(RE2FullMatchTest_236, FullMatchRequiresEntireString_236) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatchTest_236, FullMatchWithCapture_236) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &n));
  EXPECT_EQ(12345, n);
}

TEST(RE2FullMatchTest_236, FullMatchWithStringCapture_236) {
  std::string s;
  EXPECT_TRUE(RE2::FullMatch("abc", "(\\w+)", &s));
  EXPECT_EQ("abc", s);
}

TEST(RE2FullMatchTest_236, FullMatchMultipleCaptures_236) {
  std::string a, b;
  EXPECT_TRUE(RE2::FullMatch("hello-world", "(\\w+)-(\\w+)", &a, &b));
  EXPECT_EQ("hello", a);
  EXPECT_EQ("world", b);
}

TEST(RE2FullMatchTest_236, FullMatchEmptyString_236) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_TRUE(RE2::FullMatch("", ".*"));
}

// ============================================================
// PartialMatch Tests
// ============================================================

TEST(RE2PartialMatchTest_236, SimplePartialMatch_236) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "llo"));
}

TEST(RE2PartialMatchTest_236, PartialMatchNoMatch_236) {
  EXPECT_FALSE(RE2::PartialMatch("hello", "xyz"));
}

TEST(RE2PartialMatchTest_236, PartialMatchWithCapture_236) {
  int n;
  EXPECT_TRUE(RE2::PartialMatch("foo123bar", "(\\d+)", &n));
  EXPECT_EQ(123, n);
}

TEST(RE2PartialMatchTest_236, PartialMatchEmptyPattern_236) {
  EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

// ============================================================
// Consume Tests
// ============================================================

TEST(RE2ConsumeTest_236, BasicConsume_236) {
  absl::string_view input("foo123bar456");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "(\\w+)", &word));
  // Consume should have advanced input
}

TEST(RE2ConsumeTest_236, ConsumeNoMatch_236) {
  absl::string_view input("hello");
  int n;
  EXPECT_FALSE(RE2::Consume(&input, "(\\d+)", &n));
}

TEST(RE2ConsumeTest_236, ConsumeMultipleTimes_236) {
  absl::string_view input("aab");
  std::string s;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z])", &s));
  EXPECT_EQ("a", s);
  EXPECT_TRUE(RE2::Consume(&input, "([a-z])", &s));
  EXPECT_EQ("a", s);
  EXPECT_TRUE(RE2::Consume(&input, "([a-z])", &s));
  EXPECT_EQ("b", s);
}

// ============================================================
// FindAndConsume Tests
// ============================================================

TEST(RE2FindAndConsumeTest_236, BasicFindAndConsume_236) {
  absl::string_view input("foo123bar456");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(123, n);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(456, n);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

TEST(RE2FindAndConsumeTest_236, FindAndConsumeNoMatch_236) {
  absl::string_view input("abcdef");
  int n;
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

// ============================================================
// Replace Tests
// ============================================================

TEST(RE2ReplaceTest_236, BasicReplace_236) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "world", "there"));
  EXPECT_EQ("hello there", s);
}

TEST(RE2ReplaceTest_236, ReplaceNoMatch_236) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "there"));
  EXPECT_EQ("hello world", s);
}

TEST(RE2ReplaceTest_236, ReplaceWithCapture_236) {
  std::string s = "foo bar";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "<<\\1>>"));
  EXPECT_EQ("<<foo>> bar", s);
}

TEST(RE2ReplaceTest_236, ReplaceFirstOccurrenceOnly_236) {
  std::string s = "aaa";
  EXPECT_TRUE(RE2::Replace(&s, "a", "b"));
  EXPECT_EQ("baa", s);
}

// ============================================================
// GlobalReplace Tests
// ============================================================

TEST(RE2GlobalReplaceTest_236, BasicGlobalReplace_236) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, "a", "b");
  EXPECT_EQ("bbb", s);
  EXPECT_EQ(3, count);
}

TEST(RE2GlobalReplaceTest_236, GlobalReplaceNoMatch_236) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ("hello", s);
  EXPECT_EQ(0, count);
}

TEST(RE2GlobalReplaceTest_236, GlobalReplaceWithCapture_236) {
  std::string s = "foo bar baz";
  int count = RE2::GlobalReplace(&s, "(\\w+)", "[\\1]");
  EXPECT_EQ("[foo] [bar] [baz]", s);
  EXPECT_EQ(3, count);
}

TEST(RE2GlobalReplaceTest_236, GlobalReplaceEmptyMatch_236) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "", "_");
  // Empty pattern matches at every position
  EXPECT_GT(count, 0);
}

// ============================================================
// Extract Tests
// ============================================================

TEST(RE2ExtractTest_236, BasicExtract_236) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ("kremlin!boris", out);
}

TEST(RE2ExtractTest_236, ExtractNoMatch_236) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-at-sign", "(.*)@(.*)", "\\1", &out));
}

// ============================================================
// QuoteMeta Tests
// ============================================================

TEST(RE2QuoteMetaTest_236, BasicQuoteMeta_236) {
  std::string quoted = RE2::QuoteMeta("hello.world");
  EXPECT_TRUE(RE2::FullMatch("hello.world", quoted));
  EXPECT_FALSE(RE2::FullMatch("helloxworld", quoted));
}

TEST(RE2QuoteMetaTest_236, QuoteMetaSpecialChars_236) {
  std::string quoted = RE2::QuoteMeta("a+b*c?");
  RE2 re(quoted);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a+b*c?", re));
  EXPECT_FALSE(RE2::FullMatch("aabbbbc", re));
}

TEST(RE2QuoteMetaTest_236, QuoteMetaEmptyString_236) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ("", quoted);
}

TEST(RE2QuoteMetaTest_236, QuoteMetaParensAndBrackets_236) {
  std::string quoted = RE2::QuoteMeta("[a](b){c}");
  EXPECT_TRUE(RE2::FullMatch("[a](b){c}", quoted));
}

// ============================================================
// Match Tests
// ============================================================

TEST(RE2MatchTest_236, BasicMatch_236) {
  RE2 re("(\\w+):(\\d+)");
  ASSERT_TRUE(re.ok());
  absl::string_view submatch[3];
  EXPECT_TRUE(re.Match("foo:1234", 0, 8, RE2::UNANCHORED, submatch, 3));
  EXPECT_EQ("foo:1234", submatch[0]);
  EXPECT_EQ("foo", submatch[1]);
  EXPECT_EQ("1234", submatch[2]);
}

TEST(RE2MatchTest_236, MatchAnchored_236) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(re.Match("hello world", 0, 11, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_FALSE(re.Match("say hello", 0, 9, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_236, MatchAnchorBoth_236) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(re.Match("hello", 0, 5, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_FALSE(re.Match("hello world", 0, 11, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_236, MatchWithStartPos_236) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  absl::string_view submatch[1];
  EXPECT_TRUE(re.Match("abc123", 3, 6, RE2::UNANCHORED, submatch, 1));
  EXPECT_EQ("123", submatch[0]);
}

TEST(RE2MatchTest_236, MatchNoSubmatch_236) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(re.Match("abc123", 0, 6, RE2::UNANCHORED, nullptr, 0));
}

TEST(RE2MatchTest_236, MatchEndpos_236) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  // Only look at "abc1" (endpos=4), should find "1"
  absl::string_view submatch[1];
  EXPECT_TRUE(re.Match("abc123", 0, 4, RE2::UNANCHORED, submatch, 1));
  EXPECT_EQ("1", submatch[0]);
}

// ============================================================
// NumberOfCapturingGroups Tests
// ============================================================

TEST(RE2CapturingGroupsTest_236, NoCapturingGroups_236) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_236, OneCapturingGroup_236) {
  RE2 re("(hello)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_236, MultipleCapturingGroups_236) {
  RE2 re("(\\w+):(\\d+):(\\w+)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_236, NonCapturingGroup_236) {
  RE2 re("(?:hello)(world)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

// ============================================================
// NamedCapturingGroups Tests
// ============================================================

TEST(RE2NamedCapturingGroupsTest_236, NoNamedGroups_236) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2NamedCapturingGroupsTest_236, WithNamedGroups_236) {
  RE2 re("(?P<name>\\w+):(?P<value>\\d+)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_EQ(2u, groups.size());
  EXPECT_EQ(1, groups.at("name"));
  EXPECT_EQ(2, groups.at("value"));
}

// ============================================================
// CapturingGroupNames Tests
// ============================================================

TEST(RE2CapturingGroupNamesTest_236, WithNamedGroups_236) {
  RE2 re("(?P<first>\\w+)-(?P<second>\\d+)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_EQ(2u, names.size());
  EXPECT_EQ("first", names.at(1));
  EXPECT_EQ("second", names.at(2));
}

// ============================================================
// ProgramSize Tests
// ============================================================

TEST(RE2ProgramSizeTest_236, ValidProgramSize_236) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_236, ReverseProgramSize_236) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ============================================================
// ProgramFanout Tests
// ============================================================

TEST(RE2ProgramFanoutTest_236, ProgramFanoutVector_236) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ProgramFanoutTest_236, ReverseProgramFanoutVector_236) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ============================================================
// PossibleMatchRange Tests
// ============================================================

TEST(RE2PossibleMatchRangeTest_236, BasicRange_236) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "hello");
  EXPECT_GE(max, "hello");
}

TEST(RE2PossibleMatchRangeTest_236, WildcardRange_236) {
  RE2 re("h.*o");
  ASSERT_TRUE(re.ok());
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  // min should start with 'h'
  EXPECT_FALSE(min.empty());
}

// ============================================================
// CheckRewriteString Tests
// ============================================================

TEST(RE2CheckRewriteTest_236, ValidRewrite_236) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewriteTest_236, InvalidRewriteTooManyGroups_236) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  std::string error;
  // \\2 references a group that doesn't exist
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

TEST(RE2CheckRewriteTest_236, RewriteWithNoCaptures_236) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("world", &error));
}

// ============================================================
// MaxSubmatch Tests
// ============================================================

TEST(RE2MaxSubmatchTest_236, NoBackreference_236) {
  EXPECT_EQ(0, RE2::MaxSubmatch("no backrefs"));
}

TEST(RE2MaxSubmatchTest_236, SingleBackreference_236) {
  EXPECT_EQ(1, RE2::MaxSubmatch("\\1"));
}

TEST(RE2MaxSubmatchTest_236, MultipleBackreferences_236) {
  EXPECT_EQ(3, RE2::MaxSubmatch("\\1 \\2 \\3"));
}

TEST(RE2MaxSubmatchTest_236, HigherBackreference_236) {
  EXPECT_EQ(9, RE2::MaxSubmatch("\\9"));
}

// ============================================================
// Rewrite Tests
// ============================================================

TEST(RE2RewriteTest_236, BasicRewrite_236) {
  RE2 re("(\\w+):(\\d+)");
  ASSERT_TRUE(re.ok());
  std::string out;
  absl::string_view vec[3] = {"foo:123", "foo", "123"};
  EXPECT_TRUE(re.Rewrite(&out, "\\2-\\1", vec, 3));
  EXPECT_EQ("123-foo", out);
}

TEST(RE2RewriteTest_236, RewriteWithLiteralText_236) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  std::string out;
  absl::string_view vec[2] = {"hello", "hello"};
  EXPECT_TRUE(re.Rewrite(&out, "<<\\1>>", vec, 2));
  EXPECT_EQ("<<hello>>", out);
}

// ============================================================
// CRadix, Hex, Octal Tests
// ============================================================

TEST(RE2ArgTest_236, HexParsing_236) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(0x[0-9a-f]+)", RE2::Hex(&n)));
  EXPECT_EQ(0x1f, n);
}

TEST(RE2ArgTest_236, OctalParsing_236) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("077", "(0[0-7]+)", RE2::Octal(&n)));
  EXPECT_EQ(077, n);
}

TEST(RE2ArgTest_236, CRadixHex_236) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(0x[0-9a-f]+)", RE2::CRadix(&n)));
  EXPECT_EQ(0x1f, n);
}

TEST(RE2ArgTest_236, CRadixOctal_236) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("077", "(0[0-7]*)", RE2::CRadix(&n)));
  EXPECT_EQ(077, n);
}

TEST(RE2ArgTest_236, CRadixDecimal_236) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("123", "(\\d+)", RE2::CRadix(&n)));
  EXPECT_EQ(123, n);
}

// ============================================================
// Options Tests
// ============================================================

TEST(RE2OptionsTest_236, CaseInsensitive_236) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2OptionsTest_236, Literal_236) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

TEST(RE2OptionsTest_236, OptionsAccessor_236) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("test", opts);
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(re.options().case_sensitive());
}

// ============================================================
// Error Cases
// ============================================================

TEST(RE2ErrorTest_236, BadPatternErrorCode_236) {
  RE2 re("[invalid");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
}

TEST(RE2ErrorTest_236, ErrorString_236) {
  RE2 re("(");
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(re.error().empty());
}

// ============================================================
// FUZZING_ONLY_set_maximum_global_replace_count Tests
// ============================================================

TEST(RE2FuzzingTest_236, LimitGlobalReplace_236) {
  // Set a limit
  RE2::FUZZING_ONLY_set_maximum_global_replace_count(2);
  std::string s = "aaaa";
  int count = RE2::GlobalReplace(&s, "a", "b");
  // With limit of 2, should only replace at most 2
  EXPECT_LE(count, 2);
  // Reset to unlimited
  RE2::FUZZING_ONLY_set_maximum_global_replace_count(-1);
}

TEST(RE2FuzzingTest_236, UnlimitedGlobalReplace_236) {
  RE2::FUZZING_ONLY_set_maximum_global_replace_count(-1);
  std::string s = "aaaa";
  int count = RE2::GlobalReplace(&s, "a", "b");
  EXPECT_EQ(4, count);
  EXPECT_EQ("bbbb", s);
}

TEST(RE2FuzzingTest_236, ZeroLimitGlobalReplace_236) {
  RE2::FUZZING_ONLY_set_maximum_global_replace_count(0);
  std::string s = "aaaa";
  int count = RE2::GlobalReplace(&s, "a", "b");
  EXPECT_EQ(0, count);
  EXPECT_EQ("aaaa", s);
  // Reset
  RE2::FUZZING_ONLY_set_maximum_global_replace_count(-1);
}

// ============================================================
// FullMatchN / PartialMatchN Tests
// ============================================================

TEST(RE2FullMatchNTest_236, NullArgs_236) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatchN("hello", re, nullptr, 0));
}

TEST(RE2PartialMatchNTest_236, NullArgs_236) {
  RE2 re("ell");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatchN("hello", re, nullptr, 0));
}

// ============================================================
// ConsumeN / FindAndConsumeN Tests
// ============================================================

TEST(RE2ConsumeNTest_236, BasicConsumeN_236) {
  absl::string_view input("hello");
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  RE2::Arg arg;
  std::string s;
  RE2::Arg arg1(&s);
  const RE2::Arg* args[] = {&arg1};
  EXPECT_TRUE(RE2::ConsumeN(&input, re, args, 1));
  EXPECT_EQ("hello", s);
}

TEST(RE2FindAndConsumeNTest_236, BasicFindAndConsumeN_236) {
  absl::string_view input("abc123def");
  RE2 re("(\\d+)");
  ASSERT_TRUE(re.ok());
  std::string s;
  RE2::Arg arg1(&s);
  const RE2::Arg* args[] = {&arg1};
  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, args, 1));
  EXPECT_EQ("123", s);
}

// ============================================================
// Complex Pattern Tests
// ============================================================

TEST(RE2ComplexTest_236, AlternationMatch_236) {
  EXPECT_TRUE(RE2::FullMatch("cat", "cat|dog"));
  EXPECT_TRUE(RE2::FullMatch("dog", "cat|dog"));
  EXPECT_FALSE(RE2::FullMatch("bird", "cat|dog"));
}

TEST(RE2ComplexTest_236, QuantifierMatch_236) {
  EXPECT_TRUE(RE2::FullMatch("aaa", "a{3}"));
  EXPECT_FALSE(RE2::FullMatch("aa", "a{3}"));
  EXPECT_TRUE(RE2::FullMatch("aa", "a{2,4}"));
  EXPECT_TRUE(RE2::FullMatch("aaaa", "a{2,4}"));
  EXPECT_FALSE(RE2::FullMatch("a", "a{2,4}"));
}

TEST(RE2ComplexTest_236, CharacterClassMatch_236) {
  EXPECT_TRUE(RE2::FullMatch("a", "[a-z]"));
  EXPECT_TRUE(RE2::FullMatch("z", "[a-z]"));
  EXPECT_FALSE(RE2::FullMatch("A", "[a-z]"));
}

TEST(RE2ComplexTest_236, AnchorMatch_236) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "^hello"));
  EXPECT_TRUE(RE2::PartialMatch("hello world", "world$"));
  EXPECT_FALSE(RE2::PartialMatch("hello world", "^world"));
}

TEST(RE2ComplexTest_236, DotMatchesNewlineDefault_236) {
  // By default, dot does not match newline
  EXPECT_FALSE(RE2::FullMatch("a\nb", "a.b"));
}

TEST(RE2ComplexTest_236, DotMatchesNewlineOption_236) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

// ============================================================
// Type Capture Tests
// ============================================================

TEST(RE2TypeCaptureTest_236, CaptureFloat_236) {
  float f;
  EXPECT_TRUE(RE2::FullMatch("3.14", "([0-9.]+)", &f));
  EXPECT_NEAR(3.14f, f, 0.01f);
}

TEST(RE2TypeCaptureTest_236, CaptureStringView_236) {
  absl::string_view sv;
  EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", &sv));
  EXPECT_EQ("hello", sv);
}

TEST(RE2TypeCaptureTest_236, CaptureInt64_236) {
  int64_t val;
  EXPECT_TRUE(RE2::FullMatch("9876543210", "(\\d+)", &val));
  EXPECT_EQ(9876543210LL, val);
}

}  // namespace
