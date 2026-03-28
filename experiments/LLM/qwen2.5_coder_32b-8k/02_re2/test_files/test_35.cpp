#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_35 : public ::testing::Test {

protected:

    RE2::Options options;

};



TEST_F(RE2OptionsTest_35, DefaultConstructorInitializesCorrectly_35) {

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



TEST_F(RE2OptionsTest_35, SettersAndGettersWorkCorrectly_35) {

    options.set_max_mem(1024);

    EXPECT_EQ(options.max_mem(), 1024);



    options.set_encoding(EncodingLatin1);

    EXPECT_EQ(options.encoding(), EncodingLatin1);



    options.set_posix_syntax(true);

    EXPECT_TRUE(options.posix_syntax());



    options.set_longest_match(true);

    EXPECT_TRUE(options.longest_match());



    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());



    options.set_literal(true);

    EXPECT_TRUE(options.literal());



    options.set_never_nl(true);

    EXPECT_TRUE(options.never_nl());



    options.set_dot_nl(true);

    EXPECT_TRUE(options.dot_nl());



    options.set_never_capture(true);

    EXPECT_TRUE(options.never_capture());



    options.set_case_sensitive(false);

    EXPECT_FALSE(options.case_sensitive());



    options.set_perl_classes(true);

    EXPECT_TRUE(options.perl_classes());



    options.set_word_boundary(true);

    EXPECT_TRUE(options.word_boundary());



    options.set_one_line(true);

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_35, CannedOptionsConstructorInitializesCorrectlyWithLatin1_35) {

    RE2::Options latin1_options(RE2::CannedOptions::Latin1);



    EXPECT_EQ(latin1_options.encoding(), EncodingLatin1);

    EXPECT_FALSE(latin1_options.posix_syntax());

    EXPECT_FALSE(latin1_options.longest_match());

    EXPECT_TRUE(latin1_options.log_errors());

}



TEST_F(RE2OptionsTest_35, CannedOptionsConstructorInitializesCorrectlyWithPOSIX_35) {

    RE2::Options posix_options(RE2::CannedOptions::POSIX);



    EXPECT_EQ(posix_options.encoding(), EncodingUTF8);

    EXPECT_TRUE(posix_options.posix_syntax());

    EXPECT_TRUE(posix_options.longest_match());

    EXPECT_FALSE(posix_options.log_errors());

}



TEST_F(RE2OptionsTest_35, CopyFunctionCopiesAllSettings_35) {

    RE2::Options original;

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



    RE2::Options copy;

    copy.Copy(original);



    EXPECT_EQ(copy.max_mem(), original.max_mem());

    EXPECT_EQ(copy.encoding(), original.encoding());

    EXPECT_EQ(copy.posix_syntax(), original.posix_syntax());

    EXPECT_EQ(copy.longest_match(), original.longest_match());

    EXPECT_EQ(copy.log_errors(), original.log_errors());

    EXPECT_EQ(copy.literal(), original.literal());

    EXPECT_EQ(copy.never_nl(), original.never_nl());

    EXPECT_EQ(copy.dot_nl(), original.dot_nl());

    EXPECT_EQ(copy.never_capture(), original.never_capture());

    EXPECT_EQ(copy.case_sensitive(), original.case_sensitive());

    EXPECT_EQ(copy.perl_classes(), original.perl_classes());

    EXPECT_EQ(copy.word_boundary(), original.word_boundary());

    EXPECT_EQ(copy.one_line(), original.one_line());

}
