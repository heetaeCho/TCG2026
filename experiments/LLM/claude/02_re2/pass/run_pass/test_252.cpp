#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>
#include "re2/re2.h"

namespace {

// ==================== FullMatch Tests ====================

TEST(RE2FullMatchTest_252, SimpleMatch_252) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2FullMatchTest_252, SimpleNoMatch_252) {
  EXPECT_FALSE(RE2::FullMatch("hello", "world"));
}

TEST(RE2FullMatchTest_252, EmptyPatternEmptyText_252) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
}

TEST(RE2FullMatchTest_252, EmptyPatternNonEmptyText_252) {
  EXPECT_FALSE(RE2::FullMatch("hello", ""));
}

TEST(RE2FullMatchTest_252, EmptyTextNonEmptyPattern_252) {
  EXPECT_FALSE(RE2::FullMatch("", "hello"));
}

TEST(RE2FullMatchTest_252, FullMatchRequiresEntireString_252) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatchTest_252, FullMatchWithDotStar_252) {
  EXPECT_TRUE(RE2::FullMatch("hello world", "hello.*"));
}

TEST(RE2FullMatchTest_252, CaptureGroup_252) {
  std::string captured;
  EXPECT_TRUE(RE2::FullMatch("hello123", "(\\w+)", &captured));
  EXPECT_EQ(captured, "hello123");
}

TEST(RE2FullMatchTest_252, CaptureInteger_252) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("42", "(\\d+)", &value));
  EXPECT_EQ(value, 42);
}

TEST(RE2FullMatchTest_252, CaptureMultipleGroups_252) {
  std::string s1, s2;
  EXPECT_TRUE(RE2::FullMatch("hello-world", "(\\w+)-(\\w+)", &s1, &s2));
  EXPECT_EQ(s1, "hello");
  EXPECT_EQ(s2, "world");
}

TEST(RE2FullMatchTest_252, FullMatchNWithNoArgs_252) {
  RE2 re("hello");
  EXPECT_TRUE(RE2::FullMatchN("hello", re, nullptr, 0));
  EXPECT_FALSE(RE2::FullMatchN("world", re, nullptr, 0));
}

TEST(RE2FullMatchTest_252, FullMatchNWithArgs_252) {
  RE2 re("(\\d+)");
  int value;
  RE2::Arg arg(&value);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::FullMatchN("123", re, args, 1));
  EXPECT_EQ(value, 123);
}

// ==================== PartialMatch Tests ====================

TEST(RE2PartialMatchTest_252, SimplePartialMatch_252) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "hello"));
}

TEST(RE2PartialMatchTest_252, PartialMatchInMiddle_252) {
  EXPECT_TRUE(RE2::PartialMatch("say hello world", "hello"));
}

TEST(RE2PartialMatchTest_252, PartialMatchNoMatch_252) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2PartialMatchTest_252, PartialMatchEmptyPattern_252) {
  EXPECT_TRUE(RE2::PartialMatch("hello", ""));
}

TEST(RE2PartialMatchTest_252, PartialMatchCapture_252) {
  int value;
  EXPECT_TRUE(RE2::PartialMatch("age: 25 years", "(\\d+)", &value));
  EXPECT_EQ(value, 25);
}

TEST(RE2PartialMatchTest_252, PartialMatchNWithNoArgs_252) {
  RE2 re("world");
  EXPECT_TRUE(RE2::PartialMatchN("hello world", re, nullptr, 0));
  EXPECT_FALSE(RE2::PartialMatchN("hello", re, nullptr, 0));
}

// ==================== Consume Tests ====================

TEST(RE2ConsumeTest_252, ConsumeBasic_252) {
  absl::string_view input("one two three");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "(\\w+)", &word));
  EXPECT_EQ(word, "one");
}

TEST(RE2ConsumeTest_252, ConsumeMultiple_252) {
  absl::string_view input("123 456 789");
  int value;
  EXPECT_TRUE(RE2::Consume(&input, "(\\d+)", &value));
  EXPECT_EQ(value, 123);
  // After consuming "123", the remaining should start with " 456 789"
}

