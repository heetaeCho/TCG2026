#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_16 : public ::testing::Test {

protected:

    RE2::Options options;

};



TEST_F(RE2OptionsTest_16, DefaultPosixSyntaxIsFalse_16) {

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_16, SetPosixSyntaxTrueAndGetPosixSyntaxReturnsTrue_16) {

    options.set_posix_syntax(true);

    EXPECT_TRUE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_16, SetPosixSyntaxFalseAndGetPosixSyntaxReturnsFalse_16) {

    options.set_posix_syntax(false);

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_16, DefaultMaxMemIsCorrect_16) {

    EXPECT_EQ(options.max_mem(), RE2::Options::kDefaultMaxMem);

}



TEST_F(RE2OptionsTest_16, SetMaxMemAndGetMaxMemReturnsSetValue_16) {

    int64_t new_max_mem = 1024 * 1024;

    options.set_max_mem(new_max_mem);

    EXPECT_EQ(options.max_mem(), new_max_mem);

}



TEST_F(RE2OptionsTest_16, DefaultEncodingIsUTF8_16) {

    EXPECT_EQ(options.encoding(), RE2::EncodingUTF8);

}



TEST_F(RE2OptionsTest_16, SetEncodingAndGetEncodingReturnsSetValue_16) {

    options.set_encoding(RE2::EncodingLatin1);

    EXPECT_EQ(options.encoding(), RE2::EncodingLatin1);

}



TEST_F(RE2OptionsTest_16, DefaultLongestMatchIsFalse_16) {

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_16, SetLongestMatchTrueAndGetLongestMatchReturnsTrue_16) {

    options.set_longest_match(true);

    EXPECT_TRUE(options.longest_match());

}



TEST_F(RE2OptionsTest_16, SetLongestMatchFalseAndGetLongestMatchReturnsFalse_16) {

    options.set_longest_match(false);

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_16, DefaultLogErrorsIsTrue_16) {

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_16, SetLogErrorsTrueAndGetLogErrorsReturnsTrue_16) {

    options.set_log_errors(true);

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_16, SetLogErrorsFalseAndGetLogErrorsReturnsFalse_16) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_16, DefaultLiteralIsFalse_16) {

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_16, SetLiteralTrueAndGetLiteralReturnsTrue_16) {

    options.set_literal(true);

    EXPECT_TRUE(options.literal());

}



TEST_F(RE2OptionsTest_16, SetLiteralFalseAndGetLiteralReturnsFalse_16) {

    options.set_literal(false);

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_16, DefaultNeverNLIsFalse_16) {

    EXPECT_FALSE(options.never_nl());

}



TEST_F(RE2OptionsTest_16, SetNeverNLTrueAndGetNeverNLReturnsTrue_16) {

    options.set_never_nl(true);

    EXPECT_TRUE(options.never_nl());

}



TEST_F(RE2OptionsTest_16, SetNeverNLFalseAndGetNeverNLReturnsFalse_16) {

    options.set_never_nl(false);

    EXPECT_FALSE(options.never_nl());

}



TEST_F(RE2OptionsTest_16, DefaultDotNLIsFalse_16) {

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_16, SetDotNLTrueAndGetDotNLReturnsTrue_16) {

    options.set_dot_nl(true);

    EXPECT_TRUE(options.dot_nl());

}



TEST_F(RE2OptionsTest_16, SetDotNLFalseAndGetDotNLReturnsFalse_16) {

    options.set_dot_nl(false);

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_16, DefaultNeverCaptureIsFalse_16) {

    EXPECT_FALSE(options.never_capture());

}



TEST_F(RE2OptionsTest_16, SetNeverCaptureTrueAndGetNeverCaptureReturnsTrue_16) {

    options.set_never_capture(true);

    EXPECT_TRUE(options.never_capture());

}



TEST_F(RE2OptionsTest_16, SetNeverCaptureFalseAndGetNeverCaptureReturnsFalse_16) {

    options.set_never_capture(false);

    EXPECT_FALSE(options.never_capture());

}



TEST_F(RE2OptionsTest_16, DefaultCaseSensitiveIsTrue_16) {

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_16, SetCaseSensitiveTrueAndGetCaseSensitiveReturnsTrue_16) {

    options.set_case_sensitive(true);

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_16, SetCaseSensitiveFalseAndGetCaseSensitiveReturnsFalse_16) {

    options.set_case_sensitive(false);

    EXPECT_FALSE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_16, DefaultPerlClassesIsFalse_16) {

    EXPECT_FALSE(options.perl_classes());

}



