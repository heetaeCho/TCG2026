#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// Test fixture for RE2::Options
class RE2OptionsTest_17 : public ::testing::Test {
 protected:
  RE2::Options options_;
};

// ==================== Default Constructor Tests ====================

TEST_F(RE2OptionsTest_17, DefaultConstructor_PosixSyntaxIsFalse_17) {
  EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_17, DefaultConstructor_LongestMatchIsFalse_17) {
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_17, DefaultConstructor_LogErrorsIsTrue_17) {
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_17, DefaultConstructor_LiteralIsFalse_17) {
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_17, DefaultConstructor_NeverNlIsFalse_17) {
  EXPECT_FALSE(options_.never_nl());
}

TEST_F(RE2OptionsTest_17, DefaultConstructor_DotNlIsFalse_17) {
  EXPECT_FALSE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_17, DefaultConstructor_NeverCaptureIsFalse_17) {
  EXPECT_FALSE(options_.never_capture());
}

TEST_F(RE2OptionsTest_17, DefaultConstructor_CaseSensitiveIsTrue_17) {
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_17, DefaultConstructor_PerlClassesIsFalse_17) {
  EXPECT_FALSE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_17, DefaultConstructor_WordBoundaryIsFalse_17) {
  EXPECT_FALSE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_17, DefaultConstructor_OneLineIsFalse_17) {
  EXPECT_FALSE(options_.one_line());
}

TEST_F(RE2OptionsTest_17, DefaultConstructor_EncodingIsUTF8_17) {
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingUTF8);
}

// ==================== CannedOptions Constructor Tests ====================

TEST_F(RE2OptionsTest_17, Latin1Constructor_EncodingIsLatin1_17) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_17, Latin1Constructor_PosixSyntaxIsFalse_17) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_17, Latin1Constructor_LongestMatchIsFalse_17) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.longest_match());
}

TEST_F(RE2OptionsTest_17, POSIXConstructor_PosixSyntaxIsTrue_17) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_17, POSIXConstructor_LongestMatchIsTrue_17) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST_F(RE2OptionsTest_17, POSIXConstructor_EncodingIsUTF8_17) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_17, QuietConstructor_LogErrorsIsFalse_17) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST_F(RE2OptionsTest_17, QuietConstructor_PosixSyntaxIsFalse_17) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.posix_syntax());
}

// ==================== Setter/Getter Tests ====================

TEST_F(RE2OptionsTest_17, SetPosixSyntaxTrue_17) {
  options_.set_posix_syntax(true);
  EXPECT_TRUE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_17, SetPosixSyntaxFalse_17) {
  options_.set_posix_syntax(true);
  options_.set_posix_syntax(false);
  EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_17, SetLongestMatchTrue_17) {
  options_.set_longest_match(true);
  EXPECT_TRUE(options_.longest_match());
}

TEST_F(RE2OptionsTest_17, SetLongestMatchFalse_17) {
  options_.set_longest_match(true);
  options_.set_longest_match(false);
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_17, SetLogErrorsTrue_17) {
  options_.set_log_errors(false);
  options_.set_log_errors(true);
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_17, SetLogErrorsFalse_17) {
  options_.set_log_errors(false);
  EXPECT_FALSE(options_.log_errors());
}

TEST_F(RE2OptionsTest_17, SetLiteralTrue_17) {
  options_.set_literal(true);
  EXPECT_TRUE(options_.literal());
}

TEST_F(RE2OptionsTest_17, SetLiteralFalse_17) {
  options_.set_literal(true);
  options_.set_literal(false);
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_17, SetNeverNlTrue_17) {
  options_.set_never_nl(true);
  EXPECT_TRUE(options_.never_nl());
}

TEST_F(RE2OptionsTest_17, SetNeverNlFalse_17) {
  options_.set_never_nl(true);
  options_.set_never_nl(false);
  EXPECT_FALSE(options_.never_nl());
}

TEST_F(RE2OptionsTest_17, SetDotNlTrue_17) {
  options_.set_dot_nl(true);
  EXPECT_TRUE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_17, SetDotNlFalse_17) {
  options_.set_dot_nl(true);
  options_.set_dot_nl(false);
  EXPECT_FALSE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_17, SetNeverCaptureTrue_17) {
  options_.set_never_capture(true);
  EXPECT_TRUE(options_.never_capture());
}

TEST_F(RE2OptionsTest_17, SetNeverCaptureFalse_17) {
  options_.set_never_capture(true);
  options_.set_never_capture(false);
  EXPECT_FALSE(options_.never_capture());
}

TEST_F(RE2OptionsTest_17, SetCaseSensitiveTrue_17) {
  options_.set_case_sensitive(false);
  options_.set_case_sensitive(true);
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_17, SetCaseSensitiveFalse_17) {
  options_.set_case_sensitive(false);
  EXPECT_FALSE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_17, SetPerlClassesTrue_17) {
  options_.set_perl_classes(true);
  EXPECT_TRUE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_17, SetPerlClassesFalse_17) {
  options_.set_perl_classes(true);
  options_.set_perl_classes(false);
  EXPECT_FALSE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_17, SetWordBoundaryTrue_17) {
  options_.set_word_boundary(true);
  EXPECT_TRUE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_17, SetWordBoundaryFalse_17) {
  options_.set_word_boundary(true);
  options_.set_word_boundary(false);
  EXPECT_FALSE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_17, SetOneLineTrue_17) {
  options_.set_one_line(true);
  EXPECT_TRUE(options_.one_line());
}

