#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>
#include "re2/re2.h"

namespace {

// ==================== Construction and Basic Properties ====================

TEST(RE2Test_598, ConstructFromCString_598) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("hello", re.pattern());
}

TEST(RE2Test_598, ConstructFromString_598) {
  std::string pattern = "world";
  RE2 re(pattern);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("world", re.pattern());
}

TEST(RE2Test_598, ConstructFromStringView_598) {
  absl::string_view sv = "test.*pattern";
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("test.*pattern", re.pattern());
}

TEST(RE2Test_598, ConstructWithOptions_598) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("Hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("Hello", re.pattern());
  EXPECT_FALSE(re.options().case_sensitive());
}

TEST(RE2Test_598, InvalidPattern_598) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2Test_598, EmptyPattern_598) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("", re.pattern());
}

// ==================== Options ====================

TEST(RE2OptionsTest_598, DefaultOptions_598) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
  EXPECT_TRUE(opts.log_errors());
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_FALSE(opts.literal());
  EXPECT_FALSE(opts.never_nl());
  EXPECT_FALSE(opts.dot_nl());
  EXPECT_FALSE(opts.never_capture());
  EXPECT_FALSE(opts.perl_classes());
  EXPECT_FALSE(opts.word_boundary());
  EXPECT_FALSE(opts.one_line());
}

TEST(RE2OptionsTest_598, CannedOptionsPOSIX_598) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_598, CannedOptionsLatin1_598) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(RE2::Options::EncodingLatin1, opts.encoding());
}

TEST(RE2OptionsTest_598, CannedOptionsQuiet_598) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_598, SetAndGetMaxMem_598) {
  RE2::Options opts;
  opts.set_max_mem(1024 * 1024);
  EXPECT_EQ(1024 * 1024, opts.max_mem());
}

TEST(RE2OptionsTest_598, SetEncoding_598) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(RE2::Options::EncodingLatin1, opts.encoding());
}

TEST(RE2OptionsTest_598, SetLiteral_598) {
  RE2::Options opts;
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
}

TEST(RE2OptionsTest_598, SetDotNl_598) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
}

// ==================== FullMatch ====================

TEST(RE2FullMatchTest_598, SimpleMatch_598) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2FullMatchTest_598, NoMatch_598) {
  EXPECT_FALSE(RE2::FullMatch("hello", "world"));
}

TEST(RE2FullMatchTest_598, PartialDoesNotFullMatch_598) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatchTest_598, WithCapture_598) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &n));
  EXPECT_EQ(12345, n);
}

TEST(RE2FullMatchTest_598, WithStringCapture_598) {
  std::string s;
  EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", &s));
  EXPECT_EQ("hello", s);
}

TEST(RE2FullMatchTest_598, MultipleCaptures_598) {
  std::string a, b;
  EXPECT_TRUE(RE2::FullMatch("hello-world", "(\\w+)-(\\w+)", &a, &b));
  EXPECT_EQ("hello", a);
  EXPECT_EQ("world", b);
}

TEST(RE2FullMatchTest_598, EmptyString_598) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_TRUE(RE2::FullMatch("", ".*"));
}

TEST(RE2FullMatchTest_598, RegexMetaCharacters_598) {
  EXPECT_TRUE(RE2::FullMatch("a.b", "a\\.b"));
  EXPECT_FALSE(RE2::FullMatch("axb", "a\\.b"));
}

// ==================== PartialMatch ====================

TEST(RE2PartialMatchTest_598, SimplePartialMatch_598) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "hello"));
}

TEST(RE2PartialMatchTest_598, PartialMatchMiddle_598) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "lo wo"));
}

TEST(RE2PartialMatchTest_598, NoPartialMatch_598) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2PartialMatchTest_598, WithCapture_598) {
  int n;
  EXPECT_TRUE(RE2::PartialMatch("abc 123 def", "(\\d+)", &n));
  EXPECT_EQ(123, n);
}

TEST(RE2PartialMatchTest_598, EmptyPattern_598) {
  EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

// ==================== Consume ====================

TEST(RE2ConsumeTest_598, BasicConsume_598) {
  absl::string_view input = "abc123def";
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ("abc", word);
  EXPECT_EQ("123def", input);
}

TEST(RE2ConsumeTest_598, ConsumeMultipleTimes_598) {
  absl::string_view input = "aaa111bbb222";
  std::string s;
  int n;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &s));
  EXPECT_EQ("aaa", s);
  EXPECT_TRUE(RE2::Consume(&input, "(\\d+)", &n));
  EXPECT_EQ(111, n);
}

