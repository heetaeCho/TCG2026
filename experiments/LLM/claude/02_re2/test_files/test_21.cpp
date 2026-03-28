#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// Test fixture for RE2::Options
class RE2OptionsTest_21 : public ::testing::Test {
 protected:
  RE2::Options options_;
};

// ==================== Default Constructor Tests ====================

TEST_F(RE2OptionsTest_21, DefaultConstructorLogErrors_21) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
}

TEST_F(RE2OptionsTest_21, DefaultConstructorEncoding_21) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_21, DefaultConstructorPosixSyntax_21) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_21, DefaultConstructorLongestMatch_21) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
}

TEST_F(RE2OptionsTest_21, DefaultConstructorLiteral_21) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
}

TEST_F(RE2OptionsTest_21, DefaultConstructorNeverNl_21) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
}

TEST_F(RE2OptionsTest_21, DefaultConstructorDotNl_21) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
}

TEST_F(RE2OptionsTest_21, DefaultConstructorNeverCapture_21) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
}

TEST_F(RE2OptionsTest_21, DefaultConstructorCaseSensitive_21) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

TEST_F(RE2OptionsTest_21, DefaultConstructorPerlClasses_21) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

TEST_F(RE2OptionsTest_21, DefaultConstructorWordBoundary_21) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

TEST_F(RE2OptionsTest_21, DefaultConstructorOneLine_21) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
}

// ==================== CannedOptions Constructor Tests ====================

TEST_F(RE2OptionsTest_21, CannedOptionsLatin1Encoding_21) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_21, CannedOptionsLatin1LogErrors_21) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_TRUE(opts.log_errors());
}

TEST_F(RE2OptionsTest_21, CannedOptionsPOSIXPosixSyntax_21) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_21, CannedOptionsPOSIXLongestMatch_21) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST_F(RE2OptionsTest_21, CannedOptionsPOSIXLogErrors_21) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.log_errors());
}

TEST_F(RE2OptionsTest_21, CannedOptionsPOSIXEncodingUTF8_21) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_21, CannedOptionsQuietLogErrors_21) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST_F(RE2OptionsTest_21, CannedOptionsQuietCaseSensitive_21) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_TRUE(opts.case_sensitive());
}

// ==================== Setters and Getters Tests ====================

TEST_F(RE2OptionsTest_21, SetLogErrorsFalse_21) {
  options_.set_log_errors(false);
  EXPECT_FALSE(options_.log_errors());
}

TEST_F(RE2OptionsTest_21, SetLogErrorsTrue_21) {
  options_.set_log_errors(false);
  options_.set_log_errors(true);
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_21, SetMaxMem_21) {
  options_.set_max_mem(1024 * 1024);
  EXPECT_EQ(options_.max_mem(), 1024 * 1024);
}

TEST_F(RE2OptionsTest_21, SetMaxMemZero_21) {
  options_.set_max_mem(0);
  EXPECT_EQ(options_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_21, SetMaxMemLargeValue_21) {
  int64_t large_val = static_cast<int64_t>(1) << 40;
  options_.set_max_mem(large_val);
  EXPECT_EQ(options_.max_mem(), large_val);
}

TEST_F(RE2OptionsTest_21, SetEncodingLatin1_21) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_21, SetEncodingUTF8_21) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  options_.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_21, SetPosixSyntaxTrue_21) {
  options_.set_posix_syntax(true);
  EXPECT_TRUE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_21, SetPosixSyntaxFalse_21) {
  options_.set_posix_syntax(true);
  options_.set_posix_syntax(false);
  EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_21, SetLongestMatchTrue_21) {
  options_.set_longest_match(true);
  EXPECT_TRUE(options_.longest_match());
}

TEST_F(RE2OptionsTest_21, SetLongestMatchFalse_21) {
  options_.set_longest_match(true);
  options_.set_longest_match(false);
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_21, SetLiteralTrue_21) {
  options_.set_literal(true);
  EXPECT_TRUE(options_.literal());
}

TEST_F(RE2OptionsTest_21, SetLiteralFalse_21) {
  options_.set_literal(true);
  options_.set_literal(false);
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_21, SetNeverNlTrue_21) {
  options_.set_never_nl(true);
  EXPECT_TRUE(options_.never_nl());
}

TEST_F(RE2OptionsTest_21, SetNeverNlFalse_21) {
  options_.set_never_nl(true);
  options_.set_never_nl(false);
  EXPECT_FALSE(options_.never_nl());
}

TEST_F(RE2OptionsTest_21, SetDotNlTrue_21) {
  options_.set_dot_nl(true);
  EXPECT_TRUE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_21, SetDotNlFalse_21) {
  options_.set_dot_nl(true);
  options_.set_dot_nl(false);
  EXPECT_FALSE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_21, SetNeverCaptureTrue_21) {
  options_.set_never_capture(true);
  EXPECT_TRUE(options_.never_capture());
}

TEST_F(RE2OptionsTest_21, SetNeverCaptureFalse_21) {
  options_.set_never_capture(true);
  options_.set_never_capture(false);
  EXPECT_FALSE(options_.never_capture());
}

TEST_F(RE2OptionsTest_21, SetCaseSensitiveFalse_21) {
  options_.set_case_sensitive(false);
  EXPECT_FALSE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_21, SetCaseSensitiveTrue_21) {
  options_.set_case_sensitive(false);
  options_.set_case_sensitive(true);
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_21, SetPerlClassesTrue_21) {
  options_.set_perl_classes(true);
  EXPECT_TRUE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_21, SetPerlClassesFalse_21) {
  options_.set_perl_classes(true);
  options_.set_perl_classes(false);
  EXPECT_FALSE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_21, SetWordBoundaryTrue_21) {
  options_.set_word_boundary(true);
  EXPECT_TRUE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_21, SetWordBoundaryFalse_21) {
  options_.set_word_boundary(true);
  options_.set_word_boundary(false);
  EXPECT_FALSE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_21, SetOneLineTrue_21) {
  options_.set_one_line(true);
  EXPECT_TRUE(options_.one_line());
}

