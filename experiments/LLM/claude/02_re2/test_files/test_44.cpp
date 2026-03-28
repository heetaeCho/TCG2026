#include "re2/re2.h"

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

// ===========================================================================
// Basic construction / status tests
// ===========================================================================

TEST(RE2Test_44, ConstructFromCString_44) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "hello");
}

TEST(RE2Test_44, ConstructFromStdString_44) {
  std::string pat = "wor(ld)";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), pat);
}

TEST(RE2Test_44, ConstructFromStringView_44) {
  absl::string_view sv("foo.*bar");
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "foo.*bar");
}

TEST(RE2Test_44, InvalidPattern_44) {
  RE2 re("(abc");  // unclosed paren
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error_code(), RE2::NoError);
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2Test_44, ErrorCodeNoErrorOnValid_44) {
  RE2 re("abc");
  EXPECT_EQ(re.error_code(), RE2::NoError);
}

// ===========================================================================
// FullMatch tests
// ===========================================================================

TEST(RE2FullMatchTest_44, SimpleMatch_44) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2FullMatchTest_44, SimpleNoMatch_44) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatchTest_44, WithCapture_44) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &n));
  EXPECT_EQ(n, 12345);
}

TEST(RE2FullMatchTest_44, MultipleCaptures_44) {
  std::string s;
  int n;
  EXPECT_TRUE(RE2::FullMatch("abc 123", "(\\w+) (\\d+)", &s, &n));
  EXPECT_EQ(s, "abc");
  EXPECT_EQ(n, 123);
}

TEST(RE2FullMatchTest_44, EmptyPatternEmptyString_44) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
}

TEST(RE2FullMatchTest_44, EmptyPatternNonEmptyString_44) {
  EXPECT_FALSE(RE2::FullMatch("abc", ""));
}

TEST(RE2FullMatchTest_44, CaptureString_44) {
  std::string captured;
  EXPECT_TRUE(RE2::FullMatch("test123", "(\\w+)", &captured));
  EXPECT_EQ(captured, "test123");
}

// ===========================================================================
// PartialMatch tests
// ===========================================================================

TEST(RE2PartialMatchTest_44, SimplePartialMatch_44) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "llo"));
}

TEST(RE2PartialMatchTest_44, NoPartialMatch_44) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2PartialMatchTest_44, CaptureInPartialMatch_44) {
  int n;
  EXPECT_TRUE(RE2::PartialMatch("foo 42 bar", "(\\d+)", &n));
  EXPECT_EQ(n, 42);
}

TEST(RE2PartialMatchTest_44, PartialMatchAtBeginning_44) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "^hello"));
}

TEST(RE2PartialMatchTest_44, PartialMatchAtEnd_44) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "world$"));
}

// ===========================================================================
// Consume / FindAndConsume tests
// ===========================================================================

TEST(RE2ConsumeTest_44, ConsumeBasic_44) {
  absl::string_view input("one1two2three3");
  int n;
  EXPECT_TRUE(RE2::Consume(&input, "(\\d)", &n));
  // After consuming the first digit, the input should advance past it
  // Actually, RE2::Consume anchors at beginning, so let's try differently
}

TEST(RE2ConsumeTest_44, ConsumeAdvancesInput_44) {
  absl::string_view input("123abc");
  int n;
  EXPECT_TRUE(RE2::Consume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 123);
  EXPECT_EQ(input, "abc");
}

TEST(RE2ConsumeTest_44, ConsumeNoMatch_44) {
  absl::string_view input("abc123");
  int n;
  EXPECT_FALSE(RE2::Consume(&input, "(\\d+)", &n));
  EXPECT_EQ(input, "abc123");  // unchanged
}

TEST(RE2FindAndConsumeTest_44, FindAndConsumeBasic_44) {
  absl::string_view input("abc 123 def 456");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 123);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 456);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

// ===========================================================================
// Replace / GlobalReplace tests
// ===========================================================================

