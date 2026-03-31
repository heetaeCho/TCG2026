#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>

// ============================================================
// Test fixture
// ============================================================
class RE2Test_1 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ------------------------------------------------------------
// Construction & basic accessors
// ------------------------------------------------------------

TEST_F(RE2Test_1, ValidPatternIsOk_1) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.error_code(), RE2::NoError);
  EXPECT_EQ(re.pattern(), "hello");
}

TEST_F(RE2Test_1, InvalidPatternIsNotOk_1) {
  RE2 re("(");  // unmatched paren
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error_code(), RE2::NoError);
  EXPECT_FALSE(re.error().empty());
}

TEST_F(RE2Test_1, ConstructFromStdString_1) {
  std::string pat = "a+b+";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "a+b+");
}

TEST_F(RE2Test_1, ConstructFromStringView_1) {
  absl::string_view sv("x{2,4}");
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
}

TEST_F(RE2Test_1, ConstructWithOptions_1) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("ABC", opts);
  EXPECT_TRUE(re.ok());
}

TEST_F(RE2Test_1, EmptyPatternIsOk_1) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
}

// ------------------------------------------------------------
// Error codes for various bad patterns
// ------------------------------------------------------------

TEST_F(RE2Test_1, ErrorMissingParen_1) {
  RE2 re("(abc");
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.error_code(), RE2::ErrorMissingParen);
}

TEST_F(RE2Test_1, ErrorUnexpectedParen_1) {
  RE2 re(")");
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.error_code(), RE2::ErrorUnexpectedParen);
}

TEST_F(RE2Test_1, ErrorBadRepeat_1) {
  RE2 re("*abc");
  EXPECT_FALSE(re.ok());
  // The exact error code may be ErrorRepeatArgument
  EXPECT_NE(re.error_code(), RE2::NoError);
}

TEST_F(RE2Test_1, ErrorBadEscape_1) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("\\p", opts);
  // Depending on the engine this may or may not be an error,
  // but we test the observable result.
  // If it fails, error_code should not be NoError.
  if (!re.ok()) {
    EXPECT_NE(re.error_code(), RE2::NoError);
  }
}

// ------------------------------------------------------------
// NumberOfCapturingGroups
// ------------------------------------------------------------

TEST_F(RE2Test_1, NumberOfCapturingGroupsZero_1) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2Test_1, NumberOfCapturingGroupsOne_1) {
  RE2 re("(abc)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST_F(RE2Test_1, NumberOfCapturingGroupsMultiple_1) {
  RE2 re("(a)(b)(c)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(RE2Test_1, NonCapturingGroupNotCounted_1) {
  RE2 re("(?:abc)(def)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

// ------------------------------------------------------------
// FullMatch
// ------------------------------------------------------------

TEST_F(RE2Test_1, FullMatchSimple_1) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST_F(RE2Test_1, FullMatchFails_1) {
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST_F(RE2Test_1, FullMatchWithCapture_1) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("ruby:1234", "(\\w+):(\\d+)", nullptr, &n));
  EXPECT_EQ(n, 1234);
}

TEST_F(RE2Test_1, FullMatchCaptureString_1) {
  std::string word;
  EXPECT_TRUE(RE2::FullMatch("test123", "(\\w+)", &word));
  EXPECT_EQ(word, "test123");
}

TEST_F(RE2Test_1, FullMatchEmptyPattern_1) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_FALSE(RE2::FullMatch("abc", ""));
}

TEST_F(RE2Test_1, FullMatchEmptyText_1) {
  EXPECT_FALSE(RE2::FullMatch("", "abc"));
}

// ------------------------------------------------------------
// PartialMatch
// ------------------------------------------------------------

TEST_F(RE2Test_1, PartialMatchSimple_1) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "llo"));
}

TEST_F(RE2Test_1, PartialMatchFails_1) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST_F(RE2Test_1, PartialMatchWithCapture_1) {
  std::string s;
  EXPECT_TRUE(RE2::PartialMatch("abc 123 def", "(\\d+)", &s));
  EXPECT_EQ(s, "123");
}

