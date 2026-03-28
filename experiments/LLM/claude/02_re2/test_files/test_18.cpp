#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>

namespace re2 {

// ============================================================
// Tests for RE2::Options default constructor
// ============================================================

TEST(RE2OptionsTest_18, DefaultConstructor_LongestMatchIsFalse_18) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_18, DefaultConstructor_PosixSyntaxIsFalse_18) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_18, DefaultConstructor_LogErrorsIsTrue_18) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_18, DefaultConstructor_LiteralIsFalse_18) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_18, DefaultConstructor_NeverNlIsFalse_18) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_18, DefaultConstructor_DotNlIsFalse_18) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_18, DefaultConstructor_NeverCaptureIsFalse_18) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_18, DefaultConstructor_CaseSensitiveIsTrue_18) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_18, DefaultConstructor_PerlClassesIsFalse_18) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_18, DefaultConstructor_WordBoundaryIsFalse_18) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_18, DefaultConstructor_OneLineIsFalse_18) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
}

TEST(RE2OptionsTest_18, DefaultConstructor_EncodingIsUTF8_18) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// ============================================================
// Tests for RE2::Options with CannedOptions
// ============================================================

TEST(RE2OptionsTest_18, Latin1Constructor_EncodingIsLatin1_18) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_18, Latin1Constructor_PosixSyntaxIsFalse_18) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_18, Latin1Constructor_LongestMatchIsFalse_18) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_18, POSIXConstructor_PosixSyntaxIsTrue_18) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_18, POSIXConstructor_LongestMatchIsTrue_18) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_18, POSIXConstructor_LogErrorsIsTrue_18) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_18, POSIXConstructor_EncodingIsUTF8_18) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_18, QuietConstructor_LogErrorsIsFalse_18) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_18, QuietConstructor_PosixSyntaxIsFalse_18) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_18, QuietConstructor_LongestMatchIsFalse_18) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.longest_match());
}

// ============================================================
// Tests for setters and getters
// ============================================================

TEST(RE2OptionsTest_18, SetLongestMatch_True_18) {
  RE2::Options opts;
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_18, SetLongestMatch_False_18) {
  RE2::Options opts;
  opts.set_longest_match(true);
  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_18, SetPosixSyntax_True_18) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_18, SetPosixSyntax_False_18) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_18, SetLogErrors_True_18) {
  RE2::Options opts;
  opts.set_log_errors(false);
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_18, SetLogErrors_False_18) {
  RE2::Options opts;
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_18, SetLiteral_True_18) {
  RE2::Options opts;
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
}

TEST(RE2OptionsTest_18, SetLiteral_False_18) {
  RE2::Options opts;
  opts.set_literal(true);
  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_18, SetNeverNl_True_18) {
  RE2::Options opts;
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
}

TEST(RE2OptionsTest_18, SetNeverNl_False_18) {
  RE2::Options opts;
  opts.set_never_nl(true);
  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_18, SetDotNl_True_18) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
}

TEST(RE2OptionsTest_18, SetDotNl_False_18) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_18, SetNeverCapture_True_18) {
  RE2::Options opts;
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
}

TEST(RE2OptionsTest_18, SetNeverCapture_False_18) {
  RE2::Options opts;
  opts.set_never_capture(true);
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_18, SetCaseSensitive_True_18) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_18, SetCaseSensitive_False_18) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
}

TEST(RE2OptionsTest_18, SetPerlClasses_True_18) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
}

TEST(RE2OptionsTest_18, SetPerlClasses_False_18) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_18, SetWordBoundary_True_18) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
}

TEST(RE2OptionsTest_18, SetWordBoundary_False_18) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_18, SetOneLine_True_18) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
}

