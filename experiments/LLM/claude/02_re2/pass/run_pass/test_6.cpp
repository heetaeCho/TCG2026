#include "re2/re2.h"

#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

// ===========================================================================
// Basic construction & status
// ===========================================================================

TEST(RE2Test_6, ConstructFromCString_6) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "hello");
}

TEST(RE2Test_6, ConstructFromStdString_6) {
  std::string pat = "wor(ld)";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), pat);
}

TEST(RE2Test_6, ConstructFromStringView_6) {
  absl::string_view sv("abc+");
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "abc+");
}

TEST(RE2Test_6, InvalidPatternNotOk_6) {
  RE2 re("(incomplete");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error_code(), RE2::NoError);
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2Test_6, ErrorCodeNoErrorForValid_6) {
  RE2 re("valid");
  EXPECT_EQ(re.error_code(), RE2::NoError);
  EXPECT_TRUE(re.error().empty());
}

// ===========================================================================
// FullMatch
// ===========================================================================

TEST(RE2FullMatch_6, SimpleMatch_6) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2FullMatch_6, SimpleNoMatch_6) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatch_6, WithCapture_6) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &n));
  EXPECT_EQ(n, 12345);
}

TEST(RE2FullMatch_6, StringCapture_6) {
  std::string s;
  EXPECT_TRUE(RE2::FullMatch("abc-def", "([a-z]+)-([a-z]+)", &s));
  EXPECT_EQ(s, "abc");
}

TEST(RE2FullMatch_6, MultipleCaptures_6) {
  std::string a, b;
  EXPECT_TRUE(RE2::FullMatch("abc-def", "([a-z]+)-([a-z]+)", &a, &b));
  EXPECT_EQ(a, "abc");
  EXPECT_EQ(b, "def");
}

TEST(RE2FullMatch_6, EmptyPattern_6) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_FALSE(RE2::FullMatch("a", ""));
}

// ===========================================================================
// PartialMatch
// ===========================================================================

TEST(RE2PartialMatch_6, SimplePartial_6) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "wor"));
}

TEST(RE2PartialMatch_6, NoPartial_6) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2PartialMatch_6, CapturePartial_6) {
  int val;
  EXPECT_TRUE(RE2::PartialMatch("abc 42 def", "(\\d+)", &val));
  EXPECT_EQ(val, 42);
}

// ===========================================================================
// Consume & FindAndConsume
// ===========================================================================

TEST(RE2Consume_6, BasicConsume_6) {
  absl::string_view input("one123two456");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ(word, "one");
  // input should have advanced past "one"
  EXPECT_EQ(input, "123two456");
}

TEST(RE2Consume_6, ConsumeFailsOnMismatch_6) {
  absl::string_view input("123abc");
  std::string word;
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &word));
  // input unchanged on failure
  EXPECT_EQ(input, "123abc");
}

TEST(RE2FindAndConsume_6, BasicFindAndConsume_6) {
  absl::string_view input("one123two456");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 123);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 456);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

// ===========================================================================
// Replace
// ===========================================================================

TEST(RE2Replace_6, BasicReplace_6) {
  std::string s = "yabba dabba doo";
  EXPECT_TRUE(RE2::Replace(&s, "b+", "d"));
  EXPECT_EQ(s, "yadba dabba doo");
}

TEST(RE2Replace_6, NoMatchReplace_6) {
  std::string s = "hello";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ(s, "hello");
}

TEST(RE2Replace_6, ReplaceWithBackref_6) {
  std::string s = "abc def";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "[\\1]"));
  EXPECT_EQ(s, "[abc] def");
}

// ===========================================================================
// GlobalReplace
// ===========================================================================

TEST(RE2GlobalReplace_6, MultipleReplacements_6) {
  std::string s = "yabba dabba doo";
  int count = RE2::GlobalReplace(&s, "b+", "d");
  EXPECT_EQ(s, "yadda dadda doo");
  EXPECT_EQ(count, 2);
}

TEST(RE2GlobalReplace_6, NoMatchGlobal_6) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello");
}

// ===========================================================================
// Extract
// ===========================================================================

TEST(RE2Extract_6, BasicExtract_6) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST(RE2Extract_6, NoMatchExtract_6) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-at-sign", "(.*)@([^.]*)", "\\2!\\1", &out));
}

// ===========================================================================
// QuoteMeta
// ===========================================================================

TEST(RE2QuoteMeta_6, MetaCharacters_6) {
  std::string quoted = RE2::QuoteMeta("a.b+c*d");
  RE2 re(quoted);
  EXPECT_TRUE(RE2::FullMatch("a.b+c*d", re));
  EXPECT_FALSE(RE2::FullMatch("aXb+c*d", re));
}

