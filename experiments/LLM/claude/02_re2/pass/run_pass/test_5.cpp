#include "re2/re2.h"

#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

// =============================================================================
// Test fixture
// =============================================================================

class RE2Test_5 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// =============================================================================
// Construction and basic accessors
// =============================================================================

TEST_F(RE2Test_5, ConstructFromCString_5) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "hello");
}

TEST_F(RE2Test_5, ConstructFromStdString_5) {
  std::string pat = "world";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "world");
}

TEST_F(RE2Test_5, ConstructFromStringView_5) {
  absl::string_view sv = "foo.*bar";
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "foo.*bar");
}

TEST_F(RE2Test_5, InvalidPatternNotOk_5) {
  RE2 re("(incomplete");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error_code(), RE2::NoError);
  EXPECT_FALSE(re.error().empty());
}

TEST_F(RE2Test_5, ErrorCodeNoErrorForValid_5) {
  RE2 re("abc");
  EXPECT_EQ(re.error_code(), RE2::NoError);
  EXPECT_TRUE(re.error().empty());
}

TEST_F(RE2Test_5, ErrorArgForInvalidPattern_5) {
  RE2 re("[z-a]");
  EXPECT_FALSE(re.ok());
  // error_arg should contain something related to the bad range
  EXPECT_FALSE(re.error_arg().empty());
}

TEST_F(RE2Test_5, PatternReturnsSamePattern_5) {
  RE2 re("a(b+)c");
  EXPECT_EQ(re.pattern(), "a(b+)c");
}

// =============================================================================
// Options construction
// =============================================================================

TEST_F(RE2Test_5, ConstructWithOptions_5) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("Hello", opts);
  EXPECT_TRUE(re.ok());
}

// =============================================================================
// NumberOfCapturingGroups
// =============================================================================

TEST_F(RE2Test_5, NumberOfCapturingGroupsNone_5) {
  RE2 re("abc");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2Test_5, NumberOfCapturingGroupsOne_5) {
  RE2 re("a(b)c");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST_F(RE2Test_5, NumberOfCapturingGroupsMultiple_5) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(RE2Test_5, NumberOfCapturingGroupsNonCapturing_5) {
  RE2 re("(?:a)(b)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

// =============================================================================
// FullMatch
// =============================================================================

TEST_F(RE2Test_5, FullMatchSimple_5) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST_F(RE2Test_5, FullMatchWithCapture_5) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("ruby:1234", "(\\w+):(\\d+)", nullptr, &n));
  EXPECT_EQ(n, 1234);
}

TEST_F(RE2Test_5, FullMatchStringCapture_5) {
  std::string word;
  EXPECT_TRUE(RE2::FullMatch("test123", "(\\w+)", &word));
  EXPECT_EQ(word, "test123");
}

TEST_F(RE2Test_5, FullMatchNoMatch_5) {
  EXPECT_FALSE(RE2::FullMatch("abc", "def"));
}

TEST_F(RE2Test_5, FullMatchEmptyPattern_5) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_FALSE(RE2::FullMatch("a", ""));
}

TEST_F(RE2Test_5, FullMatchDot_5) {
  EXPECT_TRUE(RE2::FullMatch("a", "."));
  EXPECT_FALSE(RE2::FullMatch("ab", "."));
}

// =============================================================================
// PartialMatch
// =============================================================================

TEST_F(RE2Test_5, PartialMatchSimple_5) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "llo"));
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST_F(RE2Test_5, PartialMatchWithCapture_5) {
  std::string s;
  EXPECT_TRUE(RE2::PartialMatch("foo123bar", "(\\d+)", &s));
  EXPECT_EQ(s, "123");
}

TEST_F(RE2Test_5, PartialMatchEmptyString_5) {
  EXPECT_TRUE(RE2::PartialMatch("", ""));
  EXPECT_TRUE(RE2::PartialMatch("abc", ""));
}

// =============================================================================
// Consume
// =============================================================================

TEST_F(RE2Test_5, ConsumeBasic_5) {
  absl::string_view input("one123two456");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "(\\w+)", &word));
  EXPECT_EQ(word, "one123two456");
}