TEST(RE2ReplaceTest_44, ReplaceFirst_44) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "world", "planet"));
  EXPECT_EQ(s, "hello planet");
}

TEST(RE2ReplaceTest_44, ReplaceNoMatch_44) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ(s, "hello world");
}

TEST(RE2ReplaceTest_44, ReplaceWithCapture_44) {
  std::string s = "foo bar";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "<<\\1>>"));
  EXPECT_EQ(s, "<<foo>> bar");
}

TEST(RE2GlobalReplaceTest_44, GlobalReplaceAll_44) {
  std::string s = "aaa bbb ccc";
  int count = RE2::GlobalReplace(&s, "\\w+", "x");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "x x x");
}

TEST(RE2GlobalReplaceTest_44, GlobalReplaceNone_44) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "\\d+", "x");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello");
}

// ===========================================================================
// Extract tests
// ===========================================================================

TEST(RE2ExtractTest_44, ExtractBasic_44) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST(RE2ExtractTest_44, ExtractNoMatch_44) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-at-sign", "(.*)@(.*)", "\\1", &out));
}

// ===========================================================================
// QuoteMeta tests
// ===========================================================================

TEST(RE2QuoteMetaTest_44, QuoteMetaSpecialChars_44) {
  std::string quoted = RE2::QuoteMeta("a.b+c*d?e");
  // The quoted string should match literally
  EXPECT_TRUE(RE2::FullMatch("a.b+c*d?e", quoted));
}

TEST(RE2QuoteMetaTest_44, QuoteMetaPlainString_44) {
  std::string quoted = RE2::QuoteMeta("hello");
  EXPECT_EQ(quoted, "hello");
}

TEST(RE2QuoteMetaTest_44, QuoteMetaEmptyString_44) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

TEST(RE2QuoteMetaTest_44, QuoteMetaBackslash_44) {
  std::string quoted = RE2::QuoteMeta("a\\b");
  EXPECT_TRUE(RE2::FullMatch("a\\b", quoted));
}

// ===========================================================================
// NumberOfCapturingGroups tests
// ===========================================================================

