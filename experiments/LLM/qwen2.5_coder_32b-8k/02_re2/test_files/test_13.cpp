#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_13 : public ::testing::Test {

protected:

    RE2::Options options;

};



TEST_F(RE2OptionsTest_13, DefaultMaxMemValue_13) {

    EXPECT_EQ(options.max_mem(), kDefaultMaxMem);

}



TEST_F(RE2OptionsTest_13, SetMaxMemUpdatesValue_13) {

    int64_t new_max_mem = 1024;

    options.set_max_mem(new_max_mem);

    EXPECT_EQ(options.max_mem(), new_max_mem);

}



TEST_F(RE2OptionsTest_13, DefaultEncodingValue_13) {

    EXPECT_EQ(options.encoding(), EncodingUTF8);

}



TEST_F(RE2OptionsTest_13, SetEncodingUpdatesValue_13) {

    options.set_encoding(EncodingLatin1);

    EXPECT_EQ(options.encoding(), EncodingLatin1);

}



TEST_F(RE2OptionsTest_13, DefaultPosixSyntaxValue_13) {

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_13, SetPosixSyntaxUpdatesValue_13) {

    options.set_posix_syntax(true);

    EXPECT_TRUE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_13, DefaultLongestMatchValue_13) {

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_13, SetLongestMatchUpdatesValue_13) {

    options.set_longest_match(true);

    EXPECT_TRUE(options.longest_match());

}



TEST_F(RE2OptionsTest_13, DefaultLogErrorsValue_13) {

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_13, SetLogErrorsUpdatesValue_13) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_13, DefaultLiteralValue_13) {

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_13, SetLiteralUpdatesValue_13) {

    options.set_literal(true);

    EXPECT_TRUE(options.literal());

}



TEST_F(RE2OptionsTest_13, DefaultNeverNlValue_13) {

    EXPECT_FALSE(options.never_nl());

}



TEST_F(RE2OptionsTest_13, SetNeverNlUpdatesValue_13) {

    options.set_never_nl(true);

    EXPECT_TRUE(options.never_nl());

}



TEST_F(RE2OptionsTest_13, DefaultDotNlValue_13) {

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_13, SetDotNlUpdatesValue_13) {

    options.set_dot_nl(true);

    EXPECT_TRUE(options.dot_nl());

}



TEST_F(RE2OptionsTest_13, DefaultNeverCaptureValue_13) {

    EXPECT_FALSE(options.never_capture());

}



TEST_F(RE2OptionsTest_13, SetNeverCaptureUpdatesValue_13) {

    options.set_never_capture(true);

    EXPECT_TRUE(options.never_capture());

}



TEST_F(RE2OptionsTest_13, DefaultCaseSensitiveValue_13) {

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_13, SetCaseSensitiveUpdatesValue_13) {

    options.set_case_sensitive(false);

    EXPECT_FALSE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_13, DefaultPerlClassesValue_13) {

    EXPECT_FALSE(options.perl_classes());

}



TEST_F(RE2OptionsTest_13, SetPerlClassesUpdatesValue_13) {

    options.set_perl_classes(true);

    EXPECT_TRUE(options.perl_classes());

}



TEST_F(RE2OptionsTest_13, DefaultWordBoundaryValue_13) {

    EXPECT_FALSE(options.word_boundary());

}



TEST_F(RE2OptionsTest_13, SetWordBoundaryUpdatesValue_13) {

    options.set_word_boundary(true);

    EXPECT_TRUE(options.word_boundary());

}



TEST_F(RE2OptionsTest_13, DefaultOneLineValue_13) {

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_13, SetOneLineUpdatesValue_13) {

    options.set_one_line(true);

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_13, CannedOptionsLatin1SetsEncodingToLatin1_13) {

    RE2::Options latin1_options(RE2::Latin1);

    EXPECT_EQ(latin1_options.encoding(), EncodingLatin1);

}



TEST_F(RE2OptionsTest_13, CannedOptionsPOSIXSetsPosixSyntaxAndLongestMatch_13) {

    RE2::Options posix_options(RE2::POSIX);

    EXPECT_TRUE(posix_options.posix_syntax());

    EXPECT_TRUE(posix_options.longest_match());

}



TEST_F(RE2OptionsTest_13, CannedOptionsQuietDisablesLogErrors_13) {

    RE2::Options quiet_options(RE2::Quiet);

    EXPECT_FALSE(quiet_options.log_errors());

}
