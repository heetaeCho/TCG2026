#include <gtest/gtest.h>
#include "./TestProjects/poppler/poppler/Function.cc"  // Include the necessary header for PSStack

// Test Fixture for PSStack class
class PSStackTest_1914 : public ::testing::Test {
protected:
    PSStack stack;

    void SetUp() override {
        // Setup code to initialize the stack before each test, if necessary
    }

    void TearDown() override {
        // Cleanup code after each test, if needed
    }
};

// Test for normal operation: pushInt and popInt
TEST_F(PSStackTest_1914, PushIntPopInt_1914) {
    stack.pushInt(10); // Push an integer onto the stack
    EXPECT_EQ(stack.popInt(), 10); // Verify that popping gives the correct value
}

// Test for normal operation: pushBool and popBool
TEST_F(PSStackTest_1914, PushBoolPopBool_1914) {
    stack.pushBool(true); // Push a boolean onto the stack
    EXPECT_EQ(stack.popBool(), true); // Verify that popping gives the correct value
}

// Test for checking if the top element is an integer
TEST_F(PSStackTest_1914, TopIsInt_1914) {
    stack.pushInt(5); // Push an integer
    EXPECT_TRUE(stack.topIsInt()); // Verify that topIsInt returns true
    stack.pushReal(3.14); // Push a real number
    EXPECT_FALSE(stack.topIsInt()); // Verify that topIsInt returns false for non-integer types
}

// Test for boundary condition: checking stack overflow
TEST_F(PSStackTest_1914, StackOverflow_1914) {
    // Push beyond the stack size (psStackSize is defined as 100)
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    EXPECT_FALSE(stack.topIsInt()); // Assuming there's no more space and the topIsInt returns false on overflow
}

// Test for boundary condition: checking stack underflow
TEST_F(PSStackTest_1914, StackUnderflow_1914) {
    // Assuming the stack is empty at the start
    EXPECT_THROW(stack.popInt(), std::out_of_range); // Popping from an empty stack should throw an exception
}

// Test for normal operation: pushReal and popNum
TEST_F(PSStackTest_1914, PushRealPopNum_1914) {
    stack.pushReal(3.14); // Push a real number onto the stack
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14); // Verify that popping gives the correct value (double precision)
}

// Test for boundary case: topTwoAreInts with two integers
TEST_F(PSStackTest_1914, TopTwoAreInts_1914) {
    stack.pushInt(1); // Push first integer
    stack.pushInt(2); // Push second integer
    EXPECT_TRUE(stack.topTwoAreInts()); // Verify that topTwoAreInts returns true
}

// Test for boundary case: topTwoAreInts with one non-integer
TEST_F(PSStackTest_1914, TopTwoAreIntsFail_1914) {
    stack.pushInt(1); // Push an integer
    stack.pushReal(3.14); // Push a real number
    EXPECT_FALSE(stack.topTwoAreInts()); // Verify that topTwoAreInts returns false
}

// Test for exceptional case: check for underflow when popping more than the stack size
TEST_F(PSStackTest_1914, PopFromEmptyStack_1914) {
    EXPECT_THROW(stack.pop(), std::out_of_range); // Trying to pop from an empty stack should throw an exception
}

// Test for normal operation: clear the stack
TEST_F(PSStackTest_1914, ClearStack_1914) {
    stack.pushInt(1); // Push an integer
    stack.pushReal(2.5); // Push a real number
    stack.clear(); // Clear the stack
    EXPECT_TRUE(stack.empty()); // Verify that the stack is empty after clearing
}

// Test for verifying external interaction (if mock dependencies were involved, such as handlers)
TEST_F(PSStackTest_1914, VerifyHandlerCalls_1914) {
    // This test would mock an external collaborator (e.g., a callback) if needed
    // Here we demonstrate that external interactions (e.g., handler calls) could be verified
    // For this example, you could mock a handler and verify its invocation
    // Example: EXPECT_CALL(mockHandler, someMethod()).Times(1);
}