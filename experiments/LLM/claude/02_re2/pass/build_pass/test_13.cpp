#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// Test fixture for RE2::Options
class RE2OptionsTest_13 : public ::testing::Test {
 protected:
  RE2::Options options_;
};

// ==================== Default Constructor Tests ====================

TEST_F(RE2OptionsTest_13, DefaultConstructorMaxMem_13) {
  // Default max_mem should be kDefaultMaxMem (8<<20 = 8388608)
  EXPECT_GT(options_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_13, DefaultConstructorEncoding_13) {
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_13, DefaultConstructorPosixSyntax_13) {
  EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_13, DefaultConstructorLongestMatch_13) {
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_13, DefaultConstructorLogErrors_13) {
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_13, DefaultConstructorLiteral_13) {
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_13, DefaultConstructorNeverNl_13) {
  EXPECT_FALSE(options_.never_nl());
}

TEST_F(RE2OptionsTest_13, DefaultConstructorDotNl_13) {
  EXPECT_FALSE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_13, DefaultConstructorNeverCapture_13) {
  EXPECT_FALSE(options_.never_capture());
}

TEST_F(RE2OptionsTest_13, DefaultConstructorCaseSensitive_13) {
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_13, DefaultConstructorPerlClasses_13) {
  EXPECT_FALSE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_13, DefaultConstructorWordBoundary_13) {
  EXPECT_FALSE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_13, DefaultConstructorOneLine_13) {
  EXPECT_FALSE(options_.one_line());
}

// ==================== CannedOptions Constructor Tests ====================

TEST_F(RE2OptionsTest_13, Latin1ConstructorEncoding_13) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_13, Latin1ConstructorPosixSyntax_13) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_13, Latin1ConstructorLongestMatch_13) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.longest_match());
}

TEST_F(RE2OptionsTest_13, POSIXConstructorPosixSyntax_13) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_13, POSIXConstructorLongestMatch_13) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST_F(RE2OptionsTest_13, POSIXConstructorEncoding_13) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_13, QuietConstructorLogErrors_13) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST_F(RE2OptionsTest_13, QuietConstructorCaseSensitive_13) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_TRUE(opts.case_sensitive());
}

TEST_F(RE2OptionsTest_13, DefaultCannedConstructor_13) {
  RE2::Options opts(RE2::DefaultOptions);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
}

// ==================== Setter/Getter Tests ====================

TEST_F(RE2OptionsTest_13, SetAndGetMaxMem_13) {
  options_.set_max_mem(1024);
  EXPECT_EQ(options_.max_mem(), 1024);
}

TEST_F(RE2OptionsTest_13, SetMaxMemZero_13) {
  options_.set_max_mem(0);
  EXPECT_EQ(options_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_13, SetMaxMemLargeValue_13) {
  int64_t large_val = static_cast<int64_t>(1) << 30;
  options_.set_max_mem(large_val);
  EXPECT_EQ(options_.max_mem(), large_val);
}

TEST_F(RE2OptionsTest_13, SetAndGetEncodingUTF8_13) {
  options_.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_13, SetAndGetEncodingLatin1_13) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_13, SetAndGetPosixSyntaxTrue_13) {
  options_.set_posix_syntax(true);
  EXPECT_TRUE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_13, SetAndGetPosixSyntaxFalse_13) {
  options_.set_posix_syntax(false);
  EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_13, SetAndGetLongestMatchTrue_13) {
  options_.set_longest_match(true);
  EXPECT_TRUE(options_.longest_match());
}

TEST_F(RE2OptionsTest_13, SetAndGetLongestMatchFalse_13) {
  options_.set_longest_match(false);
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_13, SetAndGetLogErrorsTrue_13) {
  options_.set_log_errors(true);
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_13, SetAndGetLogErrorsFalse_13) {
  options_.set_log_errors(false);
  EXPECT_FALSE(options_.log_errors());
}

TEST_F(RE2OptionsTest_13, SetAndGetLiteralTrue_13) {
  options_.set_literal(true);
  EXPECT_TRUE(options_.literal());
}

TEST_F(RE2OptionsTest_13, SetAndGetLiteralFalse_13) {
  options_.set_literal(false);
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_13, SetAndGetNeverNlTrue_13) {
  options_.set_never_nl(true);
  EXPECT_TRUE(options_.never_nl());
}

TEST_F(RE2OptionsTest_13, SetAndGetNeverNlFalse_13) {
  options_.set_never_nl(false);
  EXPECT_FALSE(options_.never_nl());
}

TEST_F(RE2OptionsTest_13, SetAndGetDotNlTrue_13) {
  options_.set_dot_nl(true);
  EXPECT_TRUE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_13, SetAndGetDotNlFalse_13) {
  options_.set_dot_nl(false);
  EXPECT_FALSE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_13, SetAndGetNeverCaptureTrue_13) {
  options_.set_never_capture(true);
  EXPECT_TRUE(options_.never_capture());
}

TEST_F(RE2OptionsTest_13, SetAndGetNeverCaptureFalse_13) {
  options_.set_never_capture(false);
  EXPECT_FALSE(options_.never_capture());
}

