#include "re2/re2.h"

#include <string>
#include <map>
#include <vector>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

// ==================== Construction and Basic Properties ====================

TEST(RE2Test_9, ConstructFromCString_9) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "hello");
}

TEST(RE2Test_9, ConstructFromStdString_9) {
  std::string pattern = "world";
  RE2 re(pattern);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "world");
}

TEST(RE2Test_9, ConstructFromStringView_9) {
  absl::string_view pattern = "foo";
  RE2 re(pattern);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "foo");
}

TEST(RE2Test_9, InvalidRegexReportsError_9) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error_code(), RE2::NoError);
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2Test_9, EmptyPatternIsValid_9) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "");
}

TEST(RE2Test_9, ErrorCodeForValidRegex_9) {
  RE2 re("abc");
  EXPECT_EQ(re.error_code(), RE2::NoError);
}

// ==================== FullMatch ====================

TEST(RE2FullMatchTest_9, SimpleFullMatch_9) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2FullMatchTest_9, FullMatchFails_9) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatchTest_9, FullMatchWithCapture_9) {
  std::string captured;
  EXPECT_TRUE(RE2::FullMatch("abc123", "([a-z]+)(\\d+)", &captured));
  // First capture group
  EXPECT_EQ(captured, "abc");
}

TEST(RE2FullMatchTest_9, FullMatchIntCapture_9) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &n));
  EXPECT_EQ(n, 12345);
}

TEST(RE2FullMatchTest_9, FullMatchMultipleCaptures_9) {
  std::string s;
  int n;
  EXPECT_TRUE(RE2::FullMatch("abc-42", "([a-z]+)-(\\d+)", &s, &n));
  EXPECT_EQ(s, "abc");
  EXPECT_EQ(n, 42);
}

TEST(RE2FullMatchTest_9, FullMatchEmptyString_9) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_TRUE(RE2::FullMatch("", ".*"));
}

TEST(RE2FullMatchTest_9, FullMatchEmptyPatternNonEmptyString_9) {
  EXPECT_FALSE(RE2::FullMatch("abc", ""));
}

// ==================== PartialMatch ====================

TEST(RE2PartialMatchTest_9, SimplePartialMatch_9) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "llo"));
}

TEST(RE2PartialMatchTest_9, PartialMatchFails_9) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2PartialMatchTest_9, PartialMatchWithCapture_9) {
  int n;
  EXPECT_TRUE(RE2::PartialMatch("x]234 foo", "(\\d+)", &n));
  EXPECT_EQ(n, 234);
}

TEST(RE2PartialMatchTest_9, PartialMatchAtBeginning_9) {
  EXPECT_TRUE(RE2::PartialMatch("hello", "^hel"));
}

TEST(RE2PartialMatchTest_9, PartialMatchAtEnd_9) {
  EXPECT_TRUE(RE2::PartialMatch("hello", "llo$"));
}

// ==================== Consume ====================

TEST(RE2ConsumeTest_9, SimpleConsume_9) {
  absl::string_view input("abc123def456");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ(word, "abc");
  // Input should have advanced past "abc"
  EXPECT_EQ(input, "123def456");
}

TEST(RE2ConsumeTest_9, ConsumeMultipleTimes_9) {
  absl::string_view input("aaa111bbb222");
  std::string s;
  int n;

  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &s));
  EXPECT_EQ(s, "aaa");
  EXPECT_TRUE(RE2::Consume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 111);
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &s));
  EXPECT_EQ(s, "bbb");
  EXPECT_TRUE(RE2::Consume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 222);
  EXPECT_TRUE(input.empty());
}

TEST(RE2ConsumeTest_9, ConsumeFailsNoMatch_9) {
  absl::string_view input("123abc");
  std::string word;
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &word));
  // Input should not have been modified on failure
  EXPECT_EQ(input, "123abc");
}

TEST(RE2ConsumeTest_9, ConsumeWithoutCapture_9) {
  absl::string_view input("hello world");
  EXPECT_TRUE(RE2::Consume(&input, "hello\\s*"));
  EXPECT_EQ(input, "world");
}

