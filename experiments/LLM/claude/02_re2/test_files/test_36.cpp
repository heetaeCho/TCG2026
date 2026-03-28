#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// Test default constructor defaults
TEST(RE2OptionsTest_36, DefaultConstructorMaxMem_36) {
  RE2::Options opts;
  // Default max_mem should be kDefaultMaxMem (8<<20 = 8388608)
  EXPECT_GT(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_36, DefaultConstructorEncoding_36) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_36, DefaultConstructorPosixSyntax_36) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_36, DefaultConstructorLongestMatch_36) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_36, DefaultConstructorLogErrors_36) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_36, DefaultConstructorLiteral_36) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_36, DefaultConstructorNeverNl_36) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_36, DefaultConstructorDotNl_36) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_36, DefaultConstructorNeverCapture_36) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_36, DefaultConstructorCaseSensitive_36) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_36, DefaultConstructorPerlClasses_36) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_36, DefaultConstructorWordBoundary_36) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_36, DefaultConstructorOneLine_36) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
}

// Test CannedOptions constructor with Latin1
TEST(RE2OptionsTest_36, Latin1ConstructorEncoding_36) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_36, Latin1ConstructorPosixSyntax_36) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_36, Latin1ConstructorLongestMatch_36) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_36, Latin1ConstructorLogErrors_36) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_TRUE(opts.log_errors());
}

// Test CannedOptions constructor with POSIX
TEST(RE2OptionsTest_36, POSIXConstructorEncoding_36) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_36, POSIXConstructorPosixSyntax_36) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_36, POSIXConstructorLongestMatch_36) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_36, POSIXConstructorLogErrors_36) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_36, POSIXConstructorOneLine_36) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_FALSE(opts.one_line());
}

// Test CannedOptions constructor with Quiet
TEST(RE2OptionsTest_36, QuietConstructorLogErrors_36) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_36, QuietConstructorPosixSyntax_36) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.posix_syntax());
}

// Test setters and getters
TEST(RE2OptionsTest_36, SetMaxMem_36) {
  RE2::Options opts;
  opts.set_max_mem(1024);
  EXPECT_EQ(opts.max_mem(), 1024);
}

TEST(RE2OptionsTest_36, SetMaxMemZero_36) {
  RE2::Options opts;
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_36, SetMaxMemLargeValue_36) {
  RE2::Options opts;
  int64_t large_val = static_cast<int64_t>(1) << 30;
  opts.set_max_mem(large_val);
  EXPECT_EQ(opts.max_mem(), large_val);
}

TEST(RE2OptionsTest_36, SetEncodingUTF8_36) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_36, SetEncodingLatin1_36) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_36, SetPosixSyntaxTrue_36) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_36, SetPosixSyntaxFalse_36) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_36, SetLongestMatchTrue_36) {
  RE2::Options opts;
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_36, SetLongestMatchFalse_36) {
  RE2::Options opts;
  opts.set_longest_match(true);
  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_36, SetLogErrorsTrue_36) {
  RE2::Options opts;
  opts.set_log_errors(false);
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_36, SetLogErrorsFalse_36) {
  RE2::Options opts;
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_36, SetLiteralTrue_36) {
  RE2::Options opts;
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
}

TEST(RE2OptionsTest_36, SetLiteralFalse_36) {
  RE2::Options opts;
  opts.set_literal(true);
  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_36, SetNeverNlTrue_36) {
  RE2::Options opts;
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
}

TEST(RE2OptionsTest_36, SetNeverNlFalse_36) {
  RE2::Options opts;
  opts.set_never_nl(true);
  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_36, SetDotNlTrue_36) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
}

TEST(RE2OptionsTest_36, SetDotNlFalse_36) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_36, SetNeverCaptureTrue_36) {
  RE2::Options opts;
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
}

TEST(RE2OptionsTest_36, SetNeverCaptureFalse_36) {
  RE2::Options opts;
  opts.set_never_capture(true);
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_36, SetCaseSensitiveTrue_36) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_36, SetCaseSensitiveFalse_36) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
}

TEST(RE2OptionsTest_36, SetPerlClassesTrue_36) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
}

TEST(RE2OptionsTest_36, SetPerlClassesFalse_36) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_36, SetWordBoundaryTrue_36) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
}

TEST(RE2OptionsTest_36, SetWordBoundaryFalse_36) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_36, SetOneLineTrue_36) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
}

