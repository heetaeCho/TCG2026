#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>
#include <map>
#include <vector>

namespace {

// ============================================================
// FullMatch tests
// ============================================================

TEST(RE2FullMatchTest_7, SimpleMatch_7) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2FullMatchTest_7, SimpleNoMatch_7) {
  EXPECT_FALSE(RE2::FullMatch("hello", "world"));
}

TEST(RE2FullMatchTest_7, FullMatchRequiresEntireString_7) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatchTest_7, EmptyPatternMatchesEmptyString_7) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
}

TEST(RE2FullMatchTest_7, EmptyPatternDoesNotMatchNonEmpty_7) {
  EXPECT_FALSE(RE2::FullMatch("abc", ""));
}

TEST(RE2FullMatchTest_7, MatchWithCapture_7) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &n));
  EXPECT_EQ(n, 12345);
}

TEST(RE2FullMatchTest_7, MatchWithStringCapture_7) {
  std::string s;
  EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", &s));
  EXPECT_EQ(s, "hello");
}

TEST(RE2FullMatchTest_7, MatchWithMultipleCaptures_7) {
  int a, b;
  EXPECT_TRUE(RE2::FullMatch("123-456", "(\\d+)-(\\d+)", &a, &b));
  EXPECT_EQ(a, 123);
  EXPECT_EQ(b, 456);
}

TEST(RE2FullMatchTest_7, DotStarMatch_7) {
  EXPECT_TRUE(RE2::FullMatch("anything goes", ".*"));
}

TEST(RE2FullMatchTest_7, CaseInsensitiveWithOptions_7) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
}

// ============================================================
// PartialMatch tests
// ============================================================

TEST(RE2PartialMatchTest_7, SimplePartialMatch_7) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "hello"));
}

TEST(RE2PartialMatchTest_7, PartialMatchAnywhere_7) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "world"));
}

TEST(RE2PartialMatchTest_7, PartialMatchNoMatch_7) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2PartialMatchTest_7, PartialMatchWithCapture_7) {
  std::string word;
  EXPECT_TRUE(RE2::PartialMatch("the quick brown fox", "(\\w+)", &word));
  EXPECT_EQ(word, "the");
}

TEST(RE2PartialMatchTest_7, PartialMatchEmptyPattern_7) {
  EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

TEST(RE2PartialMatchTest_7, PartialMatchEmptyText_7) {
  EXPECT_FALSE(RE2::PartialMatch("", "\\d+"));
}

// ============================================================
// Consume tests
// ============================================================

TEST(RE2ConsumeTest_7, ConsumeBasic_7) {
  absl::string_view input("one123two456");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "(\\w+)", &word));
  // Consume anchors at the beginning, so it should match "one123two456"
}

TEST(RE2ConsumeTest_7, ConsumeMultipleCalls_7) {
  absl::string_view input("aab");
  EXPECT_TRUE(RE2::Consume(&input, "a"));
  EXPECT_TRUE(RE2::Consume(&input, "a"));
  EXPECT_TRUE(RE2::Consume(&input, "b"));
  EXPECT_TRUE(input.empty());
}

TEST(RE2ConsumeTest_7, ConsumeNoMatch_7) {
  absl::string_view input("hello");
  EXPECT_FALSE(RE2::Consume(&input, "\\d+"));
  EXPECT_EQ(input, "hello");
}

// ============================================================
// FindAndConsume tests
// ============================================================

TEST(RE2FindAndConsumeTest_7, FindAndConsumeBasic_7) {
  absl::string_view input("abc 123 def 456");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 123);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 456);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

TEST(RE2FindAndConsumeTest_7, FindAndConsumeNoMatch_7) {
  absl::string_view input("no numbers here");
  int n;
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

// ============================================================
// Replace tests
// ============================================================

TEST(RE2ReplaceTest_7, ReplaceFirst_7) {
  std::string s = "yabba dabba doo";
  EXPECT_TRUE(RE2::Replace(&s, "b+", "d"));
  EXPECT_EQ(s, "yadba dabba doo");
}

TEST(RE2ReplaceTest_7, ReplaceNoMatch_7) {
  std::string s = "hello";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ(s, "hello");
}

TEST(RE2ReplaceTest_7, ReplaceWithBackreference_7) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "[\\1]"));
  EXPECT_EQ(s, "[hello] world");
}

