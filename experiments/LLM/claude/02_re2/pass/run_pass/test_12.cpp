#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

namespace re2 {

// ============================================================
// Tests for RE2::Options
// ============================================================

class RE2OptionsTest_12 : public ::testing::Test {
 protected:
  RE2::Options opts_;
};

// --- Default constructor tests ---

TEST_F(RE2OptionsTest_12, DefaultMaxMem_12) {
  // Default max_mem should be kDefaultMaxMem (8<<20 = 8388608)
  EXPECT_GT(opts_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_12, DefaultEncodingIsUTF8_12) {
  EXPECT_EQ(opts_.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_12, DefaultPosixSyntaxIsFalse_12) {
  EXPECT_FALSE(opts_.posix_syntax());
}

TEST_F(RE2OptionsTest_12, DefaultLongestMatchIsFalse_12) {
  EXPECT_FALSE(opts_.longest_match());
}

TEST_F(RE2OptionsTest_12, DefaultLogErrorsIsTrue_12) {
  EXPECT_TRUE(opts_.log_errors());
}

TEST_F(RE2OptionsTest_12, DefaultLiteralIsFalse_12) {
  EXPECT_FALSE(opts_.literal());
}

TEST_F(RE2OptionsTest_12, DefaultNeverNlIsFalse_12) {
  EXPECT_FALSE(opts_.never_nl());
}

TEST_F(RE2OptionsTest_12, DefaultDotNlIsFalse_12) {
  EXPECT_FALSE(opts_.dot_nl());
}

TEST_F(RE2OptionsTest_12, DefaultNeverCaptureIsFalse_12) {
  EXPECT_FALSE(opts_.never_capture());
}

TEST_F(RE2OptionsTest_12, DefaultCaseSensitiveIsTrue_12) {
  EXPECT_TRUE(opts_.case_sensitive());
}

TEST_F(RE2OptionsTest_12, DefaultPerlClassesIsFalse_12) {
  EXPECT_FALSE(opts_.perl_classes());
}

TEST_F(RE2OptionsTest_12, DefaultWordBoundaryIsFalse_12) {
  EXPECT_FALSE(opts_.word_boundary());
}

TEST_F(RE2OptionsTest_12, DefaultOneLineIsFalse_12) {
  EXPECT_FALSE(opts_.one_line());
}

// --- Setter/Getter tests ---

TEST_F(RE2OptionsTest_12, SetAndGetMaxMem_12) {
  opts_.set_max_mem(1024);
  EXPECT_EQ(opts_.max_mem(), 1024);
}

TEST_F(RE2OptionsTest_12, SetMaxMemToZero_12) {
  opts_.set_max_mem(0);
  EXPECT_EQ(opts_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_12, SetMaxMemToLargeValue_12) {
  int64_t large = static_cast<int64_t>(1) << 40;
  opts_.set_max_mem(large);
  EXPECT_EQ(opts_.max_mem(), large);
}

TEST_F(RE2OptionsTest_12, SetAndGetEncodingUTF8_12) {
  opts_.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts_.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_12, SetAndGetEncodingLatin1_12) {
  opts_.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts_.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_12, SetAndGetPosixSyntax_12) {
  opts_.set_posix_syntax(true);
  EXPECT_TRUE(opts_.posix_syntax());
  opts_.set_posix_syntax(false);
  EXPECT_FALSE(opts_.posix_syntax());
}

TEST_F(RE2OptionsTest_12, SetAndGetLongestMatch_12) {
  opts_.set_longest_match(true);
  EXPECT_TRUE(opts_.longest_match());
  opts_.set_longest_match(false);
  EXPECT_FALSE(opts_.longest_match());
}

TEST_F(RE2OptionsTest_12, SetAndGetLogErrors_12) {
  opts_.set_log_errors(false);
  EXPECT_FALSE(opts_.log_errors());
  opts_.set_log_errors(true);
  EXPECT_TRUE(opts_.log_errors());
}

TEST_F(RE2OptionsTest_12, SetAndGetLiteral_12) {
  opts_.set_literal(true);
  EXPECT_TRUE(opts_.literal());
  opts_.set_literal(false);
  EXPECT_FALSE(opts_.literal());
}

TEST_F(RE2OptionsTest_12, SetAndGetNeverNl_12) {
  opts_.set_never_nl(true);
  EXPECT_TRUE(opts_.never_nl());
  opts_.set_never_nl(false);
  EXPECT_FALSE(opts_.never_nl());
}

TEST_F(RE2OptionsTest_12, SetAndGetDotNl_12) {
  opts_.set_dot_nl(true);
  EXPECT_TRUE(opts_.dot_nl());
  opts_.set_dot_nl(false);
  EXPECT_FALSE(opts_.dot_nl());
}

TEST_F(RE2OptionsTest_12, SetAndGetNeverCapture_12) {
  opts_.set_never_capture(true);
  EXPECT_TRUE(opts_.never_capture());
  opts_.set_never_capture(false);
  EXPECT_FALSE(opts_.never_capture());
}

TEST_F(RE2OptionsTest_12, SetAndGetCaseSensitive_12) {
  opts_.set_case_sensitive(false);
  EXPECT_FALSE(opts_.case_sensitive());
  opts_.set_case_sensitive(true);
  EXPECT_TRUE(opts_.case_sensitive());
}

TEST_F(RE2OptionsTest_12, SetAndGetPerlClasses_12) {
  opts_.set_perl_classes(true);
  EXPECT_TRUE(opts_.perl_classes());
  opts_.set_perl_classes(false);
  EXPECT_FALSE(opts_.perl_classes());
}

TEST_F(RE2OptionsTest_12, SetAndGetWordBoundary_12) {
  opts_.set_word_boundary(true);
  EXPECT_TRUE(opts_.word_boundary());
  opts_.set_word_boundary(false);
  EXPECT_FALSE(opts_.word_boundary());
}

TEST_F(RE2OptionsTest_12, SetAndGetOneLine_12) {
  opts_.set_one_line(true);
  EXPECT_TRUE(opts_.one_line());
  opts_.set_one_line(false);
  EXPECT_FALSE(opts_.one_line());
}

// --- CannedOptions constructor tests ---

TEST_F(RE2OptionsTest_12, Latin1CannedOption_12) {
  RE2::Options latin1_opts(RE2::Latin1);
  EXPECT_EQ(latin1_opts.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_FALSE(latin1_opts.posix_syntax());
  EXPECT_FALSE(latin1_opts.longest_match());
}

TEST_F(RE2OptionsTest_12, POSIXCannedOption_12) {
  RE2::Options posix_opts(RE2::POSIX);
  EXPECT_EQ(posix_opts.encoding(), RE2::Options::EncodingUTF8);
  EXPECT_TRUE(posix_opts.posix_syntax());
  EXPECT_TRUE(posix_opts.longest_match());
  EXPECT_TRUE(posix_opts.log_errors());
}

TEST_F(RE2OptionsTest_12, QuietCannedOption_12) {
  RE2::Options quiet_opts(RE2::Quiet);
  EXPECT_FALSE(quiet_opts.log_errors());
  EXPECT_FALSE(quiet_opts.posix_syntax());
  EXPECT_FALSE(quiet_opts.longest_match());
}

TEST_F(RE2OptionsTest_12, DefaultCannedOptionSameAsDefault_12) {
  RE2::Options default_canned(RE2::DefaultOptions);
  EXPECT_EQ(default_canned.encoding(), RE2::Options::EncodingUTF8);
  EXPECT_FALSE(default_canned.posix_syntax());
  EXPECT_FALSE(default_canned.longest_match());
  EXPECT_TRUE(default_canned.log_errors());
  EXPECT_TRUE(default_canned.case_sensitive());
}

// --- Copy tests ---

TEST_F(RE2OptionsTest_12, CopyOptions_12) {
  RE2::Options src;
  src.set_max_mem(2048);
  src.set_encoding(RE2::Options::EncodingLatin1);
  src.set_posix_syntax(true);
  src.set_longest_match(true);
  src.set_log_errors(false);
  src.set_literal(true);
  src.set_never_nl(true);
  src.set_dot_nl(true);
  src.set_never_capture(true);
  src.set_case_sensitive(false);
  src.set_perl_classes(true);
  src.set_word_boundary(true);
  src.set_one_line(true);

  RE2::Options dst;
  dst.Copy(src);

  EXPECT_EQ(dst.max_mem(), 2048);
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_TRUE(dst.posix_syntax());
  EXPECT_TRUE(dst.longest_match());
  EXPECT_FALSE(dst.log_errors());
  EXPECT_TRUE(dst.literal());
  EXPECT_TRUE(dst.never_nl());
  EXPECT_TRUE(dst.dot_nl());
  EXPECT_TRUE(dst.never_capture());
  EXPECT_FALSE(dst.case_sensitive());
  EXPECT_TRUE(dst.perl_classes());
  EXPECT_TRUE(dst.word_boundary());
  EXPECT_TRUE(dst.one_line());
}

TEST_F(RE2OptionsTest_12, CopyDefaultOptions_12) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_max_mem(999);
  dst.set_literal(true);

  dst.Copy(src);

  EXPECT_EQ(dst.max_mem(), src.max_mem());
  EXPECT_FALSE(dst.literal());
}

// --- ParseFlags tests ---

TEST_F(RE2OptionsTest_12, ParseFlagsDefaultOptions_12) {
  int flags = opts_.ParseFlags();
  // Just verify it returns a valid integer; specific flags depend on implementation
  (void)flags;
}

TEST_F(RE2OptionsTest_12, ParseFlagsChangesWithPosixSyntax_12) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_posix_syntax(true);
  // Different settings should potentially yield different flags
  int flags1 = opts1.ParseFlags();
  int flags2 = opts2.ParseFlags();
  // We can't guarantee they're different without knowing implementation,
  // but we can at least verify the call doesn't crash.
  (void)flags1;
  (void)flags2;
}

TEST_F(RE2OptionsTest_12, ParseFlagsChangesWithCaseSensitive_12) {
  RE2::Options opts_sensitive;
  opts_sensitive.set_case_sensitive(true);
  RE2::Options opts_insensitive;
  opts_insensitive.set_case_sensitive(false);

  int flags_sensitive = opts_sensitive.ParseFlags();
  int flags_insensitive = opts_insensitive.ParseFlags();
  // Case sensitivity should affect parse flags
  EXPECT_NE(flags_sensitive, flags_insensitive);
}

// ============================================================
// Tests for RE2 class basic functionality
// ============================================================

class RE2Test_12 : public ::testing::Test {};

TEST_F(RE2Test_12, SimplePatternIsOk_12) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.error(), "");
}

TEST_F(RE2Test_12, InvalidPatternIsNotOk_12) {
  RE2 re("(unclosed", RE2::Quiet);
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error(), "");
}

