#include <gtest/gtest.h>
#include "re2/re2.h"

class RE2OptionsTest_53 : public ::testing::Test {
protected:
    RE2::Options options_;
};

// Test default constructor values
TEST_F(RE2OptionsTest_53, DefaultConstructorMaxMem_53) {
    RE2::Options opts;
    // Default max_mem should be kDefaultMaxMem (typically 8<<20 = 8388608)
    EXPECT_GT(opts.max_mem(), 0);
}

TEST_F(RE2OptionsTest_53, DefaultConstructorEncoding_53) {
    RE2::Options opts;
    EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_53, DefaultConstructorPosixSyntax_53) {
    RE2::Options opts;
    EXPECT_FALSE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_53, DefaultConstructorLongestMatch_53) {
    RE2::Options opts;
    EXPECT_FALSE(opts.longest_match());
}

TEST_F(RE2OptionsTest_53, DefaultConstructorLogErrors_53) {
    RE2::Options opts;
    EXPECT_TRUE(opts.log_errors());
}

TEST_F(RE2OptionsTest_53, DefaultConstructorLiteral_53) {
    RE2::Options opts;
    EXPECT_FALSE(opts.literal());
}

TEST_F(RE2OptionsTest_53, DefaultConstructorNeverNl_53) {
    RE2::Options opts;
    EXPECT_FALSE(opts.never_nl());
}

TEST_F(RE2OptionsTest_53, DefaultConstructorDotNl_53) {
    RE2::Options opts;
    EXPECT_FALSE(opts.dot_nl());
}

TEST_F(RE2OptionsTest_53, DefaultConstructorNeverCapture_53) {
    RE2::Options opts;
    EXPECT_FALSE(opts.never_capture());
}

TEST_F(RE2OptionsTest_53, DefaultConstructorCaseSensitive_53) {
    RE2::Options opts;
    EXPECT_TRUE(opts.case_sensitive());
}

TEST_F(RE2OptionsTest_53, DefaultConstructorPerlClasses_53) {
    RE2::Options opts;
    EXPECT_FALSE(opts.perl_classes());
}

TEST_F(RE2OptionsTest_53, DefaultConstructorWordBoundary_53) {
    RE2::Options opts;
    EXPECT_FALSE(opts.word_boundary());
}

TEST_F(RE2OptionsTest_53, DefaultConstructorOneLine_53) {
    RE2::Options opts;
    EXPECT_FALSE(opts.one_line());
}

// Test CannedOptions constructor - Latin1
TEST_F(RE2OptionsTest_53, Latin1ConstructorEncoding_53) {
    RE2::Options opts(RE2::Latin1);
    EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_53, Latin1ConstructorPosixSyntax_53) {
    RE2::Options opts(RE2::Latin1);
    EXPECT_FALSE(opts.posix_syntax());
}

// Test CannedOptions constructor - POSIX
TEST_F(RE2OptionsTest_53, POSIXConstructorPosixSyntax_53) {
    RE2::Options opts(RE2::POSIX);
    EXPECT_TRUE(opts.posix_syntax());
}

TEST_F(RE2OptionsTest_53, POSIXConstructorLongestMatch_53) {
    RE2::Options opts(RE2::POSIX);
    EXPECT_TRUE(opts.longest_match());
}

