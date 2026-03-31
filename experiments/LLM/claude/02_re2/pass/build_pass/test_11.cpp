#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>

// ============================================================
// NumberOfCapturingGroups tests
// ============================================================

TEST(RE2Test_11, NumberOfCapturingGroups_NoGroups_11) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(RE2Test_11, NumberOfCapturingGroups_OneGroup_11) {
  RE2 re("(hello)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(RE2Test_11, NumberOfCapturingGroups_MultipleGroups_11) {
  RE2 re("(a)(b)(c)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2Test_11, NumberOfCapturingGroups_NestedGroups_11) {
  RE2 re("((a)(b))");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2Test_11, NumberOfCapturingGroups_NonCapturingGroup_11) {
  RE2 re("(?:a)(b)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(RE2Test_11, NumberOfCapturingGroups_EmptyPattern_11) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(RE2Test_11, NumberOfCapturingGroups_NamedGroup_11) {
  RE2 re("(?P<name>\\w+)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(RE2Test_11, NumberOfCapturingGroups_MixedGroups_11) {
  RE2 re("(?P<first>\\w+)\\s(?:and)\\s(\\w+)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(2, re.NumberOfCapturingGroups());
}

// ============================================================
// Construction and ok() tests
// ============================================================

TEST(RE2Test_11, ConstructFromCString_11) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("abc", re.pattern());
}

TEST(RE2Test_11, ConstructFromStdString_11) {
  std::string pat = "abc";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("abc", re.pattern());
}

TEST(RE2Test_11, ConstructFromStringView_11) {
  absl::string_view sv = "abc";
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("abc", re.pattern());
}

TEST(RE2Test_11, InvalidPattern_11) {
  RE2 re("(abc");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2Test_11, PatternReturnsOriginal_11) {
  RE2 re("foo.*bar");
  EXPECT_EQ("foo.*bar", re.pattern());
}

// ============================================================
// FullMatch tests
// ============================================================

TEST(RE2Test_11, FullMatch_SimpleMatch_11) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2Test_11, FullMatch_NoMatch_11) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2Test_11, FullMatch_WithCapture_11) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("123", "(\\d+)", &n));
  EXPECT_EQ(123, n);
}

TEST(RE2Test_11, FullMatch_StringCapture_11) {
  std::string s;
  EXPECT_TRUE(RE2::FullMatch("abc", "(\\w+)", &s));
  EXPECT_EQ("abc", s);
}

TEST(RE2Test_11, FullMatch_MultipleCaptures_11) {
  std::string a, b;
  EXPECT_TRUE(RE2::FullMatch("hello world", "(\\w+) (\\w+)", &a, &b));
  EXPECT_EQ("hello", a);
  EXPECT_EQ("world", b);
}

TEST(RE2Test_11, FullMatch_EmptyPattern_11) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_FALSE(RE2::FullMatch("abc", ""));
}

// ============================================================
// PartialMatch tests
// ============================================================

TEST(RE2Test_11, PartialMatch_SimpleMatch_11) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "llo"));
}

TEST(RE2Test_11, PartialMatch_NoMatch_11) {
  EXPECT_FALSE(RE2::PartialMatch("hello", "xyz"));
}

TEST(RE2Test_11, PartialMatch_WithCapture_11) {
  int n;
  EXPECT_TRUE(RE2::PartialMatch("abc 123 def", "(\\d+)", &n));
  EXPECT_EQ(123, n);
}

// ============================================================
// Consume tests
// ============================================================

TEST(RE2Test_11, Consume_Basic_11) {
  absl::string_view input("one123two456");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &word));
  EXPECT_EQ("one", word);
  // input should have been advanced past "one"
  EXPECT_EQ("123two456", std::string(input));
}

TEST(RE2Test_11, Consume_NoMatch_11) {
  absl::string_view input("123abc");
  std::string word;
  EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &word));
}

// ============================================================
// FindAndConsume tests
// ============================================================

TEST(RE2Test_11, FindAndConsume_Basic_11) {
  absl::string_view input("one 123 two 456");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(123, n);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(456, n);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

// ============================================================
// Replace tests
// ============================================================

TEST(RE2Test_11, Replace_Basic_11) {
  std::string s = "yabba dabba doo";
  EXPECT_TRUE(RE2::Replace(&s, "b+", "d"));
  EXPECT_EQ("yadba dabba doo", s);
}

TEST(RE2Test_11, Replace_NoMatch_11) {
  std::string s = "hello";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ("hello", s);
}

TEST(RE2Test_11, Replace_WithBackreference_11) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "[\\1]"));
  EXPECT_EQ("[hello] world", s);
}

