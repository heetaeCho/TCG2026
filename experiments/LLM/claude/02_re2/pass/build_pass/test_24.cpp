#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// ============================================================
// Tests for RE2::Options default constructor
// ============================================================

TEST(RE2OptionsTest_24, DefaultConstructorNeverNlIsFalse_24) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_24, DefaultConstructorDotNlIsFalse_24) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_24, DefaultConstructorPosixSyntaxIsFalse_24) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_24, DefaultConstructorLongestMatchIsFalse_24) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_24, DefaultConstructorLogErrorsIsTrue_24) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_24, DefaultConstructorLiteralIsFalse_24) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_24, DefaultConstructorNeverCaptureIsFalse_24) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_24, DefaultConstructorCaseSensitiveIsTrue_24) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_24, DefaultConstructorPerlClassesIsFalse_24) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_24, DefaultConstructorWordBoundaryIsFalse_24) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_24, DefaultConstructorOneLineIsFalse_24) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
}

TEST(RE2OptionsTest_24, DefaultConstructorEncodingIsUTF8_24) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// ============================================================
// Tests for RE2::Options CannedOptions constructors
// ============================================================

TEST(RE2OptionsTest_24, Latin1OptionSetsEncodingLatin1_24) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_24, Latin1OptionPosixSyntaxIsFalse_24) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_24, Latin1OptionLongestMatchIsFalse_24) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_24, Latin1OptionLogErrorsIsTrue_24) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_24, POSIXOptionSetsPosixSyntax_24) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_24, POSIXOptionSetsLongestMatch_24) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_24, POSIXOptionEncodingIsUTF8_24) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_24, QuietOptionLogErrorsIsFalse_24) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_24, QuietOptionNeverNlIsFalse_24) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_24, QuietOptionCaseSensitiveIsTrue_24) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_TRUE(opts.case_sensitive());
}

// ============================================================
// Tests for setters and getters
// ============================================================

TEST(RE2OptionsTest_24, SetNeverNlTrue_24) {
  RE2::Options opts;
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
}

TEST(RE2OptionsTest_24, SetNeverNlFalse_24) {
  RE2::Options opts;
  opts.set_never_nl(true);
  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_24, SetDotNlTrue_24) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
}

TEST(RE2OptionsTest_24, SetDotNlFalse_24) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_24, SetPosixSyntaxTrue_24) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_24, SetPosixSyntaxFalse_24) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_24, SetLongestMatchTrue_24) {
  RE2::Options opts;
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_24, SetLongestMatchFalse_24) {
  RE2::Options opts;
  opts.set_longest_match(true);
  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_24, SetLogErrorsTrue_24) {
  RE2::Options opts;
  opts.set_log_errors(false);
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_24, SetLogErrorsFalse_24) {
  RE2::Options opts;
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_24, SetLiteralTrue_24) {
  RE2::Options opts;
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
}

TEST(RE2OptionsTest_24, SetLiteralFalse_24) {
  RE2::Options opts;
  opts.set_literal(true);
  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_24, SetNeverCaptureTrue_24) {
  RE2::Options opts;
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
}

TEST(RE2OptionsTest_24, SetNeverCaptureFalse_24) {
  RE2::Options opts;
  opts.set_never_capture(true);
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_24, SetCaseSensitiveTrue_24) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_24, SetCaseSensitiveFalse_24) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
}

TEST(RE2OptionsTest_24, SetPerlClassesTrue_24) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
}

TEST(RE2OptionsTest_24, SetPerlClassesFalse_24) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_24, SetWordBoundaryTrue_24) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
}

TEST(RE2OptionsTest_24, SetWordBoundaryFalse_24) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_24, SetOneLineTrue_24) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
}

TEST(RE2OptionsTest_24, SetOneLineFalse_24) {
  RE2::Options opts;
  opts.set_one_line(true);
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

TEST(RE2OptionsTest_24, SetEncodingLatin1_24) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_24, SetEncodingUTF8_24) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_24, SetMaxMem_24) {
  RE2::Options opts;
  opts.set_max_mem(1024 * 1024);
  EXPECT_EQ(opts.max_mem(), 1024 * 1024);
}

TEST(RE2OptionsTest_24, SetMaxMemZero_24) {
  RE2::Options opts;
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_24, SetMaxMemLargeValue_24) {
  RE2::Options opts;
  int64_t large_val = static_cast<int64_t>(1) << 40;
  opts.set_max_mem(large_val);
  EXPECT_EQ(opts.max_mem(), large_val);
}

