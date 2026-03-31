#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"

namespace {

using re2::RE2;

// =============================================================================
// ConsumeN - Normal Operation Tests
// =============================================================================

TEST(RE2ConsumeNTest_254, BasicConsumeWithNoCaptures_254) {
  absl::string_view input("hello world");
  RE2 re("hello");
  EXPECT_TRUE(RE2::ConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ(input, " world");
}

TEST(RE2ConsumeNTest_254, ConsumeWithOneCapture_254) {
  absl::string_view input("123abc");
  RE2 re("(\\d+)");
  std::string captured;
  RE2::Arg arg(&captured);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::ConsumeN(&input, re, args, 1));
  EXPECT_EQ(captured, "123");
  EXPECT_EQ(input, "abc");
}

TEST(RE2ConsumeNTest_254, ConsumeWithMultipleCaptures_254) {
  absl::string_view input("John:30:rest");
  RE2 re("(\\w+):(\\d+):");
  std::string name;
  int age;
  RE2::Arg arg1(&name);
  RE2::Arg arg2(&age);
  const RE2::Arg* args[] = {&arg1, &arg2};
  EXPECT_TRUE(RE2::ConsumeN(&input, re, args, 2));
  EXPECT_EQ(name, "John");
  EXPECT_EQ(age, 30);
  EXPECT_EQ(input, "rest");
}

TEST(RE2ConsumeNTest_254, ConsumeEntireString_254) {
  absl::string_view input("hello");
  RE2 re("hello");
  EXPECT_TRUE(RE2::ConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ(input, "");
}

TEST(RE2ConsumeNTest_254, ConsumeRepeatedCalls_254) {
  absl::string_view input("aabbcc");
  RE2 re("(\\w\\w)");
  std::string captured;
  RE2::Arg arg(&captured);
  const RE2::Arg* args[] = {&arg};

  EXPECT_TRUE(RE2::ConsumeN(&input, re, args, 1));
  EXPECT_EQ(captured, "aa");
  EXPECT_EQ(input, "bbcc");

  EXPECT_TRUE(RE2::ConsumeN(&input, re, args, 1));
  EXPECT_EQ(captured, "bb");
  EXPECT_EQ(input, "cc");

  EXPECT_TRUE(RE2::ConsumeN(&input, re, args, 1));
  EXPECT_EQ(captured, "cc");
  EXPECT_EQ(input, "");
}

// =============================================================================
// ConsumeN - Boundary Conditions
// =============================================================================

TEST(RE2ConsumeNTest_254, ConsumeFromEmptyString_254) {
  absl::string_view input("");
  RE2 re("\\w+");
  EXPECT_FALSE(RE2::ConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ(input, "");
}

TEST(RE2ConsumeNTest_254, ConsumeWithEmptyMatch_254) {
  absl::string_view input("hello");
  RE2 re("(\\w*)");
  std::string captured;
  RE2::Arg arg(&captured);
  const RE2::Arg* args[] = {&arg};
  // Empty regex or regex matching empty string at start
  EXPECT_TRUE(RE2::ConsumeN(&input, re, args, 1));
}

TEST(RE2ConsumeNTest_254, ConsumeFromEmptyStringWithEmptyPattern_254) {
  absl::string_view input("");
  RE2 re("");
  EXPECT_TRUE(RE2::ConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ(input, "");
}

// =============================================================================
// ConsumeN - No Match / Error Cases
// =============================================================================

TEST(RE2ConsumeNTest_254, ConsumeNoMatchAtStart_254) {
  absl::string_view input("hello world");
  RE2 re("world");
  EXPECT_FALSE(RE2::ConsumeN(&input, re, nullptr, 0));
  // Input should remain unchanged on failure
  EXPECT_EQ(input, "hello world");
}

TEST(RE2ConsumeNTest_254, ConsumePatternDoesNotMatchAtBeginning_254) {
  absl::string_view input("abc123");
  RE2 re("\\d+");
  EXPECT_FALSE(RE2::ConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ(input, "abc123");
}

TEST(RE2ConsumeNTest_254, ConsumeWithIntCapture_254) {
  absl::string_view input("42 is the answer");
  RE2 re("(\\d+) ");
  int value;
  RE2::Arg arg(&value);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::ConsumeN(&input, re, args, 1));
  EXPECT_EQ(value, 42);
  EXPECT_EQ(input, "is the answer");
}

// =============================================================================
// Consume (variadic template wrapper) Tests
// =============================================================================

TEST(RE2ConsumeTest_254, ConsumeVariadicNoCaptures_254) {
  absl::string_view input("foobar");
  EXPECT_TRUE(RE2::Consume(&input, "foo"));
  EXPECT_EQ(input, "bar");
}

TEST(RE2ConsumeTest_254, ConsumeVariadicWithCapture_254) {
  absl::string_view input("123abc");
  int number;
  EXPECT_TRUE(RE2::Consume(&input, "(\\d+)", &number));
  EXPECT_EQ(number, 123);
  EXPECT_EQ(input, "abc");
}

TEST(RE2ConsumeTest_254, ConsumeVariadicNoMatch_254) {
  absl::string_view input("abc");
  int number;
  EXPECT_FALSE(RE2::Consume(&input, "(\\d+)", &number));
  EXPECT_EQ(input, "abc");
}

TEST(RE2ConsumeTest_254, ConsumeVariadicStringCapture_254) {
  absl::string_view input("hello-world");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "(\\w+)", &word));
  EXPECT_EQ(word, "hello");
  EXPECT_EQ(input, "-world");
}

// =============================================================================
// FullMatch and PartialMatch Tests (for completeness of static method testing)
// =============================================================================

TEST(RE2FullMatchTest_254, FullMatchSimple_254) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatchTest_254, FullMatchWithCapture_254) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("42", "(\\d+)", &n));
  EXPECT_EQ(n, 42);
}

