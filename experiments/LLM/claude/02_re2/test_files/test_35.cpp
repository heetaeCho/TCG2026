#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// =============================================================================
// Tests for RE2::Options default constructor
// =============================================================================

TEST(RE2OptionsTest_35, DefaultConstructor_MaxMem_35) {
  RE2::Options opts;
  // Default max_mem should be kDefaultMaxMem (typically 8<<20 = 8388608)
  EXPECT_GT(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_35, DefaultConstructor_Encoding_35) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_35, DefaultConstructor_PosixSyntax_35) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_35, DefaultConstructor_LongestMatch_35) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_35, DefaultConstructor_LogErrors_35) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_35, DefaultConstructor_Literal_35) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_35, DefaultConstructor_NeverNl_35) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_35, DefaultConstructor_DotNl_35) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_35, DefaultConstructor_NeverCapture_35) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_35, DefaultConstructor_CaseSensitive_35) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_35, DefaultConstructor_PerlClasses_35) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_35, DefaultConstructor_WordBoundary_35) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_35, DefaultConstructor_OneLine_35) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
}

// =============================================================================
// Tests for RE2::Options with CannedOptions constructor
// =============================================================================

TEST(RE2OptionsTest_35, CannedOptions_Latin1_Encoding_35) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_35, CannedOptions_Latin1_PosixSyntax_35) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_35, CannedOptions_POSIX_PosixSyntax_35) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_35, CannedOptions_POSIX_LongestMatch_35) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_35, CannedOptions_POSIX_Encoding_35) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_35, CannedOptions_Quiet_LogErrors_35) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_35, CannedOptions_Quiet_PosixSyntax_35) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_35, CannedOptions_Quiet_LongestMatch_35) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.longest_match());
}

// =============================================================================
// Tests for set/get methods
// =============================================================================

TEST(RE2OptionsTest_35, SetAndGetMaxMem_35) {
  RE2::Options opts;
  opts.set_max_mem(1024 * 1024);
  EXPECT_EQ(opts.max_mem(), 1024 * 1024);
}

TEST(RE2OptionsTest_35, SetAndGetMaxMem_Zero_35) {
  RE2::Options opts;
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_35, SetAndGetMaxMem_Large_35) {
  RE2::Options opts;
  int64_t large_val = static_cast<int64_t>(1) << 30;
  opts.set_max_mem(large_val);
  EXPECT_EQ(opts.max_mem(), large_val);
}

TEST(RE2OptionsTest_35, SetAndGetEncoding_Latin1_35) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_35, SetAndGetEncoding_UTF8_35) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_35, SetAndGetPosixSyntax_True_35) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_35, SetAndGetPosixSyntax_False_35) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_35, SetAndGetLongestMatch_True_35) {
  RE2::Options opts;
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_35, SetAndGetLongestMatch_False_35) {
  RE2::Options opts;
  opts.set_longest_match(true);
  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_35, SetAndGetLogErrors_True_35) {
  RE2::Options opts;
  opts.set_log_errors(false);
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_35, SetAndGetLogErrors_False_35) {
  RE2::Options opts;
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_35, SetAndGetLiteral_True_35) {
  RE2::Options opts;
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
}

TEST(RE2OptionsTest_35, SetAndGetLiteral_False_35) {
  RE2::Options opts;
  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_35, SetAndGetNeverNl_True_35) {
  RE2::Options opts;
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
}

TEST(RE2OptionsTest_35, SetAndGetNeverNl_False_35) {
  RE2::Options opts;
  opts.set_never_nl(true);
  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_35, SetAndGetDotNl_True_35) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
}

TEST(RE2OptionsTest_35, SetAndGetDotNl_False_35) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_35, SetAndGetNeverCapture_True_35) {
  RE2::Options opts;
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
}

TEST(RE2OptionsTest_35, SetAndGetNeverCapture_False_35) {
  RE2::Options opts;
  opts.set_never_capture(true);
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_35, SetAndGetCaseSensitive_True_35) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_35, SetAndGetCaseSensitive_False_35) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
}

TEST(RE2OptionsTest_35, SetAndGetPerlClasses_True_35) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
}

TEST(RE2OptionsTest_35, SetAndGetPerlClasses_False_35) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_35, SetAndGetWordBoundary_True_35) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
}

TEST(RE2OptionsTest_35, SetAndGetWordBoundary_False_35) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_35, SetAndGetOneLine_True_35) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
}

