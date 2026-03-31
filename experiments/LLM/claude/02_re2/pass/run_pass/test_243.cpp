#include "gtest/gtest.h"
#include "re2/re2.h"
#include <string>
#include <vector>
#include <map>

namespace re2 {

// Test fixture
class RE2Test_243 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(RE2Test_243, ConstructFromCString_243) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("hello", re.pattern());
}

TEST_F(RE2Test_243, ConstructFromStdString_243) {
  std::string pattern = "world";
  RE2 re(pattern);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("world", re.pattern());
}

TEST_F(RE2Test_243, ConstructFromStringView_243) {
  absl::string_view sv = "test.*pattern";
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("test.*pattern", re.pattern());
}

TEST_F(RE2Test_243, ConstructWithOptions_243) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("Hello", opts);
  EXPECT_TRUE(re.ok());
}

TEST_F(RE2Test_243, InvalidPattern_243) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}

TEST_F(RE2Test_243, EmptyPattern_243) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("", re.pattern());
}

// ==================== FullMatch Tests ====================

TEST_F(RE2Test_243, FullMatchSimple_243) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST_F(RE2Test_243, FullMatchWithCapture_243) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("ruby:1234", "(\\w+):(\\d+)", nullptr, &n));
  EXPECT_EQ(1234, n);
}

TEST_F(RE2Test_243, FullMatchWithStringCapture_243) {
  std::string word;
  EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", &word));
  EXPECT_EQ("hello", word);
}

TEST_F(RE2Test_243, FullMatchNoMatch_243) {
  EXPECT_FALSE(RE2::FullMatch("abc", "\\d+"));
}

TEST_F(RE2Test_243, FullMatchDotStar_243) {
  EXPECT_TRUE(RE2::FullMatch("anything goes here", ".*"));
}

// ==================== PartialMatch Tests ====================

TEST_F(RE2Test_243, PartialMatchSimple_243) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "llo"));
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST_F(RE2Test_243, PartialMatchWithCapture_243) {
  int n;
  EXPECT_TRUE(RE2::PartialMatch("x]234", "(\\d+)", &n));
  EXPECT_EQ(234, n);
}

TEST_F(RE2Test_243, PartialMatchAtStart_243) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "^hello"));
}

TEST_F(RE2Test_243, PartialMatchAtEnd_243) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "world$"));
}

// ==================== Consume Tests ====================

TEST_F(RE2Test_243, ConsumeBasic_243) {
  absl::string_view input("one123two456");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "(\\w+)", &word));
  EXPECT_EQ("one123two456", word);
}

TEST_F(RE2Test_243, ConsumeRepeated_243) {
  absl::string_view input("aaa");
  std::string s;
  EXPECT_TRUE(RE2::Consume(&input, "(a)", &s));
  EXPECT_EQ("a", s);
  EXPECT_TRUE(RE2::Consume(&input, "(a)", &s));
  EXPECT_EQ("a", s);
  EXPECT_TRUE(RE2::Consume(&input, "(a)", &s));
  EXPECT_EQ("a", s);
  EXPECT_FALSE(RE2::Consume(&input, "(a)", &s));
}

// ==================== FindAndConsume Tests ====================

TEST_F(RE2Test_243, FindAndConsumeBasic_243) {
  absl::string_view input("abc 123 def 456");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(123, n);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(456, n);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

// ==================== Replace Tests ====================

TEST_F(RE2Test_243, ReplaceFirst_243) {
  std::string s = "yabba dabba doo";
  EXPECT_TRUE(RE2::Replace(&s, "b+", "d"));
  EXPECT_EQ("yada dabba doo", s);
}

TEST_F(RE2Test_243, ReplaceNoMatch_243) {
  std::string s = "yabba dabba doo";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "q"));
  EXPECT_EQ("yabba dabba doo", s);
}

TEST_F(RE2Test_243, ReplaceWithBackreference_243) {
  std::string s = "hello world";
  RE2::Replace(&s, "(\\w+)", "<<\\1>>");
  EXPECT_EQ("<<hello>> world", s);
}

// ==================== GlobalReplace Tests ====================

TEST_F(RE2Test_243, GlobalReplaceAll_243) {
  std::string s = "yabba dabba doo";
  int count = RE2::GlobalReplace(&s, "b+", "d");
  EXPECT_EQ(2, count);
  EXPECT_EQ("yada dada doo", s);
}

