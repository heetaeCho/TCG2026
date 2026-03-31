#include "re2/re2.h"

#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

namespace re2 {
namespace {

// ==================== Construction Tests ====================

TEST(RE2Test_596, ConstructFromString_596) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("hello", re.pattern());
}

TEST(RE2Test_596, ConstructFromCString_596) {
  RE2 re("world");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("world", re.pattern());
}

TEST(RE2Test_596, ConstructFromStringView_596) {
  absl::string_view sv("test pattern");
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("test pattern", re.pattern());
}

TEST(RE2Test_596, ConstructWithOptions_596) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("abc", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("abc", re.pattern());
}

TEST(RE2Test_596, InvalidPattern_596) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE("", re.error());
}

TEST(RE2Test_596, EmptyPattern_596) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("", re.pattern());
}

// ==================== FullMatch Tests ====================

TEST(RE2FullMatchTest_596, SimpleMatch_596) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2FullMatchTest_596, NoMatch_596) {
  EXPECT_FALSE(RE2::FullMatch("hello", "world"));
}

TEST(RE2FullMatchTest_596, PartialStringDoesNotFullMatch_596) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatchTest_596, WithCapture_596) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("42", "(\\d+)", &n));
  EXPECT_EQ(42, n);
}

TEST(RE2FullMatchTest_596, StringCapture_596) {
  std::string s;
  EXPECT_TRUE(RE2::FullMatch("test123", "(\\w+)", &s));
  EXPECT_EQ("test123", s);
}

TEST(RE2FullMatchTest_596, MultipleCaptures_596) {
  std::string a, b;
  EXPECT_TRUE(RE2::FullMatch("hello-world", "(\\w+)-(\\w+)", &a, &b));
  EXPECT_EQ("hello", a);
  EXPECT_EQ("world", b);
}

TEST(RE2FullMatchTest_596, EmptyStringEmptyPattern_596) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
}

TEST(RE2FullMatchTest_596, DotStar_596) {
  EXPECT_TRUE(RE2::FullMatch("anything goes", ".*"));
}

// ==================== PartialMatch Tests ====================

TEST(RE2PartialMatchTest_596, SimplePartialMatch_596) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "hello"));
}

TEST(RE2PartialMatchTest_596, PartialMatchMiddle_596) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "lo wo"));
}

TEST(RE2PartialMatchTest_596, NoPartialMatch_596) {
  EXPECT_FALSE(RE2::PartialMatch("hello", "xyz"));
}

TEST(RE2PartialMatchTest_596, WithCapture_596) {
  int n;
  EXPECT_TRUE(RE2::PartialMatch("value=42", "(\\d+)", &n));
  EXPECT_EQ(42, n);
}

TEST(RE2PartialMatchTest_596, EmptyPattern_596) {
  EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

// ==================== Consume Tests ====================

TEST(RE2ConsumeTest_596, ConsumeAdvancesInput_596) {
  absl::string_view input("abc123def456");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ("abc", word);
  // Input should now start at "123def456"
  EXPECT_EQ("123def456", input);
}

TEST(RE2ConsumeTest_596, ConsumeNoMatch_596) {
  absl::string_view input("123abc");
  std::string word;
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ("123abc", input);  // Input should be unchanged
}

TEST(RE2ConsumeTest_596, ConsumeMultipleTimes_596) {
  absl::string_view input("aaa bbb ccc");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "(\\w+)\\s*", &word));
  EXPECT_EQ("aaa", word);
  EXPECT_TRUE(RE2::Consume(&input, "(\\w+)\\s*", &word));
  EXPECT_EQ("bbb", word);
  EXPECT_TRUE(RE2::Consume(&input, "(\\w+)\\s*", &word));
  EXPECT_EQ("ccc", word);
}

// ==================== FindAndConsume Tests ====================

TEST(RE2FindAndConsumeTest_596, FindAndConsumeSkips_596) {
  absl::string_view input("abc 123 def 456");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(123, n);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(456, n);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

TEST(RE2FindAndConsumeTest_596, FindAndConsumeNoMatch_596) {
  absl::string_view input("no numbers here");
  int n;
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

// ==================== Replace Tests ====================

TEST(RE2ReplaceTest_596, SimpleReplace_596) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "world", "there"));
  EXPECT_EQ("hello there", s);
}