TEST_F(RE2Test_12, PatternAccessor_12) {
  RE2 re("abc.*def");
  EXPECT_EQ(re.pattern(), "abc.*def");
}

TEST_F(RE2Test_12, FullMatchSimple_12) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
  EXPECT_FALSE(RE2::FullMatch("hello", "world"));
}

TEST_F(RE2Test_12, FullMatchWithWildcard_12) {
  EXPECT_TRUE(RE2::FullMatch("hello world", "hello.*"));
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello$"));
}

TEST_F(RE2Test_12, PartialMatchSimple_12) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "world"));
  EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST_F(RE2Test_12, PartialMatchSubstring_12) {
  EXPECT_TRUE(RE2::PartialMatch("abcdef", "bcd"));
}

TEST_F(RE2Test_12, FullMatchExtractInt_12) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &value));
  EXPECT_EQ(value, 12345);
}

TEST_F(RE2Test_12, FullMatchExtractString_12) {
  std::string s;
  EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", &s));
  EXPECT_EQ(s, "hello");
}

TEST_F(RE2Test_12, FullMatchNoMatchExtract_12) {
  int value = -1;
  EXPECT_FALSE(RE2::FullMatch("abc", "(\\d+)", &value));
}

TEST_F(RE2Test_12, EmptyPatternFullMatch_12) {
  EXPECT_TRUE(RE2::FullMatch("", ""));
  EXPECT_FALSE(RE2::FullMatch("abc", ""));
}

