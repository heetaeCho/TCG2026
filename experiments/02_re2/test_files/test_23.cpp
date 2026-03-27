#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_23 : public ::testing::Test {

protected:

    RE2::Options options;

};



TEST_F(RE2OptionsTest_23, DefaultLiteralIsFalse_23) {

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_23, SetLiteralToTrue_23) {

    options.set_literal(true);

    EXPECT_TRUE(options.literal());

}



TEST_F(RE2OptionsTest_23, SetLiteralToFalse_23) {

    options.set_literal(false);

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_23, DefaultMaxMemIsKDefaultMaxMem_23) {

    EXPECT_EQ(options.max_mem(), RE2::Options::kDefaultMaxMem);

}



TEST_F(RE2OptionsTest_23, SetMaxMemToCustomValue_23) {

    int64_t custom_value = 1024 * 1024;

    options.set_max_mem(custom_value);

    EXPECT_EQ(options.max_mem(), custom_value);

}



TEST_F(RE2OptionsTest_23, DefaultEncodingIsUTF8_23) {

    EXPECT_EQ(options.encoding(), RE2::Options::EncodingUTF8);

}



TEST_F(RE2OptionsTest_23, SetEncodingToLatin1_23) {

    options.set_encoding(RE2::Options::EncodingLatin1);

    EXPECT_EQ(options.encoding(), RE2::Options::EncodingLatin1);

}



TEST_F(RE2OptionsTest_23, DefaultPosixSyntaxIsFalse_23) {

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_23, SetPosixSyntaxToTrue_23) {

    options.set_posix_syntax(true);

    EXPECT_TRUE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_23, DefaultLongestMatchIsFalse_23) {

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_23, SetLongestMatchToTrue_23) {

    options.set_longest_match(true);

    EXPECT_TRUE(options.longest_match());

}



TEST_F(RE2OptionsTest_23, DefaultLogErrorsIsTrue_23) {

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_23, SetLogErrorsToFalse_23) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_23, DefaultNeverNlIsFalse_23) {

    EXPECT_FALSE(options.never_nl());

}



TEST_F(RE2OptionsTest_23, SetNeverNlToTrue_23) {

    options.set_never_nl(true);

    EXPECT_TRUE(options.never_nl());

}



TEST_F(RE2OptionsTest_23, DefaultDotNlIsFalse_23) {

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_23, SetDotNlToTrue_23) {

    options.set_dot_nl(true);

    EXPECT_TRUE(options.dot_nl());

}



TEST_F(RE2OptionsTest_23, DefaultNeverCaptureIsFalse_23) {

    EXPECT_FALSE(options.never_capture());

}



TEST_F(RE2OptionsTest_23, SetNeverCaptureToTrue_23) {

    options.set_never_capture(true);

    EXPECT_TRUE(options.never_capture());

}



TEST_F(RE2OptionsTest_23, DefaultCaseSensitiveIsTrue_23) {

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_23, SetCaseSensitiveToFalse_23) {

    options.set_case_sensitive(false);

    EXPECT_FALSE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_23, DefaultPerlClassesIsFalse_23) {

    EXPECT_FALSE(options.perl_classes());

}



TEST_F(RE2OptionsTest_23, SetPerlClassesToTrue_23) {

    options.set_perl_classes(true);

    EXPECT_TRUE(options.perl_classes());

}



TEST_F(RE2OptionsTest_23, DefaultWordBoundaryIsFalse_23) {

    EXPECT_FALSE(options.word_boundary());

}



TEST_F(RE2OptionsTest_23, SetWordBoundaryToTrue_23) {

    options.set_word_boundary(true);

    EXPECT_TRUE(options.word_boundary());

}



TEST_F(RE2OptionsTest_23, DefaultOneLineIsFalse_23) {

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_23, SetOneLineToTrue_23) {

    options.set_one_line(true);

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_23, CopyFromAnotherOptionsObject_23) {

    RE2::Options src;

    src.set_max_mem(1024);

    src.set_encoding(RE2::Options::EncodingLatin1);

    src.set_posix_syntax(true);



    options.Copy(src);



    EXPECT_EQ(options.max_mem(), 1024);

    EXPECT_EQ(options.encoding(), RE2::Options::EncodingLatin1);

    EXPECT_TRUE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_23, ParseFlagsReturnsValidInteger_23) {

    int flags = options.ParseFlags();

    EXPECT_GE(flags, 0); // Assuming ParseFlags returns a non-negative integer

}
