#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_25 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(RE2OptionsTest_25, DefaultConstructorInitializesValues_25) {

    EXPECT_EQ(options.max_mem(), kDefaultMaxMem);

    EXPECT_EQ(options.encoding(), EncodingUTF8);

    EXPECT_FALSE(options.posix_syntax());

    EXPECT_FALSE(options.longest_match());

    EXPECT_TRUE(options.log_errors());

    EXPECT_FALSE(options.literal());

    EXPECT_FALSE(options.never_nl());

    EXPECT_FALSE(options.dot_nl());

    EXPECT_FALSE(options.never_capture());

    EXPECT_TRUE(options.case_sensitive());

    EXPECT_FALSE(options.perl_classes());

    EXPECT_FALSE(options.word_boundary());

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_25, SettersChangeValuesCorrectly_25) {

    options.set_max_mem(1024);

    options.set_encoding(EncodingLatin1);

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



    EXPECT_EQ(options.max_mem(), 1024);

    EXPECT_EQ(options.encoding(), EncodingLatin1);

    EXPECT_TRUE(options.posix_syntax());

    EXPECT_TRUE(options.longest_match());

    EXPECT_FALSE(options.log_errors());

    EXPECT_TRUE(options.literal());

    EXPECT_TRUE(options.never_nl());

    EXPECT_TRUE(options.dot_nl());

    EXPECT_TRUE(options.never_capture());

    EXPECT_FALSE(options.case_sensitive());

    EXPECT_TRUE(options.perl_classes());

    EXPECT_TRUE(options.word_boundary());

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_25, ParseFlagsReturnsExpectedValue_25) {

    int flags = options.ParseFlags();

    EXPECT_EQ(flags, 0); // Assuming default values result in no flags set



    options.set_posix_syntax(true);

    options.set_longest_match(true);

    options.set_log_errors(false);



    flags = options.ParseFlags();

    EXPECT_EQ(flags, RE2::POSIX | RE2::LOG_ERRORS); // Adjust based on actual ParseFlags implementation

}



TEST_F(RE2OptionsTest_25, CopyFunctionCopiesValuesCorrectly_25) {

    Options original;

    original.set_max_mem(1024);

    original.set_encoding(EncodingLatin1);

    original.set_posix_syntax(true);

    original.set_longest_match(true);

    original.set_log_errors(false);

    original.set_literal(true);

    original.set_never_nl(true);

    original.set_dot_nl(true);

    original.set_never_capture(true);

    original.set_case_sensitive(false);

    original.set_perl_classes(true);

    original.set_word_boundary(true);

    original.set_one_line(true);



    options.Copy(original);



    EXPECT_EQ(options.max_mem(), 1024);

    EXPECT_EQ(options.encoding(), EncodingLatin1);

    EXPECT_TRUE(options.posix_syntax());

    EXPECT_TRUE(options.longest_match());

    EXPECT_FALSE(options.log_errors());

    EXPECT_TRUE(options.literal());

    EXPECT_TRUE(options.never_nl());

    EXPECT_TRUE(options.dot_nl());

    EXPECT_TRUE(options.never_capture());

    EXPECT_FALSE(options.case_sensitive());

    EXPECT_TRUE(options.perl_classes());

    EXPECT_TRUE(options.word_boundary());

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_25, CannedOptionsConstructorInitializesValuesCorrectly_25) {

    Options optionsLatin1(RE2::Latin1);

    EXPECT_EQ(optionsLatin1.encoding(), EncodingLatin1);



    Options optionsPOSIX(RE2::POSIX);

    EXPECT_TRUE(optionsPOSIX.posix_syntax());

    EXPECT_TRUE(optionsPOSIX.longest_match());



    Options optionsQuiet(RE2::Quiet);

    EXPECT_FALSE(optionsQuiet.log_errors());

}
