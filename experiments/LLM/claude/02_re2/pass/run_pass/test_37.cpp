#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// ============================================================
// Tests for RE2::Options default constructor
// ============================================================

TEST(RE2OptionsTest_37, DefaultConstructor_MaxMem_37) {
  RE2::Options opts;
  // Default max_mem should be kDefaultMaxMem (8<<20 = 8388608)
  EXPECT_GT(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_37, DefaultConstructor_Encoding_37) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_37, DefaultConstructor_PosixSyntax_37) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_37, DefaultConstructor_LongestMatch_37) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_37, DefaultConstructor_LogErrors_37) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_37, DefaultConstructor_Literal_37) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_37, DefaultConstructor_NeverNl_37) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_37, DefaultConstructor_DotNl_37) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_37, DefaultConstructor_NeverCapture_37) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_37, DefaultConstructor_CaseSensitive_37) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_37, DefaultConstructor_PerlClasses_37) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_37, DefaultConstructor_WordBoundary_37) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_37, DefaultConstructor_OneLine_37) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
}

// ============================================================
// Tests for RE2::Options CannedOptions constructors
// ============================================================

TEST(RE2OptionsTest_37, CannedOptionLatin1_Encoding_37) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_37, CannedOptionLatin1_PosixSyntax_37) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_37, CannedOptionLatin1_LogErrors_37) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_37, CannedOptionPOSIX_PosixSyntax_37) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_37, CannedOptionPOSIX_LongestMatch_37) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_37, CannedOptionPOSIX_Encoding_37) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_37, CannedOptionPOSIX_LogErrors_37) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_37, CannedOptionQuiet_LogErrors_37) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_37, CannedOptionQuiet_PosixSyntax_37) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_37, CannedOptionQuiet_LongestMatch_37) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.longest_match());
}

// ============================================================
// Tests for setter/getter pairs
// ============================================================

TEST(RE2OptionsTest_37, SetMaxMem_37) {
  RE2::Options opts;
  opts.set_max_mem(1024);
  EXPECT_EQ(opts.max_mem(), 1024);
}

TEST(RE2OptionsTest_37, SetMaxMemZero_37) {
  RE2::Options opts;
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_37, SetMaxMemLarge_37) {
  RE2::Options opts;
  int64_t large_val = static_cast<int64_t>(1) << 30;
  opts.set_max_mem(large_val);
  EXPECT_EQ(opts.max_mem(), large_val);
}

TEST(RE2OptionsTest_37, SetEncodingUTF8_37) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_37, SetEncodingLatin1_37) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_37, SetPosixSyntaxTrue_37) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_37, SetPosixSyntaxFalse_37) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_37, SetLongestMatchTrue_37) {
  RE2::Options opts;
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_37, SetLongestMatchFalse_37) {
  RE2::Options opts;
  opts.set_longest_match(true);
  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_37, SetLogErrorsTrue_37) {
  RE2::Options opts;
  opts.set_log_errors(false);
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_37, SetLogErrorsFalse_37) {
  RE2::Options opts;
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_37, SetLiteralTrue_37) {
  RE2::Options opts;
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
}

TEST(RE2OptionsTest_37, SetLiteralFalse_37) {
  RE2::Options opts;
  opts.set_literal(true);
  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_37, SetNeverNlTrue_37) {
  RE2::Options opts;
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
}

TEST(RE2OptionsTest_37, SetNeverNlFalse_37) {
  RE2::Options opts;
  opts.set_never_nl(true);
  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_37, SetDotNlTrue_37) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
}

TEST(RE2OptionsTest_37, SetDotNlFalse_37) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_37, SetNeverCaptureTrue_37) {
  RE2::Options opts;
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
}

TEST(RE2OptionsTest_37, SetNeverCaptureFalse_37) {
  RE2::Options opts;
  opts.set_never_capture(true);
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_37, SetCaseSensitiveTrue_37) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_37, SetCaseSensitiveFalse_37) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
}

TEST(RE2OptionsTest_37, SetPerlClassesTrue_37) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
}

TEST(RE2OptionsTest_37, SetPerlClassesFalse_37) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_37, SetWordBoundaryTrue_37) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
}

TEST(RE2OptionsTest_37, SetWordBoundaryFalse_37) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_37, SetOneLineTrue_37) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
}

