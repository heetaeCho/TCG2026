#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>
#include <cstdint>

using namespace re2;

// ============================================================
// Basic Construction Tests
// ============================================================

TEST(RE2BasicTest_43, ConstructFromCString_43) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("hello", re.pattern());
}

TEST(RE2BasicTest_43, ConstructFromStdString_43) {
  std::string pattern = "world";
  RE2 re(pattern);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("world", re.pattern());
}

TEST(RE2BasicTest_43, ConstructFromStringView_43) {
  absl::string_view sv = "test.*pattern";
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("test.*pattern", re.pattern());
}

TEST(RE2BasicTest_43, InvalidPattern_43) {
  RE2 re("[invalid");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2BasicTest_43, EmptyPattern_43) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("", re.pattern());
}

// ============================================================
// FullMatch Tests
// ============================================================

TEST(RE2FullMatchTest_43, SimpleMatch_43) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2FullMatchTest_43, SimpleNoMatch_43) {
  EXPECT_FALSE(RE2::FullMatch("hello", "world"));
}

TEST(RE2FullMatchTest_43, FullMatchRequiresEntireString_43) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatchTest_43, FullMatchWithCapture_43) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &n));
  EXPECT_EQ(12345, n);
}

TEST(RE2FullMatchTest_43, FullMatchWithStringCapture_43) {
  std::string s;
  EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", &s));
  EXPECT_EQ("hello", s);
}

TEST(RE2FullMatchTest_43, FullMatchMultipleCaptures_43) {
  std::string first, second;
  EXPECT_TRUE(RE2::FullMatch("hello-world", "(\\w+)-(\\w+)", &first, &second));
  EXPECT_EQ("hello", first);
  EXPECT_EQ("world", second);
}

TEST(RE2FullMatchTest_43, FullMatchEmptyString_43) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_TRUE(RE2::FullMatch("", ".*"));
}

TEST(RE2FullMatchTest_43, FullMatchWithDot_43) {
  EXPECT_TRUE(RE2::FullMatch("a", "."));
  EXPECT_FALSE(RE2::FullMatch("ab", "."));
}

// ============================================================
// PartialMatch Tests
// ============================================================

TEST(RE2PartialMatchTest_43, SimplePartialMatch_43) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "hello"));
}

TEST(RE2PartialMatchTest_43, PartialMatchAnywhere_43) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "world"));
}

TEST(RE2PartialMatchTest_43, PartialMatchNoMatch_43) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2PartialMatchTest_43, PartialMatchWithCapture_43) {
  int val;
  EXPECT_TRUE(RE2::PartialMatch("abc 42 def", "(\\d+)", &val));
  EXPECT_EQ(42, val);
}

TEST(RE2PartialMatchTest_43, PartialMatchEmptyPattern_43) {
  EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

// ============================================================
// Consume Tests
// ============================================================

TEST(RE2ConsumeTest_43, BasicConsume_43) {
  absl::string_view input = "abc123def";
  std::string letters;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &letters));
  EXPECT_EQ("abc", letters);
  EXPECT_EQ("123def", input);
}

TEST(RE2ConsumeTest_43, ConsumeNoMatch_43) {
  absl::string_view input = "123abc";
  std::string letters;
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &letters));
  EXPECT_EQ("123abc", input);
}

TEST(RE2ConsumeTest_43, ConsumeMultipleTimes_43) {
  absl::string_view input = "aabbcc";
  std::string s;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]{2})", &s));
  EXPECT_EQ("aa", s);
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]{2})", &s));
  EXPECT_EQ("bb", s);
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]{2})", &s));
  EXPECT_EQ("cc", s);
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]{2})", &s));
}

// ============================================================
// FindAndConsume Tests
// ============================================================

TEST(RE2FindAndConsumeTest_43, BasicFindAndConsume_43) {
  absl::string_view input = "abc 123 def 456";
  int val;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &val));
  EXPECT_EQ(123, val);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &val));
  EXPECT_EQ(456, val);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &val));
}

TEST(RE2FindAndConsumeTest_43, FindAndConsumeNoMatch_43) {
  absl::string_view input = "no numbers here";
  int val;
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &val));
}

// ============================================================
// Replace Tests
// ============================================================

TEST(RE2ReplaceTest_43, BasicReplace_43) {
  std::string str = "hello world";
  EXPECT_TRUE(RE2::Replace(&str, "world", "there"));
  EXPECT_EQ("hello there", str);
}

