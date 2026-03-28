#include "gtest/gtest.h"
#include "re2/re2.h"
#include <string>
#include <vector>
#include <map>

namespace re2 {

// =============================================================================
// ProgramSize Tests
// =============================================================================

TEST(RE2ProgramSizeTest_244, SimplePattern_244) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_244, EmptyPattern_244) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_244, ComplexPattern_244) {
  RE2 re("(a|b)*c+[d-f]{2,5}");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_244, InvalidPattern_244) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.ProgramSize(), -1);
}

TEST(RE2ProgramSizeTest_244, SingleCharPattern_244) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_244, DotStarPattern_244) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_244, LargerPatternHasLargerOrEqualSize_244) {
  RE2 re_small("a");
  RE2 re_large("abcdefghijklmnop");
  ASSERT_TRUE(re_small.ok());
  ASSERT_TRUE(re_large.ok());
  EXPECT_GE(re_large.ProgramSize(), re_small.ProgramSize());
}

// =============================================================================
// ReverseProgramSize Tests
// =============================================================================

TEST(RE2ReverseProgramSizeTest_244, SimplePattern_244) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

TEST(RE2ReverseProgramSizeTest_244, InvalidPattern_244) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.ReverseProgramSize(), -1);
}

// =============================================================================
// ok() / pattern() / error() Tests
// =============================================================================

TEST(RE2BasicTest_244, OkForValidPattern_244) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
}

TEST(RE2BasicTest_244, NotOkForInvalidPattern_244) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
}

TEST(RE2BasicTest_244, PatternReturnsOriginal_244) {
  RE2 re("hello.*world");
  EXPECT_EQ(re.pattern(), "hello.*world");
}

TEST(RE2BasicTest_244, ErrorEmptyForValid_244) {
  RE2 re("abc");
  EXPECT_TRUE(re.error().empty());
}

TEST(RE2BasicTest_244, ErrorNonEmptyForInvalid_244) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2BasicTest_244, ErrorCodeNoError_244) {
  RE2 re("abc");
  EXPECT_EQ(re.error_code(), RE2::NoError);
}

TEST(RE2BasicTest_244, ErrorCodeForInvalid_244) {
  RE2 re("(unclosed");
  EXPECT_NE(re.error_code(), RE2::NoError);
}

// =============================================================================
// FullMatch Tests
// =============================================================================

TEST(RE2FullMatchTest_244, SimpleMatch_244) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2FullMatchTest_244, SimpleNoMatch_244) {
  EXPECT_FALSE(RE2::FullMatch("hello", "world"));
}

TEST(RE2FullMatchTest_244, PartialStringDoesNotFullMatch_244) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatchTest_244, RegexMatch_244) {
  EXPECT_TRUE(RE2::FullMatch("abc123", "[a-z]+[0-9]+"));
}

TEST(RE2FullMatchTest_244, EmptyPatternMatchesEmpty_244) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
}

TEST(RE2FullMatchTest_244, EmptyPatternDoesNotMatchNonEmpty_244) {
  EXPECT_FALSE(RE2::FullMatch("abc", ""));
}

TEST(RE2FullMatchTest_244, CaptureGroup_244) {
  std::string captured;
  EXPECT_TRUE(RE2::FullMatch("hello123", "(\\w+)", &captured));
  EXPECT_EQ(captured, "hello123");
}

TEST(RE2FullMatchTest_244, CaptureInt_244) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &n));
  EXPECT_EQ(n, 12345);
}

// =============================================================================
// PartialMatch Tests
// =============================================================================

TEST(RE2PartialMatchTest_244, SimpleMatch_244) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "hello"));
}

TEST(RE2PartialMatchTest_244, NoMatch_244) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2PartialMatchTest_244, MatchInMiddle_244) {
  EXPECT_TRUE(RE2::PartialMatch("abc123def", "\\d+"));
}

TEST(RE2PartialMatchTest_244, CaptureFromPartial_244) {
  std::string captured;
  EXPECT_TRUE(RE2::PartialMatch("abc123def", "(\\d+)", &captured));
  EXPECT_EQ(captured, "123");
}

// =============================================================================
// Consume Tests
// =============================================================================

TEST(RE2ConsumeTest_244, ConsumeFromBeginning_244) {
  absl::string_view input("abc123def");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ(word, "abc");
  EXPECT_EQ(input, "123def");
}

