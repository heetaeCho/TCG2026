#include <gtest/gtest.h>

#include "Function.cc"



class PSStackTest_1911 : public ::testing::Test {

protected:

    PSStack stack;



    void SetUp() override {

        // Clear the stack before each test

        stack.clear();

    }

};



TEST_F(PSStackTest_1911, PopInt_ReturnsZeroOnEmptyStack_1911) {

    EXPECT_EQ(stack.popInt(), 0);

}



TEST_F(PSStackTest_1911, PopInt_ReturnsCorrectValueAfterPushInt_1911) {

    stack.pushInt(42);

    EXPECT_EQ(stack.popInt(), 42);

}



TEST_F(PSStackTest_1911, PopInt_ReturnsZeroOnTypeMismatch_1911) {

    stack.pushBool(true);

    EXPECT_EQ(stack.popInt(), 0);

}



TEST_F(PSStackTest_1911, PopInt_HandlesMultiplePushesAndPopsCorrectly_1911) {

    stack.pushInt(10);

    stack.pushInt(20);

    EXPECT_EQ(stack.popInt(), 20);

    EXPECT_EQ(stack.popInt(), 10);

}



TEST_F(PSStackTest_1911, PopInt_ReturnsZeroOnUnderflowAfterClear_1911) {

    stack.pushInt(30);

    stack.clear();

    EXPECT_EQ(stack.popInt(), 0);

}
