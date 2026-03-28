#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>

namespace re2 {

// Test fixture for RE2::Options
class RE2OptionsTest_15 : public ::testing::Test {
 protected:
  RE2::Options options_;
};

// ==================== Default Constructor Tests ====================

TEST_F(RE2OptionsTest_15, DefaultConstructorMaxMem_15) {
  // Default max_mem should be kDefaultMaxMem (8<<20 = 8388608)
  EXPECT_EQ(options_.max_mem(), 8 << 20);
}

TEST_F(RE2OptionsTest_15, DefaultConstructorEncoding_15) {
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_15, DefaultConstructorPosixSyntax_15) {
  EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_15, DefaultConstructorLongestMatch_15) {
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_15, DefaultConstructorLogErrors_15) {
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_15, DefaultConstructorLiteral_15) {
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_15, DefaultConstructorNeverNl_15) {
  EXPECT_FALSE(options_.never_nl());
}

TEST_F(RE2OptionsTest_15, DefaultConstructorDotNl_15) {
  EXPECT_FALSE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_15, DefaultConstructorNeverCapture_15) {
  EXPECT_FALSE(options_.never_capture());
}

TEST_F(RE2OptionsTest_15, DefaultConstructorCaseSensitive_15) {
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_15, DefaultConstructorPerlClasses_15) {
  EXPECT_FALSE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_15, DefaultConstructorWordBoundary_15) {
  EXPECT_FALSE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_15, DefaultConstructorOneLine_15) {
  EXPECT_FALSE(options_.one_line());
}

// ==================== CannedOptions Constructor Tests ====================

TEST_F(RE2OptionsTest_15, Latin1ConstructorEncoding_15) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_15, Latin1ConstructorPosixSyntax_15) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_15, Latin1ConstructorLongestMatch_15) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.longest_match());
}

TEST_F(RE2OptionsTest_15, Latin1ConstructorLogErrors_15) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_TRUE(opts.log_errors());
}

TEST_F(RE2OptionsTest_15, POSIXConstructorEncoding_15) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_15, POSIXConstructorPosixSyntax_15) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_15, POSIXConstructorLongestMatch_15) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST_F(RE2OptionsTest_15, POSIXConstructorLogErrors_15) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.log_errors());
}

TEST_F(RE2OptionsTest_15, QuietConstructorLogErrors_15) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST_F(RE2OptionsTest_15, QuietConstructorPosixSyntax_15) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_15, QuietConstructorLongestMatch_15) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.longest_match());
}

TEST_F(RE2OptionsTest_15, QuietConstructorEncoding_15) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// ==================== Setter/Getter Tests ====================

TEST_F(RE2OptionsTest_15, SetAndGetMaxMem_15) {
  options_.set_max_mem(1024);
  EXPECT_EQ(options_.max_mem(), 1024);
}

TEST_F(RE2OptionsTest_15, SetMaxMemToZero_15) {
  options_.set_max_mem(0);
  EXPECT_EQ(options_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_15, SetMaxMemToLargeValue_15) {
  int64_t large_val = static_cast<int64_t>(1) << 40;
  options_.set_max_mem(large_val);
  EXPECT_EQ(options_.max_mem(), large_val);
}

TEST_F(RE2OptionsTest_15, SetEncodingUTF8_15) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  options_.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_15, SetEncodingLatin1_15) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_15, SetPosixSyntaxTrue_15) {
  options_.set_posix_syntax(true);
  EXPECT_TRUE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_15, SetPosixSyntaxFalse_15) {
  options_.set_posix_syntax(true);
  options_.set_posix_syntax(false);
  EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_15, SetLongestMatchTrue_15) {
  options_.set_longest_match(true);
  EXPECT_TRUE(options_.longest_match());
}

TEST_F(RE2OptionsTest_15, SetLongestMatchFalse_15) {
  options_.set_longest_match(true);
  options_.set_longest_match(false);
  EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_15, SetLogErrorsTrue_15) {
  options_.set_log_errors(false);
  options_.set_log_errors(true);
  EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_15, SetLogErrorsFalse_15) {
  options_.set_log_errors(false);
  EXPECT_FALSE(options_.log_errors());
}

