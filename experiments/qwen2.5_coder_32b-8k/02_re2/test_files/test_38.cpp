#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;

using ::testing::Eq;



class RE2OptionsTest_38 : public ::testing::Test {

protected:

    Options default_options;

};



TEST_F(RE2OptionsTest_38, DefaultConstructorInitializesValues_38) {

    EXPECT_EQ(default_options.max_mem(), kDefaultMaxMem);

    EXPECT_EQ(default_options.encoding(), EncodingUTF8);

    EXPECT_FALSE(default_options.posix_syntax());

    EXPECT_FALSE(default_options.longest_match());

    EXPECT_TRUE(default_options.log_errors());

    EXPECT_FALSE(default_options.literal());

    EXPECT_FALSE(default_options.never_nl());

    EXPECT_FALSE(default_options.dot_nl());

    EXPECT_FALSE(default_options.never_capture());

    EXPECT_TRUE(default_options.case_sensitive());

    EXPECT_FALSE(default_options.perl_classes());

    EXPECT_FALSE(default_options.word_boundary());

    EXPECT_FALSE(default_options.one_line());

}



TEST_F(RE2OptionsTest_38, CopyConstructorCopiesValues_38) {

    Options options;

    options.set_max_mem(1024);

    options.set_encoding(EncodingLatin1);

    options.set_posix_syntax(true);



    Options copied_options(options);

    EXPECT_EQ(copied_options.max_mem(), 1024);

    EXPECT_EQ(copied_options.encoding(), EncodingLatin1);

    EXPECT_TRUE(copied_options.posix_syntax());

}



TEST_F(RE2OptionsTest_38, CopyFunctionCopiesValues_38) {

    Options options;

    options.set_max_mem(1024);

    options.set_encoding(EncodingLatin1);

    options.set_posix_syntax(true);



    Options copied_options;

    copied_options.Copy(options);

    EXPECT_EQ(copied_options.max_mem(), 1024);

    EXPECT_EQ(copied_options.encoding(), EncodingLatin1);

    EXPECT_TRUE(copied_options.posix_syntax());

}



TEST_F(RE2OptionsTest_38, SettersModifyValues_38) {

    default_options.set_max_mem(2048);

    default_options.set_encoding(EncodingLatin1);

    default_options.set_posix_syntax(true);

    default_options.set_longest_match(true);

    default_options.set_log_errors(false);

    default_options.set_literal(true);

    default_options.set_never_nl(true);

    default_options.set_dot_nl(true);

    default_options.set_never_capture(true);

    default_options.set_case_sensitive(false);

    default_options.set_perl_classes(true);

    default_options.set_word_boundary(true);

    default_options.set_one_line(true);



    EXPECT_EQ(default_options.max_mem(), 2048);

    EXPECT_EQ(default_options.encoding(), EncodingLatin1);

    EXPECT_TRUE(default_options.posix_syntax());

    EXPECT_TRUE(default_options.longest_match());

    EXPECT_FALSE(default_options.log_errors());

    EXPECT_TRUE(default_options.literal());

    EXPECT_TRUE(default_options.never_nl());

    EXPECT_TRUE(default_options.dot_nl());

    EXPECT_TRUE(default_options.never_capture());

    EXPECT_FALSE(default_options.case_sensitive());

    EXPECT_TRUE(default_options.perl_classes());

    EXPECT_TRUE(default_options.word_boundary());

    EXPECT_TRUE(default_options.one_line());

}



TEST_F(RE2OptionsTest_38, CannedOptionsLatin1SetsEncoding_38) {

    Options options(CannedOptions::Latin1);

    EXPECT_EQ(options.encoding(), EncodingLatin1);

}



TEST_F(RE2OptionsTest_38, CannedOptionsPOSIXSetsFlags_38) {

    Options options(CannedOptions::POSIX);

    EXPECT_TRUE(options.posix_syntax());

    EXPECT_TRUE(options.longest_match());

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_38, CannedOptionsQuietSuppressesErrors_38) {

    Options options(CannedOptions::Quiet);

    EXPECT_FALSE(options.log_errors());

}
