#include "gtest/gtest.h"
#include "re2/re2.h"
#include <string>
#include <vector>
#include <map>

namespace {

// ============================================================
// Construction and basic accessors
// ============================================================

TEST(RE2Test_595, ConstructFromCString_595) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("hello", re.pattern());
}

TEST(RE2Test_595, ConstructFromStdString_595) {
  std::string pat = "wor(ld)";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(pat, re.pattern());
}

TEST(RE2Test_595, ConstructFromStringView_595) {
  absl::string_view sv("abc+");
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("abc+", re.pattern());
}

TEST(RE2Test_595, ConstructWithOptions_595) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("Hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("Hello", re.pattern());
}

TEST(RE2Test_595, InvalidPattern_595) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2Test_595, EmptyPattern_595) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("", re.pattern());
}

// ============================================================
// NumberOfCapturingGroups
// ============================================================

TEST(RE2Test_595, NumberOfCapturingGroupsNone_595) {
  RE2 re("abc");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(RE2Test_595, NumberOfCapturingGroupsOne_595) {
  RE2 re("a(bc)d");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(RE2Test_595, NumberOfCapturingGroupsMultiple_595) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2Test_595, NumberOfCapturingGroupsNonCapturing_595) {
  RE2 re("(?:abc)(def)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

// ============================================================
// FullMatch
// ============================================================

TEST(RE2Test_595, FullMatchSimple_595) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2Test_595, FullMatchWithCapture_595) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &n));
  EXPECT_EQ(12345, n);
}

TEST(RE2Test_595, FullMatchStringCapture_595) {
  std::string s;
  EXPECT_TRUE(RE2::FullMatch("abc", "(\\w+)", &s));
  EXPECT_EQ("abc", s);
}

TEST(RE2Test_595, FullMatchFails_595) {
  EXPECT_FALSE(RE2::FullMatch("abc", "\\d+"));
}

TEST(RE2Test_595, FullMatchEmptyPattern_595) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_FALSE(RE2::FullMatch("a", ""));
}

// ============================================================
// PartialMatch
// ============================================================

TEST(RE2Test_595, PartialMatchSimple_595) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "llo"));
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2Test_595, PartialMatchWithCapture_595) {
  std::string word;
  EXPECT_TRUE(RE2::PartialMatch("foo bar baz", "(bar)", &word));
  EXPECT_EQ("bar", word);
}

TEST(RE2Test_595, PartialMatchEmptyText_595) {
  EXPECT_TRUE(RE2::PartialMatch("", ""));
  EXPECT_FALSE(RE2::PartialMatch("", "a"));
}

// ============================================================
// Consume
// ============================================================

TEST(RE2Test_595, ConsumeBasic_595) {
  absl::string_view input("aab");
  EXPECT_TRUE(RE2::Consume(&input, "a"));
  EXPECT_EQ("ab", input);
  EXPECT_TRUE(RE2::Consume(&input, "a"));
  EXPECT_EQ("b", input);
  EXPECT_FALSE(RE2::Consume(&input, "a"));
}

TEST(RE2Test_595, ConsumeWithCapture_595) {
  absl::string_view input("123abc");
  int n;
  EXPECT_TRUE(RE2::Consume(&input, "(\\d+)", &n));
  EXPECT_EQ(123, n);
  EXPECT_EQ("abc", input);
}

// ============================================================
// FindAndConsume
// ============================================================

TEST(RE2Test_595, FindAndConsumeBasic_595) {
  absl::string_view input("aXbXc");
  std::string val;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(X)", &val));
  EXPECT_EQ("X", val);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(X)", &val));
  EXPECT_EQ("X", val);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(X)", &val));
}

// ============================================================
// Replace
// ============================================================

TEST(RE2Test_595, ReplaceFirst_595) {
  std::string s = "yabba dabba doo";
  EXPECT_TRUE(RE2::Replace(&s, "b+", "d"));
  EXPECT_EQ("yada dabba doo", s);
}

TEST(RE2Test_595, ReplaceNoMatch_595) {
  std::string s = "hello";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ("hello", s);
}

TEST(RE2Test_595, ReplaceWithBackreference_595) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "[\\1]"));
  EXPECT_EQ("[hello] world", s);
}

// ============================================================
// GlobalReplace
// ============================================================

TEST(RE2Test_595, GlobalReplaceBasic_595) {
  std::string s = "yabba dabba doo";
  int count = RE2::GlobalReplace(&s, "b+", "d");
  EXPECT_EQ("yada dada doo", s);
  EXPECT_EQ(2, count);
}

TEST(RE2Test_595, GlobalReplaceNoMatch_595) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "x", "y");
  EXPECT_EQ(0, count);
  EXPECT_EQ("abc", s);
}