TEST_F(RE2Test_5, ConsumeRepeated_5) {
  absl::string_view input("aab");
  std::string s;
  EXPECT_TRUE(RE2::Consume(&input, "(a)", &s));
  EXPECT_EQ(s, "a");
  EXPECT_TRUE(RE2::Consume(&input, "(a)", &s));
  EXPECT_EQ(s, "a");
  EXPECT_FALSE(RE2::Consume(&input, "(a)", &s));
}

TEST_F(RE2Test_5, ConsumeNoMatch_5) {
  absl::string_view input("hello");
  EXPECT_FALSE(RE2::Consume(&input, "(\\d+)"));
  EXPECT_EQ(input, "hello");
}

// =============================================================================
// FindAndConsume
// =============================================================================

TEST_F(RE2Test_5, FindAndConsumeBasic_5) {
  absl::string_view input("a]]]b]]]c");
  std::string s;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "([a-z])", &s));
  EXPECT_EQ(s, "a");
  EXPECT_TRUE(RE2::FindAndConsume(&input, "([a-z])", &s));
  EXPECT_EQ(s, "b");
  EXPECT_TRUE(RE2::FindAndConsume(&input, "([a-z])", &s));
  EXPECT_EQ(s, "c");
  EXPECT_FALSE(RE2::FindAndConsume(&input, "([a-z])", &s));
}

// =============================================================================
// Replace
// =============================================================================

TEST_F(RE2Test_5, ReplaceFirst_5) {
  std::string s = "yabba dabba doo";
  EXPECT_TRUE(RE2::Replace(&s, "b+", "d"));
  EXPECT_EQ(s, "yada dabba doo");
}

TEST_F(RE2Test_5, ReplaceNoMatch_5) {
  std::string s = "hello";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ(s, "hello");
}

TEST_F(RE2Test_5, ReplaceWithBackreference_5) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "[\\1]"));
  EXPECT_EQ(s, "[hello] world");
}

// =============================================================================
// GlobalReplace
// =============================================================================

TEST_F(RE2Test_5, GlobalReplaceMultiple_5) {
  std::string s = "yabba dabba doo";
  int count = RE2::GlobalReplace(&s, "b+", "d");
  EXPECT_EQ(s, "yada dada doo");
  EXPECT_EQ(count, 2);
}

TEST_F(RE2Test_5, GlobalReplaceNoMatch_5) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello");
}

TEST_F(RE2Test_5, GlobalReplaceEmptyMatch_5) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "", "-");
  // Each position (including start and end) gets a replacement
  EXPECT_EQ(s, "-a-b-c-");
  EXPECT_EQ(count, 4);
}

// =============================================================================
// Extract
// =============================================================================

TEST_F(RE2Test_5, ExtractBasic_5) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremvax.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ(out, "kremvax!boris");
}

TEST_F(RE2Test_5, ExtractNoMatch_5) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-at-sign", "(.*)@([^.]*)", "\\2!\\1", &out));
}

// =============================================================================
// QuoteMeta
// =============================================================================

TEST_F(RE2Test_5, QuoteMetaSimple_5) {
  std::string quoted = RE2::QuoteMeta("1.5-2.0?");
  EXPECT_TRUE(RE2::FullMatch("1.5-2.0?", quoted));
  EXPECT_FALSE(RE2::FullMatch("1X5-2X0Y", quoted));
}

TEST_F(RE2Test_5, QuoteMetaSpecialChars_5) {
  std::string quoted = RE2::QuoteMeta("a]b[c");
  EXPECT_TRUE(RE2::FullMatch("a]b[c", quoted));
}

TEST_F(RE2Test_5, QuoteMetaEmpty_5) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

// =============================================================================
// Match (low-level)
// =============================================================================

TEST_F(RE2Test_5, MatchFullAnchor_5) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("1234", 0, 4, RE2::ANCHOR_BOTH, submatch, 2));
  EXPECT_EQ(submatch[0], "1234");
  EXPECT_EQ(submatch[1], "1234");
}

TEST_F(RE2Test_5, MatchPartialAnchor_5) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ(submatch[1], "123");
}

TEST_F(RE2Test_5, MatchNoSubmatch_5) {
  RE2 re("hello");
  EXPECT_TRUE(re.Match("say hello world", 0, 15, RE2::UNANCHORED, nullptr, 0));
}

