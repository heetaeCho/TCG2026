#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_14 : public ::testing::Test {

protected:

    RE2::Options options;

};



TEST_F(RE2OptionsTest_14, DefaultConstructorSetsDefaultValues_14) {

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



TEST_F(RE2OptionsTest_14, CannedOptionsConstructorSetsCorrectValuesForLatin1_14) {

    RE2::Options latin1_options(RE2::CannedOptions::Latin1);

    EXPECT_EQ(latin1_options.encoding(), EncodingLatin1);

}



TEST_F(RE2OptionsTest_14, CannedOptionsConstructorSetsCorrectValuesForPOSIX_14) {

    RE2::Options posix_options(RE2::CannedOptions::POSIX);

    EXPECT_TRUE(posix_options.posix_syntax());

    EXPECT_TRUE(posix_options.longest_match());

    EXPECT_FALSE(posix_options.log_errors());

}



TEST_F(RE2OptionsTest_14, CannedOptionsConstructorSetsCorrectValuesForQuiet_14) {

    RE2::Options quiet_options(RE2::CannedOptions::Quiet);

    EXPECT_TRUE(quiet_options.log_errors());

}



TEST_F(RE2OptionsTest_14, SettersChangeValuesCorrectly_14) {

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



TEST_F(RE2OptionsTest_14, CopyFunctionCopiesValuesCorrectly_14) {

    RE2::Options options_copy;

    options_copy.Copy(options);



    EXPECT_EQ(options.max_mem(), options_copy.max_mem());

    EXPECT_EQ(options.encoding(), options_copy.encoding());

    EXPECT_EQ(options.posix_syntax(), options_copy.posix_syntax());

    EXPECT_EQ(options.longest_match(), options_copy.longest_match());

    EXPECT_EQ(options.log_errors(), options_copy.log_errors());

    EXPECT_EQ(options.literal(), options_copy.literal());

    EXPECT_EQ(options.never_nl(), options_copy.never_nl());

    EXPECT_EQ(options.dot_nl(), options_copy.dot_nl());

    EXPECT_EQ(options.never_capture(), options_copy.never_capture());

    EXPECT_EQ(options.case_sensitive(), options_copy.case_sensitive());

    EXPECT_EQ(options.perl_classes(), options_copy.perl_classes());

    EXPECT_EQ(options.word_boundary(), options_copy.word_boundary());

    EXPECT_EQ(options.one_line(), options_copy.one_line());

}



TEST_F(RE2OptionsTest_14, ParseFlagsReturnsNonNegativeValue_14) {

    EXPECT_GE(options.ParseFlags(), 0);

}
