#include "re2/re2.h"

#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

// ===========================================================================
// Construction & basic accessors
// ===========================================================================

TEST(RE2Test_3, ConstructFromCString_3) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "hello");
  EXPECT_EQ(re.error(), "");
}

TEST(RE2Test_3, ConstructFromStdString_3) {
  std::string pat = "wor(ld)";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), pat);
}

TEST(RE2Test_3, ConstructFromStringView_3) {
  absl::string_view sv("abc+");
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "abc+");
}

TEST(RE2Test_3, InvalidPatternNotOk_3) {
  RE2 re("(abc");  // unmatched parenthesis
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error(), "");
  EXPECT_NE(re.error_code(), RE2::NoError);
}

TEST(RE2Test_3, ErrorCodeIsNoErrorForValid_3) {
  RE2 re("abc");
  EXPECT_EQ(re.error_code(), RE2::NoError);
}

TEST(RE2Test_3, EmptyPattern_3) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "");
}

// ===========================================================================
// FullMatch
// ===========================================================================

TEST(RE2FullMatchTest_3, SimpleMatch_3) {
  EXPECT_TRUE(RE2::FullMatch("hello", "h.*o"));
}

TEST(RE2FullMatchTest_3, SimpleNoMatch_3) {
  EXPECT_FALSE(RE2::FullMatch("hello", "e"));
}

TEST(RE2FullMatchTest_3, CaptureGroup_3) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("ruby:1234", "(\\w+):(\\d+)", (void*)nullptr, &n));
  EXPECT_EQ(n, 1234);
}

TEST(RE2FullMatchTest_3, CaptureString_3) {
  std::string word;
  EXPECT_TRUE(RE2::FullMatch("test123", "(\\w+)", &word));
  EXPECT_EQ(word, "test123");
}

TEST(RE2FullMatchTest_3, EmptyTextAndPattern_3) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
}

TEST(RE2FullMatchTest_3, EmptyTextNonEmptyPattern_3) {
  EXPECT_FALSE(RE2::FullMatch("", "abc"));
}

TEST(RE2FullMatchTest_3, PatternDoesNotCoverEntireText_3) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

// ===========================================================================
// PartialMatch
// ===========================================================================

TEST(RE2PartialMatchTest_3, SimplePartialMatch_3) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "ello"));
}

TEST(RE2PartialMatchTest_3, NoPartialMatch_3) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2PartialMatchTest_3, CaptureInPartialMatch_3) {
  int value;
  EXPECT_TRUE(RE2::PartialMatch("x]234 foo", "(\\d+)", &value));
  EXPECT_EQ(value, 234);
}

TEST(RE2PartialMatchTest_3, EmptyPatternMatchesAnything_3) {
  EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

// ===========================================================================
// Consume
// ===========================================================================

TEST(RE2ConsumeTest_3, ConsumeAdvancesInput_3) {
  absl::string_view input("one two three");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "(\\w+)", &word));
  EXPECT_EQ(word, "one");
  // input should have advanced past "one"
  EXPECT_EQ(input.substr(0, 1), " ");
}

TEST(RE2ConsumeTest_3, ConsumeNoMatch_3) {
  absl::string_view input("123abc");
  std::string word;
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &word));
}

// ===========================================================================
// FindAndConsume
// ===========================================================================

TEST(RE2FindAndConsumeTest_3, FindAndConsumeMultiple_3) {
  absl::string_view input("a]1 b]2 c]3");
  int val;
  std::vector<int> results;
  while (RE2::FindAndConsume(&input, "(\\d+)", &val)) {
    results.push_back(val);
  }
  ASSERT_EQ(results.size(), 3u);
  EXPECT_EQ(results[0], 1);
  EXPECT_EQ(results[1], 2);
  EXPECT_EQ(results[2], 3);
}

// ===========================================================================
// Replace
// ===========================================================================

TEST(RE2ReplaceTest_3, ReplaceFirst_3) {
  std::string s = "yabba dabba doo";
  EXPECT_TRUE(RE2::Replace(&s, "b+", "d"));
  EXPECT_EQ(s, "yadba dabba doo");
}

TEST(RE2ReplaceTest_3, ReplaceNoMatch_3) {
  std::string s = "hello";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ(s, "hello");
}

TEST(RE2ReplaceTest_3, ReplaceWithBackreference_3) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "[\\1]"));
  EXPECT_EQ(s, "[hello] world");
}

// ===========================================================================
// GlobalReplace
// ===========================================================================

TEST(RE2GlobalReplaceTest_3, ReplaceAll_3) {
  std::string s = "yabba dabba doo";
  int count = RE2::GlobalReplace(&s, "b+", "d");
  EXPECT_EQ(s, "yadda dadda doo");
  EXPECT_EQ(count, 2);
}

TEST(RE2GlobalReplaceTest_3, ReplaceAllNone_3) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello");
}

TEST(RE2GlobalReplaceTest_3, GlobalReplaceEmptyMatch_3) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "", "-");
  // Empty pattern matches at every position
  EXPECT_GE(count, 4);  // before a, a, b, c, after c
}

// ===========================================================================
// Extract
// ===========================================================================