TEST(RE2ReplaceTest_43, ReplaceNoMatch_43) {
  std::string str = "hello world";
  EXPECT_FALSE(RE2::Replace(&str, "xyz", "there"));
  EXPECT_EQ("hello world", str);
}

TEST(RE2ReplaceTest_43, ReplaceOnlyFirst_43) {
  std::string str = "aaa";
  EXPECT_TRUE(RE2::Replace(&str, "a", "b"));
  EXPECT_EQ("baa", str);
}

TEST(RE2ReplaceTest_43, ReplaceWithBackreference_43) {
  std::string str = "hello world";
  EXPECT_TRUE(RE2::Replace(&str, "(\\w+)", "\\1!"));
  EXPECT_EQ("hello! world", str);
}

// ============================================================
// GlobalReplace Tests
// ============================================================

TEST(RE2GlobalReplaceTest_43, BasicGlobalReplace_43) {
  std::string str = "aaa";
  int count = RE2::GlobalReplace(&str, "a", "b");
  EXPECT_EQ("bbb", str);
  EXPECT_EQ(3, count);
}

TEST(RE2GlobalReplaceTest_43, GlobalReplaceNoMatch_43) {
  std::string str = "hello";
  int count = RE2::GlobalReplace(&str, "x", "y");
  EXPECT_EQ("hello", str);
  EXPECT_EQ(0, count);
}

TEST(RE2GlobalReplaceTest_43, GlobalReplaceEmptyMatch_43) {
  std::string str = "abc";
  int count = RE2::GlobalReplace(&str, "b", "");
  EXPECT_EQ("ac", str);
  EXPECT_EQ(1, count);
}

// ============================================================
// Extract Tests
// ============================================================

TEST(RE2ExtractTest_43, BasicExtract_43) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ("kremlin!boris", out);
}

TEST(RE2ExtractTest_43, ExtractNoMatch_43) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no match", "(\\d+)", "\\1", &out));
}

// ============================================================
// QuoteMeta Tests
// ============================================================

TEST(RE2QuoteMetaTest_43, BasicQuoteMeta_43) {
  std::string quoted = RE2::QuoteMeta("hello.world");
  RE2 re(quoted);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello.world", re));
  EXPECT_FALSE(RE2::FullMatch("helloXworld", re));
}

TEST(RE2QuoteMetaTest_43, QuoteMetaSpecialChars_43) {
  std::string quoted = RE2::QuoteMeta("a+b*c?d");
  EXPECT_TRUE(RE2::FullMatch("a+b*c?d", quoted));
  EXPECT_FALSE(RE2::FullMatch("aaabbbccd", quoted));
}

TEST(RE2QuoteMetaTest_43, QuoteMetaEmpty_43) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ("", quoted);
}

// ============================================================
// NumberOfCapturingGroups Tests
// ============================================================