TEST(RE2ConsumeTest_244, ConsumeNoMatch_244) {
  absl::string_view input("123abc");
  std::string word;
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &word));
}

// =============================================================================
// FindAndConsume Tests
// =============================================================================

TEST(RE2FindAndConsumeTest_244, FindAndConsumeDigits_244) {
  absl::string_view input("abc123def456");
  std::string digits;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &digits));
  EXPECT_EQ(digits, "123");
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &digits));
  EXPECT_EQ(digits, "456");
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &digits));
}

// =============================================================================
// Replace Tests
// =============================================================================

TEST(RE2ReplaceTest_244, SimpleReplace_244) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "world", "there"));
  EXPECT_EQ(s, "hello there");
}

TEST(RE2ReplaceTest_244, NoMatch_244) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "there"));
  EXPECT_EQ(s, "hello world");
}

TEST(RE2ReplaceTest_244, ReplaceFirstOnly_244) {
  std::string s = "aaa";
  RE2::Replace(&s, "a", "b");
  EXPECT_EQ(s, "baa");
}

// =============================================================================
// GlobalReplace Tests
// =============================================================================

TEST(RE2GlobalReplaceTest_244, ReplaceAll_244) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, "a", "b");
  EXPECT_EQ(s, "bbb");
  EXPECT_EQ(count, 3);
}

TEST(RE2GlobalReplaceTest_244, NoMatchReturnsZero_244) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, "x", "b");
  EXPECT_EQ(s, "aaa");
  EXPECT_EQ(count, 0);
}

TEST(RE2GlobalReplaceTest_244, EmptyString_244) {
  std::string s = "";
  int count = RE2::GlobalReplace(&s, "a", "b");
  EXPECT_EQ(count, 0);
}

// =============================================================================
// Extract Tests
// =============================================================================

TEST(RE2ExtractTest_244, SimpleExtract_244) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST(RE2ExtractTest_244, NoMatch_244) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-at-sign", "(.*)@(.*)", "\\1", &out));
}

// =============================================================================
// QuoteMeta Tests
// =============================================================================

TEST(RE2QuoteMetaTest_244, NoSpecialChars_244) {
  EXPECT_EQ(RE2::QuoteMeta("hello"), "hello");
}

TEST(RE2QuoteMetaTest_244, SpecialChars_244) {
  std::string quoted = RE2::QuoteMeta("a.b+c*d");
  RE2 re(quoted);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a.b+c*d", re));
  EXPECT_FALSE(RE2::FullMatch("aXbXcXd", re));
}

TEST(RE2QuoteMetaTest_244, EmptyString_244) {
  EXPECT_EQ(RE2::QuoteMeta(""), "");
}

// =============================================================================
// NumberOfCapturingGroups Tests
// =============================================================================

TEST(RE2CapturingGroupsTest_244, NoGroups_244) {
  RE2 re("abc");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2CapturingGroupsTest_244, OneGroup_244) {
  RE2 re("(abc)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(RE2CapturingGroupsTest_244, MultipleGroups_244) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2CapturingGroupsTest_244, NestedGroups_244) {
  RE2 re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2CapturingGroupsTest_244, NonCapturingGroup_244) {
  RE2 re("(?:abc)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

// =============================================================================
// NamedCapturingGroups Tests
// =============================================================================

TEST(RE2NamedCapturingGroupsTest_244, NoNamedGroups_244) {
  RE2 re("(abc)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2NamedCapturingGroupsTest_244, OneNamedGroup_244) {
  RE2 re("(?P<name>\\w+)");
  ASSERT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 1u);
  auto it = groups.find("name");
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, 1);
}

// =============================================================================
// CapturingGroupNames Tests
// =============================================================================

TEST(RE2CapturingGroupNamesTest_244, OneNamedGroup_244) {
  RE2 re("(?P<name>\\w+)");
  ASSERT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 1u);
  auto it = names.find(1);
  ASSERT_NE(it, names.end());
  EXPECT_EQ(it->second, "name");
}

// =============================================================================
// Match Tests
// =============================================================================

TEST(RE2MatchTest_244, SimpleMatch_244) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, nullptr, 0));
}