TEST(RE2ExtractTest_3, ExtractSuccess_3) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremvax.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ(out, "kremvax!boris");
}

TEST(RE2ExtractTest_3, ExtractFailure_3) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-at-sign", "(.*)@(.*)", "\\2!\\1", &out));
}

// ===========================================================================
// QuoteMeta
// ===========================================================================

TEST(RE2QuoteMetaTest_3, SimpleQuote_3) {
  std::string quoted = RE2::QuoteMeta("1.5-2.0?");
  EXPECT_TRUE(RE2::FullMatch("1.5-2.0?", quoted));
}

TEST(RE2QuoteMetaTest_3, EmptyString_3) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

TEST(RE2QuoteMetaTest_3, SpecialCharacters_3) {
  std::string special = "a]b[c(d)e{f}g*h+i?j.k\\l^m$n|o";
  std::string quoted = RE2::QuoteMeta(special);
  EXPECT_TRUE(RE2::FullMatch(special, quoted));
}

// ===========================================================================
// NumberOfCapturingGroups
// ===========================================================================

TEST(RE2CapturingGroupsTest_3, ZeroGroups_3) {
  RE2 re("abc");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2CapturingGroupsTest_3, OneGroup_3) {
  RE2 re("(abc)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(RE2CapturingGroupsTest_3, MultipleGroups_3) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2CapturingGroupsTest_3, NestedGroups_3) {
  RE2 re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2CapturingGroupsTest_3, NonCapturingGroup_3) {
  RE2 re("(?:abc)(def)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

// ===========================================================================
// NamedCapturingGroups
// ===========================================================================

TEST(RE2NamedCapturingGroupsTest_3, NoNamedGroups_3) {
  RE2 re("(abc)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2NamedCapturingGroupsTest_3, OneNamedGroup_3) {
  RE2 re("(?P<name>\\w+)");
  const auto& groups = re.NamedCapturingGroups();
  ASSERT_EQ(groups.size(), 1u);
  EXPECT_EQ(groups.at("name"), 1);
}

TEST(RE2NamedCapturingGroupsTest_3, MultipleNamedGroups_3) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  const auto& groups = re.NamedCapturingGroups();
  ASSERT_EQ(groups.size(), 2u);
  EXPECT_EQ(groups.at("first"), 1);
  EXPECT_EQ(groups.at("second"), 2);
}

// ===========================================================================
// CapturingGroupNames
// ===========================================================================

TEST(RE2CapturingGroupNamesTest_3, NoNames_3) {
  RE2 re("(abc)");
  const auto& names = re.CapturingGroupNames();
  EXPECT_TRUE(names.empty());
}

TEST(RE2CapturingGroupNamesTest_3, WithNames_3) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  const auto& names = re.CapturingGroupNames();
  ASSERT_EQ(names.size(), 2u);
  EXPECT_EQ(names.at(1), "first");
  EXPECT_EQ(names.at(2), "second");
}

// ===========================================================================
// Match
// ===========================================================================

TEST(RE2MatchTest_3, FullAnchor_3) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("1234", 0, 4, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_FALSE(re.Match("12ab", 0, 4, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_3, UnanchoredMatch_3) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, nullptr, 0));
}

TEST(RE2MatchTest_3, AnchorStartMatch_3) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_FALSE(re.Match("abc123", 0, 6, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_3, SubmatchCapture_3) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ(submatch[0], "123");
  EXPECT_EQ(submatch[1], "123");
}

TEST(RE2MatchTest_3, StartposEndpos_3) {
  RE2 re("\\d+");
  // Restrict search to a substring
  EXPECT_TRUE(re.Match("abc123def", 3, 6, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_FALSE(re.Match("abc123def", 0, 3, RE2::UNANCHORED, nullptr, 0));
}

// ===========================================================================
// PossibleMatchRange
// ===========================================================================

TEST(RE2PossibleMatchRangeTest_3, BasicRange_3) {
  RE2 re("abc.*");
  std::string min_s, max_s;
  EXPECT_TRUE(re.PossibleMatchRange(&min_s, &max_s, 10));
  EXPECT_LE(min_s, "abc");
  EXPECT_GE(max_s, "abc");
}

// ===========================================================================
// CheckRewriteString
// ===========================================================================

TEST(RE2CheckRewriteStringTest_3, ValidRewrite_3) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewriteStringTest_3, InvalidRewriteTooHighBackref_3) {
  RE2 re("(\\w+)");
  std::string error;
  // \2 refers to a non-existent group
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_NE(error, "");
}

// ===========================================================================
// MaxSubmatch
// ===========================================================================

TEST(RE2MaxSubmatchTest_3, NoBackreferences_3) {
  EXPECT_EQ(RE2::MaxSubmatch("hello"), 0);
}

TEST(RE2MaxSubmatchTest_3, OneBackreference_3) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
}

TEST(RE2MaxSubmatchTest_3, MultipleBackreferences_3) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1 \\3 \\2"), 3);
}

// ===========================================================================
// Rewrite
// ===========================================================================

