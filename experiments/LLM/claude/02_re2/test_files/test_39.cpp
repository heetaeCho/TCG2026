#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>

namespace {

// =====================================================================
// Construction and basic accessors
// =====================================================================

TEST(RE2Test_39, ConstructFromCString_39) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("hello", re.pattern());
}

TEST(RE2Test_39, ConstructFromStdString_39) {
  std::string pat = "world";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("world", re.pattern());
}

TEST(RE2Test_39, ConstructFromStringView_39) {
  absl::string_view sv = "foo.*bar";
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("foo.*bar", re.pattern());
}

TEST(RE2Test_39, ConstructWithOptions_39) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("Hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(false, re.options().case_sensitive());
}

TEST(RE2Test_39, InvalidPattern_39) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2Test_39, EmptyPattern_39) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("", re.pattern());
}

TEST(RE2Test_39, ErrorCodeOnValid_39) {
  RE2 re("abc");
  EXPECT_EQ(RE2::NoError, re.error_code());
}

// =====================================================================
// FullMatch
// =====================================================================

TEST(RE2FullMatchTest_39, SimpleMatch_39) {
  EXPECT_TRUE(RE2::FullMatch("hello", "h.*o"));
}

TEST(RE2FullMatchTest_39, NoMatch_39) {
  EXPECT_FALSE(RE2::FullMatch("hello", "world"));
}

TEST(RE2FullMatchTest_39, EmptyPatternEmptyString_39) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
}

TEST(RE2FullMatchTest_39, EmptyPatternNonEmptyString_39) {
  EXPECT_FALSE(RE2::FullMatch("abc", ""));
}

TEST(RE2FullMatchTest_39, CaptureGroup_39) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &n));
  EXPECT_EQ(12345, n);
}

TEST(RE2FullMatchTest_39, MultipleCaptureGroups_39) {
  std::string s;
  int n;
  EXPECT_TRUE(RE2::FullMatch("abc-123", "(\\w+)-(\\d+)", &s, &n));
  EXPECT_EQ("abc", s);
  EXPECT_EQ(123, n);
}

TEST(RE2FullMatchTest_39, PartialDoesNotFullMatch_39) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

// =====================================================================
// PartialMatch
// =====================================================================

TEST(RE2PartialMatchTest_39, SimplePartialMatch_39) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "llo"));
}

TEST(RE2PartialMatchTest_39, NoPartialMatch_39) {
  EXPECT_FALSE(RE2::PartialMatch("hello", "xyz"));
}

TEST(RE2PartialMatchTest_39, CapturePartialMatch_39) {
  std::string word;
  EXPECT_TRUE(RE2::PartialMatch("the quick brown fox", "(\\w+)\\s+fox", &word));
  EXPECT_EQ("brown", word);
}

TEST(RE2PartialMatchTest_39, EmptyStringEmptyPattern_39) {
  EXPECT_TRUE(RE2::PartialMatch("", ""));
}

// =====================================================================
// Consume
// =====================================================================

TEST(RE2ConsumeTest_39, BasicConsume_39) {
  absl::string_view input("one123two456");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ("one", word);
  EXPECT_EQ("123two456", std::string(input));
}

TEST(RE2ConsumeTest_39, ConsumeNoMatch_39) {
  absl::string_view input("123abc");
  std::string word;
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ("123abc", std::string(input));
}

TEST(RE2ConsumeTest_39, ConsumeRepeated_39) {
  absl::string_view input("aabbbcccc");
  std::string s;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z])", &s));
  EXPECT_EQ("a", s);
  EXPECT_TRUE(RE2::Consume(&input, "([a-z])", &s));
  EXPECT_EQ("a", s);
}

// =====================================================================
// FindAndConsume
// =====================================================================

TEST(RE2FindAndConsumeTest_39, BasicFindAndConsume_39) {
  absl::string_view input("123abc456def");
  std::string word;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "([a-z]+)", &word));
  EXPECT_EQ("abc", word);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "([a-z]+)", &word));
  EXPECT_EQ("def", word);
}

TEST(RE2FindAndConsumeTest_39, FindAndConsumeNoMatch_39) {
  absl::string_view input("123456");
  std::string word;
  EXPECT_FALSE(RE2::FindAndConsume(&input, "([a-z]+)", &word));
}

// =====================================================================
// Replace
// =====================================================================

TEST(RE2ReplaceTest_39, BasicReplace_39) {
  std::string s = "yabba dabba doo";
  EXPECT_TRUE(RE2::Replace(&s, "b+", "d"));
  EXPECT_EQ("yada dabba doo", s);
}

TEST(RE2ReplaceTest_39, ReplaceNoMatch_39) {
  std::string s = "hello";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ("hello", s);
}

TEST(RE2ReplaceTest_39, ReplaceWithBackreference_39) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "[\\1]"));
  EXPECT_EQ("[hello] world", s);
}

// =====================================================================
// GlobalReplace
// =====================================================================

TEST(RE2GlobalReplaceTest_39, BasicGlobalReplace_39) {
  std::string s = "yabba dabba doo";
  int count = RE2::GlobalReplace(&s, "b+", "d");
  EXPECT_EQ("yada dada doo", s);
  EXPECT_EQ(2, count);
}

