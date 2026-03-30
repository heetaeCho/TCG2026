#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_31 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(RE2OptionsTest_31, DefaultCaseSensitiveTrue_31) {

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_31, SetCaseSensitiveFalse_31) {

    options.set_case_sensitive(false);

    EXPECT_FALSE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_31, SetCaseSensitiveTrue_31) {

    options.set_case_sensitive(false); // First set to false

    options.set_case_sensitive(true);

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_31, DefaultMaxMemValue_31) {

    EXPECT_EQ(options.max_mem(), kDefaultMaxMem);

}



TEST_F(RE2OptionsTest_31, SetMaxMemBoundaryConditionMin_31) {

    options.set_max_mem(0);

    EXPECT_EQ(options.max_mem(), 0);

}



TEST_F(RE2OptionsTest_31, SetMaxMemBoundaryConditionMax_31) {

    int64_t max_value = std::numeric_limits<int64_t>::max();

    options.set_max_mem(max_value);

    EXPECT_EQ(options.max_mem(), max_value);

}



TEST_F(RE2OptionsTest_31, DefaultEncodingUTF8_31) {

    EXPECT_EQ(options.encoding(), EncodingUTF8);

}



TEST_F(RE2OptionsTest_31, SetEncodingLatin1_31) {

    options.set_encoding(EncodingLatin1);

    EXPECT_EQ(options.encoding(), EncodingLatin1);

}



TEST_F(RE2OptionsTest_31, DefaultPosixSyntaxFalse_31) {

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_31, SetPosixSyntaxTrue_31) {

    options.set_posix_syntax(true);

    EXPECT_TRUE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_31, DefaultLongestMatchFalse_31) {

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_31, SetLongestMatchTrue_31) {

    options.set_longest_match(true);

    EXPECT_TRUE(options.longest_match());

}



TEST_F(RE2OptionsTest_31, DefaultLogErrorsTrue_31) {

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_31, SetLogErrorsFalse_31) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_31, DefaultLiteralFalse_31) {

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_31, SetLiteralTrue_31) {

    options.set_literal(true);

    EXPECT_TRUE(options.literal());

}



TEST_F(RE2OptionsTest_31, DefaultNeverNlFalse_31) {

    EXPECT_FALSE(options.never_nl());

}



TEST_F(RE2OptionsTest_31, SetNeverNlTrue_31) {

    options.set_never_nl(true);

    EXPECT_TRUE(options.never_nl());

}



TEST_F(RE2OptionsTest_31, DefaultDotNlFalse_31) {

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_31, SetDotNlTrue_31) {

    options.set_dot_nl(true);

    EXPECT_TRUE(options.dot_nl());

}



TEST_F(RE2OptionsTest_31, DefaultNeverCaptureFalse_31) {

    EXPECT_FALSE(options.never_capture());

}



TEST_F(RE2OptionsTest_31, SetNeverCaptureTrue_31) {

    options.set_never_capture(true);

    EXPECT_TRUE(options.never_capture());

}



TEST_F(RE2OptionsTest_31, DefaultPerlClassesFalse_31) {

    EXPECT_FALSE(options.perl_classes());

}



TEST_F(RE2OptionsTest_31, SetPerlClassesTrue_31) {

    options.set_perl_classes(true);

    EXPECT_TRUE(options.perl_classes());

}



TEST_F(RE2OptionsTest_31, DefaultWordBoundaryFalse_31) {

    EXPECT_FALSE(options.word_boundary());

}



TEST_F(RE2OptionsTest_31, SetWordBoundaryTrue_31) {

    options.set_word_boundary(true);

    EXPECT_TRUE(options.word_boundary());

}



TEST_F(RE2OptionsTest_31, DefaultOneLineFalse_31) {

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_31, SetOneLineTrue_31) {

    options.set_one_line(true);

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_31, CopyConstructorPreservesValues_31) {

    Options original;

    original.set_case_sensitive(false);

    original.set_max_mem(1024);

    original.set_encoding(EncodingLatin1);

    original.set_posix_syntax(true);



    Options copy;

    copy.Copy(original);



    EXPECT_EQ(copy.case_sensitive(), original.case_sensitive());

    EXPECT_EQ(copy.max_mem(), original.max_mem());

    EXPECT_EQ(copy.encoding(), original.encoding());

    EXPECT_EQ(copy.posix_syntax(), original.posix_syntax());

}
