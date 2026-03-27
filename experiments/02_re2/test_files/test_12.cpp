#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_12 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(RE2OptionsTest_12, DefaultMaxMemValue_12) {

    EXPECT_EQ(options.max_mem(), 8 << 20); // Assuming kDefaultMaxMem is 8MB

}



TEST_F(RE2OptionsTest_12, SetAndGetMaxMem_12) {

    int64_t new_max_mem = 16 << 20;

    options.set_max_mem(new_max_mem);

    EXPECT_EQ(options.max_mem(), new_max_mem);

}



TEST_F(RE2OptionsTest_12, DefaultEncodingValue_12) {

    EXPECT_EQ(options.encoding(), EncodingUTF8);

}



TEST_F(RE2OptionsTest_12, SetAndGetEncoding_12) {

    options.set_encoding(EncodingLatin1);

    EXPECT_EQ(options.encoding(), EncodingLatin1);

}



TEST_F(RE2OptionsTest_12, DefaultPosixSyntaxValue_12) {

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_12, SetAndGetPosixSyntax_12) {

    options.set_posix_syntax(true);

    EXPECT_TRUE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_12, DefaultLongestMatchValue_12) {

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_12, SetAndGetLongestMatch_12) {

    options.set_longest_match(true);

    EXPECT_TRUE(options.longest_match());

}



TEST_F(RE2OptionsTest_12, DefaultLogErrorsValue_12) {

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_12, SetAndGetLogErrors_12) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_12, DefaultLiteralValue_12) {

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_12, SetAndGetLiteral_12) {

    options.set_literal(true);

    EXPECT_TRUE(options.literal());

}



TEST_F(RE2OptionsTest_12, DefaultNeverNLValue_12) {

    EXPECT_FALSE(options.never_nl());

}



TEST_F(RE2OptionsTest_12, SetAndGetNeverNL_12) {

    options.set_never_nl(true);

    EXPECT_TRUE(options.never_nl());

}



TEST_F(RE2OptionsTest_12, DefaultDotNLValue_12) {

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_12, SetAndGetDotNL_12) {

    options.set_dot_nl(true);

    EXPECT_TRUE(options.dot_nl());

}



TEST_F(RE2OptionsTest_12, DefaultNeverCaptureValue_12) {

    EXPECT_FALSE(options.never_capture());

}



TEST_F(RE2OptionsTest_12, SetAndGetNeverCapture_12) {

    options.set_never_capture(true);

    EXPECT_TRUE(options.never_capture());

}



TEST_F(RE2OptionsTest_12, DefaultCaseSensitiveValue_12) {

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_12, SetAndGetCaseSensitive_12) {

    options.set_case_sensitive(false);

    EXPECT_FALSE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_12, DefaultPerlClassesValue_12) {

    EXPECT_FALSE(options.perl_classes());

}



TEST_F(RE2OptionsTest_12, SetAndGetPerlClasses_12) {

    options.set_perl_classes(true);

    EXPECT_TRUE(options.perl_classes());

}



TEST_F(RE2OptionsTest_12, DefaultWordBoundaryValue_12) {

    EXPECT_FALSE(options.word_boundary());

}



TEST_F(RE2OptionsTest_12, SetAndGetWordBoundary_12) {

    options.set_word_boundary(true);

    EXPECT_TRUE(options.word_boundary());

}



TEST_F(RE2OptionsTest_12, DefaultOneLineValue_12) {

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_12, SetAndGetOneLine_12) {

    options.set_one_line(true);

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_12, CopyConstructorPreservesValues_12) {

    Options original;

    original.set_max_mem(4 << 20);

    original.set_encoding(EncodingLatin1);

    original.set_posix_syntax(true);



    Options copy(original);

    EXPECT_EQ(copy.max_mem(), original.max_mem());

    EXPECT_EQ(copy.encoding(), original.encoding());

    EXPECT_EQ(copy.posix_syntax(), original.posix_syntax());

}



TEST_F(RE2OptionsTest_12, CopyMethodPreservesValues_12) {

    Options original;

    original.set_max_mem(4 << 20);

    original.set_encoding(EncodingLatin1);

    original.set_posix_syntax(true);



    Options copy;

    copy.Copy(original);

    EXPECT_EQ(copy.max_mem(), original.max_mem());

    EXPECT_EQ(copy.encoding(), original.encoding());

    EXPECT_EQ(copy.posix_syntax(), original.posix_syntax());

}



TEST_F(RE2OptionsTest_12, DefaultConstructorSetsCannedOptionsLatin1_12) {

    Options options(CannedOptions::Latin1);

    EXPECT_EQ(options.encoding(), EncodingLatin1);

}



TEST_F(RE2OptionsTest_12, DefaultConstructorSetsCannedOptionsPOSIX_12) {

    Options options(CannedOptions::POSIX);

    EXPECT_TRUE(options.posix_syntax());

    EXPECT_TRUE(options.longest_match());

    EXPECT_FALSE(options.log_errors());

}
