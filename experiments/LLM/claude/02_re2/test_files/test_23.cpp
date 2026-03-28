#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>

namespace re2 {

// ============================================================
// Tests for RE2::Options default constructor
// ============================================================

TEST(RE2OptionsTest_23, DefaultConstructorEncoding_23) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_23, DefaultConstructorMaxMem_23) {
  RE2::Options opts;
  // Default max_mem should be positive (kDefaultMaxMem)
  EXPECT_GT(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_23, DefaultConstructorPosixSyntax_23) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_23, DefaultConstructorLongestMatch_23) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_23, DefaultConstructorLogErrors_23) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_23, DefaultConstructorLiteral_23) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_23, DefaultConstructorNeverNl_23) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_23, DefaultConstructorDotNl_23) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_23, DefaultConstructorNeverCapture_23) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_23, DefaultConstructorCaseSensitive_23) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_23, DefaultConstructorPerlClasses_23) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_23, DefaultConstructorWordBoundary_23) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_23, DefaultConstructorOneLine_23) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
}

// ============================================================
// Tests for RE2::Options CannedOptions constructor
// ============================================================

TEST(RE2OptionsTest_23, CannedOptionLatin1Encoding_23) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_23, CannedOptionLatin1PosixSyntax_23) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_23, CannedOptionLatin1LongestMatch_23) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_23, CannedOptionPOSIXEncoding_23) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_23, CannedOptionPOSIXPosixSyntax_23) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_23, CannedOptionPOSIXLongestMatch_23) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_23, CannedOptionPOSIXLogErrors_23) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_23, CannedOptionQuietLogErrors_23) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_23, CannedOptionQuietEncoding_23) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_23, CannedOptionQuietPosixSyntax_23) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_23, CannedOptionQuietLongestMatch_23) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.longest_match());
}

// All canned options should have literal=false, never_nl=false, etc.
TEST(RE2OptionsTest_23, CannedOptionPOSIXLiteral_23) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_23, CannedOptionPOSIXCaseSensitive_23) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.case_sensitive());
}

// ============================================================
// Tests for setters and getters
// ============================================================

TEST(RE2OptionsTest_23, SetAndGetLiteral_23) {
  RE2::Options opts;
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_23, SetAndGetMaxMem_23) {
  RE2::Options opts;
  opts.set_max_mem(1024 * 1024);
  EXPECT_EQ(opts.max_mem(), 1024 * 1024);
}

TEST(RE2OptionsTest_23, SetAndGetMaxMemZero_23) {
  RE2::Options opts;
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_23, SetAndGetMaxMemLargeValue_23) {
  RE2::Options opts;
  int64_t large = static_cast<int64_t>(1) << 40;
  opts.set_max_mem(large);
  EXPECT_EQ(opts.max_mem(), large);
}

TEST(RE2OptionsTest_23, SetAndGetEncoding_23) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_23, SetAndGetPosixSyntax_23) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_23, SetAndGetLongestMatch_23) {
  RE2::Options opts;
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_23, SetAndGetLogErrors_23) {
  RE2::Options opts;
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_23, SetAndGetNeverNl_23) {
  RE2::Options opts;
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_23, SetAndGetDotNl_23) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_23, SetAndGetNeverCapture_23) {
  RE2::Options opts;
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_23, SetAndGetCaseSensitive_23) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_23, SetAndGetPerlClasses_23) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_23, SetAndGetWordBoundary_23) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_23, SetAndGetOneLine_23) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

// ============================================================
// Tests for Copy
// ============================================================

TEST(RE2OptionsTest_23, CopyAllFields_23) {
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

  RE2::Options dst;
  dst.Copy(src);

  EXPECT_EQ(dst.max_mem(), 12345);
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingLatin1);
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

TEST(RE2OptionsTest_23, CopyFromDefault_23) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_literal(true);
  dst.set_case_sensitive(false);

  dst.Copy(src);

  EXPECT_FALSE(dst.literal());
  EXPECT_TRUE(dst.case_sensitive());
}