TEST_F(RE2OptionsTest_21, SetOneLineFalse_21) {
  options_.set_one_line(true);
  options_.set_one_line(false);
  EXPECT_FALSE(options_.one_line());
}

// ==================== Copy Tests ====================

TEST_F(RE2OptionsTest_21, CopyPreservesAllSettings_21) {
  RE2::Options src;
  src.set_log_errors(false);
  src.set_max_mem(12345);
  src.set_encoding(RE2::Options::EncodingLatin1);
  src.set_posix_syntax(true);
  src.set_longest_match(true);
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

  EXPECT_FALSE(dest.log_errors());
  EXPECT_EQ(dest.max_mem(), 12345);
  EXPECT_EQ(dest.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_TRUE(dest.posix_syntax());
  EXPECT_TRUE(dest.longest_match());
  EXPECT_TRUE(dest.literal());
  EXPECT_TRUE(dest.never_nl());
  EXPECT_TRUE(dest.dot_nl());
  EXPECT_TRUE(dest.never_capture());
  EXPECT_FALSE(dest.case_sensitive());
  EXPECT_TRUE(dest.perl_classes());
  EXPECT_TRUE(dest.word_boundary());
  EXPECT_TRUE(dest.one_line());
}

TEST_F(RE2OptionsTest_21, CopyFromDefaultOptions_21) {
  RE2::Options src;
  RE2::Options dest;
  dest.set_log_errors(false);
  dest.set_case_sensitive(false);

  dest.Copy(src);

  EXPECT_TRUE(dest.log_errors());
  EXPECT_TRUE(dest.case_sensitive());
}

// ==================== Multiple Set Calls Tests ====================

TEST_F(RE2OptionsTest_21, MultipleSetCallsLastWins_21) {
  options_.set_log_errors(true);
  options_.set_log_errors(false);
  options_.set_log_errors(true);
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_21, IndependentBooleanSettings_21) {
  options_.set_posix_syntax(true);
  options_.set_longest_match(false);
  options_.set_literal(true);
  options_.set_never_nl(false);

  EXPECT_TRUE(options_.posix_syntax());
  EXPECT_FALSE(options_.longest_match());
  EXPECT_TRUE(options_.literal());
  EXPECT_FALSE(options_.never_nl());
}

// ==================== ParseFlags Tests ====================

TEST_F(RE2OptionsTest_21, ParseFlagsDefaultOptions_21) {
  RE2::Options opts;
  // ParseFlags returns an int based on the options configuration.
  // We just verify it returns consistently.
  int flags1 = opts.ParseFlags();
  int flags2 = opts.ParseFlags();
  EXPECT_EQ(flags1, flags2);
}

TEST_F(RE2OptionsTest_21, ParseFlagsChangesWithSettings_21) {
  RE2::Options opts1;
  int flags_default = opts1.ParseFlags();

  RE2::Options opts2;
  opts2.set_case_sensitive(false);
  int flags_case_insensitive = opts2.ParseFlags();

  // Changing case sensitivity should change parse flags
  EXPECT_NE(flags_default, flags_case_insensitive);
}

TEST_F(RE2OptionsTest_21, ParseFlagsPosixSyntaxAffectsFlags_21) {
  RE2::Options opts1;
  int flags_default = opts1.ParseFlags();

  RE2::Options opts2;
  opts2.set_posix_syntax(true);
  int flags_posix = opts2.ParseFlags();

  EXPECT_NE(flags_default, flags_posix);
}

TEST_F(RE2OptionsTest_21, ParseFlagsLiteralAffectsFlags_21) {
  RE2::Options opts1;
  int flags_default = opts1.ParseFlags();

  RE2::Options opts2;
  opts2.set_literal(true);
  int flags_literal = opts2.ParseFlags();

  EXPECT_NE(flags_default, flags_literal);
}

// ==================== RE2 Integration Tests with Options ====================

class RE2WithOptionsTest_21 : public ::testing::Test {};

TEST_F(RE2WithOptionsTest_21, BasicMatchWithDefaultOptions_21) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

TEST_F(RE2WithOptionsTest_21, CaseInsensitiveMatch_21) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST_F(RE2WithOptionsTest_21, LiteralMatch_21) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

TEST_F(RE2WithOptionsTest_21, QuietOptionSuppressesLogErrors_21) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
  // Invalid regex with Quiet should not log errors
  RE2 re("(", opts);
  EXPECT_FALSE(re.ok());
}

TEST_F(RE2WithOptionsTest_21, POSIXOptionEnablesLongestMatch_21) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
}

TEST_F(RE2WithOptionsTest_21, DotNlOptionAllowsDotToMatchNewline_21) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2WithOptionsTest_21, DotNlFalseDisallowsDotMatchingNewline_21) {
  RE2::Options opts;
  opts.set_dot_nl(false);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2WithOptionsTest_21, NeverCaptureDisablesCapturing_21) {
  RE2::Options opts;
  opts.set_never_capture(true);
  RE2 re("(a)(b)", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2WithOptionsTest_21, Latin1EncodingOption_21) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
  RE2 re(".", opts);
  EXPECT_TRUE(re.ok());
}

}  // namespace re2