TEST_F(RE2Test_243, GlobalReplaceNone_243) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "xyz", "q");
  EXPECT_EQ(0, count);
  EXPECT_EQ("hello", s);
}

TEST_F(RE2Test_243, GlobalReplaceEmpty_243) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "b", "");
  EXPECT_EQ(1, count);
  EXPECT_EQ("ac", s);
}

// ==================== Extract Tests ====================

TEST_F(RE2Test_243, ExtractBasic_243) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ("kremlin!boris", out);
}

TEST_F(RE2Test_243, ExtractNoMatch_243) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no email here", "(.*)@([^.]*)", "\\2!\\1", &out));
}

// ==================== QuoteMeta Tests ====================

TEST_F(RE2Test_243, QuoteMetaSimple_243) {
  EXPECT_EQ("hello", RE2::QuoteMeta("hello"));
}

TEST_F(RE2Test_243, QuoteMetaSpecialChars_243) {
  std::string quoted = RE2::QuoteMeta("a.b*c+d?e[f]g");
  RE2 re(quoted);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a.b*c+d?e[f]g", re));
  EXPECT_FALSE(RE2::FullMatch("axbxcxdxexfxg", re));
}

TEST_F(RE2Test_243, QuoteMetaEmpty_243) {
  EXPECT_EQ("", RE2::QuoteMeta(""));
}

