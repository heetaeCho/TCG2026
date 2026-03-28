#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_28 : public ::testing::Test {

protected:

    RE2::Options options;

};



TEST_F(RE2OptionsTest_28, DefaultNeverCaptureValue_28) {

    EXPECT_FALSE(options.never_capture());

}



TEST_F(RE2OptionsTest_28, SetNeverCaptureTrue_28) {

    options.set_never_capture(true);

    EXPECT_TRUE(options.never_capture());

}



TEST_F(RE2OptionsTest_28, SetNeverCaptureFalse_28) {

    options.set_never_capture(false);

    EXPECT_FALSE(options.never_capture());

}



TEST_F(RE2OptionsTest_28, DefaultMaxMemValue_28) {

    EXPECT_EQ(options.max_mem(), RE2::kDefaultMaxMem);

}



TEST_F(RE2OptionsTest_28, SetMaxMemPositiveValue_28) {

    int64_t test_value = 1024;

    options.set_max_mem(test_value);

    EXPECT_EQ(options.max_mem(), test_value);

}



TEST_F(RE2OptionsTest_28, SetMaxMemZeroValue_28) {

    int64_t test_value = 0;

    options.set_max_mem(test_value);

    EXPECT_EQ(options.max_mem(), test_value);

}



TEST_F(RE2OptionsTest_28, DefaultPosixSyntaxValue_28) {

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_28, SetPosixSyntaxTrue_28) {

    options.set_posix_syntax(true);

    EXPECT_TRUE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_28, SetPosixSyntaxFalse_28) {

    options.set_posix_syntax(false);

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_28, DefaultLongestMatchValue_28) {

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_28, SetLongestMatchTrue_28) {

    options.set_longest_match(true);

    EXPECT_TRUE(options.longest_match());

}



TEST_F(RE2OptionsTest_28, SetLongestMatchFalse_28) {

    options.set_longest_match(false);

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_28, DefaultLogErrorsValue_28) {

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_28, SetLogErrorsTrue_28) {

    options.set_log_errors(true);

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_28, SetLogErrorsFalse_28) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_28, DefaultLiteralValue_28) {

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_28, SetLiteralTrue_28) {

    options.set_literal(true);

    EXPECT_TRUE(options.literal());

}



TEST_F(RE2OptionsTest_28, SetLiteralFalse_28) {

    options.set_literal(false);

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_28, DefaultNeverNlValue_28) {

    EXPECT_FALSE(options.never_nl());

}



TEST_F(RE2OptionsTest_28, SetNeverNlTrue_28) {

    options.set_never_nl(true);

    EXPECT_TRUE(options.never_nl());

}



TEST_F(RE2OptionsTest_28, SetNeverNlFalse_28) {

    options.set_never_nl(false);

    EXPECT_FALSE(options.never_nl());

}



TEST_F(RE2OptionsTest_28, DefaultDotNlValue_28) {

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_28, SetDotNlTrue_28) {

    options.set_dot_nl(true);

    EXPECT_TRUE(options.dot_nl());

}



TEST_F(RE2OptionsTest_28, SetDotNlFalse_28) {

    options.set_dot_nl(false);

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_28, DefaultCaseSensitiveValue_28) {

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_28, SetCaseSensitiveTrue_28) {

    options.set_case_sensitive(true);

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_28, SetCaseSensitiveFalse_28) {

    options.set_case_sensitive(false);

    EXPECT_FALSE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_28, DefaultPerlClassesValue_28) {

    EXPECT_FALSE(options.perl_classes());

}



TEST_F(RE2OptionsTest_28, SetPerlClassesTrue_28) {

    options.set_perl_classes(true);

    EXPECT_TRUE(options.perl_classes());

}



TEST_F(RE2OptionsTest_28, SetPerlClassesFalse_28) {

    options.set_perl_classes(false);

    EXPECT_FALSE(options.perl_classes());

}



TEST_F(RE2OptionsTest_28, DefaultWordBoundaryValue_28) {

    EXPECT_FALSE(options.word_boundary());

}



TEST_F(RE2OptionsTest_28, SetWordBoundaryTrue_28) {

    options.set_word_boundary(true);

    EXPECT_TRUE(options.word_boundary());

}



TEST_F(RE2OptionsTest_28, SetWordBoundaryFalse_28) {

    options.set_word_boundary(false);

    EXPECT_FALSE(options.word_boundary());

}



TEST_F(RE2OptionsTest_28, DefaultOneLineValue_28) {

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_28, SetOneLineTrue_28) {

    options.set_one_line(true);

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_28, SetOneLineFalse_28) {

    options.set_one_line(false);

    EXPECT_FALSE(options.one_line());

}
