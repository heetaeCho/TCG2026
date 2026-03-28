#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// Test fixture for RE2::Options tests
class RE2OptionsTest_29 : public ::testing::Test {
 protected:
  RE2::Options options_;
};

// ==================== Default Constructor Tests ====================

TEST_F(RE2OptionsTest_29, DefaultConstructorMaxMem_29) {
  // Default max_mem should be kDefaultMaxMem (8<<20 = 8388608)
  EXPECT_GT(options_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_29, DefaultConstructorEncoding_29) {
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_29, DefaultConstructorPosixSyntax_29) {
  EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_29, DefaultConstructorLongestMatch_29) {
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_29, DefaultConstructorLogErrors_29) {
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_29, DefaultConstructorLiteral_29) {
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_29, DefaultConstructorNeverNl_29) {
  EXPECT_FALSE(options_.never_nl());
}

TEST_F(RE2OptionsTest_29, DefaultConstructorDotNl_29) {
  EXPECT_FALSE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_29, DefaultConstructorNeverCapture_29) {
  EXPECT_FALSE(options_.never_capture());
}

TEST_F(RE2OptionsTest_29, DefaultConstructorCaseSensitive_29) {
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_29, DefaultConstructorPerlClasses_29) {
  EXPECT_FALSE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_29, DefaultConstructorWordBoundary_29) {
  EXPECT_FALSE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_29, DefaultConstructorOneLine_29) {
  EXPECT_FALSE(options_.one_line());
}

// ==================== CannedOptions Constructor Tests ====================

TEST_F(RE2OptionsTest_29, CannedOptionsLatin1Encoding_29) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_29, CannedOptionsPOSIXPosixSyntax_29) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_29, CannedOptionsPOSIXLongestMatch_29) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST_F(RE2OptionsTest_29, CannedOptionsQuietLogErrors_29) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST_F(RE2OptionsTest_29, CannedOptionsQuietEncoding_29) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_29, CannedOptionsDefaultNoCapture_29) {
  RE2::Options opts(RE2::DefaultOptions);
  EXPECT_FALSE(opts.never_capture());
}

TEST_F(RE2OptionsTest_29, CannedOptionsDefaultCaseSensitive_29) {
  RE2::Options opts(RE2::DefaultOptions);
  EXPECT_TRUE(opts.case_sensitive());
}

// ==================== Setter/Getter Tests ====================

TEST_F(RE2OptionsTest_29, SetMaxMem_29) {
  options_.set_max_mem(1024);
  EXPECT_EQ(options_.max_mem(), 1024);
}

TEST_F(RE2OptionsTest_29, SetMaxMemZero_29) {
  options_.set_max_mem(0);
  EXPECT_EQ(options_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_29, SetMaxMemLargeValue_29) {
  int64_t large_val = static_cast<int64_t>(1) << 30;
  options_.set_max_mem(large_val);
  EXPECT_EQ(options_.max_mem(), large_val);
}

TEST_F(RE2OptionsTest_29, SetEncodingUTF8_29) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  options_.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_29, SetEncodingLatin1_29) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_29, SetPosixSyntaxTrue_29) {
  options_.set_posix_syntax(true);
  EXPECT_TRUE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_29, SetPosixSyntaxFalse_29) {
  options_.set_posix_syntax(true);
  options_.set_posix_syntax(false);
  EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_29, SetLongestMatchTrue_29) {
  options_.set_longest_match(true);
  EXPECT_TRUE(options_.longest_match());
}

TEST_F(RE2OptionsTest_29, SetLongestMatchFalse_29) {
  options_.set_longest_match(true);
  options_.set_longest_match(false);
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_29, SetLogErrorsTrue_29) {
  options_.set_log_errors(false);
  options_.set_log_errors(true);
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_29, SetLogErrorsFalse_29) {
  options_.set_log_errors(false);
  EXPECT_FALSE(options_.log_errors());
}

