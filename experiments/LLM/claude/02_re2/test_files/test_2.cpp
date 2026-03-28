#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>

using namespace re2;

// ==================== Construction and Pattern Tests ====================

TEST(RE2Test_2, ConstructFromCString_2) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("hello", re.pattern());
}

TEST(RE2Test_2, ConstructFromStdString_2) {
  std::string pat = "world";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("world", re.pattern());
}

TEST(RE2Test_2, ConstructFromStringView_2) {
  absl::string_view sv = "test.*pattern";
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("test.*pattern", re.pattern());
}

TEST(RE2Test_2, InvalidPattern_2) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2Test_2, EmptyPattern_2) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("", re.pattern());
}

TEST(RE2Test_2, OptionsConstruction_2) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("Hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("Hello", re.pattern());
}

// ==================== FullMatch Tests ====================

TEST(RE2FullMatch_2, SimpleMatch_2) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2FullMatch_2, NoMatch_2) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatch_2, WithCapture_2) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("42", "(\\d+)", &n));
  EXPECT_EQ(42, n);
}

TEST(RE2FullMatch_2, MultipleCaptures_2) {
  std::string s1, s2;
  EXPECT_TRUE(RE2::FullMatch("abc-def", "(\\w+)-(\\w+)", &s1, &s2));
  EXPECT_EQ("abc", s1);
  EXPECT_EQ("def", s2);
}

TEST(RE2FullMatch_2, EmptyStringEmptyPattern_2) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
}

TEST(RE2FullMatch_2, EmptyStringNonEmptyPattern_2) {
  EXPECT_FALSE(RE2::FullMatch("", "a"));
}

TEST(RE2FullMatch_2, DotStar_2) {
  EXPECT_TRUE(RE2::FullMatch("anything goes", ".*"));
}

// ==================== PartialMatch Tests ====================

TEST(RE2PartialMatch_2, SimplePartial_2) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "hello"));
}

TEST(RE2PartialMatch_2, NoPartialMatch_2) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2PartialMatch_2, CaptureInMiddle_2) {
  int n;
  EXPECT_TRUE(RE2::PartialMatch("x = 42;", "(\\d+)", &n));
  EXPECT_EQ(42, n);
}

TEST(RE2PartialMatch_2, EmptyPattern_2) {
  EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

// ==================== Consume Tests ====================

TEST(RE2Consume_2, BasicConsume_2) {
  absl::string_view input("one123two456");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ("one", word);
  // input should have been advanced past "one"
  EXPECT_EQ("123two456", std::string(input));
}

TEST(RE2Consume_2, ConsumeNoMatch_2) {
  absl::string_view input("123abc");
  std::string word;
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &word));
  // input should be unchanged
  EXPECT_EQ("123abc", std::string(input));
}

// ==================== FindAndConsume Tests ====================

TEST(RE2FindAndConsume_2, BasicFindAndConsume_2) {
  absl::string_view input("one 2 three 4");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(2, n);
}

TEST(RE2FindAndConsume_2, MultipleFindAndConsume_2) {
  absl::string_view input("a1b2c3");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(1, n);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(2, n);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(3, n);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

// ==================== Replace Tests ====================

TEST(RE2Replace_2, SimpleReplace_2) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "world", "there"));
  EXPECT_EQ("hello there", s);
}

TEST(RE2Replace_2, ReplaceNoMatch_2) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ("hello world", s);
}

TEST(RE2Replace_2, ReplaceWithCapture_2) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "\\1!"));
  EXPECT_EQ("hello! world", s);
}

TEST(RE2Replace_2, ReplaceFirstOccurrenceOnly_2) {
  std::string s = "aaa";
  EXPECT_TRUE(RE2::Replace(&s, "a", "b"));
  EXPECT_EQ("baa", s);
}

// ==================== GlobalReplace Tests ====================

TEST(RE2GlobalReplace_2, ReplaceAll_2) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, "a", "b");
  EXPECT_EQ("bbb", s);
  EXPECT_EQ(3, count);
}

TEST(RE2GlobalReplace_2, NoMatchGlobalReplace_2) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ("hello", s);
  EXPECT_EQ(0, count);
}

TEST(RE2GlobalReplace_2, GlobalReplaceWithCapture_2) {
  std::string s = "abc def ghi";
  int count = RE2::GlobalReplace(&s, "(\\w+)", "[\\1]");
  EXPECT_EQ("[abc] [def] [ghi]", s);
  EXPECT_EQ(3, count);
}

// ==================== Extract Tests ====================

TEST(RE2Extract_2, SimpleExtract_2) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ("kremlin!boris", out);
}

TEST(RE2Extract_2, ExtractNoMatch_2) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no match here", "(\\d+)@(\\d+)", "\\1-\\2", &out));
}

