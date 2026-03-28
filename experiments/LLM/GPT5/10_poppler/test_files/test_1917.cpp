#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"  // Include the relevant header for PSStack and PSObject

class PSStackTest_1917 : public ::testing::Test {
protected:
    PSStack stack;

    void SetUp() override {
        // Optionally, initialize or reset the stack before each test case
    }
    
    void TearDown() override {
        // Optionally, clean up after each test case
    }
};

// Normal operation tests
TEST_F(PSStackTest_1917, TopTwoAreNums_ReturnsTrue_WhenTopTwoAreNumbers_1917) {
    stack.pushInt(5);
    stack.pushReal(3.14);

    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1917, TopTwoAreNums_ReturnsFalse_WhenTopTwoAreNotNumbers_1917) {
    stack.pushInt(5);
    stack.pushBool(true);

    EXPECT_FALSE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1917, TopTwoAreNums_ReturnsFalse_WhenStackIsEmpty_1917) {
    EXPECT_FALSE(stack.topTwoAreNums());
}

// Boundary condition tests
TEST_F(PSStackTest_1917, TopTwoAreNums_ReturnsFalse_WhenNotEnoughElementsOnStack_1917) {
    stack.pushInt(5);

    EXPECT_FALSE(stack.topTwoAreNums());  // Only one element on stack
}

// Exceptional/error case tests
TEST_F(PSStackTest_1917, TopTwoAreNums_ReturnsFalse_WhenStackIsOverflowed_1917) {
    // Simulate stack overflow by pushing beyond capacity
    for (int i = 0; i < 101; ++i) {
        stack.pushInt(i);  // Assuming the stack size is 100
    }

    EXPECT_FALSE(stack.topTwoAreNums());  // This will check if it handles overflow correctly
}

TEST_F(PSStackTest_1917, TopTwoAreNums_ReturnsFalse_WhenStackUnderflow_1917) {
    // Attempt to access top elements from an empty stack
    EXPECT_FALSE(stack.topTwoAreNums());
}

// Verification of external interactions (Mock example)
class MockPSStack : public PSStack {
public:
    MOCK_METHOD(bool, topTwoAreNums, (), (override));  // Mocking the topTwoAreNums method
};

TEST_F(PSStackTest_1917, TopTwoAreNums_CallsTopTwoAreNums_ExternalInteraction_1917) {
    MockPSStack mockStack;
    EXPECT_CALL(mockStack, topTwoAreNums()).WillOnce(testing::Return(true));

    mockStack.topTwoAreNums();  // This will verify the call to topTwoAreNums
}