#include "gtest/gtest.h"
#include "re2/re2.h"
#include <string>
#include <vector>
#include <map>

namespace {

// ============================================================
// Construction and basic properties
// ============================================================

TEST(RE2Test_597, ConstructFromStringView_597) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "hello");
}

TEST(RE2Test_597, ConstructFromStdString_597) {
  std::string pat = "world";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "world");
}

TEST(RE2Test_597, ConstructFromCString_597) {
  const char* pat = "foo";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "foo");
}

TEST(RE2Test_597, InvalidPatternNotOk_597) {
  RE2 re("(invalid[");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error_code(), RE2::NoError);
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2Test_597, EmptyPatternIsOk_597) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "");
}

TEST(RE2Test_597, ErrorCodeNoErrorForValidPattern_597) {
  RE2 re("abc");
  EXPECT_EQ(re.error_code(), RE2::NoError);
}

TEST(RE2Test_597, ConstructWithOptions_597) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("Hello", opts);
  EXPECT_TRUE(re.ok());
}

// ============================================================
// FullMatch tests
// ============================================================

TEST(RE2Test_597, FullMatchSimple_597) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2Test_597, FullMatchWithCapture_597) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("42", "(\\d+)", &n));
  EXPECT_EQ(n, 42);
}

TEST(RE2Test_597, FullMatchMultipleCaptures_597) {
  std::string s;
  int n;
  EXPECT_TRUE(RE2::FullMatch("abc 123", "(\\w+) (\\d+)", &s, &n));
  EXPECT_EQ(s, "abc");
  EXPECT_EQ(n, 123);
}

TEST(RE2Test_597, FullMatchNoMatch_597) {
  EXPECT_FALSE(RE2::FullMatch("abc", "\\d+"));
}

TEST(RE2Test_597, FullMatchEmptyPattern_597) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_FALSE(RE2::FullMatch("a", ""));
}

// ============================================================
// PartialMatch tests
// ============================================================

TEST(RE2Test_597, PartialMatchSimple_597) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "llo"));
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST(RE2Test_597, PartialMatchWithCapture_597) {
  std::string word;
  EXPECT_TRUE(RE2::PartialMatch("the quick brown fox", "(\\w+)ox", &word));
  EXPECT_EQ(word, "f");
}

TEST(RE2Test_597, PartialMatchEmptyText_597) {
  EXPECT_TRUE(RE2::PartialMatch("", ""));
  EXPECT_FALSE(RE2::PartialMatch("", "a"));
}

// ============================================================
// Consume tests
// ============================================================

TEST(RE2Test_597, ConsumeBasic_597) {
  absl::string_view input("one1two2three3");
  std::string word;
  int number;
  EXPECT_TRUE(RE2::Consume(&input, "(\\w+)(\\d)", &word, &number));
  // After consuming, input should have been advanced
  EXPECT_EQ(word, "one");
  EXPECT_EQ(number, 1);
}

TEST(RE2Test_597, ConsumeRepeated_597) {
  absl::string_view input("aab");
  std::string s;
  EXPECT_TRUE(RE2::Consume(&input, "(a)", &s));
  EXPECT_EQ(s, "a");
  EXPECT_TRUE(RE2::Consume(&input, "(a)", &s));
  EXPECT_EQ(s, "a");
  EXPECT_FALSE(RE2::Consume(&input, "(a)", &s));
}

// ============================================================
// FindAndConsume tests
// ============================================================

TEST(RE2Test_597, FindAndConsumeBasic_597) {
  absl::string_view input("abc 123 def 456");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 123);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 456);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

// ============================================================
// Replace tests
// ============================================================

TEST(RE2Test_597, ReplaceFirst_597) {
  std::string str = "hello world hello";
  EXPECT_TRUE(RE2::Replace(&str, "hello", "hi"));
  EXPECT_EQ(str, "hi world hello");
}