TEST_F(RE2Test_243, QuoteMetaBackslash_243) {
  std::string quoted = RE2::QuoteMeta("\\");
  RE2 re(quoted);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("\\", re));
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST_F(RE2Test_243, NumberOfCapturingGroupsNone_243) {
  RE2 re("hello");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST_F(RE2Test_243, NumberOfCapturingGroupsOne_243) {
  RE2 re("(hello)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST_F(RE2Test_243, NumberOfCapturingGroupsMultiple_243) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST_F(RE2Test_243, NumberOfCapturingGroupsNonCapturing_243) {
  RE2 re("(?:hello)");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST_F(RE2Test_243, NumberOfCapturingGroupsMixed_243) {
  RE2 re("(a)(?:b)(c)");
  EXPECT_EQ(2, re.NumberOfCapturingGroups());
}

// ==================== NamedCapturingGroups Tests ====================

TEST_F(RE2Test_243, NamedCapturingGroupsNone_243) {
  RE2 re("hello");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST_F(RE2Test_243, NamedCapturingGroupsPresent_243) {
  RE2 re("(?P<name>\\w+) (?P<age>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(2u, groups.size());
  auto it = groups.find("name");
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(1, it->second);
  it = groups.find("age");
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(2, it->second);
}

// ==================== CapturingGroupNames Tests ====================

TEST_F(RE2Test_243, CapturingGroupNamesNone_243) {
  RE2 re("hello");
  const auto& names = re.CapturingGroupNames();
  EXPECT_TRUE(names.empty());
}

TEST_F(RE2Test_243, CapturingGroupNamesPresent_243) {
  RE2 re("(?P<first>\\w+) (?P<second>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(2u, names.size());
  auto it = names.find(1);
  ASSERT_NE(it, names.end());
  EXPECT_EQ("first", it->second);
  it = names.find(2);
  ASSERT_NE(it, names.end());
  EXPECT_EQ("second", it->second);
}

// ==================== Match Tests ====================

TEST_F(RE2Test_243, MatchFullAnchor_243) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("1234", 0, 4, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_FALSE(re.Match("12ab", 0, 4, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST_F(RE2Test_243, MatchUnanchored_243) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, nullptr, 0));
  EXPECT_FALSE(re.Match("abcdef", 0, 6, RE2::UNANCHORED, nullptr, 0));
}

TEST_F(RE2Test_243, MatchWithSubmatch_243) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ("123", submatch[0]);
  EXPECT_EQ("123", submatch[1]);
}

TEST_F(RE2Test_243, MatchStartpos_243) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("abc123", 3, 6, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_FALSE(re.Match("abc123", 0, 3, RE2::ANCHOR_START, nullptr, 0));
}

TEST_F(RE2Test_243, MatchAnchorStart_243) {
  RE2 re("hello");
  EXPECT_TRUE(re.Match("hello world", 0, 11, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_FALSE(re.Match("say hello", 0, 9, RE2::ANCHOR_START, nullptr, 0));
}

// ==================== ProgramSize Tests ====================

TEST_F(RE2Test_243, ProgramSizePositive_243) {
  RE2 re("a+b+c+");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST_F(RE2Test_243, ReverseProgramSizePositive_243) {
  RE2 re("a+b+c+");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ==================== ProgramFanout Tests ====================

TEST_F(RE2Test_243, ProgramFanout_243) {
  RE2 re("a+b+");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST_F(RE2Test_243, ReverseProgramFanout_243) {
  RE2 re("a+b+");
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ==================== PossibleMatchRange Tests ====================

TEST_F(RE2Test_243, PossibleMatchRange_243) {
  RE2 re("abc.*");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "abc");
}

TEST_F(RE2Test_243, PossibleMatchRangeEmpty_243) {
  RE2 re("[^\\s\\S]");  // unmatchable
  std::string min_str, max_str;
  // The function might return false or return empty range
  re.PossibleMatchRange(&min_str, &max_str, 10);
}

// ==================== CheckRewriteString Tests ====================

TEST_F(RE2Test_243, CheckRewriteStringValid_243) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST_F(RE2Test_243, CheckRewriteStringInvalidRef_243) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

TEST_F(RE2Test_243, CheckRewriteStringNoCapture_243) {
  RE2 re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("world", &error));
}

// ==================== MaxSubmatch Tests ====================

TEST_F(RE2Test_243, MaxSubmatchNone_243) {
  EXPECT_EQ(0, RE2::MaxSubmatch("no backrefs"));
}

TEST_F(RE2Test_243, MaxSubmatchOne_243) {
  EXPECT_EQ(1, RE2::MaxSubmatch("\\1"));
}

TEST_F(RE2Test_243, MaxSubmatchMultiple_243) {
  EXPECT_EQ(3, RE2::MaxSubmatch("\\1 \\3 \\2"));
}

// ==================== Rewrite Tests ====================

TEST_F(RE2Test_243, RewriteBasic_243) {
  RE2 re("(\\w+):(\\d+)");
  absl::string_view vec[3];
  vec[0] = "hello:123";
  vec[1] = "hello";
  vec[2] = "123";
  std::string out;
  EXPECT_TRUE(re.Rewrite(&out, "\\2-\\1", vec, 3));
  EXPECT_EQ("123-hello", out);
}

TEST_F(RE2Test_243, RewriteInvalidBackref_243) {
  RE2 re("(\\w+)");
  absl::string_view vec[2];
  vec[0] = "hello";
  vec[1] = "hello";
  std::string out;
  EXPECT_FALSE(re.Rewrite(&out, "\\2", vec, 2));
}

// ==================== Options Tests ====================

TEST_F(RE2Test_243, OptionsAccessor_243) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("Hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(re.options().case_sensitive());
}

TEST_F(RE2Test_243, CaseInsensitiveMatch_243) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

// ==================== Error Code Tests ====================

TEST_F(RE2Test_243, ErrorCodeNoError_243) {
  RE2 re("valid");
  EXPECT_EQ(RE2::NoError, re.error_code());
  EXPECT_TRUE(re.error().empty());
}

TEST_F(RE2Test_243, ErrorCodeBadPattern_243) {
  RE2 re("(unclosed");
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}

TEST_F(RE2Test_243, ErrorArgBadPattern_243) {
  RE2 re("(abc");
  EXPECT_FALSE(re.ok());
  // error_arg should have some content
}

// ==================== Complex Pattern Tests ====================

TEST_F(RE2Test_243, ComplexPatternEmail_243) {
  RE2 re("([\\w.]+)@(\\w+\\.\\w+)");
  EXPECT_TRUE(re.ok());
  std::string user, domain;
  EXPECT_TRUE(RE2::FullMatch("user@example.com", re, &user, &domain));
  EXPECT_EQ("user", user);
  EXPECT_EQ("example.com", domain);
}

TEST_F(RE2Test_243, ComplexPatternIP_243) {
  RE2 re("(\\d+)\\.(\\d+)\\.(\\d+)\\.(\\d+)");
  int a, b, c, d;
  EXPECT_TRUE(RE2::FullMatch("192.168.1.1", re, &a, &b, &c, &d));
  EXPECT_EQ(192, a);
  EXPECT_EQ(168, b);
  EXPECT_EQ(1, c);
  EXPECT_EQ(1, d);
}

// ==================== Hex/Octal/CRadix Tests ====================

TEST_F(RE2Test_243, HexCapture_243) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("ff", "([0-9a-fA-F]+)", RE2::Hex(&n)));
  EXPECT_EQ(255, n);
}

TEST_F(RE2Test_243, OctalCapture_243) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("77", "([0-7]+)", RE2::Octal(&n)));
  EXPECT_EQ(63, n);
}

TEST_F(RE2Test_243, CRadixHexCapture_243) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("0xff", "(0[xX][0-9a-fA-F]+)", RE2::CRadix(&n)));
  EXPECT_EQ(255, n);
}

TEST_F(RE2Test_243, CRadixOctalCapture_243) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("077", "(0[0-7]*)", RE2::CRadix(&n)));
  EXPECT_EQ(63, n);
}

TEST_F(RE2Test_243, CRadixDecimalCapture_243) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("123", "([1-9][0-9]*)", RE2::CRadix(&n)));
  EXPECT_EQ(123, n);
}