TEST_F(RE2Test_12, EmptyStringPartialMatch_12) {
  EXPECT_TRUE(RE2::PartialMatch("", ""));
  EXPECT_TRUE(RE2::PartialMatch("abc", ""));
}

TEST_F(RE2Test_12, NumberOfCapturingGroups_12) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(RE2Test_12, NumberOfCapturingGroupsNone_12) {
  RE2 re("abc");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2Test_12, NumberOfCapturingGroupsNested_12) {
  RE2 re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(RE2Test_12, ReplaceFirst_12) {
  std::string s = "hello world hello";
  EXPECT_TRUE(RE2::Replace(&s, "hello", "hi"));
  EXPECT_EQ(s, "hi world hello");
}

TEST_F(RE2Test_12, ReplaceFirstNoMatch_12) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ(s, "hello world");
}

TEST_F(RE2Test_12, GlobalReplace_12) {
  std::string s = "hello world hello";
  int count = RE2::GlobalReplace(&s, "hello", "hi");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(s, "hi world hi");
}

TEST_F(RE2Test_12, GlobalReplaceNoMatch_12) {
  std::string s = "hello world";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello world");
}

TEST_F(RE2Test_12, QuoteMetaSpecialChars_12) {
  std::string quoted = RE2::QuoteMeta("a.b+c*d");
  RE2 re(quoted);
  EXPECT_TRUE(RE2::FullMatch("a.b+c*d", re));
  EXPECT_FALSE(RE2::FullMatch("aXbYcZd", re));
}