TEST(RE2RewriteTest_3, SimpleRewrite_3) {
  RE2 re("(\\d+)");
  std::string out;
  absl::string_view vec[] = {"123", "123"};
  EXPECT_TRUE(re.Rewrite(&out, "number=\\1", vec, 2));
  EXPECT_EQ(out, "number=123");
}

TEST(RE2RewriteTest_3, RewriteWithInvalidBackref_3) {
  RE2 re("(\\d+)");
  std::string out;
  absl::string_view vec[] = {"123", "123"};
  // \2 doesn't exist in vec of size 2 (indices 0 and 1)
  EXPECT_FALSE(re.Rewrite(&out, "\\2", vec, 2));
}

// ===========================================================================
// ProgramSize
// ===========================================================================

TEST(RE2ProgramSizeTest_3, ValidPatternHasPositiveSize_3) {
  RE2 re("hello.*world");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_3, SimplePatternSmallSize_3) {
  RE2 re("a");
  EXPECT_GT(re.ProgramSize(), 0);
}

// ===========================================================================
// ReverseProgramSize
// ===========================================================================

TEST(RE2ReverseProgramSizeTest_3, ValidPatternHasPositiveSize_3) {
  RE2 re("hello.*world");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ===========================================================================
// ProgramFanout
// ===========================================================================

TEST(RE2ProgramFanoutTest_3, ValidPatternFanout_3) {
  RE2 re("hello.*world");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ===========================================================================
// Options
// ===========================================================================

TEST(RE2OptionsTest_3, CaseSensitiveByDefault_3) {
  RE2 re("hello");
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
}

TEST(RE2OptionsTest_3, CaseInsensitive_3) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
}

TEST(RE2OptionsTest_3, Posix_3) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  opts.set_longest_match(true);
  RE2 re("(a|ab)", opts);
  EXPECT_TRUE(re.ok());
}

// ===========================================================================
// Hex / Octal / CRadix parsing
// ===========================================================================

TEST(RE2HexTest_3, ParseHexValue_3) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(0x[0-9a-fA-F]+)", RE2::Hex(&value)));
  EXPECT_EQ(value, 0x1f);
}

TEST(RE2OctalTest_3, ParseOctalValue_3) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("077", "(0[0-7]+)", RE2::Octal(&value)));
  EXPECT_EQ(value, 077);
}

TEST(RE2CRadixTest_3, ParseCRadixDecimal_3) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("100", "(\\d+)", RE2::CRadix(&value)));
  EXPECT_EQ(value, 100);
}

TEST(RE2CRadixTest_3, ParseCRadixHex_3) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("0x10", "(0x[0-9a-fA-F]+)", RE2::CRadix(&value)));
  EXPECT_EQ(value, 16);
}

// ===========================================================================
// Type capture tests
// ===========================================================================

TEST(RE2CaptureTypesTest_3, CaptureFloat_3) {
  float f;
  EXPECT_TRUE(RE2::FullMatch("3.14", "([0-9.]+)", &f));
  EXPECT_NEAR(f, 3.14f, 0.001f);
}

TEST(RE2CaptureTypesTest_3, CaptureDouble_3) {
  double d;
  EXPECT_TRUE(RE2::FullMatch("2.71828", "([0-9.]+)", &d));
  EXPECT_NEAR(d, 2.71828, 0.00001);
}

TEST(RE2CaptureTypesTest_3, CaptureLong_3) {
  long l;
  EXPECT_TRUE(RE2::FullMatch("987654321", "(\\d+)", &l));
  EXPECT_EQ(l, 987654321L);
}

// ===========================================================================
// Edge cases
// ===========================================================================

TEST(RE2EdgeCaseTest_3, VeryLongPattern_3) {
  // Build a valid long pattern
  std::string pattern(1000, 'a');
  RE2 re(pattern);
  EXPECT_TRUE(re.ok());
  std::string text(1000, 'a');
  EXPECT_TRUE(RE2::FullMatch(text, re));
  std::string short_text(999, 'a');
  EXPECT_FALSE(RE2::FullMatch(short_text, re));
}

TEST(RE2EdgeCaseTest_3, NullSubmatchArray_3) {
  RE2 re("(\\d+)-(\\d+)");
  EXPECT_TRUE(re.Match("123-456", 0, 7, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2EdgeCaseTest_3, DotMatchesNewlineDefault_3) {
  // By default, . does not match \n
  EXPECT_FALSE(RE2::FullMatch("a\nb", "a.b"));
}

TEST(RE2EdgeCaseTest_3, DotMatchesNewlineOption_3) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST(RE2EdgeCaseTest_3, MultipleMatchTypes_3) {
  std::string s1;
  int n;
  EXPECT_TRUE(RE2::FullMatch("abc:42", "(\\w+):(\\d+)", &s1, &n));
  EXPECT_EQ(s1, "abc");
  EXPECT_EQ(n, 42);
}

TEST(RE2EdgeCaseTest_3, FullMatchNWithNoArgs_3) {
  EXPECT_TRUE(RE2::FullMatchN("hello", RE2("hello"), nullptr, 0));
  EXPECT_FALSE(RE2::FullMatchN("world", RE2("hello"), nullptr, 0));
}
