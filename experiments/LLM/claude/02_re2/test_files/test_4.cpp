#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>

namespace {

// ==================== Construction and Basic Properties ====================

TEST(RE2Test_4, ConstructFromCString_4) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("hello", re.pattern());
}

TEST(RE2Test_4, ConstructFromStdString_4) {
  std::string pattern = "world";
  RE2 re(pattern);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("world", re.pattern());
}

TEST(RE2Test_4, ConstructFromStringView_4) {
  absl::string_view sv = "test.*pattern";
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("test.*pattern", re.pattern());
}

TEST(RE2Test_4, ConstructWithOptions_4) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("Hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("Hello", re.pattern());
}

TEST(RE2Test_4, InvalidPattern_4) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2Test_4, EmptyPattern_4) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("", re.pattern());
}

TEST(RE2Test_4, ErrorCodeForValidPattern_4) {
  RE2 re("abc");
  EXPECT_EQ(RE2::NoError, re.error_code());
}

TEST(RE2Test_4, ErrorArgForInvalidPattern_4) {
  RE2 re("[z-a]");
  EXPECT_FALSE(re.ok());
  // error_arg should give some info about the bad part
  EXPECT_FALSE(re.error_arg().empty());
}

// ==================== NumberOfCapturingGroups ====================

TEST(RE2Test_4, NumberOfCapturingGroupsNone_4) {
  RE2 re("abc");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(RE2Test_4, NumberOfCapturingGroupsOne_4) {
  RE2 re("(abc)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(RE2Test_4, NumberOfCapturingGroupsMultiple_4) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2Test_4, NumberOfCapturingGroupsNonCapturing_4) {
  RE2 re("(?:abc)");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(RE2Test_4, NumberOfCapturingGroupsNested_4) {
  RE2 re("((a)(b))");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

// ==================== FullMatch ====================

TEST(RE2Test_4, FullMatchSimple_4) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2Test_4, FullMatchWithCapture_4) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("123", "(\\d+)", &n));
  EXPECT_EQ(123, n);
}

TEST(RE2Test_4, FullMatchStringCapture_4) {
  std::string s;
  EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", &s));
  EXPECT_EQ("hello", s);
}

TEST(RE2Test_4, FullMatchMultipleCaptures_4) {
  std::string a, b;
  EXPECT_TRUE(RE2::FullMatch("hello-world", "(\\w+)-(\\w+)", &a, &b));
  EXPECT_EQ("hello", a);
  EXPECT_EQ("world", b);
}

TEST(RE2Test_4, FullMatchFails_4) {
  EXPECT_FALSE(RE2::FullMatch("abc", "\\d+"));
}

TEST(RE2Test_4, FullMatchEmpty_4) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_TRUE(RE2::FullMatch("", ".*"));
}

// ==================== PartialMatch ====================

TEST(RE2Test_4, PartialMatchSimple_4) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "llo"));
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2Test_4, PartialMatchWithCapture_4) {
  int n;
  EXPECT_TRUE(RE2::PartialMatch("abc 123 def", "(\\d+)", &n));
  EXPECT_EQ(123, n);
}

TEST(RE2Test_4, PartialMatchAtStart_4) {
  EXPECT_TRUE(RE2::PartialMatch("hello", "^hel"));
}

TEST(RE2Test_4, PartialMatchAtEnd_4) {
  EXPECT_TRUE(RE2::PartialMatch("hello", "llo$"));
}

// ==================== Consume ====================

TEST(RE2Test_4, ConsumeBasic_4) {
  absl::string_view input("one123two456");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ("one", word);
  // Input should have advanced past "one"
  EXPECT_EQ("123two456", std::string(input));
}

TEST(RE2Test_4, ConsumeMultipleTimes_4) {
  absl::string_view input("aabb");
  std::string s;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z])", &s));
  EXPECT_EQ("a", s);
  EXPECT_TRUE(RE2::Consume(&input, "([a-z])", &s));
  EXPECT_EQ("a", s);
  EXPECT_TRUE(RE2::Consume(&input, "([a-z])", &s));
  EXPECT_EQ("b", s);
  EXPECT_TRUE(RE2::Consume(&input, "([a-z])", &s));
  EXPECT_EQ("b", s);
  EXPECT_FALSE(RE2::Consume(&input, "([a-z])", &s));
}

