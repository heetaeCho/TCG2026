#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/Function.cc"

class PSStackTest_1915 : public ::testing::Test {
protected:
    PSStack stack;

    void SetUp() override {
        // Initialize any setup for PSStack if necessary
    }

    void TearDown() override {
        // Clean up any resources after each test
    }
};

// Test normal operation of topTwoAreInts when stack has two integers
TEST_F(PSStackTest_1915, topTwoAreInts_NormalOperation_1915) {
    stack.pushInt(10);
    stack.pushInt(20);
    EXPECT_TRUE(stack.topTwoAreInts());
}

// Test boundary case when stack has fewer than two elements
TEST_F(PSStackTest_1915, topTwoAreInts_BoundaryCondition_FewerThanTwo_1915) {
    stack.pushInt(10);
    EXPECT_FALSE(stack.topTwoAreInts());  // Only one element, cannot be two integers
}

// Test boundary case when stack has no elements
TEST_F(PSStackTest_1915, topTwoAreInts_BoundaryCondition_EmptyStack_1915) {
    EXPECT_FALSE(stack.topTwoAreInts());  // No elements, cannot be two integers
}

// Test normal operation of pushing and popping integers
TEST_F(PSStackTest_1915, PushPopInt_NormalOperation_1915) {
    stack.pushInt(42);
    EXPECT_EQ(stack.popInt(), 42);
}

// Test exceptional case when attempting to pop from an empty stack
TEST_F(PSStackTest_1915, PopInt_ExceptionalCase_EmptyStack_1915) {
    EXPECT_THROW(stack.popInt(), std::out_of_range);  // Should throw exception due to empty stack
}

// Test normal operation of checking if the top element is an integer
TEST_F(PSStackTest_1915, topIsInt_NormalOperation_1915) {
    stack.pushInt(42);
    EXPECT_TRUE(stack.topIsInt());  // The top element is an integer
}

// Test boundary condition when top element is not an integer
TEST_F(PSStackTest_1915, topIsInt_BoundaryCondition_NotInt_1915) {
    stack.pushReal(3.14);
    EXPECT_FALSE(stack.topIsInt());  // The top element is not an integer
}

// Test exceptional case when attempting to perform operations on an empty stack
TEST_F(PSStackTest_1915, PopBool_ExceptionalCase_EmptyStack_1915) {
    EXPECT_THROW(stack.popBool(), std::out_of_range);  // Should throw exception due to empty stack
}

// Test verification of external interactions if there were any (none provided in the prompt)
TEST_F(PSStackTest_1915, VerifyExternalInteractions_1915) {
    // Mock behavior could be tested here if the class had external interactions (e.g., mock dependencies)
    // However, since this class doesn't involve external dependencies, no test is included
}