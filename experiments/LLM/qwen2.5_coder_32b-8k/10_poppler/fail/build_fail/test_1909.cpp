#include <gtest/gtest.h>

#include "Function.cc"



class PSStackTest : public ::testing::Test {

protected:

    PSStack stack;



    void SetUp() override {

        // Initialize the stack before each test

        stack.clear();

    }

};



TEST_F(PSStackTest_1909, PushReal_IncreasesCount_1909) {

    EXPECT_TRUE(stack.empty());

    stack.pushReal(3.14);

    EXPECT_FALSE(stack.empty());

}



TEST_F(PSStackTest_1909, PushReal_TopIsReal_1909) {

    stack.pushReal(3.14);

    EXPECT_TRUE(stack.topIsReal());

}



TEST_F(PSStackTest_1909, PushReal_ValueCorrect_1909) {

    double value = 2.71;

    stack.pushReal(value);

    EXPECT_EQ(value, stack.popNum());

}



TEST_F(PSStackTest_1909, PushReal_MultipleValues_1909) {

    stack.pushReal(3.14);

    stack.pushReal(2.71);

    EXPECT_FALSE(stack.empty());

    EXPECT_TRUE(stack.topIsReal());

    EXPECT_EQ(2.71, stack.popNum());

    EXPECT_EQ(3.14, stack.popNum());

}



TEST_F(PSStackTest_1909, PushReal_BoundaryCondition_EmptyAfterPop_1909) {

    stack.pushReal(3.14);

    stack.pop();

    EXPECT_TRUE(stack.empty());

}