TEST(RE2GlobalReplaceTest_39, GlobalReplaceNoMatch_39) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ(0, count);
  EXPECT_EQ("hello", s);
}

TEST(RE2GlobalReplaceTest_39, GlobalReplaceEmptyMatch_39) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "", "-");
  // Empty pattern matches at every position
  EXPECT_EQ("-a-b-c-", s);
  EXPECT_EQ(4, count);
}

// =====================================================================
// Extract
// =====================================================================

TEST(RE2ExtractTest_39, BasicExtract_39) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ("kremlin!boris", out);
}

TEST(RE2ExtractTest_39, ExtractNoMatch_39) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-at-sign", "(.*)@(.*)", "\\1", &out));
}

// =====================================================================
// QuoteMeta
// =====================================================================

TEST(RE2QuoteMetaTest_39, SimpleQuote_39) {
  std::string quoted = RE2::QuoteMeta("hello");
  EXPECT_EQ("hello", quoted);
}

TEST(RE2QuoteMetaTest_39, SpecialCharsQuote_39) {
  std::string quoted = RE2::QuoteMeta("a.b+c*d?e");
  // After quoting, using it as pattern should match literally
  EXPECT_TRUE(RE2::FullMatch("a.b+c*d?e", quoted));
}

TEST(RE2QuoteMetaTest_39, EmptyStringQuote_39) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ("", quoted);
}

TEST(RE2QuoteMetaTest_39, BackslashQuote_39) {
  std::string quoted = RE2::QuoteMeta("a\\b");
  EXPECT_TRUE(RE2::FullMatch("a\\b", quoted));
}

// =====================================================================
// NumberOfCapturingGroups
// =====================================================================

TEST(RE2CapturingGroupsTest_39, NoGroups_39) {
  RE2 re("abc");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_39, OneGroup_39) {
  RE2 re("(abc)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_39, MultipleGroups_39) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_39, NestedGroups_39) {
  RE2 re("((a)(b))");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_39, NonCapturingGroup_39) {
  RE2 re("(?:abc)(def)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

// =====================================================================
// NamedCapturingGroups
// =====================================================================

TEST(RE2NamedGroupsTest_39, NoNamedGroups_39) {
  RE2 re("(abc)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2NamedGroupsTest_39, OneNamedGroup_39) {
  RE2 re("(?P<name>\\w+)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(1u, groups.size());
  auto it = groups.find("name");
  ASSERT_NE(groups.end(), it);
  EXPECT_EQ(1, it->second);
}

TEST(RE2NamedGroupsTest_39, MultipleNamedGroups_39) {
  RE2 re("(?P<first>\\w+)\\s+(?P<second>\\w+)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(2u, groups.size());
  EXPECT_EQ(1, groups.at("first"));
  EXPECT_EQ(2, groups.at("second"));
}

// =====================================================================
// CapturingGroupNames
// =====================================================================

TEST(RE2GroupNamesTest_39, BasicGroupNames_39) {
  RE2 re("(?P<alpha>\\w+)\\s+(?P<beta>\\d+)");
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(2u, names.size());
  EXPECT_EQ("alpha", names.at(1));
  EXPECT_EQ("beta", names.at(2));
}

// =====================================================================
// Match
// =====================================================================

TEST(RE2MatchTest_39, FullAnchorMatch_39) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("12345", 0, 5, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_39, FullAnchorNoMatch_39) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("abc", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_39, UnanchoredMatch_39) {
  RE2 re("\\d+");
  absl::string_view match;
  EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, &match, 1));
  EXPECT_EQ("123", std::string(match));
}

TEST(RE2MatchTest_39, AnchorStartMatch_39) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_FALSE(re.Match("abc123", 0, 6, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_39, MatchWithStartPos_39) {
  RE2 re("\\d+");
  absl::string_view match;
  EXPECT_TRUE(re.Match("abc123", 3, 6, RE2::UNANCHORED, &match, 1));
  EXPECT_EQ("123", std::string(match));
}

TEST(RE2MatchTest_39, MatchWithSubmatch_39) {
  RE2 re("(\\w+)@(\\w+)");
  absl::string_view submatch[3];
  EXPECT_TRUE(re.Match("user@host", 0, 9, RE2::ANCHOR_BOTH, submatch, 3));
  EXPECT_EQ("user@host", std::string(submatch[0]));
  EXPECT_EQ("user", std::string(submatch[1]));
  EXPECT_EQ("host", std::string(submatch[2]));
}

// =====================================================================
// ProgramSize / ReverseProgramSize
// =====================================================================

TEST(RE2ProgramSizeTest_39, ValidPatternHasPositiveSize_39) {
  RE2 re("abc");
  EXPECT_GT(re.ProgramSize(), 0);
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// =====================================================================
// ProgramFanout
// =====================================================================

TEST(RE2ProgramFanoutTest_39, FanoutReturnsNonNegative_39) {
  RE2 re("a|b|c");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ProgramFanoutTest_39, ReverseFanoutReturnsNonNegative_39) {
  RE2 re("a|b|c");
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// =====================================================================
// PossibleMatchRange
// =====================================================================

TEST(RE2PossibleMatchRangeTest_39, BasicRange_39) {
  RE2 re("abc.*");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "abc");
  EXPECT_GE(max_str, "abc");
}

TEST(RE2PossibleMatchRangeTest_39, EmptyPatternRange_39) {
  RE2 re("");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
}

// =====================================================================
// CheckRewriteString
// =====================================================================

TEST(RE2CheckRewriteTest_39, ValidRewrite_39) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewriteTest_39, InvalidRewriteTooManyGroups_39) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// =====================================================================
// MaxSubmatch
// =====================================================================

TEST(RE2MaxSubmatchTest_39, NoBackreferences_39) {
  EXPECT_EQ(0, RE2::MaxSubmatch("no refs here"));
}

TEST(RE2MaxSubmatchTest_39, SingleBackreference_39) {
  EXPECT_EQ(3, RE2::MaxSubmatch("\\3"));
}

TEST(RE2MaxSubmatchTest_39, MultipleBackreferences_39) {
  EXPECT_EQ(5, RE2::MaxSubmatch("\\1 \\5 \\3"));
}

// =====================================================================
// Rewrite
// =====================================================================

TEST(RE2RewriteTest_39, BasicRewrite_39) {
  RE2 re("(\\w+)@(\\w+)");
  std::string out;
  absl::string_view vec[] = {"user@host", "user", "host"};
  EXPECT_TRUE(re.Rewrite(&out, "\\2!\\1", vec, 3));
  EXPECT_EQ("host!user", out);
}

TEST(RE2RewriteTest_39, RewriteInvalidBackref_39) {
  RE2 re("(a)");
  std::string out;
  absl::string_view vec[] = {"a", "a"};
  EXPECT_FALSE(re.Rewrite(&out, "\\3", vec, 2));
}

// =====================================================================
// Hex, Octal, CRadix parsing
// =====================================================================

TEST(RE2HexTest_39, ParseHex_39) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("ff", "([0-9a-fA-F]+)", RE2::Hex(&v)));
  EXPECT_EQ(255, v);
}

TEST(RE2OctalTest_39, ParseOctal_39) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("77", "([0-7]+)", RE2::Octal(&v)));
  EXPECT_EQ(63, v);
}

TEST(RE2CRadixTest_39, ParseCRadixDecimal_39) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("100", "(.*)", RE2::CRadix(&v)));
  EXPECT_EQ(100, v);
}