TEST_F(RE2Test_5, MatchAnchorStartOnly_5) {
  RE2 re("hello");
  EXPECT_TRUE(re.Match("hello world", 0, 11, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_FALSE(re.Match("say hello", 0, 9, RE2::ANCHOR_START, nullptr, 0));
}

TEST_F(RE2Test_5, MatchStartposEndpos_5) {
  RE2 re("(\\d+)");
  absl::string_view text = "abc123def";
  absl::string_view submatch[2];
  // Search only in the range [3, 6) which is "123"
  EXPECT_TRUE(re.Match(text, 3, 6, RE2::ANCHOR_BOTH, submatch, 2));
  EXPECT_EQ(submatch[1], "123");
}

TEST_F(RE2Test_5, MatchFails_5) {
  RE2 re("xyz");
  EXPECT_FALSE(re.Match("hello", 0, 5, RE2::UNANCHORED, nullptr, 0));
}

// =============================================================================
// ProgramSize / ReverseProgramSize
// =============================================================================

TEST_F(RE2Test_5, ProgramSizePositive_5) {
  RE2 re("a+b*c?");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST_F(RE2Test_5, ReverseProgramSizePositive_5) {
  RE2 re("a+b*c?");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// =============================================================================
// ProgramFanout / ReverseProgramFanout
// =============================================================================

TEST_F(RE2Test_5, ProgramFanoutVector_5) {
  RE2 re("a+b");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST_F(RE2Test_5, ReverseProgramFanoutVector_5) {
  RE2 re("a+b");
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// =============================================================================
// NamedCapturingGroups / CapturingGroupNames
// =============================================================================

TEST_F(RE2Test_5, NamedCapturingGroupsEmpty_5) {
  RE2 re("(a)(b)");
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST_F(RE2Test_5, NamedCapturingGroupsPresent_5) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 2);
  EXPECT_EQ(groups.at("first"), 1);
  EXPECT_EQ(groups.at("second"), 2);
}

TEST_F(RE2Test_5, CapturingGroupNamesPresent_5) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 2);
  EXPECT_EQ(names.at(1), "first");
  EXPECT_EQ(names.at(2), "second");
}

TEST_F(RE2Test_5, CapturingGroupNamesEmpty_5) {
  RE2 re("(a)(b)");
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_TRUE(names.empty());
}

// =============================================================================
// CheckRewriteString
// =============================================================================

TEST_F(RE2Test_5, CheckRewriteStringValid_5) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST_F(RE2Test_5, CheckRewriteStringInvalidBackref_5) {
  RE2 re("(\\w+)");
  std::string error;
  // Only one capturing group, so \2 is invalid
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// =============================================================================
// MaxSubmatch
// =============================================================================

TEST_F(RE2Test_5, MaxSubmatchNone_5) {
  EXPECT_EQ(RE2::MaxSubmatch("no backrefs"), 0);
}

TEST_F(RE2Test_5, MaxSubmatchOne_5) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
}

TEST_F(RE2Test_5, MaxSubmatchMultiple_5) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1 and \\3"), 3);
}

// =============================================================================
// Rewrite
// =============================================================================

TEST_F(RE2Test_5, RewriteBasic_5) {
  RE2 re("(\\w+):(\\d+)");
  std::string out;
  absl::string_view vec[] = {"full:match", "full", "123"};
  EXPECT_TRUE(re.Rewrite(&out, "\\2-\\1", vec, 3));
  EXPECT_EQ(out, "123-full");
}

// =============================================================================
// PossibleMatchRange
// =============================================================================

TEST_F(RE2Test_5, PossibleMatchRangeBasic_5) {
  RE2 re("abc.*");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "abc");
  EXPECT_GE(max_str, "abc");
}

TEST_F(RE2Test_5, PossibleMatchRangeInvalid_5) {
  RE2 re("(bad");
  std::string min_str, max_str;
  // Invalid regex — behavior may vary, but we just check it doesn't crash
  re.PossibleMatchRange(&min_str, &max_str, 10);
}

// =============================================================================
// Hex, Octal, CRadix captures
// =============================================================================

TEST_F(RE2Test_5, HexCapture_5) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("ff", "(.*)", RE2::Hex(&v)));
  EXPECT_EQ(v, 255);
}

