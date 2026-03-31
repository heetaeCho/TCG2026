#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// ============================================================
// Tests for RE2::Options default constructor
// ============================================================

TEST(RE2OptionsTest_25, DefaultConstructorMaxMem_25) {
  RE2::Options opts;
  // Default max_mem should be some positive value (kDefaultMaxMem)
  EXPECT_GT(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_25, DefaultConstructorEncoding_25) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_25, DefaultConstructorPosixSyntax_25) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_25, DefaultConstructorLongestMatch_25) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_25, DefaultConstructorLogErrors_25) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_25, DefaultConstructorLiteral_25) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_25, DefaultConstructorNeverNl_25) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_25, DefaultConstructorDotNl_25) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_25, DefaultConstructorNeverCapture_25) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_25, DefaultConstructorCaseSensitive_25) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_25, DefaultConstructorPerlClasses_25) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_25, DefaultConstructorWordBoundary_25) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_25, DefaultConstructorOneLine_25) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
}

// ============================================================
// Tests for RE2::Options CannedOptions constructor
// ============================================================

TEST(RE2OptionsTest_25, CannedOptionsLatin1Encoding_25) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_25, CannedOptionsPOSIXPosixSyntax_25) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_25, CannedOptionsPOSIXLongestMatch_25) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_25, CannedOptionsQuietLogErrors_25) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_25, CannedOptionsQuietEncoding_25) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_25, CannedOptionsQuietPosixSyntax_25) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_25, CannedOptionsPOSIXLogErrors_25) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_25, CannedOptionsLatin1PosixSyntax_25) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_25, CannedOptionsLatin1LongestMatch_25) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.longest_match());
}

// ============================================================
// Tests for set/get methods
// ============================================================

TEST(RE2OptionsTest_25, SetAndGetNeverNlTrue_25) {
  RE2::Options opts;
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
}

TEST(RE2OptionsTest_25, SetAndGetNeverNlFalse_25) {
  RE2::Options opts;
  opts.set_never_nl(true);
  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_25, SetAndGetMaxMem_25) {
  RE2::Options opts;
  opts.set_max_mem(1024 * 1024);
  EXPECT_EQ(opts.max_mem(), 1024 * 1024);
}

TEST(RE2OptionsTest_25, SetAndGetMaxMemZero_25) {
  RE2::Options opts;
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_25, SetAndGetMaxMemLargeValue_25) {
  RE2::Options opts;
  int64_t large_val = static_cast<int64_t>(1) << 40;
  opts.set_max_mem(large_val);
  EXPECT_EQ(opts.max_mem(), large_val);
}

TEST(RE2OptionsTest_25, SetAndGetEncodingLatin1_25) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_25, SetAndGetEncodingUTF8_25) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_25, SetAndGetPosixSyntax_25) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_25, SetAndGetLongestMatch_25) {
  RE2::Options opts;
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_25, SetAndGetLogErrors_25) {
  RE2::Options opts;
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_25, SetAndGetLiteral_25) {
  RE2::Options opts;
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_25, SetAndGetDotNl_25) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_25, SetAndGetNeverCapture_25) {
  RE2::Options opts;
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_25, SetAndGetCaseSensitive_25) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_25, SetAndGetPerlClasses_25) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_25, SetAndGetWordBoundary_25) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_25, SetAndGetOneLine_25) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

// ============================================================
// Tests for Copy method
// ============================================================

TEST(RE2OptionsTest_25, CopyAllDefaults_25) {
  RE2::Options src;
  src.set_never_nl(true);
  src.set_dot_nl(true);
  src.set_case_sensitive(false);
  src.set_max_mem(12345);
  src.set_encoding(RE2::Options::EncodingLatin1);
  src.set_posix_syntax(true);
  src.set_longest_match(true);
  src.set_log_errors(false);
  src.set_literal(true);
  src.set_never_capture(true);
  src.set_perl_classes(true);
  src.set_word_boundary(true);
  src.set_one_line(true);

  RE2::Options dst;
  dst.Copy(src);

  EXPECT_TRUE(dst.never_nl());
  EXPECT_TRUE(dst.dot_nl());
  EXPECT_FALSE(dst.case_sensitive());
  EXPECT_EQ(dst.max_mem(), 12345);
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_TRUE(dst.posix_syntax());
  EXPECT_TRUE(dst.longest_match());
  EXPECT_FALSE(dst.log_errors());
  EXPECT_TRUE(dst.literal());
  EXPECT_TRUE(dst.never_capture());
  EXPECT_TRUE(dst.perl_classes());
  EXPECT_TRUE(dst.word_boundary());
  EXPECT_TRUE(dst.one_line());
}