TEST(RE2OptionsTest_18, SetOneLine_False_18) {
  RE2::Options opts;
  opts.set_one_line(true);
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

TEST(RE2OptionsTest_18, SetMaxMem_18) {
  RE2::Options opts;
  opts.set_max_mem(1024 * 1024);
  EXPECT_EQ(opts.max_mem(), 1024 * 1024);
}

TEST(RE2OptionsTest_18, SetMaxMem_Zero_18) {
  RE2::Options opts;
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_18, SetMaxMem_Large_18) {
  RE2::Options opts;
  int64_t large_val = static_cast<int64_t>(1) << 40;
  opts.set_max_mem(large_val);
  EXPECT_EQ(opts.max_mem(), large_val);
}

TEST(RE2OptionsTest_18, SetEncoding_Latin1_18) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_18, SetEncoding_UTF8_18) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// ============================================================
// Tests for Copy
// ============================================================

TEST(RE2OptionsTest_18, Copy_AllFieldsCopied_18) {
  RE2::Options src;
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
  src.set_max_mem(12345);
  src.set_encoding(RE2::Options::EncodingLatin1);

  RE2::Options dst;
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
  EXPECT_EQ(dst.max_mem(), 12345);
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_18, Copy_DefaultValues_18) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_longest_match(true);
  dst.set_literal(true);

  dst.Copy(src);

  EXPECT_FALSE(dst.longest_match());
  EXPECT_FALSE(dst.literal());
}

// ============================================================
// Tests for RE2 basic operations using Options
// ============================================================

TEST(RE2OptionsTest_18, RE2WithDefaultOptions_FullMatch_18) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

TEST(RE2OptionsTest_18, RE2WithLongestMatch_18) {
  RE2::Options opts;
  opts.set_longest_match(true);
  RE2 re("a+", opts);
  EXPECT_TRUE(re.ok());

  std::string match;
  EXPECT_TRUE(RE2::PartialMatch("aaa", re, &match));
  EXPECT_EQ(match, "aaa");
}

TEST(RE2OptionsTest_18, RE2WithLiteral_18) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());

  // literal mode: "a.b" should match literal "a.b" not "aXb"
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("aXb", re));
}

TEST(RE2OptionsTest_18, RE2WithCaseInsensitive_18) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());

  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2OptionsTest_18, RE2WithNeverCapture_18) {
  RE2::Options opts;
  opts.set_never_capture(true);
  RE2 re("(hello)", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2OptionsTest_18, RE2WithDotNl_18) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST(RE2OptionsTest_18, RE2WithoutDotNl_18) {
  RE2::Options opts;
  opts.set_dot_nl(false);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

TEST(RE2OptionsTest_18, RE2POSIXCannedOption_18) {
  RE2 re("a+", RE2::POSIX);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(re.options().posix_syntax());
  EXPECT_TRUE(re.options().longest_match());
}

TEST(RE2OptionsTest_18, RE2QuietCannedOption_18) {
  RE2 re("[invalid", RE2::Quiet);
  EXPECT_FALSE(re.ok());
}

TEST(RE2OptionsTest_18, RE2DefaultCannedOption_18) {
  RE2 re("hello", RE2::DefaultOptions);
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(re.options().posix_syntax());
  EXPECT_FALSE(re.options().longest_match());
  EXPECT_TRUE(re.options().log_errors());
}

// ============================================================
// Boundary condition tests
// ============================================================

TEST(RE2OptionsTest_18, SetMaxMem_NegativeValue_18) {
  RE2::Options opts;
  opts.set_max_mem(-1);
  EXPECT_EQ(opts.max_mem(), -1);
}

TEST(RE2OptionsTest_18, MultipleSetCalls_LastWins_18) {
  RE2::Options opts;
  opts.set_longest_match(true);
  opts.set_longest_match(false);
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_18, CopySelf_18) {
  RE2::Options opts;
  opts.set_longest_match(true);
  opts.set_max_mem(9999);
  opts.Copy(opts);
  EXPECT_TRUE(opts.longest_match());
  EXPECT_EQ(opts.max_mem(), 9999);
}

}  // namespace re2
