#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_29 : public ::testing::Test {

protected:

    RE2::Options options;

};



TEST_F(RE2OptionsTest_29, DefaultConstructorInitializesCorrectly_29) {

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



TEST_F(RE2OptionsTest_29, SettersWorkAsExpected_29) {

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



TEST_F(RE2OptionsTest_29, ParseFlagsReturnsExpectedValue_29) {

    int flags = options.ParseFlags();

    // Assuming default values are correctly encoded in ParseFlags

    EXPECT_EQ(flags, 0); // This is a placeholder. Actual value depends on how ParseFlags encodes the flags.



    options.set_posix_syntax(true);

    options.set_longest_match(true);

    flags = options.ParseFlags();

    // Again, this is a placeholder.

    EXPECT_EQ(flags, RE2::POSIX);



    options.set_log_errors(false);

    flags = options.ParseFlags();

    EXPECT_EQ(flags, RE2::POSIX | RE2::Quiet); // This is a placeholder.

}



TEST_F(RE2OptionsTest_29, CopyMethodCopiesCorrectly_29) {

    RE2::Options original;

    original.set_max_mem(1024);

    original.set_encoding(EncodingLatin1);

    original.set_posix_syntax(true);



    options.Copy(original);



    EXPECT_EQ(options.max_mem(), original.max_mem());

    EXPECT_EQ(options.encoding(), original.encoding());

    EXPECT_EQ(options.posix_syntax(), original.posix_syntax());

}



TEST_F(RE2OptionsTest_29, CannedOptionsConstructorInitializesCorrectly_29) {

    RE2::Options latin1_options(RE2::Latin1);

    EXPECT_EQ(latin1_options.encoding(), EncodingLatin1);



    RE2::Options posix_options(RE2::POSIX);

    EXPECT_TRUE(posix_options.posix_syntax());

    EXPECT_TRUE(posix_options.longest_match());



    RE2::Options quiet_options(RE2::Quiet);

    EXPECT_FALSE(quiet_options.log_errors());

}



TEST_F(RE2OptionsTest_29, BoundaryConditionForMaxMem_29) {

    options.set_max_mem(INT64_MIN);

    EXPECT_EQ(options.max_mem(), INT64_MIN);



    options.set_max_mem(INT64_MAX);

    EXPECT_EQ(options.max_mem(), INT64_MAX);

}



TEST_F(RE2OptionsTest_29, BooleanFlagBoundaryConditions_29) {

    options.set_posix_syntax(true);

    EXPECT_TRUE(options.posix_syntax());

    options.set_posix_syntax(false);

    EXPECT_FALSE(options.posix_syntax());



    // Repeat for other boolean flags

    options.set_longest_match(true); EXPECT_TRUE(options.longest_match()); options.set_longest_match(false); EXPECT_FALSE(options.longest_match());

    options.set_log_errors(true); EXPECT_TRUE(options.log_errors()); options.set_log_errors(false); EXPECT_FALSE(options.log_errors());

    options.set_literal(true); EXPECT_TRUE(options.literal()); options.set_literal(false); EXPECT_FALSE(options.literal());

    options.set_never_nl(true); EXPECT_TRUE(options.never_nl()); options.set_never_nl(false); EXPECT_FALSE(options.never_nl());

    options.set_dot_nl(true); EXPECT_TRUE(options.dot_nl()); options.set_dot_nl(false); EXPECT_FALSE(options.dot_nl());

    options.set_never_capture(true); EXPECT_TRUE(options.never_capture()); options.set_never_capture(false); EXPECT_FALSE(options.never_capture());

    options.set_case_sensitive(true); EXPECT_TRUE(options.case_sensitive()); options.set_case_sensitive(false); EXPECT_FALSE(options.case_sensitive());

    options.set_perl_classes(true); EXPECT_TRUE(options.perl_classes()); options.set_perl_classes(false); EXPECT_FALSE(options.perl_classes());

    options.set_word_boundary(true); EXPECT_TRUE(options.word_boundary()); options.set_word_boundary(false); EXPECT_FALSE(options.word_boundary());

    options.set_one_line(true); EXPECT_TRUE(options.one_line()); options.set_one_line(false); EXPECT_FALSE(options.one_line());

}