TEST(RE2PartialMatchTest_254, PartialMatchSimple_254) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "world"));
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2PartialMatchTest_254, PartialMatchWithCapture_254) {
  std::string word;
  EXPECT_TRUE(RE2::PartialMatch("the quick brown fox", "(\\w+)", &word));
  EXPECT_EQ(word, "the");
}

// =============================================================================
// FindAndConsume Tests
// =============================================================================

TEST(RE2FindAndConsumeTest_254, FindAndConsumeBasic_254) {
  absl::string_view input("one:1 two:2 three:3");
  std::string word;
  int number;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\w+):(\\d+)", &word, &number));
  EXPECT_EQ(word, "one");
  EXPECT_EQ(number, 1);
}

TEST(RE2FindAndConsumeTest_254, FindAndConsumeNoMatch_254) {
  absl::string_view input("no match here");
  int number;
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &number));
}

TEST(RE2FindAndConsumeTest_254, FindAndConsumeRepeated_254) {
  absl::string_view input("a1b2c3");
  std::string letter;
  int digit;
  
  EXPECT_TRUE(RE2::FindAndConsume(&input, "([a-z])(\\d)", &letter, &digit));
  EXPECT_EQ(letter, "a");
  EXPECT_EQ(digit, 1);
  
  EXPECT_TRUE(RE2::FindAndConsume(&input, "([a-z])(\\d)", &letter, &digit));
  EXPECT_EQ(letter, "b");
  EXPECT_EQ(digit, 2);
  
  EXPECT_TRUE(RE2::FindAndConsume(&input, "([a-z])(\\d)", &letter, &digit));
  EXPECT_EQ(letter, "c");
  EXPECT_EQ(digit, 3);
}

// =============================================================================
// Replace and GlobalReplace Tests
// =============================================================================

TEST(RE2ReplaceTest_254, ReplaceFirst_254) {
  std::string s = "hello world hello";
  EXPECT_TRUE(RE2::Replace(&s, "hello", "hi"));
  EXPECT_EQ(s, "hi world hello");
}

TEST(RE2ReplaceTest_254, ReplaceNoMatch_254) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ(s, "hello world");
}

TEST(RE2ReplaceTest_254, GlobalReplaceAll_254) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, "a", "bb");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "bbbbbb");
}

TEST(RE2ReplaceTest_254, GlobalReplaceNone_254) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello");
}

TEST(RE2ReplaceTest_254, ReplaceWithCaptureReference_254) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "[\\1]"));
  EXPECT_EQ(s, "[hello] world");
}

// =============================================================================
// Extract Tests
// =============================================================================

TEST(RE2ExtractTest_254, ExtractBasic_254) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST(RE2ExtractTest_254, ExtractNoMatch_254) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-email-here", "(.*)@([^.]*)", "\\2!\\1", &out));
}

// =============================================================================
// QuoteMeta Tests
// =============================================================================

TEST(RE2QuoteMetaTest_254, QuoteMetaSpecialChars_254) {
  std::string quoted = RE2::QuoteMeta("a.b+c*d?e");
  // The quoted string should be usable as a literal pattern
  EXPECT_TRUE(RE2::FullMatch("a.b+c*d?e", quoted));
  EXPECT_FALSE(RE2::FullMatch("aXb+c*d?e", quoted));
}

TEST(RE2QuoteMetaTest_254, QuoteMetaNoSpecialChars_254) {
  std::string quoted = RE2::QuoteMeta("hello");
  EXPECT_EQ(quoted, "hello");
}

TEST(RE2QuoteMetaTest_254, QuoteMetaEmptyString_254) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

// =============================================================================
// RE2 Construction and Query Tests
// =============================================================================

TEST(RE2ConstructionTest_254, ValidPatternIsOk_254) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.ok());
}

TEST(RE2ConstructionTest_254, InvalidPatternIsNotOk_254) {
  RE2 re("[invalid");
  EXPECT_FALSE(re.ok());
}

