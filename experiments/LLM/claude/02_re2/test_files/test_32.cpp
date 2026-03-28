#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {
namespace {

// Test default constructor initializes options to expected defaults
TEST(RE2OptionsTest_32, DefaultConstructorDefaults_32) {
  RE2::Options opts;
  EXPECT_EQ(opts.max_mem(), 8 << 20);  // kDefaultMaxMem
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
  EXPECT_FALSE(opts.literal());
  EXPECT_FALSE(opts.never_nl());
  EXPECT_FALSE(opts.dot_nl());
  EXPECT_FALSE(opts.never_capture());
  EXPECT_TRUE(opts.case_sensitive());
  EXPECT_FALSE(opts.perl_classes());
  EXPECT_FALSE(opts.word_boundary());
  EXPECT_FALSE(opts.one_line());
}

// Test CannedOptions constructor with RE2::DefaultOptions
TEST(RE2OptionsTest_32, CannedDefaultOptions_32) {
  RE2::Options opts(RE2::DefaultOptions);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
  EXPECT_FALSE(opts.perl_classes());
  EXPECT_FALSE(opts.word_boundary());
  EXPECT_TRUE(opts.case_sensitive());
}

// Test CannedOptions constructor with RE2::Latin1
TEST(RE2OptionsTest_32, CannedLatin1Options_32) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
}

// Test CannedOptions constructor with RE2::POSIX
TEST(RE2OptionsTest_32, CannedPOSIXOptions_32) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
}

// Test CannedOptions constructor with RE2::Quiet
TEST(RE2OptionsTest_32, CannedQuietOptions_32) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
}

// Test set_max_mem / max_mem
TEST(RE2OptionsTest_32, SetMaxMem_32) {
  RE2::Options opts;
  opts.set_max_mem(1024);
  EXPECT_EQ(opts.max_mem(), 1024);
}

TEST(RE2OptionsTest_32, SetMaxMemZero_32) {
  RE2::Options opts;
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_32, SetMaxMemLarge_32) {
  RE2::Options opts;
  int64_t large = static_cast<int64_t>(1) << 40;
  opts.set_max_mem(large);
  EXPECT_EQ(opts.max_mem(), large);
}

// Test set_encoding / encoding
TEST(RE2OptionsTest_32, SetEncodingUTF8_32) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_32, SetEncodingLatin1_32) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

// Test set_posix_syntax / posix_syntax
TEST(RE2OptionsTest_32, SetPosixSyntaxTrue_32) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_32, SetPosixSyntaxFalse_32) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

// Test set_longest_match / longest_match
TEST(RE2OptionsTest_32, SetLongestMatchTrue_32) {
  RE2::Options opts;
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_32, SetLongestMatchFalse_32) {
  RE2::Options opts;
  opts.set_longest_match(true);
  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

// Test set_log_errors / log_errors
TEST(RE2OptionsTest_32, SetLogErrorsFalse_32) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_32, SetLogErrorsTrue_32) {
  RE2::Options opts;
  opts.set_log_errors(false);
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

// Test set_literal / literal
TEST(RE2OptionsTest_32, SetLiteralTrue_32) {
  RE2::Options opts;
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
}

TEST(RE2OptionsTest_32, SetLiteralFalse_32) {
  RE2::Options opts;
  opts.set_literal(true);
  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

// Test set_never_nl / never_nl
TEST(RE2OptionsTest_32, SetNeverNlTrue_32) {
  RE2::Options opts;
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
}

TEST(RE2OptionsTest_32, SetNeverNlFalse_32) {
  RE2::Options opts;
  opts.set_never_nl(true);
  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

// Test set_dot_nl / dot_nl
TEST(RE2OptionsTest_32, SetDotNlTrue_32) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
}

TEST(RE2OptionsTest_32, SetDotNlFalse_32) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

// Test set_never_capture / never_capture
TEST(RE2OptionsTest_32, SetNeverCaptureTrue_32) {
  RE2::Options opts;
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
}

TEST(RE2OptionsTest_32, SetNeverCaptureFalse_32) {
  RE2::Options opts;
  opts.set_never_capture(true);
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

// Test set_case_sensitive / case_sensitive
TEST(RE2OptionsTest_32, SetCaseSensitiveFalse_32) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
}

TEST(RE2OptionsTest_32, SetCaseSensitiveTrue_32) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

// Test set_perl_classes / perl_classes
TEST(RE2OptionsTest_32, SetPerlClassesTrue_32) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
}

TEST(RE2OptionsTest_32, SetPerlClassesFalse_32) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_32, PerlClassesDefaultFalse_32) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

// Test set_word_boundary / word_boundary
TEST(RE2OptionsTest_32, SetWordBoundaryTrue_32) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
}

TEST(RE2OptionsTest_32, SetWordBoundaryFalse_32) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