TEST(RE2Test_597, ReplaceNoMatch_597) {
  std::string str = "hello world";
  EXPECT_FALSE(RE2::Replace(&str, "xyz", "abc"));
  EXPECT_EQ(str, "hello world");
}

TEST(RE2Test_597, ReplaceWithBackreference_597) {
  std::string str = "foo bar";
  EXPECT_TRUE(RE2::Replace(&str, "(\\w+)", "<<\\1>>"));
  EXPECT_EQ(str, "<<foo>> bar");
}

// ============================================================
// GlobalReplace tests
// ============================================================

TEST(RE2Test_597, GlobalReplaceAll_597) {
  std::string str = "aaa";
  int count = RE2::GlobalReplace(&str, "a", "b");
  EXPECT_EQ(str, "bbb");
  EXPECT_EQ(count, 3);
}

TEST(RE2Test_597, GlobalReplaceNoMatch_597) {
  std::string str = "abc";
  int count = RE2::GlobalReplace(&str, "x", "y");
  EXPECT_EQ(str, "abc");
  EXPECT_EQ(count, 0);
}

TEST(RE2Test_597, GlobalReplaceEmptyMatch_597) {
  std::string str = "abc";
  int count = RE2::GlobalReplace(&str, "", "-");
  // Empty pattern matches between every character and at start/end
  EXPECT_GT(count, 0);
}

// ============================================================
// Extract tests
// ============================================================

TEST(RE2Test_597, ExtractBasic_597) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST(RE2Test_597, ExtractNoMatch_597) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-at-sign", "(.*)@(.*)", "\\1", &out));
}

// ============================================================
// QuoteMeta tests
// ============================================================

TEST(RE2Test_597, QuoteMetaSimple_597) {
  std::string quoted = RE2::QuoteMeta("hello");
  EXPECT_EQ(quoted, "hello");
}

TEST(RE2Test_597, QuoteMetaSpecialChars_597) {
  std::string quoted = RE2::QuoteMeta("a.b+c*d?e");
  // After quoting, these should be treated as literals
  EXPECT_TRUE(RE2::FullMatch("a.b+c*d?e", quoted));
}

TEST(RE2Test_597, QuoteMetaEmpty_597) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

TEST(RE2Test_597, QuoteMetaBrackets_597) {
  std::string quoted = RE2::QuoteMeta("[foo]");
  EXPECT_TRUE(RE2::FullMatch("[foo]", quoted));
}

// ============================================================
// NumberOfCapturingGroups tests
// ============================================================

