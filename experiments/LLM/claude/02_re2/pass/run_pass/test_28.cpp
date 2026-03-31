#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>

namespace re2 {
namespace {

// ============================================================================
// Tests for RE2::Options default constructor
// ============================================================================

TEST(RE2OptionsTest_28, DefaultConstructor_NeverCaptureIsFalse_28) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_28, DefaultConstructor_CaseSensitiveIsTrue_28) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_28, DefaultConstructor_PosixSyntaxIsFalse_28) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_28, DefaultConstructor_LongestMatchIsFalse_28) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_28, DefaultConstructor_LogErrorsIsTrue_28) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_28, DefaultConstructor_LiteralIsFalse_28) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_28, DefaultConstructor_NeverNlIsFalse_28) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_28, DefaultConstructor_DotNlIsFalse_28) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_28, DefaultConstructor_PerlClassesIsFalse_28) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_28, DefaultConstructor_WordBoundaryIsFalse_28) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_28, DefaultConstructor_OneLineIsFalse_28) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
}

TEST(RE2OptionsTest_28, DefaultConstructor_EncodingIsUTF8_28) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// ============================================================================
// Tests for RE2::Options with CannedOptions
// ============================================================================

TEST(RE2OptionsTest_28, Latin1CannedOption_EncodingIsLatin1_28) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_28, Latin1CannedOption_PosixSyntaxIsFalse_28) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_28, Latin1CannedOption_LongestMatchIsFalse_28) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_28, POSIXCannedOption_PosixSyntaxIsTrue_28) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_28, POSIXCannedOption_LongestMatchIsTrue_28) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_28, POSIXCannedOption_EncodingIsUTF8_28) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_28, QuietCannedOption_LogErrorsIsFalse_28) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_28, QuietCannedOption_NeverCaptureIsFalse_28) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_28, DefaultNoArgCannedOption_LogErrorsIsTrue_28) {
  RE2::Options opts(RE2::DefaultOptions);
  EXPECT_TRUE(opts.log_errors());
}

// ============================================================================
// Tests for setters and getters
// ============================================================================

TEST(RE2OptionsTest_28, SetNeverCapture_True_28) {
  RE2::Options opts;
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
}

TEST(RE2OptionsTest_28, SetNeverCapture_False_28) {
  RE2::Options opts;
  opts.set_never_capture(true);
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_28, SetCaseSensitive_False_28) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
}

TEST(RE2OptionsTest_28, SetCaseSensitive_True_28) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_28, SetPosixSyntax_True_28) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_28, SetLongestMatch_True_28) {
  RE2::Options opts;
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_28, SetLogErrors_False_28) {
  RE2::Options opts;
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_28, SetLiteral_True_28) {
  RE2::Options opts;
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
}

TEST(RE2OptionsTest_28, SetNeverNl_True_28) {
  RE2::Options opts;
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
}

TEST(RE2OptionsTest_28, SetDotNl_True_28) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
}

TEST(RE2OptionsTest_28, SetPerlClasses_True_28) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
}

TEST(RE2OptionsTest_28, SetWordBoundary_True_28) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
}

TEST(RE2OptionsTest_28, SetOneLine_True_28) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
}

TEST(RE2OptionsTest_28, SetEncoding_Latin1_28) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_28, SetEncoding_UTF8_28) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_28, SetMaxMem_28) {
  RE2::Options opts;
  opts.set_max_mem(1024 * 1024);
  EXPECT_EQ(opts.max_mem(), 1024 * 1024);
}

TEST(RE2OptionsTest_28, SetMaxMem_Zero_28) {
  RE2::Options opts;
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_28, SetMaxMem_LargeValue_28) {
  RE2::Options opts;
  int64_t large_val = static_cast<int64_t>(1) << 40;
  opts.set_max_mem(large_val);
  EXPECT_EQ(opts.max_mem(), large_val);
}

// ============================================================================
// Tests for Copy
// ============================================================================