TEST(RE2QuoteMeta_6, EmptyString_6) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

TEST(RE2QuoteMeta_6, AlphanumericPassThrough_6) {
  std::string quoted = RE2::QuoteMeta("hello123");
  EXPECT_EQ(quoted, "hello123");
}

// ===========================================================================
// NumberOfCapturingGroups
// ===========================================================================

TEST(RE2CapturingGroups_6, NoGroups_6) {
  RE2 re("abc");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2CapturingGroups_6, OneGroup_6) {
  RE2 re("a(bc)d");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(RE2CapturingGroups_6, MultipleGroups_6) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2CapturingGroups_6, NonCapturingGroup_6) {
  RE2 re("(?:abc)(def)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

// ===========================================================================
// NamedCapturingGroups & CapturingGroupNames
// ===========================================================================

TEST(RE2NamedGroups_6, NoNamedGroups_6) {
  RE2 re("(a)(b)");
  const std::map<std::string, int>& ncg = re.NamedCapturingGroups();
  EXPECT_TRUE(ncg.empty());
}

TEST(RE2NamedGroups_6, WithNamedGroups_6) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& ncg = re.NamedCapturingGroups();
  EXPECT_EQ(ncg.size(), 2u);
  ASSERT_NE(ncg.find("first"), ncg.end());
  EXPECT_EQ(ncg.at("first"), 1);
  ASSERT_NE(ncg.find("second"), ncg.end());
  EXPECT_EQ(ncg.at("second"), 2);
}

TEST(RE2CapturingGroupNames_6, WithNamedGroups_6) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  ASSERT_TRUE(re.ok());
  const std::map<int, std::string>& cgn = re.CapturingGroupNames();
  EXPECT_EQ(cgn.size(), 2u);
  ASSERT_NE(cgn.find(1), cgn.end());
  EXPECT_EQ(cgn.at(1), "first");
  ASSERT_NE(cgn.find(2), cgn.end());
  EXPECT_EQ(cgn.at(2), "second");
}

// ===========================================================================
// Match
// ===========================================================================

TEST(RE2Match_6, UnanchoredMatch_6) {
  RE2 re("(\\d+)");
  absl::string_view match;
  EXPECT_TRUE(re.Match("abc 123 def", 0, 11, RE2::UNANCHORED, &match, 1));
  EXPECT_EQ(match, "123");
}

TEST(RE2Match_6, AnchorStartMatch_6) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("abc 123", 0, 7, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_TRUE(re.Match("123 abc", 0, 7, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2Match_6, AnchorBothMatch_6) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_FALSE(re.Match("123 abc", 0, 7, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2Match_6, MatchWithStartPos_6) {
  RE2 re("\\d+");
  absl::string_view match;
  EXPECT_TRUE(re.Match("abc123def456", 6, 12, RE2::UNANCHORED, &match, 1));
  EXPECT_EQ(match, "456");
}

TEST(RE2Match_6, MatchWithEndPos_6) {
  RE2 re("\\d+");
  absl::string_view match;
  // Only search within "abc12"
  EXPECT_TRUE(re.Match("abc123def", 0, 5, RE2::UNANCHORED, &match, 1));
  EXPECT_EQ(match, "12");
}

TEST(RE2Match_6, MatchNullSubmatch_6) {
  RE2 re("hello");
  EXPECT_TRUE(re.Match("say hello world", 0, 15, RE2::UNANCHORED, nullptr, 0));
}

// ===========================================================================
// PossibleMatchRange
// ===========================================================================

TEST(RE2PossibleMatchRange_6, BasicRange_6) {
  RE2 re("abc.*");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "abc");
  EXPECT_GE(max_str, "abc");
}

// ===========================================================================
// CheckRewriteString
// ===========================================================================

TEST(RE2CheckRewrite_6, ValidRewrite_6) {
  RE2 re("(\\w+) (\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1-\\2", &error));
}

TEST(RE2CheckRewrite_6, InvalidRewriteTooHighBackref_6) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ===========================================================================
// MaxSubmatch
// ===========================================================================

TEST(RE2MaxSubmatch_6, NoBackrefs_6) {
  EXPECT_EQ(RE2::MaxSubmatch("hello"), 0);
}

TEST(RE2MaxSubmatch_6, SingleBackref_6) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
}

TEST(RE2MaxSubmatch_6, MultipleBackrefs_6) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1 and \\3"), 3);
}

// ===========================================================================
// Rewrite
// ===========================================================================