TEST_F(RE2Test_5, OctalCapture_5) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("77", "(.*)", RE2::Octal(&v)));
  EXPECT_EQ(v, 63);
}

TEST_F(RE2Test_5, CRadixHexCapture_5) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(.*)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 31);
}

TEST_F(RE2Test_5, CRadixDecimalCapture_5) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("100", "(.*)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 100);
}

TEST_F(RE2Test_5, CRadixOctalCapture_5) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("010", "(.*)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 8);
}

// =============================================================================
// Edge cases
// =============================================================================

TEST_F(RE2Test_5, EmptyPatternMatchesEmptyString_5) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
}

TEST_F(RE2Test_5, EmptyPatternPartialMatchAnything_5) {
  EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

TEST_F(RE2Test_5, ComplexPatternWorks_5) {
  RE2 re("^(?:(?P<year>\\d{4})-(?P<month>\\d{2})-(?P<day>\\d{2}))$");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
  std::string year, month, day;
  EXPECT_TRUE(RE2::FullMatch("2023-12-25", re, &year, &month, &day));
  EXPECT_EQ(year, "2023");
  EXPECT_EQ(month, "12");
  EXPECT_EQ(day, "25");
}

TEST_F(RE2Test_5, FullMatchWithNullArgs_5) {
  EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", nullptr));
}

TEST_F(RE2Test_5, FullMatchNWithNoArgs_5) {
  RE2 re("hello");
  EXPECT_TRUE(RE2::FullMatchN("hello", re, nullptr, 0));
  EXPECT_FALSE(RE2::FullMatchN("world", re, nullptr, 0));
}

TEST_F(RE2Test_5, PartialMatchNWithNoArgs_5) {
  RE2 re("ell");
  EXPECT_TRUE(RE2::PartialMatchN("hello", re, nullptr, 0));
  EXPECT_FALSE(RE2::PartialMatchN("world", re, nullptr, 0));
}

TEST_F(RE2Test_5, CaseSensitiveOptionDefault_5) {
  // By default case sensitive
  EXPECT_FALSE(RE2::FullMatch("Hello", "hello"));
}

TEST_F(RE2Test_5, CaseInsensitiveOption_5) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
}

TEST_F(RE2Test_5, OptionsAccessor_5) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_FALSE(re.options().case_sensitive());
}

// =============================================================================
// Multiple captures
// =============================================================================

TEST_F(RE2Test_5, MultipleCaptureTypes_5) {
  std::string s;
  int i;
  float f;
  EXPECT_TRUE(RE2::FullMatch("hello 42", "(\\w+) (\\d+)", &s, &i));
  EXPECT_EQ(s, "hello");
  EXPECT_EQ(i, 42);
}

TEST_F(RE2Test_5, LongCaptureChain_5) {
  std::string a, b, c, d;
  EXPECT_TRUE(RE2::FullMatch("1-2-3-4", "(\\d)-(\\d)-(\\d)-(\\d)", &a, &b, &c, &d));
  EXPECT_EQ(a, "1");
  EXPECT_EQ(b, "2");
  EXPECT_EQ(c, "3");
  EXPECT_EQ(d, "4");
}

// =============================================================================
// GlobalReplace with backreferences
// =============================================================================

TEST_F(RE2Test_5, GlobalReplaceWithBackreference_5) {
  std::string s = "aaa bbb ccc";
  int count = RE2::GlobalReplace(&s, "(\\w+)", "[\\1]");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "[aaa] [bbb] [ccc]");
}

// =============================================================================
// ok() on invalid regex
// =============================================================================

TEST_F(RE2Test_5, OkReturnsFalseForBadRegex_5) {
  RE2 re("*invalid");
  EXPECT_FALSE(re.ok());
}

TEST_F(RE2Test_5, OkReturnsTrueForGoodRegex_5) {
  RE2 re("valid.*");
  EXPECT_TRUE(re.ok());
}

// =============================================================================
// FullMatch with invalid regex
// =============================================================================

TEST_F(RE2Test_5, FullMatchWithInvalidRegex_5) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("anything", re));
}

TEST_F(RE2Test_5, PartialMatchWithInvalidRegex_5) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(RE2::PartialMatch("anything", re));
}
