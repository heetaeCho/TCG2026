#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_15 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(RE2OptionsTest_15, DefaultConstructorInitializesCorrectly_15) {

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



TEST_F(RE2OptionsTest_15, CannedOptionsConstructorInitializesCorrectlyWithUTF8_15) {

    Options options(UTF8);

    EXPECT_EQ(options.encoding(), EncodingUTF8);

}



TEST_F(RE2OptionsTest_15, CannedOptionsConstructorInitializesCorrectlyWithLatin1_15) {

    Options options(Latin1);

    EXPECT_EQ(options.encoding(), EncodingLatin1);

}



TEST_F(RE2OptionsTest_15, CannedOptionsConstructorInitializesCorrectlyWithPOSIX_15) {

    Options options(POSIX);

    EXPECT_TRUE(options.posix_syntax());

    EXPECT_TRUE(options.longest_match());

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_15, CannedOptionsConstructorInitializesCorrectlyWithQuiet_15) {

    Options options(Quiet);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_15, SetMaxMemUpdatesValue_15) {

    int64_t new_max_mem = 1024 * 1024;

    options.set_max_mem(new_max_mem);

    EXPECT_EQ(options.max_mem(), new_max_mem);

}



TEST_F(RE2OptionsTest_15, SetEncodingUpdatesValue_15) {

    Encoding new_encoding = EncodingLatin1;

    options.set_encoding(new_encoding);

    EXPECT_EQ(options.encoding(), new_encoding);

}



TEST_F(RE2OptionsTest_15, SetPosixSyntaxUpdatesValue_15) {

    bool new_value = true;

    options.set_posix_syntax(new_value);

    EXPECT_EQ(options.posix_syntax(), new_value);

}



TEST_F(RE2OptionsTest_15, SetLongestMatchUpdatesValue_15) {

    bool new_value = true;

    options.set_longest_match(new_value);

    EXPECT_EQ(options.longest_match(), new_value);

}



TEST_F(RE2OptionsTest_15, SetLogErrorsUpdatesValue_15) {

    bool new_value = false;

    options.set_log_errors(new_value);

    EXPECT_EQ(options.log_errors(), new_value);

}



TEST_F(RE2OptionsTest_15, SetLiteralUpdatesValue_15) {

    bool new_value = true;

    options.set_literal(new_value);

    EXPECT_EQ(options.literal(), new_value);

}



TEST_F(RE2OptionsTest_15, SetNeverNlUpdatesValue_15) {

    bool new_value = true;

    options.set_never_nl(new_value);

    EXPECT_EQ(options.never_nl(), new_value);

}



TEST_F(RE2OptionsTest_15, SetDotNlUpdatesValue_15) {

    bool new_value = true;

    options.set_dot_nl(new_value);

    EXPECT_EQ(options.dot_nl(), new_value);

}



TEST_F(RE2OptionsTest_15, SetNeverCaptureUpdatesValue_15) {

    bool new_value = true;

    options.set_never_capture(new_value);

    EXPECT_EQ(options.never_capture(), new_value);

}



TEST_F(RE2OptionsTest_15, SetCaseSensitiveUpdatesValue_15) {

    bool new_value = false;

    options.set_case_sensitive(new_value);

    EXPECT_EQ(options.case_sensitive(), new_value);

}



TEST_F(RE2OptionsTest_15, SetPerlClassesUpdatesValue_15) {

    bool new_value = true;

    options.set_perl_classes(new_value);

    EXPECT_EQ(options.perl_classes(), new_value);

}



TEST_F(RE2OptionsTest_15, SetWordBoundaryUpdatesValue_15) {

    bool new_value = true;

    options.set_word_boundary(new_value);

    EXPECT_EQ(options.word_boundary(), new_value);

}



TEST_F(RE2OptionsTest_15, SetOneLineUpdatesValue_15) {

    bool new_value = true;

    options.set_one_line(new_value);

    EXPECT_EQ(options.one_line(), new_value);

}
