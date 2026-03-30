#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class RegexpTest_345 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(RegexpTest_345, RepeatCreatesValidObject_345) {

    Regexp* sub = new Regexp(kRegexpLiteral, 0);

    Regexp* repeat = Regexp::Repeat(sub, 0, 1, 2);



    EXPECT_EQ(repeat->op(), kRegexpRepeat);

    EXPECT_EQ(repeat->min(), 1);

    EXPECT_EQ(repeat->max(), 2);

    EXPECT_EQ(repeat->sub()[0], sub);



    repeat->Decref();

}



TEST_F(RegexpTest_345, RepeatMinBoundary_345) {

    Regexp* sub = new Regexp(kRegexpLiteral, 0);

    Regexp* repeat = Regexp::Repeat(sub, 0, 0, 1);



    EXPECT_EQ(repeat->op(), kRegexpRepeat);

    EXPECT_EQ(repeat->min(), 0);

    EXPECT_EQ(repeat->max(), 1);



    repeat->Decref();

}



TEST_F(RegexpTest_345, RepeatMaxBoundary_345) {

    Regexp* sub = new Regexp(kRegexpLiteral, 0);

    Regexp* repeat = Regexp::Repeat(sub, 0, 2, 2);



    EXPECT_EQ(repeat->op(), kRegexpRepeat);

    EXPECT_EQ(repeat->min(), 2);

    EXPECT_EQ(repeat->max(), 2);



    repeat->Decref();

}



TEST_F(RegexpTest_345, RepeatSubPointerValidity_345) {

    Regexp* sub = new Regexp(kRegexpLiteral, 0);

    Regexp* repeat = Regexp::Repeat(sub, 0, 1, 2);



    EXPECT_EQ(repeat->sub()[0], sub);



    repeat->Decref();

}



TEST_F(RegexpTest_345, RepeatWithZeroSubPointer_345) {

    Regexp* sub = nullptr;

    Regexp* repeat = Regexp::Repeat(sub, 0, 1, 2);



    EXPECT_EQ(repeat->op(), kRegexpRepeat);

    EXPECT_EQ(repeat->min(), 1);

    EXPECT_EQ(repeat->max(), 2);

    EXPECT_EQ(repeat->sub()[0], sub);



    repeat->Decref();

}



TEST_F(RegexpTest_345, RepeatWithNegativeMinAndMax_345) {

    Regexp* sub = new Regexp(kRegexpLiteral, 0);

    EXPECT_DEATH(Regexp::Repeat(sub, 0, -1, -2), "");



    sub->Decref();

}