// ============================================================
// GlobalReplace tests
// ============================================================

TEST(RE2Test_11, GlobalReplace_Basic_11) {
  std::string s = "yabba dabba doo";
  int count = RE2::GlobalReplace(&s, "b+", "d");
  EXPECT_EQ("yadda dadda doo", s);
  EXPECT_EQ(3, count);
}

TEST(RE2Test_11, GlobalReplace_NoMatch_11) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ(0, count);
  EXPECT_EQ("hello", s);
}

// ============================================================
// Extract tests
// ============================================================

TEST(RE2Test_11, Extract_Basic_11) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremvax.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ("kremvax!boris", out);
}

TEST(RE2Test_11, Extract_NoMatch_11) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("noatsign", "(.*)@(.*)", "\\2!\\1", &out));
}

// ============================================================
// QuoteMeta tests
// ============================================================

TEST(RE2Test_11, QuoteMeta_BasicEscape_11) {
  std::string quoted = RE2::QuoteMeta("a.b");
  RE2 re(quoted);
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

TEST(RE2Test_11, QuoteMeta_NoSpecialChars_11) {
  EXPECT_EQ("hello", RE2::QuoteMeta("hello"));
}

TEST(RE2Test_11, QuoteMeta_Empty_11) {
  EXPECT_EQ("", RE2::QuoteMeta(""));
}

TEST(RE2Test_11, QuoteMeta_SpecialChars_11) {
  std::string quoted = RE2::QuoteMeta("1.5-2.0?");
  RE2 re(quoted);
  EXPECT_TRUE(RE2::FullMatch("1.5-2.0?", re));
  EXPECT_FALSE(RE2::FullMatch("1x5-2x0?", re));
}

// ============================================================
// Match tests
// ============================================================

TEST(RE2Test_11, Match_FullText_11) {
  RE2 re("(\\w+):(\\d+)");
  ASSERT_TRUE(re.ok());
  absl::string_view submatch[3];
  EXPECT_TRUE(re.Match("foo:123", 0, 7, RE2::ANCHOR_BOTH, submatch, 3));
  EXPECT_EQ("foo:123", std::string(submatch[0]));
  EXPECT_EQ("foo", std::string(submatch[1]));
  EXPECT_EQ("123", std::string(submatch[2]));
}

TEST(RE2Test_11, Match_Unanchored_11) {
  RE2 re("(\\d+)");
  ASSERT_TRUE(re.ok());
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc 123 def", 0, 11, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ("123", std::string(submatch[0]));
  EXPECT_EQ("123", std::string(submatch[1]));
}

TEST(RE2Test_11, Match_NoMatch_11) {
  RE2 re("(\\d+)");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(re.Match("abcdef", 0, 6, RE2::UNANCHORED, nullptr, 0));
}

TEST(RE2Test_11, Match_AnchorStart_11) {
  RE2 re("(\\d+)");
  ASSERT_TRUE(re.ok());
  absl::string_view submatch[2];
  EXPECT_FALSE(re.Match("abc123", 0, 6, RE2::ANCHOR_START, submatch, 2));
  EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::ANCHOR_START, submatch, 2));
  EXPECT_EQ("123", std::string(submatch[1]));
}

TEST(RE2Test_11, Match_WithStartPos_11) {
  RE2 re("(\\d+)");
  ASSERT_TRUE(re.ok());
  absl::string_view submatch[2];
  absl::string_view text = "abc123def456";
  EXPECT_TRUE(re.Match(text, 6, text.size(), RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ("456", std::string(submatch[1]));
}

// ============================================================
// PossibleMatchRange tests
// ============================================================

TEST(RE2Test_11, PossibleMatchRange_Basic_11) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "hello");
  EXPECT_GE(max_str, "hello");
}

// ============================================================
// NamedCapturingGroups tests
// ============================================================

TEST(RE2Test_11, NamedCapturingGroups_Basic_11) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  ASSERT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(2u, groups.size());
  auto it = groups.find("first");
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(1, it->second);
  it = groups.find("second");
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(2, it->second);
}

TEST(RE2Test_11, NamedCapturingGroups_NoNames_11) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

// ============================================================
// CapturingGroupNames tests
// ============================================================

TEST(RE2Test_11, CapturingGroupNames_Basic_11) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  ASSERT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(2u, names.size());
  auto it = names.find(1);
  ASSERT_NE(it, names.end());
  EXPECT_EQ("first", it->second);
  it = names.find(2);
  ASSERT_NE(it, names.end());
  EXPECT_EQ("second", it->second);
}

// ============================================================
// CheckRewriteString tests
// ============================================================