TEST_F(RE2OptionsTest_29, SetLiteralTrue_29) {
  options_.set_literal(true);
  EXPECT_TRUE(options_.literal());
}

TEST_F(RE2OptionsTest_29, SetLiteralFalse_29) {
  options_.set_literal(true);
  options_.set_literal(false);
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_29, SetNeverNlTrue_29) {
  options_.set_never_nl(true);
  EXPECT_TRUE(options_.never_nl());
}

TEST_F(RE2OptionsTest_29, SetNeverNlFalse_29) {
  options_.set_never_nl(true);
  options_.set_never_nl(false);
  EXPECT_FALSE(options_.never_nl());
}

TEST_F(RE2OptionsTest_29, SetDotNlTrue_29) {
  options_.set_dot_nl(true);
  EXPECT_TRUE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_29, SetDotNlFalse_29) {
  options_.set_dot_nl(true);
  options_.set_dot_nl(false);
  EXPECT_FALSE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_29, SetNeverCaptureTrue_29) {
  options_.set_never_capture(true);
  EXPECT_TRUE(options_.never_capture());
}

TEST_F(RE2OptionsTest_29, SetNeverCaptureFalse_29) {
  options_.set_never_capture(true);
  options_.set_never_capture(false);
  EXPECT_FALSE(options_.never_capture());
}

TEST_F(RE2OptionsTest_29, SetCaseSensitiveTrue_29) {
  options_.set_case_sensitive(false);
  options_.set_case_sensitive(true);
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_29, SetCaseSensitiveFalse_29) {
  options_.set_case_sensitive(false);
  EXPECT_FALSE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_29, SetPerlClassesTrue_29) {
  options_.set_perl_classes(true);
  EXPECT_TRUE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_29, SetPerlClassesFalse_29) {
  options_.set_perl_classes(true);
  options_.set_perl_classes(false);
  EXPECT_FALSE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_29, SetWordBoundaryTrue_29) {
  options_.set_word_boundary(true);
  EXPECT_TRUE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_29, SetWordBoundaryFalse_29) {
  options_.set_word_boundary(true);
  options_.set_word_boundary(false);
  EXPECT_FALSE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_29, SetOneLineTrue_29) {
  options_.set_one_line(true);
  EXPECT_TRUE(options_.one_line());
}

TEST_F(RE2OptionsTest_29, SetOneLineFalse_29) {
  options_.set_one_line(true);
  options_.set_one_line(false);
  EXPECT_FALSE(options_.one_line());
}

// ==================== Copy Tests ====================

TEST_F(RE2OptionsTest_29, CopyAllOptions_29) {
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

TEST_F(RE2OptionsTest_29, CopyDefaultOptions_29) {
  RE2::Options src;
  RE2::Options dest;
  dest.set_never_capture(true);
  dest.set_case_sensitive(false);

  dest.Copy(src);

  EXPECT_FALSE(dest.never_capture());
  EXPECT_TRUE(dest.case_sensitive());
}

// ==================== Multiple Set/Get Cycles ====================

TEST_F(RE2OptionsTest_29, ToggleNeverCaptureMultipleTimes_29) {
  options_.set_never_capture(true);
  EXPECT_TRUE(options_.never_capture());
  options_.set_never_capture(false);
  EXPECT_FALSE(options_.never_capture());
  options_.set_never_capture(true);
  EXPECT_TRUE(options_.never_capture());
}

TEST_F(RE2OptionsTest_29, SetMultipleOptionsIndependently_29) {
  options_.set_never_capture(true);
  options_.set_dot_nl(true);
  options_.set_case_sensitive(false);

  EXPECT_TRUE(options_.never_capture());
  EXPECT_TRUE(options_.dot_nl());
  EXPECT_FALSE(options_.case_sensitive());

  // Ensure other defaults are unaffected
  EXPECT_FALSE(options_.posix_syntax());
  EXPECT_FALSE(options_.longest_match());
  EXPECT_TRUE(options_.log_errors());
  EXPECT_FALSE(options_.literal());
  EXPECT_FALSE(options_.never_nl());
  EXPECT_FALSE(options_.perl_classes());
  EXPECT_FALSE(options_.word_boundary());
  EXPECT_FALSE(options_.one_line());
}

// ==================== ParseFlags Tests ====================

TEST_F(RE2OptionsTest_29, ParseFlagsDefaultReturnsNonNegative_29) {
  int flags = options_.ParseFlags();
  // ParseFlags should return a valid flags value
  EXPECT_GE(flags, 0);
}

TEST_F(RE2OptionsTest_29, ParseFlagsChangesWithPosixSyntax_29) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_posix_syntax(true);

  // Changing posix_syntax should result in different parse flags
  int flags1 = opts1.ParseFlags();
  int flags2 = opts2.ParseFlags();
  EXPECT_NE(flags1, flags2);
}

