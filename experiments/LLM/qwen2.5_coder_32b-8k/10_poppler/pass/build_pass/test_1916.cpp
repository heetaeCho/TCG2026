#include <gtest/gtest.h>

#include "Function.cc" // Assuming header file with class and enum definitions



class PSStackTest_1916 : public ::testing::Test {

protected:

    PSStack* stack;



    void SetUp() override {

        stack = new PSStack();

    }



    void TearDown() override {

        delete stack;

    }

};



TEST_F(PSStackTest_1916, TopIsReal_EmptyStack_False_1916) {

    EXPECT_FALSE(stack->topIsReal());

}



TEST_F(PSStackTest_1916, TopIsReal_TopIsBool_False_1916) {

    stack->pushBool(true);

    EXPECT_FALSE(stack->topIsReal());

}



TEST_F(PSStackTest_1916, TopIsReal_TopIsInt_False_1916) {

    stack->pushInt(42);

    EXPECT_FALSE(stack->topIsReal());

}



TEST_F(PSStackTest_1916, TopIsReal_TopIsReal_True_1916) {

    stack->pushReal(3.14);

    EXPECT_TRUE(stack->topIsReal());

}



TEST_F(PSStackTest_1916, TopIsReal_TopTwoAreReal_SecondTopIsReal_True_1916) {

    stack->pushReal(2.71);

    stack->pushReal(3.14);

    stack->popNum(); // Remove top real

    EXPECT_TRUE(stack->topIsReal());

}



TEST_F(PSStackTest_1916, TopIsReal_TopTwoAreReal_SecondTopIsNotReal_False_1916) {

    stack->pushInt(42);

    stack->pushReal(3.14);

    stack->popNum(); // Remove top real

    EXPECT_FALSE(stack->topIsReal());

}