// ============================================================
// GlobalReplace tests
// ============================================================

TEST(RE2GlobalReplaceTest_7, GlobalReplaceAll_7) {
  std::string s = "yabba dabba doo";
  int count = RE2::GlobalReplace(&s, "b+", "d");
  EXPECT_EQ(s, "yadda dadda doo");
  EXPECT_EQ(count, 2);
}

TEST(RE2GlobalReplaceTest_7, GlobalReplaceNoMatch_7) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello");
}

TEST(RE2GlobalReplaceTest_7, GlobalReplaceEmpty_7) {
  std::string s = "";
  int count = RE2::GlobalReplace(&s, "a", "b");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "");
}

// ============================================================
// Extract tests
// ============================================================

TEST(RE2ExtractTest_7, ExtractBasic_7) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@example.com", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ(out, "example!boris");
}

TEST(RE2ExtractTest_7, ExtractNoMatch_7) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no match", "(\\d+)", "\\1", &out));
}

// ============================================================
// QuoteMeta tests
// ============================================================

TEST(RE2QuoteMetaTest_7, QuoteMetaSpecialChars_7) {
  std::string quoted = RE2::QuoteMeta("1.5-2.0?");
  EXPECT_TRUE(RE2::FullMatch("1.5-2.0?", quoted));
}

TEST(RE2QuoteMetaTest_7, QuoteMetaPlainString_7) {
  std::string quoted = RE2::QuoteMeta("hello");
  EXPECT_EQ(quoted, "hello");
}

TEST(RE2QuoteMetaTest_7, QuoteMetaEmpty_7) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

TEST(RE2QuoteMetaTest_7, QuoteMetaDoesNotMatchExtra_7) {
  std::string quoted = RE2::QuoteMeta("a.b");
  EXPECT_FALSE(RE2::FullMatch("axb", quoted));
  EXPECT_TRUE(RE2::FullMatch("a.b", quoted));
}

// ============================================================
// RE2 construction and status tests
// ============================================================

TEST(RE2ConstructionTest_7, ValidPattern_7) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.error_code(), RE2::NoError);
  EXPECT_EQ(re.error(), "");
}

TEST(RE2ConstructionTest_7, InvalidPattern_7) {
  RE2 re("(abc");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error_code(), RE2::NoError);
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2ConstructionTest_7, PatternAccessor_7) {
  RE2 re("hello.*world");
  EXPECT_EQ(re.pattern(), "hello.*world");
}

TEST(RE2ConstructionTest_7, ConstructFromCString_7) {
  RE2 re("test");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "test");
}

TEST(RE2ConstructionTest_7, ConstructFromStdString_7) {
  std::string pat = "test";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "test");
}

TEST(RE2ConstructionTest_7, ConstructFromStringView_7) {
  absl::string_view sv = "test";
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
}

// ============================================================
// NumberOfCapturingGroups tests
// ============================================================

