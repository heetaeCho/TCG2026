#include <gtest/gtest.h>

#include "Function.cc"  // Assuming the header file is included here



class PSStackTest_1919 : public ::testing::Test {

protected:

    PSStack stack;



    void SetUp() override {

        // Initialize the stack if necessary

        stack.clear();

    }

};



TEST_F(PSStackTest_1919, PopOnEmptyStack_1919) {

    // Test popping from an empty stack should not change the state

    stack.pop();

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1919, PushAndPop_1919) {

    // Test normal operation of push and pop

    stack.pushInt(42);

    EXPECT_FALSE(stack.empty());



    int value = stack.popInt();

    EXPECT_EQ(value, 42);

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1919, PopMultipleElements_1919) {

    // Test popping multiple elements

    stack.pushInt(10);

    stack.pushBool(true);

    stack.pushReal(3.14);



    EXPECT_FALSE(stack.empty());



    double real = stack.popNum();

    bool boolean = stack.popBool();

    int integer = stack.popInt();



    EXPECT_EQ(real, 3.14);

    EXPECT_TRUE(boolean);

    EXPECT_EQ(integer, 10);

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1919, PopAfterClear_1919) {

    // Test popping after clearing the stack

    stack.pushInt(20);

    stack.clear();

    EXPECT_TRUE(stack.empty());



    stack.pop();  // Should not throw or change state

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1919, PushAndCheckEmpty_1919) {

    // Test pushing and checking if the stack is empty

    stack.pushInt(5);

    EXPECT_FALSE(stack.empty());



    stack.pop();

    EXPECT_TRUE(stack.empty());

}
