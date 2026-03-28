#include "re2/re2.h"

#include <string>
#include <map>
#include <vector>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

// ==================== PartialMatch Tests ====================

TEST(RE2PartialMatchTest_8, SimpleMatch_8) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", RE2("llo")));
}

TEST(RE2PartialMatchTest_8, NoMatch_8) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", RE2("xyz")));
}

TEST(RE2PartialMatchTest_8, MatchAtBeginning_8) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", RE2("^hello")));
}

TEST(RE2PartialMatchTest_8, MatchAtEnd_8) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", RE2("world$")));
}

TEST(RE2PartialMatchTest_8, EmptyPattern_8) {
  EXPECT_TRUE(RE2::PartialMatch("hello", RE2("")));
}

TEST(RE2PartialMatchTest_8, EmptyText_8) {
  EXPECT_FALSE(RE2::PartialMatch("", RE2("hello")));
}

TEST(RE2PartialMatchTest_8, EmptyTextEmptyPattern_8) {
  EXPECT_TRUE(RE2::PartialMatch("", RE2("")));
}

TEST(RE2PartialMatchTest_8, CaptureGroup_8) {
  std::string captured;
  EXPECT_TRUE(RE2::PartialMatch("hello world 123", RE2("(\\d+)"), &captured));
  EXPECT_EQ("123", captured);
}

TEST(RE2PartialMatchTest_8, MultipleCaptureGroups_8) {
  std::string s1, s2;
  EXPECT_TRUE(RE2::PartialMatch("abc=def", RE2("(\\w+)=(\\w+)"), &s1, &s2));
  EXPECT_EQ("abc", s1);
  EXPECT_EQ("def", s2);
}

TEST(RE2PartialMatchTest_8, IntCapture_8) {
  int value;
  EXPECT_TRUE(RE2::PartialMatch("age is 42 years", RE2("(\\d+)"), &value));
  EXPECT_EQ(42, value);
}

TEST(RE2PartialMatchTest_8, PartialMatchDoesNotRequireFullMatch_8) {
  EXPECT_TRUE(RE2::PartialMatch("abcdef", RE2("cde")));
}

TEST(RE2PartialMatchTest_8, CaseSensitiveByDefault_8) {
  EXPECT_FALSE(RE2::PartialMatch("Hello", RE2("hello")));
}

TEST(RE2PartialMatchTest_8, CaseInsensitiveWithFlag_8) {
  EXPECT_TRUE(RE2::PartialMatch("Hello", RE2("(?i)hello")));
}

// ==================== FullMatch Tests ====================

TEST(RE2FullMatchTest_8, SimpleFullMatch_8) {
  EXPECT_TRUE(RE2::FullMatch("hello", RE2("hello")));
}

TEST(RE2FullMatchTest_8, FullMatchRequiresEntireString_8) {
  EXPECT_FALSE(RE2::FullMatch("hello world", RE2("hello")));
}

TEST(RE2FullMatchTest_8, FullMatchWithWildcard_8) {
  EXPECT_TRUE(RE2::FullMatch("hello world", RE2("hello.*")));
}

TEST(RE2FullMatchTest_8, EmptyTextEmptyPattern_8) {
  EXPECT_TRUE(RE2::FullMatch("", RE2("")));
}

TEST(RE2FullMatchTest_8, FullMatchCapture_8) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("12345", RE2("(\\d+)"), &n));
  EXPECT_EQ(12345, n);
}

TEST(RE2FullMatchTest_8, FullMatchNoMatch_8) {
  EXPECT_FALSE(RE2::FullMatch("abc", RE2("\\d+")));
}

// ==================== Consume Tests ====================

TEST(RE2ConsumeTest_8, ConsumeAdvancesInput_8) {
  absl::string_view input("one1two2three3");
  std::string word;
  int number;
  EXPECT_TRUE(RE2::Consume(&input, RE2("([a-z]+)(\\d)"), &word, &number));
  EXPECT_EQ("one", word);
  EXPECT_EQ(1, number);
  EXPECT_TRUE(RE2::Consume(&input, RE2("([a-z]+)(\\d)"), &word, &number));
  EXPECT_EQ("two", word);
  EXPECT_EQ(2, number);
}