TEST(RE2ConsumeTest_252, ConsumeNoMatch_252) {
  absl::string_view input("hello");
  int value;
  EXPECT_FALSE(RE2::Consume(&input, "(\\d+)", &value));
}

TEST(RE2ConsumeTest_252, ConsumeNWithNoArgs_252) {
  RE2 re("\\w+");
  absl::string_view input("hello world");
  EXPECT_TRUE(RE2::ConsumeN(&input, re, nullptr, 0));
}

// ==================== FindAndConsume Tests ====================

TEST(RE2FindAndConsumeTest_252, FindAndConsumeBasic_252) {
  absl::string_view input("foo = 123; bar = 456;");
  int value;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &value));
  EXPECT_EQ(value, 123);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &value));
  EXPECT_EQ(value, 456);
}

TEST(RE2FindAndConsumeTest_252, FindAndConsumeNoMatch_252) {
  absl::string_view input("no numbers here");
  int value;
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &value));
}

// ==================== Replace Tests ====================

TEST(RE2ReplaceTest_252, ReplaceSimple_252) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "world", "there"));
  EXPECT_EQ(s, "hello there");
}

TEST(RE2ReplaceTest_252, ReplaceNoMatch_252) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ(s, "hello world");
}

TEST(RE2ReplaceTest_252, ReplaceFirstOccurrenceOnly_252) {
  std::string s = "aaa";
  EXPECT_TRUE(RE2::Replace(&s, "a", "b"));
  EXPECT_EQ(s, "baa");
}

TEST(RE2ReplaceTest_252, ReplaceWithBackreference_252) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "[\\1]"));
  EXPECT_EQ(s, "[hello] world");
}

// ==================== GlobalReplace Tests ====================

TEST(RE2GlobalReplaceTest_252, GlobalReplaceAll_252) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, "a", "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "bbb");
}

TEST(RE2GlobalReplaceTest_252, GlobalReplaceNone_252) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "x", "y");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello");
}

TEST(RE2GlobalReplaceTest_252, GlobalReplaceMultipleOccurrences_252) {
  std::string s = "the cat sat on the mat";
  int count = RE2::GlobalReplace(&s, "the", "a");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(s, "a cat sat on a mat");
}

// ==================== Extract Tests ====================

TEST(RE2ExtractTest_252, ExtractSimple_252) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST(RE2ExtractTest_252, ExtractNoMatch_252) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-at-sign", "(.*)@([^.]*)", "\\2!\\1", &out));
}

// ==================== QuoteMeta Tests ====================

TEST(RE2QuoteMetaTest_252, QuoteMetaSpecialChars_252) {
  std::string quoted = RE2::QuoteMeta("hello.world");
  // The quoted version should match literally
  EXPECT_TRUE(RE2::FullMatch("hello.world", quoted));
  EXPECT_FALSE(RE2::FullMatch("helloXworld", quoted));
}

TEST(RE2QuoteMetaTest_252, QuoteMetaEmpty_252) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

TEST(RE2QuoteMetaTest_252, QuoteMetaBrackets_252) {
  std::string quoted = RE2::QuoteMeta("[test]");
  EXPECT_TRUE(RE2::FullMatch("[test]", quoted));
}

TEST(RE2QuoteMetaTest_252, QuoteMetaParens_252) {
  std::string quoted = RE2::QuoteMeta("(abc)");
  EXPECT_TRUE(RE2::FullMatch("(abc)", quoted));
}

// ==================== RE2 Construction Tests ====================

TEST(RE2ConstructionTest_252, ValidPattern_252) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "hello");
}

TEST(RE2ConstructionTest_252, InvalidPattern_252) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error_code(), RE2::NoError);
}

TEST(RE2ConstructionTest_252, PatternFromCString_252) {
  RE2 re("test.*");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "test.*");
}