TEST(RE2CapturingGroupsTest_43, NoCapturingGroups_43) {
  RE2 re("hello");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_43, OneCapturingGroup_43) {
  RE2 re("(hello)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_43, MultipleCapturingGroups_43) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_43, NonCapturingGroup_43) {
  RE2 re("(?:hello)(world)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

// ============================================================
// NamedCapturingGroups Tests
// ============================================================

TEST(RE2NamedCapturingGroupsTest_43, NoNamedGroups_43) {
  RE2 re("(hello)(world)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2NamedCapturingGroupsTest_43, WithNamedGroups_43) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(2u, groups.size());
  EXPECT_EQ(1, groups.at("first"));
  EXPECT_EQ(2, groups.at("second"));
}

// ============================================================
// CapturingGroupNames Tests
// ============================================================

TEST(RE2CapturingGroupNamesTest_43, NoNames_43) {
  RE2 re("(hello)");
  const auto& names = re.CapturingGroupNames();
  EXPECT_TRUE(names.empty());
}

TEST(RE2CapturingGroupNamesTest_43, WithNames_43) {
  RE2 re("(?P<name>\\w+)");
  EXPECT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(1u, names.size());
  EXPECT_EQ("name", names.at(1));
}

// ============================================================
// Match Tests
// ============================================================

TEST(RE2MatchTest_43, BasicMatch_43) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc 123 def", 0, 11, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ("123", submatch[0]);
  EXPECT_EQ("123", submatch[1]);
}

TEST(RE2MatchTest_43, AnchoredMatch_43) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("abc 123", 0, 7, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_TRUE(re.Match("123 abc", 0, 7, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_43, AnchoredBothMatch_43) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("123 abc", 0, 7, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_43, MatchWithStartPos_43) {
  RE2 re("\\d+");
  absl::string_view submatch[1];
  EXPECT_TRUE(re.Match("abc 123 def", 4, 11, RE2::UNANCHORED, submatch, 1));
  EXPECT_EQ("123", submatch[0]);
}

TEST(RE2MatchTest_43, MatchNoSubmatch_43) {
  RE2 re("hello");
  EXPECT_TRUE(re.Match("say hello world", 0, 15, RE2::UNANCHORED, nullptr, 0));
}

// ============================================================
// PossibleMatchRange Tests
// ============================================================

TEST(RE2PossibleMatchRangeTest_43, BasicRange_43) {
  RE2 re("hello");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "hello");
  EXPECT_GE(max_str, "hello");
}

// ============================================================
// ProgramSize Tests
// ============================================================

TEST(RE2ProgramSizeTest_43, ValidPattern_43) {
  RE2 re("hello");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_43, ComplexPattern_43) {
  RE2 re("(a|b|c)+d*[e-g]{2,5}");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_43, ReverseProgramSize_43) {
  RE2 re("hello");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ============================================================
// CheckRewriteString Tests
// ============================================================

TEST(RE2CheckRewriteTest_43, ValidRewrite_43) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewriteTest_43, InvalidRewrite_43) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ============================================================
// MaxSubmatch Tests
// ============================================================

TEST(RE2MaxSubmatchTest_43, NoBackreferences_43) {
  EXPECT_EQ(0, RE2::MaxSubmatch("no backrefs"));
}

TEST(RE2MaxSubmatchTest_43, SingleBackreference_43) {
  EXPECT_EQ(1, RE2::MaxSubmatch("\\1"));
}

TEST(RE2MaxSubmatchTest_43, MultipleBackreferences_43) {
  EXPECT_EQ(3, RE2::MaxSubmatch("\\1 \\2 \\3"));
}

// ============================================================
// CRadix Tests
// ============================================================

TEST(RE2CRadixTest_43, ParseDecimal_43) {
  int val = 0;
  EXPECT_TRUE(RE2::FullMatch("42", "(.*)", RE2::CRadix(&val)));
  EXPECT_EQ(42, val);
}

TEST(RE2CRadixTest_43, ParseHexWithPrefix_43) {
  int val = 0;
  EXPECT_TRUE(RE2::FullMatch("0x1a", "(.*)", RE2::CRadix(&val)));
  EXPECT_EQ(0x1a, val);
}

TEST(RE2CRadixTest_43, ParseOctalWithPrefix_43) {
  int val = 0;
  EXPECT_TRUE(RE2::FullMatch("010", "(.*)", RE2::CRadix(&val)));
  EXPECT_EQ(010, val);
}

// ============================================================
// Hex Tests
// ============================================================

TEST(RE2HexTest_43, ParseHex_43) {
  int val = 0;
  EXPECT_TRUE(RE2::FullMatch("1a", "(.*)", RE2::Hex(&val)));
  EXPECT_EQ(0x1a, val);
}

TEST(RE2HexTest_43, ParseHexUppercase_43) {
  int val = 0;
  EXPECT_TRUE(RE2::FullMatch("FF", "(.*)", RE2::Hex(&val)));
  EXPECT_EQ(0xFF, val);
}

// ============================================================
// Octal Tests
// ============================================================

TEST(RE2OctalTest_43, ParseOctal_43) {
  int val = 0;
  EXPECT_TRUE(RE2::FullMatch("77", "(.*)", RE2::Octal(&val)));
  EXPECT_EQ(077, val);
}

TEST(RE2OctalTest_43, ParseOctalInvalid_43) {
  int val = 0;
  EXPECT_FALSE(RE2::FullMatch("89", "(.*)", RE2::Octal(&val)));
}

// ============================================================
// Options Tests
// ============================================================

TEST(RE2OptionsTest_43, CaseSensitiveByDefault_43) {
  RE2 re("hello");
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
}

TEST(RE2OptionsTest_43, CaseInsensitive_43) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HeLLo", re));
}

TEST(RE2OptionsTest_43, DotNL_43) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re(".", opts);
  EXPECT_TRUE(RE2::FullMatch("\n", re));
}

TEST(RE2OptionsTest_43, DotNLDefault_43) {
  RE2 re(".");
  EXPECT_FALSE(RE2::FullMatch("\n", re));
}

// ============================================================
// Rewrite Tests
// ============================================================

TEST(RE2RewriteTest_43, BasicRewrite_43) {
  RE2 re("(\\w+) (\\w+)");
  std::string out;
  absl::string_view vec[3];
  vec[0] = "hello world";
  vec[1] = "hello";
  vec[2] = "world";
  EXPECT_TRUE(re.Rewrite(&out, "\\2 \\1", vec, 3));
  EXPECT_EQ("world hello", out);
}

// ============================================================
// ProgramFanout Tests
// ============================================================

TEST(RE2ProgramFanoutTest_43, BasicFanout_43) {
  RE2 re("(a|b)c");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ProgramFanoutTest_43, ReverseFanout_43) {
  RE2 re("(a|b)c");
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ============================================================
// Edge Cases and Error Cases
// ============================================================

TEST(RE2EdgeCaseTest_43, MatchEmptyStringEmptyPattern_43) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
}

TEST(RE2EdgeCaseTest_43, MatchEmptyStringStarPattern_43) {
  EXPECT_TRUE(RE2::FullMatch("", "a*"));
}

TEST(RE2EdgeCaseTest_43, VeryLongString_43) {
  std::string long_str(10000, 'a');
  EXPECT_TRUE(RE2::FullMatch(long_str, "a+"));
}

TEST(RE2EdgeCaseTest_43, UnicodeInPattern_43) {
  RE2 re("\\p{L}+");
  EXPECT_TRUE(re.ok());
}

TEST(RE2EdgeCaseTest_43, FullMatchNWithNullArgs_43) {
  EXPECT_TRUE(RE2::FullMatchN("hello", RE2("hello"), nullptr, 0));
}

TEST(RE2EdgeCaseTest_43, PartialMatchNWithNullArgs_43) {
  EXPECT_TRUE(RE2::PartialMatchN("hello world", RE2("hello"), nullptr, 0));
}

TEST(RE2EdgeCaseTest_43, ReplaceEmptyPattern_43) {
  std::string str = "abc";
  RE2::Replace(&str, "", "x");
  // Empty pattern matches at beginning
  EXPECT_EQ("xabc", str);
}

TEST(RE2EdgeCaseTest_43, GlobalReplaceEmptyPattern_43) {
  std::string str = "ab";
  int count = RE2::GlobalReplace(&str, "", "x");
  // Empty pattern matches at every position
  EXPECT_GT(count, 0);
}

// ============================================================
// Type-specific capture tests
// ============================================================

TEST(RE2TypeCaptureTest_43, CaptureFloat_43) {
  float val = 0.0f;
  EXPECT_TRUE(RE2::FullMatch("3.14", "([\\d.]+)", &val));
  EXPECT_NEAR(3.14f, val, 0.001f);
}

TEST(RE2TypeCaptureTest_43, CaptureDouble_43) {
  double val = 0.0;
  EXPECT_TRUE(RE2::FullMatch("3.14159", "([\\d.]+)", &val));
  EXPECT_NEAR(3.14159, val, 0.00001);
}

TEST(RE2TypeCaptureTest_43, CaptureStringView_43) {
  absl::string_view sv;
  EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", &sv));
  EXPECT_EQ("hello", sv);
}

TEST(RE2TypeCaptureTest_43, CaptureLong_43) {
  long val = 0;
  EXPECT_TRUE(RE2::FullMatch("123456", "(\\d+)", &val));
  EXPECT_EQ(123456L, val);
}

TEST(RE2TypeCaptureTest_43, CaptureLongLong_43) {
  long long val = 0;
  EXPECT_TRUE(RE2::FullMatch("9999999999", "(\\d+)", &val));
  EXPECT_EQ(9999999999LL, val);
}

TEST(RE2TypeCaptureTest_43, CaptureOverflowInt_43) {
  int val = 0;
  // Value too large for int
  EXPECT_FALSE(RE2::FullMatch("99999999999999999999", "(\\d+)", &val));
}

// ============================================================
// Error code tests
// ============================================================

TEST(RE2ErrorCodeTest_43, NoError_43) {
  RE2 re("valid");
  EXPECT_EQ(RE2::NoError, re.error_code());
  EXPECT_TRUE(re.error().empty());
}

TEST(RE2ErrorCodeTest_43, ErrorOnBadPattern_43) {
  RE2 re("(unclosed");
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}