TEST_F(RE2OptionsTest_15, SetLiteralTrue_15) {
  options_.set_literal(true);
  EXPECT_TRUE(options_.literal());
}

TEST_F(RE2OptionsTest_15, SetLiteralFalse_15) {
  options_.set_literal(true);
  options_.set_literal(false);
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_15, SetNeverNlTrue_15) {
  options_.set_never_nl(true);
  EXPECT_TRUE(options_.never_nl());
}

TEST_F(RE2OptionsTest_15, SetNeverNlFalse_15) {
  options_.set_never_nl(true);
  options_.set_never_nl(false);
  EXPECT_FALSE(options_.never_nl());
}

TEST_F(RE2OptionsTest_15, SetDotNlTrue_15) {
  options_.set_dot_nl(true);
  EXPECT_TRUE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_15, SetDotNlFalse_15) {
  options_.set_dot_nl(true);
  options_.set_dot_nl(false);
  EXPECT_FALSE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_15, SetNeverCaptureTrue_15) {
  options_.set_never_capture(true);
  EXPECT_TRUE(options_.never_capture());
}

TEST_F(RE2OptionsTest_15, SetNeverCaptureFalse_15) {
  options_.set_never_capture(true);
  options_.set_never_capture(false);
  EXPECT_FALSE(options_.never_capture());
}

TEST_F(RE2OptionsTest_15, SetCaseSensitiveTrue_15) {
  options_.set_case_sensitive(false);
  options_.set_case_sensitive(true);
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_15, SetCaseSensitiveFalse_15) {
  options_.set_case_sensitive(false);
  EXPECT_FALSE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_15, SetPerlClassesTrue_15) {
  options_.set_perl_classes(true);
  EXPECT_TRUE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_15, SetPerlClassesFalse_15) {
  options_.set_perl_classes(true);
  options_.set_perl_classes(false);
  EXPECT_FALSE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_15, SetWordBoundaryTrue_15) {
  options_.set_word_boundary(true);
  EXPECT_TRUE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_15, SetWordBoundaryFalse_15) {
  options_.set_word_boundary(true);
  options_.set_word_boundary(false);
  EXPECT_FALSE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_15, SetOneLineTrue_15) {
  options_.set_one_line(true);
  EXPECT_TRUE(options_.one_line());
}

TEST_F(RE2OptionsTest_15, SetOneLineFalse_15) {
  options_.set_one_line(true);
  options_.set_one_line(false);
  EXPECT_FALSE(options_.one_line());
}

// ==================== Copy Tests ====================

TEST_F(RE2OptionsTest_15, CopyAllSettings_15) {
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

TEST_F(RE2OptionsTest_15, CopyDefaultOptions_15) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_max_mem(999);
  dst.set_encoding(RE2::Options::EncodingLatin1);
  dst.set_posix_syntax(true);
  
  dst.Copy(src);

  EXPECT_EQ(dst.max_mem(), src.max_mem());
  EXPECT_EQ(dst.encoding(), src.encoding());
  EXPECT_EQ(dst.posix_syntax(), src.posix_syntax());
  EXPECT_EQ(dst.longest_match(), src.longest_match());
  EXPECT_EQ(dst.log_errors(), src.log_errors());
  EXPECT_EQ(dst.literal(), src.literal());
  EXPECT_EQ(dst.never_nl(), src.never_nl());
  EXPECT_EQ(dst.dot_nl(), src.dot_nl());
  EXPECT_EQ(dst.never_capture(), src.never_capture());
  EXPECT_EQ(dst.case_sensitive(), src.case_sensitive());
  EXPECT_EQ(dst.perl_classes(), src.perl_classes());
  EXPECT_EQ(dst.word_boundary(), src.word_boundary());
  EXPECT_EQ(dst.one_line(), src.one_line());
}

TEST_F(RE2OptionsTest_15, CopySelf_15) {
  options_.set_max_mem(4096);
  options_.set_literal(true);
  options_.Copy(options_);
  EXPECT_EQ(options_.max_mem(), 4096);
  EXPECT_TRUE(options_.literal());
}