TEST(RE2Test_595, GlobalReplaceEmptyMatch_595) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "", "-");
  // Empty regex matches at every position (before each char and at the end)
  EXPECT_EQ("-a-b-c-", s);
  EXPECT_EQ(4, count);
}

// ============================================================
// Extract
// ============================================================

TEST(RE2Test_595, ExtractBasic_595) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremvax.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ("kremvax!boris", out);
}

TEST(RE2Test_595, ExtractNoMatch_595) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no email here", "(.*)@([^.]*)", "\\2!\\1", &out));
}

// ============================================================
// QuoteMeta
// ============================================================

TEST(RE2Test_595, QuoteMetaBasic_595) {
  EXPECT_EQ("hello", RE2::QuoteMeta("hello"));
}

TEST(RE2Test_595, QuoteMetaSpecialChars_595) {
  std::string quoted = RE2::QuoteMeta("a.b+c*d?e");
  RE2 re(quoted);
  EXPECT_TRUE(RE2::FullMatch("a.b+c*d?e", re));
  EXPECT_FALSE(RE2::FullMatch("aXb+c*d?e", re));
}

TEST(RE2Test_595, QuoteMetaEmpty_595) {
  EXPECT_EQ("", RE2::QuoteMeta(""));
}

// ============================================================
// Match
// ============================================================

TEST(RE2Test_595, MatchUnanchored_595) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc 123 def", 0, 11, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ("123", submatch[0]);
  EXPECT_EQ("123", submatch[1]);
}

TEST(RE2Test_595, MatchAnchorStart_595) {
  RE2 re("(\\d+)");
  EXPECT_FALSE(re.Match("abc 123", 0, 7, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_TRUE(re.Match("123 abc", 0, 7, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2Test_595, MatchAnchorBoth_595) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_FALSE(re.Match("123abc", 0, 6, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2Test_595, MatchStartposEndpos_595) {
  RE2 re("\\d+");
  // Only search in the range [4, 7) of "abc 123 def" which is "123"
  EXPECT_TRUE(re.Match("abc 123 def", 4, 7, RE2::UNANCHORED, nullptr, 0));
  // Range [0, 3) is "abc" — no digits
  EXPECT_FALSE(re.Match("abc 123 def", 0, 3, RE2::UNANCHORED, nullptr, 0));
}

// ============================================================
// ProgramSize / ReverseProgramSize
// ============================================================

TEST(RE2Test_595, ProgramSizePositive_595) {
  RE2 re("a+b+c+");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2Test_595, ReverseProgramSizePositive_595) {
  RE2 re("a+b+c+");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ============================================================
// ProgramFanout / ReverseProgramFanout
// ============================================================

TEST(RE2Test_595, ProgramFanout_595) {
  RE2 re("abc");
  std::vector<int> histogram;
  int val = re.ProgramFanout(&histogram);
  // Just check it doesn't crash and returns something
  EXPECT_GE(val, 0);
}

TEST(RE2Test_595, ReverseProgramFanout_595) {
  RE2 re("abc");
  std::vector<int> histogram;
  int val = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(val, 0);
}

// ============================================================
// NamedCapturingGroups / CapturingGroupNames
// ============================================================

TEST(RE2Test_595, NamedCapturingGroupsEmpty_595) {
  RE2 re("(a)(b)");
  const auto& ncg = re.NamedCapturingGroups();
  EXPECT_TRUE(ncg.empty());
}

TEST(RE2Test_595, NamedCapturingGroupsNonEmpty_595) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  ASSERT_TRUE(re.ok());
  const auto& ncg = re.NamedCapturingGroups();
  EXPECT_EQ(2u, ncg.size());
  EXPECT_EQ(1, ncg.at("first"));
  EXPECT_EQ(2, ncg.at("second"));
}

TEST(RE2Test_595, CapturingGroupNames_595) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  ASSERT_TRUE(re.ok());
  const auto& cgn = re.CapturingGroupNames();
  EXPECT_EQ(2u, cgn.size());
  EXPECT_EQ("first", cgn.at(1));
  EXPECT_EQ("second", cgn.at(2));
}

// ============================================================
// CheckRewriteString
// ============================================================

TEST(RE2Test_595, CheckRewriteStringValid_595) {
  RE2 re("(\\w+) (\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1-\\2", &error));
}

TEST(RE2Test_595, CheckRewriteStringInvalid_595) {
  RE2 re("(\\w+)");
  std::string error;
  // \\2 references group 2 but there's only 1 group
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ============================================================
// MaxSubmatch
// ============================================================

TEST(RE2Test_595, MaxSubmatchNone_595) {
  EXPECT_EQ(0, RE2::MaxSubmatch("no backrefs"));
}

TEST(RE2Test_595, MaxSubmatchSome_595) {
  EXPECT_EQ(3, RE2::MaxSubmatch("\\1 and \\3"));
}

TEST(RE2Test_595, MaxSubmatchSingle_595) {
  EXPECT_EQ(1, RE2::MaxSubmatch("\\1"));
}

// ============================================================
// PossibleMatchRange
// ============================================================

TEST(RE2Test_595, PossibleMatchRange_595) {
  RE2 re("abc.*");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "abc");
  EXPECT_GE(max_str, "abc");
}

TEST(RE2Test_595, PossibleMatchRangeInvalid_595) {
  RE2 re("(bad");
  std::string min_str, max_str;
  // Invalid pattern; PossibleMatchRange may return false
  // (just ensure no crash)
  re.PossibleMatchRange(&min_str, &max_str, 10);
}

// ============================================================
// Rewrite
// ============================================================

TEST(RE2Test_595, RewriteBasic_595) {
  RE2 re("(\\w+):(\\d+)");
  absl::string_view vec[3] = {"full:123", "full", "123"};
  std::string out;
  EXPECT_TRUE(re.Rewrite(&out, "\\2-\\1", vec, 3));
  EXPECT_EQ("123-full", out);
}

// ============================================================
// Options
// ============================================================

TEST(RE2Test_595, OptionsAccessor_595) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(re.options().case_sensitive());
}

TEST(RE2Test_595, CaseInsensitiveFullMatch_595) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

// ============================================================
// Error code / error_arg
// ============================================================

TEST(RE2Test_595, ErrorCodeNoError_595) {
  RE2 re("abc");
  EXPECT_EQ(RE2::NoError, re.error_code());
  EXPECT_TRUE(re.error().empty());
}

TEST(RE2Test_595, ErrorCodeBadPattern_595) {
  RE2 re("[invalid");
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}

// ============================================================
// FullMatch with various data types
// ============================================================

TEST(RE2Test_595, FullMatchFloat_595) {
  float f;
  EXPECT_TRUE(RE2::FullMatch("3.14", "([\\d.]+)", &f));
  EXPECT_NEAR(3.14f, f, 0.001f);
}

TEST(RE2Test_595, FullMatchMultipleCaptures_595) {
  std::string s1, s2;
  int n;
  EXPECT_TRUE(RE2::FullMatch("abc-42-xyz", "(\\w+)-(\\d+)-(\\w+)", &s1, &n, &s2));
  EXPECT_EQ("abc", s1);
  EXPECT_EQ(42, n);
  EXPECT_EQ("xyz", s2);
}

// ============================================================
// Hex / Octal / CRadix
// ============================================================

TEST(RE2Test_595, HexCapture_595) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("ff", "([0-9a-fA-F]+)", RE2::Hex(&n)));
  EXPECT_EQ(255, n);
}

