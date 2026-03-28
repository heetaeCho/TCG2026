#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {
namespace {

// ============================================================
// Tests for RE2::Options default constructor
// ============================================================

TEST(RE2OptionsTest_27, DefaultConstructor_DotNlIsFalse_27) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_27, DefaultConstructor_MaxMemIsDefault_27) {
  RE2::Options opts;
  // Default max_mem should be positive (kDefaultMaxMem = 8<<20)
  EXPECT_GT(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_27, DefaultConstructor_EncodingIsUTF8_27) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_27, DefaultConstructor_PosixSyntaxIsFalse_27) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_27, DefaultConstructor_LongestMatchIsFalse_27) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_27, DefaultConstructor_LogErrorsIsTrue_27) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_27, DefaultConstructor_LiteralIsFalse_27) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_27, DefaultConstructor_NeverNlIsFalse_27) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_27, DefaultConstructor_NeverCaptureIsFalse_27) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_27, DefaultConstructor_CaseSensitiveIsTrue_27) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_27, DefaultConstructor_PerlClassesIsFalse_27) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_27, DefaultConstructor_WordBoundaryIsFalse_27) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_27, DefaultConstructor_OneLineIsFalse_27) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
}

// ============================================================
// Tests for set_dot_nl / dot_nl
// ============================================================

TEST(RE2OptionsTest_27, SetDotNlTrue_27) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
}

TEST(RE2OptionsTest_27, SetDotNlFalse_27) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_27, SetDotNlToggle_27) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

// ============================================================
// Tests for set_max_mem / max_mem
// ============================================================

TEST(RE2OptionsTest_27, SetMaxMem_27) {
  RE2::Options opts;
  opts.set_max_mem(1024);
  EXPECT_EQ(opts.max_mem(), 1024);
}

TEST(RE2OptionsTest_27, SetMaxMemZero_27) {
  RE2::Options opts;
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_27, SetMaxMemLargeValue_27) {
  RE2::Options opts;
  int64_t large = static_cast<int64_t>(1) << 30;
  opts.set_max_mem(large);
  EXPECT_EQ(opts.max_mem(), large);
}

// ============================================================
// Tests for set_encoding / encoding
// ============================================================

TEST(RE2OptionsTest_27, SetEncodingLatin1_27) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_27, SetEncodingUTF8_27) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// ============================================================
// Tests for set_posix_syntax / posix_syntax
// ============================================================

TEST(RE2OptionsTest_27, SetPosixSyntaxTrue_27) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_27, SetPosixSyntaxFalse_27) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

// ============================================================
// Tests for set_longest_match / longest_match
// ============================================================

