#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// Test fixture for RE2::Options
class RE2OptionsTest_33 : public ::testing::Test {
 protected:
  RE2::Options options_;
};

// ==================== Default Constructor Tests ====================

TEST_F(RE2OptionsTest_33, DefaultConstructorMaxMem_33) {
  // Default max_mem should be kDefaultMaxMem (8<<20 = 8388608)
  EXPECT_GT(options_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_33, DefaultConstructorEncoding_33) {
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_33, DefaultConstructorPosixSyntax_33) {
  EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_33, DefaultConstructorLongestMatch_33) {
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_33, DefaultConstructorLogErrors_33) {
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_33, DefaultConstructorLiteral_33) {
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_33, DefaultConstructorNeverNl_33) {
  EXPECT_FALSE(options_.never_nl());
}

TEST_F(RE2OptionsTest_33, DefaultConstructorDotNl_33) {
  EXPECT_FALSE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_33, DefaultConstructorNeverCapture_33) {
  EXPECT_FALSE(options_.never_capture());
}

TEST_F(RE2OptionsTest_33, DefaultConstructorCaseSensitive_33) {
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_33, DefaultConstructorPerlClasses_33) {
  EXPECT_FALSE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_33, DefaultConstructorWordBoundary_33) {
  EXPECT_FALSE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_33, DefaultConstructorOneLine_33) {
  EXPECT_FALSE(options_.one_line());
}

// ==================== CannedOptions Constructor Tests ====================

TEST_F(RE2OptionsTest_33, CannedOptionsLatin1Encoding_33) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_33, CannedOptionsPOSIXSyntax_33) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
}

TEST_F(RE2OptionsTest_33, CannedOptionsQuietLogErrors_33) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST_F(RE2OptionsTest_33, CannedOptionsPOSIXPerlClassesFalse_33) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_FALSE(opts.perl_classes());
}

TEST_F(RE2OptionsTest_33, CannedOptionsQuietCaseSensitiveTrue_33) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_TRUE(opts.case_sensitive());
}

// ==================== Setter/Getter Tests ====================

TEST_F(RE2OptionsTest_33, SetAndGetMaxMem_33) {
  options_.set_max_mem(1024);
  EXPECT_EQ(options_.max_mem(), 1024);
}

TEST_F(RE2OptionsTest_33, SetAndGetMaxMemZero_33) {
  options_.set_max_mem(0);
  EXPECT_EQ(options_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_33, SetAndGetMaxMemLargeValue_33) {
  int64_t large = static_cast<int64_t>(1) << 30;
  options_.set_max_mem(large);
  EXPECT_EQ(options_.max_mem(), large);
}

TEST_F(RE2OptionsTest_33, SetAndGetEncodingUTF8_33) {
  options_.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_33, SetAndGetEncodingLatin1_33) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_33, SetAndGetPosixSyntaxTrue_33) {
  options_.set_posix_syntax(true);
  EXPECT_TRUE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_33, SetAndGetPosixSyntaxFalse_33) {
  options_.set_posix_syntax(true);
  options_.set_posix_syntax(false);
  EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_33, SetAndGetLongestMatchTrue_33) {
  options_.set_longest_match(true);
  EXPECT_TRUE(options_.longest_match());
}

TEST_F(RE2OptionsTest_33, SetAndGetLongestMatchFalse_33) {
  options_.set_longest_match(true);
  options_.set_longest_match(false);
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_33, SetAndGetLogErrorsTrue_33) {
  options_.set_log_errors(false);
  options_.set_log_errors(true);
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_33, SetAndGetLogErrorsFalse_33) {
  options_.set_log_errors(false);
  EXPECT_FALSE(options_.log_errors());
}

TEST_F(RE2OptionsTest_33, SetAndGetLiteralTrue_33) {
  options_.set_literal(true);
  EXPECT_TRUE(options_.literal());
}

