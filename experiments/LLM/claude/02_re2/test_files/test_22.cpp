#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>

// Test fixture for RE2::Options tests
class RE2OptionsTest_22 : public ::testing::Test {
 protected:
  re2::RE2::Options options_;
};

// ==================== Default Constructor Tests ====================

TEST_F(RE2OptionsTest_22, DefaultConstructorMaxMem_22) {
  // Default max_mem should be kDefaultMaxMem (8<<20 = 8MB typically)
  EXPECT_GT(options_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_22, DefaultConstructorEncoding_22) {
  EXPECT_EQ(options_.encoding(), re2::RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_22, DefaultConstructorPosixSyntax_22) {
  EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_22, DefaultConstructorLongestMatch_22) {
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_22, DefaultConstructorLogErrors_22) {
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_22, DefaultConstructorLiteral_22) {
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_22, DefaultConstructorNeverNl_22) {
  EXPECT_FALSE(options_.never_nl());
}

TEST_F(RE2OptionsTest_22, DefaultConstructorDotNl_22) {
  EXPECT_FALSE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_22, DefaultConstructorNeverCapture_22) {
  EXPECT_FALSE(options_.never_capture());
}

TEST_F(RE2OptionsTest_22, DefaultConstructorCaseSensitive_22) {
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_22, DefaultConstructorPerlClasses_22) {
  EXPECT_FALSE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_22, DefaultConstructorWordBoundary_22) {
  EXPECT_FALSE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_22, DefaultConstructorOneLine_22) {
  EXPECT_FALSE(options_.one_line());
}

// ==================== CannedOptions Constructor Tests ====================

TEST_F(RE2OptionsTest_22, CannedOptionsLatin1Encoding_22) {
  re2::RE2::Options opts(re2::RE2::Latin1);
  EXPECT_EQ(opts.encoding(), re2::RE2::Options::EncodingLatin1);
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
}

TEST_F(RE2OptionsTest_22, CannedOptionsPOSIX_22) {
  re2::RE2::Options opts(re2::RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
  EXPECT_EQ(opts.encoding(), re2::RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_22, CannedOptionsQuiet_22) {
  re2::RE2::Options opts(re2::RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST_F(RE2OptionsTest_22, CannedOptionsDefaultRE2_22) {
  re2::RE2::Options opts(re2::RE2::DefaultOptions);
  EXPECT_EQ(opts.encoding(), re2::RE2::Options::EncodingUTF8);
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
}

// ==================== Setter/Getter Tests ====================

TEST_F(RE2OptionsTest_22, SetAndGetMaxMem_22) {
  options_.set_max_mem(1024 * 1024);
  EXPECT_EQ(options_.max_mem(), 1024 * 1024);
}

TEST_F(RE2OptionsTest_22, SetAndGetMaxMemZero_22) {
  options_.set_max_mem(0);
  EXPECT_EQ(options_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_22, SetAndGetMaxMemLargeValue_22) {
  int64_t large_val = static_cast<int64_t>(1) << 30;  // 1 GB
  options_.set_max_mem(large_val);
  EXPECT_EQ(options_.max_mem(), large_val);
}

TEST_F(RE2OptionsTest_22, SetAndGetEncodingUTF8_22) {
  options_.set_encoding(re2::RE2::Options::EncodingUTF8);
  EXPECT_EQ(options_.encoding(), re2::RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_22, SetAndGetEncodingLatin1_22) {
  options_.set_encoding(re2::RE2::Options::EncodingLatin1);
  EXPECT_EQ(options_.encoding(), re2::RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_22, SetAndGetPosixSyntaxTrue_22) {
  options_.set_posix_syntax(true);
  EXPECT_TRUE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_22, SetAndGetPosixSyntaxFalse_22) {
  options_.set_posix_syntax(true);
  options_.set_posix_syntax(false);
  EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_22, SetAndGetLongestMatchTrue_22) {
  options_.set_longest_match(true);
  EXPECT_TRUE(options_.longest_match());
}

TEST_F(RE2OptionsTest_22, SetAndGetLongestMatchFalse_22) {
  options_.set_longest_match(true);
  options_.set_longest_match(false);
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_22, SetAndGetLogErrorsTrue_22) {
  options_.set_log_errors(false);
  options_.set_log_errors(true);
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_22, SetAndGetLogErrorsFalse_22) {
  options_.set_log_errors(false);
  EXPECT_FALSE(options_.log_errors());
}

TEST_F(RE2OptionsTest_22, SetAndGetLiteralTrue_22) {
  options_.set_literal(true);
  EXPECT_TRUE(options_.literal());
}

TEST_F(RE2OptionsTest_22, SetAndGetLiteralFalse_22) {
  options_.set_literal(true);
  options_.set_literal(false);
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_22, SetAndGetNeverNlTrue_22) {
  options_.set_never_nl(true);
  EXPECT_TRUE(options_.never_nl());
}

TEST_F(RE2OptionsTest_22, SetAndGetNeverNlFalse_22) {
  options_.set_never_nl(true);
  options_.set_never_nl(false);
  EXPECT_FALSE(options_.never_nl());
}

TEST_F(RE2OptionsTest_22, SetAndGetDotNlTrue_22) {
  options_.set_dot_nl(true);
  EXPECT_TRUE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_22, SetAndGetDotNlFalse_22) {
  options_.set_dot_nl(true);
  options_.set_dot_nl(false);
  EXPECT_FALSE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_22, SetAndGetNeverCaptureTrue_22) {
  options_.set_never_capture(true);
  EXPECT_TRUE(options_.never_capture());
}

TEST_F(RE2OptionsTest_22, SetAndGetNeverCaptureFalse_22) {
  options_.set_never_capture(true);
  options_.set_never_capture(false);
  EXPECT_FALSE(options_.never_capture());
}

TEST_F(RE2OptionsTest_22, SetAndGetCaseSensitiveTrue_22) {
  options_.set_case_sensitive(false);
  options_.set_case_sensitive(true);
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_22, SetAndGetCaseSensitiveFalse_22) {
  options_.set_case_sensitive(false);
  EXPECT_FALSE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_22, SetAndGetPerlClassesTrue_22) {
  options_.set_perl_classes(true);
  EXPECT_TRUE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_22, SetAndGetPerlClassesFalse_22) {
  options_.set_perl_classes(true);
  options_.set_perl_classes(false);
  EXPECT_FALSE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_22, SetAndGetWordBoundaryTrue_22) {
  options_.set_word_boundary(true);
  EXPECT_TRUE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_22, SetAndGetWordBoundaryFalse_22) {
  options_.set_word_boundary(true);
  options_.set_word_boundary(false);
  EXPECT_FALSE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_22, SetAndGetOneLineTrue_22) {
  options_.set_one_line(true);
  EXPECT_TRUE(options_.one_line());
}

TEST_F(RE2OptionsTest_22, SetAndGetOneLineFalse_22) {
  options_.set_one_line(true);
  options_.set_one_line(false);
  EXPECT_FALSE(options_.one_line());
}

// ==================== Copy Tests ====================

TEST_F(RE2OptionsTest_22, CopyAllOptions_22) {
  re2::RE2::Options src;
  src.set_max_mem(12345);
  src.set_encoding(re2::RE2::Options::EncodingLatin1);
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

  re2::RE2::Options dst;
  dst.Copy(src);

  EXPECT_EQ(dst.max_mem(), 12345);
  EXPECT_EQ(dst.encoding(), re2::RE2::Options::EncodingLatin1);
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
}

TEST_F(RE2OptionsTest_22, CopyDefaultOptions_22) {
  re2::RE2::Options src;
  re2::RE2::Options dst;
  dst.set_literal(true);
  dst.set_dot_nl(true);

  dst.Copy(src);

  EXPECT_FALSE(dst.literal());
  EXPECT_FALSE(dst.dot_nl());
  EXPECT_TRUE(dst.log_errors());
  EXPECT_TRUE(dst.case_sensitive());
}

// ==================== ParseFlags Tests ====================

TEST_F(RE2OptionsTest_22, ParseFlagsDefaultOptions_22) {
  // ParseFlags should return a consistent value for default options
  int flags = options_.ParseFlags();
  // We just check it returns something without crashing
  (void)flags;
}

TEST_F(RE2OptionsTest_22, ParseFlagsChangeWithLiteral_22) {
  int flags_before = options_.ParseFlags();
  options_.set_literal(true);
  int flags_after = options_.ParseFlags();
  // Changing literal should potentially change parse flags
  // We don't know exact values but this verifies the method works
  (void)flags_before;
  (void)flags_after;
}

TEST_F(RE2OptionsTest_22, ParseFlagsChangeWithCaseSensitive_22) {
  int flags_before = options_.ParseFlags();
  options_.set_case_sensitive(false);
  int flags_after = options_.ParseFlags();
  EXPECT_NE(flags_before, flags_after);
}

TEST_F(RE2OptionsTest_22, ParseFlagsChangeWithPosixSyntax_22) {
  int flags_before = options_.ParseFlags();
  options_.set_posix_syntax(true);
  int flags_after = options_.ParseFlags();
  EXPECT_NE(flags_before, flags_after);
}

// ==================== RE2 with Options Integration Tests ====================

class RE2WithOptionsTest_22 : public ::testing::Test {};

TEST_F(RE2WithOptionsTest_22, LiteralOptionMatchesLiteralString_22) {
  re2::RE2::Options opts;
  opts.set_literal(true);
  re2::RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  // With literal mode, "a.b" should match literal "a.b" not regex
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

TEST_F(RE2WithOptionsTest_22, NonLiteralOptionMatchesRegex_22) {
  re2::RE2::Options opts;
  opts.set_literal(false);
  re2::RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_TRUE(RE2::FullMatch("axb", re));
}

TEST_F(RE2WithOptionsTest_22, CaseInsensitiveMatch_22) {
  re2::RE2::Options opts;
  opts.set_case_sensitive(false);
  re2::RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HeLLo", re));
}

TEST_F(RE2WithOptionsTest_22, CaseSensitiveMatch_22) {
  re2::RE2::Options opts;
  opts.set_case_sensitive(true);
  re2::RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
}

TEST_F(RE2WithOptionsTest_22, DotNlOption_22) {
  re2::RE2::Options opts;
  opts.set_dot_nl(true);
  re2::RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2WithOptionsTest_22, DotNlOptionDisabled_22) {
  re2::RE2::Options opts;
  opts.set_dot_nl(false);
  re2::RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2WithOptionsTest_22, NeverCaptureOption_22) {
  re2::RE2::Options opts;
  opts.set_never_capture(true);
  re2::RE2 re("(a)(b)", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2WithOptionsTest_22, NeverCaptureOptionDisabled_22) {
  re2::RE2::Options opts;
  opts.set_never_capture(false);
  re2::RE2 re("(a)(b)", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 2);
}

TEST_F(RE2WithOptionsTest_22, POSIXCannedOption_22) {
  re2::RE2 re("a+", re2::RE2::POSIX);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
}

TEST_F(RE2WithOptionsTest_22, QuietCannedOption_22) {
  // Quiet mode should not log errors for invalid patterns
  re2::RE2 re("(", re2::RE2::Quiet);
  EXPECT_FALSE(re.ok());
}

TEST_F(RE2WithOptionsTest_22, Latin1Encoding_22) {
  re2::RE2::Options opts;
  opts.set_encoding(re2::RE2::Options::EncodingLatin1);
  re2::RE2 re("\\xff", opts);
  EXPECT_TRUE(re.ok());
}

// ==================== Multiple Set/Get Round-Trip Tests ====================

TEST_F(RE2OptionsTest_22, MultipleSetGetRoundTrips_22) {
  for (int i = 0; i < 10; ++i) {
    bool val = (i % 2 == 0);
    options_.set_literal(val);
    EXPECT_EQ(options_.literal(), val);
    options_.set_dot_nl(!val);
    EXPECT_EQ(options_.dot_nl(), !val);
  }
}

TEST_F(RE2OptionsTest_22, SetMaxMemNegativeValue_22) {
  // Boundary: test with negative value
  options_.set_max_mem(-1);
  EXPECT_EQ(options_.max_mem(), -1);
}

TEST_F(RE2OptionsTest_22, SetMaxMemMaxInt64_22) {
  int64_t max_val = INT64_MAX;
  options_.set_max_mem(max_val);
  EXPECT_EQ(options_.max_mem(), max_val);
}