TEST_F(RE2OptionsTest_16, SetPerlClassesTrueAndGetPerlClassesReturnsTrue_16) {

    options.set_perl_classes(true);

    EXPECT_TRUE(options.perl_classes());

}



TEST_F(RE2OptionsTest_16, SetPerlClassesFalseAndGetPerlClassesReturnsFalse_16) {

    options.set_perl_classes(false);

    EXPECT_FALSE(options.perl_classes());

}



TEST_F(RE2OptionsTest_16, DefaultWordBoundaryIsFalse_16) {

    EXPECT_FALSE(options.word_boundary());

}



TEST_F(RE2OptionsTest_16, SetWordBoundaryTrueAndGetWordBoundaryReturnsTrue_16) {

    options.set_word_boundary(true);

    EXPECT_TRUE(options.word_boundary());

}



TEST_F(RE2OptionsTest_16, SetWordBoundaryFalseAndGetWordBoundaryReturnsFalse_16) {

    options.set_word_boundary(false);

    EXPECT_FALSE(options.word_boundary());

}



TEST_F(RE2OptionsTest_16, DefaultOneLineIsFalse_16) {

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_16, SetOneLineTrueAndGetOneLineReturnsTrue_16) {

    options.set_one_line(true);

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_16, SetOneLineFalseAndGetOneLineReturnsFalse_16) {

    options.set_one_line(false);

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_16, CopyFromAnotherOptionsObjectPreservesValues_16) {

    RE2::Options other_options;

    other_options.set_posix_syntax(true);

    other_options.set_max_mem(4096);

    other_options.set_encoding(RE2::EncodingLatin1);

    other_options.set_longest_match(true);

    other_options.set_log_errors(false);

    other_options.set_literal(true);

    other_options.set_never_nl(true);

    other_options.set_dot_nl(true);

    other_options.set_never_capture(true);

    other_options.set_case_sensitive(false);

    other_options.set_perl_classes(true);

    other_options.set_word_boundary(true);

    other_options.set_one_line(true);



    options.Copy(other_options);



    EXPECT_EQ(options.posix_syntax(), other_options.posix_syntax());

    EXPECT_EQ(options.max_mem(), other_options.max_mem());

    EXPECT_EQ(options.encoding(), other_options.encoding());

    EXPECT_EQ(options.longest_match(), other_options.longest_match());

    EXPECT_EQ(options.log_errors(), other_options.log_errors());

    EXPECT_EQ(options.literal(), other_options.literal());

    EXPECT_EQ(options.never_nl(), other_options.never_nl());

    EXPECT_EQ(options.dot_nl(), other_options.dot_nl());

    EXPECT_EQ(options.never_capture(), other_options.never_capture());

    EXPECT_EQ(options.case_sensitive(), other_options.case_sensitive());

    EXPECT_EQ(options.perl_classes(), other_options.perl_classes());

    EXPECT_EQ(options.word_boundary(), other_options.word_boundary());

    EXPECT_EQ(options.one_line(), other_options.one_line());

}



TEST_F(RE2OptionsTest_16, ParseFlagsReturnsExpectedValueForDefaultOptions_16) {

    int expected_flags = RE2::Unanchored;

    EXPECT_EQ(options.ParseFlags(), expected_flags);

}



TEST_F(RE2OptionsTest_16, ParseFlagsReturnsExpectedValueWithModifiedOptions_16) {

    options.set_posix_syntax(true);

    options.set_longest_match(true);

    options.set_log_errors(false);

    options.set_literal(true);

    options.set_never_nl(true);

    options.set_dot_nl(true);

    options.set_never_capture(true);

    options.set_case_sensitive(false);

    options.set_perl_classes(true);

    options.set_word_boundary(true);

    options.set_one_line(true);



    int expected_flags = RE2::POSIX | RE2::LongestMatch | RE2::Quiet | RE2::Literal | RE2::NeverNL | RE2::DotNL | 

                        RE2::NeverCapture | RE2::CaseInsensitive | RE2::PerlClasses | RE2::WordBoundary | RE2::OneLine;

    EXPECT_EQ(options.ParseFlags(), expected_flags);

}
