#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>

// Test fixture for RE2::Options
class RE2OptionsTest_19 : public ::testing::Test {
 protected:
  re2::RE2::Options options_;
};

// ============================================================
// Default constructor tests
// ============================================================

TEST_F(RE2OptionsTest_19, DefaultConstructor_LongestMatchIsFalse_19) {
  re2::RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
}

TEST_F(RE2OptionsTest_19, DefaultConstructor_PosixSyntaxIsFalse_19) {
  re2::RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_19, DefaultConstructor_LogErrorsIsTrue_19) {
  re2::RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
}

TEST_F(RE2OptionsTest_19, DefaultConstructor_LiteralIsFalse_19) {
  re2::RE2::Options opts;
  EXPECT_FALSE(opts.literal());
}

TEST_F(RE2OptionsTest_19, DefaultConstructor_NeverNlIsFalse_19) {
  re2::RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
}

TEST_F(RE2OptionsTest_19, DefaultConstructor_DotNlIsFalse_19) {
  re2::RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
}

TEST_F(RE2OptionsTest_19, DefaultConstructor_NeverCaptureIsFalse_19) {
  re2::RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
}

TEST_F(RE2OptionsTest_19, DefaultConstructor_CaseSensitiveIsTrue_19) {
  re2::RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

TEST_F(RE2OptionsTest_19, DefaultConstructor_PerlClassesIsFalse_19) {
  re2::RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

TEST_F(RE2OptionsTest_19, DefaultConstructor_WordBoundaryIsFalse_19) {
  re2::RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

TEST_F(RE2OptionsTest_19, DefaultConstructor_OneLineIsFalse_19) {
  re2::RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
}

TEST_F(RE2OptionsTest_19, DefaultConstructor_EncodingIsUTF8_19) {
  re2::RE2::Options opts;
  EXPECT_EQ(opts.encoding(), re2::RE2::Options::EncodingUTF8);
}

// ============================================================
// CannedOptions constructor tests - Latin1
// ============================================================

TEST_F(RE2OptionsTest_19, Latin1Constructor_EncodingIsLatin1_19) {
  re2::RE2::Options opts(re2::RE2::Latin1);
  EXPECT_EQ(opts.encoding(), re2::RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_19, Latin1Constructor_PosixSyntaxIsFalse_19) {
  re2::RE2::Options opts(re2::RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_19, Latin1Constructor_LongestMatchIsFalse_19) {
  re2::RE2::Options opts(re2::RE2::Latin1);
  EXPECT_FALSE(opts.longest_match());
}

TEST_F(RE2OptionsTest_19, Latin1Constructor_LogErrorsIsTrue_19) {
  re2::RE2::Options opts(re2::RE2::Latin1);
  EXPECT_TRUE(opts.log_errors());
}

// ============================================================
// CannedOptions constructor tests - POSIX
// ============================================================

TEST_F(RE2OptionsTest_19, POSIXConstructor_PosixSyntaxIsTrue_19) {
  re2::RE2::Options opts(re2::RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_19, POSIXConstructor_LongestMatchIsTrue_19) {
  re2::RE2::Options opts(re2::RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST_F(RE2OptionsTest_19, POSIXConstructor_EncodingIsUTF8_19) {
  re2::RE2::Options opts(re2::RE2::POSIX);
  EXPECT_EQ(opts.encoding(), re2::RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_19, POSIXConstructor_LogErrorsIsTrue_19) {
  re2::RE2::Options opts(re2::RE2::POSIX);
  EXPECT_TRUE(opts.log_errors());
}

// ============================================================
// CannedOptions constructor tests - Quiet
// ============================================================

TEST_F(RE2OptionsTest_19, QuietConstructor_LogErrorsIsFalse_19) {
  re2::RE2::Options opts(re2::RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST_F(RE2OptionsTest_19, QuietConstructor_PosixSyntaxIsFalse_19) {
  re2::RE2::Options opts(re2::RE2::Quiet);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_19, QuietConstructor_LongestMatchIsFalse_19) {
  re2::RE2::Options opts(re2::RE2::Quiet);
  EXPECT_FALSE(opts.longest_match());
}

// ============================================================
// set_longest_match / longest_match tests
// ============================================================

TEST_F(RE2OptionsTest_19, SetLongestMatchTrue_19) {
  options_.set_longest_match(true);
  EXPECT_TRUE(options_.longest_match());
}

TEST_F(RE2OptionsTest_19, SetLongestMatchFalse_19) {
  options_.set_longest_match(true);
  options_.set_longest_match(false);
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_19, SetLongestMatchToggle_19) {
  options_.set_longest_match(false);
  EXPECT_FALSE(options_.longest_match());
  options_.set_longest_match(true);
  EXPECT_TRUE(options_.longest_match());
  options_.set_longest_match(false);
  EXPECT_FALSE(options_.longest_match());
}

// ============================================================
// set_posix_syntax / posix_syntax tests
// ============================================================

TEST_F(RE2OptionsTest_19, SetPosixSyntaxTrue_19) {
  options_.set_posix_syntax(true);
  EXPECT_TRUE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_19, SetPosixSyntaxFalse_19) {
  options_.set_posix_syntax(true);
  options_.set_posix_syntax(false);
  EXPECT_FALSE(options_.posix_syntax());
}

// ============================================================
// set_log_errors / log_errors tests
// ============================================================

TEST_F(RE2OptionsTest_19, SetLogErrorsFalse_19) {
  options_.set_log_errors(false);
  EXPECT_FALSE(options_.log_errors());
}

TEST_F(RE2OptionsTest_19, SetLogErrorsTrue_19) {
  options_.set_log_errors(false);
  options_.set_log_errors(true);
  EXPECT_TRUE(options_.log_errors());
}

// ============================================================
// set_literal / literal tests
// ============================================================

TEST_F(RE2OptionsTest_19, SetLiteralTrue_19) {
  options_.set_literal(true);
  EXPECT_TRUE(options_.literal());
}

TEST_F(RE2OptionsTest_19, SetLiteralFalse_19) {
  options_.set_literal(true);
  options_.set_literal(false);
  EXPECT_FALSE(options_.literal());
}

// ============================================================
// set_never_nl / never_nl tests
// ============================================================

TEST_F(RE2OptionsTest_19, SetNeverNlTrue_19) {
  options_.set_never_nl(true);
  EXPECT_TRUE(options_.never_nl());
}

TEST_F(RE2OptionsTest_19, SetNeverNlFalse_19) {
  options_.set_never_nl(true);
  options_.set_never_nl(false);
  EXPECT_FALSE(options_.never_nl());
}

// ============================================================
// set_dot_nl / dot_nl tests
// ============================================================

TEST_F(RE2OptionsTest_19, SetDotNlTrue_19) {
  options_.set_dot_nl(true);
  EXPECT_TRUE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_19, SetDotNlFalse_19) {
  options_.set_dot_nl(true);
  options_.set_dot_nl(false);
  EXPECT_FALSE(options_.dot_nl());
}

// ============================================================
// set_never_capture / never_capture tests
// ============================================================

TEST_F(RE2OptionsTest_19, SetNeverCaptureTrue_19) {
  options_.set_never_capture(true);
  EXPECT_TRUE(options_.never_capture());
}

TEST_F(RE2OptionsTest_19, SetNeverCaptureFalse_19) {
  options_.set_never_capture(true);
  options_.set_never_capture(false);
  EXPECT_FALSE(options_.never_capture());
}

// ============================================================
// set_case_sensitive / case_sensitive tests
// ============================================================

TEST_F(RE2OptionsTest_19, SetCaseSensitiveFalse_19) {
  options_.set_case_sensitive(false);
  EXPECT_FALSE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_19, SetCaseSensitiveTrue_19) {
  options_.set_case_sensitive(false);
  options_.set_case_sensitive(true);
  EXPECT_TRUE(options_.case_sensitive());
}

// ============================================================
// set_perl_classes / perl_classes tests
// ============================================================

TEST_F(RE2OptionsTest_19, SetPerlClassesTrue_19) {
  options_.set_perl_classes(true);
  EXPECT_TRUE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_19, SetPerlClassesFalse_19) {
  options_.set_perl_classes(true);
  options_.set_perl_classes(false);
  EXPECT_FALSE(options_.perl_classes());
}

// ============================================================
// set_word_boundary / word_boundary tests
// ============================================================

TEST_F(RE2OptionsTest_19, SetWordBoundaryTrue_19) {
  options_.set_word_boundary(true);
  EXPECT_TRUE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_19, SetWordBoundaryFalse_19) {
  options_.set_word_boundary(true);
  options_.set_word_boundary(false);
  EXPECT_FALSE(options_.word_boundary());
}

// ============================================================
// set_one_line / one_line tests
// ============================================================

TEST_F(RE2OptionsTest_19, SetOneLineTrue_19) {
  options_.set_one_line(true);
  EXPECT_TRUE(options_.one_line());
}

TEST_F(RE2OptionsTest_19, SetOneLineFalse_19) {
  options_.set_one_line(true);
  options_.set_one_line(false);
  EXPECT_FALSE(options_.one_line());
}

// ============================================================
// set_max_mem / max_mem tests
// ============================================================

TEST_F(RE2OptionsTest_19, SetMaxMem_19) {
  options_.set_max_mem(1024);
  EXPECT_EQ(options_.max_mem(), 1024);
}

TEST_F(RE2OptionsTest_19, SetMaxMemZero_19) {
  options_.set_max_mem(0);
  EXPECT_EQ(options_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_19, SetMaxMemLargeValue_19) {
  int64_t large_val = static_cast<int64_t>(1) << 40;  // 1 TB
  options_.set_max_mem(large_val);
  EXPECT_EQ(options_.max_mem(), large_val);
}

// ============================================================
// set_encoding / encoding tests
// ============================================================

TEST_F(RE2OptionsTest_19, SetEncodingLatin1_19) {
  options_.set_encoding(re2::RE2::Options::EncodingLatin1);
  EXPECT_EQ(options_.encoding(), re2::RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_19, SetEncodingUTF8_19) {
  options_.set_encoding(re2::RE2::Options::EncodingLatin1);
  options_.set_encoding(re2::RE2::Options::EncodingUTF8);
  EXPECT_EQ(options_.encoding(), re2::RE2::Options::EncodingUTF8);
}

// ============================================================
// Copy tests
// ============================================================

TEST_F(RE2OptionsTest_19, CopyOptions_19) {
  re2::RE2::Options src;
  src.set_longest_match(true);
  src.set_posix_syntax(true);
  src.set_log_errors(false);
  src.set_literal(true);
  src.set_never_nl(true);
  src.set_dot_nl(true);
  src.set_never_capture(true);
  src.set_case_sensitive(false);
  src.set_perl_classes(true);
  src.set_word_boundary(true);
  src.set_one_line(true);
  src.set_max_mem(2048);
  src.set_encoding(re2::RE2::Options::EncodingLatin1);

  re2::RE2::Options dst;
  dst.Copy(src);

  EXPECT_TRUE(dst.longest_match());
  EXPECT_TRUE(dst.posix_syntax());
  EXPECT_FALSE(dst.log_errors());
  EXPECT_TRUE(dst.literal());
  EXPECT_TRUE(dst.never_nl());
  EXPECT_TRUE(dst.dot_nl());
  EXPECT_TRUE(dst.never_capture());
  EXPECT_FALSE(dst.case_sensitive());
  EXPECT_TRUE(dst.perl_classes());
  EXPECT_TRUE(dst.word_boundary());
  EXPECT_TRUE(dst.one_line());
  EXPECT_EQ(dst.max_mem(), 2048);
  EXPECT_EQ(dst.encoding(), re2::RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_19, CopyDefaultOptions_19) {
  re2::RE2::Options src;
  re2::RE2::Options dst;
  dst.set_longest_match(true);
  dst.set_log_errors(false);

  dst.Copy(src);

  EXPECT_FALSE(dst.longest_match());
  EXPECT_TRUE(dst.log_errors());
}

// ============================================================
// Multiple sets of the same property
// ============================================================

TEST_F(RE2OptionsTest_19, MultipleSetsSameProperty_19) {
  options_.set_longest_match(true);
  EXPECT_TRUE(options_.longest_match());
  options_.set_longest_match(true);
  EXPECT_TRUE(options_.longest_match());
  options_.set_longest_match(false);
  EXPECT_FALSE(options_.longest_match());
  options_.set_longest_match(false);
  EXPECT_FALSE(options_.longest_match());
}

// ============================================================
// Independence of different boolean properties
// ============================================================

TEST_F(RE2OptionsTest_19, IndependenceOfBooleanProperties_19) {
  options_.set_longest_match(true);
  options_.set_posix_syntax(false);
  options_.set_literal(true);
  options_.set_case_sensitive(false);

  EXPECT_TRUE(options_.longest_match());
  EXPECT_FALSE(options_.posix_syntax());
  EXPECT_TRUE(options_.literal());
  EXPECT_FALSE(options_.case_sensitive());
  // Others should remain at defaults
  EXPECT_TRUE(options_.log_errors());
  EXPECT_FALSE(options_.never_nl());
  EXPECT_FALSE(options_.dot_nl());
  EXPECT_FALSE(options_.never_capture());
  EXPECT_FALSE(options_.perl_classes());
  EXPECT_FALSE(options_.word_boundary());
  EXPECT_FALSE(options_.one_line());
}

// ============================================================
// RE2 construction with Options and basic matching
// ============================================================

TEST_F(RE2OptionsTest_19, RE2WithDefaultOptions_19) {
  re2::RE2 re("hello", options_);
  EXPECT_TRUE(re.ok());
}

TEST_F(RE2OptionsTest_19, RE2WithLongestMatch_19) {
  options_.set_longest_match(true);
  re2::RE2 re("a+", options_);
  EXPECT_TRUE(re.ok());
}

TEST_F(RE2OptionsTest_19, RE2WithCaseInsensitive_19) {
  options_.set_case_sensitive(false);
  re2::RE2 re("hello", options_);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HeLLo", re));
}

TEST_F(RE2OptionsTest_19, RE2WithLiteralMode_19) {
  options_.set_literal(true);
  re2::RE2 re("a.b", options_);
  EXPECT_TRUE(re.ok());
  // In literal mode, "a.b" should match only literal "a.b", not "axb"
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

TEST_F(RE2OptionsTest_19, RE2WithNeverCapture_19) {
  options_.set_never_capture(true);
  re2::RE2 re("(a)(b)", options_);
  EXPECT_TRUE(re.ok());
  // With never_capture, groups should not capture
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2OptionsTest_19, RE2POSIXLongestMatch_19) {
  re2::RE2::Options opts(re2::RE2::POSIX);
  // POSIX mode should give longest match
  EXPECT_TRUE(opts.longest_match());
  EXPECT_TRUE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_19, RE2WithDotNl_19) {
  options_.set_dot_nl(true);
  re2::RE2 re("a.b", options_);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2OptionsTest_19, RE2WithoutDotNl_19) {
  options_.set_dot_nl(false);
  re2::RE2 re("a.b", options_);
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2OptionsTest_19, RE2QuietMode_19) {
  re2::RE2::Options opts(re2::RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
  // Invalid regex should not crash even in quiet mode
  re2::RE2 re("(invalid[", opts);
  EXPECT_FALSE(re.ok());
}