TEST(RE2ReplaceTest_596, ReplaceFirstOccurrence_596) {
  std::string s = "aaa bbb aaa";
  RE2::Replace(&s, "aaa", "ccc");
  EXPECT_EQ("ccc bbb aaa", s);
}

TEST(RE2ReplaceTest_596, ReplaceNoMatch_596) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ("hello world", s);
}

TEST(RE2ReplaceTest_596, ReplaceWithBackreference_596) {
  std::string s = "hello world";
  RE2::Replace(&s, "(\\w+)", "\\1!");
  EXPECT_EQ("hello! world", s);
}

// ==================== GlobalReplace Tests ====================

TEST(RE2GlobalReplaceTest_596, ReplaceAll_596) {
  std::string s = "aaa bbb aaa";
  int count = RE2::GlobalReplace(&s, "aaa", "ccc");
  EXPECT_EQ("ccc bbb ccc", s);
  EXPECT_EQ(2, count);
}

TEST(RE2GlobalReplaceTest_596, NoMatch_596) {
  std::string s = "hello world";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ("hello world", s);
  EXPECT_EQ(0, count);
}

TEST(RE2GlobalReplaceTest_596, ReplaceEmptyMatch_596) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "", "-");
  // Each position (including before first and after last char) gets replaced
  EXPECT_GE(count, 4);  // At least 4 positions: before a, before b, before c, after c
}

// ==================== Extract Tests ====================

TEST(RE2ExtractTest_596, SimpleExtract_596) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@example.com", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ("example!boris", out);
}

TEST(RE2ExtractTest_596, NoMatch_596) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no match", "(\\d+)", "\\1", &out));
}

// ==================== QuoteMeta Tests ====================

TEST(RE2QuoteMetaTest_596, NoSpecialChars_596) {
  EXPECT_EQ("hello", RE2::QuoteMeta("hello"));
}

TEST(RE2QuoteMetaTest_596, WithSpecialChars_596) {
  std::string quoted = RE2::QuoteMeta("a.b*c+d?e");
  // The result should be usable as a literal match
  EXPECT_TRUE(RE2::FullMatch("a.b*c+d?e", quoted));
}

TEST(RE2QuoteMetaTest_596, EmptyString_596) {
  EXPECT_EQ("", RE2::QuoteMeta(""));
}

TEST(RE2QuoteMetaTest_596, AllSpecialChars_596) {
  std::string input = "[](){}.*+?|^$\\";
  std::string quoted = RE2::QuoteMeta(input);
  EXPECT_TRUE(RE2::FullMatch(input, quoted));
}

// ==================== Match Tests ====================

TEST(RE2MatchTest_596, MatchAnchored_596) {
  RE2 re("(\\w+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("hello world", 0, 11, RE2::ANCHOR_START, submatch, 2));
  EXPECT_EQ("hello", submatch[0]);
  EXPECT_EQ("hello", submatch[1]);
}

TEST(RE2MatchTest_596, MatchUnanchored_596) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc 42 def", 0, 10, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ("42", submatch[0]);
  EXPECT_EQ("42", submatch[1]);
}

TEST(RE2MatchTest_596, MatchNoSubmatch_596) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("abc 42 def", 0, 10, RE2::UNANCHORED, nullptr, 0));
}