TEST(RE2OptionsTest_37, SetOneLineFalse_37) {
  RE2::Options opts;
  opts.set_one_line(true);
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

// ============================================================
// Tests for Copy
// ============================================================

TEST(RE2OptionsTest_37, CopyAllDefaults_37) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_log_errors(false);
  dst.set_case_sensitive(false);
  dst.Copy(src);
  EXPECT_TRUE(dst.log_errors());
  EXPECT_TRUE(dst.case_sensitive());
  EXPECT_FALSE(dst.posix_syntax());
}

TEST(RE2OptionsTest_37, CopyModifiedOptions_37) {
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
  EXPECT_EQ(dst.max_mem(), 12345);
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_37, CopyCannedPOSIX_37) {
  RE2::Options src(RE2::POSIX);
  RE2::Options dst;
  dst.Copy(src);
  EXPECT_TRUE(dst.posix_syntax());
  EXPECT_TRUE(dst.longest_match());
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_37, CopyCannedLatin1_37) {
  RE2::Options src(RE2::Latin1);
  RE2::Options dst;
  dst.Copy(src);
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_FALSE(dst.posix_syntax());
}

TEST(RE2OptionsTest_37, CopySelfAssignment_37) {
  RE2::Options opts;
  opts.set_one_line(true);
  opts.set_max_mem(9999);
  opts.Copy(opts);
  EXPECT_TRUE(opts.one_line());
  EXPECT_EQ(opts.max_mem(), 9999);
}

// ============================================================
// Tests for ParseFlags (observable return, should be consistent)
// ============================================================

TEST(RE2OptionsTest_37, ParseFlagsDefaultOptions_37) {
  RE2::Options opts;
  int flags = opts.ParseFlags();
  // We just verify it returns a value without crashing.
  // The exact value depends on internal implementation.
  (void)flags;
}

TEST(RE2OptionsTest_37, ParseFlagsDifferentForDifferentOptions_37) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_case_sensitive(false);
  // Changing case_sensitive should change parse flags
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

TEST(RE2OptionsTest_37, ParseFlagsPosixVsDefault_37) {
  RE2::Options def;
  RE2::Options posix(RE2::POSIX);
  // POSIX options differ from default
  EXPECT_NE(def.ParseFlags(), posix.ParseFlags());
}

TEST(RE2OptionsTest_37, ParseFlagsConsistentOnMultipleCalls_37) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  opts.set_one_line(true);
  int flags1 = opts.ParseFlags();
  int flags2 = opts.ParseFlags();
  EXPECT_EQ(flags1, flags2);
}

// ============================================================
// Boundary / Multiple set operations
// ============================================================

TEST(RE2OptionsTest_37, MultipleSetOperationsOnSameField_37) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
}

TEST(RE2OptionsTest_37, SetAllBoolsTrue_37) {
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

TEST(RE2OptionsTest_37, SetAllBoolsFalse_37) {
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

// ============================================================
// Integration: Options used with RE2
// ============================================================

TEST(RE2OptionsIntegration_37, OptionsUsedWithRE2_37) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2OptionsIntegration_37, LiteralOption_37) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  // Literal mode should treat "." as a literal character
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

TEST(RE2OptionsIntegration_37, DotNlOption_37) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST(RE2OptionsIntegration_37, DotNlOptionFalse_37) {
  RE2::Options opts;
  opts.set_dot_nl(false);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

TEST(RE2OptionsIntegration_37, POSIXCannedOption_37) {
  RE2::Options opts(RE2::POSIX);
  RE2 re("a|ab", opts);
  EXPECT_TRUE(re.ok());
  // POSIX longest match: "ab" should be matched over "a"
  std::string match;
  EXPECT_TRUE(RE2::PartialMatch("ab", re, &match));
  EXPECT_EQ(match, "ab");
}

TEST(RE2OptionsIntegration_37, NeverCaptureOption_37) {
  RE2::Options opts;
  opts.set_never_capture(true);
  RE2 re("(\\d+)", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2OptionsIntegration_37, QuietOption_37) {
  RE2::Options opts(RE2::Quiet);
  // Invalid regex should not log errors
  RE2 re("(", opts);
  EXPECT_FALSE(re.ok());
}

}  // namespace re2