// ==================== Boundary / Edge Case Tests ====================

TEST_F(RE2Test_243, MatchEmptyString_243) {
  RE2 re("");
  EXPECT_TRUE(RE2::FullMatch("", re));
}

TEST_F(RE2Test_243, MatchEmptyStringPartial_243) {
  RE2 re("");
  EXPECT_TRUE(RE2::PartialMatch("anything", re));
}

TEST_F(RE2Test_243, VeryLongString_243) {
  std::string long_str(10000, 'a');
  RE2 re("a+");
  EXPECT_TRUE(RE2::FullMatch(long_str, re));
}

TEST_F(RE2Test_243, UnicodePattern_243) {
  RE2 re("\\pL+");  // Unicode letter
  EXPECT_TRUE(re.ok());
}

TEST_F(RE2Test_243, FullMatchNBasic_243) {
  RE2 re("(\\d+)");
  int n;
  RE2::Arg arg(&n);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::FullMatchN("123", re, args, 1));
  EXPECT_EQ(123, n);
}

TEST_F(RE2Test_243, FullMatchNZeroArgs_243) {
  RE2 re("hello");
  EXPECT_TRUE(RE2::FullMatchN("hello", re, nullptr, 0));
  EXPECT_FALSE(RE2::FullMatchN("world", re, nullptr, 0));
}

TEST_F(RE2Test_243, PartialMatchNBasic_243) {
  RE2 re("(\\d+)");
  int n;
  RE2::Arg arg(&n);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::PartialMatchN("abc123def", re, args, 1));
  EXPECT_EQ(123, n);
}

TEST_F(RE2Test_243, ConsumeNBasic_243) {
  RE2 re("(\\d+)");
  absl::string_view input("123abc");
  int n;
  RE2::Arg arg(&n);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::ConsumeN(&input, re, args, 1));
  EXPECT_EQ(123, n);
  EXPECT_EQ("abc", input);
}

TEST_F(RE2Test_243, FindAndConsumeNBasic_243) {
  RE2 re("(\\d+)");
  absl::string_view input("abc123def456");
  int n;
  RE2::Arg arg(&n);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, args, 1));
  EXPECT_EQ(123, n);
  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, args, 1));
  EXPECT_EQ(456, n);
}

// ==================== Regexp accessor Tests ====================

TEST_F(RE2Test_243, RegexpAccessor_243) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_NE(nullptr, re.Regexp());
}

TEST_F(RE2Test_243, RegexpAccessorInvalid_243) {
  RE2 re("(bad");
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(nullptr, re.Regexp());
}

// ==================== GlobalReplace edge cases ====================

TEST_F(RE2Test_243, GlobalReplaceEmptyMatch_243) {
  std::string s = "abc";
  // Replacing empty matches
  int count = RE2::GlobalReplace(&s, "", "-");
  // Should insert between every character and at boundaries
  EXPECT_GT(count, 0);
}

TEST_F(RE2Test_243, ReplaceWithEmptyPattern_243) {
  std::string s = "abc";
  EXPECT_TRUE(RE2::Replace(&s, "", "X"));
  EXPECT_EQ("Xabc", s);
}

}  // namespace re2