TEST(RE2ConsumeTest_598, ConsumeNoMatch_598) {
  absl::string_view input = "123abc";
  std::string s;
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &s));
  // Input should not be modified on failure
  EXPECT_EQ("123abc", input);
}

// ==================== FindAndConsume ====================

TEST(RE2FindAndConsumeTest_598, BasicFindAndConsume_598) {
  absl::string_view input = "abc 123 def 456";
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(123, n);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(456, n);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

// ==================== Replace ====================

TEST(RE2ReplaceTest_598, BasicReplace_598) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "world", "there"));
  EXPECT_EQ("hello there", s);
}

TEST(RE2ReplaceTest_598, ReplaceFirstOccurrenceOnly_598) {
  std::string s = "aaa bbb aaa";
  EXPECT_TRUE(RE2::Replace(&s, "aaa", "ccc"));
  EXPECT_EQ("ccc bbb aaa", s);
}

TEST(RE2ReplaceTest_598, ReplaceNoMatch_598) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ("hello world", s);
}

TEST(RE2ReplaceTest_598, ReplaceWithBackreference_598) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "[\\1]"));
  EXPECT_EQ("[hello] world", s);
}

// ==================== GlobalReplace ====================

TEST(RE2GlobalReplaceTest_598, BasicGlobalReplace_598) {
  std::string s = "aaa bbb aaa";
  int count = RE2::GlobalReplace(&s, "aaa", "ccc");
  EXPECT_EQ(2, count);
  EXPECT_EQ("ccc bbb ccc", s);
}

TEST(RE2GlobalReplaceTest_598, NoMatch_598) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ(0, count);
  EXPECT_EQ("hello", s);
}

TEST(RE2GlobalReplaceTest_598, ReplaceEmptyMatch_598) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "", "-");
  // Empty pattern matches before each character and at end
  EXPECT_GT(count, 0);
}

// ==================== Extract ====================

TEST(RE2ExtractTest_598, BasicExtract_598) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@google.com", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ("google!boris", out);
}

TEST(RE2ExtractTest_598, ExtractNoMatch_598) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-at-sign", "(.*)@([^.]*)", "\\2!\\1", &out));
}

// ==================== QuoteMeta ====================

TEST(RE2QuoteMetaTest_598, SimpleString_598) {
  EXPECT_EQ("hello", RE2::QuoteMeta("hello"));
}

TEST(RE2QuoteMetaTest_598, MetaCharacters_598) {
  std::string quoted = RE2::QuoteMeta("a.b+c*d?e");
  RE2 re(quoted);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a.b+c*d?e", re));
  EXPECT_FALSE(RE2::FullMatch("axb+c*d?e", re));
}

TEST(RE2QuoteMetaTest_598, EmptyString_598) {
  EXPECT_EQ("", RE2::QuoteMeta(""));
}

TEST(RE2QuoteMetaTest_598, SpecialCharsQuoted_598) {
  std::string quoted = RE2::QuoteMeta("\\d+");
  EXPECT_TRUE(RE2::FullMatch("\\d+", quoted));
}

// ==================== NumberOfCapturingGroups ====================