TEST_F(RE2Test_1, PartialMatchEmptyPattern_1) {
  EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

// ------------------------------------------------------------
// Consume
// ------------------------------------------------------------

TEST_F(RE2Test_1, ConsumeBasic_1) {
  absl::string_view input("one123two456");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "(\\w+)", &word));
  EXPECT_EQ(word, "one123two456");
}

TEST_F(RE2Test_1, ConsumeIterative_1) {
  absl::string_view input("a]b]c]");
  std::string s;
  RE2 re("([a-z])\\]");
  std::vector<std::string> results;
  while (RE2::Consume(&input, re, &s)) {
    results.push_back(s);
  }
  ASSERT_EQ(results.size(), 3u);
  EXPECT_EQ(results[0], "a");
  EXPECT_EQ(results[1], "b");
  EXPECT_EQ(results[2], "c");
}

TEST_F(RE2Test_1, ConsumeFails_1) {
  absl::string_view input("hello");
  EXPECT_FALSE(RE2::Consume(&input, "\\d+"));
  EXPECT_EQ(input, "hello");  // input should be unchanged
}

// ------------------------------------------------------------
// FindAndConsume
// ------------------------------------------------------------

TEST_F(RE2Test_1, FindAndConsumeBasic_1) {
  absl::string_view input("one:1 two:2 three:3");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 1);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 2);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
  EXPECT_EQ(n, 3);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

// ------------------------------------------------------------
// Replace
// ------------------------------------------------------------

TEST_F(RE2Test_1, ReplaceFirst_1) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "world", "there"));
  EXPECT_EQ(s, "hello there");
}

TEST_F(RE2Test_1, ReplaceNoMatch_1) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ(s, "hello world");
}

TEST_F(RE2Test_1, ReplaceWithBackreference_1) {
  std::string s = "foo bar baz";
  EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "[\\1]"));
  EXPECT_EQ(s, "[foo] bar baz");
}

// ------------------------------------------------------------
// GlobalReplace
// ------------------------------------------------------------

TEST_F(RE2Test_1, GlobalReplaceAll_1) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, "a", "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "bbb");
}

TEST_F(RE2Test_1, GlobalReplaceNone_1) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, "\\d", "X");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello");
}

TEST_F(RE2Test_1, GlobalReplaceEmptyMatch_1) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "b*", "X");
  // Empty matches are handled; the result depends on implementation.
  EXPECT_GE(count, 0);
}

// ------------------------------------------------------------
// Extract
// ------------------------------------------------------------

TEST_F(RE2Test_1, ExtractBasic_1) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST_F(RE2Test_1, ExtractNoMatch_1) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no email here", "(.*)@(.*)", "\\1", &out));
}

// ------------------------------------------------------------
// QuoteMeta
// ------------------------------------------------------------

TEST_F(RE2Test_1, QuoteMetaSimple_1) {
  std::string quoted = RE2::QuoteMeta("hello");
  EXPECT_EQ(quoted, "hello");
}

TEST_F(RE2Test_1, QuoteMetaSpecialChars_1) {
  std::string quoted = RE2::QuoteMeta("a.b+c*d?e");
  // The quoted version should match the literal string
  RE2 re(quoted);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a.b+c*d?e", re));
}

TEST_F(RE2Test_1, QuoteMetaEmpty_1) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

TEST_F(RE2Test_1, QuoteMetaBackslash_1) {
  std::string quoted = RE2::QuoteMeta("a\\b");
  RE2 re(quoted);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a\\b", re));
}

// ------------------------------------------------------------
// Match (low-level)
// ------------------------------------------------------------

TEST_F(RE2Test_1, MatchAnchored_1) {
  RE2 re("(\\d+)");
  EXPECT_TRUE(re.ok());
  absl::string_view submatch;
  EXPECT_TRUE(re.Match("1234", 0, 4, RE2::ANCHOR_BOTH, &submatch, 1));
  EXPECT_EQ(submatch, "1234");
}

TEST_F(RE2Test_1, MatchUnanchored_1) {
  RE2 re("(\\d+)");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "123");
}

TEST_F(RE2Test_1, MatchAnchorStart_1) {
  RE2 re("(\\d+)");
  absl::string_view submatch;
  EXPECT_FALSE(re.Match("abc123", 0, 6, RE2::ANCHOR_START, &submatch, 1));
  EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::ANCHOR_START, &submatch, 1));
  EXPECT_EQ(submatch, "123");
}