// Test set_one_line / one_line
TEST(RE2OptionsTest_32, SetOneLineTrue_32) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
}

TEST(RE2OptionsTest_32, SetOneLineFalse_32) {
  RE2::Options opts;
  opts.set_one_line(true);
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

// Test Copy
TEST(RE2OptionsTest_32, CopyOptions_32) {
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

// Test Copy with default source
TEST(RE2OptionsTest_32, CopyDefaultOptions_32) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_perl_classes(true);
  dst.set_log_errors(false);

  dst.Copy(src);

  EXPECT_FALSE(dst.perl_classes());
  EXPECT_TRUE(dst.log_errors());
}

// Test multiple set operations on same option
TEST(RE2OptionsTest_32, MultipleSetOperations_32) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
}

// Test setting all boolean options to true
TEST(RE2OptionsTest_32, AllBooleanOptionsTrue_32) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  opts.set_longest_match(true);
  opts.set_log_errors(true);
  opts.set_literal(true);
  opts.set_never_nl(true);
  opts.set_dot_nl(true);
  opts.set_never_capture(true);
  opts.set_case_sensitive(true);
  opts.set_perl_classes(true);
  opts.set_word_boundary(true);
  opts.set_one_line(true);

  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
  EXPECT_TRUE(opts.literal());
  EXPECT_TRUE(opts.never_nl());
  EXPECT_TRUE(opts.dot_nl());
  EXPECT_TRUE(opts.never_capture());
  EXPECT_TRUE(opts.case_sensitive());
  EXPECT_TRUE(opts.perl_classes());
  EXPECT_TRUE(opts.word_boundary());
  EXPECT_TRUE(opts.one_line());
}

// Test setting all boolean options to false
TEST(RE2OptionsTest_32, AllBooleanOptionsFalse_32) {
  RE2::Options opts;
  opts.set_posix_syntax(false);
  opts.set_longest_match(false);
  opts.set_log_errors(false);
  opts.set_literal(false);
  opts.set_never_nl(false);
  opts.set_dot_nl(false);
  opts.set_never_capture(false);
  opts.set_case_sensitive(false);
  opts.set_perl_classes(false);
  opts.set_word_boundary(false);
  opts.set_one_line(false);

  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_FALSE(opts.log_errors());
  EXPECT_FALSE(opts.literal());
  EXPECT_FALSE(opts.never_nl());
  EXPECT_FALSE(opts.dot_nl());
  EXPECT_FALSE(opts.never_capture());
  EXPECT_FALSE(opts.case_sensitive());
  EXPECT_FALSE(opts.perl_classes());
  EXPECT_FALSE(opts.word_boundary());
  EXPECT_FALSE(opts.one_line());
}

// Test max_mem boundary with negative value
TEST(RE2OptionsTest_32, SetMaxMemNegative_32) {
  RE2::Options opts;
  opts.set_max_mem(-1);
  EXPECT_EQ(opts.max_mem(), -1);
}

// Test that options set independently don't affect each other
TEST(RE2OptionsTest_32, OptionsAreIndependent_32) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_FALSE(opts.word_boundary());
  EXPECT_FALSE(opts.one_line());
  EXPECT_TRUE(opts.case_sensitive());

  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.perl_classes());
  EXPECT_TRUE(opts.word_boundary());
  EXPECT_FALSE(opts.one_line());
}

// Test ParseFlags returns an int (basic smoke test)
TEST(RE2OptionsTest_32, ParseFlagsReturnsValue_32) {
  RE2::Options opts;
  int flags = opts.ParseFlags();
  // We just verify it doesn't crash and returns some value
  (void)flags;
}

// Test ParseFlags changes with options
TEST(RE2OptionsTest_32, ParseFlagsChangesWithPerlClasses_32) {
  RE2::Options opts1;
  int flags1 = opts1.ParseFlags();

  RE2::Options opts2;
  opts2.set_perl_classes(true);
  int flags2 = opts2.ParseFlags();

  // Different options should generally produce different parse flags
  // (perl_classes is known to affect parse flags)
  EXPECT_NE(flags1, flags2);
}

TEST(RE2OptionsTest_32, ParseFlagsChangesWithWordBoundary_32) {
  RE2::Options opts1;
  int flags1 = opts1.ParseFlags();

  RE2::Options opts2;
  opts2.set_word_boundary(true);
  int flags2 = opts2.ParseFlags();

  EXPECT_NE(flags1, flags2);
}

TEST(RE2OptionsTest_32, ParseFlagsChangesWithCaseSensitive_32) {
  RE2::Options opts1;
  int flags1 = opts1.ParseFlags();

  RE2::Options opts2;
  opts2.set_case_sensitive(false);
  int flags2 = opts2.ParseFlags();

  EXPECT_NE(flags1, flags2);
}

}  // namespace
}  // namespace re2