TEST(RE2CRadixTest_39, ParseCRadixHex_39) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(.*)", RE2::CRadix(&v)));
  EXPECT_EQ(31, v);
}

TEST(RE2CRadixTest_39, ParseCRadixOctal_39) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("010", "(.*)", RE2::CRadix(&v)));
  EXPECT_EQ(8, v);
}

// =====================================================================
// Options
// =====================================================================

TEST(RE2OptionsTest_39, DefaultOptions_39) {
  RE2 re("abc");
  EXPECT_TRUE(re.options().case_sensitive());
}

TEST(RE2OptionsTest_39, CaseInsensitive_39) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("abc", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("ABC", re));
}

TEST(RE2OptionsTest_39, Latin1Encoding_39) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re(".", opts);
  EXPECT_TRUE(re.ok());
}

TEST(RE2OptionsTest_39, DotNLOption_39) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST(RE2OptionsTest_39, DotNLDefaultFalse_39) {
  RE2 re("a.b");
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

// =====================================================================
// Edge cases
// =====================================================================

TEST(RE2EdgeCaseTest_39, NullSubmatchPointer_39) {
  RE2 re("(\\d+)");
  EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2EdgeCaseTest_39, MatchEmptyString_39) {
  RE2 re(".*");
  EXPECT_TRUE(RE2::FullMatch("", re));
}

TEST(RE2EdgeCaseTest_39, ComplexPattern_39) {
  RE2 re("^([a-zA-Z0-9_.+-]+)@([a-zA-Z0-9-]+)\\.([a-zA-Z0-9-.]+)$");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("user@example.com", re));
  EXPECT_FALSE(RE2::FullMatch("not-an-email", re));
}

TEST(RE2EdgeCaseTest_39, LargeCapturingGroups_39) {
  RE2 re("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(10, re.NumberOfCapturingGroups());
}

TEST(RE2EdgeCaseTest_39, MatchStartposBeyondText_39) {
  RE2 re("a");
  EXPECT_FALSE(re.Match("a", 5, 5, RE2::UNANCHORED, nullptr, 0));
}

TEST(RE2EdgeCaseTest_39, GlobalReplaceOnEmptyString_39) {
  std::string s = "";
  int count = RE2::GlobalReplace(&s, "a", "b");
  EXPECT_EQ(0, count);
  EXPECT_EQ("", s);
}

TEST(RE2EdgeCaseTest_39, ReplaceAllOccurrences_39) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, "a", "bb");
  EXPECT_EQ(3, count);
  EXPECT_EQ("bbbbbb", s);
}

}  // namespace