TEST(RE2ConstructionTest_252, PatternFromStdString_252) {
  std::string pat = "\\d+";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "\\d+");
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST(RE2CapturingGroupsTest_252, NoGroups_252) {
  RE2 re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2CapturingGroupsTest_252, OneGroup_252) {
  RE2 re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(RE2CapturingGroupsTest_252, MultipleGroups_252) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2CapturingGroupsTest_252, NestedGroups_252) {
  RE2 re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2CapturingGroupsTest_252, NonCapturingGroup_252) {
  RE2 re("(?:hello)(world)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

// ==================== NamedCapturingGroups Tests ====================

TEST(RE2NamedCapturingGroupsTest_252, NoNamedGroups_252) {
  RE2 re("(hello)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2NamedCapturingGroupsTest_252, NamedGroup_252) {
  RE2 re("(?P<name>\\w+)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 1u);
  auto it = groups.find("name");
  EXPECT_NE(it, groups.end());
  EXPECT_EQ(it->second, 1);
}

TEST(RE2NamedCapturingGroupsTest_252, MultipleNamedGroups_252) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 2u);
  EXPECT_EQ(groups.at("first"), 1);
  EXPECT_EQ(groups.at("second"), 2);
}

// ==================== CapturingGroupNames Tests ====================

TEST(RE2CapturingGroupNamesTest_252, NamedGroupReverse_252) {
  RE2 re("(?P<name>\\w+)");
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 1u);
  auto it = names.find(1);
  EXPECT_NE(it, names.end());
  EXPECT_EQ(it->second, "name");
}

// ==================== Match Tests ====================

TEST(RE2MatchTest_252, MatchAnchored_252) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_FALSE(re.Match("abc", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_252, MatchAnchorStart_252) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_FALSE(re.Match("abc123", 0, 6, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_252, MatchUnanchored_252) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, nullptr, 0));
  EXPECT_FALSE(re.Match("abcdef", 0, 6, RE2::UNANCHORED, nullptr, 0));
}

TEST(RE2MatchTest_252, MatchWithSubmatch_252) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ(submatch[0], "123");
  EXPECT_EQ(submatch[1], "123");
}

TEST(RE2MatchTest_252, MatchWithStartPos_252) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("abc123", 3, 6, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_252, MatchEmptyRange_252) {
  RE2 re(".*");
  EXPECT_TRUE(re.Match("hello", 0, 0, RE2::ANCHOR_BOTH, nullptr, 0));
}

// ==================== PossibleMatchRange Tests ====================

TEST(RE2PossibleMatchRangeTest_252, BasicRange_252) {
  RE2 re("hello");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "hello");
  EXPECT_GE(max_str, "hello");
}

// ==================== CheckRewriteString Tests ====================

TEST(RE2CheckRewriteStringTest_252, ValidRewrite_252) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewriteStringTest_252, InvalidRewriteTooManyGroups_252) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
}

// ==================== MaxSubmatch Tests ====================

TEST(RE2MaxSubmatchTest_252, NoSubmatch_252) {
  EXPECT_EQ(RE2::MaxSubmatch("no backrefs"), 0);
}

TEST(RE2MaxSubmatchTest_252, SingleSubmatch_252) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
}

TEST(RE2MaxSubmatchTest_252, MultipleSubmatch_252) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1 and \\3"), 3);
}

// ==================== ProgramSize Tests ====================

TEST(RE2ProgramSizeTest_252, ProgramSizePositive_252) {
  RE2 re("hello");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_252, ReverseProgramSizePositive_252) {
  RE2 re("hello");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ==================== Arg Tests ====================

TEST(RE2ArgTest_252, ArgParseInt_252) {
  int value = 0;
  RE2::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("42", 2));
  EXPECT_EQ(value, 42);
}

TEST(RE2ArgTest_252, ArgParseString_252) {
  std::string value;
  RE2::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("hello", 5));
  EXPECT_EQ(value, "hello");
}