TEST(RE2ConsumeTest_8, ConsumeNoMatch_8) {
  absl::string_view input("hello");
  EXPECT_FALSE(RE2::Consume(&input, RE2("\\d+")));
}

// ==================== FindAndConsume Tests ====================

TEST(RE2FindAndConsumeTest_8, FindAndConsumeSkipsNonMatching_8) {
  absl::string_view input("abc 123 def 456");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, RE2("(\\d+)"), &n));
  EXPECT_EQ(123, n);
  EXPECT_TRUE(RE2::FindAndConsume(&input, RE2("(\\d+)"), &n));
  EXPECT_EQ(456, n);
  EXPECT_FALSE(RE2::FindAndConsume(&input, RE2("(\\d+)"), &n));
}

// ==================== Replace Tests ====================

TEST(RE2ReplaceTest_8, SimpleReplace_8) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, RE2("world"), "there"));
  EXPECT_EQ("hello there", s);
}

TEST(RE2ReplaceTest_8, ReplaceNoMatch_8) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, RE2("xyz"), "there"));
  EXPECT_EQ("hello world", s);
}

TEST(RE2ReplaceTest_8, ReplaceOnlyFirst_8) {
  std::string s = "aaa";
  RE2::Replace(&s, RE2("a"), "b");
  EXPECT_EQ("baa", s);
}

TEST(RE2ReplaceTest_8, ReplaceWithBackreference_8) {
  std::string s = "hello world";
  RE2::Replace(&s, RE2("(\\w+) (\\w+)"), "\\2 \\1");
  EXPECT_EQ("world hello", s);
}

// ==================== GlobalReplace Tests ====================

TEST(RE2GlobalReplaceTest_8, ReplaceAll_8) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, RE2("a"), "b");
  EXPECT_EQ("bbb", s);
  EXPECT_EQ(3, count);
}

TEST(RE2GlobalReplaceTest_8, GlobalReplaceNoMatch_8) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, RE2("x"), "y");
  EXPECT_EQ("hello", s);
  EXPECT_EQ(0, count);
}

// ==================== Extract Tests ====================

TEST(RE2ExtractTest_8, SimpleExtract_8) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremvax.ru", RE2("(.*)@([^.]*)"), "\\2!\\1", &out));
  EXPECT_EQ("kremvax!boris", out);
}

TEST(RE2ExtractTest_8, ExtractNoMatch_8) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no email here", RE2("(.*)@([^.]*)"), "\\2!\\1", &out));
}

// ==================== QuoteMeta Tests ====================

TEST(RE2QuoteMetaTest_8, QuoteSpecialCharacters_8) {
  std::string quoted = RE2::QuoteMeta("a.b+c*d?e");
  RE2 re(quoted);
  EXPECT_TRUE(RE2::FullMatch("a.b+c*d?e", re));
  EXPECT_FALSE(RE2::FullMatch("aXb+c*d?e", re));
}

TEST(RE2QuoteMetaTest_8, QuoteEmptyString_8) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ("", quoted);
}

TEST(RE2QuoteMetaTest_8, QuoteNoSpecialChars_8) {
  std::string quoted = RE2::QuoteMeta("hello");
  EXPECT_EQ("hello", quoted);
}

// ==================== RE2 Construction and Status Tests ====================

TEST(RE2ConstructionTest_8, ValidPattern_8) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("hello", re.pattern());
}

TEST(RE2ConstructionTest_8, InvalidPattern_8) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2ConstructionTest_8, ConstructFromCString_8) {
  RE2 re("test");
  EXPECT_TRUE(re.ok());
}

TEST(RE2ConstructionTest_8, ConstructFromStdString_8) {
  std::string pattern = "test";
  RE2 re(pattern);
  EXPECT_TRUE(re.ok());
}

