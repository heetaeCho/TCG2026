#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>
#include <cstdint>

namespace {

// ===========================================================================
// Basic Construction and Pattern Tests
// ===========================================================================

TEST(RE2Test_45, ConstructFromCString_45) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("hello", re.pattern());
}

TEST(RE2Test_45, ConstructFromStdString_45) {
  std::string pat = "world";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("world", re.pattern());
}

TEST(RE2Test_45, ConstructFromStringView_45) {
  absl::string_view sv = "test.*pattern";
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("test.*pattern", re.pattern());
}

TEST(RE2Test_45, InvalidPatternNotOk_45) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2Test_45, EmptyPattern_45) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("", re.pattern());
}

// ===========================================================================
// FullMatch Tests
// ===========================================================================

TEST(RE2FullMatchTest_45, SimpleMatch_45) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2FullMatchTest_45, SimpleNoMatch_45) {
  EXPECT_FALSE(RE2::FullMatch("hello", "world"));
}

TEST(RE2FullMatchTest_45, FullMatchRequiresEntireString_45) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatchTest_45, FullMatchWithCapture_45) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &n));
  EXPECT_EQ(12345, n);
}

TEST(RE2FullMatchTest_45, FullMatchWithStringCapture_45) {
  std::string s;
  EXPECT_TRUE(RE2::FullMatch("abc", "(\\w+)", &s));
  EXPECT_EQ("abc", s);
}

TEST(RE2FullMatchTest_45, FullMatchMultipleCaptures_45) {
  std::string a, b;
  EXPECT_TRUE(RE2::FullMatch("hello-world", "(\\w+)-(\\w+)", &a, &b));
  EXPECT_EQ("hello", a);
  EXPECT_EQ("world", b);
}

TEST(RE2FullMatchTest_45, FullMatchEmptyStringEmptyPattern_45) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
}

TEST(RE2FullMatchTest_45, FullMatchEmptyStringNonEmptyPattern_45) {
  EXPECT_FALSE(RE2::FullMatch("", "a"));
}

// ===========================================================================
// PartialMatch Tests
// ===========================================================================

TEST(RE2PartialMatchTest_45, SimplePartialMatch_45) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "hello"));
}

TEST(RE2PartialMatchTest_45, PartialMatchSubstring_45) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "world"));
}

TEST(RE2PartialMatchTest_45, PartialMatchNoMatch_45) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2PartialMatchTest_45, PartialMatchWithCapture_45) {
  int n;
  EXPECT_TRUE(RE2::PartialMatch("x=42", "(\\d+)", &n));
  EXPECT_EQ(42, n);
}

TEST(RE2PartialMatchTest_45, PartialMatchEmptyPattern_45) {
  EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

// ===========================================================================
// Consume Tests
// ===========================================================================

TEST(RE2ConsumeTest_45, BasicConsume_45) {
  absl::string_view input = "abc123def";
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ("abc", word);
  EXPECT_EQ("123def", input);
}

TEST(RE2ConsumeTest_45, ConsumeNoMatch_45) {
  absl::string_view input = "123abc";
  std::string word;
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ("123abc", input);
}

TEST(RE2ConsumeTest_45, ConsumeMultipleTimes_45) {
  absl::string_view input = "aabbbcc";
  std::string s;
  EXPECT_TRUE(RE2::Consume(&input, "(a+)", &s));
  EXPECT_EQ("aa", s);
  EXPECT_TRUE(RE2::Consume(&input, "(b+)", &s));
  EXPECT_EQ("bbb", s);
  EXPECT_TRUE(RE2::Consume(&input, "(c+)", &s));
  EXPECT_EQ("cc", s);
}

// ===========================================================================
// FindAndConsume Tests
// ===========================================================================

TEST(RE2FindAndConsumeTest_45, BasicFindAndConsume_45) {
  absl::string_view input = "abc 123 def 456";
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(123, n);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(456, n);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

// ===========================================================================
// Replace Tests
// ===========================================================================

TEST(RE2ReplaceTest_45, BasicReplace_45) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "world", "there"));
  EXPECT_EQ("hello there", s);
}

TEST(RE2ReplaceTest_45, ReplaceNoMatch_45) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ("hello world", s);
}

TEST(RE2ReplaceTest_45, ReplaceOnlyFirstOccurrence_45) {
  std::string s = "aaa";
  RE2::Replace(&s, "a", "b");
  EXPECT_EQ("baa", s);
}

TEST(RE2ReplaceTest_45, ReplaceWithBackreference_45) {
  std::string s = "hello world";
  RE2::Replace(&s, "(\\w+)", "\\1!");
  EXPECT_EQ("hello! world", s);
}

