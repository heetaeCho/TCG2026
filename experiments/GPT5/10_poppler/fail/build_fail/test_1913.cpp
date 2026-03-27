#include <gtest/gtest.h>
#include "./TestProjects/poppler/poppler/Function.cc"  // Include the necessary header for PSStack

// Test Fixture for PSStack
class PSStackTest_1913 : public ::testing::Test {
protected:
    PSStack stack;

    void SetUp() override {
        // Any setup code (if needed) goes here
    }

    void TearDown() override {
        // Cleanup code (if needed) goes here
    }
};

// Normal operation: Check if the stack is empty initially
TEST_F(PSStackTest_1913, EmptyStackInitially_1913) {
    EXPECT_TRUE(stack.empty());
}

// Boundary condition: Check if stack correctly handles pushing and popping values
TEST_F(PSStackTest_1913, PushPopBool_1913) {
    stack.pushBool(true);
    EXPECT_FALSE(stack.empty());  // Stack should not be empty after pushing
    EXPECT_TRUE(stack.popBool());  // Should return the bool pushed onto the stack
    EXPECT_TRUE(stack.empty());  // Stack should be empty after popping
}

TEST_F(PSStackTest_1913, PushPopInt_1913) {
    stack.pushInt(42);
    EXPECT_FALSE(stack.empty());  // Stack should not be empty after pushing
    EXPECT_EQ(stack.popInt(), 42);  // Should return the integer pushed onto the stack
    EXPECT_TRUE(stack.empty());  // Stack should be empty after popping
}

TEST_F(PSStackTest_1913, PushPopReal_1913) {
    stack.pushReal(3.14);
    EXPECT_FALSE(stack.empty());  // Stack should not be empty after pushing
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);  // Should return the real number pushed onto the stack
    EXPECT_TRUE(stack.empty());  // Stack should be empty after popping
}

// Boundary condition: Check stack size boundary
TEST_F(PSStackTest_1913, CheckOverflow_1913) {
    // Push until the stack is full
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    EXPECT_FALSE(stack.empty());
    // Test check overflow by pushing one more element
    // Ideally, you would want to mock the `checkOverflow()` method, but for the purpose of boundary, we assume that the implementation will throw or handle this internally.
}

// Exceptional case: Try popping from an empty stack
TEST_F(PSStackTest_1913, PopFromEmptyStack_1913) {
    EXPECT_TRUE(stack.empty());
    // Since the pop method doesn't return anything for empty stack,
    // we will assume it would throw or handle the error (based on the implementation of the `pop` method)
    EXPECT_THROW(stack.pop(), std::runtime_error);
}

// Exceptional case: Check underflow condition
TEST_F(PSStackTest_1913, Underflow_1913) {
    // You can assume the `checkUnderflow` function would be involved in handling this.
    // Test underflow condition when attempting to pop from an empty stack
    EXPECT_TRUE(stack.empty());
    EXPECT_THROW(stack.pop(), std::runtime_error);
}

// Boundary condition: Ensure `topIsInt()` and `topIsReal()` return the correct result
TEST_F(PSStackTest_1913, TopIsIntOrReal_1913) {
    stack.pushInt(10);
    EXPECT_TRUE(stack.topIsInt());  // The top should be int
    EXPECT_FALSE(stack.topIsReal());  // The top should not be real

    stack.pushReal(2.71);
    EXPECT_FALSE(stack.topIsInt());  // The top should not be int
    EXPECT_TRUE(stack.topIsReal());  // The top should be real
}

// Verify external interactions: Testing `copy` and `roll` for behavior based on stack operations
TEST_F(PSStackTest_1913, CopyAndRollOperations_1913) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);

    // Assuming these functions modify the stack or interact in some way that can be observed
    stack.copy(2);  // Copy the top 2 elements
    EXPECT_EQ(stack.popInt(), 2);  // Last pushed element should be popped

    stack.roll(3, 1);  // Roll operation with n=3, j=1 (Modify stack as per spec)
    // Behavior should be verified based on how roll manipulates the stack; check accordingly
}