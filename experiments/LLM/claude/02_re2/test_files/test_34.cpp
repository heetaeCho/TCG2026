#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// Test default constructor initializes word_boundary to false
TEST(RE2OptionsTest_34, DefaultConstructorWordBoundaryIsFalse_34) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

// Test setting word_boundary to true
TEST(RE2OptionsTest_34, SetWordBoundaryTrue_34) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
}

// Test setting word_boundary to false explicitly
TEST(RE2OptionsTest_34, SetWordBoundaryFalse_34) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

// Test toggling word_boundary multiple times
TEST(RE2OptionsTest_34, ToggleWordBoundaryMultipleTimes_34) {
  RE2::Options opts;
  for (int i = 0; i < 10; i++) {
    opts.set_word_boundary(true);
    EXPECT_TRUE(opts.word_boundary());
    opts.set_word_boundary(false);
    EXPECT_FALSE(opts.word_boundary());
  }
}

// Test CannedOptions constructors don't set word_boundary
TEST(RE2OptionsTest_34, CannedOptionsDefaultWordBoundaryFalse_34) {
  RE2::Options opts_default(RE2::DefaultOptions);
  EXPECT_FALSE(opts_default.word_boundary());

  RE2::Options opts_latin1(RE2::Latin1);
  EXPECT_FALSE(opts_latin1.word_boundary());

  RE2::Options opts_posix(RE2::POSIX);
  EXPECT_FALSE(opts_posix.word_boundary());

  RE2::Options opts_quiet(RE2::Quiet);
  EXPECT_FALSE(opts_quiet.word_boundary());
}

// Test default constructor values for all boolean options
TEST(RE2OptionsTest_34, DefaultConstructorAllDefaults_34) {
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

// Test set_max_mem and max_mem
TEST(RE2OptionsTest_34, MaxMemDefaultAndSet_34) {
  RE2::Options opts;
  int64_t default_max = opts.max_mem();
  EXPECT_GT(default_max, 0);

  opts.set_max_mem(1024);
  EXPECT_EQ(1024, opts.max_mem());
}

// Test encoding default and set
TEST(RE2OptionsTest_34, EncodingDefaultAndSet_34) {
  RE2::Options opts;
  EXPECT_EQ(RE2::Options::EncodingUTF8, opts.encoding());

  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(RE2::Options::EncodingLatin1, opts.encoding());
}

// Test posix_syntax
TEST(RE2OptionsTest_34, PosixSyntax_34) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
}

// Test longest_match
TEST(RE2OptionsTest_34, LongestMatch_34) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
}

// Test log_errors
TEST(RE2OptionsTest_34, LogErrors_34) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
}

// Test literal
TEST(RE2OptionsTest_34, Literal_34) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
}

// Test never_nl
TEST(RE2OptionsTest_34, NeverNl_34) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
}

// Test dot_nl
TEST(RE2OptionsTest_34, DotNl_34) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
}

// Test never_capture
TEST(RE2OptionsTest_34, NeverCapture_34) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
}

// Test case_sensitive
TEST(RE2OptionsTest_34, CaseSensitive_34) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
}

// Test perl_classes
TEST(RE2OptionsTest_34, PerlClasses_34) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
}

// Test one_line
TEST(RE2OptionsTest_34, OneLine_34) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
}

// Test Copy preserves word_boundary
TEST(RE2OptionsTest_34, CopyPreservesWordBoundary_34) {
  RE2::Options src;
  src.set_word_boundary(true);

  RE2::Options dst;
  dst.Copy(src);
  EXPECT_TRUE(dst.word_boundary());
}

// Test Copy preserves all options
TEST(RE2OptionsTest_34, CopyPreservesAllOptions_34) {
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
  src.set_max_mem(12345);
  src.set_encoding(RE2::Options::EncodingLatin1);

  RE2::Options dst;
  dst.Copy(src);

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
  EXPECT_EQ(12345, dst.max_mem());
  EXPECT_EQ(RE2::Options::EncodingLatin1, dst.encoding());
}

// Test POSIX CannedOption sets posix_syntax and longest_match
TEST(RE2OptionsTest_34, POSIXCannedOption_34) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
  EXPECT_FALSE(opts.word_boundary());
}

// Test Latin1 CannedOption sets encoding
TEST(RE2OptionsTest_34, Latin1CannedOption_34) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(RE2::Options::EncodingLatin1, opts.encoding());
  EXPECT_FALSE(opts.word_boundary());
}

// Test Quiet CannedOption disables log_errors
TEST(RE2OptionsTest_34, QuietCannedOption_34) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
  EXPECT_FALSE(opts.word_boundary());
}

// Test max_mem boundary: setting to zero
TEST(RE2OptionsTest_34, MaxMemZero_34) {
  RE2::Options opts;
  opts.set_max_mem(0);
  EXPECT_EQ(0, opts.max_mem());
}

// Test max_mem boundary: large value
TEST(RE2OptionsTest_34, MaxMemLargeValue_34) {
  RE2::Options opts;
  opts.set_max_mem(INT64_MAX);
  EXPECT_EQ(INT64_MAX, opts.max_mem());
}

// Test that word_boundary with RE2 pattern works (integration-like)
TEST(RE2OptionsTest_34, WordBoundaryWithRE2Pattern_34) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  // Just ensure the option is set; actual regex behavior depends on implementation
  EXPECT_TRUE(opts.word_boundary());
}

// Test setting same value repeatedly
TEST(RE2OptionsTest_34, SetWordBoundarySameValueRepeatedly_34) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  opts.set_word_boundary(true);
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
}

// Test Copy from default options
TEST(RE2OptionsTest_34, CopyFromDefaultOptions_34) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_word_boundary(true);
  dst.Copy(src);
  EXPECT_FALSE(dst.word_boundary());
}

}  // namespace re2