TEST_F(RE2OptionsTest_13, SetAndGetCaseSensitiveTrue_13) {
  options_.set_case_sensitive(true);
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_13, SetAndGetCaseSensitiveFalse_13) {
  options_.set_case_sensitive(false);
  EXPECT_FALSE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_13, SetAndGetPerlClassesTrue_13) {
  options_.set_perl_classes(true);
  EXPECT_TRUE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_13, SetAndGetPerlClassesFalse_13) {
  options_.set_perl_classes(false);
  EXPECT_FALSE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_13, SetAndGetWordBoundaryTrue_13) {
  options_.set_word_boundary(true);
  EXPECT_TRUE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_13, SetAndGetWordBoundaryFalse_13) {
  options_.set_word_boundary(false);
  EXPECT_FALSE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_13, SetAndGetOneLineTrue_13) {
  options_.set_one_line(true);
  EXPECT_TRUE(options_.one_line());
}

TEST_F(RE2OptionsTest_13, SetAndGetOneLineFalse_13) {
  options_.set_one_line(false);
  EXPECT_FALSE(options_.one_line());
}

// ==================== Copy Tests ====================

TEST_F(RE2OptionsTest_13, CopyAllOptions_13) {
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

TEST_F(RE2OptionsTest_13, CopyDefaultOptions_13) {
  RE2::Options src;
  RE2::Options dest;
  dest.set_max_mem(999);
  dest.set_literal(true);

  dest.Copy(src);

  EXPECT_EQ(dest.max_mem(), src.max_mem());
  EXPECT_EQ(dest.literal(), src.literal());
  EXPECT_EQ(dest.encoding(), src.encoding());
}

// ==================== Multiple Set Calls ====================

TEST_F(RE2OptionsTest_13, OverwriteMaxMem_13) {
  options_.set_max_mem(100);
  EXPECT_EQ(options_.max_mem(), 100);
  options_.set_max_mem(200);
  EXPECT_EQ(options_.max_mem(), 200);
}

TEST_F(RE2OptionsTest_13, ToggleBoolOption_13) {
  options_.set_case_sensitive(false);
  EXPECT_FALSE(options_.case_sensitive());
  options_.set_case_sensitive(true);
  EXPECT_TRUE(options_.case_sensitive());
}

// ==================== ParseFlags Test ====================

TEST_F(RE2OptionsTest_13, ParseFlagsDefaultOptions_13) {
  // ParseFlags should return a valid integer for default options
  int flags = options_.ParseFlags();
  // We can't check exact value without knowing internals, but it should be consistent
  EXPECT_EQ(flags, options_.ParseFlags());
}

TEST_F(RE2OptionsTest_13, ParseFlagsChangesWithOptions_13) {
  int flags_default = options_.ParseFlags();
  options_.set_case_sensitive(false);
  int flags_case_insensitive = options_.ParseFlags();
  // Changing case_sensitive should change parse flags
  EXPECT_NE(flags_default, flags_case_insensitive);
}

TEST_F(RE2OptionsTest_13, ParseFlagsPosixSyntax_13) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_posix_syntax(true);
  // POSIX syntax should produce different flags
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

TEST_F(RE2OptionsTest_13, ParseFlagsLongestMatch_13) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_longest_match(true);
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

TEST_F(RE2OptionsTest_13, ParseFlagsLiteral_13) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_literal(true);
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

TEST_F(RE2OptionsTest_13, ParseFlagsNeverNl_13) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_never_nl(true);
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

TEST_F(RE2OptionsTest_13, ParseFlagsDotNl_13) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_dot_nl(true);
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

TEST_F(RE2OptionsTest_13, ParseFlagsNeverCapture_13) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_never_capture(true);
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

// ==================== Boundary Value Tests ====================

TEST_F(RE2OptionsTest_13, SetMaxMemNegative_13) {
  options_.set_max_mem(-1);
  EXPECT_EQ(options_.max_mem(), -1);
}

TEST_F(RE2OptionsTest_13, SetMaxMemMaxInt64_13) {
  int64_t max_val = std::numeric_limits<int64_t>::max();
  options_.set_max_mem(max_val);
  EXPECT_EQ(options_.max_mem(), max_val);
}

TEST_F(RE2OptionsTest_13, SetMaxMemMinInt64_13) {
  int64_t min_val = std::numeric_limits<int64_t>::min();
  options_.set_max_mem(min_val);
  EXPECT_EQ(options_.max_mem(), min_val);
}

// ==================== Independence of Options ====================

TEST_F(RE2OptionsTest_13, SettingOneOptionDoesNotAffectOthers_13) {
  // Record defaults
  bool default_posix = options_.posix_syntax();
  bool default_longest = options_.longest_match();
  bool default_literal = options_.literal();

  options_.set_case_sensitive(false);

  EXPECT_EQ(options_.posix_syntax(), default_posix);
  EXPECT_EQ(options_.longest_match(), default_longest);
  EXPECT_EQ(options_.literal(), default_literal);
}

}  // namespace re2