TEST(RE2OptionsTest_35, SetAndGetOneLine_False_35) {
  RE2::Options opts;
  opts.set_one_line(true);
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

// =============================================================================
// Tests for Copy method
// =============================================================================

TEST(RE2OptionsTest_35, Copy_AllFieldsCopied_35) {
  RE2::Options src;
  src.set_max_mem(12345);
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

  RE2::Options dest;
  dest.Copy(src);

  EXPECT_EQ(dest.max_mem(), 12345);
  EXPECT_EQ(dest.encoding(), RE2::Options::EncodingLatin1);
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
}

TEST(RE2OptionsTest_35, Copy_DefaultValues_35) {
  RE2::Options src;
  RE2::Options dest;

  // Modify dest first
  dest.set_literal(true);
  dest.set_dot_nl(true);
  dest.set_word_boundary(true);

  // Copy defaults from src
  dest.Copy(src);

  EXPECT_FALSE(dest.literal());
  EXPECT_FALSE(dest.dot_nl());
  EXPECT_FALSE(dest.word_boundary());
}

TEST(RE2OptionsTest_35, Copy_SelfCopy_35) {
  RE2::Options opts;
  opts.set_max_mem(99999);
  opts.set_word_boundary(true);

  opts.Copy(opts);

  EXPECT_EQ(opts.max_mem(), 99999);
  EXPECT_TRUE(opts.word_boundary());
}

// =============================================================================
// Tests for ParseFlags
// =============================================================================

TEST(RE2OptionsTest_35, ParseFlags_DefaultOptions_35) {
  RE2::Options opts;
  int flags = opts.ParseFlags();
  // We just verify it returns some value without crashing
  (void)flags;
}

TEST(RE2OptionsTest_35, ParseFlags_DifferentOptionsProduceDifferentFlags_35) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_case_sensitive(false);

  // Case insensitive should produce different parse flags
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

TEST(RE2OptionsTest_35, ParseFlags_PosixOptions_35) {
  RE2::Options opts(RE2::POSIX);
  int flags = opts.ParseFlags();
  (void)flags;
  // Just ensure it doesn't crash and returns a value
}

TEST(RE2OptionsTest_35, ParseFlags_WordBoundaryAffectsFlags_35) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_word_boundary(true);

  // Changing word_boundary may or may not change flags depending on implementation,
  // but at minimum we verify no crash
  int f1 = opts1.ParseFlags();
  int f2 = opts2.ParseFlags();
  (void)f1;
  (void)f2;
}

TEST(RE2OptionsTest_35, ParseFlags_LiteralAffectsFlags_35) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_literal(true);

  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

TEST(RE2OptionsTest_35, ParseFlags_DotNlAffectsFlags_35) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_dot_nl(true);

  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

TEST(RE2OptionsTest_35, ParseFlags_NeverNlAffectsFlags_35) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_never_nl(true);

  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

// =============================================================================
// Tests for multiple set operations (boundary/sequencing)
// =============================================================================

TEST(RE2OptionsTest_35, MultipleSetOperations_35) {
  RE2::Options opts;
  
  // Toggle values multiple times
  for (int i = 0; i < 10; i++) {
    opts.set_word_boundary(i % 2 == 0);
    opts.set_case_sensitive(i % 2 != 0);
  }
  
  // After 10 iterations (i=9 last), word_boundary = false, case_sensitive = true
  EXPECT_FALSE(opts.word_boundary());
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_35, SetMaxMem_NegativeValue_35) {
  RE2::Options opts;
  opts.set_max_mem(-1);
  EXPECT_EQ(opts.max_mem(), -1);
}

TEST(RE2OptionsTest_35, SetMaxMem_MaxInt64_35) {
  RE2::Options opts;
  int64_t max_val = std::numeric_limits<int64_t>::max();
  opts.set_max_mem(max_val);
  EXPECT_EQ(opts.max_mem(), max_val);
}

// =============================================================================
// Tests confirming independence of Options instances
// =============================================================================

TEST(RE2OptionsTest_35, OptionsInstancesAreIndependent_35) {
  RE2::Options opts1;
  RE2::Options opts2;

  opts1.set_word_boundary(true);
  opts1.set_literal(true);
  opts1.set_max_mem(42);

  // opts2 should still have defaults
  EXPECT_FALSE(opts2.word_boundary());
  EXPECT_FALSE(opts2.literal());
  EXPECT_NE(opts2.max_mem(), 42);
}

}  // namespace re2
