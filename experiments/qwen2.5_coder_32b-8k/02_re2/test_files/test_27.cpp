#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_27 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(RE2OptionsTest_27, DefaultDotNL_27) {

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_27, SetDotNLTrue_27) {

    options.set_dot_nl(true);

    EXPECT_TRUE(options.dot_nl());

}



TEST_F(RE2OptionsTest_27, SetDotNLFALSE_27) {

    options.set_dot_nl(false);

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_27, DefaultMaxMem_27) {

    EXPECT_EQ(options.max_mem(), Options::kDefaultMaxMem);

}



TEST_F(RE2OptionsTest_27, SetMaxMem_27) {

    int64_t new_max_mem = 1024;

    options.set_max_mem(new_max_mem);

    EXPECT_EQ(options.max_mem(), new_max_mem);

}



TEST_F(RE2OptionsTest_27, DefaultEncoding_27) {

    EXPECT_EQ(options.encoding(), Options::EncodingUTF8);

}



TEST_F(RE2OptionsTest_27, SetEncodingLatin1_27) {

    options.set_encoding(Options::EncodingLatin1);

    EXPECT_EQ(options.encoding(), Options::EncodingLatin1);

}



TEST_F(RE2OptionsTest_27, DefaultPosixSyntax_27) {

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_27, SetPosixSyntaxTrue_27) {

    options.set_posix_syntax(true);

    EXPECT_TRUE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_27, DefaultLongestMatch_27) {

    EXPECT_FALSE(options.longest_match());

}



TEST_F(RE2OptionsTest_27, SetLongestMatchTrue_27) {

    options.set_longest_match(true);

    EXPECT_TRUE(options.longest_match());

}



TEST_F(RE2OptionsTest_27, DefaultLogErrors_27) {

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_27, SetLogErrorsFalse_27) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_27, DefaultLiteral_27) {

    EXPECT_FALSE(options.literal());

}



TEST_F(RE2OptionsTest_27, SetLiteralTrue_27) {

    options.set_literal(true);

    EXPECT_TRUE(options.literal());

}



TEST_F(RE2OptionsTest_27, DefaultNeverNL_27) {

    EXPECT_FALSE(options.never_nl());

}



TEST_F(RE2OptionsTest_27, SetNeverNLTrue_27) {

    options.set_never_nl(true);

    EXPECT_TRUE(options.never_nl());

}



TEST_F(RE2OptionsTest_27, DefaultNeverCapture_27) {

    EXPECT_FALSE(options.never_capture());

}



TEST_F(RE2OptionsTest_27, SetNeverCaptureTrue_27) {

    options.set_never_capture(true);

    EXPECT_TRUE(options.never_capture());

}



TEST_F(RE2OptionsTest_27, DefaultCaseSensitive_27) {

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_27, SetCaseSensitiveFalse_27) {

    options.set_case_sensitive(false);

    EXPECT_FALSE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_27, DefaultPerlClasses_27) {

    EXPECT_FALSE(options.perl_classes());

}



TEST_F(RE2OptionsTest_27, SetPerlClassesTrue_27) {

    options.set_perl_classes(true);

    EXPECT_TRUE(options.perl_classes());

}



TEST_F(RE2OptionsTest_27, DefaultWordBoundary_27) {

    EXPECT_FALSE(options.word_boundary());

}



TEST_F(RE2OptionsTest_27, SetWordBoundaryTrue_27) {

    options.set_word_boundary(true);

    EXPECT_TRUE(options.word_boundary());

}



TEST_F(RE2OptionsTest_27, DefaultOneLine_27) {

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_27, SetOneLineTrue_27) {

    options.set_one_line(true);

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_27, CopyConstructor_27) {

    Options original;

    original.set_dot_nl(true);

    original.set_max_mem(1024);

    original.set_encoding(EncodingLatin1);



    Options copy(original);

    EXPECT_EQ(copy.dot_nl(), original.dot_nl());

    EXPECT_EQ(copy.max_mem(), original.max_mem());

    EXPECT_EQ(copy.encoding(), original.encoding());

}



TEST_F(RE2OptionsTest_27, CopyFunction_27) {

    Options original;

    original.set_dot_nl(true);

    original.set_max_mem(1024);

    original.set_encoding(EncodingLatin1);



    Options copy;

    copy.Copy(original);

    EXPECT_EQ(copy.dot_nl(), original.dot_nl());

    EXPECT_EQ(copy.max_mem(), original.max_mem());

    EXPECT_EQ(copy.encoding(), original.encoding());

}
