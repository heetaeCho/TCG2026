#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_18 : public ::testing::Test {

protected:

    RE2::Options options;

};



TEST_F(RE2OptionsTest_18, DefaultConstructorInitializesDefaultValues_18) {

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



TEST_F(RE2OptionsTest_18, SettersChangeValuesCorrectly_18) {

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



TEST_F(RE2OptionsTest_18, CannedOptionsLatin1SetsCorrectValues_18) {

    RE2::Options latin1_options(RE2::CannedOptions::Latin1);

    EXPECT_EQ(latin1_options.encoding(), EncodingLatin1);

    EXPECT_FALSE(latin1_options.posix_syntax());

    EXPECT_FALSE(latin1_options.longest_match());

}



TEST_F(RE2OptionsTest_18, CannedOptionsPOSIXSetsCorrectValues_18) {

    RE2::Options posix_options(RE2::CannedOptions::POSIX);

    EXPECT_EQ(posix_options.encoding(), EncodingUTF8);

    EXPECT_TRUE(posix_options.posix_syntax());

    EXPECT_TRUE(posix_options.longest_match());

}



TEST_F(RE2OptionsTest_18, CannedOptionsQuietSetsCorrectValues_18) {

    RE2::Options quiet_options(RE2::CannedOptions::Quiet);

    EXPECT_EQ(quiet_options.encoding(), EncodingUTF8);

    EXPECT_FALSE(quiet_options.posix_syntax());

    EXPECT_FALSE(quiet_options.longest_match());

    EXPECT_FALSE(quiet_options.log_errors());

}



TEST_F(RE2OptionsTest_18, CopyConstructorCopiesValuesCorrectly_18) {

    RE2::Options original;

    original.set_max_mem(512);

    original.set_encoding(EncodingLatin1);

    original.set_posix_syntax(true);

    original.set_longest_match(true);



    RE2::Options copy;

    copy.Copy(original);



    EXPECT_EQ(copy.max_mem(), 512);

    EXPECT_EQ(copy.encoding(), EncodingLatin1);

    EXPECT_TRUE(copy.posix_syntax());

    EXPECT_TRUE(copy.longest_match());

}
