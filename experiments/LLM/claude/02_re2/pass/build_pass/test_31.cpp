#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// Test fixture for RE2::Options
class RE2OptionsTest_31 : public ::testing::Test {
 protected:
  RE2::Options options_;
};

// ==================== Default Constructor Tests ====================

TEST_F(RE2OptionsTest_31, DefaultConstructor_CaseSensitiveIsTrue_31) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

TEST_F(RE2OptionsTest_31, DefaultConstructor_PosixSyntaxIsFalse_31) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_31, DefaultConstructor_LongestMatchIsFalse_31) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
}

TEST_F(RE2OptionsTest_31, DefaultConstructor_LogErrorsIsTrue_31) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
}

TEST_F(RE2OptionsTest_31, DefaultConstructor_LiteralIsFalse_31) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
}

TEST_F(RE2OptionsTest_31, DefaultConstructor_NeverNlIsFalse_31) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
}

TEST_F(RE2OptionsTest_31, DefaultConstructor_DotNlIsFalse_31) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
}

TEST_F(RE2OptionsTest_31, DefaultConstructor_NeverCaptureIsFalse_31) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
}

TEST_F(RE2OptionsTest_31, DefaultConstructor_PerlClassesIsFalse_31) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

TEST_F(RE2OptionsTest_31, DefaultConstructor_WordBoundaryIsFalse_31) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

TEST_F(RE2OptionsTest_31, DefaultConstructor_OneLineIsFalse_31) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
}

TEST_F(RE2OptionsTest_31, DefaultConstructor_EncodingIsUTF8_31) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// ==================== CannedOptions Constructor Tests ====================

TEST_F(RE2OptionsTest_31, Latin1Constructor_EncodingIsLatin1_31) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_31, Latin1Constructor_CaseSensitiveIsTrue_31) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_TRUE(opts.case_sensitive());
}

TEST_F(RE2OptionsTest_31, Latin1Constructor_PosixSyntaxIsFalse_31) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_31, Latin1Constructor_LongestMatchIsFalse_31) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.longest_match());
}

TEST_F(RE2OptionsTest_31, POSIXConstructor_PosixSyntaxIsTrue_31) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_31, POSIXConstructor_LongestMatchIsTrue_31) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST_F(RE2OptionsTest_31, POSIXConstructor_EncodingIsUTF8_31) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_31, QuietConstructor_LogErrorsIsFalse_31) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST_F(RE2OptionsTest_31, QuietConstructor_PosixSyntaxIsFalse_31) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.posix_syntax());
}

// ==================== Setter/Getter Tests ====================

TEST_F(RE2OptionsTest_31, SetCaseSensitiveFalse_31) {
  options_.set_case_sensitive(false);
  EXPECT_FALSE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_31, SetCaseSensitiveTrue_31) {
  options_.set_case_sensitive(false);
  options_.set_case_sensitive(true);
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_31, SetPosixSyntaxTrue_31) {
  options_.set_posix_syntax(true);
  EXPECT_TRUE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_31, SetPosixSyntaxFalse_31) {
  options_.set_posix_syntax(true);
  options_.set_posix_syntax(false);
  EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_31, SetLongestMatchTrue_31) {
  options_.set_longest_match(true);
  EXPECT_TRUE(options_.longest_match());
}

TEST_F(RE2OptionsTest_31, SetLongestMatchFalse_31) {
  options_.set_longest_match(true);
  options_.set_longest_match(false);
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_31, SetLogErrorsFalse_31) {
  options_.set_log_errors(false);
  EXPECT_FALSE(options_.log_errors());
}

TEST_F(RE2OptionsTest_31, SetLogErrorsTrue_31) {
  options_.set_log_errors(false);
  options_.set_log_errors(true);
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_31, SetLiteralTrue_31) {
  options_.set_literal(true);
  EXPECT_TRUE(options_.literal());
}

TEST_F(RE2OptionsTest_31, SetLiteralFalse_31) {
  options_.set_literal(true);
  options_.set_literal(false);
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_31, SetNeverNlTrue_31) {
  options_.set_never_nl(true);
  EXPECT_TRUE(options_.never_nl());
}

TEST_F(RE2OptionsTest_31, SetNeverNlFalse_31) {
  options_.set_never_nl(true);
  options_.set_never_nl(false);
  EXPECT_FALSE(options_.never_nl());
}

TEST_F(RE2OptionsTest_31, SetDotNlTrue_31) {
  options_.set_dot_nl(true);
  EXPECT_TRUE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_31, SetDotNlFalse_31) {
  options_.set_dot_nl(true);
  options_.set_dot_nl(false);
  EXPECT_FALSE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_31, SetNeverCaptureTrue_31) {
  options_.set_never_capture(true);
  EXPECT_TRUE(options_.never_capture());
}

TEST_F(RE2OptionsTest_31, SetNeverCaptureFalse_31) {
  options_.set_never_capture(true);
  options_.set_never_capture(false);
  EXPECT_FALSE(options_.never_capture());
}

TEST_F(RE2OptionsTest_31, SetPerlClassesTrue_31) {
  options_.set_perl_classes(true);
  EXPECT_TRUE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_31, SetPerlClassesFalse_31) {
  options_.set_perl_classes(true);
  options_.set_perl_classes(false);
  EXPECT_FALSE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_31, SetWordBoundaryTrue_31) {
  options_.set_word_boundary(true);
  EXPECT_TRUE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_31, SetWordBoundaryFalse_31) {
  options_.set_word_boundary(true);
  options_.set_word_boundary(false);
  EXPECT_FALSE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_31, SetOneLineTrue_31) {
  options_.set_one_line(true);
  EXPECT_TRUE(options_.one_line());
}