// ==================== QuoteMeta Tests ====================

TEST(RE2QuoteMeta_2, SimpleQuote_2) {
  std::string quoted = RE2::QuoteMeta("hello.world");
  // The quoted version should escape the dot
  EXPECT_TRUE(RE2::FullMatch("hello.world", quoted));
  EXPECT_FALSE(RE2::FullMatch("helloXworld", quoted));
}

TEST(RE2QuoteMeta_2, SpecialCharacters_2) {
  std::string special = "a+b*c?d[e]f(g)h{i}j|k^l$m.n\\o";
  std::string quoted = RE2::QuoteMeta(special);
  EXPECT_TRUE(RE2::FullMatch(special, quoted));
}

TEST(RE2QuoteMeta_2, EmptyString_2) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ("", quoted);
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST(RE2CapturingGroups_2, NoGroups_2) {
  RE2 re("hello");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroups_2, OneGroup_2) {
  RE2 re("(hello)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroups_2, MultipleGroups_2) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroups_2, NestedGroups_2) {
  RE2 re("((a)(b))");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroups_2, NonCapturingGroup_2) {
  RE2 re("(?:abc)(def)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

// ==================== NamedCapturingGroups Tests ====================

TEST(RE2NamedCapturingGroups_2, NoNamedGroups_2) {
  RE2 re("(a)(b)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2NamedCapturingGroups_2, WithNamedGroups_2) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(2u, groups.size());
  EXPECT_EQ(1, groups.at("first"));
  EXPECT_EQ(2, groups.at("second"));
}

// ==================== CapturingGroupNames Tests ====================

TEST(RE2CapturingGroupNames_2, WithNamedGroups_2) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(2u, names.size());
  EXPECT_EQ("first", names.at(1));
  EXPECT_EQ("second", names.at(2));
}

// ==================== Match Tests ====================

TEST(RE2Match_2, BasicMatch_2) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("abc 123 def", 0, 11, RE2::UNANCHORED, nullptr, 0));
}

TEST(RE2Match_2, AnchoredStart_2) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("abc 123", 0, 7, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_TRUE(re.Match("123 abc", 0, 7, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2Match_2, AnchoredBoth_2) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("123 abc", 0, 7, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2Match_2, SubmatchExtraction_2) {
  RE2 re("(\\w+)@(\\w+)");
  absl::string_view submatch[3];
  EXPECT_TRUE(re.Match("test@host", 0, 9, RE2::ANCHOR_BOTH, submatch, 3));
  EXPECT_EQ("test@host", submatch[0]);
  EXPECT_EQ("test", submatch[1]);
  EXPECT_EQ("host", submatch[2]);
}

TEST(RE2Match_2, StartposEndpos_2) {
  RE2 re("\\d+");
  absl::string_view text = "abc123def";
  // Match only within the substring starting at position 3
  EXPECT_TRUE(re.Match(text, 3, 6, RE2::UNANCHORED, nullptr, 0));
  EXPECT_FALSE(re.Match(text, 0, 3, RE2::UNANCHORED, nullptr, 0));
}

// ==================== ProgramSize Tests ====================

TEST(RE2ProgramSize_2, PositiveSize_2) {
  RE2 re("a+b+c+");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSize_2, ReverseProgramSize_2) {
  RE2 re("a+b+c+");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ==================== ProgramFanout Tests ====================

TEST(RE2ProgramFanout_2, VectorFanout_2) {
  RE2 re("a+b+");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ProgramFanout_2, ReverseFanout_2) {
  RE2 re("a+b+");
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ==================== PossibleMatchRange Tests ====================

TEST(RE2PossibleMatchRange_2, BasicRange_2) {
  RE2 re("abc.*");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "abc");
}

TEST(RE2PossibleMatchRange_2, InvalidRegex_2) {
  RE2 re("(bad");
  std::string min_str, max_str;
  // Invalid regex; PossibleMatchRange behavior
  EXPECT_FALSE(re.PossibleMatchRange(&min_str, &max_str, 10));
}

// ==================== CheckRewriteString Tests ====================

TEST(RE2CheckRewrite_2, ValidRewrite_2) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewrite_2, InvalidRewriteTooManyBackrefs_2) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ==================== MaxSubmatch Tests ====================

TEST(RE2MaxSubmatch_2, NoBackref_2) {
  EXPECT_EQ(0, RE2::MaxSubmatch("no backrefs here"));
}

TEST(RE2MaxSubmatch_2, SingleBackref_2) {
  EXPECT_EQ(1, RE2::MaxSubmatch("\\1"));
}

TEST(RE2MaxSubmatch_2, MultipleBackrefs_2) {
  EXPECT_EQ(3, RE2::MaxSubmatch("\\1 \\2 \\3"));
}

TEST(RE2MaxSubmatch_2, NonSequentialBackrefs_2) {
  EXPECT_EQ(5, RE2::MaxSubmatch("\\5 \\1"));
}

// ==================== Rewrite Tests ====================

TEST(RE2Rewrite_2, BasicRewrite_2) {
  RE2 re("(\\w+)-(\\w+)");
  absl::string_view vec[3];
  vec[0] = absl::string_view("abc-def");
  vec[1] = absl::string_view("abc");
  vec[2] = absl::string_view("def");
  std::string out;
  EXPECT_TRUE(re.Rewrite(&out, "\\2-\\1", vec, 3));
  EXPECT_EQ("def-abc", out);
}

// ==================== CRadix / Hex / Octal Tests ====================

TEST(RE2Parsers_2, HexParsing_2) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("0xff", "0x([0-9a-fA-F]+)", RE2::Hex(&n)));
  EXPECT_EQ(255, n);
}

TEST(RE2Parsers_2, OctalParsing_2) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("77", "(\\d+)", RE2::Octal(&n)));
  EXPECT_EQ(63, n);  // 77 in octal = 63 in decimal
}

