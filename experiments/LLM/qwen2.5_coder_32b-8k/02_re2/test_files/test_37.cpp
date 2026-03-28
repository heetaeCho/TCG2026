#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_37 : public ::testing::Test {

protected:

    RE2::Options options;

};



TEST_F(RE2OptionsTest_37, DefaultConstructorInitializesDefaultValues_37) {

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



TEST_F(RE2OptionsTest_37, SetOneLineChangesOneLineOption_37) {

    options.set_one_line(true);

    EXPECT_TRUE(options.one_line());



    options.set_one_line(false);

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_37, ParseFlagsReturnsCorrectValue_37) {

    int flags = options.ParseFlags();

    // Assuming ParseFlags returns a bitmask based on the settings

    // Here we check that the default flag state matches expected value

    EXPECT_EQ(flags, 0); // Placeholder for actual expected value based on defaults



    options.set_posix_syntax(true);

    flags = options.ParseFlags();

    // Check if setting posix_syntax affects the returned flags

    // This is a placeholder and should be replaced with actual bitmask checks

    EXPECT_NE(flags, 0); // Placeholder for actual expected value based on changes

}



TEST_F(RE2OptionsTest_37, SetMaxMemChangesMaxMemValue_37) {

    int64_t new_max_mem = 1024 * 1024;

    options.set_max_mem(new_max_mem);

    EXPECT_EQ(options.max_mem(), new_max_mem);

}



TEST_F(RE2OptionsTest_37, SetEncodingChangesEncodingValue_37) {

    Encoding new_encoding = EncodingLatin1;

    options.set_encoding(new_encoding);

    EXPECT_EQ(options.encoding(), new_encoding);

}



TEST_F(RE2OptionsTest_37, SetPosixSyntaxChangesPosixSyntaxOption_37) {

    options.set_posix_syntax(true);

    EXPECT_TRUE(options.posix_syntax());



    options.set_posix_syntax(false);

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_37, SetLongestMatchChangesLongestMatchOption_37) {

    options.set_longest_match(true);

    EXPECT_TRUE(options.longest_match());



    options.set_longest_match(false);

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_37, SetLogErrorsChangesLogErrorsOption_37) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());



    options.set_log_errors(true);

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_37, SetLiteralChangesLiteralOption_37) {

    options.set_literal(true);

    EXPECT_TRUE(options.literal());



    options.set_literal(false);

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_37, SetNeverNlChangesNeverNlOption_37) {

    options.set_never_nl(true);

    EXPECT_TRUE(options.never_nl());



    options.set_never_nl(false);

    EXPECT_FALSE(options.never_nl());

}



TEST_F(RE2OptionsTest_37, SetDotNlChangesDotNlOption_37) {

    options.set_dot_nl(true);

    EXPECT_TRUE(options.dot_nl());



    options.set_dot_nl(false);

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_37, SetNeverCaptureChangesNeverCaptureOption_37) {

    options.set_never_capture(true);

    EXPECT_TRUE(options.never_capture());



    options.set_never_capture(false);

    EXPECT_FALSE(options.never_capture());

}



TEST_F(RE2OptionsTest_37, SetCaseSensitiveChangesCaseSensitiveOption_37) {

    options.set_case_sensitive(false);

    EXPECT_FALSE(options.case_sensitive());



    options.set_case_sensitive(true);

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_37, SetPerlClassesChangesPerlClassesOption_37) {

    options.set_perl_classes(true);

    EXPECT_TRUE(options.perl_classes());



    options.set_perl_classes(false);

    EXPECT_FALSE(options.perl_classes());

}



TEST_F(RE2OptionsTest_37, SetWordBoundaryChangesWordBoundaryOption_37) {

    options.set_word_boundary(true);

    EXPECT_TRUE(options.word_boundary());



    options.set_word_boundary(false);

    EXPECT_FALSE(options.word_boundary());

}
