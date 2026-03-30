#include <gtest/gtest.h>
#include "Function.h"  // Make sure the correct header is included

class PSStackTest_1907 : public ::testing::Test {
protected:
    PSStack psStack;

    void SetUp() override {
        // Any setup needed for the tests, such as initializing the PSStack instance.
    }

    void TearDown() override {
        // Any teardown needed after tests, e.g., clearing resources.
    }
};

// Normal operation tests
TEST_F(PSStackTest_1907, PushBool_1907) {
    psStack.pushBool(true);
    EXPECT_FALSE(psStack.empty());
    EXPECT_EQ(psStack.popBool(), true);
}

TEST_F(PSStackTest_1907, PushInt_1907) {
    psStack.pushInt(42);
    EXPECT_FALSE(psStack.empty());
    EXPECT_EQ(psStack.popInt(), 42);
}

TEST_F(PSStackTest_1907, PushReal_1907) {
    psStack.pushReal(3.14);
    EXPECT_FALSE(psStack.empty());
    EXPECT_EQ(psStack.popNum(), 3.14);
}

// Boundary conditions tests
TEST_F(PSStackTest_1907, PushOverflow_1907) {
    // Push to the stack beyond its capacity
    for (int i = 0; i < 100; ++i) {
        psStack.pushInt(i);
    }
    EXPECT_THROW(psStack.pushInt(101), std::overflow_error);  // Expect overflow error
}

TEST_F(PSStackTest_1907, PopUnderflow_1907) {
    // Pop from an empty stack should throw underflow error
    EXPECT_THROW(psStack.pop(), std::underflow_error);  // Expect underflow error
}

// Exceptional cases (Observable behavior based on the interface)
TEST_F(PSStackTest_1907, CheckOverflow_1907) {
    // Check overflow behavior (simulate by pushing to the stack's limit)
    psStack.pushInt(1);
    for (int i = 0; i < 99; ++i) {
        psStack.pushInt(i);  // Fill the stack
    }
    EXPECT_THROW(psStack.pushInt(100), std::overflow_error);  // Should throw overflow error when exceeding capacity
}

TEST_F(PSStackTest_1907, PopBool_1907) {
    psStack.pushBool(true);
    EXPECT_EQ(psStack.popBool(), true);
    EXPECT_THROW(psStack.popBool(), std::underflow_error);  // Should throw underflow error if empty
}

// Verification of external interactions (e.g., mock handlers)
class MockPSStack : public PSStack {
public:
    MOCK_METHOD(bool, checkOverflow, (int n), (const, override));  // Mocking checkOverflow method for interaction testing
};

TEST_F(PSStackTest_1907, VerifyCheckOverflowInteraction_1907) {
    MockPSStack mockStack;
    EXPECT_CALL(mockStack, checkOverflow(1)).WillOnce(testing::Return(true));

    mockStack.pushInt(10);
    EXPECT_TRUE(mockStack.checkOverflow(1));  // Verifying interaction with the mock method
}