TEST(RE2Test_597, NumberOfCapturingGroupsNone_597) {
  RE2 re("abc");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2Test_597, NumberOfCapturingGroupsOne_597) {
  RE2 re("(abc)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(RE2Test_597, NumberOfCapturingGroupsMultiple_597) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2Test_597, NumberOfCapturingGroupsNested_597) {
  RE2 re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2Test_597, NumberOfCapturingGroupsNonCapturing_597) {
  RE2 re("(?:abc)(def)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

// ============================================================
// NamedCapturingGroups tests
// ============================================================

TEST(RE2Test_597, NamedCapturingGroupsNone_597) {
  RE2 re("(abc)");
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2Test_597, NamedCapturingGroupsPresent_597) {
  RE2 re("(?P<name>\\w+) (?P<age>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 2);
  EXPECT_EQ(groups.at("name"), 1);
  EXPECT_EQ(groups.at("age"), 2);
}

// ============================================================
// CapturingGroupNames tests
// ============================================================

TEST(RE2Test_597, CapturingGroupNamesPresent_597) {
  RE2 re("(?P<first>\\w+) (?P<second>\\d+)");
  EXPECT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 2);
  EXPECT_EQ(names.at(1), "first");
  EXPECT_EQ(names.at(2), "second");
}

// ============================================================
// Match tests
// ============================================================

TEST(RE2Test_597, MatchUnanchored_597) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc 123 def", 0, 11, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ(submatch[0], "123");
  EXPECT_EQ(submatch[1], "123");
}

TEST(RE2Test_597, MatchAnchorStart_597) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("abc 123", 0, 7, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_TRUE(re.Match("123 abc", 0, 7, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2Test_597, MatchAnchorBoth_597) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("123 abc", 0, 7, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2Test_597, MatchWithStartpos_597) {
  RE2 re("\\d+");
  absl::string_view submatch[1];
  EXPECT_TRUE(re.Match("abc123def456", 6, 12, RE2::UNANCHORED, submatch, 1));
  EXPECT_EQ(submatch[0], "456");
}

TEST(RE2Test_597, MatchNoSubmatch_597) {
  RE2 re("abc");
  EXPECT_TRUE(re.Match("xabcy", 0, 5, RE2::UNANCHORED, nullptr, 0));
}

// ============================================================
// ProgramSize / ReverseProgramSize tests
// ============================================================

TEST(RE2Test_597, ProgramSizePositive_597) {
  RE2 re("abc");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2Test_597, ReverseProgramSizePositive_597) {
  RE2 re("abc");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ============================================================
// ProgramFanout tests
// ============================================================

TEST(RE2Test_597, ProgramFanout_597) {
  RE2 re("abc|def");
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2Test_597, ReverseProgramFanout_597) {
  RE2 re("abc|def");
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ============================================================
// PossibleMatchRange tests
// ============================================================

TEST(RE2Test_597, PossibleMatchRangeSimple_597) {
  RE2 re("abc");
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "abc");
  EXPECT_GE(max_str, "abc");
}

TEST(RE2Test_597, PossibleMatchRangeInvalid_597) {
  RE2 re("(invalid[");
  std::string min_str, max_str;
  // Invalid regex - behavior may vary but should not crash
  re.PossibleMatchRange(&min_str, &max_str, 10);
}

// ============================================================
// CheckRewriteString tests
// ============================================================

TEST(RE2Test_597, CheckRewriteStringValid_597) {
  RE2 re("(\\w+) (\\d+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1-\\2", &error));
}

TEST(RE2Test_597, CheckRewriteStringInvalidBackref_597) {
  RE2 re("(\\w+)");
  std::string error;
  // \2 doesn't exist since there's only one capture group
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ============================================================
// MaxSubmatch tests
// ============================================================

TEST(RE2Test_597, MaxSubmatchNone_597) {
  EXPECT_EQ(RE2::MaxSubmatch("no backrefs"), 0);
}

TEST(RE2Test_597, MaxSubmatchOne_597) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
}

TEST(RE2Test_597, MaxSubmatchMultiple_597) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1 \\3 \\2"), 3);
}

// ============================================================
// Rewrite tests
// ============================================================

TEST(RE2Test_597, RewriteBasic_597) {
  RE2 re("(\\w+)@(\\w+)");
  std::string out;
  absl::string_view vec[] = {"user@host", "user", "host"};
  EXPECT_TRUE(re.Rewrite(&out, "\\2!\\1", vec, 3));
  EXPECT_EQ(out, "host!user");
}

// ============================================================
// Hex, Octal, CRadix capture tests
// ============================================================

TEST(RE2Test_597, HexCapture_597) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("ff", "([0-9a-fA-F]+)", RE2::Hex(&v)));
  EXPECT_EQ(v, 255);
}

TEST(RE2Test_597, OctalCapture_597) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("77", "([0-7]+)", RE2::Octal(&v)));
  EXPECT_EQ(v, 63);
}

TEST(RE2Test_597, CRadixHex_597) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("0xff", "(0x[0-9a-fA-F]+)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 255);
}

TEST(RE2Test_597, CRadixOctal_597) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("077", "(0[0-7]*)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 63);
}

TEST(RE2Test_597, CRadixDecimal_597) {
  int v;
  EXPECT_TRUE(RE2::FullMatch("100", "(\\d+)", RE2::CRadix(&v)));
  EXPECT_EQ(v, 100);
}

// ============================================================
// String capture types
// ============================================================