TEST(RE2CapturingGroupsTest_7, NoCapturingGroups_7) {
  RE2 re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2CapturingGroupsTest_7, OneCapturingGroup_7) {
  RE2 re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(RE2CapturingGroupsTest_7, MultipleCapturingGroups_7) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2CapturingGroupsTest_7, NonCapturingGroup_7) {
  RE2 re("(?:hello)(world)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

// ============================================================
// NamedCapturingGroups tests
// ============================================================

TEST(RE2NamedCapturingGroupsTest_7, HasNamedGroup_7) {
  RE2 re("(?P<name>\\w+) (?P<age>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 2);
  EXPECT_EQ(groups.at("name"), 1);
  EXPECT_EQ(groups.at("age"), 2);
}

TEST(RE2NamedCapturingGroupsTest_7, NoNamedGroup_7) {
  RE2 re("(\\w+)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

// ============================================================
// CapturingGroupNames tests
// ============================================================

TEST(RE2CapturingGroupNamesTest_7, GroupNames_7) {
  RE2 re("(?P<first>\\w+)-(?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 2);
  EXPECT_EQ(names.at(1), "first");
  EXPECT_EQ(names.at(2), "second");
}

// ============================================================
// Match tests
// ============================================================

TEST(RE2MatchTest_7, MatchAnchored_7) {
  RE2 re("(\\d+)-(\\w+)");
  absl::string_view submatch[3];
  EXPECT_TRUE(re.Match("123-abc", 0, 7, RE2::ANCHOR_BOTH, submatch, 3));
  EXPECT_EQ(submatch[0], "123-abc");
  EXPECT_EQ(submatch[1], "123");
  EXPECT_EQ(submatch[2], "abc");
}

TEST(RE2MatchTest_7, MatchUnanchored_7) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc 123 def", 0, 11, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ(submatch[1], "123");
}

TEST(RE2MatchTest_7, MatchNoMatch_7) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("abc", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_7, MatchAnchorStart_7) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_FALSE(re.Match("abc123", 0, 6, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_7, MatchSubRange_7) {
  RE2 re("\\d+");
  // Match within a subrange
  EXPECT_TRUE(re.Match("abc123def", 3, 6, RE2::ANCHOR_BOTH, nullptr, 0));
}

// ============================================================
// ProgramSize tests
// ============================================================

TEST(RE2ProgramSizeTest_7, ProgramSizePositive_7) {
  RE2 re("hello");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_7, ReverseProgramSizePositive_7) {
  RE2 re("hello");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ============================================================
// PossibleMatchRange tests
// ============================================================

TEST(RE2PossibleMatchRangeTest_7, BasicRange_7) {
  RE2 re("hello");
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "hello");
  EXPECT_GE(max, "hello");
}

// ============================================================
// CheckRewriteString tests
// ============================================================

TEST(RE2CheckRewriteStringTest_7, ValidRewrite_7) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewriteStringTest_7, InvalidRewrite_7) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ============================================================
// MaxSubmatch tests
// ============================================================

TEST(RE2MaxSubmatchTest_7, NoSubmatch_7) {
  EXPECT_EQ(RE2::MaxSubmatch("no backrefs"), 0);
}

TEST(RE2MaxSubmatchTest_7, OneSubmatch_7) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
}

TEST(RE2MaxSubmatchTest_7, MultipleSubmatch_7) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1 and \\3"), 3);
}

// ============================================================
// Hex, Octal, CRadix capture tests
// ============================================================

TEST(RE2HexTest_7, HexCapture_7) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("ff", "(\\w+)", RE2::Hex(&v)));
  EXPECT_EQ(v, 255);
}

TEST(RE2OctalTest_7, OctalCapture_7) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("77", "(\\w+)", RE2::Octal(&v)));
  EXPECT_EQ(v, 63);
}

TEST(RE2CRadixTest_7, CRadixHex_7) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(\\w+)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 31);
}

TEST(RE2CRadixTest_7, CRadixOctal_7) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("010", "(\\w+)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 8);
}

TEST(RE2CRadixTest_7, CRadixDecimal_7) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("42", "(\\w+)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 42);
}

// ============================================================
// ProgramFanout tests
// ============================================================