TEST_F(RE2OptionsTest_31, SetOneLineFalse_31) {
  options_.set_one_line(true);
  options_.set_one_line(false);
  EXPECT_FALSE(options_.one_line());
}

TEST_F(RE2OptionsTest_31, SetMaxMem_31) {
  options_.set_max_mem(1024 * 1024);
  EXPECT_EQ(options_.max_mem(), 1024 * 1024);
}

TEST_F(RE2OptionsTest_31, SetMaxMemZero_31) {
  options_.set_max_mem(0);
  EXPECT_EQ(options_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_31, SetMaxMemLargeValue_31) {
  int64_t large_val = static_cast<int64_t>(1) << 40;  // 1 TB
  options_.set_max_mem(large_val);
  EXPECT_EQ(options_.max_mem(), large_val);
}

TEST_F(RE2OptionsTest_31, SetEncodingUTF8_31) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  options_.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_31, SetEncodingLatin1_31) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingLatin1);
}

// ==================== Copy Tests ====================

TEST_F(RE2OptionsTest_31, CopyOptions_31) {
  RE2::Options src;
  src.set_case_sensitive(false);
  src.set_posix_syntax(true);
  src.set_longest_match(true);
  src.set_log_errors(false);
  src.set_literal(true);
  src.set_never_nl(true);
  src.set_dot_nl(true);
  src.set_never_capture(true);
  src.set_perl_classes(true);
  src.set_word_boundary(true);
  src.set_one_line(true);
  src.set_max_mem(12345);
  src.set_encoding(RE2::Options::EncodingLatin1);

  RE2::Options dst;
  dst.Copy(src);

  EXPECT_FALSE(dst.case_sensitive());
  EXPECT_TRUE(dst.posix_syntax());
  EXPECT_TRUE(dst.longest_match());
  EXPECT_FALSE(dst.log_errors());
  EXPECT_TRUE(dst.literal());
  EXPECT_TRUE(dst.never_nl());
  EXPECT_TRUE(dst.dot_nl());
  EXPECT_TRUE(dst.never_capture());
  EXPECT_TRUE(dst.perl_classes());
  EXPECT_TRUE(dst.word_boundary());
  EXPECT_TRUE(dst.one_line());
  EXPECT_EQ(dst.max_mem(), 12345);
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_31, CopyDefaultOptions_31) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_case_sensitive(false);
  dst.set_literal(true);

  dst.Copy(src);

  // After copying defaults, dst should match src (defaults)
  EXPECT_TRUE(dst.case_sensitive());
  EXPECT_FALSE(dst.literal());
}

// ==================== RE2 with Options Integration Tests ====================

TEST_F(RE2OptionsTest_31, RE2CaseInsensitiveMatch_31) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HeLLo", re));
}

TEST_F(RE2OptionsTest_31, RE2CaseSensitiveMatch_31) {
  RE2::Options opts;
  opts.set_case_sensitive(true);
  RE2 re("hello", opts);
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
}

TEST_F(RE2OptionsTest_31, RE2LiteralMatch_31) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  // Literal mode: "." is not a regex metacharacter
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

TEST_F(RE2OptionsTest_31, RE2NonLiteralMatch_31) {
  RE2::Options opts;
  opts.set_literal(false);
  RE2 re("a.b", opts);
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_TRUE(RE2::FullMatch("axb", re));
}

TEST_F(RE2OptionsTest_31, RE2DotNlTrue_31) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2OptionsTest_31, RE2DotNlFalse_31) {
  RE2::Options opts;
  opts.set_dot_nl(false);
  RE2 re("a.b", opts);
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2OptionsTest_31, RE2PosixSyntax_31) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
  RE2 re("(a|ab)c", opts);
  // POSIX longest match: "ab" should be preferred over "a"
  std::string match;
  EXPECT_TRUE(RE2::FullMatch("abc", re));
}

TEST_F(RE2OptionsTest_31, RE2NeverCapture_31) {
  RE2::Options opts;
  opts.set_never_capture(true);
  RE2 re("(\\d+)-(\\d+)", opts);
  // With never_capture, groups should not capture
  // The pattern should still match
  EXPECT_TRUE(RE2::PartialMatch("123-456", re));
}

// ==================== Multiple Setter Calls ====================

TEST_F(RE2OptionsTest_31, MultipleSetsOnSameOption_31) {
  options_.set_case_sensitive(false);
  EXPECT_FALSE(options_.case_sensitive());
  options_.set_case_sensitive(true);
  EXPECT_TRUE(options_.case_sensitive());
  options_.set_case_sensitive(false);
  EXPECT_FALSE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_31, SetMultipleOptionsCombined_31) {
  options_.set_case_sensitive(false);
  options_.set_dot_nl(true);
  options_.set_one_line(true);
  options_.set_max_mem(999);

  EXPECT_FALSE(options_.case_sensitive());
  EXPECT_TRUE(options_.dot_nl());
  EXPECT_TRUE(options_.one_line());
  EXPECT_EQ(options_.max_mem(), 999);
  // Unchanged defaults
  EXPECT_FALSE(options_.posix_syntax());
  EXPECT_FALSE(options_.longest_match());
  EXPECT_TRUE(options_.log_errors());
}

}  // namespace re2