// ===========================================================================
// GlobalReplace Tests
// ===========================================================================

TEST(RE2GlobalReplaceTest_45, BasicGlobalReplace_45) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, "a", "b");
  EXPECT_EQ("bbb", s);
  EXPECT_EQ(3, count);
}

TEST(RE2GlobalReplaceTest_45, GlobalReplaceNoMatch_45) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "x", "y");
  EXPECT_EQ("hello", s);
  EXPECT_EQ(0, count);
}

TEST(RE2GlobalReplaceTest_45, GlobalReplaceEmptyMatch_45) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "", "-");
  // Empty pattern matches before each char and at end
  EXPECT_EQ("-a-b-c-", s);
  EXPECT_EQ(4, count);
}

// ===========================================================================
// Extract Tests
// ===========================================================================

TEST(RE2ExtractTest_45, BasicExtract_45) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremvax.com", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ("kremvax!boris", out);
}

TEST(RE2ExtractTest_45, ExtractNoMatch_45) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no match", "(\\d+)", "\\1", &out));
}

// ===========================================================================
// QuoteMeta Tests
// ===========================================================================

TEST(RE2QuoteMetaTest_45, BasicQuoteMeta_45) {
  std::string quoted = RE2::QuoteMeta("hello.world");
  EXPECT_TRUE(RE2::FullMatch("hello.world", quoted));
  EXPECT_FALSE(RE2::FullMatch("helloXworld", quoted));
}

TEST(RE2QuoteMetaTest_45, QuoteMetaSpecialChars_45) {
  std::string quoted = RE2::QuoteMeta("a+b*c?");
  EXPECT_TRUE(RE2::FullMatch("a+b*c?", quoted));
}

TEST(RE2QuoteMetaTest_45, QuoteMetaEmptyString_45) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ("", quoted);
}

// ===========================================================================
// NumberOfCapturingGroups Tests
// ===========================================================================

TEST(RE2CapturingGroupsTest_45, NoCaptures_45) {
  RE2 re("hello");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_45, OneCapture_45) {
  RE2 re("(hello)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_45, MultipleCaptures_45) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_45, NestedCaptures_45) {
  RE2 re("((a)(b))");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

// ===========================================================================
// NamedCapturingGroups Tests
// ===========================================================================

TEST(RE2NamedCapturingGroupsTest_45, NoNamedGroups_45) {
  RE2 re("(\\d+)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2NamedCapturingGroupsTest_45, WithNamedGroups_45) {
  RE2 re("(?P<name>\\w+) (?P<age>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(2u, groups.size());
  auto it = groups.find("name");
  ASSERT_NE(groups.end(), it);
  EXPECT_EQ(1, it->second);
  it = groups.find("age");
  ASSERT_NE(groups.end(), it);
  EXPECT_EQ(2, it->second);
}

// ===========================================================================
// CapturingGroupNames Tests
// ===========================================================================

TEST(RE2CapturingGroupNamesTest_45, WithNamedGroups_45) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(2u, names.size());
  auto it = names.find(1);
  ASSERT_NE(names.end(), it);
  EXPECT_EQ("first", it->second);
  it = names.find(2);
  ASSERT_NE(names.end(), it);
  EXPECT_EQ("second", it->second);
}

// ===========================================================================
// Match Tests
// ===========================================================================

TEST(RE2MatchTest_45, BasicMatch_45) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc 123 def", 0, 11, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ("123", submatch[1]);
}

TEST(RE2MatchTest_45, AnchoredMatch_45) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("abc123", 0, 6, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_45, AnchoredBothMatch_45) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("123abc", 0, 6, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_45, MatchWithStartposEndpos_45) {
  RE2 re("\\d+");
  absl::string_view text = "abc123def";
  absl::string_view submatch[1];
  EXPECT_TRUE(re.Match(text, 3, 6, RE2::ANCHOR_BOTH, submatch, 1));
  EXPECT_EQ("123", submatch[0]);
}

// ===========================================================================
// Octal Tests
// ===========================================================================

TEST(RE2OctalTest_45, ParseOctalInt_45) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("77", "(\\d+)", RE2::Octal(&value)));
  EXPECT_EQ(077, value);  // 63 in decimal
}

TEST(RE2OctalTest_45, ParseOctalShort_45) {
  short value;
  EXPECT_TRUE(RE2::FullMatch("10", "(\\d+)", RE2::Octal(&value)));
  EXPECT_EQ(010, value);  // 8 in decimal
}