TEST(RE2Test_11, CheckRewriteString_Valid_11) {
  RE2 re("(\\w+) (\\w+)");
  ASSERT_TRUE(re.ok());
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1 and \\2", &error));
}

TEST(RE2Test_11, CheckRewriteString_InvalidBackref_11) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ============================================================
// MaxSubmatch tests
// ============================================================

TEST(RE2Test_11, MaxSubmatch_Basic_11) {
  EXPECT_EQ(0, RE2::MaxSubmatch("no backrefs"));
  EXPECT_EQ(1, RE2::MaxSubmatch("\\1"));
  EXPECT_EQ(3, RE2::MaxSubmatch("\\1 \\3 \\2"));
  EXPECT_EQ(0, RE2::MaxSubmatch("\\0"));
}

// ============================================================
// ProgramSize / ReverseProgramSize tests
// ============================================================

TEST(RE2Test_11, ProgramSize_Basic_11) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2Test_11, ReverseProgramSize_Basic_11) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ============================================================
// ProgramFanout tests
// ============================================================

TEST(RE2Test_11, ProgramFanout_Vector_11) {
  RE2 re("[abc].*[xyz]");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2Test_11, ReverseProgramFanout_Vector_11) {
  RE2 re("[abc].*[xyz]");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ============================================================
// Options tests
// ============================================================

TEST(RE2Test_11, Options_CaseSensitiveDefault_11) {
  RE2 re("Hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_FALSE(RE2::FullMatch("hello", re));
}

TEST(RE2Test_11, Options_CaseInsensitive_11) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("Hello", opts);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
}

// ============================================================
// Error code tests
// ============================================================

TEST(RE2Test_11, ErrorCode_NoError_11) {
  RE2 re("abc");
  EXPECT_EQ(RE2::NoError, re.error_code());
  EXPECT_TRUE(re.error().empty());
}

TEST(RE2Test_11, ErrorCode_BadPattern_11) {
  RE2 re("(abc");
  EXPECT_NE(RE2::NoError, re.error_code());
  EXPECT_FALSE(re.error().empty());
}

// ============================================================
// Rewrite tests
// ============================================================

TEST(RE2Test_11, Rewrite_Basic_11) {
  RE2 re("(\\w+):(\\d+)");
  ASSERT_TRUE(re.ok());
  absl::string_view vec[3] = {"foo:123", "foo", "123"};
  std::string out;
  EXPECT_TRUE(re.Rewrite(&out, "\\2-\\1", vec, 3));
  EXPECT_EQ("123-foo", out);
}

// ============================================================
// Edge case: complex patterns
// ============================================================

TEST(RE2Test_11, ComplexPattern_Alternation_11) {
  RE2 re("(cat|dog|fish)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
  EXPECT_TRUE(RE2::FullMatch("cat", re));
  EXPECT_TRUE(RE2::FullMatch("dog", re));
  EXPECT_TRUE(RE2::FullMatch("fish", re));
  EXPECT_FALSE(RE2::FullMatch("bird", re));
}

TEST(RE2Test_11, ComplexPattern_Quantifiers_11) {
  RE2 re("a{2,4}");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("aa", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaa", re));
  EXPECT_FALSE(RE2::FullMatch("aaaaa", re));
}

TEST(RE2Test_11, NumberOfCapturingGroups_ComplexNested_11) {
  RE2 re("((a)(b(c)(d)))");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(5, re.NumberOfCapturingGroups());
}

// ============================================================
// FullMatch with hex/octal parsing
// ============================================================

TEST(RE2Test_11, FullMatch_HexParse_11) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("0xff", "0x([0-9a-fA-F]+)", RE2::Hex(&n)));
  EXPECT_EQ(255, n);
}

TEST(RE2Test_11, FullMatch_OctalParse_11) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("0777", "0(\\d+)", RE2::Octal(&n)));
  EXPECT_EQ(511, n);
}

TEST(RE2Test_11, FullMatch_CRadixParse_11) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(.*)", RE2::CRadix(&n)));
  EXPECT_EQ(31, n);
}

// ============================================================
// GlobalReplace with empty match
// ============================================================

TEST(RE2Test_11, GlobalReplace_EmptyMatch_11) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "", "-");
  // Each position (before a, between a-b, between b-c, after c) should get a dash
  EXPECT_GT(count, 0);
}

// ============================================================
// Boundary: very simple regex
// ============================================================

TEST(RE2Test_11, FullMatch_DotStar_11) {
  EXPECT_TRUE(RE2::FullMatch("anything at all", ".*"));
  EXPECT_TRUE(RE2::FullMatch("", ".*"));
}

TEST(RE2Test_11, FullMatch_EmptyBoth_11) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
}