TEST(RE2ArgTest_252, ArgNull_252) {
  RE2::Arg arg(nullptr);
  EXPECT_TRUE(arg.Parse("anything", 8));
}

// ==================== Hex and Octal Tests ====================

TEST(RE2HexTest_252, HexCapture_252) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("ff", "([0-9a-fA-F]+)", RE2::Hex(&value)));
  EXPECT_EQ(value, 255);
}

TEST(RE2OctalTest_252, OctalCapture_252) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("77", "([0-7]+)", RE2::Octal(&value)));
  EXPECT_EQ(value, 63);
}

TEST(RE2CRadixTest_252, CRadixHex_252) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("0xff", "(.*)", RE2::CRadix(&value)));
  EXPECT_EQ(value, 255);
}

TEST(RE2CRadixTest_252, CRadixOctal_252) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("077", "(.*)", RE2::CRadix(&value)));
  EXPECT_EQ(value, 63);
}

TEST(RE2CRadixTest_252, CRadixDecimal_252) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("42", "(.*)", RE2::CRadix(&value)));
  EXPECT_EQ(value, 42);
}

// ==================== Rewrite Tests ====================

TEST(RE2RewriteTest_252, RewriteBasic_252) {
  RE2 re("(\\w+) (\\w+)");
  std::string out;
  absl::string_view vec[3] = {"hello world", "hello", "world"};
  EXPECT_TRUE(re.Rewrite(&out, "\\2 \\1", vec, 3));
  EXPECT_EQ(out, "world hello");
}

// ==================== Error Cases ====================

TEST(RE2ErrorTest_252, ErrorCodeOnBadPattern_252) {
  RE2 re("[");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error().size(), 0u);
  EXPECT_NE(re.error_code(), RE2::NoError);
}

TEST(RE2ErrorTest_252, ErrorArgOnBadPattern_252) {
  RE2 re("(abc");
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(re.error().empty());
}

// ==================== Boundary Cases ====================

TEST(RE2BoundaryTest_252, VeryLongString_252) {
  std::string long_str(10000, 'a');
  EXPECT_TRUE(RE2::FullMatch(long_str, "a+"));
}

TEST(RE2BoundaryTest_252, UnicodePattern_252) {
  EXPECT_TRUE(RE2::FullMatch("café", "caf."));
}

TEST(RE2BoundaryTest_252, SpecialCharsInText_252) {
  std::string quoted = RE2::QuoteMeta("^$.|?*+()[]{}\\");
  EXPECT_TRUE(RE2::FullMatch("^$.|?*+()[]{}\\", quoted));
}

TEST(RE2BoundaryTest_252, NullCharInText_252) {
  std::string text("a\0b", 3);
  RE2 re("a.b");
  RE2::Options opt;
  opt.set_dot_nl(true);
  RE2 re2("a.b", opt);
  // The null char should be matched by dot with dot_nl
  EXPECT_TRUE(RE2::FullMatch(text, re2));
}

// ==================== Options Tests ====================

TEST(RE2OptionsTest_252, CaseSensitiveByDefault_252) {
  EXPECT_FALSE(RE2::FullMatch("HELLO", "hello"));
}

TEST(RE2OptionsTest_252, CaseInsensitive_252) {
  RE2::Options opt;
  opt.set_case_sensitive(false);
  RE2 re("hello", opt);
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
}

TEST(RE2OptionsTest_252, DotMatchesNewline_252) {
  RE2::Options opt;
  opt.set_dot_nl(true);
  RE2 re("a.b", opt);
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST(RE2OptionsTest_252, DotDoesNotMatchNewlineByDefault_252) {
  RE2 re("a.b");
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

// ==================== ProgramFanout Tests ====================

TEST(RE2ProgramFanoutTest_252, ProgramFanoutBasic_252) {
  RE2 re("hello");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ProgramFanoutTest_252, ReverseProgramFanoutBasic_252) {
  RE2 re("hello");
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

}  // namespace