TEST(RE2ConstructionTest_254, PatternReturnsOriginal_254) {
  RE2 re("hello.*world");
  EXPECT_EQ(re.pattern(), "hello.*world");
}

TEST(RE2ConstructionTest_254, ErrorCodeOnBadPattern_254) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error_code(), RE2::NoError);
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2ConstructionTest_254, NumberOfCapturingGroups_254) {
  RE2 re("(\\w+)\\s+(\\d+)\\s+(\\w+)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2ConstructionTest_254, NumberOfCapturingGroupsNone_254) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

// =============================================================================
// Match Tests
// =============================================================================

TEST(RE2MatchTest_254, MatchUnanchored_254) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ(submatch[0], "123");
  EXPECT_EQ(submatch[1], "123");
}

TEST(RE2MatchTest_254, MatchAnchorStart_254) {
  RE2 re("(\\d+)");
  EXPECT_FALSE(re.Match("abc123", 0, 6, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_254, MatchAnchorBoth_254) {
  RE2 re("(\\d+)");
  EXPECT_FALSE(re.Match("123abc", 0, 6, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

// =============================================================================
// MaxSubmatch Tests
// =============================================================================

TEST(RE2MaxSubmatchTest_254, MaxSubmatchBasic_254) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1 \\2 \\3"), 3);
}

TEST(RE2MaxSubmatchTest_254, MaxSubmatchNone_254) {
  EXPECT_EQ(RE2::MaxSubmatch("no refs"), 0);
}

// =============================================================================
// CheckRewriteString Tests
// =============================================================================

TEST(RE2CheckRewriteTest_254, ValidRewrite_254) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewriteTest_254, InvalidRewriteTooHighSubmatch_254) {
  RE2 re("(\\w+)");
  std::string error;
  // \\2 references a group that doesn't exist (only 1 capturing group)
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// =============================================================================
// PossibleMatchRange Tests
// =============================================================================

TEST(RE2PossibleMatchRangeTest_254, BasicRange_254) {
  RE2 re("abc.*");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "abc");
}

// =============================================================================
// Named Capturing Groups Tests
// =============================================================================

TEST(RE2NamedGroupsTest_254, NamedCapturingGroups_254) {
  RE2 re("(?P<name>\\w+) (?P<age>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& named = re.NamedCapturingGroups();
  EXPECT_EQ(named.size(), 2);
  EXPECT_EQ(named.at("name"), 1);
  EXPECT_EQ(named.at("age"), 2);
}

TEST(RE2NamedGroupsTest_254, CapturingGroupNames_254) {
  RE2 re("(?P<first>\\w+)(?P<second>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.CapturingGroupNames();
  EXPECT_EQ(groups.size(), 2);
  EXPECT_EQ(groups.at(1), "first");
  EXPECT_EQ(groups.at(2), "second");
}

TEST(RE2NamedGroupsTest_254, NoNamedGroups_254) {
  RE2 re("(\\w+)(\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& named = re.NamedCapturingGroups();
  EXPECT_TRUE(named.empty());
}

// =============================================================================
// ConsumeN with integer capture type mismatch
// =============================================================================

TEST(RE2ConsumeNTest_254, ConsumeIntegerOverflow_254) {
  absl::string_view input("99999999999999999999 rest");
  RE2 re("(\\d+) ");
  int value;
  RE2::Arg arg(&value);
  const RE2::Arg* args[] = {&arg};
  // Depending on implementation, this may fail due to overflow
  bool result = RE2::ConsumeN(&input, re, args, 1);
  // We just verify it doesn't crash; result may vary
  (void)result;
}

// =============================================================================
// ConsumeN with nullptr args but n=0
// =============================================================================

TEST(RE2ConsumeNTest_254, ConsumeNNullArgsZeroN_254) {
  absl::string_view input("hello world");
  RE2 re("hello");
  EXPECT_TRUE(RE2::ConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ(input, " world");
}

// =============================================================================
// ConsumeN - pattern with anchoring at start
// =============================================================================

TEST(RE2ConsumeNTest_254, ConsumeWithCaret_254) {
  absl::string_view input("hello world");
  RE2 re("^hello");
  EXPECT_TRUE(RE2::ConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ(input, " world");
}

// =============================================================================
// Consume after full consumption
// =============================================================================

TEST(RE2ConsumeNTest_254, ConsumeAfterExhausted_254) {
  absl::string_view input("ab");
  RE2 re("(.)");
  std::string s;
  RE2::Arg arg(&s);
  const RE2::Arg* args[] = {&arg};

  EXPECT_TRUE(RE2::ConsumeN(&input, re, args, 1));
  EXPECT_EQ(s, "a");
  EXPECT_TRUE(RE2::ConsumeN(&input, re, args, 1));
  EXPECT_EQ(s, "b");
  EXPECT_FALSE(RE2::ConsumeN(&input, re, args, 1));
}

}  // namespace