TEST(RE2OptionsTest_27, SetLongestMatchTrue_27) {
  RE2::Options opts;
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_27, SetLongestMatchFalse_27) {
  RE2::Options opts;
  opts.set_longest_match(true);
  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

// ============================================================
// Tests for set_log_errors / log_errors
// ============================================================

TEST(RE2OptionsTest_27, SetLogErrorsFalse_27) {
  RE2::Options opts;
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_27, SetLogErrorsTrue_27) {
  RE2::Options opts;
  opts.set_log_errors(false);
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

// ============================================================
// Tests for set_literal / literal
// ============================================================

TEST(RE2OptionsTest_27, SetLiteralTrue_27) {
  RE2::Options opts;
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
}

TEST(RE2OptionsTest_27, SetLiteralFalse_27) {
  RE2::Options opts;
  opts.set_literal(true);
  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

// ============================================================
// Tests for set_never_nl / never_nl
// ============================================================

TEST(RE2OptionsTest_27, SetNeverNlTrue_27) {
  RE2::Options opts;
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
}

TEST(RE2OptionsTest_27, SetNeverNlFalse_27) {
  RE2::Options opts;
  opts.set_never_nl(true);
  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

// ============================================================
// Tests for set_never_capture / never_capture
// ============================================================

TEST(RE2OptionsTest_27, SetNeverCaptureTrue_27) {
  RE2::Options opts;
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
}

TEST(RE2OptionsTest_27, SetNeverCaptureFalse_27) {
  RE2::Options opts;
  opts.set_never_capture(true);
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

// ============================================================
// Tests for set_case_sensitive / case_sensitive
// ============================================================

TEST(RE2OptionsTest_27, SetCaseSensitiveFalse_27) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
}

TEST(RE2OptionsTest_27, SetCaseSensitiveTrue_27) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

// ============================================================
// Tests for set_perl_classes / perl_classes
// ============================================================

TEST(RE2OptionsTest_27, SetPerlClassesTrue_27) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
}

TEST(RE2OptionsTest_27, SetPerlClassesFalse_27) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

// ============================================================
// Tests for set_word_boundary / word_boundary
// ============================================================

TEST(RE2OptionsTest_27, SetWordBoundaryTrue_27) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
}

TEST(RE2OptionsTest_27, SetWordBoundaryFalse_27) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

// ============================================================
// Tests for set_one_line / one_line
// ============================================================

TEST(RE2OptionsTest_27, SetOneLineTrue_27) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
}

TEST(RE2OptionsTest_27, SetOneLineFalse_27) {
  RE2::Options opts;
  opts.set_one_line(true);
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

// ============================================================
// Tests for CannedOptions constructors
// ============================================================

TEST(RE2OptionsTest_27, CannedOptionLatin1_27) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_27, CannedOptionPOSIX_27) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_27, CannedOptionQuiet_27) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_27, CannedOptionDefaultFlags_27) {
  RE2::Options opts(RE2::DefaultOptions);
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

// ============================================================
// Tests for Copy
// ============================================================

TEST(RE2OptionsTest_27, CopyAllSettings_27) {
  RE2::Options src;
  src.set_dot_nl(true);
  src.set_never_nl(true);
  src.set_posix_syntax(true);
  src.set_longest_match(true);
  src.set_log_errors(false);
  src.set_literal(true);
  src.set_never_capture(true);
  src.set_case_sensitive(false);
  src.set_perl_classes(true);
  src.set_word_boundary(true);
  src.set_one_line(true);
  src.set_max_mem(12345);
  src.set_encoding(RE2::Options::EncodingLatin1);

  RE2::Options dst;
  dst.Copy(src);

  EXPECT_TRUE(dst.dot_nl());
  EXPECT_TRUE(dst.never_nl());
  EXPECT_TRUE(dst.posix_syntax());
  EXPECT_TRUE(dst.longest_match());
  EXPECT_FALSE(dst.log_errors());
  EXPECT_TRUE(dst.literal());
  EXPECT_TRUE(dst.never_capture());
  EXPECT_FALSE(dst.case_sensitive());
  EXPECT_TRUE(dst.perl_classes());
  EXPECT_TRUE(dst.word_boundary());
  EXPECT_TRUE(dst.one_line());
  EXPECT_EQ(dst.max_mem(), 12345);
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_27, CopyDefaultOptions_27) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_dot_nl(true);
  dst.set_case_sensitive(false);

  dst.Copy(src);

  EXPECT_FALSE(dst.dot_nl());
  EXPECT_TRUE(dst.case_sensitive());
}

// ============================================================
// Tests for dot_nl behavioral effect on RE2 matching
// ============================================================

TEST(RE2OptionsTest_27, DotNlAffectsMatching_DotMatchesNewline_27) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST(RE2OptionsTest_27, DotNlAffectsMatching_DotDoesNotMatchNewline_27) {
  RE2::Options opts;
  opts.set_dot_nl(false);
  RE2 re("a.b", opts);
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

// ============================================================
// Tests for ParseFlags (observable via the interface)
// ============================================================

TEST(RE2OptionsTest_27, ParseFlagsDefaultOptions_27) {
  RE2::Options opts;
  int flags = opts.ParseFlags();
  // ParseFlags should return some non-negative value for default options
  EXPECT_GE(flags, 0);
}

TEST(RE2OptionsTest_27, ParseFlagsChangesWithDotNl_27) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_dot_nl(true);
  // Setting dot_nl should change parse flags
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

TEST(RE2OptionsTest_27, ParseFlagsChangesWithCaseSensitive_27) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_case_sensitive(false);
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

TEST(RE2OptionsTest_27, ParseFlagsChangesWithPosixSyntax_27) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_posix_syntax(true);
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

// ============================================================
// Tests for multiple setters interaction
// ============================================================

TEST(RE2OptionsTest_27, MultipleSettersAreIndependent_27) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  opts.set_never_nl(true);
  opts.set_literal(true);
  opts.set_case_sensitive(false);

  EXPECT_TRUE(opts.dot_nl());
  EXPECT_TRUE(opts.never_nl());
  EXPECT_TRUE(opts.literal());
  EXPECT_FALSE(opts.case_sensitive());

  // Other fields remain default
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
  EXPECT_FALSE(opts.never_capture());
  EXPECT_FALSE(opts.perl_classes());
  EXPECT_FALSE(opts.word_boundary());
  EXPECT_FALSE(opts.one_line());
}

}  // namespace
}  // namespace re2