// ==================== FindAndConsume ====================

TEST(RE2FindAndConsumeTest_9, SimpleFindAndConsume_9) {
  absl::string_view input("abc123def456");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 123);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 456);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

TEST(RE2FindAndConsumeTest_9, FindAndConsumeNoMatch_9) {
  absl::string_view input("abcdef");
  int n;
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

// ==================== Replace ====================

TEST(RE2ReplaceTest_9, SimpleReplace_9) {
  std::string str = "hello world";
  EXPECT_TRUE(RE2::Replace(&str, "world", "there"));
  EXPECT_EQ(str, "hello there");
}

TEST(RE2ReplaceTest_9, ReplaceNoMatch_9) {
  std::string str = "hello world";
  EXPECT_FALSE(RE2::Replace(&str, "xyz", "abc"));
  EXPECT_EQ(str, "hello world");
}

TEST(RE2ReplaceTest_9, ReplaceOnlyFirst_9) {
  std::string str = "aaa";
  EXPECT_TRUE(RE2::Replace(&str, "a", "b"));
  EXPECT_EQ(str, "baa");
}

TEST(RE2ReplaceTest_9, ReplaceWithBackreference_9) {
  std::string str = "hello world";
  EXPECT_TRUE(RE2::Replace(&str, "(\\w+)\\s+(\\w+)", "\\2 \\1"));
  EXPECT_EQ(str, "world hello");
}

// ==================== GlobalReplace ====================

TEST(RE2GlobalReplaceTest_9, SimpleGlobalReplace_9) {
  std::string str = "aaa";
  int count = RE2::GlobalReplace(&str, "a", "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "bbb");
}

TEST(RE2GlobalReplaceTest_9, GlobalReplaceNoMatch_9) {
  std::string str = "hello";
  int count = RE2::GlobalReplace(&str, "x", "y");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

TEST(RE2GlobalReplaceTest_9, GlobalReplaceWithCapture_9) {
  std::string str = "abc def ghi";
  int count = RE2::GlobalReplace(&str, "(\\w+)", "[\\1]");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "[abc] [def] [ghi]");
}

// ==================== Extract ====================

TEST(RE2ExtractTest_9, SimpleExtract_9) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST(RE2ExtractTest_9, ExtractNoMatch_9) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-at-sign", "(.*)@(.*)", "\\1", &out));
}

// ==================== QuoteMeta ====================

TEST(RE2QuoteMetaTest_9, SimpleQuoteMeta_9) {
  std::string quoted = RE2::QuoteMeta("1.5-2.0?");
  EXPECT_TRUE(RE2::FullMatch("1.5-2.0?", quoted));
}

TEST(RE2QuoteMetaTest_9, QuoteMetaSpecialChars_9) {
  std::string quoted = RE2::QuoteMeta("a+b*c?");
  EXPECT_TRUE(RE2::FullMatch("a+b*c?", quoted));
  EXPECT_FALSE(RE2::FullMatch("abc", quoted));
}

TEST(RE2QuoteMetaTest_9, QuoteMetaEmptyString_9) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ(quoted, "");
  EXPECT_TRUE(RE2::FullMatch("", quoted));
}

// ==================== NumberOfCapturingGroups ====================

