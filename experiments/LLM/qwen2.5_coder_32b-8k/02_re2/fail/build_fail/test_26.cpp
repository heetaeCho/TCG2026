#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_26 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(RE2OptionsTest_26, DefaultConstructorInitializesDotNlToFalse_26) {

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_26, SetDotNlChangesValue_26) {

    options.set_dot_nl(true);

    EXPECT_TRUE(options.dot_nl());



    options.set_dot_nl(false);

    EXPECT_FALSE(options.dot_nl());

}



TEST_F(RE2OptionsTest_26, DotNlIsFalseAfterCopyFromDefault_26) {

    Options src;

    Options dest;



    dest.Copy(src);

    EXPECT_FALSE(dest.dot_nl());

}



TEST_F(RE2OptionsTest_26, DotNlIsTrueAfterCopyingModifiedSource_26) {

    Options src;

    Options dest;



    src.set_dot_nl(true);

    dest.Copy(src);

    EXPECT_TRUE(dest.dot_nl());

}



TEST_F(RE2OptionsTest_26, ParseFlagsDoesNotAffectDotNl_26) {

    options.set_dot_nl(true);

    int flags = options.ParseFlags();

    (void)flags;  // Suppress unused variable warning

    EXPECT_TRUE(options.dot_nl());



    options.set_dot_nl(false);

    flags = options.ParseFlags();

    EXPECT_FALSE(options.dot_nl());

}
