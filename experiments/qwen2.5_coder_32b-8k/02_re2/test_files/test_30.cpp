#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_30 : public ::testing::Test {

protected:

    RE2::Options options;

};



TEST_F(RE2OptionsTest_30, DefaultCaseSensitiveIsTrue_30) {

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_30, SetCaseSensitiveFalseWorks_30) {

    options.set_case_sensitive(false);

    EXPECT_FALSE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_30, SetCaseSensitiveTrueWorks_30) {

    options.set_case_sensitive(true);

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_30, DefaultMaxMemIsValid_30) {

    EXPECT_GT(options.max_mem(), 0);

}



TEST_F(RE2OptionsTest_30, SetMaxMemUpdatesValue_30) {

    int64_t new_max_mem = 1024;

    options.set_max_mem(new_max_mem);

    EXPECT_EQ(options.max_mem(), new_max_mem);

}



TEST_F(RE2OptionsTest_30, DefaultEncodingIsUTF8_30) {

    EXPECT_EQ(options.encoding(), RE2::EncodingUTF8);

}



TEST_F(RE2OptionsTest_30, SetEncodingUpdatesValue_30) {

    options.set_encoding(RE2::EncodingLatin1);

    EXPECT_EQ(options.encoding(), RE2::EncodingLatin1);

}



TEST_F(RE2OptionsTest_30, DefaultPosixSyntaxIsFalse_30) {

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_30, SetPosixSyntaxUpdatesValue_30) {

    options.set_posix_syntax(true);

    EXPECT_TRUE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_30, DefaultLongestMatchIsFalse_30) {

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_30, SetLongestMatchUpdatesValue_30) {

    options.set_longest_match(true);

    EXPECT_TRUE(options.longest_match());

}



TEST_F(RE2OptionsTest_30, DefaultLogErrorsIsTrue_30) {

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_30, SetLogErrorsUpdatesValue_30) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_30, DefaultLiteralIsFalse_30) {

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_30, SetLiteralUpdatesValue_30) {

    options.set_literal(true);

    EXPECT_TRUE(options.literal());

}



TEST_F(RE2OptionsTest_30, DefaultNeverNLIsFalse_30) {

    EXPECT_FALSE(options.never_nl());

}



TEST_F(RE2OptionsTest_30, SetNeverNLUpdatesValue_30) {

    options.set_never_nl(true);

    EXPECT_TRUE(options.never_nl());

}



TEST_F(RE2OptionsTest_30, DefaultDotNLIsFalse_30) {

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_30, SetDotNLUpdatesValue_30) {

    options.set_dot_nl(true);

    EXPECT_TRUE(options.dot_nl());

}



TEST_F(RE2OptionsTest_30, DefaultNeverCaptureIsFalse_30) {

    EXPECT_FALSE(options.never_capture());

}



TEST_F(RE2OptionsTest_30, SetNeverCaptureUpdatesValue_30) {

    options.set_never_capture(true);

    EXPECT_TRUE(options.never_capture());

}



TEST_F(RE2OptionsTest_30, DefaultPerlClassesIsFalse_30) {

    EXPECT_FALSE(options.perl_classes());

}



TEST_F(RE2OptionsTest_30, SetPerlClassesUpdatesValue_30) {

    options.set_perl_classes(true);

    EXPECT_TRUE(options.perl_classes());

}



TEST_F(RE2OptionsTest_30, DefaultWordBoundaryIsFalse_30) {

    EXPECT_FALSE(options.word_boundary());

}



TEST_F(RE2OptionsTest_30, SetWordBoundaryUpdatesValue_30) {

    options.set_word_boundary(true);

    EXPECT_TRUE(options.word_boundary());

}



TEST_F(RE2OptionsTest_30, DefaultOneLineIsFalse_30) {

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_30, SetOneLineUpdatesValue_30) {

    options.set_one_line(true);

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_30, CopyPreservesValues_30) {

    RE2::Options original;

    original.set_case_sensitive(false);

    original.set_max_mem(1024);

    original.set_encoding(RE2::EncodingLatin1);

    original.set_posix_syntax(true);

    original.set_longest_match(true);

    original.set_log_errors(false);

    original.set_literal(true);

    original.set_never_nl(true);

    original.set_dot_nl(true);

    original.set_never_capture(true);

    original.set_perl_classes(true);

    original.set_word_boundary(true);

    original.set_one_line(true);



    RE2::Options copy;

    copy.Copy(original);



    EXPECT_EQ(copy.case_sensitive(), original.case_sensitive());

    EXPECT_EQ(copy.max_mem(), original.max_mem());

    EXPECT_EQ(copy.encoding(), original.encoding());

    EXPECT_EQ(copy.posix_syntax(), original.posix_syntax());

    EXPECT_EQ(copy.longest_match(), original.longest_match());

    EXPECT_EQ(copy.log_errors(), original.log_errors());

    EXPECT_EQ(copy.literal(), original.literal());

    EXPECT_EQ(copy.never_nl(), original.never_nl());

    EXPECT_EQ(copy.dot_nl(), original.dot_nl());

    EXPECT_EQ(copy.never_capture(), original.never_capture());

    EXPECT_EQ(copy.perl_classes(), original.perl_classes());

    EXPECT_EQ(copy.word_boundary(), original.word_boundary());

    EXPECT_EQ(copy.one_line(), original.one_line());

}