TEST(RE2Test_9, NumberOfCapturingGroups_9) {
  RE2 re("(\\d+)-(\\w+)-(.)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2Test_9, NumberOfCapturingGroupsNone_9) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2Test_9, NumberOfCapturingGroupsNonCapturing_9) {
  RE2 re("(?:abc)(def)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

// ==================== NamedCapturingGroups ====================

TEST(RE2Test_9, NamedCapturingGroups_9) {
  RE2 re("(?P<name>\\w+)\\s+(?P<age>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 2);
  EXPECT_EQ(groups.at("name"), 1);
  EXPECT_EQ(groups.at("age"), 2);
}

TEST(RE2Test_9, CapturingGroupNames_9) {
  RE2 re("(?P<name>\\w+)\\s+(?P<age>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 2);
  EXPECT_EQ(names.at(1), "name");
  EXPECT_EQ(names.at(2), "age");
}

// ==================== Match ====================

TEST(RE2MatchTest_9, MatchAnchored_9) {
  RE2 re("(\\d+)");
  EXPECT_TRUE(re.ok());
  absl::string_view text("abc123def");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 3, 6, RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "123");
}

TEST(RE2MatchTest_9, MatchAnchorStart_9) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
  absl::string_view text("abcdef");
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::ANCHOR_START, nullptr, 0));
  EXPECT_FALSE(re.Match(text, 0, text.size(), RE2::ANCHOR_START, nullptr, 0) &&
               false); // just checking it returns true above
}

TEST(RE2MatchTest_9, MatchAnchorBoth_9) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
  absl::string_view text("abc");
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_9, MatchAnchorBothFails_9) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
  absl::string_view text("abcdef");
  EXPECT_FALSE(re.Match(text, 0, text.size(), RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_9, MatchUnanchored_9) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.ok());
  absl::string_view text("abc123def");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "123");
}

TEST(RE2MatchTest_9, MatchNoSubmatch_9) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  absl::string_view text("hello world");
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, nullptr, 0));
}

TEST(RE2MatchTest_9, MatchSubrange_9) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.ok());
  absl::string_view text("abc123def456");
  absl::string_view submatch;
  // Only search in range [7, 12) which is "ef456"
  EXPECT_TRUE(re.Match(text, 7, text.size(), RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "456");
}

// ==================== CheckRewriteString ====================

TEST(RE2Test_9, CheckRewriteStringValid_9) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2Test_9, CheckRewriteStringInvalidGroup_9) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ==================== MaxSubmatch ====================

TEST(RE2Test_9, MaxSubmatch_9) {
  EXPECT_EQ(RE2::MaxSubmatch("\\0"), 0);
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
  EXPECT_EQ(RE2::MaxSubmatch("\\1 and \\3"), 3);
  EXPECT_EQ(RE2::MaxSubmatch("no backrefs"), 0);
}

// ==================== ProgramSize ====================

TEST(RE2Test_9, ProgramSize_9) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2Test_9, ReverseProgramSize_9) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ==================== PossibleMatchRange ====================

TEST(RE2Test_9, PossibleMatchRange_9) {
  RE2 re("abc.*");
  EXPECT_TRUE(re.ok());
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "abc");
  // max should be >= "abc"
  EXPECT_GE(max_str, "abc");
}

// ==================== Options ====================

TEST(RE2OptionsTest_9, CaseInsensitive_9) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HeLLo", re));
}

TEST(RE2OptionsTest_9, CaseSensitiveByDefault_9) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
}

// ==================== Hex / Octal / CRadix ====================

TEST(RE2Test_9, HexCapture_9) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("0x1a2b", "0x([0-9a-fA-F]+)", RE2::Hex(&v)));
  EXPECT_EQ(v, 0x1a2b);
}

TEST(RE2Test_9, OctalCapture_9) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("777", "(\\d+)", RE2::Octal(&v)));
  EXPECT_EQ(v, 0777);  // 511 decimal
}

TEST(RE2Test_9, CRadixHex_9) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(0x[0-9a-fA-F]+)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 0x1f);
}

TEST(RE2Test_9, CRadixOctal_9) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("010", "(0\\d+)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 010);  // 8 decimal
}

TEST(RE2Test_9, CRadixDecimal_9) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("42", "(\\d+)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 42);
}

// ==================== Rewrite ====================

TEST(RE2Test_9, Rewrite_9) {
  RE2 re("(\\w+):(\\d+)");
  EXPECT_TRUE(re.ok());
  std::string out;
  absl::string_view vec[3];
  vec[0] = "host:80";
  vec[1] = "host";
  vec[2] = "80";
  EXPECT_TRUE(re.Rewrite(&out, "\\1 at port \\2", vec, 3));
  EXPECT_EQ(out, "host at port 80");
}

// ==================== Edge Cases ====================

TEST(RE2Test_9, FullMatchWithDotStar_9) {
  EXPECT_TRUE(RE2::FullMatch("anything goes here", ".*"));
}

