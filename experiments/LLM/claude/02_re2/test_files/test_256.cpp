#include "re2/re2.h"

#include <string>
#include <vector>
#include <map>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

namespace re2 {
namespace {

// =============================================================================
// RE2::Replace Tests
// =============================================================================

TEST(RE2ReplaceTest_256, BasicReplacement_256) {
  std::string str = "hello world";
  EXPECT_TRUE(RE2::Replace(&str, RE2("world"), "there"));
  EXPECT_EQ(str, "hello there");
}

TEST(RE2ReplaceTest_256, ReplaceWithCapturingGroup_256) {
  std::string str = "hello world";
  EXPECT_TRUE(RE2::Replace(&str, RE2("(world)"), "\\1!"));
  EXPECT_EQ(str, "hello world!");
}

TEST(RE2ReplaceTest_256, ReplaceNoMatch_256) {
  std::string str = "hello world";
  EXPECT_FALSE(RE2::Replace(&str, RE2("xyz"), "replacement"));
  EXPECT_EQ(str, "hello world");
}

TEST(RE2ReplaceTest_256, ReplaceFirstOccurrenceOnly_256) {
  std::string str = "aaa";
  EXPECT_TRUE(RE2::Replace(&str, RE2("a"), "b"));
  EXPECT_EQ(str, "baa");
}

TEST(RE2ReplaceTest_256, ReplaceWithEmptyString_256) {
  std::string str = "hello world";
  EXPECT_TRUE(RE2::Replace(&str, RE2("world"), ""));
  EXPECT_EQ(str, "hello ");
}

TEST(RE2ReplaceTest_256, ReplaceEmptyPattern_256) {
  std::string str = "hello";
  EXPECT_TRUE(RE2::Replace(&str, RE2(""), "x"));
  EXPECT_EQ(str, "xhello");
}

TEST(RE2ReplaceTest_256, ReplaceOnEmptyString_256) {
  std::string str = "";
  EXPECT_TRUE(RE2::Replace(&str, RE2(""), "x"));
  EXPECT_EQ(str, "x");
}

TEST(RE2ReplaceTest_256, ReplaceEmptyStringNoMatch_256) {
  std::string str = "";
  EXPECT_FALSE(RE2::Replace(&str, RE2("a"), "x"));
  EXPECT_EQ(str, "");
}

TEST(RE2ReplaceTest_256, ReplaceWithBackreference_256) {
  std::string str = "foo bar";
  EXPECT_TRUE(RE2::Replace(&str, RE2("(foo) (bar)"), "\\2 \\1"));
  EXPECT_EQ(str, "bar foo");
}

TEST(RE2ReplaceTest_256, ReplaceInvalidRewriteSubmatch_256) {
  // Rewrite references more groups than the pattern has
  std::string str = "hello";
  EXPECT_FALSE(RE2::Replace(&str, RE2("hello"), "\\1"));
  EXPECT_EQ(str, "hello");
}

TEST(RE2ReplaceTest_256, ReplacePartialMatch_256) {
  std::string str = "abcdef";
  EXPECT_TRUE(RE2::Replace(&str, RE2("cd"), "XX"));
  EXPECT_EQ(str, "abXXef");
}

TEST(RE2ReplaceTest_256, ReplaceAtBeginning_256) {
  std::string str = "hello world";
  EXPECT_TRUE(RE2::Replace(&str, RE2("hello"), "goodbye"));
  EXPECT_EQ(str, "goodbye world");
}

TEST(RE2ReplaceTest_256, ReplaceAtEnd_256) {
  std::string str = "hello world";
  EXPECT_TRUE(RE2::Replace(&str, RE2("world"), "earth"));
  EXPECT_EQ(str, "hello earth");
}

TEST(RE2ReplaceTest_256, ReplaceWithLongerString_256) {
  std::string str = "ab";
  EXPECT_TRUE(RE2::Replace(&str, RE2("ab"), "abcdef"));
  EXPECT_EQ(str, "abcdef");
}

TEST(RE2ReplaceTest_256, ReplaceWithShorterString_256) {
  std::string str = "abcdef";
  EXPECT_TRUE(RE2::Replace(&str, RE2("abcdef"), "ab"));
  EXPECT_EQ(str, "ab");
}

TEST(RE2ReplaceTest_256, ReplaceDigitPattern_256) {
  std::string str = "abc123def";
  EXPECT_TRUE(RE2::Replace(&str, RE2("\\d+"), "NUM"));
  EXPECT_EQ(str, "abcNUMdef");
}

TEST(RE2ReplaceTest_256, ReplaceWithLiteralBackslash_256) {
  std::string str = "hello world";
  EXPECT_TRUE(RE2::Replace(&str, RE2("world"), "w\\\\o"));
  EXPECT_EQ(str, "hello w\\o");
}

// =============================================================================
// RE2::GlobalReplace Tests
// =============================================================================

TEST(RE2GlobalReplaceTest_256, BasicGlobalReplace_256) {
  std::string str = "aaa";
  int count = RE2::GlobalReplace(&str, RE2("a"), "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "bbb");
}

TEST(RE2GlobalReplaceTest_256, GlobalReplaceNoMatch_256) {
  std::string str = "hello";
  int count = RE2::GlobalReplace(&str, RE2("x"), "y");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

TEST(RE2GlobalReplaceTest_256, GlobalReplaceMultipleOccurrences_256) {
  std::string str = "the cat sat on the mat";
  int count = RE2::GlobalReplace(&str, RE2("at"), "og");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "the cog sog on the mog");
}

TEST(RE2GlobalReplaceTest_256, GlobalReplaceEmptyMatch_256) {
  std::string str = "abc";
  int count = RE2::GlobalReplace(&str, RE2(""), "x");
  // Each position between characters and at start/end can match empty
  EXPECT_GT(count, 0);
}

TEST(RE2GlobalReplaceTest_256, GlobalReplaceWithCapturingGroup_256) {
  std::string str = "abc def ghi";
  int count = RE2::GlobalReplace(&str, RE2("(\\w+)"), "[\\1]");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "[abc] [def] [ghi]");
}

// =============================================================================
// RE2::Extract Tests
// =============================================================================

TEST(RE2ExtractTest_256, BasicExtract_256) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", RE2("(.*)@([^.]*)"), "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST(RE2ExtractTest_256, ExtractNoMatch_256) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("hello", RE2("(xyz)"), "\\1", &out));
}