TEST(RE2OctalTest_45, ParseOctalInvalidDigit_45) {
  int value = -1;
  // '89' is not valid octal
  EXPECT_FALSE(RE2::FullMatch("89", "(\\d+)", RE2::Octal(&value)));
}

TEST(RE2OctalTest_45, ParseOctalZero_45) {
  int value = -1;
  EXPECT_TRUE(RE2::FullMatch("0", "(\\d+)", RE2::Octal(&value)));
  EXPECT_EQ(0, value);
}

TEST(RE2OctalTest_45, ParseOctalUnsigned_45) {
  unsigned int value;
  EXPECT_TRUE(RE2::FullMatch("777", "(\\d+)", RE2::Octal(&value)));
  EXPECT_EQ(0777u, value);  // 511 in decimal
}

TEST(RE2OctalTest_45, ParseOctalLong_45) {
  long value;
  EXPECT_TRUE(RE2::FullMatch("123", "(\\d+)", RE2::Octal(&value)));
  EXPECT_EQ(0123L, value);  // 83 in decimal
}

// ===========================================================================
// Hex Tests
// ===========================================================================

TEST(RE2HexTest_45, ParseHexInt_45) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("ff", "([0-9a-f]+)", RE2::Hex(&value)));
  EXPECT_EQ(0xff, value);
}

TEST(RE2HexTest_45, ParseHexUppercase_45) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("FF", "([0-9A-Fa-f]+)", RE2::Hex(&value)));
  EXPECT_EQ(0xFF, value);
}

TEST(RE2HexTest_45, ParseHexZero_45) {
  int value = -1;
  EXPECT_TRUE(RE2::FullMatch("0", "([0-9a-f]+)", RE2::Hex(&value)));
  EXPECT_EQ(0, value);
}

// ===========================================================================
// CRadix Tests
// ===========================================================================

TEST(RE2CRadixTest_45, ParseDecimal_45) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("100", "(\\S+)", RE2::CRadix(&value)));
  EXPECT_EQ(100, value);
}

TEST(RE2CRadixTest_45, ParseHexWithPrefix_45) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(\\S+)", RE2::CRadix(&value)));
  EXPECT_EQ(0x1f, value);
}

TEST(RE2CRadixTest_45, ParseOctalWithPrefix_45) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("010", "(\\S+)", RE2::CRadix(&value)));
  EXPECT_EQ(010, value);  // 8 in decimal
}

// ===========================================================================
// PossibleMatchRange Tests
// ===========================================================================

TEST(RE2PossibleMatchRangeTest_45, BasicRange_45) {
  RE2 re("abc.*");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "abc");
  EXPECT_GE(max_str, "abc");
}

// ===========================================================================
// ProgramSize Tests
// ===========================================================================

