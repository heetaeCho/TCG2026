#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_32 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(RE2OptionsTest_32, DefaultConstructorInitializesPerlClassesFalse_32) {

    EXPECT_FALSE(options.perl_classes());

}



TEST_F(RE2OptionsTest_32, SetPerlClassesReflectsInGetter_32) {

    options.set_perl_classes(true);

    EXPECT_TRUE(options.perl_classes());



    options.set_perl_classes(false);

    EXPECT_FALSE(options.perl_classes());

}



TEST_F(RE2OptionsTest_32, DefaultConstructorInitializesMaxMemToDefault_32) {

    // Assuming kDefaultMaxMem is a known constant value

    const int64_t kDefaultMaxMem = 8 << 20; // Example default value

    EXPECT_EQ(options.max_mem(), kDefaultMaxMem);

}



TEST_F(RE2OptionsTest_32, SetMaxMemReflectsInGetter_32) {

    int64_t new_max_mem = 1024;

    options.set_max_mem(new_max_mem);

    EXPECT_EQ(options.max_mem(), new_max_mem);

}



TEST_F(RE2OptionsTest_32, DefaultConstructorInitializesPosixSyntaxFalse_32) {

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_32, SetPosixSyntaxReflectsInGetter_32) {

    options.set_posix_syntax(true);

    EXPECT_TRUE(options.posix_syntax());



    options.set_posix_syntax(false);

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_32, DefaultConstructorInitializesLongestMatchFalse_32) {

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_32, SetLongestMatchReflectsInGetter_32) {

    options.set_longest_match(true);

    EXPECT_TRUE(options.longest_match());



    options.set_longest_match(false);

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_32, DefaultConstructorInitializesLogErrorsTrue_32) {

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_32, SetLogErrorsReflectsInGetter_32) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());



    options.set_log_errors(true);

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_32, DefaultConstructorInitializesLiteralFalse_32) {

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_32, SetLiteralReflectsInGetter_32) {

    options.set_literal(true);

    EXPECT_TRUE(options.literal());



    options.set_literal(false);

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_32, DefaultConstructorInitializesNeverNlFalse_32) {

    EXPECT_FALSE(options.never_nl());

}



TEST_F(RE2OptionsTest_32, SetNeverNlReflectsInGetter_32) {

    options.set_never_nl(true);

    EXPECT_TRUE(options.never_nl());



    options.set_never_nl(false);

    EXPECT_FALSE(options.never_nl());

}



TEST_F(RE2OptionsTest_32, DefaultConstructorInitializesDotNlFalse_32) {

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_32, SetDotNlReflectsInGetter_32) {

    options.set_dot_nl(true);

    EXPECT_TRUE(options.dot_nl());



    options.set_dot_nl(false);

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_32, DefaultConstructorInitializesNeverCaptureFalse_32) {

    EXPECT_FALSE(options.never_capture());

}



TEST_F(RE2OptionsTest_32, SetNeverCaptureReflectsInGetter_32) {

    options.set_never_capture(true);

    EXPECT_TRUE(options.never_capture());



    options.set_never_capture(false);

    EXPECT_FALSE(options.never_capture());

}



TEST_F(RE2OptionsTest_32, DefaultConstructorInitializesCaseSensitiveTrue_32) {

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_32, SetCaseSensitiveReflectsInGetter_32) {

    options.set_case_sensitive(false);

    EXPECT_FALSE(options.case_sensitive());



    options.set_case_sensitive(true);

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_32, DefaultConstructorInitializesWordBoundaryFalse_32) {

    EXPECT_FALSE(options.word_boundary());

}



TEST_F(RE2OptionsTest_32, SetWordBoundaryReflectsInGetter_32) {

    options.set_word_boundary(true);

    EXPECT_TRUE(options.word_boundary());



    options.set_word_boundary(false);

    EXPECT_FALSE(options.word_boundary());

}



TEST_F(RE2OptionsTest_32, DefaultConstructorInitializesOneLineFalse_32) {

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_32, SetOneLineReflectsInGetter_32) {

    options.set_one_line(true);

    EXPECT_TRUE(options.one_line());



    options.set_one_line(false);

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_32, CopyConstructorCopiesValues_32) {

    Options original;

    original.set_perl_classes(true);

    original.set_max_mem(1024);



    Options copy = original;



    EXPECT_EQ(copy.perl_classes(), original.perl_classes());

    EXPECT_EQ(copy.max_mem(), original.max_mem());

}



TEST_F(RE2OptionsTest_32, CopyMethodCopiesValues_32) {

    Options original;

    original.set_perl_classes(true);

    original.set_max_mem(1024);



    Options copy;

    copy.Copy(original);



    EXPECT_EQ(copy.perl_classes(), original.perl_classes());

    EXPECT_EQ(copy.max_mem(), original.max_mem());

}