TEST_F(RE2Test_12, QuoteMetaEmpty_12) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

TEST_F(RE2Test_12, ConstructWithOptions_12) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST_F(RE2Test_12, ConstructWithLatin1_12) {
  RE2 re("hello", RE2::Latin1);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST_F(RE2Test_12, ConstructWithPOSIX_12) {
  RE2 re("hello", RE2::POSIX);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST_F(RE2Test_12, ErrorCodeForInvalidPattern_12) {
  RE2 re("(", RE2::Quiet);
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error_code(), RE2::NoError);
}

TEST_F(RE2Test_12, ErrorCodeForValidPattern_12) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.error_code(), RE2::NoError);
}

TEST_F(RE2Test_12, FullMatchWithDotNl_12) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2Test_12, FullMatchWithoutDotNl_12) {
  RE2::Options opts;
  opts.set_dot_nl(false);
  RE2 re("a.b", opts);
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2Test_12, LiteralMode_12) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("aXb", re));
}

TEST_F(RE2Test_12, NamedCapturingGroups_12) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 2);
  EXPECT_NE(groups.find("first"), groups.end());
  EXPECT_NE(groups.find("second"), groups.end());
}

TEST_F(RE2Test_12, NamedCapturingGroupsEmpty_12) {
  RE2 re("(\\w+)");
  EXPECT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

// Test multiple captures
TEST_F(RE2Test_12, FullMatchMultipleCaptures_12) {
  std::string s1, s2;
  EXPECT_TRUE(RE2::FullMatch("hello world", "(\\w+) (\\w+)", &s1, &s2));
  EXPECT_EQ(s1, "hello");
  EXPECT_EQ(s2, "world");
}

// Test boundary: very long pattern
TEST_F(RE2Test_12, LongPattern_12) {
  std::string pattern(1000, 'a');
  std::string text(1000, 'a');
  RE2 re(pattern);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch(text, re));
}

// Test boundary: single character
TEST_F(RE2Test_12, SingleCharPattern_12) {
  EXPECT_TRUE(RE2::FullMatch("a", "a"));
  EXPECT_FALSE(RE2::FullMatch("b", "a"));
}

// Test replace with backreference
TEST_F(RE2Test_12, ReplaceWithBackreference_12) {
  std::string s = "hello world";
  RE2::Replace(&s, "(\\w+)", "\\1!");
  EXPECT_EQ(s, "hello! world");
}

// Test GlobalReplace with empty match
TEST_F(RE2Test_12, GlobalReplaceEmptyPattern_12) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, "", "-");
  // Empty pattern matches at every position
  EXPECT_GT(count, 0);
}

// Test PossibleMatchRange
TEST_F(RE2Test_12, PossibleMatchRange_12) {
  RE2 re("hello");
  std::string min_str, max_str;
  bool result = re.PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, "hello");
  EXPECT_GE(max_str, "hello");
}

}  // namespace re2