TEST(RE2Test_595, OctalCapture_595) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("77", "([0-7]+)", RE2::Octal(&n)));
  EXPECT_EQ(63, n);
}

TEST(RE2Test_595, CRadixHex_595) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(0x[0-9a-fA-F]+)", RE2::CRadix(&n)));
  EXPECT_EQ(31, n);
}

TEST(RE2Test_595, CRadixDecimal_595) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("100", "(\\d+)", RE2::CRadix(&n)));
  EXPECT_EQ(100, n);
}

TEST(RE2Test_595, CRadixOctal_595) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("010", "(0[0-7]*)", RE2::CRadix(&n)));
  EXPECT_EQ(8, n);
}

// ============================================================
// Complex patterns
// ============================================================

TEST(RE2Test_595, NestedGroups_595) {
  RE2 re("((a)(b))c");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
  std::string s1, s2, s3;
  EXPECT_TRUE(RE2::FullMatch("abc", re, &s1, &s2, &s3));
  EXPECT_EQ("ab", s1);
  EXPECT_EQ("a", s2);
  EXPECT_EQ("b", s3);
}

TEST(RE2Test_595, AlternationMatch_595) {
  RE2 re("cat|dog");
  EXPECT_TRUE(RE2::FullMatch("cat", re));
  EXPECT_TRUE(RE2::FullMatch("dog", re));
  EXPECT_FALSE(RE2::FullMatch("bird", re));
}

// ============================================================
// Boundary / edge cases
// ============================================================

TEST(RE2Test_595, VeryLongString_595) {
  std::string long_str(10000, 'a');
  RE2 re("a+");
  EXPECT_TRUE(RE2::FullMatch(long_str, re));
}

TEST(RE2Test_595, NullByteInPattern_595) {
  // Patterns with embedded NUL when using string_view
  std::string pat("a\\x00b", 5);
  // This is an unusual pattern; just ensure no crash
  RE2 re(pat);
  // ok or not is implementation-defined; just don't crash
}

TEST(RE2Test_595, PartialMatchEmptyPattern_595) {
  EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

TEST(RE2Test_595, GlobalReplaceIdentical_595) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, "a", "a");
  EXPECT_EQ(3, count);
  EXPECT_EQ("aaa", s);
}

}  // namespace