TEST(RE2ExtractTest_256, ExtractFullString_256) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("hello", RE2("(.*)"), "\\1", &out));
  EXPECT_EQ(out, "hello");
}

TEST(RE2ExtractTest_256, ExtractInvalidRewrite_256) {
  std::string out;
  // Reference to group that doesn't exist
  EXPECT_FALSE(RE2::Extract("hello", RE2("hello"), "\\1", &out));
}

// =============================================================================
// RE2::FullMatch Tests
// =============================================================================

TEST(RE2FullMatchTest_256, BasicFullMatch_256) {
  EXPECT_TRUE(RE2::FullMatch("hello", RE2("hello")));
}

TEST(RE2FullMatchTest_256, FullMatchFails_256) {
  EXPECT_FALSE(RE2::FullMatch("hello world", RE2("hello")));
}

TEST(RE2FullMatchTest_256, FullMatchWithCapture_256) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("123", RE2("(\\d+)"), &n));
  EXPECT_EQ(n, 123);
}

TEST(RE2FullMatchTest_256, FullMatchEmptyString_256) {
  EXPECT_TRUE(RE2::FullMatch("", RE2("")));
}

TEST(RE2FullMatchTest_256, FullMatchEmptyStringWithPattern_256) {
  EXPECT_FALSE(RE2::FullMatch("", RE2("a")));
}

// =============================================================================
// RE2::PartialMatch Tests
// =============================================================================

TEST(RE2PartialMatchTest_256, BasicPartialMatch_256) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", RE2("world")));
}

TEST(RE2PartialMatchTest_256, PartialMatchFails_256) {
  EXPECT_FALSE(RE2::PartialMatch("hello", RE2("xyz")));
}

TEST(RE2PartialMatchTest_256, PartialMatchWithCapture_256) {
  std::string word;
  EXPECT_TRUE(RE2::PartialMatch("hello world", RE2("(\\w+)"), &word));
  EXPECT_EQ(word, "hello");
}

// =============================================================================
// RE2::Consume Tests
// =============================================================================

TEST(RE2ConsumeTest_256, BasicConsume_256) {
  absl::string_view input("one two three");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, RE2("(\\w+)\\s*"), &word));
  EXPECT_EQ(word, "one");
  EXPECT_TRUE(RE2::Consume(&input, RE2("(\\w+)\\s*"), &word));
  EXPECT_EQ(word, "two");
  EXPECT_TRUE(RE2::Consume(&input, RE2("(\\w+)\\s*"), &word));
  EXPECT_EQ(word, "three");
}