TEST_F(RE2OptionsTest_33, SetAndGetLiteralFalse_33) {
  options_.set_literal(false);
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_33, SetAndGetNeverNlTrue_33) {
  options_.set_never_nl(true);
  EXPECT_TRUE(options_.never_nl());
}

TEST_F(RE2OptionsTest_33, SetAndGetNeverNlFalse_33) {
  options_.set_never_nl(false);
  EXPECT_FALSE(options_.never_nl());
}

TEST_F(RE2OptionsTest_33, SetAndGetDotNlTrue_33) {
  options_.set_dot_nl(true);
  EXPECT_TRUE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_33, SetAndGetDotNlFalse_33) {
  options_.set_dot_nl(false);
  EXPECT_FALSE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_33, SetAndGetNeverCaptureTrue_33) {
  options_.set_never_capture(true);
  EXPECT_TRUE(options_.never_capture());
}

TEST_F(RE2OptionsTest_33, SetAndGetNeverCaptureFalse_33) {
  options_.set_never_capture(false);
  EXPECT_FALSE(options_.never_capture());
}

TEST_F(RE2OptionsTest_33, SetAndGetCaseSensitiveTrue_33) {
  options_.set_case_sensitive(true);
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_33, SetAndGetCaseSensitiveFalse_33) {
  options_.set_case_sensitive(false);
  EXPECT_FALSE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_33, SetAndGetPerlClassesTrue_33) {
  options_.set_perl_classes(true);
  EXPECT_TRUE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_33, SetAndGetPerlClassesFalse_33) {
  options_.set_perl_classes(true);
  options_.set_perl_classes(false);
  EXPECT_FALSE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_33, SetAndGetWordBoundaryTrue_33) {
  options_.set_word_boundary(true);
  EXPECT_TRUE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_33, SetAndGetWordBoundaryFalse_33) {
  options_.set_word_boundary(true);
  options_.set_word_boundary(false);
  EXPECT_FALSE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_33, SetAndGetOneLineTrue_33) {
  options_.set_one_line(true);
  EXPECT_TRUE(options_.one_line());
}

TEST_F(RE2OptionsTest_33, SetAndGetOneLineFalse_33) {
  options_.set_one_line(true);
  options_.set_one_line(false);
  EXPECT_FALSE(options_.one_line());
}

// ==================== Copy Tests ====================