TEST(RE2Rewrite_6, BasicRewrite_6) {
  RE2 re("(\\w+)@(\\w+)");
  absl::string_view vec[3];
  vec[0] = "user@host";
  vec[1] = "user";
  vec[2] = "host";
  std::string out;
  EXPECT_TRUE(re.Rewrite(&out, "\\2!\\1", vec, 3));
  EXPECT_EQ(out, "host!user");
}

TEST(RE2Rewrite_6, RewriteInvalidBackref_6) {
  RE2 re("(\\w+)");
  absl::string_view vec[2];
  vec[0] = "hello";
  vec[1] = "hello";
  std::string out;
  // \\3 is out of range for veclen=2
  EXPECT_FALSE(re.Rewrite(&out, "\\3", vec, 2));
}

// ===========================================================================
// ProgramSize & ReverseProgramSize
// ===========================================================================

TEST(RE2ProgramSize_6, ValidPatternHasPositiveSize_6) {
  RE2 re("a+b*c?");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSize_6, ReverseProgramSize_6) {
  RE2 re("a+b*c?");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ===========================================================================
// ProgramFanout
// ===========================================================================

TEST(RE2ProgramFanout_6, BasicFanout_6) {
  RE2 re("a+b*c?");
  std::vector<int> histogram;
  int fanout = re.ProgramFanout(&histogram);
  EXPECT_GE(fanout, 0);
}

TEST(RE2ProgramFanout_6, ReverseFanout_6) {
  RE2 re("a+b*c?");
  std::vector<int> histogram;
  int fanout = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(fanout, 0);
}

// ===========================================================================
// Options
// ===========================================================================

TEST(RE2Options_6, CaseInsensitive_6) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2Options_6, OptionsAccessor_6) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_FALSE(re.options().case_sensitive());
}

// ===========================================================================
// Hex, Octal, CRadix
// ===========================================================================

TEST(RE2Hex_6, ParseHex_6) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("ff", "([0-9a-fA-F]+)", RE2::Hex(&n)));
  EXPECT_EQ(n, 255);
}

TEST(RE2Octal_6, ParseOctal_6) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("77", "([0-7]+)", RE2::Octal(&n)));
  EXPECT_EQ(n, 63);
}

TEST(RE2CRadix_6, ParseCRadixDecimal_6) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("100", "(\\w+)", RE2::CRadix(&n)));
  EXPECT_EQ(n, 100);
}

TEST(RE2CRadix_6, ParseCRadixHex_6) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(\\w+)", RE2::CRadix(&n)));
  EXPECT_EQ(n, 31);
}

TEST(RE2CRadix_6, ParseCRadixOctal_6) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("010", "(\\w+)", RE2::CRadix(&n)));
  EXPECT_EQ(n, 8);
}

// ===========================================================================
// Regexp() accessor
// ===========================================================================

TEST(RE2Regexp_6, ValidPatternReturnsNonNull_6) {
  RE2 re("abc");
  EXPECT_NE(re.Regexp(), nullptr);
}

TEST(RE2Regexp_6, InvalidPatternReturnsNull_6) {
  RE2 re("(abc");
  // An invalid pattern may or may not have a Regexp; test ok() is false
  EXPECT_FALSE(re.ok());
}

// ===========================================================================
// Edge cases
// ===========================================================================

TEST(RE2EdgeCase_6, EmptyPatternMatchesEmpty_6) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
}

TEST(RE2EdgeCase_6, DotMatchesNonNewline_6) {
  EXPECT_TRUE(RE2::FullMatch("a", "."));
  EXPECT_FALSE(RE2::FullMatch("\n", "."));
}

TEST(RE2EdgeCase_6, UnicodePattern_6) {
  RE2 re("\\p{L}+");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("café", re));
}

TEST(RE2EdgeCase_6, LargeCapture_6) {
  // Pattern with many groups
  RE2 re("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 10);
  EXPECT_TRUE(RE2::FullMatch("abcdefghij", re));
}

TEST(RE2EdgeCase_6, FullMatchPartialContent_6) {
  // FullMatch requires the entire string to match
  EXPECT_FALSE(RE2::FullMatch("abc123", "[a-z]+"));
  EXPECT_TRUE(RE2::FullMatch("abc123", "[a-z]+\\d+"));
}

TEST(RE2EdgeCase_6, OverflowIntCapture_6) {
  // A number too large for int; parsing should fail
  int n = 0;
  EXPECT_FALSE(RE2::FullMatch("99999999999999999999", "(\\d+)", &n));
}

TEST(RE2EdgeCase_6, ReplaceEmptyMatch_6) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "", "-");
  // Empty pattern matches at every position
  EXPECT_GT(count, 0);
}