TEST(RE2ConstructionTest_8, ConstructFromStringView_8) {
  absl::string_view sv("test");
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
}

TEST(RE2ConstructionTest_8, ConstructWithOptions_8) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("Hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST(RE2CapturingGroupsTest_8, NoCapturingGroups_8) {
  RE2 re("hello");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_8, OneCapturingGroup_8) {
  RE2 re("(hello)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_8, MultipleCapturingGroups_8) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_8, NonCapturingGroup_8) {
  RE2 re("(?:abc)(def)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

// ==================== NamedCapturingGroups Tests ====================

TEST(RE2NamedCapturingGroupsTest_8, NoNamedGroups_8) {
  RE2 re("(hello)");
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2NamedCapturingGroupsTest_8, WithNamedGroups_8) {
  RE2 re("(?P<name>\\w+) (?P<age>\\d+)");
  EXPECT_TRUE(re.ok());
  const std::map<std::string, int>& groups = re.NamedCapturingGroups();
  EXPECT_EQ(2u, groups.size());
  EXPECT_EQ(1, groups.at("name"));
  EXPECT_EQ(2, groups.at("age"));
}

// ==================== CapturingGroupNames Tests ====================

TEST(RE2CapturingGroupNamesTest_8, WithNamedGroups_8) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const std::map<int, std::string>& names = re.CapturingGroupNames();
  EXPECT_EQ(2u, names.size());
  EXPECT_EQ("first", names.at(1));
  EXPECT_EQ("second", names.at(2));
}

// ==================== Match Tests ====================

TEST(RE2MatchTest_8, MatchAnchored_8) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.ok());
  absl::string_view submatch;
  EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ("123", submatch);
}

TEST(RE2MatchTest_8, MatchAnchoredStart_8) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_FALSE(re.Match("abc123", 0, 6, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_8, MatchAnchoredBoth_8) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_FALSE(re.Match("123abc", 0, 6, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_8, MatchWithStartPos_8) {
  RE2 re("\\d+");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match("abc123def", 3, 9, RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ("123", submatch);
}

TEST(RE2MatchTest_8, MatchNoSubmatch_8) {
  RE2 re("hello");
  EXPECT_TRUE(re.Match("say hello world", 0, 15, RE2::UNANCHORED, nullptr, 0));
}

// ==================== ProgramSize Tests ====================

TEST(RE2ProgramSizeTest_8, ProgramSizePositive_8) {
  RE2 re("hello");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_8, ReverseProgramSizePositive_8) {
  RE2 re("hello");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ==================== PossibleMatchRange Tests ====================

TEST(RE2PossibleMatchRangeTest_8, SimpleRange_8) {
  RE2 re("abc");
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_FALSE(min.empty());
}

// ==================== CheckRewriteString Tests ====================

TEST(RE2CheckRewriteStringTest_8, ValidRewrite_8) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewriteStringTest_8, InvalidRewrite_8) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ==================== MaxSubmatch Tests ====================

TEST(RE2MaxSubmatchTest_8, NoBackreferences_8) {
  EXPECT_EQ(0, RE2::MaxSubmatch("no backrefs"));
}

TEST(RE2MaxSubmatchTest_8, WithBackreferences_8) {
  EXPECT_EQ(3, RE2::MaxSubmatch("\\1 \\2 \\3"));
}

TEST(RE2MaxSubmatchTest_8, SingleBackreference_8) {
  EXPECT_EQ(1, RE2::MaxSubmatch("\\1"));
}

// ==================== Hex, Octal, CRadix Tests ====================

TEST(RE2HexTest_8, HexCapture_8) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("ff", RE2("([0-9a-fA-F]+)"), RE2::Hex(&value)));
  EXPECT_EQ(255, value);
}

TEST(RE2OctalTest_8, OctalCapture_8) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("77", RE2("([0-7]+)"), RE2::Octal(&value)));
  EXPECT_EQ(63, value);
}