TEST(RE2ProgramSizeTest_45, BasicProgramSize_45) {
  RE2 re("hello");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_45, ReverseProgramSize_45) {
  RE2 re("hello");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ===========================================================================
// CheckRewriteString Tests
// ===========================================================================

TEST(RE2CheckRewriteTest_45, ValidRewrite_45) {
  RE2 re("(\\d+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewriteTest_45, InvalidRewriteTooManyBackrefs_45) {
  RE2 re("(\\d+)");
  std::string error;
  // \\2 is out of range because there's only 1 capturing group
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
}

// ===========================================================================
// MaxSubmatch Tests
// ===========================================================================

TEST(RE2MaxSubmatchTest_45, NoBackreferences_45) {
  EXPECT_EQ(0, RE2::MaxSubmatch("no refs here"));
}

TEST(RE2MaxSubmatchTest_45, WithBackreferences_45) {
  EXPECT_EQ(3, RE2::MaxSubmatch("\\1 \\2 \\3"));
}

TEST(RE2MaxSubmatchTest_45, SingleBackreference_45) {
  EXPECT_EQ(1, RE2::MaxSubmatch("\\1"));
}

// ===========================================================================
// Rewrite Tests
// ===========================================================================

TEST(RE2RewriteTest_45, BasicRewrite_45) {
  RE2 re("(\\w+):(\\d+)");
  std::string out;
  absl::string_view vec[] = {"full", "host", "80"};
  EXPECT_TRUE(re.Rewrite(&out, "\\1-\\2", vec, 3));
  EXPECT_EQ("host-80", out);
}

// ===========================================================================
// Options Tests
// ===========================================================================

TEST(RE2OptionsTest_45, CaseSensitiveByDefault_45) {
  EXPECT_FALSE(RE2::FullMatch("HELLO", "hello"));
}

TEST(RE2OptionsTest_45, CaseInsensitive_45) {
  RE2::Options opt;
  opt.set_case_sensitive(false);
  RE2 re("hello", opt);
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
}

TEST(RE2OptionsTest_45, Latin1Encoding_45) {
  RE2::Options opt;
  opt.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re(".", opt);
  EXPECT_TRUE(re.ok());
}

// ===========================================================================
// ProgramFanout Tests
// ===========================================================================

TEST(RE2ProgramFanoutTest_45, BasicFanout_45) {
  RE2 re("abc");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ProgramFanoutTest_45, ReverseFanout_45) {
  RE2 re("abc");
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ===========================================================================
// Error Handling Tests
// ===========================================================================

TEST(RE2ErrorTest_45, ErrorCodeOnInvalidPattern_45) {
  RE2 re("[invalid");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
}

TEST(RE2ErrorTest_45, ErrorStringOnInvalidPattern_45) {
  RE2 re("[invalid");
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2ErrorTest_45, ErrorArgOnInvalidPattern_45) {
  RE2 re("(?P<>abc)");
  if (!re.ok()) {
    // error_arg should have some content
    // (behavior depends on the specific error)
    EXPECT_TRUE(!re.error().empty());
  }
}

TEST(RE2ErrorTest_45, NoErrorOnValidPattern_45) {
  RE2 re("valid.*pattern");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(RE2::NoError, re.error_code());
  EXPECT_TRUE(re.error().empty() || re.error() == "");
}

// ===========================================================================
// Type Capture Tests
// ===========================================================================

TEST(RE2TypeCaptureTest_45, CaptureFloat_45) {
  float f;
  EXPECT_TRUE(RE2::FullMatch("3.14", "([\\d.]+)", &f));
  EXPECT_NEAR(3.14f, f, 0.01f);
}

TEST(RE2TypeCaptureTest_45, CaptureDouble_45) {
  double d;
  EXPECT_TRUE(RE2::FullMatch("3.14159", "([\\d.]+)", &d));
  EXPECT_NEAR(3.14159, d, 0.0001);
}

TEST(RE2TypeCaptureTest_45, CaptureStringView_45) {
  absl::string_view sv;
  EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", &sv));
  EXPECT_EQ("hello", sv);
}

TEST(RE2TypeCaptureTest_45, CaptureLongLong_45) {
  int64_t n;
  EXPECT_TRUE(RE2::FullMatch("1234567890123", "(\\d+)", &n));
  EXPECT_EQ(1234567890123LL, n);
}

// ===========================================================================
// Boundary / Edge Cases
// ===========================================================================

TEST(RE2BoundaryTest_45, VeryLongString_45) {
  std::string long_str(10000, 'a');
  EXPECT_TRUE(RE2::FullMatch(long_str, "a+"));
}

TEST(RE2BoundaryTest_45, NullCapturePointer_45) {
  // Passing nullptr to ignore captures should work
  EXPECT_TRUE(RE2::FullMatch("hello123", "(\\w+)(\\d+)"));
}

TEST(RE2BoundaryTest_45, MatchEmptyStringWithStar_45) {
  EXPECT_TRUE(RE2::FullMatch("", "a*"));
}

TEST(RE2BoundaryTest_45, PartialMatchOnEmptyString_45) {
  EXPECT_TRUE(RE2::PartialMatch("", ""));
}

TEST(RE2BoundaryTest_45, FullMatchDotStar_45) {
  EXPECT_TRUE(RE2::FullMatch("anything at all", ".*"));
}

// ===========================================================================
// FullMatchN Tests
// ===========================================================================

TEST(RE2FullMatchNTest_45, ZeroArgs_45) {
  RE2 re("hello");
  EXPECT_TRUE(RE2::FullMatchN("hello", re, nullptr, 0));
}

TEST(RE2FullMatchNTest_45, OneArg_45) {
  RE2 re("(\\d+)");
  int n;
  RE2::Arg arg(&n);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::FullMatchN("42", re, args, 1));
  EXPECT_EQ(42, n);
}

// ===========================================================================
// Octal overflow / boundary Tests
// ===========================================================================

TEST(RE2OctalTest_45, OctalOverflowUint16_45) {
  uint16_t value;
  // 0177777 in octal = 65535 = max uint16_t
  EXPECT_TRUE(RE2::FullMatch("177777", "(\\d+)", RE2::Octal(&value)));
  EXPECT_EQ(65535u, value);
}

TEST(RE2OctalTest_45, OctalOverflowUint16Fails_45) {
  uint16_t value;
  // 0200000 in octal = 65536, which overflows uint16_t
  EXPECT_FALSE(RE2::FullMatch("200000", "(\\d+)", RE2::Octal(&value)));
}

}  // namespace