TEST(RE2OptionsTest_25, CopyFromDefaultOptions_25) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_never_nl(true);
  dst.set_log_errors(false);

  dst.Copy(src);

  EXPECT_FALSE(dst.never_nl());
  EXPECT_TRUE(dst.log_errors());
}

// ============================================================
// Tests for ParseFlags method
// ============================================================

TEST(RE2OptionsTest_25, ParseFlagsDefaultOptions_25) {
  RE2::Options opts;
  int flags = opts.ParseFlags();
  // Just verify it returns some value; we treat implementation as black box
  (void)flags;
}

TEST(RE2OptionsTest_25, ParseFlagsChangesWithNeverNl_25) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_never_nl(true);
  // Different settings may produce different flags
  // We can't guarantee they differ but we can ensure no crash
  int flags1 = opts1.ParseFlags();
  int flags2 = opts2.ParseFlags();
  // If never_nl changes behavior, flags should differ
  // But we don't assert specific values since it's a black box
  (void)flags1;
  (void)flags2;
}

TEST(RE2OptionsTest_25, ParseFlagsDotNlAffectsFlags_25) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_dot_nl(true);
  int flags1 = opts1.ParseFlags();
  int flags2 = opts2.ParseFlags();
  // dot_nl likely changes parse flags
  EXPECT_NE(flags1, flags2);
}

TEST(RE2OptionsTest_25, ParseFlagsCaseInsensitiveAffectsFlags_25) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_case_sensitive(false);
  int flags1 = opts1.ParseFlags();
  int flags2 = opts2.ParseFlags();
  EXPECT_NE(flags1, flags2);
}

// ============================================================
// Tests for multiple set/get toggling
// ============================================================

TEST(RE2OptionsTest_25, MultipleTogglesNeverNl_25) {
  RE2::Options opts;
  for (int i = 0; i < 10; i++) {
    opts.set_never_nl(true);
    EXPECT_TRUE(opts.never_nl());
    opts.set_never_nl(false);
    EXPECT_FALSE(opts.never_nl());
  }
}

TEST(RE2OptionsTest_25, SetAllOptionsToNonDefault_25) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  opts.set_longest_match(true);
  opts.set_log_errors(false);
  opts.set_literal(true);
  opts.set_never_nl(true);
  opts.set_dot_nl(true);
  opts.set_never_capture(true);
  opts.set_case_sensitive(false);
  opts.set_perl_classes(true);
  opts.set_word_boundary(true);
  opts.set_one_line(true);

  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
  EXPECT_FALSE(opts.log_errors());
  EXPECT_TRUE(opts.literal());
  EXPECT_TRUE(opts.never_nl());
  EXPECT_TRUE(opts.dot_nl());
  EXPECT_TRUE(opts.never_capture());
  EXPECT_FALSE(opts.case_sensitive());
  EXPECT_TRUE(opts.perl_classes());
  EXPECT_TRUE(opts.word_boundary());
  EXPECT_TRUE(opts.one_line());
}

// ============================================================
// Test Copy self-assignment scenario
// ============================================================

TEST(RE2OptionsTest_25, CopySelfAssignment_25) {
  RE2::Options opts;
  opts.set_never_nl(true);
  opts.set_max_mem(99999);
  opts.Copy(opts);
  EXPECT_TRUE(opts.never_nl());
  EXPECT_EQ(opts.max_mem(), 99999);
}

// ============================================================
// Boundary: max_mem with negative value
// ============================================================

TEST(RE2OptionsTest_25, SetMaxMemNegative_25) {
  RE2::Options opts;
  opts.set_max_mem(-1);
  EXPECT_EQ(opts.max_mem(), -1);
}

}  // namespace re2