TEST(RE2CRadixTest_8, CRadixHex_8) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("0xff", RE2("(0x[0-9a-fA-F]+)"), RE2::CRadix(&value)));
  EXPECT_EQ(255, value);
}

TEST(RE2CRadixTest_8, CRadixDecimal_8) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("100", RE2("(\\d+)"), RE2::CRadix(&value)));
  EXPECT_EQ(100, value);
}

TEST(RE2CRadixTest_8, CRadixOctal_8) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("010", RE2("(0[0-7]+)"), RE2::CRadix(&value)));
  EXPECT_EQ(8, value);
}

// ==================== ProgramFanout Tests ====================

TEST(RE2ProgramFanoutTest_8, FanoutWithVector_8) {
  RE2 re("(a|b)c");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ProgramFanoutTest_8, ReverseFanoutWithVector_8) {
  RE2 re("(a|b)c");
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ==================== Error Code Tests ====================

TEST(RE2ErrorCodeTest_8, NoErrorOnValidPattern_8) {
  RE2 re("hello");
  EXPECT_EQ(RE2::NoError, re.error_code());
}

TEST(RE2ErrorCodeTest_8, ErrorOnInvalidPattern_8) {
  RE2 re("[unclosed");
  EXPECT_NE(RE2::NoError, re.error_code());
}

// ==================== Rewrite Tests ====================

TEST(RE2RewriteTest_8, SimpleRewrite_8) {
  RE2 re("(\\w+)@(\\w+)");
  std::string out;
  absl::string_view vec[3];
  vec[0] = absl::string_view("user@host");
  vec[1] = absl::string_view("user");
  vec[2] = absl::string_view("host");
  EXPECT_TRUE(re.Rewrite(&out, "\\2!\\1", vec, 3));
  EXPECT_EQ("host!user", out);
}

// ==================== PartialMatch with Various Types ====================

TEST(RE2PartialMatchTest_8, CaptureFloat_8) {
  float f;
  EXPECT_TRUE(RE2::PartialMatch("value is 3.14 approx", RE2("([\\d.]+)"), &f));
  EXPECT_NEAR(3.14, f, 0.01);
}

TEST(RE2PartialMatchTest_8, CaptureStringPiece_8) {
  absl::string_view sp;
  EXPECT_TRUE(RE2::PartialMatch("hello world", RE2("(\\w+)"), &sp));
  EXPECT_EQ("hello", sp);
}

TEST(RE2PartialMatchTest_8, NoCaptureArgs_8) {
  EXPECT_TRUE(RE2::PartialMatch("abc123", RE2("\\d+")));
}

// ==================== Boundary Conditions ====================

TEST(RE2BoundaryTest_8, VeryLongString_8) {
  std::string longStr(10000, 'a');
  EXPECT_TRUE(RE2::PartialMatch(longStr, RE2("a+")));
}

TEST(RE2BoundaryTest_8, MatchEmptyWithStar_8) {
  EXPECT_TRUE(RE2::FullMatch("", RE2("a*")));
}

TEST(RE2BoundaryTest_8, PartialMatchEmptyWithStar_8) {
  EXPECT_TRUE(RE2::PartialMatch("", RE2("a*")));
}

TEST(RE2BoundaryTest_8, MatchWithStartPosEqualEndPos_8) {
  RE2 re("a*");
  EXPECT_TRUE(re.Match("abc", 0, 0, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2BoundaryTest_8, PartialMatchSpecialCharsInText_8) {
  EXPECT_TRUE(RE2::PartialMatch("a.b", RE2("a\\.b")));
  EXPECT_FALSE(RE2::PartialMatch("acb", RE2("a\\.b")));
}

// ==================== Invalid RE2 usage ====================

TEST(RE2InvalidPatternTest_8, PartialMatchWithInvalidRE_8) {
  RE2 re("(invalid");
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(RE2::PartialMatch("test", re));
}

TEST(RE2InvalidPatternTest_8, FullMatchWithInvalidRE_8) {
  RE2 re("*invalid");
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("test", re));
}