TEST(RE2Parsers_2, CRadixHex_2) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(0x[0-9a-fA-F]+)", RE2::CRadix(&n)));
  EXPECT_EQ(31, n);
}

TEST(RE2Parsers_2, CRadixOctal_2) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("010", "(0[0-7]+)", RE2::CRadix(&n)));
  EXPECT_EQ(8, n);
}

TEST(RE2Parsers_2, CRadixDecimal_2) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("42", "(\\d+)", RE2::CRadix(&n)));
  EXPECT_EQ(42, n);
}

// ==================== Error Tests ====================

TEST(RE2Error_2, ErrorCodeOnInvalid_2) {
  RE2 re("[invalid");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
}

TEST(RE2Error_2, NoErrorOnValid_2) {
  RE2 re("valid");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(RE2::NoError, re.error_code());
}

TEST(RE2Error_2, ErrorStringNonEmpty_2) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(re.error().empty());
}

// ==================== Options Tests ====================

TEST(RE2Options_2, CaseInsensitive_2) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HeLlO", re));
}

TEST(RE2Options_2, OptionsAccessor_2) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("test", opts);
  EXPECT_FALSE(re.options().case_sensitive());
}

// ==================== Edge Cases ====================

TEST(RE2EdgeCases_2, LargeInput_2) {
  std::string large_str(10000, 'a');
  EXPECT_TRUE(RE2::FullMatch(large_str, "a+"));
}

TEST(RE2EdgeCases_2, ComplexPattern_2) {
  RE2 re("(a|b)*c(d|e)+f?");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abcdef", re));
  EXPECT_TRUE(RE2::FullMatch("cd", re));
  EXPECT_FALSE(RE2::FullMatch("abc", re));
}

TEST(RE2EdgeCases_2, UnicodePattern_2) {
  RE2 re("\\p{L}+");
  EXPECT_TRUE(re.ok());
}

TEST(RE2EdgeCases_2, FullMatchNWithNullArgs_2) {
  RE2 re("hello");
  EXPECT_TRUE(RE2::FullMatchN("hello", re, nullptr, 0));
  EXPECT_FALSE(RE2::FullMatchN("world", re, nullptr, 0));
}

TEST(RE2EdgeCases_2, PartialMatchNWithNullArgs_2) {
  RE2 re("hello");
  EXPECT_TRUE(RE2::PartialMatchN("say hello world", re, nullptr, 0));
  EXPECT_FALSE(RE2::PartialMatchN("say world", re, nullptr, 0));
}

TEST(RE2EdgeCases_2, ConsumeNWithNullArgs_2) {
  RE2 re("\\d+");
  absl::string_view input("123abc");
  EXPECT_TRUE(RE2::ConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ("abc", std::string(input));
}

TEST(RE2EdgeCases_2, FindAndConsumeNWithNullArgs_2) {
  RE2 re("\\d+");
  absl::string_view input("abc123def");
  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ("def", std::string(input));
}

// ==================== Replace with empty pattern ====================

TEST(RE2Replace_2, ReplaceWithEmptyMatch_2) {
  std::string s = "abc";
  RE2::Replace(&s, "", "X");
  // Empty pattern matches at the beginning
  EXPECT_EQ("Xabc", s);
}

TEST(RE2GlobalReplace_2, GlobalReplaceEmptyString_2) {
  std::string s = "";
  int count = RE2::GlobalReplace(&s, ".*", "X");
  EXPECT_GE(count, 1);
}