TEST(RE2ConsumeTest_256, ConsumeNoMatch_256) {
  absl::string_view input("hello");
  EXPECT_FALSE(RE2::Consume(&input, RE2("\\d+")));
}

// =============================================================================
// RE2::FindAndConsume Tests
// =============================================================================

TEST(RE2FindAndConsumeTest_256, BasicFindAndConsume_256) {
  absl::string_view input("one 123 two 456");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, RE2("(\\d+)"), &n));
  EXPECT_EQ(n, 123);
  EXPECT_TRUE(RE2::FindAndConsume(&input, RE2("(\\d+)"), &n));
  EXPECT_EQ(n, 456);
}

TEST(RE2FindAndConsumeTest_256, FindAndConsumeNoMatch_256) {
  absl::string_view input("no digits here");
  EXPECT_FALSE(RE2::FindAndConsume(&input, RE2("(\\d+)")));
}

// =============================================================================
// RE2 Constructor and Status Tests
// =============================================================================

TEST(RE2ConstructorTest_256, ValidPattern_256) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
}

TEST(RE2ConstructorTest_256, InvalidPattern_256) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error_code(), RE2::NoError);
}

TEST(RE2ConstructorTest_256, PatternAccessor_256) {
  RE2 re("abc");
  EXPECT_EQ(re.pattern(), "abc");
}

TEST(RE2ConstructorTest_256, NumberOfCapturingGroups_256) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2ConstructorTest_256, NoCapturingGroups_256) {
  RE2 re("abc");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

// =============================================================================
// RE2::QuoteMeta Tests
// =============================================================================

TEST(RE2QuoteMetaTest_256, BasicQuoteMeta_256) {
  std::string quoted = RE2::QuoteMeta("hello.world");
  RE2 re(quoted);
  EXPECT_TRUE(RE2::FullMatch("hello.world", re));
  EXPECT_FALSE(RE2::FullMatch("helloXworld", re));
}

TEST(RE2QuoteMetaTest_256, QuoteMetaSpecialChars_256) {
  std::string quoted = RE2::QuoteMeta("a+b*c?");
  RE2 re(quoted);
  EXPECT_TRUE(RE2::FullMatch("a+b*c?", re));
}

TEST(RE2QuoteMetaTest_256, QuoteMetaEmptyString_256) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

// =============================================================================
// RE2::MaxSubmatch Tests
// =============================================================================

TEST(RE2MaxSubmatchTest_256, NoSubmatch_256) {
  EXPECT_EQ(RE2::MaxSubmatch("hello"), 0);
}

TEST(RE2MaxSubmatchTest_256, SingleSubmatch_256) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
}

TEST(RE2MaxSubmatchTest_256, MultipleSubmatches_256) {
  EXPECT_EQ(RE2::MaxSubmatch("\\2 \\1"), 2);
}

TEST(RE2MaxSubmatchTest_256, HigherSubmatch_256) {
  EXPECT_EQ(RE2::MaxSubmatch("\\5"), 5);
}

// =============================================================================
// RE2::CheckRewriteString Tests
// =============================================================================

TEST(RE2CheckRewriteStringTest_256, ValidRewrite_256) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewriteStringTest_256, InvalidRewriteTooManyGroups_256) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

TEST(RE2CheckRewriteStringTest_256, NoGroupsValidRewrite_256) {
  RE2 re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("world", &error));
}

// =============================================================================
// RE2::Match Tests
// =============================================================================