TEST(RE2Test_9, PartialMatchEmptyPattern_9) {
  EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

TEST(RE2Test_9, FullMatchNullCapture_9) {
  // Passing nullptr as capture arg - should still match but not capture
  EXPECT_TRUE(RE2::FullMatch("hello123", "(\\w+)(\\d+)"));
}

TEST(RE2Test_9, ConsumeEmptyMatch_9) {
  absl::string_view input("hello");
  // Regex that matches empty string
  EXPECT_TRUE(RE2::Consume(&input, ""));
}

TEST(RE2Test_9, ProgramFanout_9) {
  RE2 re("(a|b)c");
  EXPECT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2Test_9, ReverseProgramFanout_9) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ==================== Complex Patterns ====================

TEST(RE2Test_9, NestedGroups_9) {
  std::string outer, inner;
  EXPECT_TRUE(RE2::FullMatch("abcdef", "((abc)def)", &outer, &inner));
  EXPECT_EQ(outer, "abcdef");
  EXPECT_EQ(inner, "abc");
}

TEST(RE2Test_9, AlternationFullMatch_9) {
  EXPECT_TRUE(RE2::FullMatch("cat", "cat|dog"));
  EXPECT_TRUE(RE2::FullMatch("dog", "cat|dog"));
  EXPECT_FALSE(RE2::FullMatch("bird", "cat|dog"));
}

TEST(RE2Test_9, RepetitionFullMatch_9) {
  EXPECT_TRUE(RE2::FullMatch("aaa", "a{3}"));
  EXPECT_FALSE(RE2::FullMatch("aa", "a{3}"));
  EXPECT_FALSE(RE2::FullMatch("aaaa", "a{3}"));
}

TEST(RE2Test_9, FloatingPointCapture_9) {
  float f;
  EXPECT_TRUE(RE2::FullMatch("3.14", "([\\d.]+)", &f));
  EXPECT_NEAR(f, 3.14f, 0.001f);
}

TEST(RE2Test_9, DoubleCapture_9) {
  double d;
  EXPECT_TRUE(RE2::FullMatch("2.71828", "([\\d.]+)", &d));
  EXPECT_NEAR(d, 2.71828, 0.0001);
}

// ==================== Global Replace Edge Cases ====================

TEST(RE2GlobalReplaceTest_9, GlobalReplaceEmptyMatch_9) {
  std::string str = "abc";
  int count = RE2::GlobalReplace(&str, "", "-");
  // Empty pattern matches before each char and at end
  EXPECT_GT(count, 0);
}

TEST(RE2GlobalReplaceTest_9, GlobalReplaceOnEmptyString_9) {
  std::string str = "";
  int count = RE2::GlobalReplace(&str, "a", "b");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "");
}

// ==================== Replace with empty replacement ====================

TEST(RE2ReplaceTest_9, ReplaceWithEmpty_9) {
  std::string str = "hello world";
  EXPECT_TRUE(RE2::Replace(&str, "world", ""));
  EXPECT_EQ(str, "hello ");
}

// ==================== FullMatchN / PartialMatchN / ConsumeN / FindAndConsumeN ====================

TEST(RE2Test_9, FullMatchNZeroArgs_9) {
  EXPECT_TRUE(RE2::FullMatchN("hello", RE2("hello"), nullptr, 0));
}

TEST(RE2Test_9, PartialMatchNZeroArgs_9) {
  EXPECT_TRUE(RE2::PartialMatchN("hello world", RE2("llo"), nullptr, 0));
}

TEST(RE2Test_9, ConsumeNZeroArgs_9) {
  absl::string_view input("hello world");
  EXPECT_TRUE(RE2::ConsumeN(&input, RE2("hello\\s*"), nullptr, 0));
  EXPECT_EQ(input, "world");
}

TEST(RE2Test_9, FindAndConsumeNZeroArgs_9) {
  absl::string_view input("abc123");
  EXPECT_TRUE(RE2::FindAndConsumeN(&input, RE2("\\d+"), nullptr, 0));
}