TEST_F(RE2OptionsTest_17, SetOneLineFalse_17) {
  options_.set_one_line(true);
  options_.set_one_line(false);
  EXPECT_FALSE(options_.one_line());
}

TEST_F(RE2OptionsTest_17, SetEncodingUTF8_17) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  options_.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_17, SetEncodingLatin1_17) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_17, SetMaxMem_17) {
  options_.set_max_mem(1024 * 1024);
  EXPECT_EQ(options_.max_mem(), 1024 * 1024);
}

TEST_F(RE2OptionsTest_17, SetMaxMemZero_17) {
  options_.set_max_mem(0);
  EXPECT_EQ(options_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_17, SetMaxMemLargeValue_17) {
  int64_t large_val = static_cast<int64_t>(1) << 40;
  options_.set_max_mem(large_val);
  EXPECT_EQ(options_.max_mem(), large_val);
}

// ==================== Copy Tests ====================

TEST_F(RE2OptionsTest_17, CopyOptions_17) {
  RE2::Options src;
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
  src.set_encoding(RE2::Options::EncodingLatin1);
  src.set_max_mem(999999);

  RE2::Options dest;
  dest.Copy(src);

  EXPECT_TRUE(dest.posix_syntax());
  EXPECT_TRUE(dest.longest_match());
  EXPECT_FALSE(dest.log_errors());
  EXPECT_TRUE(dest.literal());
  EXPECT_TRUE(dest.never_nl());
  EXPECT_TRUE(dest.dot_nl());
  EXPECT_TRUE(dest.never_capture());
  EXPECT_FALSE(dest.case_sensitive());
  EXPECT_TRUE(dest.perl_classes());
  EXPECT_TRUE(dest.word_boundary());
  EXPECT_TRUE(dest.one_line());
  EXPECT_EQ(dest.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_EQ(dest.max_mem(), 999999);
}

TEST_F(RE2OptionsTest_17, CopyDefaultOptions_17) {
  RE2::Options src;
  RE2::Options dest;
  dest.set_posix_syntax(true);
  dest.set_case_sensitive(false);

  dest.Copy(src);

  EXPECT_FALSE(dest.posix_syntax());
  EXPECT_TRUE(dest.case_sensitive());
}

// ==================== Multiple Sets on Same Option ====================

TEST_F(RE2OptionsTest_17, MultipleSetsPosixSyntax_17) {
  options_.set_posix_syntax(true);
  EXPECT_TRUE(options_.posix_syntax());
  options_.set_posix_syntax(false);
  EXPECT_FALSE(options_.posix_syntax());
  options_.set_posix_syntax(true);
  EXPECT_TRUE(options_.posix_syntax());
}

// ==================== RE2 with Options ====================

TEST_F(RE2OptionsTest_17, RE2WithDefaultOptions_17) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
}

TEST_F(RE2OptionsTest_17, RE2WithPOSIXOptions_17) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  opts.set_longest_match(true);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
}

TEST_F(RE2OptionsTest_17, RE2WithLiteralOption_17) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  // With literal, "a.b" should only match the literal string "a.b"
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

TEST_F(RE2OptionsTest_17, RE2WithCaseInsensitive_17) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HeLLo", re));
}

TEST_F(RE2OptionsTest_17, RE2WithDotNl_17) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2OptionsTest_17, RE2WithoutDotNl_17) {
  RE2::Options opts;
  opts.set_dot_nl(false);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2OptionsTest_17, RE2WithNeverCapture_17) {
  RE2::Options opts;
  opts.set_never_capture(true);
  RE2 re("(a)(b)", opts);
  EXPECT_TRUE(re.ok());
  // With never_capture, NumberOfCapturingGroups should be 0
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2OptionsTest_17, RE2WithoutNeverCapture_17) {
  RE2::Options opts;
  opts.set_never_capture(false);
  RE2 re("(a)(b)", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 2);
}

TEST_F(RE2OptionsTest_17, RE2CannedOptionPOSIX_17) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
}

TEST_F(RE2OptionsTest_17, RE2CannedOptionQuiet_17) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
}

// ==================== ParseFlags Tests ====================

TEST_F(RE2OptionsTest_17, ParseFlagsDefault_17) {
  // Just ensure it returns without crashing and returns a value
  int flags = options_.ParseFlags();
  // We don't know the exact value, but it should be deterministic
  int flags2 = options_.ParseFlags();
  EXPECT_EQ(flags, flags2);
}

TEST_F(RE2OptionsTest_17, ParseFlagsChangesWithOptions_17) {
  int flags_before = options_.ParseFlags();
  options_.set_case_sensitive(false);
  int flags_after = options_.ParseFlags();
  // Changing case_sensitive should change parse flags
  EXPECT_NE(flags_before, flags_after);
}

}  // namespace re2
