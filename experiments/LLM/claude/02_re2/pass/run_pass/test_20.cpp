#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>

namespace re2 {

// =============================================================================
// Options Default Constructor Tests
// =============================================================================

TEST(RE2OptionsTest_20, DefaultConstructorLogErrors_20) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_20, DefaultConstructorEncoding_20) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_20, DefaultConstructorPosixSyntax_20) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_20, DefaultConstructorLongestMatch_20) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_20, DefaultConstructorLiteral_20) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_20, DefaultConstructorNeverNl_20) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_20, DefaultConstructorDotNl_20) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_20, DefaultConstructorNeverCapture_20) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_20, DefaultConstructorCaseSensitive_20) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_20, DefaultConstructorPerlClasses_20) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_20, DefaultConstructorWordBoundary_20) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_20, DefaultConstructorOneLine_20) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
}

// =============================================================================
// Options CannedOptions Constructor Tests
// =============================================================================

TEST(RE2OptionsTest_20, CannedOptionLatin1Encoding_20) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_20, CannedOptionLatin1LogErrors_20) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_20, CannedOptionLatin1PosixSyntax_20) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_20, CannedOptionLatin1LongestMatch_20) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_20, CannedOptionPOSIXPosixSyntax_20) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_20, CannedOptionPOSIXLongestMatch_20) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_20, CannedOptionPOSIXLogErrors_20) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_20, CannedOptionPOSIXEncodingUTF8_20) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_20, CannedOptionQuietLogErrors_20) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_20, CannedOptionQuietPosixSyntax_20) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_20, CannedOptionQuietLongestMatch_20) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.longest_match());
}

// =============================================================================
// Setter/Getter Tests
// =============================================================================

TEST(RE2OptionsTest_20, SetAndGetMaxMem_20) {
  RE2::Options opts;
  opts.set_max_mem(1024 * 1024);
  EXPECT_EQ(opts.max_mem(), 1024 * 1024);
}

TEST(RE2OptionsTest_20, SetAndGetEncoding_20) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_20, SetAndGetPosixSyntax_20) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_20, SetAndGetLongestMatch_20) {
  RE2::Options opts;
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_20, SetAndGetLogErrors_20) {
  RE2::Options opts;
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_20, SetAndGetLiteral_20) {
  RE2::Options opts;
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_20, SetAndGetNeverNl_20) {
  RE2::Options opts;
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_20, SetAndGetDotNl_20) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_20, SetAndGetNeverCapture_20) {
  RE2::Options opts;
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_20, SetAndGetCaseSensitive_20) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_20, SetAndGetPerlClasses_20) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_20, SetAndGetWordBoundary_20) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_20, SetAndGetOneLine_20) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

// =============================================================================
// Copy Tests
// =============================================================================

TEST(RE2OptionsTest_20, CopyAllOptions_20) {
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

  RE2::Options dst;
  dst.Copy(src);

  EXPECT_EQ(dst.max_mem(), 2048);
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

TEST(RE2OptionsTest_20, CopyDefaultOptions_20) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_log_errors(false);
  dst.set_literal(true);

  dst.Copy(src);

  EXPECT_TRUE(dst.log_errors());
  EXPECT_FALSE(dst.literal());
}

// =============================================================================
// Boundary Tests for max_mem
// =============================================================================

TEST(RE2OptionsTest_20, SetMaxMemZero_20) {
  RE2::Options opts;
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_20, SetMaxMemLargeValue_20) {
  RE2::Options opts;
  int64_t large_val = static_cast<int64_t>(1) << 40;  // 1 TB
  opts.set_max_mem(large_val);
  EXPECT_EQ(opts.max_mem(), large_val);
}

TEST(RE2OptionsTest_20, DefaultMaxMemIsPositive_20) {
  RE2::Options opts;
  EXPECT_GT(opts.max_mem(), 0);
}

// =============================================================================
// RE2 Basic Usage Tests (using Options)
// =============================================================================

TEST(RE2BasicTest_20, SimpleMatchWithDefaultOptions_20) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

TEST(RE2BasicTest_20, SimpleMatchWithQuietOption_20) {
  RE2 re("hello", RE2::Quiet);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2BasicTest_20, InvalidPatternWithQuietOption_20) {
  RE2 re("(invalid[", RE2::Quiet);
  EXPECT_FALSE(re.ok());
}

TEST(RE2BasicTest_20, PartialMatchBasic_20) {
  RE2 re("world");
  EXPECT_TRUE(RE2::PartialMatch("hello world", re));
  EXPECT_FALSE(RE2::PartialMatch("hello earth", re));
}

TEST(RE2BasicTest_20, FullMatchWithCapture_20) {
  std::string captured;
  EXPECT_TRUE(RE2::FullMatch("hello123", "(\\w+)", &captured));
  EXPECT_EQ(captured, "hello123");
}

TEST(RE2BasicTest_20, PartialMatchWithCapture_20) {
  int value;
  EXPECT_TRUE(RE2::PartialMatch("age: 42", "(\\d+)", &value));
  EXPECT_EQ(value, 42);
}

TEST(RE2BasicTest_20, LiteralOption_20) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("aXb", re));
}

TEST(RE2BasicTest_20, CaseInsensitiveOption_20) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2BasicTest_20, DotNlOption_20) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST(RE2BasicTest_20, DotNlDefaultDoesNotMatchNewline_20) {
  RE2 re("a.b");
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

TEST(RE2BasicTest_20, NeverCaptureOption_20) {
  RE2::Options opts;
  opts.set_never_capture(true);
  RE2 re("(\\d+)-(\\d+)", opts);
  EXPECT_TRUE(re.ok());
  // With never_capture, groups become non-capturing
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2BasicTest_20, POSIXLongestMatch_20) {
  RE2::Options opts(RE2::POSIX);
  RE2 re("a*", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(opts.longest_match());
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2BasicTest_20, PatternAndError_20) {
  RE2 re("abc");
  EXPECT_EQ(re.pattern(), "abc");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.error(), "");
}

TEST(RE2BasicTest_20, InvalidPatternError_20) {
  RE2 re("(abc", RE2::Quiet);
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2BasicTest_20, NumberOfCapturingGroups_20) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2BasicTest_20, ZeroCapturingGroups_20) {
  RE2 re("abc");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2BasicTest_20, EmptyPattern_20) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
}

TEST(RE2BasicTest_20, Latin1EncodingOption_20) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
  RE2 re("abc", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
}

// =============================================================================
// RE2 Replace Tests
// =============================================================================

TEST(RE2ReplaceTest_20, ReplaceFirst_20) {
  std::string s = "hello world hello";
  EXPECT_TRUE(RE2::Replace(&s, "hello", "hi"));
  EXPECT_EQ(s, "hi world hello");
}

TEST(RE2ReplaceTest_20, GlobalReplace_20) {
  std::string s = "hello world hello";
  int count = RE2::GlobalReplace(&s, "hello", "hi");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(s, "hi world hi");
}

TEST(RE2ReplaceTest_20, ReplaceNoMatch_20) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ(s, "hello world");
}

TEST(RE2ReplaceTest_20, GlobalReplaceNoMatch_20) {
  std::string s = "hello world";
  int count = RE2::GlobalReplace(&s, "xyz", "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello world");
}

}  // namespace re2