TEST(RE2ProgramFanoutTest_7, FanoutVector_7) {
  RE2 re("(a|b)c");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ProgramFanoutTest_7, ReverseFanoutVector_7) {
  RE2 re("(a|b)c");
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ============================================================
// Rewrite tests
// ============================================================

TEST(RE2RewriteTest_7, BasicRewrite_7) {
  RE2 re("(\\w+)@(\\w+)");
  absl::string_view vec[3];
  vec[0] = "boris@example";
  vec[1] = "boris";
  vec[2] = "example";
  std::string out;
  EXPECT_TRUE(re.Rewrite(&out, "\\2!\\1", vec, 3));
  EXPECT_EQ(out, "example!boris");
}

TEST(RE2RewriteTest_7, RewriteInvalidBackref_7) {
  RE2 re("(\\w+)");
  absl::string_view vec[2];
  vec[0] = "hello";
  vec[1] = "hello";
  std::string out;
  // \3 does not exist with only 1 submatch
  EXPECT_FALSE(re.Rewrite(&out, "\\3", vec, 2));
}

// ============================================================
// Edge cases with special characters and unicode
// ============================================================

TEST(RE2SpecialCasesTest_7, MatchNewline_7) {
  EXPECT_FALSE(RE2::FullMatch("hello\nworld", "hello.world"));
  // With s flag
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("hello.world", opts);
  EXPECT_TRUE(RE2::FullMatch("hello\nworld", re));
}

TEST(RE2SpecialCasesTest_7, UnicodeMatch_7) {
  EXPECT_TRUE(RE2::FullMatch("café", "caf."));
}

TEST(RE2SpecialCasesTest_7, LongStringMatch_7) {
  std::string long_str(10000, 'a');
  EXPECT_TRUE(RE2::FullMatch(long_str, "a+"));
}

TEST(RE2SpecialCasesTest_7, NullBytesInString_7) {
  std::string s("abc\0def", 7);
  absl::string_view sv(s);
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("abc.def", opts);
  EXPECT_TRUE(RE2::FullMatch(sv, re));
}

// ============================================================
// Type capture tests
// ============================================================

TEST(RE2TypeCaptureTest_7, CaptureFloat_7) {
  float f;
  EXPECT_TRUE(RE2::FullMatch("3.14", "([\\d.]+)", &f));
  EXPECT_NEAR(f, 3.14f, 0.01f);
}

TEST(RE2TypeCaptureTest_7, CaptureDouble_7) {
  double d;
  EXPECT_TRUE(RE2::FullMatch("3.14159", "([\\d.]+)", &d));
  EXPECT_NEAR(d, 3.14159, 0.0001);
}

TEST(RE2TypeCaptureTest_7, CaptureStringPiece_7) {
  absl::string_view sp;
  EXPECT_TRUE(RE2::FullMatch("hello world", "(\\S+)\\s+(\\S+)", &sp));
  EXPECT_EQ(sp, "hello");
}

TEST(RE2TypeCaptureTest_7, OverflowIntCapture_7) {
  int v;
  // Number too large for int
  EXPECT_FALSE(RE2::FullMatch("99999999999999999999", "(\\d+)", &v));
}

// ============================================================
// Options tests
// ============================================================

TEST(RE2OptionsTest_7, OptionsAccessor_7) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_FALSE(re.options().case_sensitive());
}

TEST(RE2OptionsTest_7, Utf8OptionDefault_7) {
  RE2 re("test");
  EXPECT_TRUE(re.options().utf8());
}

// ============================================================
// FullMatchN / PartialMatchN with no captures
// ============================================================

TEST(RE2FullMatchNTest_7, NoCaptures_7) {
  EXPECT_TRUE(RE2::FullMatchN("hello", RE2("hello"), nullptr, 0));
}

TEST(RE2PartialMatchNTest_7, NoCaptures_7) {
  EXPECT_TRUE(RE2::PartialMatchN("hello world", RE2("hello"), nullptr, 0));
}

TEST(RE2ConsumeNTest_7, NoCaptures_7) {
  absl::string_view input("hello world");
  EXPECT_TRUE(RE2::ConsumeN(&input, RE2("hello"), nullptr, 0));
  EXPECT_EQ(input, " world");
}

TEST(RE2FindAndConsumeNTest_7, NoCaptures_7) {
  absl::string_view input("abc 123 def");
  EXPECT_TRUE(RE2::FindAndConsumeN(&input, RE2("\\d+"), nullptr, 0));
  EXPECT_EQ(input, " def");
}

}  // namespace