TEST_F(RE2OptionsTest_29, ParseFlagsChangesWithCaseSensitive_29) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_case_sensitive(false);

  int flags1 = opts1.ParseFlags();
  int flags2 = opts2.ParseFlags();
  EXPECT_NE(flags1, flags2);
}

TEST_F(RE2OptionsTest_29, ParseFlagsChangesWithLiteral_29) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_literal(true);

  int flags1 = opts1.ParseFlags();
  int flags2 = opts2.ParseFlags();
  EXPECT_NE(flags1, flags2);
}

TEST_F(RE2OptionsTest_29, ParseFlagsChangesWithNeverCapture_29) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_never_capture(true);

  int flags1 = opts1.ParseFlags();
  int flags2 = opts2.ParseFlags();
  EXPECT_NE(flags1, flags2);
}

// ==================== RE2 with Options Integration Tests ====================

TEST_F(RE2OptionsTest_29, RE2WithNeverCaptureOption_29) {
  RE2::Options opts;
  opts.set_never_capture(true);
  RE2 re("(\\d+)", opts);
  EXPECT_TRUE(re.ok());

  // With never_capture, the regex should have no capturing groups
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2OptionsTest_29, RE2WithoutNeverCaptureOption_29) {
  RE2::Options opts;
  opts.set_never_capture(false);
  RE2 re("(\\d+)", opts);
  EXPECT_TRUE(re.ok());

  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST_F(RE2OptionsTest_29, RE2WithCaseInsensitive_29) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());

  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HeLLo", re));
}

TEST_F(RE2OptionsTest_29, RE2WithCaseSensitive_29) {
  RE2::Options opts;
  opts.set_case_sensitive(true);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());

  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
}

TEST_F(RE2OptionsTest_29, RE2WithLiteralOption_29) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());

  // With literal, "a.b" matches literal "a.b" not "aXb"
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("aXb", re));
}

TEST_F(RE2OptionsTest_29, RE2WithDotNlOption_29) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());

  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2OptionsTest_29, RE2WithoutDotNlOption_29) {
  RE2::Options opts;
  opts.set_dot_nl(false);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());

  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2OptionsTest_29, RE2WithLongestMatchOption_29) {
  RE2::Options opts;
  opts.set_longest_match(true);
  RE2 re("a+", opts);
  EXPECT_TRUE(re.ok());
}

TEST_F(RE2OptionsTest_29, RE2WithLogErrorsFalse_29) {
  RE2::Options opts;
  opts.set_log_errors(false);
  // Invalid regex should not log errors but still fail
  RE2 re("(unclosed", opts);
  EXPECT_FALSE(re.ok());
}

TEST_F(RE2OptionsTest_29, RE2WithQuietOption_29) {
  RE2 re("(unclosed", RE2::Quiet);
  EXPECT_FALSE(re.ok());
}

TEST_F(RE2OptionsTest_29, RE2WithLatin1Option_29) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
  RE2 re("test", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("test", re));
}

}  // namespace re2