TEST(RE2MatchTest_596, MatchStartpos_596) {
  RE2 re("(\\w+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("hello world", 6, 11, RE2::ANCHOR_START, submatch, 2));
  EXPECT_EQ("world", submatch[0]);
}

TEST(RE2MatchTest_596, MatchBothAnchored_596) {
  RE2 re("hello world");
  EXPECT_TRUE(re.Match("hello world", 0, 11, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_FALSE(re.Match("hello world!", 0, 12, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_596, MatchNoResult_596) {
  RE2 re("xyz");
  EXPECT_FALSE(re.Match("hello world", 0, 11, RE2::UNANCHORED, nullptr, 0));
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST(RE2CapturingGroupsTest_596, NoGroups_596) {
  RE2 re("hello");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_596, OneGroup_596) {
  RE2 re("(hello)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_596, MultipleGroups_596) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_596, NestedGroups_596) {
  RE2 re("((a)(b))");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_596, NonCapturingGroup_596) {
  RE2 re("(?:a)(b)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

// ==================== NamedCapturingGroups Tests ====================

TEST(RE2NamedCapturingGroupsTest_596, NoNamedGroups_596) {
  RE2 re("(a)(b)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2NamedCapturingGroupsTest_596, WithNamedGroup_596) {
  RE2 re("(?P<name>\\w+) (?P<value>\\d+)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(2u, groups.size());
  EXPECT_EQ(1, groups.at("name"));
  EXPECT_EQ(2, groups.at("value"));
}

// ==================== CapturingGroupNames Tests ====================

TEST(RE2CapturingGroupNamesTest_596, WithNamedGroups_596) {
  RE2 re("(?P<first>\\w+)-(?P<second>\\w+)");
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(2u, names.size());
  EXPECT_EQ("first", names.at(1));
  EXPECT_EQ("second", names.at(2));
}

TEST(RE2CapturingGroupNamesTest_596, NoNamedGroups_596) {
  RE2 re("(a)(b)");
  const auto& names = re.CapturingGroupNames();
  EXPECT_TRUE(names.empty());
}

// ==================== ProgramSize Tests ====================

TEST(RE2ProgramSizeTest_596, BasicPattern_596) {
  RE2 re("hello");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_596, ComplexPattern_596) {
  RE2 simple("a");
  RE2 complex("(a|b|c|d|e)+");
  EXPECT_GT(complex.ProgramSize(), simple.ProgramSize());
}

// ==================== ReverseProgramSize Tests ====================

TEST(RE2ReverseProgramSizeTest_596, BasicPattern_596) {
  RE2 re("hello");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ==================== ProgramFanout Tests ====================

TEST(RE2ProgramFanoutTest_596, BasicTest_596) {
  RE2 re("hello");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ReverseProgramFanoutTest_596, BasicTest_596) {
  RE2 re("hello");
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ==================== PossibleMatchRange Tests ====================

TEST(RE2PossibleMatchRangeTest_596, BasicRange_596) {
  RE2 re("hello");
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "hello");
  EXPECT_GE(max, "hello");
}

TEST(RE2PossibleMatchRangeTest_596, MaxlenZero_596) {
  RE2 re("hello");
  std::string min, max;
  // maxlen of 0 should still work or return false
  re.PossibleMatchRange(&min, &max, 0);
}

// ==================== CheckRewriteString Tests ====================

TEST(RE2CheckRewriteStringTest_596, ValidRewrite_596) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewriteStringTest_596, InvalidRewriteTooManyBackrefs_596) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_NE("", error);
}

TEST(RE2CheckRewriteStringTest_596, NoCapturingGroups_596) {
  RE2 re("\\w+");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\1", &error));
}

// ==================== MaxSubmatch Tests ====================

TEST(RE2MaxSubmatchTest_596, NoBackreference_596) {
  EXPECT_EQ(0, RE2::MaxSubmatch("no backrefs"));
}

TEST(RE2MaxSubmatchTest_596, SingleBackreference_596) {
  EXPECT_EQ(1, RE2::MaxSubmatch("\\1"));
}

TEST(RE2MaxSubmatchTest_596, MultipleBackreferences_596) {
  EXPECT_EQ(3, RE2::MaxSubmatch("\\1 \\2 \\3"));
}

TEST(RE2MaxSubmatchTest_596, HigherBackreference_596) {
  EXPECT_EQ(9, RE2::MaxSubmatch("\\9"));
}

// ==================== Rewrite Tests ====================

TEST(RE2RewriteTest_596, SimpleRewrite_596) {
  RE2 re("(\\w+)-(\\w+)");
  std::string out;
  absl::string_view vec[] = {"hello-world", "hello", "world"};
  EXPECT_TRUE(re.Rewrite(&out, "\\2-\\1", vec, 3));
  EXPECT_EQ("world-hello", out);
}

TEST(RE2RewriteTest_596, RewriteWithLiteral_596) {
  RE2 re("(\\d+)");
  std::string out;
  absl::string_view vec[] = {"42", "42"};
  EXPECT_TRUE(re.Rewrite(&out, "value=\\1", vec, 2));
  EXPECT_EQ("value=42", out);
}

// ==================== ErrorCode Tests ====================

TEST(RE2ErrorTest_596, ValidPatternNoError_596) {
  RE2 re("hello");
  EXPECT_EQ(RE2::NoError, re.error_code());
  EXPECT_EQ("", re.error());
}

TEST(RE2ErrorTest_596, InvalidPatternHasError_596) {
  RE2 re("(unclosed");
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_NE("", re.error());
}

TEST(RE2ErrorTest_596, BadCharClass_596) {
  RE2 re("[z-a]");
  EXPECT_FALSE(re.ok());
}

// ==================== Options Tests ====================

TEST(RE2OptionsTest_596, CaseInsensitive_596) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2OptionsTest_596, CaseSensitiveDefault_596) {
  RE2 re("hello");
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2OptionsTest_596, Literal_596) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

// ==================== Type Capture Tests ====================

TEST(RE2TypeCaptureTest_596, CaptureInt_596) {
  int val;
  EXPECT_TRUE(RE2::FullMatch("42", "(\\d+)", &val));
  EXPECT_EQ(42, val);
}

TEST(RE2TypeCaptureTest_596, CaptureFloat_596) {
  float val;
  EXPECT_TRUE(RE2::FullMatch("3.14", "([\\d.]+)", &val));
  EXPECT_NEAR(3.14, val, 0.01);
}

TEST(RE2TypeCaptureTest_596, CaptureString_596) {
  std::string val;
  EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", &val));
  EXPECT_EQ("hello", val);
}

TEST(RE2TypeCaptureTest_596, CaptureStringView_596) {
  absl::string_view val;
  EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", &val));
  EXPECT_EQ("hello", val);
}

TEST(RE2TypeCaptureTest_596, HexCapture_596) {
  int val;
  EXPECT_TRUE(RE2::FullMatch("ff", "([0-9a-fA-F]+)", RE2::Hex(&val)));
  EXPECT_EQ(255, val);
}

TEST(RE2TypeCaptureTest_596, OctalCapture_596) {
  int val;
  EXPECT_TRUE(RE2::FullMatch("77", "([0-7]+)", RE2::Octal(&val)));
  EXPECT_EQ(63, val);
}

TEST(RE2TypeCaptureTest_596, CRadixHex_596) {
  int val;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(0x[0-9a-fA-F]+)", RE2::CRadix(&val)));
  EXPECT_EQ(31, val);
}

// ==================== Edge Cases ====================

TEST(RE2EdgeCaseTest_596, VeryLongString_596) {
  std::string long_string(10000, 'a');
  RE2 re("a+");
  EXPECT_TRUE(RE2::FullMatch(long_string, re));
}

TEST(RE2EdgeCaseTest_596, UnicodePattern_596) {
  RE2 re("\\p{L}+");
  EXPECT_TRUE(re.ok());
}

TEST(RE2EdgeCaseTest_596, NullInPattern_596) {
  // Patterns with null bytes
  std::string pattern("a\\x00b", 4);
  // Just ensure it doesn't crash
  RE2 re(pattern);
}

TEST(RE2EdgeCaseTest_596, MatchEmptyString_596) {
  RE2 re(".*");
  EXPECT_TRUE(RE2::FullMatch("", re));
}

TEST(RE2EdgeCaseTest_596, ReplaceEmptyString_596) {
  std::string s = "";
  RE2::Replace(&s, ".*", "replaced");
  EXPECT_EQ("replaced", s);
}

TEST(RE2EdgeCaseTest_596, GlobalReplaceNoChange_596) {
  std::string s = "no match here";
  int count = RE2::GlobalReplace(&s, "\\d+", "num");
  EXPECT_EQ(0, count);
  EXPECT_EQ("no match here", s);
}

// ==================== Alternation and Complex Patterns ====================

TEST(RE2ComplexPatternTest_596, Alternation_596) {
  RE2 re("cat|dog|fish");
  EXPECT_TRUE(RE2::FullMatch("cat", re));
  EXPECT_TRUE(RE2::FullMatch("dog", re));
  EXPECT_TRUE(RE2::FullMatch("fish", re));
  EXPECT_FALSE(RE2::FullMatch("bird", re));
}

TEST(RE2ComplexPatternTest_596, Repetition_596) {
  RE2 re("a{3,5}");
  EXPECT_FALSE(RE2::FullMatch("aa", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaaa", re));
  EXPECT_FALSE(RE2::FullMatch("aaaaaa", re));
}

TEST(RE2ComplexPatternTest_596, Anchors_596) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "^hello"));
  EXPECT_TRUE(RE2::PartialMatch("hello world", "world$"));
  EXPECT_FALSE(RE2::PartialMatch("hello world", "^world"));
}

}  // namespace
}  // namespace re2