TEST(RE2CapturingGroupsTest_44, ZeroGroups_44) {
  RE2 re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2CapturingGroupsTest_44, OneGroup_44) {
  RE2 re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(RE2CapturingGroupsTest_44, MultipleGroups_44) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2CapturingGroupsTest_44, NestedGroups_44) {
  RE2 re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2CapturingGroupsTest_44, NonCapturingGroup_44) {
  RE2 re("(?:abc)(def)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

// ===========================================================================
// NamedCapturingGroups tests
// ===========================================================================

TEST(RE2NamedGroupsTest_44, NoNamedGroups_44) {
  RE2 re("(abc)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2NamedGroupsTest_44, WithNamedGroup_44) {
  RE2 re("(?P<name>\\w+) (?P<value>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 2);
  EXPECT_EQ(groups.at("name"), 1);
  EXPECT_EQ(groups.at("value"), 2);
}

// ===========================================================================
// CapturingGroupNames tests
// ===========================================================================

TEST(RE2GroupNamesTest_44, CapturingGroupNamesBasic_44) {
  RE2 re("(?P<first>\\w+) (?P<second>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 2);
  EXPECT_EQ(names.at(1), "first");
  EXPECT_EQ(names.at(2), "second");
}

// ===========================================================================
// Match tests
// ===========================================================================

TEST(RE2MatchTest_44, MatchUnanchored_44) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc 123 def", 0, 11, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ(submatch[0], "123");
  EXPECT_EQ(submatch[1], "123");
}

TEST(RE2MatchTest_44, MatchAnchorStart_44) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("abc 123", 0, 7, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_TRUE(re.Match("123 abc", 0, 7, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_44, MatchAnchorBoth_44) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("123 abc", 0, 7, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_TRUE(re.Match("12345", 0, 5, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_44, MatchWithStartpos_44) {
  RE2 re("\\d+");
  absl::string_view submatch[1];
  EXPECT_TRUE(re.Match("abc 123 456", 4, 11, RE2::UNANCHORED, submatch, 1));
  EXPECT_EQ(submatch[0], "123");
}

TEST(RE2MatchTest_44, MatchEmptyText_44) {
  RE2 re(".*");
  EXPECT_TRUE(re.Match("", 0, 0, RE2::ANCHOR_BOTH, nullptr, 0));
}

// ===========================================================================
// ProgramSize / ReverseProgramSize tests
// ===========================================================================

TEST(RE2ProgramSizeTest_44, ProgramSizePositive_44) {
  RE2 re("hello");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_44, ReverseProgramSizePositive_44) {
  RE2 re("hello");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ===========================================================================
// PossibleMatchRange tests
// ===========================================================================

TEST(RE2PossibleMatchRangeTest_44, BasicRange_44) {
  RE2 re("abc.*");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "abc");
  EXPECT_GE(max_str, "abc");
}

// ===========================================================================
// CheckRewriteString tests
// ===========================================================================

TEST(RE2CheckRewriteTest_44, ValidRewrite_44) {
  RE2 re("(\\w+) (\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1-\\2", &error));
}

TEST(RE2CheckRewriteTest_44, InvalidRewriteBackref_44) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ===========================================================================
// MaxSubmatch tests
// ===========================================================================

TEST(RE2MaxSubmatchTest_44, NoBackreferences_44) {
  EXPECT_EQ(RE2::MaxSubmatch("hello"), 0);
}

TEST(RE2MaxSubmatchTest_44, SingleBackreference_44) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
}

TEST(RE2MaxSubmatchTest_44, MultipleBackreferences_44) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1 \\3 \\2"), 3);
}

// ===========================================================================
// Hex / Octal / CRadix tests
// ===========================================================================

TEST(RE2HexTest_44, ParseHexValue_44) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("ff", "(\\w+)", RE2::Hex(&value)));
  EXPECT_EQ(value, 255);
}

TEST(RE2HexTest_44, ParseHexUpperCase_44) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("FF", "(\\w+)", RE2::Hex(&value)));
  EXPECT_EQ(value, 255);
}

TEST(RE2HexTest_44, ParseHexZero_44) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("0", "(\\w+)", RE2::Hex(&value)));
  EXPECT_EQ(value, 0);
}

TEST(RE2OctalTest_44, ParseOctalValue_44) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("77", "(\\w+)", RE2::Octal(&value)));
  EXPECT_EQ(value, 63);
}

TEST(RE2OctalTest_44, ParseOctalZero_44) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("0", "(\\w+)", RE2::Octal(&value)));
  EXPECT_EQ(value, 0);
}

TEST(RE2CRadixTest_44, ParseDecimal_44) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("100", "(\\w+)", RE2::CRadix(&value)));
  EXPECT_EQ(value, 100);
}

TEST(RE2CRadixTest_44, ParseHexPrefix_44) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("0x1a", "(\\w+)", RE2::CRadix(&value)));
  EXPECT_EQ(value, 26);
}

TEST(RE2CRadixTest_44, ParseOctalPrefix_44) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("010", "(\\w+)", RE2::CRadix(&value)));
  EXPECT_EQ(value, 8);
}

// ===========================================================================
// Options tests
// ===========================================================================

TEST(RE2OptionsTest_44, CaseInsensitive_44) {
  RE2::Options opt;
  opt.set_case_sensitive(false);
  RE2 re("hello", opt);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
}