TEST(RE2MatchTest_256, BasicMatch_256) {
  RE2 re("(\\w+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("hello world", 0, 11, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ(submatch[0], "hello");
  EXPECT_EQ(submatch[1], "hello");
}

TEST(RE2MatchTest_256, MatchAnchored_256) {
  RE2 re("hello");
  EXPECT_TRUE(re.Match("hello world", 0, 11, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_FALSE(re.Match("say hello", 0, 9, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_256, MatchAnchorBoth_256) {
  RE2 re("hello");
  EXPECT_TRUE(re.Match("hello", 0, 5, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_FALSE(re.Match("hello world", 0, 11, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_256, MatchNoMatch_256) {
  RE2 re("xyz");
  EXPECT_FALSE(re.Match("hello world", 0, 11, RE2::UNANCHORED, nullptr, 0));
}

TEST(RE2MatchTest_256, MatchWithStartPos_256) {
  RE2 re("world");
  EXPECT_TRUE(re.Match("hello world", 6, 11, RE2::UNANCHORED, nullptr, 0));
  EXPECT_FALSE(re.Match("hello world", 0, 5, RE2::UNANCHORED, nullptr, 0));
}

// =============================================================================
// RE2::PossibleMatchRange Tests
// =============================================================================

TEST(RE2PossibleMatchRangeTest_256, BasicRange_256) {
  RE2 re("abc");
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_FALSE(min.empty());
  EXPECT_FALSE(max.empty());
  EXPECT_LE(min, "abc");
  EXPECT_GE(max, "abc");
}

// =============================================================================
// RE2::NamedCapturingGroups Tests
// =============================================================================

TEST(RE2NamedCapturingGroupsTest_256, NoNamedGroups_256) {
  RE2 re("(\\w+)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2NamedCapturingGroupsTest_256, WithNamedGroups_256) {
  RE2 re("(?P<name>\\w+) (?P<age>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 2);
  EXPECT_EQ(groups.at("name"), 1);
  EXPECT_EQ(groups.at("age"), 2);
}

// =============================================================================
// RE2::CapturingGroupNames Tests
// =============================================================================

TEST(RE2CapturingGroupNamesTest_256, WithNamedGroups_256) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 2);
  EXPECT_EQ(names.at(1), "first");
  EXPECT_EQ(names.at(2), "second");
}

// =============================================================================
// RE2 Options Tests
// =============================================================================

TEST(RE2OptionsTest_256, CaseInsensitive_256) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HeLLo", re));
}

// =============================================================================
// RE2::ProgramSize Tests
// =============================================================================

TEST(RE2ProgramSizeTest_256, BasicProgramSize_256) {
  RE2 re("hello");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_256, ComplexPatternLargerSize_256) {
  RE2 simple("a");
  RE2 complex("(a|b|c|d|e)(f|g|h|i|j)");
  EXPECT_GT(complex.ProgramSize(), simple.ProgramSize());
}

// =============================================================================
// Replace edge cases
// =============================================================================

TEST(RE2ReplaceTest_256, ReplaceWithMultipleCapturingGroups_256) {
  std::string str = "2023-01-15";
  EXPECT_TRUE(RE2::Replace(&str, RE2("(\\d{4})-(\\d{2})-(\\d{2})"), "\\2/\\3/\\1"));
  EXPECT_EQ(str, "01/15/2023");
}

TEST(RE2ReplaceTest_256, ReplaceDoesNotModifyOnInvalidRewrite_256) {
  std::string str = "hello";
  std::string original = str;
  // Pattern has no capture groups but rewrite references \\1
  EXPECT_FALSE(RE2::Replace(&str, RE2("hello"), "\\1"));
  EXPECT_EQ(str, original);
}

TEST(RE2ReplaceTest_256, ReplaceSamePatternAndRewrite_256) {
  std::string str = "abc";
  EXPECT_TRUE(RE2::Replace(&str, RE2("abc"), "abc"));
  EXPECT_EQ(str, "abc");
}

TEST(RE2ReplaceTest_256, ReplaceWithSpecialRegexCharacters_256) {
  std::string str = "price is $100";
  EXPECT_TRUE(RE2::Replace(&str, RE2("\\$\\d+"), "free"));
  EXPECT_EQ(str, "price is free");
}

TEST(RE2ReplaceTest_256, ReplaceUnicodeContent_256) {
  std::string str = "hello wörld";
  EXPECT_TRUE(RE2::Replace(&str, RE2("wörld"), "world"));
  EXPECT_EQ(str, "hello world");
}

// =============================================================================
// GlobalReplace edge cases
// =============================================================================

TEST(RE2GlobalReplaceTest_256, GlobalReplaceOnEmptyString_256) {
  std::string str = "";
  int count = RE2::GlobalReplace(&str, RE2("a"), "b");
  EXPECT_EQ(count, 0);
}

TEST(RE2GlobalReplaceTest_256, GlobalReplaceAllCharacters_256) {
  std::string str = "aaaa";
  int count = RE2::GlobalReplace(&str, RE2("a"), "bb");
  EXPECT_EQ(count, 4);
  EXPECT_EQ(str, "bbbbbbbb");
}

}  // namespace
}  // namespace re2