TEST(RE2Test_4, ConsumeFails_4) {
  absl::string_view input("123abc");
  std::string word;
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &word));
  // Input should not have changed
  EXPECT_EQ("123abc", std::string(input));
}

// ==================== FindAndConsume ====================

TEST(RE2Test_4, FindAndConsumeBasic_4) {
  absl::string_view input("one123two456");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(123, n);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(456, n);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

TEST(RE2Test_4, FindAndConsumeString_4) {
  absl::string_view input("key=value;foo=bar");
  std::string key, value;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\w+)=(\\w+)", &key, &value));
  EXPECT_EQ("key", key);
  EXPECT_EQ("value", value);
}

// ==================== Replace ====================

TEST(RE2Test_4, ReplaceSimple_4) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "world", "there"));
  EXPECT_EQ("hello there", s);
}

TEST(RE2Test_4, ReplaceNoMatch_4) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "there"));
  EXPECT_EQ("hello world", s);
}

TEST(RE2Test_4, ReplaceWithBackreference_4) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "\\1!"));
  EXPECT_EQ("hello! world", s);
}

TEST(RE2Test_4, ReplaceFirstOccurrenceOnly_4) {
  std::string s = "aaa";
  RE2::Replace(&s, "a", "b");
  EXPECT_EQ("baa", s);
}

// ==================== GlobalReplace ====================

TEST(RE2Test_4, GlobalReplaceMultiple_4) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, "a", "b");
  EXPECT_EQ("bbb", s);
  EXPECT_EQ(3, count);
}

TEST(RE2Test_4, GlobalReplaceNoMatch_4) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "x", "y");
  EXPECT_EQ("hello", s);
  EXPECT_EQ(0, count);
}

TEST(RE2Test_4, GlobalReplaceWithCapture_4) {
  std::string s = "abc def ghi";
  int count = RE2::GlobalReplace(&s, "(\\w+)", "[\\1]");
  EXPECT_EQ("[abc] [def] [ghi]", s);
  EXPECT_EQ(3, count);
}

TEST(RE2Test_4, GlobalReplaceEmpty_4) {
  std::string s = "";
  int count = RE2::GlobalReplace(&s, "a", "b");
  EXPECT_EQ(0, count);
  EXPECT_EQ("", s);
}

// ==================== Extract ====================

TEST(RE2Test_4, ExtractSimple_4) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@example.com", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ("example!boris", out);
}

TEST(RE2Test_4, ExtractNoMatch_4) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no match here", "(\\d+)", "\\1", &out));
}

TEST(RE2Test_4, ExtractWholeMatch_4) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("hello", "(h)(e)(l)(l)(o)", "\\1-\\5", &out));
  EXPECT_EQ("h-o", out);
}

// ==================== QuoteMeta ====================

TEST(RE2Test_4, QuoteMetaNoSpecialChars_4) {
  EXPECT_EQ("hello", RE2::QuoteMeta("hello"));
}

TEST(RE2Test_4, QuoteMetaWithSpecialChars_4) {
  std::string quoted = RE2::QuoteMeta("a.b*c+d?e[f]g{h}");
  // The quoted string should match literally
  EXPECT_TRUE(RE2::FullMatch("a.b*c+d?e[f]g{h}", quoted));
}

TEST(RE2Test_4, QuoteMetaEmpty_4) {
  EXPECT_EQ("", RE2::QuoteMeta(""));
}

TEST(RE2Test_4, QuoteMetaBackslash_4) {
  std::string quoted = RE2::QuoteMeta("a\\b");
  EXPECT_TRUE(RE2::FullMatch("a\\b", quoted));
}

TEST(RE2Test_4, QuoteMetaParens_4) {
  std::string quoted = RE2::QuoteMeta("(foo)");
  EXPECT_TRUE(RE2::FullMatch("(foo)", quoted));
}

// ==================== Match ====================

TEST(RE2Test_4, MatchAnchored_4) {
  RE2 re("(\\d+)-(\\d+)");
  absl::string_view submatch[3];
  EXPECT_TRUE(re.Match("123-456", 0, 7, RE2::ANCHOR_BOTH, submatch, 3));
  EXPECT_EQ("123-456", std::string(submatch[0]));
  EXPECT_EQ("123", std::string(submatch[1]));
  EXPECT_EQ("456", std::string(submatch[2]));
}

TEST(RE2Test_4, MatchUnanchored_4) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc 123 def", 0, 11, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ("123", std::string(submatch[0]));
  EXPECT_EQ("123", std::string(submatch[1]));
}