TEST(RE2OptionsTest_36, SetOneLineFalse_36) {
  RE2::Options opts;
  opts.set_one_line(true);
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

// Test Copy
TEST(RE2OptionsTest_36, CopyOptions_36) {
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

TEST(RE2OptionsTest_36, CopyDefaultOptions_36) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_one_line(true);
  dst.set_literal(true);
  dst.Copy(src);

  EXPECT_FALSE(dst.one_line());
  EXPECT_FALSE(dst.literal());
}

// Test ParseFlags returns a value (we can't know exact value, but it should be deterministic)
TEST(RE2OptionsTest_36, ParseFlagsDeterministic_36) {
  RE2::Options opts;
  int flags1 = opts.ParseFlags();
  int flags2 = opts.ParseFlags();
  EXPECT_EQ(flags1, flags2);
}

TEST(RE2OptionsTest_36, ParseFlagsChangesWithOptions_36) {
  RE2::Options opts1;
  int flags1 = opts1.ParseFlags();

  RE2::Options opts2;
  opts2.set_case_sensitive(false);
  int flags2 = opts2.ParseFlags();

  // Different options should likely produce different flags
  EXPECT_NE(flags1, flags2);
}

TEST(RE2OptionsTest_36, ParseFlagsPOSIXvDefault_36) {
  RE2::Options def_opts;
  RE2::Options posix_opts(RE2::POSIX);

  int def_flags = def_opts.ParseFlags();
  int posix_flags = posix_opts.ParseFlags();

  // POSIX options differ from default, so flags should differ
  EXPECT_NE(def_flags, posix_flags);
}

// Test that multiple set calls work correctly (last write wins)
TEST(RE2OptionsTest_36, MultipleSetCalls_36) {
  RE2::Options opts;
  opts.set_one_line(true);
  opts.set_one_line(false);
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
}

TEST(RE2OptionsTest_36, SetMaxMemMultipleTimes_36) {
  RE2::Options opts;
  opts.set_max_mem(100);
  opts.set_max_mem(200);
  opts.set_max_mem(300);
  EXPECT_EQ(opts.max_mem(), 300);
}

// Test CannedOptions DefaultMaxMem check
TEST(RE2OptionsTest_36, CannedOptionsDefaultMaxMem_36) {
  RE2::Options def_opts;
  RE2::Options latin1_opts(RE2::Latin1);
  RE2::Options posix_opts(RE2::POSIX);
  RE2::Options quiet_opts(RE2::Quiet);

  // All canned options should have the same default max_mem
  EXPECT_EQ(def_opts.max_mem(), latin1_opts.max_mem());
  EXPECT_EQ(def_opts.max_mem(), posix_opts.max_mem());
  EXPECT_EQ(def_opts.max_mem(), quiet_opts.max_mem());
}

// Test that canned options have common defaults for fields not affected by the option
TEST(RE2OptionsTest_36, CannedOptionsCommonDefaults_36) {
  RE2::Options latin1_opts(RE2::Latin1);
  EXPECT_FALSE(latin1_opts.literal());
  EXPECT_FALSE(latin1_opts.never_nl());
  EXPECT_FALSE(latin1_opts.dot_nl());
  EXPECT_FALSE(latin1_opts.never_capture());
  EXPECT_TRUE(latin1_opts.case_sensitive());
  EXPECT_FALSE(latin1_opts.perl_classes());
  EXPECT_FALSE(latin1_opts.word_boundary());
  EXPECT_FALSE(latin1_opts.one_line());
}

TEST(RE2OptionsTest_36, QuietOptionsCommonDefaults_36) {
  RE2::Options quiet_opts(RE2::Quiet);
  EXPECT_EQ(quiet_opts.encoding(), RE2::Options::EncodingUTF8);
  EXPECT_FALSE(quiet_opts.posix_syntax());
  EXPECT_FALSE(quiet_opts.longest_match());
  EXPECT_FALSE(quiet_opts.literal());
  EXPECT_FALSE(quiet_opts.never_nl());
  EXPECT_FALSE(quiet_opts.dot_nl());
  EXPECT_FALSE(quiet_opts.never_capture());
  EXPECT_TRUE(quiet_opts.case_sensitive());
  EXPECT_FALSE(quiet_opts.perl_classes());
  EXPECT_FALSE(quiet_opts.word_boundary());
  EXPECT_FALSE(quiet_opts.one_line());
}

}  // namespace re2
