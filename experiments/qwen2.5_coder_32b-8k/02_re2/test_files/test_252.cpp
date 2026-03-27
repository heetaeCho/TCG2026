#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2Test_252 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(RE2Test_252, FullMatchN_ValidPatternAndText_252) {

    RE2 re("hello");

    const char* text = "hello";

    EXPECT_TRUE(FullMatchN(text, re, nullptr, 0));

}



TEST_F(RE2Test_252, FullMatchN_EmptyTextWithEmptyPattern_252) {

    RE2 re("");

    const char* text = "";

    EXPECT_TRUE(FullMatchN(text, re, nullptr, 0));

}



TEST_F(RE2Test_252, FullMatchN_MismatchedPatternAndText_252) {

    RE2 re("hello");

    const char* text = "world";

    EXPECT_FALSE(FullMatchN(text, re, nullptr, 0));

}



TEST_F(RE2Test_252, FullMatchN_NullPattern_252) {

    RE2 re(nullptr);

    const char* text = "hello";

    EXPECT_FALSE(FullMatchN(text, re, nullptr, 0));

}



TEST_F(RE2Test_252, FullMatchN_ArgsProvided_252) {

    int num;

    RE2::Arg arg(&num);

    RE2 re("(\\d+)");

    const char* text = "123";

    const RE2::Arg* args[] = { &arg };

    EXPECT_TRUE(FullMatchN(text, re, args, 1));

    EXPECT_EQ(num, 123);

}



TEST_F(RE2Test_252, FullMatchN_ZeroArgsProvided_252) {

    RE2 re("(\\d+)");

    const char* text = "123";

    EXPECT_TRUE(FullMatchN(text, re, nullptr, 0));

}



TEST_F(RE2Test_252, FullMatchN_InvalidPattern_252) {

    RE2 re("[");

    const char* text = "hello";

    EXPECT_FALSE(FullMatchN(text, re, nullptr, 0));

}



TEST_F(RE2Test_252, FullMatchN_BoundaryCondition_EmptyTextNonEmptyPattern_252) {

    RE2 re("a");

    const char* text = "";

    EXPECT_FALSE(FullMatchN(text, re, nullptr, 0));

}



TEST_F(RE2Test_252, FullMatchN_BoundaryCondition_NonEmptyTextEmptyPattern_252) {

    RE2 re("");

    const char* text = "a";

    EXPECT_TRUE(FullMatchN(text, re, nullptr, 0));

}