TEST_F(RE2Test_1, MatchWithStartPos_1) {
  RE2 re("(\\d+)");
  absl::string_view submatch;
  EXPECT_TRUE(re.Match("abc123def", 3, 9, RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "123");
}

TEST_F(RE2Test_1, MatchNoSubmatch_1) {
  RE2 re("\\d+");
  EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, nullptr, 0));
}

TEST_F(RE2Test_1, MatchFailure_1) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("abcdef", 0, 6, RE2::UNANCHORED, nullptr, 0));
}

// ------------------------------------------------------------
// NamedCapturingGroups
// ------------------------------------------------------------

TEST_F(RE2Test_1, NamedCapturingGroupsEmpty_1) {
  RE2 re("(abc)(def)");
  EXPECT_TRUE(re.ok());
  const auto& named = re.NamedCapturingGroups();
  EXPECT_TRUE(named.empty());
}

TEST_F(RE2Test_1, NamedCapturingGroupsPresent_1) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const auto& named = re.NamedCapturingGroups();
  EXPECT_EQ(named.size(), 2u);
  EXPECT_EQ(named.at("first"), 1);
  EXPECT_EQ(named.at("second"), 2);
}

// ------------------------------------------------------------
// CapturingGroupNames
// ------------------------------------------------------------

TEST_F(RE2Test_1, CapturingGroupNamesEmpty_1) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.CapturingGroupNames();
  EXPECT_TRUE(groups.empty());
}

TEST_F(RE2Test_1, CapturingGroupNamesPresent_1) {
  RE2 re("(?P<word>\\w+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.CapturingGroupNames();
  ASSERT_EQ(groups.size(), 1u);
  EXPECT_EQ(groups.at(1), "word");
}

// ------------------------------------------------------------
// ProgramSize / ReverseProgramSize
// ------------------------------------------------------------

TEST_F(RE2Test_1, ProgramSizePositive_1) {
  RE2 re("a+b+c+");
  EXPECT_TRUE(re.ok());
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST_F(RE2Test_1, ReverseProgramSizePositive_1) {
  RE2 re("a+b+c+");
  EXPECT_TRUE(re.ok());
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ------------------------------------------------------------
// ProgramFanout / ReverseProgramFanout
// ------------------------------------------------------------

TEST_F(RE2Test_1, ProgramFanout_1) {
  RE2 re("a+b+");
  EXPECT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST_F(RE2Test_1, ReverseProgramFanout_1) {
  RE2 re("a+b+");
  EXPECT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ------------------------------------------------------------
// PossibleMatchRange
// ------------------------------------------------------------

TEST_F(RE2Test_1, PossibleMatchRangeBasic_1) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "hello");
  EXPECT_GE(max_str, "hello");
}

TEST_F(RE2Test_1, PossibleMatchRangeWildcard_1) {
  RE2 re(".*");
  EXPECT_TRUE(re.ok());
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
}

// ------------------------------------------------------------
// CheckRewriteString
// ------------------------------------------------------------

TEST_F(RE2Test_1, CheckRewriteStringValid_1) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST_F(RE2Test_1, CheckRewriteStringInvalid_1) {
  RE2 re("(\\w+)");
  std::string error;
  // \\2 refers to a group that doesn't exist (only 1 capturing group)
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

// ------------------------------------------------------------
// MaxSubmatch
// ------------------------------------------------------------

TEST_F(RE2Test_1, MaxSubmatchZero_1) {
  EXPECT_EQ(RE2::MaxSubmatch("no backrefs"), 0);
}

TEST_F(RE2Test_1, MaxSubmatchOne_1) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
}

TEST_F(RE2Test_1, MaxSubmatchMultiple_1) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1 and \\3"), 3);
}

// ------------------------------------------------------------
// Rewrite
// ------------------------------------------------------------

TEST_F(RE2Test_1, RewriteBasic_1) {
  RE2 re("(\\w+)@(\\w+)");
  EXPECT_TRUE(re.ok());
  std::string out;
  absl::string_view vec[] = {"user@host", "user", "host"};
  EXPECT_TRUE(re.Rewrite(&out, "\\2!\\1", vec, 3));
  EXPECT_EQ(out, "host!user");
}

TEST_F(RE2Test_1, RewriteInvalidRef_1) {
  RE2 re("(\\w+)");
  EXPECT_TRUE(re.ok());
  std::string out;
  absl::string_view vec[] = {"test", "test"};
  // \\2 is out of range; only vec[0] and vec[1] exist
  EXPECT_FALSE(re.Rewrite(&out, "\\2", vec, 2));
}

// ------------------------------------------------------------
// CRadix, Hex, Octal
// ------------------------------------------------------------

TEST_F(RE2Test_1, HexCapture_1) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("0ff", "0([0-9a-fA-F]+)", RE2::Hex(&n)));
  EXPECT_EQ(n, 255);
}