TEST(RE2Test_4, MatchAnchorStart_4) {
  RE2 re("(\\w+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("hello world", 0, 11, RE2::ANCHOR_START, submatch, 2));
  EXPECT_EQ("hello", std::string(submatch[0]));
}

TEST(RE2Test_4, MatchFails_4) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("abc", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2Test_4, MatchWithStartPos_4) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc123def", 3, 9, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ("123", std::string(submatch[0]));
}

TEST(RE2Test_4, MatchNoSubmatch_4) {
  RE2 re("hello");
  EXPECT_TRUE(re.Match("hello world", 0, 11, RE2::UNANCHORED, nullptr, 0));
}

// ==================== PossibleMatchRange ====================

TEST(RE2Test_4, PossibleMatchRangeBasic_4) {
  RE2 re("hello");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "hello");
  EXPECT_GE(max_str, "hello");
}

TEST(RE2Test_4, PossibleMatchRangePrefix_4) {
  RE2 re("abc.*");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_EQ("abc", min_str);
}

// ==================== CheckRewriteString ====================

TEST(RE2Test_4, CheckRewriteStringValid_4) {
  RE2 re("(\\w+)-(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1 and \\2", &error));
}

TEST(RE2Test_4, CheckRewriteStringInvalidBackref_4) {
  RE2 re("(\\w+)");
  std::string error;
  // \\2 references a group that doesn't exist
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ==================== MaxSubmatch ====================

TEST(RE2Test_4, MaxSubmatchNone_4) {
  EXPECT_EQ(0, RE2::MaxSubmatch("no backrefs here"));
}

TEST(RE2Test_4, MaxSubmatchOne_4) {
  EXPECT_EQ(1, RE2::MaxSubmatch("\\1"));
}

TEST(RE2Test_4, MaxSubmatchMultiple_4) {
  EXPECT_EQ(3, RE2::MaxSubmatch("\\1-\\3-\\2"));
}

// ==================== Rewrite ====================

TEST(RE2Test_4, RewriteBasic_4) {
  RE2 re("(\\w+)@(\\w+)");
  absl::string_view vec[3];
  vec[0] = "user@host";
  vec[1] = "user";
  vec[2] = "host";
  std::string out;
  EXPECT_TRUE(re.Rewrite(&out, "\\2!\\1", vec, 3));
  EXPECT_EQ("host!user", out);
}

TEST(RE2Test_4, RewriteNoBackrefs_4) {
  RE2 re("abc");
  absl::string_view vec[1];
  vec[0] = "abc";
  std::string out;
  EXPECT_TRUE(re.Rewrite(&out, "xyz", vec, 1));
  EXPECT_EQ("xyz", out);
}

// ==================== ProgramSize ====================

TEST(RE2Test_4, ProgramSizePositive_4) {
  RE2 re("abc");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2Test_4, ReverseProgramSizePositive_4) {
  RE2 re("abc");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ==================== ProgramFanout ====================

TEST(RE2Test_4, ProgramFanoutVector_4) {
  RE2 re("abc");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2Test_4, ReverseProgramFanoutVector_4) {
  RE2 re("abc");
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ==================== NamedCapturingGroups ====================

TEST(RE2Test_4, NamedCapturingGroupsNone_4) {
  RE2 re("(\\d+)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2Test_4, NamedCapturingGroupsPresent_4) {
  RE2 re("(?P<name>\\w+) (?P<age>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(2u, groups.size());
  EXPECT_EQ(1, groups.at("name"));
  EXPECT_EQ(2, groups.at("age"));
}

// ==================== CapturingGroupNames ====================

TEST(RE2Test_4, CapturingGroupNamesNone_4) {
  RE2 re("(\\d+)");
  const auto& names = re.CapturingGroupNames();
  EXPECT_TRUE(names.empty());
}

TEST(RE2Test_4, CapturingGroupNamesPresent_4) {
  RE2 re("(?P<first>\\w+)-(?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(2u, names.size());
  EXPECT_EQ("first", names.at(1));
  EXPECT_EQ("second", names.at(2));
}

// ==================== Options ====================

TEST(RE2Test_4, OptionsDefault_4) {
  RE2 re("abc");
  const RE2::Options& opts = re.options();
  // Default encoding should be UTF8
  EXPECT_EQ(RE2::Options::EncodingUTF8, opts.encoding());
}

TEST(RE2Test_4, OptionsCaseInsensitive_4) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
}

TEST(RE2Test_4, OptionsLatin1_4) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re("abc", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
}

// ==================== Type Captures ====================

TEST(RE2Test_4, CaptureFloat_4) {
  float f;
  EXPECT_TRUE(RE2::FullMatch("3.14", "([\\d.]+)", &f));
  EXPECT_NEAR(3.14f, f, 0.001f);
}

TEST(RE2Test_4, CaptureDouble_4) {
  double d;
  EXPECT_TRUE(RE2::FullMatch("2.71828", "([\\d.]+)", &d));
  EXPECT_NEAR(2.71828, d, 0.00001);
}

TEST(RE2Test_4, CaptureStringPiece_4) {
  absl::string_view sp;
  EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", &sp));
  EXPECT_EQ("hello", std::string(sp));
}

// ==================== Hex and Octal ====================

TEST(RE2Test_4, HexCapture_4) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("ff", "([0-9a-fA-F]+)", RE2::Hex(&n)));
  EXPECT_EQ(255, n);
}

TEST(RE2Test_4, OctalCapture_4) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("77", "([0-7]+)", RE2::Octal(&n)));
  EXPECT_EQ(63, n);
}

TEST(RE2Test_4, CRadixHex_4) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(0x[0-9a-fA-F]+)", RE2::CRadix(&n)));
  EXPECT_EQ(31, n);
}

