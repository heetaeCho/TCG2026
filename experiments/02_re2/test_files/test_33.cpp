#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_33 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(RE2OptionsTest_33, DefaultConstructorInitializesValues_33) {

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



TEST_F(RE2OptionsTest_33, CannedOptionsConstructorInitializesValuesLatin1_33) {

    Options options(CannedOptions::Latin1);

    EXPECT_EQ(options.encoding(), EncodingLatin1);

    EXPECT_FALSE(options.posix_syntax());

    EXPECT_FALSE(options.longest_match());

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_33, CannedOptionsConstructorInitializesValuesPOSIX_33) {

    Options options(CannedOptions::POSIX);

    EXPECT_EQ(options.encoding(), EncodingUTF8);

    EXPECT_TRUE(options.posix_syntax());

    EXPECT_TRUE(options.longest_match());

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_33, SetMaxMemUpdatesValue_33) {

    int64_t new_max_mem = 1024;

    options.set_max_mem(new_max_mem);

    EXPECT_EQ(options.max_mem(), new_max_mem);

}



TEST_F(RE2OptionsTest_33, SetEncodingUpdatesValue_33) {

    Encoding new_encoding = EncodingLatin1;

    options.set_encoding(new_encoding);

    EXPECT_EQ(options.encoding(), new_encoding);

}



TEST_F(RE2OptionsTest_33, SetPosixSyntaxUpdatesValue_33) {

    bool new_value = true;

    options.set_posix_syntax(new_value);

    EXPECT_TRUE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_33, SetLongestMatchUpdatesValue_33) {

    bool new_value = true;

    options.set_longest_match(new_value);

    EXPECT_TRUE(options.longest_match());

}



TEST_F(RE2OptionsTest_33, SetLogErrorsUpdatesValue_33) {

    bool new_value = false;

    options.set_log_errors(new_value);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_33, SetLiteralUpdatesValue_33) {

    bool new_value = true;

    options.set_literal(new_value);

    EXPECT_TRUE(options.literal());

}



TEST_F(RE2OptionsTest_33, SetNeverNlUpdatesValue_33) {

    bool new_value = true;

    options.set_never_nl(new_value);

    EXPECT_TRUE(options.never_nl());

}



TEST_F(RE2OptionsTest_33, SetDotNlUpdatesValue_33) {

    bool new_value = true;

    options.set_dot_nl(new_value);

    EXPECT_TRUE(options.dot_nl());

}



TEST_F(RE2OptionsTest_33, SetNeverCaptureUpdatesValue_33) {

    bool new_value = true;

    options.set_never_capture(new_value);

    EXPECT_TRUE(options.never_capture());

}



TEST_F(RE2OptionsTest_33, SetCaseSensitiveUpdatesValue_33) {

    bool new_value = false;

    options.set_case_sensitive(new_value);

    EXPECT_FALSE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_33, SetPerlClassesUpdatesValue_33) {

    bool new_value = true;

    options.set_perl_classes(new_value);

    EXPECT_TRUE(options.perl_classes());

}



TEST_F(RE2OptionsTest_33, SetWordBoundaryUpdatesValue_33) {

    bool new_value = true;

    options.set_word_boundary(new_value);

    EXPECT_TRUE(options.word_boundary());

}



TEST_F(RE2OptionsTest_33, SetOneLineUpdatesValue_33) {

    bool new_value = true;

    options.set_one_line(new_value);

    EXPECT_TRUE(options.one_line());

}
