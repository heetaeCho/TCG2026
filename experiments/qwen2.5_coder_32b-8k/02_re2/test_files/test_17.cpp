#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_17 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(RE2OptionsTest_17, DefaultPosixSyntaxFalse_17) {

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_17, SetPosixSyntaxTrue_17) {

    options.set_posix_syntax(true);

    EXPECT_TRUE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_17, SetPosixSyntaxFalse_17) {

    options.set_posix_syntax(false);

    EXPECT_FALSE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_17, DefaultMaxMem_17) {

    EXPECT_EQ(options.max_mem(), kDefaultMaxMem);

}



TEST_F(RE2OptionsTest_17, SetMaxMem_17) {

    int64_t testValue = 1024;

    options.set_max_mem(testValue);

    EXPECT_EQ(options.max_mem(), testValue);

}



TEST_F(RE2OptionsTest_17, DefaultEncodingUTF8_17) {

    EXPECT_EQ(options.encoding(), EncodingUTF8);

}



TEST_F(RE2OptionsTest_17, SetEncodingLatin1_17) {

    options.set_encoding(EncodingLatin1);

    EXPECT_EQ(options.encoding(), EncodingLatin1);

}



TEST_F(RE2OptionsTest_17, DefaultLogErrorsTrue_17) {

    EXPECT_TRUE(options.log_errors());

}



TEST_F(RE2OptionsTest_17, SetLogErrorsFalse_17) {

    options.set_log_errors(false);

    EXPECT_FALSE(options.log_errors());

}



TEST_F(RE2OptionsTest_17, DefaultCaseSensitiveTrue_17) {

    EXPECT_TRUE(options.case_sensitive());

}



TEST_F(RE2OptionsTest_17, SetCaseSensitiveFalse_17) {

    options.set_case_sensitive(false);

    EXPECT_FALSE(options.case_sensitive());

}