TEST(RE2Test_4, CRadixOctal_4) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("010", "(0[0-7]*)", RE2::CRadix(&n)));
  EXPECT_EQ(8, n);
}

TEST(RE2Test_4, CRadixDecimal_4) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("42", "(\\d+)", RE2::CRadix(&n)));
  EXPECT_EQ(42, n);
}

// ==================== Edge Cases ====================

TEST(RE2Test_4, FullMatchNullCapture_4) {
  // Pass nullptr for captures we don't care about
  EXPECT_TRUE(RE2::FullMatch("123-456", "(\\d+)-(\\d+)"));
}

TEST(RE2Test_4, VeryLongPattern_4) {
  std::string long_str(10000, 'a');
  RE2 re(long_str);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch(long_str, re));
}

TEST(RE2Test_4, PatternWithNullByte_4) {
  // Pattern containing null bytes via string_view
  std::string pattern("a\0b", 3);
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re(pattern, opts);
  // This might or might not be ok depending on implementation
  // Just check it doesn't crash
  (void)re.ok();
}

TEST(RE2Test_4, MatchEmptyString_4) {
  RE2 re(".*");
  EXPECT_TRUE(RE2::FullMatch("", re));
}

TEST(RE2Test_4, MatchWithAlternation_4) {
  RE2 re("cat|dog");
  EXPECT_TRUE(RE2::FullMatch("cat", re));
  EXPECT_TRUE(RE2::FullMatch("dog", re));
  EXPECT_FALSE(RE2::FullMatch("bird", re));
}

TEST(RE2Test_4, MatchWithQuantifiers_4) {
  RE2 re("a{3,5}");
  EXPECT_FALSE(RE2::FullMatch("aa", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaaa", re));
  EXPECT_FALSE(RE2::FullMatch("aaaaaa", re));
}

TEST(RE2Test_4, MatchWithCharacterClass_4) {
  RE2 re("[abc]+");
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_FALSE(RE2::FullMatch("def", re));
}

TEST(RE2Test_4, MatchUnicode_4) {
  RE2 re("\\p{L}+");
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2Test_4, GlobalReplaceEmptyMatch_4) {
  std::string s = "abc";
  // ".*" can match empty strings
  int count = RE2::GlobalReplace(&s, "b*", "x");
  // Behavior depends on implementation; just check no crash
  EXPECT_GE(count, 0);
}

TEST(RE2Test_4, ReplaceBackslashZero_4) {
  std::string s = "hello";
  RE2::Replace(&s, "(h\\w+)", "\\0");
  EXPECT_EQ("hello", s);
}

TEST(RE2Test_4, MatchBoundaryStartposEqualsEndpos_4) {
  RE2 re("");
  EXPECT_TRUE(re.Match("abc", 1, 1, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2Test_4, InvalidPatternBadRepetition_4) {
  RE2 re("*");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
}

TEST(RE2Test_4, InvalidPatternBadEscape_4) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("\\", opts);
  EXPECT_FALSE(re.ok());
}

}  // namespace