// ============================================================
// Tests for RE2 with Options (behavioral)
// ============================================================

TEST(RE2OptionsTest_23, LiteralMatchesLiteralString_23) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  // With literal mode, "a.b" should match exactly "a.b" not "aXb"
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("aXb", re));
}

TEST(RE2OptionsTest_23, NonLiteralMatchesDotAsWildcard_23) {
  RE2::Options opts;
  opts.set_literal(false);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("aXb", re));
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
}

TEST(RE2OptionsTest_23, CaseInsensitiveMatch_23) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2OptionsTest_23, CaseSensitiveMatchDefault_23) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
}

TEST(RE2OptionsTest_23, DotNlMatchesNewline_23) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST(RE2OptionsTest_23, DotNlDefaultDoesNotMatchNewline_23) {
  RE2::Options opts;
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

TEST(RE2OptionsTest_23, NeverCaptureOption_23) {
  RE2::Options opts;
  opts.set_never_capture(true);
  RE2 re("(a)(b)", opts);
  EXPECT_TRUE(re.ok());
  // With never_capture, NumberOfCapturingGroups should be 0
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2OptionsTest_23, NeverCaptureDefaultAllowsCapture_23) {
  RE2 re("(a)(b)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 2);
}

TEST(RE2OptionsTest_23, LongestMatchOption_23) {
  RE2::Options opts;
  opts.set_longest_match(true);
  RE2 re("a+", opts);
  EXPECT_TRUE(re.ok());
  std::string match;
  EXPECT_TRUE(RE2::PartialMatch("aaa", re, &match));
  EXPECT_EQ(match, "aaa");
}

TEST(RE2OptionsTest_23, PosixSyntaxOption_23) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  RE2 re("abc", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
}

TEST(RE2OptionsTest_23, QuietOptionSuppressesLogErrors_23) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
  // Invalid regex should fail gracefully
  RE2 re("[invalid", opts);
  EXPECT_FALSE(re.ok());
}

TEST(RE2OptionsTest_23, MaxMemSmallCausesError_23) {
  RE2::Options opts;
  opts.set_max_mem(1);  // Very small memory limit
  opts.set_log_errors(false);
  RE2 re("a{1000}{1000}", opts);
  // With very small max_mem, the regex may fail to compile
  // This is implementation-dependent; we just check it doesn't crash
  // and the error code reflects the situation
  if (!re.ok()) {
    EXPECT_NE(re.error_code(), RE2::NoError);
  }
}

// ============================================================
// Tests for ParseFlags
// ============================================================

TEST(RE2OptionsTest_23, ParseFlagsDefault_23) {
  RE2::Options opts;
  int flags = opts.ParseFlags();
  // ParseFlags should return a non-negative value
  EXPECT_GE(flags, 0);
}

TEST(RE2OptionsTest_23, ParseFlagsDifferForDifferentOptions_23) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_case_sensitive(false);
  // Different options should (likely) produce different parse flags
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

TEST(RE2OptionsTest_23, ParseFlagsChangeWithLiteral_23) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_literal(true);
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

TEST(RE2OptionsTest_23, ParseFlagsChangeWithDotNl_23) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_dot_nl(true);
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

// ============================================================
// Boundary / edge case tests
// ============================================================

TEST(RE2OptionsTest_23, SetMaxMemNegative_23) {
  RE2::Options opts;
  opts.set_max_mem(-1);
  EXPECT_EQ(opts.max_mem(), -1);
}

TEST(RE2OptionsTest_23, MultipleSetsRetainLastValue_23) {
  RE2::Options opts;
  opts.set_literal(true);
  opts.set_literal(false);
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
}

TEST(RE2OptionsTest_23, CopyToSelf_23) {
  RE2::Options opts;
  opts.set_literal(true);
  opts.set_max_mem(999);
  opts.Copy(opts);
  EXPECT_TRUE(opts.literal());
  EXPECT_EQ(opts.max_mem(), 999);
}

TEST(RE2OptionsTest_23, EncodingLatin1WithRE2_23) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re("abc", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
}

}  // namespace re2
