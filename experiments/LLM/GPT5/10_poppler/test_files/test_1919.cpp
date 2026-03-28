#include <gtest/gtest.h>
#include "./TestProjects/poppler/poppler/Function.cc"  // Include the relevant header or source file

// Mocking any dependencies (if needed)
// In this case, there are no external dependencies that need to be mocked.

class PSStackTest_1919 : public ::testing::Test {
protected:
    PSStack stack;

    void SetUp() override {
        // Optional: Set up the stack if necessary.
    }

    void TearDown() override {
        // Optional: Clean up after tests if necessary.
    }
};

// Normal operation tests

TEST_F(PSStackTest_1919, PushBoolAddsBool_1919) {
    stack.pushBool(true);
    EXPECT_TRUE(stack.topIsBool());
}

TEST_F(PSStackTest_1919, PushIntAddsInt_1919) {
    stack.pushInt(42);
    EXPECT_TRUE(stack.topIsInt());
}

TEST_F(PSStackTest_1919, PushRealAddsReal_1919) {
    stack.pushReal(3.14);
    EXPECT_TRUE(stack.topIsReal());
}

TEST_F(PSStackTest_1919, PopBoolReturnsBool_1919) {
    stack.pushBool(false);
    bool value = stack.popBool();
    EXPECT_EQ(value, false);
}

TEST_F(PSStackTest_1919, PopIntReturnsInt_1919) {
    stack.pushInt(10);
    int value = stack.popInt();
    EXPECT_EQ(value, 10);
}

TEST_F(PSStackTest_1919, PopNumReturnsReal_1919) {
    stack.pushReal(9.99);
    double value = stack.popNum();
    EXPECT_EQ(value, 9.99);
}

// Boundary tests

TEST_F(PSStackTest_1919, StackOverflowCheck_1919) {
    // Assuming the stack has a max size of 100
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    // This should fail the overflow check, but based on the interface, 
    // we need to check behavior when stack is at max capacity.
    EXPECT_FALSE(stack.checkOverflow());
}

TEST_F(PSStackTest_1919, StackUnderflowCheck_1919) {
    // Trying to pop from an empty stack should cause underflow
    stack.clear();
    EXPECT_THROW(stack.pop(), std::underflow_error);
}

// Exceptional or error case tests

TEST_F(PSStackTest_1919, PopFromEmptyStackThrows_1919) {
    stack.clear();
    EXPECT_THROW(stack.popBool(), std::underflow_error);  // Should throw underflow error
    EXPECT_THROW(stack.popInt(), std::underflow_error);   // Should throw underflow error
    EXPECT_THROW(stack.popNum(), std::underflow_error);   // Should throw underflow error
}

// Verification of external interactions (mock handler calls)

TEST_F(PSStackTest_1919, CheckTopIsInt_1919) {
    stack.pushInt(100);
    EXPECT_TRUE(stack.topIsInt());
    EXPECT_FALSE(stack.topIsReal());
}

// Boundary condition tests for stack operations

TEST_F(PSStackTest_1919, PushMultipleTypes_1919) {
    stack.pushInt(10);
    stack.pushReal(3.14);
    stack.pushBool(true);

    EXPECT_TRUE(stack.topIsBool());
    stack.popBool();

    EXPECT_TRUE(stack.topIsReal());
    stack.popNum();

    EXPECT_TRUE(stack.topIsInt());
    stack.popInt();
}

// Helper functions (if needed)

TEST_F(PSStackTest_1919, CheckOverflowForMultiplePush_1919) {
    // Add more elements to the stack and check overflow.
    for (int i = 0; i < 105; ++i) {
        stack.pushInt(i);
    }
    EXPECT_TRUE(stack.checkOverflow());
}

TEST_F(PSStackTest_1919, CheckUnderflowForPop_1919) {
    stack.clear();
    EXPECT_FALSE(stack.checkUnderflow());
}