TEST(RE2MatchTest_244, NoMatch_244) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(re.Match("abcdef", 0, 6, RE2::UNANCHORED, nullptr, 0));
}

TEST(RE2MatchTest_244, AnchorStart_244) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(re.Match("abc123", 0, 6, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_244, AnchorBoth_244) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_FALSE(re.Match("123abc", 0, 6, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_244, SubmatchCapture_244) {
  RE2 re("(\\d+)");
  ASSERT_TRUE(re.ok());
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ(submatch[0], "123");
  EXPECT_EQ(submatch[1], "123");
}

TEST(RE2MatchTest_244, StartEndPos_244) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  // Search only within "abc" portion - no digits
  EXPECT_FALSE(re.Match("abc123", 0, 3, RE2::UNANCHORED, nullptr, 0));
  // Search within "123" portion
  EXPECT_TRUE(re.Match("abc123", 3, 6, RE2::UNANCHORED, nullptr, 0));
}

// =============================================================================
// PossibleMatchRange Tests
// =============================================================================

TEST(RE2PossibleMatchRangeTest_244, SimplePattern_244) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "hello");
  EXPECT_GE(max_str, "hello");
}

// =============================================================================
// CheckRewriteString Tests
// =============================================================================

TEST(RE2CheckRewriteStringTest_244, ValidRewrite_244) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewriteStringTest_244, InvalidRewriteBackref_244) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  std::string error;
  // \2 is invalid since there's only one capture group
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// =============================================================================
// MaxSubmatch Tests
// =============================================================================

TEST(RE2MaxSubmatchTest_244, NoBackref_244) {
  EXPECT_EQ(RE2::MaxSubmatch("no backrefs"), 0);
}

TEST(RE2MaxSubmatchTest_244, SingleBackref_244) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
}

TEST(RE2MaxSubmatchTest_244, MultipleBackrefs_244) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1 and \\3"), 3);
}

// =============================================================================
// ProgramFanout Tests
// =============================================================================

TEST(RE2ProgramFanoutTest_244, SimplePattern_244) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ProgramFanoutTest_244, InvalidPattern_244) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_EQ(result, -1);
}

// =============================================================================
// ReverseProgramFanout Tests
// =============================================================================

TEST(RE2ReverseProgramFanoutTest_244, SimplePattern_244) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// =============================================================================
// Options Tests
// =============================================================================

TEST(RE2OptionsTest_244, CaseSensitiveByDefault_244) {
  RE2 re("hello");
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
}

TEST(RE2OptionsTest_244, CaseInsensitiveOption_244) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
}

// =============================================================================
// Constructor Variants Tests
// =============================================================================

TEST(RE2ConstructorTest_244, ConstCharPtr_244) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "abc");
}

TEST(RE2ConstructorTest_244, StdString_244) {
  std::string pattern = "abc";
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "abc");
}

TEST(RE2ConstructorTest_244, StringView_244) {
  absl::string_view pattern("abc");
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "abc");
}

// =============================================================================
// Rewrite Tests
// =============================================================================

TEST(RE2RewriteTest_244, SimpleRewrite_244) {
  RE2 re("(\\w+)@(\\w+)");
  ASSERT_TRUE(re.ok());
  std::string out;
  absl::string_view vec[3];
  vec[0] = "boris@kremlin";
  vec[1] = "boris";
  vec[2] = "kremlin";
  EXPECT_TRUE(re.Rewrite(&out, "\\2!\\1", vec, 3));
  EXPECT_EQ(out, "kremlin!boris");
}

// =============================================================================
// Edge Cases
// =============================================================================

TEST(RE2EdgeCaseTest_244, DotMatchesNewlineDefault_244) {
  // By default, . does not match \n
  EXPECT_FALSE(RE2::FullMatch("a\nb", "a.b"));
}

TEST(RE2EdgeCaseTest_244, DotMatchesNewlineOption_244) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST(RE2EdgeCaseTest_244, LargePatternCompiles_244) {
  // Build a pattern like (a|b|c|...) with many alternatives
  std::string pattern = "(";
  for (int i = 0; i < 100; i++) {
    if (i > 0) pattern += "|";
    pattern += "alt" + std::to_string(i);
  }
  pattern += ")";
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ProgramSize(), 0);
  EXPECT_TRUE(RE2::FullMatch("alt50", re));
}

}  // namespace re2
