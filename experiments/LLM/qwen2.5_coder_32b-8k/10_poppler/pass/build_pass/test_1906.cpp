#include <gtest/gtest.h>

#include "Function.cc" // Assuming PSStack is defined in this file



class PSStackTest_1906 : public ::testing::Test {

protected:

    PSStack stack;



    void SetUp() override {

        stack.clear();  // Reset the stack for each test

    }

};



TEST_F(PSStackTest_1906, ClearResetsStackPointer_1906) {

    // Push some elements onto the stack

    stack.pushInt(42);

    stack.pushBool(true);



    // Clear the stack

    stack.clear();



    // Attempt to pop an element should fail as the stack is empty

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1906, PushPopIntegers_1906) {

    stack.pushInt(42);

    stack.pushInt(7);



    EXPECT_EQ(7, stack.popInt());

    EXPECT_EQ(42, stack.popInt());

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1906, PushPopBooleans_1906) {

    stack.pushBool(true);

    stack.pushBool(false);



    EXPECT_FALSE(stack.popBool());

    EXPECT_TRUE(stack.popBool());

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1906, PushPopReals_1906) {

    stack.pushReal(3.14);

    stack.pushReal(2.71);



    EXPECT_DOUBLE_EQ(2.71, stack.popNum());

    EXPECT_DOUBLE_EQ(3.14, stack.popNum());

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1906, EmptyCheckOnEmptyStack_1906) {

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1906, EmptyCheckAfterPush_1906) {

    stack.pushInt(42);

    EXPECT_FALSE(stack.empty());

}



TEST_F(PSStackTest_1906, TopIsIntWhenTopIsInteger_1906) {

    stack.pushInt(42);

    EXPECT_TRUE(stack.topIsInt());

}



TEST_F(PSStackTest_1906, TopIsNotIntWhenTopIsBoolean_1906) {

    stack.pushBool(true);

    EXPECT_FALSE(stack.topIsInt());

}



TEST_F(PSStackTest_1906, TopTwoAreIntsWhenTopTwoAreIntegers_1906) {

    stack.pushInt(42);

    stack.pushInt(7);

    EXPECT_TRUE(stack.topTwoAreInts());

}



TEST_F(PSStackTest_1906, TopTwoAreNotIntsWhenTopIsBoolean_1906) {

    stack.pushBool(true);

    stack.pushInt(42);

    EXPECT_FALSE(stack.topTwoAreInts());

}



TEST_F(PSStackTest_1906, TopIsRealWhenTopIsDouble_1906) {

    stack.pushReal(3.14);

    EXPECT_TRUE(stack.topIsReal());

}



TEST_F(PSStackTest_1906, TopTwoAreNumsWhenTopTwoAreNumbers_1906) {

    stack.pushInt(42);

    stack.pushReal(3.14);

    EXPECT_TRUE(stack.topTwoAreNums());

}
