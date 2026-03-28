#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/Function.cc"  // Adjust path as necessary

// Mocked external collaborator, if necessary
// class MockHandler {
//     MOCK_METHOD(void, handle, (int param), ());
// };

class PSStackTest_1916 : public ::testing::Test {
protected:
    PSStack stack;

    // You can add common setup here if needed
    // void SetUp() override { ... }
};

// Test for normal operation: pushing and popping boolean values
TEST_F(PSStackTest_1916, PushPopBool_1916) {
    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());  // Expected to pop the boolean value `true`
}

// Test for normal operation: pushing and popping integer values
TEST_F(PSStackTest_1916, PushPopInt_1916) {
    stack.pushInt(42);
    EXPECT_EQ(stack.popInt(), 42);  // Expected to pop the integer value `42`
}

// Test for normal operation: pushing and popping real (double) values
TEST_F(PSStackTest_1916, PushPopReal_1916) {
    stack.pushReal(3.14);
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);  // Expected to pop the real value `3.14`
}

// Test for boundary condition: checking if stack is empty after popping all elements
TEST_F(PSStackTest_1916, EmptyStackAfterPop_1916) {
    stack.pushInt(1);
    stack.pushBool(true);
    stack.popInt();
    stack.popBool();
    EXPECT_TRUE(stack.empty());  // Expected to be empty after popping all elements
}

// Test for boundary condition: checking the size of stack exceeds the limit
TEST_F(PSStackTest_1916, StackOverflow_1916) {
    EXPECT_NO_THROW(stack.pushInt(1));  // Test pushing an element
    // Push enough elements to test boundary condition
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    EXPECT_FALSE(stack.pushInt(101));  // Should not overflow the stack
}

// Test for exceptional condition: popping from an empty stack
TEST_F(PSStackTest_1916, PopFromEmptyStack_1916) {
    EXPECT_THROW(stack.popInt(), std::underflow_error);  // Should throw underflow error when popping from an empty stack
}

// Test for boundary condition: topIsReal should be true when the top element is a real number
TEST_F(PSStackTest_1916, TopIsReal_1916) {
    stack.pushReal(1.23);
    EXPECT_TRUE(stack.topIsReal());  // Should return true since top is a real number
}

// Test for boundary condition: topIsReal should be false when the top element is not a real number
TEST_F(PSStackTest_1916, TopIsRealFalse_1916) {
    stack.pushInt(5);
    EXPECT_FALSE(stack.topIsReal());  // Should return false since top is an integer
}

// Test for exceptional condition: underflow when checking the top of an empty stack
TEST_F(PSStackTest_1916, TopOfEmptyStack_1916) {
    EXPECT_THROW(stack.topIsReal(), std::underflow_error);  // Should throw underflow error when checking the top of an empty stack
}

// Test for normal operation: copy operation
TEST_F(PSStackTest_1916, CopyOperation_1916) {
    stack.pushInt(10);
    stack.copy(1);  // Copy the top element
    EXPECT_EQ(stack.popInt(), 10);  // Should pop the copied value `10`
}

// Test for normal operation: roll operation
TEST_F(PSStackTest_1916, RollOperation_1916) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 1);  // Roll top 3 elements with a distance of 1
    EXPECT_EQ(stack.popInt(), 2);  // The rolled value should be 2
    EXPECT_EQ(stack.popInt(), 3);  // Then, the next should be 3
}

// Test for boundary condition: checking if topTwoAreInts works correctly
TEST_F(PSStackTest_1916, TopTwoAreInts_1916) {
    stack.pushInt(5);
    stack.pushInt(10);
    EXPECT_TRUE(stack.topTwoAreInts());  // Should return true since both top two elements are integers
}

// Test for exceptional condition: check type mismatch during checkType call
TEST_F(PSStackTest_1916, CheckTypeMismatch_1916) {
    stack.pushBool(true);
    stack.pushInt(10);
    EXPECT_FALSE(stack.checkType(psBool, psInt));  // Should return false since the types don't match
}

// Test for verifying external interaction: mock external interaction if applicable
// TEST_F(PSStackTest_1916, MockExternalInteraction_1916) {
//     MockHandler mockHandler;
//     EXPECT_CALL(mockHandler, handle(1));
//     stack.pushInt(1);  // Simulating interaction
//     mockHandler.handle(1);  // Verify that the handle method is called as expected
// }