TEST_F(RE2OptionsTest_33, CopyAllOptions_33) {
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

  RE2::Options dest;
  dest.Copy(src);

  EXPECT_EQ(dest.max_mem(), 2048);
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

TEST_F(RE2OptionsTest_33, CopyDefaultOptions_33) {
  RE2::Options src;
  RE2::Options dest;
  dest.set_perl_classes(true);
  dest.set_case_sensitive(false);

  dest.Copy(src);

  EXPECT_FALSE(dest.perl_classes());
  EXPECT_TRUE(dest.case_sensitive());
}

// ==================== ParseFlags Tests ====================

TEST_F(RE2OptionsTest_33, ParseFlagsDefaultOptions_33) {
  // ParseFlags should return a valid integer for default options
  int flags = options_.ParseFlags();
  EXPECT_NE(flags, 0);  // Default options should produce non-zero flags
}

TEST_F(RE2OptionsTest_33, ParseFlagsChangesWithPerlClasses_33) {
  int flags_without = options_.ParseFlags();
  options_.set_perl_classes(true);
  int flags_with = options_.ParseFlags();
  EXPECT_NE(flags_without, flags_with);
}

TEST_F(RE2OptionsTest_33, ParseFlagsChangesWithWordBoundary_33) {
  int flags_without = options_.ParseFlags();
  options_.set_word_boundary(true);
  int flags_with = options_.ParseFlags();
  EXPECT_NE(flags_without, flags_with);
}

TEST_F(RE2OptionsTest_33, ParseFlagsChangesWithCaseSensitive_33) {
  int flags_with_case = options_.ParseFlags();
  options_.set_case_sensitive(false);
  int flags_without_case = options_.ParseFlags();
  EXPECT_NE(flags_with_case, flags_without_case);
}

TEST_F(RE2OptionsTest_33, ParseFlagsChangesWithOneLine_33) {
  int flags_without = options_.ParseFlags();
  options_.set_one_line(true);
  int flags_with = options_.ParseFlags();
  EXPECT_NE(flags_without, flags_with);
}

TEST_F(RE2OptionsTest_33, ParseFlagsChangesWithNeverNl_33) {
  int flags_without = options_.ParseFlags();
  options_.set_never_nl(true);
  int flags_with = options_.ParseFlags();
  EXPECT_NE(flags_without, flags_with);
}

TEST_F(RE2OptionsTest_33, ParseFlagsChangesWithDotNl_33) {
  int flags_without = options_.ParseFlags();
  options_.set_dot_nl(true);
  int flags_with = options_.ParseFlags();
  EXPECT_NE(flags_without, flags_with);
}

TEST_F(RE2OptionsTest_33, ParseFlagsChangesWithLiteral_33) {
  int flags_without = options_.ParseFlags();
  options_.set_literal(true);
  int flags_with = options_.ParseFlags();
  EXPECT_NE(flags_without, flags_with);
}

TEST_F(RE2OptionsTest_33, ParseFlagsChangesWithNeverCapture_33) {
  int flags_without = options_.ParseFlags();
  options_.set_never_capture(true);
  int flags_with = options_.ParseFlags();
  EXPECT_NE(flags_without, flags_with);
}

// ==================== Multiple Set Operations ====================

TEST_F(RE2OptionsTest_33, SetPerlClassesMultipleTimes_33) {
  options_.set_perl_classes(true);
  EXPECT_TRUE(options_.perl_classes());
  options_.set_perl_classes(false);
  EXPECT_FALSE(options_.perl_classes());
  options_.set_perl_classes(true);
  EXPECT_TRUE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_33, SetMaxMemMultipleTimes_33) {
  options_.set_max_mem(100);
  EXPECT_EQ(options_.max_mem(), 100);
  options_.set_max_mem(200);
  EXPECT_EQ(options_.max_mem(), 200);
  options_.set_max_mem(0);
  EXPECT_EQ(options_.max_mem(), 0);
}

// ==================== Boundary Conditions ====================

TEST_F(RE2OptionsTest_33, MaxMemNegativeValue_33) {
  options_.set_max_mem(-1);
  EXPECT_EQ(options_.max_mem(), -1);
}

TEST_F(RE2OptionsTest_33, MaxMemMaxInt64_33) {
  int64_t maxval = INT64_MAX;
  options_.set_max_mem(maxval);
  EXPECT_EQ(options_.max_mem(), maxval);
}

// ==================== Integration: Options affect RE2 behavior ====================

TEST_F(RE2OptionsTest_33, RE2WithDefaultOptions_33) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
}

TEST_F(RE2OptionsTest_33, RE2WithCaseInsensitive_33) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
}

TEST_F(RE2OptionsTest_33, RE2WithLiteral_33) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  // With literal, "a.b" should match literally, not as regex
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

TEST_F(RE2OptionsTest_33, RE2WithPosixSyntax_33) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  RE2 re("abc", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
}

TEST_F(RE2OptionsTest_33, RE2WithDotNl_33) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2OptionsTest_33, RE2WithoutDotNl_33) {
  RE2::Options opts;
  opts.set_dot_nl(false);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2OptionsTest_33, RE2WithLatin1Encoding_33) {
  RE2::Options opts(RE2::Latin1);
  RE2 re("test", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("test", re));
}

TEST_F(RE2OptionsTest_33, RE2WithQuietOption_33) {
  RE2::Options opts(RE2::Quiet);
  // Invalid regex should not log errors with Quiet
  RE2 re("(invalid", opts);
  EXPECT_FALSE(re.ok());
}

}  // namespace re2