TEST(RE2CapturingGroupsTest_598, NoGroups_598) {
  RE2 re("hello");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_598, OneGroup_598) {
  RE2 re("(hello)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_598, MultipleGroups_598) {
  RE2 re("(\\w+)-(\\d+)-(\\w+)");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_598, NonCapturingGroup_598) {
  RE2 re("(?:hello)(world)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

// ==================== NamedCapturingGroups ====================

TEST(RE2NamedGroupsTest_598, NoNamedGroups_598) {
  RE2 re("(\\w+)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2NamedGroupsTest_598, WithNamedGroups_598) {
  RE2 re("(?P<first>\\w+)-(?P<second>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(2u, groups.size());
  EXPECT_EQ(1, groups.at("first"));
  EXPECT_EQ(2, groups.at("second"));
}

// ==================== CapturingGroupNames ====================

TEST(RE2GroupNamesTest_598, WithNamedGroups_598) {
  RE2 re("(?P<name>\\w+)@(?P<domain>\\w+)");
  EXPECT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(2u, names.size());
  EXPECT_EQ("name", names.at(1));
  EXPECT_EQ("domain", names.at(2));
}

// ==================== Match ====================

TEST(RE2MatchTest_598, BasicMatch_598) {
  RE2 re("(\\w+)");
  EXPECT_TRUE(re.ok());
  absl::string_view text = "hello world";
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ("hello", submatch[0]);
  EXPECT_EQ("hello", submatch[1]);
}

TEST(RE2MatchTest_598, AnchoredStart_598) {
  RE2 re("\\d+");
  absl::string_view text = "abc123";
  EXPECT_FALSE(re.Match(text, 0, text.size(), RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_598, AnchoredBoth_598) {
  RE2 re("\\d+");
  absl::string_view text = "123";
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_598, AnchoredBothFail_598) {
  RE2 re("\\d+");
  absl::string_view text = "123abc";
  EXPECT_FALSE(re.Match(text, 0, text.size(), RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_598, MatchWithStartpos_598) {
  RE2 re("\\d+");
  absl::string_view text = "abc123def";
  absl::string_view submatch[1];
  EXPECT_TRUE(re.Match(text, 3, text.size(), RE2::UNANCHORED, submatch, 1));
  EXPECT_EQ("123", submatch[0]);
}

TEST(RE2MatchTest_598, MatchWithEndpos_598) {
  RE2 re("\\d+");
  absl::string_view text = "abc123def";
  // Search only in "abc1"
  absl::string_view submatch[1];
  EXPECT_TRUE(re.Match(text, 0, 4, RE2::UNANCHORED, submatch, 1));
  EXPECT_EQ("1", submatch[0]);
}

TEST(RE2MatchTest_598, NoSubmatch_598) {
  RE2 re("hello");
  absl::string_view text = "hello world";
  EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::UNANCHORED, nullptr, 0));
}

// ==================== CheckRewriteString ====================

TEST(RE2CheckRewriteTest_598, ValidRewrite_598) {
  RE2 re("(\\w+)-(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1 and \\2", &error));
}

TEST(RE2CheckRewriteTest_598, InvalidRewrite_598) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ==================== MaxSubmatch ====================

TEST(RE2MaxSubmatchTest_598, NoBackreferences_598) {
  EXPECT_EQ(0, RE2::MaxSubmatch("no backrefs"));
}

TEST(RE2MaxSubmatchTest_598, SingleBackreference_598) {
  EXPECT_EQ(1, RE2::MaxSubmatch("\\1"));
}

TEST(RE2MaxSubmatchTest_598, MultipleBackreferences_598) {
  EXPECT_EQ(3, RE2::MaxSubmatch("\\1 \\2 \\3"));
}

// ==================== ProgramSize ====================

TEST(RE2ProgramSizeTest_598, BasicProgramSize_598) {
  RE2 re("hello");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_598, ComplexPatternLarger_598) {
  RE2 simple("a");
  RE2 complex("(a|b|c|d|e)(f|g|h|i|j)");
  EXPECT_GT(complex.ProgramSize(), simple.ProgramSize());
}

// ==================== ReverseProgramSize ====================

TEST(RE2ReverseProgramSizeTest_598, BasicReverseProgramSize_598) {
  RE2 re("hello");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ==================== ProgramFanout ====================

TEST(RE2ProgramFanoutTest_598, BasicFanout_598) {
  RE2 re("(a|b)c");
  std::vector<int> histogram;
  int fanout = re.ProgramFanout(&histogram);
  EXPECT_GE(fanout, 0);
}

// ==================== PossibleMatchRange ====================

TEST(RE2PossibleMatchRangeTest_598, BasicRange_598) {
  RE2 re("hello");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "hello");
  EXPECT_GE(max_str, "hello");
}

TEST(RE2PossibleMatchRangeTest_598, WildcardPattern_598) {
  RE2 re(".*");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
}

// ==================== Rewrite ====================

TEST(RE2RewriteTest_598, BasicRewrite_598) {
  RE2 re("(\\w+)@(\\w+)");
  std::string out;
  absl::string_view vec[] = {"boris@google", "boris", "google"};
  EXPECT_TRUE(re.Rewrite(&out, "\\2!\\1", vec, 3));
  EXPECT_EQ("google!boris", out);
}

// ==================== Error Code ====================

TEST(RE2ErrorCodeTest_598, NoError_598) {
  RE2 re("valid");
  EXPECT_EQ(RE2::NoError, re.error_code());
}

TEST(RE2ErrorCodeTest_598, ErrorOnBadPattern_598) {
  RE2 re("(");
  EXPECT_NE(RE2::NoError, re.error_code());
}

// ==================== Literal Option ====================

TEST(RE2LiteralTest_598, LiteralMatchesMetaCharacters_598) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

// ==================== Case Insensitive ====================

TEST(RE2CaseInsensitiveTest_598, CaseInsensitiveMatch_598) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

// ==================== Hex, Octal, CRadix Capture ====================

TEST(RE2HexTest_598, HexCapture_598) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "0x([0-9a-fA-F]+)", RE2::Hex(&v)));
  EXPECT_EQ(31, v);
}

TEST(RE2OctalTest_598, OctalCapture_598) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("77", "(\\d+)", RE2::Octal(&v)));
  EXPECT_EQ(63, v);
}

TEST(RE2CRadixTest_598, CRadixHex_598) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(0x[0-9a-fA-F]+)", RE2::CRadix(&v)));
  EXPECT_EQ(31, v);
}

