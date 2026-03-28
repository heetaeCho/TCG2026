#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_36 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(RE2OptionsTest_36, DefaultConstructorSetsOneLineFalse_36) {

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_36, SetOneLineTrueReflectsInGetter_36) {

    options.set_one_line(true);

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_36, SetOneLineFalseReflectsInGetter_36) {

    options.set_one_line(false);

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_36, CopyConstructorCopiesOneLineFlag_36) {

    Options original;

    original.set_one_line(true);

    Options copy(original);

    EXPECT_EQ(copy.one_line(), original.one_line());

}



TEST_F(RE2OptionsTest_36, CopyMethodCopiesOneLineFlag_36) {

    Options original;

    original.set_one_line(true);

    Options copy;

    copy.Copy(original);

    EXPECT_EQ(copy.one_line(), original.one_line());

}



TEST_F(RE2OptionsTest_36, DefaultConstructorInitializesMaxMemToDefault_36) {

    int64_t default_max_mem = kDefaultMaxMem; // Assuming kDefaultMaxMem is defined somewhere

    EXPECT_EQ(options.max_mem(), default_max_mem);

}



TEST_F(RE2OptionsTest_36, SetMaxMemReflectsInGetter_36) {

    int64_t test_value = 1024;

    options.set_max_mem(test_value);

    EXPECT_EQ(options.max_mem(), test_value);

}



TEST_F(RE2OptionsTest_36, DefaultConstructorInitializesEncodingToUTF8_36) {

    EXPECT_EQ(options.encoding(), EncodingUTF8);

}



TEST_F(RE2OptionsTest_36, SetEncodingReflectsInGetter_36) {

    options.set_encoding(EncodingLatin1);

    EXPECT_EQ(options.encoding(), EncodingLatin1);

}