// ============================================================
// Tests for Copy
// ============================================================

TEST(RE2OptionsTest_24, CopyCopiesAllFields_24) {
  RE2::Options src;
  src.set_never_nl(true);
  src.set_dot_nl(true);
  src.set_posix_syntax(true);
  src.set_longest_match(true);
  src.set_log_errors(false);
  src.set_literal(true);
  src.set_never_capture(true);
  src.set_case_sensitive(false);
  src.set_perl_classes(true);
  src.set_word_boundary(true);
  src.set_one_line(true);
  src.set_encoding(RE2::Options::EncodingLatin1);
  src.set_max_mem(12345);

  RE2::Options dst;
  dst.Copy(src);

  EXPECT_EQ(dst.never_nl(), true);
  EXPECT_EQ(dst.dot_nl(), true);
  EXPECT_EQ(dst.posix_syntax(), true);
  EXPECT_EQ(dst.longest_match(), true);
  EXPECT_EQ(dst.log_errors(), false);
  EXPECT_EQ(dst.literal(), true);
  EXPECT_EQ(dst.never_capture(), true);
  EXPECT_EQ(dst.case_sensitive(), false);
  EXPECT_EQ(dst.perl_classes(), true);
  EXPECT_EQ(dst.word_boundary(), true);
  EXPECT_EQ(dst.one_line(), true);
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_EQ(dst.max_mem(), 12345);
}

TEST(RE2OptionsTest_24, CopyDefaultOptions_24) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_never_nl(true);
  dst.set_case_sensitive(false);

  dst.Copy(src);

  EXPECT_FALSE(dst.never_nl());
  EXPECT_TRUE(dst.case_sensitive());
}

// ============================================================
// Tests for RE2 with Options (integration-like, still black box)
// ============================================================

TEST(RE2OptionsTest_24, NeverNlAffectsMatching_24) {
  RE2::Options opts;
  opts.set_never_nl(true);
  RE2 re(".", opts);
  EXPECT_TRUE(re.ok());
  // With never_nl, '.' should not match '\n'
  EXPECT_FALSE(RE2::FullMatch("\n", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
}

TEST(RE2OptionsTest_24, NeverNlFalseAllowsDotToMatchNewline_24) {
  // By default never_nl is false. '.' still does not match '\n' unless dot_nl is set.
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re(".", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("\n", re));
}

TEST(RE2OptionsTest_24, DotNlAllowsDotToMatchNewline_24) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re(".", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("\n", re));
}

TEST(RE2OptionsTest_24, DotNlFalseDoesNotMatchNewline_24) {
  RE2::Options opts;
  opts.set_dot_nl(false);
  RE2 re(".", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("\n", re));
}

TEST(RE2OptionsTest_24, CaseInsensitiveMatching_24) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2OptionsTest_24, CaseSensitiveMatching_24) {
  RE2::Options opts;
  opts.set_case_sensitive(true);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
}

TEST(RE2OptionsTest_24, LiteralMatchingSpecialChars_24) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  // Literal mode: "a.b" matches literally, not as regex
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

TEST(RE2OptionsTest_24, PosixSyntaxOption_24) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_24, NeverCaptureOption_24) {
  RE2::Options opts;
  opts.set_never_capture(true);
  RE2 re("(\\d+)", opts);
  EXPECT_TRUE(re.ok());
  // With never_capture, groups are non-capturing
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2OptionsTest_24, NeverCaptureOffStillCaptures_24) {
  RE2::Options opts;
  opts.set_never_capture(false);
  RE2 re("(\\d+)", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

// ============================================================
// Tests for toggling options multiple times
// ============================================================

TEST(RE2OptionsTest_24, ToggleNeverNlMultipleTimes_24) {
  RE2::Options opts;
  for (int i = 0; i < 10; ++i) {
    opts.set_never_nl(true);
    EXPECT_TRUE(opts.never_nl());
    opts.set_never_nl(false);
    EXPECT_FALSE(opts.never_nl());
  }
}

TEST(RE2OptionsTest_24, SetMaxMemMultipleTimes_24) {
  RE2::Options opts;
  opts.set_max_mem(100);
  EXPECT_EQ(opts.max_mem(), 100);
  opts.set_max_mem(200);
  EXPECT_EQ(opts.max_mem(), 200);
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
}

}  // namespace re2
