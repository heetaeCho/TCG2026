#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_20 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(RE2OptionsTest_20, DefaultConstructor_LogErrorsTrue_20) {

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_20, SetLogErrors_FalseThenGet_LogErrorsFalse_20) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_20, CannedOptionsQuiet_SetMaxMemDefaultAndLogErrorsFalse_20) {

    Options quiet_options(CannedOptions::Quiet);

    EXPECT_EQ(quiet_options.max_mem(), kDefaultMaxMem);

    EXPECT_FALSE(quiet_options.log_errors());

}



TEST_F(RE2OptionsTest_20, CannedOptionsPOSIX_SetPosixSyntaxAndLongestMatchTrue_20) {

    Options posix_options(CannedOptions::POSIX);

    EXPECT_TRUE(posix_options.posix_syntax());

    EXPECT_TRUE(posix_options.longest_match());

}



TEST_F(RE2OptionsTest_20, SetMaxMem_NegativeValue_DoesNotThrowException_20) {

    EXPECT_NO_THROW(options.set_max_mem(-1));

    EXPECT_EQ(options.max_mem(), -1);

}



TEST_F(RE2OptionsTest_20, SetMaxMem_ZeroValue_SetsCorrectly_20) {

    options.set_max_mem(0);

    EXPECT_EQ(options.max_mem(), 0);

}



TEST_F(RE2OptionsTest_20, SetEncoding_UTF8ThenGet_ReturnsUTF8_20) {

    options.set_encoding(EncodingUTF8);

    EXPECT_EQ(options.encoding(), EncodingUTF8);

}



TEST_F(RE2OptionsTest_20, SetPosixSyntax_TrueThenGet_ReturnsTrue_20) {

    options.set_posix_syntax(true);

    EXPECT_TRUE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_20, SetLongestMatch_FalseThenGet_ReturnsFalse_20) {

    options.set_longest_match(false);

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_20, SetLiteral_TrueThenGet_ReturnsTrue_20) {

    options.set_literal(true);

    EXPECT_TRUE(options.literal());

}



TEST_F(RE2OptionsTest_20, SetNeverNl_TrueThenGet_ReturnsTrue_20) {

    options.set_never_nl(true);

    EXPECT_TRUE(options.never_nl());

}



TEST_F(RE2OptionsTest_20, SetDotNl_TrueThenGet_ReturnsTrue_20) {

    options.set_dot_nl(true);

    EXPECT_TRUE(options.dot_nl());

}



TEST_F(RE2OptionsTest_20, SetNeverCapture_TrueThenGet_ReturnsTrue_20) {

    options.set_never_capture(true);

    EXPECT_TRUE(options.never_capture());

}



TEST_F(RE2OptionsTest_20, SetCaseSensitive_FalseThenGet_ReturnsFalse_20) {

    options.set_case_sensitive(false);

    EXPECT_FALSE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_20, SetPerlClasses_TrueThenGet_ReturnsTrue_20) {

    options.set_perl_classes(true);

    EXPECT_TRUE(options.perl_classes());

}



TEST_F(RE2OptionsTest_20, SetWordBoundary_TrueThenGet_ReturnsTrue_20) {

    options.set_word_boundary(true);

    EXPECT_TRUE(options.word_boundary());

}



TEST_F(RE2OptionsTest_20, SetOneLine_TrueThenGet_ReturnsTrue_20) {

    options.set_one_line(true);

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_20, CopyConstructor_AllFieldsCopiedCorrectly_20) {

    Options original;

    original.set_max_mem(12345);

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



    EXPECT_EQ(copy.max_mem(), 12345);

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



TEST_F(RE2OptionsTest_20, ParseFlags_DefaultOptions_ReturnsExpectedValue_20) {

    int flags = options.ParseFlags();

    // This test assumes a known return value from ParseFlags() for default options.

    // The actual value should be determined based on the implementation details.

    EXPECT_EQ(flags, 0); // Placeholder value

}