// ==================== Multiple Sets Overwrite Previous Values ====================

TEST_F(RE2OptionsTest_15, MultipleSetMaxMemOverwrites_15) {
  options_.set_max_mem(100);
  EXPECT_EQ(options_.max_mem(), 100);
  options_.set_max_mem(200);
  EXPECT_EQ(options_.max_mem(), 200);
  options_.set_max_mem(300);
  EXPECT_EQ(options_.max_mem(), 300);
}

TEST_F(RE2OptionsTest_15, MultipleSetEncodingOverwrites_15) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingLatin1);
  options_.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(options_.encoding(), RE2::Options::EncodingUTF8);
}

// ==================== RE2 Construction with Options ====================

class RE2Test_15 : public ::testing::Test {};

TEST_F(RE2Test_15, SimpleMatch_15) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

TEST_F(RE2Test_15, ConstructWithLatin1Option_15) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST_F(RE2Test_15, ConstructWithPOSIX_15) {
  RE2 re("hello", RE2::POSIX);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST_F(RE2Test_15, ConstructWithQuiet_15) {
  RE2 re("hello", RE2::Quiet);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST_F(RE2Test_15, InvalidPattern_15) {
  RE2 re("(invalid[", RE2::Quiet);
  EXPECT_FALSE(re.ok());
}

TEST_F(RE2Test_15, LiteralOption_15) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  // With literal mode, "a.b" should match literally, not as a regex
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

TEST_F(RE2Test_15, CaseInsensitiveOption_15) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST_F(RE2Test_15, DotNlOption_15) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2Test_15, DotNlOptionFalse_15) {
  RE2::Options opts;
  opts.set_dot_nl(false);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

TEST_F(RE2Test_15, PartialMatch_15) {
  RE2 re("ell");
  EXPECT_TRUE(RE2::PartialMatch("hello", re));
  EXPECT_FALSE(RE2::PartialMatch("world", re));
}

TEST_F(RE2Test_15, EmptyPattern_15) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("notempty", re));
  EXPECT_TRUE(RE2::PartialMatch("anything", re));
}

TEST_F(RE2Test_15, PatternAccessor_15) {
  RE2 re("test_pattern");
  EXPECT_EQ(re.pattern(), "test_pattern");
}

TEST_F(RE2Test_15, ErrorAfterInvalidPattern_15) {
  RE2 re("(unclosed", RE2::Quiet);
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(re.error().empty());
}

// ==================== ParseFlags Tests ====================

TEST_F(RE2OptionsTest_15, ParseFlagsDefault_15) {
  // Just ensure ParseFlags returns without crashing with default options
  int flags = options_.ParseFlags();
  // We don't know the exact value, but it should be deterministic
  int flags2 = options_.ParseFlags();
  EXPECT_EQ(flags, flags2);
}

TEST_F(RE2OptionsTest_15, ParseFlagsChangesWithOptions_15) {
  RE2::Options opts1;
  int flags1 = opts1.ParseFlags();

  RE2::Options opts2;
  opts2.set_case_sensitive(false);
  int flags2 = opts2.ParseFlags();

  // Changing an option should (likely) change parse flags
  EXPECT_NE(flags1, flags2);
}

TEST_F(RE2OptionsTest_15, ParseFlagsChangesWithPosixSyntax_15) {
  RE2::Options opts1;
  int flags1 = opts1.ParseFlags();

  RE2::Options opts2;
  opts2.set_posix_syntax(true);
  int flags2 = opts2.ParseFlags();

  EXPECT_NE(flags1, flags2);
}

// ==================== Boundary: max_mem edge cases ====================

TEST_F(RE2OptionsTest_15, SetMaxMemNegative_15) {
  options_.set_max_mem(-1);
  EXPECT_EQ(options_.max_mem(), -1);
}

TEST_F(RE2OptionsTest_15, SetMaxMemMaxInt64_15) {
  options_.set_max_mem(INT64_MAX);
  EXPECT_EQ(options_.max_mem(), INT64_MAX);
}

}  // namespace re2
