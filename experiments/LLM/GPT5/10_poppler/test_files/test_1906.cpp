#include <gtest/gtest.h>
#include "Function.h"

class PSStackTest_1906 : public ::testing::Test {
protected:
    PSStack psStack;

    PSStackTest_1906() {
        // You can initialize the PSStack here if needed
    }
};

// Test the `clear` function to ensure the stack pointer resets to the size of the stack
TEST_F(PSStackTest_1906, Clear_ResetsStackPointer_1906) {
    psStack.pushInt(10);
    psStack.clear();
    // After clearing, the stack pointer should be reset (assuming sp is publicly accessible or tested indirectly)
    ASSERT_EQ(psStack.empty(), true);
}

// Test the `pushInt` function and check if an integer is correctly pushed onto the stack
TEST_F(PSStackTest_1906, PushInt_Success_1906) {
    psStack.pushInt(42);
    ASSERT_EQ(psStack.popInt(), 42);
}

// Test the `pushBool` function and check if a boolean is correctly pushed onto the stack
TEST_F(PSStackTest_1906, PushBool_Success_1906) {
    psStack.pushBool(true);
    ASSERT_EQ(psStack.popBool(), true);
}

// Test the `pushReal` function and check if a real number is correctly pushed onto the stack
TEST_F(PSStackTest_1906, PushReal_Success_1906) {
    psStack.pushReal(3.14);
    ASSERT_EQ(psStack.popNum(), 3.14);
}

// Test the `popInt` function to ensure it pops the correct integer value from the stack
TEST_F(PSStackTest_1906, PopInt_Success_1906) {
    psStack.pushInt(10);
    ASSERT_EQ(psStack.popInt(), 10);
}

// Test the `popBool` function to ensure it pops the correct boolean value from the stack
TEST_F(PSStackTest_1906, PopBool_Success_1906) {
    psStack.pushBool(true);
    ASSERT_EQ(psStack.popBool(), true);
}

// Test the `popNum` function to ensure it pops the correct real value from the stack
TEST_F(PSStackTest_1906, PopNum_Success_1906) {
    psStack.pushReal(5.67);
    ASSERT_EQ(psStack.popNum(), 5.67);
}

// Test `empty` function to ensure the stack is empty after a clear
TEST_F(PSStackTest_1906, Empty_AfterClear_1906) {
    psStack.pushInt(100);
    psStack.clear();
    ASSERT_TRUE(psStack.empty());
}

// Test `empty` function when the stack is not empty
TEST_F(PSStackTest_1906, Empty_WhenNotEmpty_1906) {
    psStack.pushInt(10);
    ASSERT_FALSE(psStack.empty());
}

// Test `checkOverflow` and `checkUnderflow` by pushing beyond the stack size
TEST_F(PSStackTest_1906, Overflow_Underflow_1906) {
    // Push to overflow
    for (int i = 0; i < 100; i++) {
        psStack.pushInt(i);
    }
    // The stack is now full, push one more should cause an overflow
    ASSERT_THROW(psStack.pushInt(101), std::overflow_error);

    // Clear the stack and test underflow
    psStack.clear();
    // Pop from an empty stack should cause underflow
    ASSERT_THROW(psStack.popInt(), std::underflow_error);
}

// Test `topIsInt` to check if the top of the stack is an integer
TEST_F(PSStackTest_1906, TopIsInt_True_1906) {
    psStack.pushInt(123);
    ASSERT_TRUE(psStack.topIsInt());
}

// Test `topIsInt` when top of the stack is not an integer
TEST_F(PSStackTest_1906, TopIsInt_False_1906) {
    psStack.pushReal(3.14);
    ASSERT_FALSE(psStack.topIsInt());
}

// Test `topIsReal` to check if the top of the stack is a real number
TEST_F(PSStackTest_1906, TopIsReal_True_1906) {
    psStack.pushReal(3.14);
    ASSERT_TRUE(psStack.topIsReal());
}

// Test `topIsReal` when top of the stack is not a real number
TEST_F(PSStackTest_1906, TopIsReal_False_1906) {
    psStack.pushInt(5);
    ASSERT_FALSE(psStack.topIsReal());
}

// Test `topTwoAreInts` when the top two items are integers
TEST_F(PSStackTest_1906, TopTwoAreInts_True_1906) {
    psStack.pushInt(1);
    psStack.pushInt(2);
    ASSERT_TRUE(psStack.topTwoAreInts());
}

// Test `topTwoAreInts` when the top two items are not both integers
TEST_F(PSStackTest_1906, TopTwoAreInts_False_1906) {
    psStack.pushInt(1);
    psStack.pushReal(3.14);
    ASSERT_FALSE(psStack.topTwoAreInts());
}

// Test exceptional case for `popInt` when the stack is empty
TEST_F(PSStackTest_1906, PopInt_ThrowsWhenEmpty_1906) {
    ASSERT_THROW(psStack.popInt(), std::underflow_error);
}