#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_19 : public ::testing::Test {

protected:

    RE2::Options options;

};



TEST_F(RE2OptionsTest_19, DefaultLongestMatchFalse_19) {

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_19, SetLongestMatchTrueAndGetTrue_19) {

    options.set_longest_match(true);

    EXPECT_TRUE(options.longest_match());

}



TEST_F(RE2OptionsTest_19, SetLongestMatchFalseAndGetFalse_19) {

    options.set_longest_match(false);

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_19, DefaultLogErrorsTrue_19) {

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_19, SetLogErrorsFalseAndGetFalse_19) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_19, DefaultCaseSensitiveTrue_19) {

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_19, SetCaseSensitiveFalseAndGetFalse_19) {

    options.set_case_sensitive(false);

    EXPECT_FALSE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_19, DefaultLiteralFalse_19) {

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_19, SetLiteralTrueAndGetTrue_19) {

    options.set_literal(true);

    EXPECT_TRUE(options.literal());

}



TEST_F(RE2OptionsTest_19, DefaultNeverNlFalse_19) {

    EXPECT_FALSE(options.never_nl());

}



TEST_F(RE2OptionsTest_19, SetNeverNlTrueAndGetTrue_19) {

    options.set_never_nl(true);

    EXPECT_TRUE(options.never_nl());

}



TEST_F(RE2OptionsTest_19, DefaultDotNlFalse_19) {

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_19, SetDotNlTrueAndGetTrue_19) {

    options.set_dot_nl(true);

    EXPECT_TRUE(options.dot_nl());

}



TEST_F(RE2OptionsTest_19, DefaultNeverCaptureFalse_19) {

    EXPECT_FALSE(options.never_capture());

}



TEST_F(RE2OptionsTest_19, SetNeverCaptureTrueAndGetTrue_19) {

    options.set_never_capture(true);

    EXPECT_TRUE(options.never_capture());

}



TEST_F(RE2OptionsTest_19, DefaultPerlClassesFalse_19) {

    EXPECT_FALSE(options.perl_classes());

}



TEST_F(RE2OptionsTest_19, SetPerlClassesTrueAndGetTrue_19) {

    options.set_perl_classes(true);

    EXPECT_TRUE(options.perl_classes());

}



TEST_F(RE2OptionsTest_19, DefaultWordBoundaryFalse_19) {

    EXPECT_FALSE(options.word_boundary());

}



TEST_F(RE2OptionsTest_19, SetWordBoundaryTrueAndGetTrue_19) {

    options.set_word_boundary(true);

    EXPECT_TRUE(options.word_boundary());

}



TEST_F(RE2OptionsTest_19, DefaultOneLineFalse_19) {

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_19, SetOneLineTrueAndGetTrue_19) {

    options.set_one_line(true);

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_19, CannedOptionsPOSIXSetsExpectedValues_19) {

    RE2::Options posix_options(RE2::CannedOptions::POSIX);

    EXPECT_EQ(posix_options.encoding(), EncodingUTF8);

    EXPECT_TRUE(posix_options.posix_syntax());

    EXPECT_TRUE(posix_options.longest_match());

    EXPECT_TRUE(posix_options.log_errors());

}



TEST_F(RE2OptionsTest_19, CannedOptionsLatin1SetsExpectedValues_19) {

    RE2::Options latin1_options(RE2::CannedOptions::Latin1);

    EXPECT_EQ(latin1_options.encoding(), EncodingLatin1);

    EXPECT_FALSE(latin1_options.posix_syntax());

    EXPECT_FALSE(latin1_options.longest_match());

    EXPECT_TRUE(latin1_options.log_errors());

}



TEST_F(RE2OptionsTest_19, CannedOptionsQuietSetsExpectedValues_19) {

    RE2::Options quiet_options(RE2::CannedOptions::Quiet);

    EXPECT_EQ(quiet_options.encoding(), EncodingUTF8);

    EXPECT_FALSE(quiet_options.posix_syntax());

    EXPECT_FALSE(quiet_options.longest_match());

    EXPECT_FALSE(quiet_options.log_errors());

}