TEST(RE2OptionsTest_28, Copy_AllFieldsCopied_28) {
  RE2::Options src;
  src.set_never_capture(true);
  src.set_case_sensitive(false);
  src.set_posix_syntax(true);
  src.set_longest_match(true);
  src.set_log_errors(false);
  src.set_literal(true);
  src.set_never_nl(true);
  src.set_dot_nl(true);
  src.set_perl_classes(true);
  src.set_word_boundary(true);
  src.set_one_line(true);
  src.set_encoding(RE2::Options::EncodingLatin1);
  src.set_max_mem(2048);

  RE2::Options dst;
  dst.Copy(src);

  EXPECT_TRUE(dst.never_capture());
  EXPECT_FALSE(dst.case_sensitive());
  EXPECT_TRUE(dst.posix_syntax());
  EXPECT_TRUE(dst.longest_match());
  EXPECT_FALSE(dst.log_errors());
  EXPECT_TRUE(dst.literal());
  EXPECT_TRUE(dst.never_nl());
  EXPECT_TRUE(dst.dot_nl());
  EXPECT_TRUE(dst.perl_classes());
  EXPECT_TRUE(dst.word_boundary());
  EXPECT_TRUE(dst.one_line());
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_EQ(dst.max_mem(), 2048);
}

TEST(RE2OptionsTest_28, Copy_DefaultValues_28) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_never_capture(true);
  dst.set_case_sensitive(false);

  dst.Copy(src);

  EXPECT_FALSE(dst.never_capture());
  EXPECT_TRUE(dst.case_sensitive());
}

// ============================================================================
// Tests for RE2::Options with CannedOptions - all boolean fields
// ============================================================================

TEST(RE2OptionsTest_28, POSIXCannedOption_NeverCaptureIsFalse_28) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_28, POSIXCannedOption_CaseSensitiveIsTrue_28) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_28, POSIXCannedOption_LiteralIsFalse_28) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_28, POSIXCannedOption_LogErrorsIsTrue_28) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.log_errors());
}

// ============================================================================
// Tests for multiple set operations (boundary: toggling)
// ============================================================================

TEST(RE2OptionsTest_28, ToggleNeverCapture_28) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
}

TEST(RE2OptionsTest_28, ToggleAllBooleans_28) {
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

  // Toggle all back
  opts.set_posix_syntax(false);
  opts.set_longest_match(false);
  opts.set_log_errors(true);
  opts.set_literal(false);
  opts.set_never_nl(false);
  opts.set_dot_nl(false);
  opts.set_never_capture(false);
  opts.set_case_sensitive(true);
  opts.set_perl_classes(false);
  opts.set_word_boundary(false);
  opts.set_one_line(false);

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

// ============================================================================
// Tests for RE2 with Options having never_capture set
// ============================================================================

TEST(RE2OptionsTest_28, RE2WithNeverCaptureOption_28) {
  RE2::Options opts;
  opts.set_never_capture(true);
  RE2 re("(\\d+)-(\\d+)", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("123-456", re));
}

TEST(RE2OptionsTest_28, RE2WithDefaultOptions_28) {
  RE2::Options opts;
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("say hello world", re));
}

TEST(RE2OptionsTest_28, RE2WithCaseInsensitiveOption_28) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("HELLO", re));
}

TEST(RE2OptionsTest_28, RE2WithLiteralOption_28) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  // With literal mode, "a.b" should match literal "a.b" not "axb"
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

TEST(RE2OptionsTest_28, RE2OptionsRetrievedFromRE2_28) {
  RE2::Options opts;
  opts.set_never_capture(true);
  opts.set_dot_nl(true);
  RE2 re("test", opts);
  EXPECT_TRUE(re.ok());
  const RE2::Options& retrieved = re.options();
  EXPECT_TRUE(retrieved.never_capture());
  EXPECT_TRUE(retrieved.dot_nl());
}

// ============================================================================
// ParseFlags test (indirectly - just ensure it returns without error)
// ============================================================================

TEST(RE2OptionsTest_28, ParseFlags_DefaultOptions_28) {
  RE2::Options opts;
  int flags = opts.ParseFlags();
  // We can't know exact value, but it should be deterministic
  int flags2 = opts.ParseFlags();
  EXPECT_EQ(flags, flags2);
}

TEST(RE2OptionsTest_28, ParseFlags_DifferentOptions_28) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_posix_syntax(true);
  // Different options should potentially produce different flags
  // (though we don't know the exact mapping, we test they're callable)
  int flags1 = opts1.ParseFlags();
  int flags2 = opts2.ParseFlags();
  // They should differ since posix_syntax is different
  EXPECT_NE(flags1, flags2);
}

}  // namespace
}  // namespace re2
