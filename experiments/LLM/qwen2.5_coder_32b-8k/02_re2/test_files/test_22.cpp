#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_22 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(RE2OptionsTest_22, DefaultConstructorInitializesValues_22) {

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



TEST_F(RE2OptionsTest_22, CannedOptionsConstructorInitializesValuesForLatin1_22) {

    Options options(CannedOptions::Latin1);

    EXPECT_EQ(options.max_mem(), kDefaultMaxMem);

    EXPECT_EQ(options.encoding(), EncodingLatin1);

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



TEST_F(RE2OptionsTest_22, CannedOptionsConstructorInitializesValuesForPOSIX_22) {

    Options options(CannedOptions::POSIX);

    EXPECT_EQ(options.max_mem(), kDefaultMaxMem);

    EXPECT_EQ(options.encoding(), EncodingUTF8);

    EXPECT_TRUE(options.posix_syntax());

    EXPECT_TRUE(options.longest_match());

    EXPECT_FALSE(options.log_errors());

    EXPECT_FALSE(options.literal());

    EXPECT_FALSE(options.never_nl());

    EXPECT_FALSE(options.dot_nl());

    EXPECT_FALSE(options.never_capture());

    EXPECT_TRUE(options.case_sensitive());

    EXPECT_FALSE(options.perl_classes());

    EXPECT_FALSE(options.word_boundary());

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_22, CannedOptionsConstructorInitializesValuesForQuiet_22) {

    Options options(CannedOptions::Quiet);

    EXPECT_EQ(options.max_mem(), kDefaultMaxMem);

    EXPECT_EQ(options.encoding(), EncodingUTF8);

    EXPECT_FALSE(options.posix_syntax());

    EXPECT_FALSE(options.longest_match());

    EXPECT_FALSE(options.log_errors());

    EXPECT_FALSE(options.literal());

    EXPECT_FALSE(options.never_nl());

    EXPECT_FALSE(options.dot_nl());

    EXPECT_FALSE(options.never_capture());

    EXPECT_TRUE(options.case_sensitive());

    EXPECT_FALSE(options.perl_classes());

    EXPECT_FALSE(options.word_boundary());

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_22, SettersUpdateValuesCorrectly_22) {

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



TEST_F(RE2OptionsTest_22, CopyMethodCopiesValuesCorrectly_22) {

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



    Options copy;

    copy.Copy(original);



    EXPECT_EQ(copy.max_mem(), 1024);

    EXPECT_EQ(copy.encoding(), EncodingLatin1);

    EXPECT_TRUE(copy.posix_syntax());

    EXPECT_TRUE(copy.longest_match());

    EXPECT_FALSE(copy.log_errors());

    EXPECT_TRUE(copy.literal());

    EXPECT_TRUE(copy.never_nl());

    EXPECT_TRUE(copy.dot_nl());

    EXPECT_TRUE(copy.never_capture());

    EXPECT_FALSE(copy.case_sensitive());

    EXPECT_TRUE(copy.perl_classes());

    EXPECT_TRUE(copy.word_boundary());

    EXPECT_TRUE(copy.one_line());

}



TEST_F(RE2OptionsTest_22, LiteralOptionInitialValue_22) {

    EXPECT_FALSE(options.literal());

}