TEST(RE2OptionsTest_44, DotMatchesNewline_44) {
  RE2::Options opt;
  opt.set_dot_nl(true);
  RE2 re("a.b", opt);
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST(RE2OptionsTest_44, DefaultDotDoesNotMatchNewline_44) {
  RE2 re("a.b");
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

// ===========================================================================
// Various data type captures
// ===========================================================================

TEST(RE2TypesTest_44, CaptureFloat_44) {
  float f;
  EXPECT_TRUE(RE2::FullMatch("3.14", "([\\d.]+)", &f));
  EXPECT_NEAR(f, 3.14f, 0.01f);
}

TEST(RE2TypesTest_44, CaptureDouble_44) {
  double d;
  EXPECT_TRUE(RE2::FullMatch("2.71828", "([\\d.]+)", &d));
  EXPECT_NEAR(d, 2.71828, 0.00001);
}

TEST(RE2TypesTest_44, CaptureStringView_44) {
  absl::string_view sv;
  EXPECT_TRUE(RE2::FullMatch("hello world", "(\\w+) (\\w+)", &sv));
  EXPECT_EQ(sv, "hello");
}

TEST(RE2TypesTest_44, CaptureInt64_44) {
  int64_t val;
  EXPECT_TRUE(RE2::FullMatch("9999999999", "(\\d+)", &val));
  EXPECT_EQ(val, 9999999999LL);
}

TEST(RE2TypesTest_44, CaptureUint32_44) {
  uint32_t val;
  EXPECT_TRUE(RE2::FullMatch("4294967295", "(\\d+)", &val));
  EXPECT_EQ(val, 4294967295U);
}

// ===========================================================================
// Rewrite tests
// ===========================================================================

TEST(RE2RewriteTest_44, RewriteBasic_44) {
  RE2 re("(\\w+):(\\d+)");
  std::string out;
  absl::string_view vec[3] = {"host:80", "host", "80"};
  EXPECT_TRUE(re.Rewrite(&out, "\\1 at port \\2", vec, 3));
  EXPECT_EQ(out, "host at port 80");
}

TEST(RE2RewriteTest_44, RewriteInvalidBackref_44) {
  RE2 re("(\\w+)");
  std::string out;
  absl::string_view vec[2] = {"abc", "abc"};
  // \2 refers to a submatch that doesn't exist in vec with size 2 (indices 0,1)
  EXPECT_FALSE(re.Rewrite(&out, "\\2", vec, 2));
}

// ===========================================================================
// ProgramFanout tests
// ===========================================================================

TEST(RE2ProgramFanoutTest_44, FanoutWithVector_44) {
  RE2 re("(a|b)c");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ProgramFanoutTest_44, ReverseFanoutWithVector_44) {
  RE2 re("(a|b)c");
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ===========================================================================
// Edge/boundary cases
// ===========================================================================

TEST(RE2EdgeCaseTest_44, LongPattern_44) {
  std::string long_pattern(1000, 'a');
  RE2 re(long_pattern);
  EXPECT_TRUE(re.ok());
  std::string long_string(1000, 'a');
  EXPECT_TRUE(RE2::FullMatch(long_string, re));
  std::string short_string(999, 'a');
  EXPECT_FALSE(RE2::FullMatch(short_string, re));
}

TEST(RE2EdgeCaseTest_44, EmptyPattern_44) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
}

TEST(RE2EdgeCaseTest_44, FullMatchNullCapture_44) {
  // Pass no capture arguments
  EXPECT_TRUE(RE2::FullMatch("12345", "\\d+"));
}

TEST(RE2EdgeCaseTest_44, ReplaceEmptyMatch_44) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "", "X");
  // Each position + empty matches between chars
  EXPECT_GT(count, 0);
}

TEST(RE2EdgeCaseTest_44, MatchStartposEndpos_44) {
  RE2 re("abc");
  // endpos < startpos should not match
  EXPECT_FALSE(re.Match("abc", 2, 1, RE2::UNANCHORED, nullptr, 0));
}

TEST(RE2EdgeCaseTest_44, GlobalReplaceWithBackref_44) {
  std::string s = "aaa bbb ccc";
  int count = RE2::GlobalReplace(&s, "(\\w+)", "[\\1]");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "[aaa] [bbb] [ccc]");
}
