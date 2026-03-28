#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// Test default constructor initializes case_sensitive to true
TEST(RE2OptionsTest_30, DefaultConstructorCaseSensitiveTrue_30) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

// Test default constructor initializes all boolean defaults correctly
TEST(RE2OptionsTest_30, DefaultConstructorDefaults_30) {
  RE2::Options opts;
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

// Test default encoding is UTF8
TEST(RE2OptionsTest_30, DefaultEncodingUTF8_30) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// Test set_case_sensitive changes the value
TEST(RE2OptionsTest_30, SetCaseSensitiveFalse_30) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
}

TEST(RE2OptionsTest_30, SetCaseSensitiveTrue_30) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

// Test set_posix_syntax
TEST(RE2OptionsTest_30, SetPosixSyntax_30) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

// Test set_longest_match
TEST(RE2OptionsTest_30, SetLongestMatch_30) {
  RE2::Options opts;
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

// Test set_log_errors
TEST(RE2OptionsTest_30, SetLogErrors_30) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

// Test set_literal
TEST(RE2OptionsTest_30, SetLiteral_30) {
  RE2::Options opts;
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

// Test set_never_nl
TEST(RE2OptionsTest_30, SetNeverNl_30) {
  RE2::Options opts;
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

// Test set_dot_nl
TEST(RE2OptionsTest_30, SetDotNl_30) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

// Test set_never_capture
TEST(RE2OptionsTest_30, SetNeverCapture_30) {
  RE2::Options opts;
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

// Test set_perl_classes
TEST(RE2OptionsTest_30, SetPerlClasses_30) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

// Test set_word_boundary
TEST(RE2OptionsTest_30, SetWordBoundary_30) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

// Test set_one_line
TEST(RE2OptionsTest_30, SetOneLine_30) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

// Test set_encoding
TEST(RE2OptionsTest_30, SetEncoding_30) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// Test set_max_mem
TEST(RE2OptionsTest_30, SetMaxMem_30) {
  RE2::Options opts;
  int64_t original = opts.max_mem();
  EXPECT_GT(original, 0);
  opts.set_max_mem(1024 * 1024);
  EXPECT_EQ(opts.max_mem(), 1024 * 1024);
}

// Test max_mem boundary: zero
TEST(RE2OptionsTest_30, SetMaxMemZero_30) {
  RE2::Options opts;
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
}

// Test max_mem boundary: large value
TEST(RE2OptionsTest_30, SetMaxMemLarge_30) {
  RE2::Options opts;
  opts.set_max_mem(INT64_MAX);
  EXPECT_EQ(opts.max_mem(), INT64_MAX);
}

// Test CannedOptions constructor with Latin1
TEST(RE2OptionsTest_30, CannedOptionsLatin1_30) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
  EXPECT_TRUE(opts.case_sensitive());
}

// Test CannedOptions constructor with POSIX
TEST(RE2OptionsTest_30, CannedOptionsPOSIX_30) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
  EXPECT_TRUE(opts.case_sensitive());
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// Test CannedOptions constructor with Quiet
TEST(RE2OptionsTest_30, CannedOptionsQuiet_30) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_TRUE(opts.case_sensitive());
}

// Test Copy method
TEST(RE2OptionsTest_30, CopyOptions_30) {
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
  src.set_encoding(RE2::Options::EncodingLatin1);
  src.set_max_mem(999);

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
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_EQ(dst.max_mem(), 999);
}

// Test that Copy with default source resets destination
TEST(RE2OptionsTest_30, CopyDefaultResetsOptions_30) {
  RE2::Options modified;
  modified.set_case_sensitive(false);
  modified.set_dot_nl(true);

  RE2::Options defaults;
  modified.Copy(defaults);

  EXPECT_TRUE(modified.case_sensitive());
  EXPECT_FALSE(modified.dot_nl());
}

// Test toggling case_sensitive multiple times
TEST(RE2OptionsTest_30, ToggleCaseSensitiveMultipleTimes_30) {
  RE2::Options opts;
  for (int i = 0; i < 10; ++i) {
    opts.set_case_sensitive(i % 2 == 0);
    EXPECT_EQ(opts.case_sensitive(), (i % 2 == 0));
  }
}

// Test ParseFlags returns a value (non-crash, basic sanity)
TEST(RE2OptionsTest_30, ParseFlagsDefault_30) {
  RE2::Options opts;
  int flags = opts.ParseFlags();
  // We just verify it doesn't crash and returns some value
  (void)flags;
}

// Test that ParseFlags changes when options change
TEST(RE2OptionsTest_30, ParseFlagsChangesWithOptions_30) {
  RE2::Options opts1;
  int flags1 = opts1.ParseFlags();

  RE2::Options opts2;
  opts2.set_case_sensitive(false);
  int flags2 = opts2.ParseFlags();

  // Changing case_sensitive should affect parse flags
  EXPECT_NE(flags1, flags2);
}

// Test that POSIX canned option produces different ParseFlags than default
TEST(RE2OptionsTest_30, ParseFlagsPOSIXDiffersFromDefault_30) {
  RE2::Options def;
  RE2::Options posix(RE2::POSIX);
  EXPECT_NE(def.ParseFlags(), posix.ParseFlags());
}

}  // namespace re2