TEST(RE2Test_597, CaptureStringPiece_597) {
  absl::string_view sp;
  EXPECT_TRUE(RE2::FullMatch("hello world", "(\\w+) (\\w+)", &sp));
  // sp should capture the first group
  EXPECT_EQ(sp, "hello");
}

TEST(RE2Test_597, CaptureString_597) {
  std::string s;
  EXPECT_TRUE(RE2::FullMatch("test123", "(\\w+)", &s));
  EXPECT_EQ(s, "test123");
}

// ============================================================
// Various data type captures
// ============================================================

TEST(RE2Test_597, CaptureFloat_597) {
  float f;
  EXPECT_TRUE(RE2::FullMatch("3.14", "([\\d.]+)", &f));
  EXPECT_NEAR(f, 3.14f, 0.01f);
}

TEST(RE2Test_597, CaptureDouble_597) {
  double d;
  EXPECT_TRUE(RE2::FullMatch("2.718281828", "([\\d.]+)", &d));
  EXPECT_NEAR(d, 2.718281828, 0.0001);
}

TEST(RE2Test_597, CaptureLong_597) {
  long v;
  EXPECT_TRUE(RE2::FullMatch("999999", "(\\d+)", &v));
  EXPECT_EQ(v, 999999L);
}

// ============================================================
// Boundary/edge cases
// ============================================================

TEST(RE2Test_597, FullMatchUnicodePattern_597) {
  // RE2 handles UTF-8 by default
  RE2 re("\\p{L}+");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2Test_597, LargePattern_597) {
  // Test a somewhat large alternation
  std::string pattern;
  for (int i = 0; i < 100; i++) {
    if (i > 0) pattern += "|";
    pattern += "word" + std::to_string(i);
  }
  RE2 re(pattern);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("word50", re));
  EXPECT_FALSE(RE2::FullMatch("word100", re));
}

TEST(RE2Test_597, MatchEmptyString_597) {
  RE2 re(".*");
  EXPECT_TRUE(RE2::FullMatch("", re));
}

TEST(RE2Test_597, PartialMatchAtEnd_597) {
  EXPECT_TRUE(RE2::PartialMatch("foobar", "bar$"));
}

TEST(RE2Test_597, ConsumeEmptyInput_597) {
  absl::string_view input("");
  EXPECT_FALSE(RE2::Consume(&input, "\\w+"));
}

TEST(RE2Test_597, FindAndConsumeEmptyInput_597) {
  absl::string_view input("");
  EXPECT_FALSE(RE2::FindAndConsume(&input, "\\w+"));
}

TEST(RE2Test_597, ReplaceEmptyString_597) {
  std::string str = "";
  EXPECT_FALSE(RE2::Replace(&str, "abc", "def"));
  EXPECT_EQ(str, "");
}

TEST(RE2Test_597, GlobalReplaceEmptyString_597) {
  std::string str = "";
  int count = RE2::GlobalReplace(&str, "abc", "def");
  EXPECT_EQ(count, 0);
}

TEST(RE2Test_597, OptionsQuiet_597) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("(bad[", opts);
  EXPECT_FALSE(re.ok());
}

TEST(RE2Test_597, OptionsCaseSensitiveFalse_597) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
}

TEST(RE2Test_597, MatchSubstringRange_597) {
  RE2 re("\\d+");
  absl::string_view text("abc123def456ghi");
  absl::string_view submatch[1];
  // Match only in a substring
  EXPECT_TRUE(re.Match(text, 3, 6, RE2::ANCHOR_BOTH, submatch, 1));
  EXPECT_EQ(submatch[0], "123");
}

TEST(RE2Test_597, ErrorArgOnInvalidPattern_597) {
  RE2 re("(?P<name");
  EXPECT_FALSE(re.ok());
  // error_arg should provide some info about what went wrong
  // Just verify it doesn't crash
  const std::string& earg = re.error_arg();
  (void)earg;
}

}  // namespace