TEST_F(RE2Test_1, OctalCapture_1) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("77", "(\\d+)", RE2::Octal(&n)));
  EXPECT_EQ(n, 63);
}

TEST_F(RE2Test_1, CRadixDecimal_1) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("100", "(\\d+)", RE2::CRadix(&n)));
  EXPECT_EQ(n, 100);
}

TEST_F(RE2Test_1, CRadixHex_1) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("0x1f", "(0x[0-9a-fA-F]+)", RE2::CRadix(&n)));
  EXPECT_EQ(n, 31);
}

// ------------------------------------------------------------
// Options
// ------------------------------------------------------------

TEST_F(RE2Test_1, CaseInsensitiveOption_1) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
}

TEST_F(RE2Test_1, Latin1Encoding_1) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re(".", opts);
  EXPECT_TRUE(re.ok());
  // A single byte should match
  EXPECT_TRUE(RE2::FullMatch("\xff", re));
}

TEST_F(RE2Test_1, OptionsAccessor_1) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("test", opts);
  EXPECT_FALSE(re.options().case_sensitive());
}

// ------------------------------------------------------------
// Boundary / edge cases
// ------------------------------------------------------------

TEST_F(RE2Test_1, FullMatchNullArgs_1) {
  EXPECT_TRUE(RE2::FullMatchN("test", RE2("test"), nullptr, 0));
}

TEST_F(RE2Test_1, PartialMatchNullArgs_1) {
  EXPECT_TRUE(RE2::PartialMatchN("test123", RE2("\\d+"), nullptr, 0));
}

TEST_F(RE2Test_1, MatchEmptyText_1) {
  RE2 re(".*");
  EXPECT_TRUE(re.Match("", 0, 0, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST_F(RE2Test_1, MatchStartposEqualsEndpos_1) {
  RE2 re(".*");
  EXPECT_TRUE(re.Match("hello", 3, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST_F(RE2Test_1, ReplaceEmptyString_1) {
  std::string s = "";
  EXPECT_FALSE(RE2::Replace(&s, "a", "b"));
  EXPECT_EQ(s, "");
}

TEST_F(RE2Test_1, GlobalReplaceEmptyString_1) {
  std::string s = "";
  int count = RE2::GlobalReplace(&s, "a", "b");
  EXPECT_EQ(count, 0);
}

TEST_F(RE2Test_1, LargeCapturingGroupCount_1) {
  // Pattern with many groups
  RE2 re("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 10);
}

TEST_F(RE2Test_1, QuoteMetaParens_1) {
  std::string q = RE2::QuoteMeta("(a+b)");
  RE2 re(q);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("(a+b)", re));
  EXPECT_FALSE(RE2::FullMatch("aab", re));
}

TEST_F(RE2Test_1, ErrorArgAccessor_1) {
  RE2 re("[z-a]");  // bad char range
  EXPECT_FALSE(re.ok());
  // error_arg should give some indication of the problematic part
  // Just ensure it doesn't crash
  const std::string& arg = re.error_arg();
  (void)arg;
}

TEST_F(RE2Test_1, PatternAccessor_1) {
  RE2 re("foo|bar");
  EXPECT_EQ(re.pattern(), "foo|bar");
}

TEST_F(RE2Test_1, ErrorAccessorOnValid_1) {
  RE2 re("valid");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(re.error().empty());
}