TEST_F(RE2OptionsTest_53, POSIXConstructorEncoding_53) {
    RE2::Options opts(RE2::POSIX);
    EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// Test CannedOptions constructor - Quiet
TEST_F(RE2OptionsTest_53, QuietConstructorLogErrors_53) {
    RE2::Options opts(RE2::Quiet);
    EXPECT_FALSE(opts.log_errors());
}

// Test setters and getters
TEST_F(RE2OptionsTest_53, SetMaxMem_53) {
    options_.set_max_mem(1024);
    EXPECT_EQ(options_.max_mem(), 1024);
}

TEST_F(RE2OptionsTest_53, SetMaxMemZero_53) {
    options_.set_max_mem(0);
    EXPECT_EQ(options_.max_mem(), 0);
}

TEST_F(RE2OptionsTest_53, SetMaxMemLargeValue_53) {
    int64_t large = static_cast<int64_t>(1) << 30;
    options_.set_max_mem(large);
    EXPECT_EQ(options_.max_mem(), large);
}

TEST_F(RE2OptionsTest_53, SetEncodingLatin1_53) {
    options_.set_encoding(RE2::Options::EncodingLatin1);
    EXPECT_EQ(options_.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_53, SetEncodingUTF8_53) {
    options_.set_encoding(RE2::Options::EncodingUTF8);
    EXPECT_EQ(options_.encoding(), RE2::Options::EncodingUTF8);
}

TEST_F(RE2OptionsTest_53, SetPosixSyntaxTrue_53) {
    options_.set_posix_syntax(true);
    EXPECT_TRUE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_53, SetPosixSyntaxFalse_53) {
    options_.set_posix_syntax(false);
    EXPECT_FALSE(options_.posix_syntax());
}

TEST_F(RE2OptionsTest_53, SetLongestMatchTrue_53) {
    options_.set_longest_match(true);
    EXPECT_TRUE(options_.longest_match());
}

TEST_F(RE2OptionsTest_53, SetLongestMatchFalse_53) {
    options_.set_longest_match(false);
    EXPECT_FALSE(options_.longest_match());
}

TEST_F(RE2OptionsTest_53, SetLogErrorsTrue_53) {
    options_.set_log_errors(true);
    EXPECT_TRUE(options_.log_errors());
}

TEST_F(RE2OptionsTest_53, SetLogErrorsFalse_53) {
    options_.set_log_errors(false);
    EXPECT_FALSE(options_.log_errors());
}

TEST_F(RE2OptionsTest_53, SetLiteralTrue_53) {
    options_.set_literal(true);
    EXPECT_TRUE(options_.literal());
}

TEST_F(RE2OptionsTest_53, SetLiteralFalse_53) {
    options_.set_literal(false);
    EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_53, SetNeverNlTrue_53) {
    options_.set_never_nl(true);
    EXPECT_TRUE(options_.never_nl());
}

TEST_F(RE2OptionsTest_53, SetDotNlTrue_53) {
    options_.set_dot_nl(true);
    EXPECT_TRUE(options_.dot_nl());
}

TEST_F(RE2OptionsTest_53, SetNeverCaptureTrue_53) {
    options_.set_never_capture(true);
    EXPECT_TRUE(options_.never_capture());
}

TEST_F(RE2OptionsTest_53, SetCaseSensitiveFalse_53) {
    options_.set_case_sensitive(false);
    EXPECT_FALSE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_53, SetPerlClassesTrue_53) {
    options_.set_perl_classes(true);
    EXPECT_TRUE(options_.perl_classes());
}

TEST_F(RE2OptionsTest_53, SetWordBoundaryTrue_53) {
    options_.set_word_boundary(true);
    EXPECT_TRUE(options_.word_boundary());
}

TEST_F(RE2OptionsTest_53, SetOneLineTrue_53) {
    options_.set_one_line(true);
    EXPECT_TRUE(options_.one_line());
}

// Test Copy
TEST_F(RE2OptionsTest_53, CopyOptions_53) {
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

// Test RE2 construction with simple patterns
class RE2ConstructionTest_53 : public ::testing::Test {};

TEST_F(RE2ConstructionTest_53, SimplePatternIsOk_53) {
    RE2 re("hello");
    EXPECT_TRUE(re.ok());
}

TEST_F(RE2ConstructionTest_53, InvalidPatternIsNotOk_53) {
    RE2::Options opts;
    opts.set_log_errors(false);
    RE2 re("[invalid", opts);
    EXPECT_FALSE(re.ok());
}

TEST_F(RE2ConstructionTest_53, EmptyPatternIsOk_53) {
    RE2 re("");
    EXPECT_TRUE(re.ok());
}

TEST_F(RE2ConstructionTest_53, PatternReturned_53) {
    RE2 re("abc.*def");
    EXPECT_EQ(re.pattern(), "abc.*def");
}

TEST_F(RE2ConstructionTest_53, ConstructWithOptions_53) {
    RE2::Options opts;
    opts.set_case_sensitive(false);
    RE2 re("Hello", opts);
    EXPECT_TRUE(re.ok());
}

TEST_F(RE2ConstructionTest_53, ConstructWithLiteral_53) {
    RE2::Options opts;
    opts.set_literal(true);
    RE2 re("a.b", opts);
    EXPECT_TRUE(re.ok());
}

TEST_F(RE2ConstructionTest_53, ComplexPatternIsOk_53) {
    RE2 re("(\\d+)-(\\w+)");
    EXPECT_TRUE(re.ok());
}

TEST_F(RE2ConstructionTest_53, ConstructWithPOSIX_53) {
    RE2::Options opts(RE2::POSIX);
    RE2 re("abc", opts);
    EXPECT_TRUE(re.ok());
}

TEST_F(RE2ConstructionTest_53, ConstructWithQuiet_53) {
    RE2::Options opts(RE2::Quiet);
    RE2 re("[bad", opts);
    EXPECT_FALSE(re.ok());
}

TEST_F(RE2ConstructionTest_53, FullMatchSimple_53) {
    RE2 re("hello");
    EXPECT_TRUE(RE2::FullMatch("hello", re));
    EXPECT_FALSE(RE2::FullMatch("hello world", re));
}

TEST_F(RE2ConstructionTest_53, PartialMatchSimple_53) {
    RE2 re("hello");
    EXPECT_TRUE(RE2::PartialMatch("say hello world", re));
    EXPECT_FALSE(RE2::PartialMatch("goodbye", re));
}

TEST_F(RE2ConstructionTest_53, OptionsParseFlags_53) {
    RE2::Options opts;
    // ParseFlags should return a valid integer
    int flags = opts.ParseFlags();
    EXPECT_GE(flags, 0);
}

TEST_F(RE2ConstructionTest_53, OptionsParsesFlagsWithPOSIX_53) {
    RE2::Options opts(RE2::POSIX);
    int flags = opts.ParseFlags();
    EXPECT_GE(flags, 0);
}

// Test toggling options multiple times
TEST_F(RE2OptionsTest_53, ToggleBooleanOptions_53) {
    options_.set_case_sensitive(false);
    EXPECT_FALSE(options_.case_sensitive());
    options_.set_case_sensitive(true);
    EXPECT_TRUE(options_.case_sensitive());
    options_.set_case_sensitive(false);
    EXPECT_FALSE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_53, SetMaxMemNegative_53) {
    options_.set_max_mem(-1);
    EXPECT_EQ(options_.max_mem(), -1);
}