TEST(RE2CRadixTest_598, CRadixDecimal_598) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("100", "(\\d+)", RE2::CRadix(&v)));
  EXPECT_EQ(100, v);
}

TEST(RE2CRadixTest_598, CRadixOctal_598) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("010", "(0\\d+)", RE2::CRadix(&v)));
  EXPECT_EQ(8, v);
}

// ==================== NeverCapture Option ====================

TEST(RE2NeverCaptureTest_598, NeverCapture_598) {
  RE2::Options opts;
  opts.set_never_capture(true);
  RE2 re("(\\d+)", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

// ==================== FullMatchN / PartialMatchN ====================

TEST(RE2FullMatchNTest_598, NoArgs_598) {
  RE2 re("hello");
  EXPECT_TRUE(RE2::FullMatchN("hello", re, nullptr, 0));
  EXPECT_FALSE(RE2::FullMatchN("world", re, nullptr, 0));
}

TEST(RE2PartialMatchNTest_598, NoArgs_598) {
  RE2 re("ell");
  EXPECT_TRUE(RE2::PartialMatchN("hello", re, nullptr, 0));
  EXPECT_FALSE(RE2::PartialMatchN("world", re, nullptr, 0));
}

// ==================== Boundary: Large Input ====================

TEST(RE2BoundaryTest_598, LargeInput_598) {
  std::string big(10000, 'a');
  EXPECT_TRUE(RE2::FullMatch(big, "a+"));
  EXPECT_FALSE(RE2::FullMatch(big, "b+"));
}

// ==================== Various Data Types for Capture ====================

TEST(RE2CaptureTypesTest_598, CaptureFloat_598) {
  float f;
  EXPECT_TRUE(RE2::FullMatch("3.14", "([\\d.]+)", &f));
  EXPECT_NEAR(3.14f, f, 0.01f);
}

TEST(RE2CaptureTypesTest_598, CaptureDouble_598) {
  double d;
  EXPECT_TRUE(RE2::FullMatch("3.14159", "([\\d.]+)", &d));
  EXPECT_NEAR(3.14159, d, 0.0001);
}

TEST(RE2CaptureTypesTest_598, CaptureStringPiece_598) {
  absl::string_view sp;
  EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", &sp));
  EXPECT_EQ("hello", sp);
}

TEST(RE2CaptureTypesTest_598, CaptureLong_598) {
  long v;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &v));
  EXPECT_EQ(12345L, v);
}

// ==================== ConsumeN and FindAndConsumeN ====================

TEST(RE2ConsumeNTest_598, BasicConsumeN_598) {
  RE2 re("(\\d+)");
  absl::string_view input = "123abc";
  int val;
  const RE2::Arg arg(&val);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::ConsumeN(&input, re, args, 1));
  EXPECT_EQ(123, val);
  EXPECT_EQ("abc", input);
}

TEST(RE2FindAndConsumeNTest_598, BasicFindAndConsumeN_598) {
  RE2 re("(\\d+)");
  absl::string_view input = "abc123def";
  int val;
  const RE2::Arg arg(&val);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, args, 1));
  EXPECT_EQ(123, val);
}

}  // namespace
