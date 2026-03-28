#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/Function.cc"

class PSStackTest_1912 : public ::testing::Test {
protected:
    PSStack stack;

    void SetUp() override {
        // You may initialize the stack or perform any other necessary setup here
    }
};

TEST_F(PSStackTest_1912, PopNum_SuccessfulPopInt_1912) {
    stack.pushInt(10);
    double result = stack.popNum();
    EXPECT_EQ(result, 10.0);  // Ensure the popped value is 10 as double
}

TEST_F(PSStackTest_1912, PopNum_SuccessfulPopReal_1912) {
    stack.pushReal(3.14);
    double result = stack.popNum();
    EXPECT_EQ(result, 3.14);  // Ensure the popped value is 3.14 as double
}

TEST_F(PSStackTest_1912, PopNum_Underflow_1912) {
    double result = stack.popNum();
    EXPECT_EQ(result, 0.0);  // Should return 0 in case of underflow
}

TEST_F(PSStackTest_1912, PopNum_TypeMismatch_1912) {
    stack.pushBool(true);
    double result = stack.popNum();
    EXPECT_EQ(result, 0.0);  // Should return 0 in case of type mismatch
}

TEST_F(PSStackTest_1912, PushAndPopInt_1912) {
    stack.pushInt(42);
    int result = stack.popInt();
    EXPECT_EQ(result, 42);  // Ensure that the popped value is the correct integer
}

TEST_F(PSStackTest_1912, PushAndPopBool_1912) {
    stack.pushBool(true);
    bool result = stack.popBool();
    EXPECT_TRUE(result);  // Ensure that the popped boolean is correct
}

TEST_F(PSStackTest_1912, StackEmptyAfterPop_1912) {
    stack.pushInt(100);
    stack.pop();
    EXPECT_TRUE(stack.empty());  // Ensure that the stack is empty after popping
}

TEST_F(PSStackTest_1912, TopIsIntTrue_1912) {
    stack.pushInt(5);
    EXPECT_TRUE(stack.topIsInt());  // Ensure that topIsInt returns true when the top is an integer
}

TEST_F(PSStackTest_1912, TopIsRealFalse_1912) {
    stack.pushInt(5);
    EXPECT_FALSE(stack.topIsReal());  // Ensure that topIsReal returns false for an integer on top
}

TEST_F(PSStackTest_1912, TopTwoAreIntsTrue_1912) {
    stack.pushInt(10);
    stack.pushInt(20);
    EXPECT_TRUE(stack.topTwoAreInts());  // Ensure that topTwoAreInts returns true for two integers
}

TEST_F(PSStackTest_1912, TopTwoAreIntsFalse_1912) {
    stack.pushInt(10);
    stack.pushReal(20.0);
    EXPECT_FALSE(stack.topTwoAreInts());  // Ensure that topTwoAreInts returns false when one is not an integer
}

TEST_F(PSStackTest_1912, CheckOverflow_1912) {
    // Assuming the stack has a max size of 100 elements
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    EXPECT_FALSE(stack.checkOverflow(1));  // No overflow expected yet

    stack.pushInt(101);  // This should cause overflow
    EXPECT_TRUE(stack.checkOverflow(1));  // Overflow should be detected now
}

TEST_F(PSStackTest_1912, CheckUnderflow_1912) {
    stack.pushInt(1);
    stack.pop();  // Remove the element
    EXPECT_TRUE(stack.checkUnderflow());  // Underflow should be detected after popping the only element
}

TEST_F(PSStackTest_1912, CopyTest_1912) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.copy(1);  // Copy the top 1 element
    int result = stack.popInt();
    EXPECT_EQ(result, 20);  // Ensure that the copied element is the top of the stack
}

TEST_F(PSStackTest_1912, RollTest_1912) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 1);  // Roll the top 3 elements by 1 position
    int result = stack.popInt();
    EXPECT_EQ(result, 1);  // Ensure the order of elements is correct after roll
}

TEST_F(PSStackTest_1912, ClearTest_1912) {
    stack.pushInt(1);
    stack.pushReal(3.14);
    stack.clear();
    EXPECT_TRUE(stack.empty());  // Ensure the stack is empty after clearing
}