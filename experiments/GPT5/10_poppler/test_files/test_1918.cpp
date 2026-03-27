#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"  // Include the header that declares PSStack

// Mocking the error function used in PSStack for error handling
class MockError {
public:
    MOCK_METHOD(void, error, (ErrorCategory, int, const char*), ());
};

class PSStackTest_1918 : public ::testing::Test {
protected:
    MockError mockError;
    PSStack psStack;

    void SetUp() override {
        // You can initialize any necessary objects here
    }

    void TearDown() override {
        // You can clean up after tests if necessary
    }
};

// Normal Operation Tests
TEST_F(PSStackTest_1918, PushPopInt_NormalOperation_1918) {
    psStack.pushInt(10);
    EXPECT_EQ(psStack.popInt(), 10);
}

TEST_F(PSStackTest_1918, PushPopReal_NormalOperation_1918) {
    psStack.pushReal(3.14);
    EXPECT_EQ(psStack.popNum(), 3.14);
}

// Boundary Conditions Tests
TEST_F(PSStackTest_1918, IndexWithValidIndex_1918) {
    psStack.pushInt(1);
    psStack.pushInt(2);
    psStack.index(0);
    EXPECT_EQ(psStack.popInt(), 2);  // The element at index 0 should be 2
}

TEST_F(PSStackTest_1918, StackOverflowTest_1918) {
    // Mock error method to ensure that the error is called on overflow
    EXPECT_CALL(mockError, error(errSyntaxError, -1, "Stack overflow in PostScript function")).Times(1);
    psStack.index(101);  // Should trigger overflow as it exceeds stack size
}

TEST_F(PSStackTest_1918, StackUnderflowTest_1918) {
    // Mock error method to ensure that the error is called on underflow
    EXPECT_CALL(mockError, error(errSyntaxError, -1, "Stack underflow in PostScript function")).Times(1);
    psStack.index(-1);  // Should trigger underflow as it is less than 0
}

// Exceptional/Error Case Tests
TEST_F(PSStackTest_1918, OverflowCheckError_1918) {
    // Mock error to check that the overflow case triggers the error
    EXPECT_CALL(mockError, error(errSyntaxError, -1, "Stack overflow in PostScript function")).Times(1);
    psStack.index(101);  // This should trigger the overflow error
}

TEST_F(PSStackTest_1918, UnderflowCheckError_1918) {
    // Mock error to check that the underflow case triggers the error
    EXPECT_CALL(mockError, error(errSyntaxError, -1, "Stack underflow in PostScript function")).Times(1);
    psStack.index(-1);  // This should trigger the underflow error
}

// External Interaction Tests (Mock error handling)
TEST_F(PSStackTest_1918, ErrorHandlingOnOverflow_1918) {
    EXPECT_CALL(mockError, error(errSyntaxError, -1, "Stack overflow in PostScript function")).Times(1);
    psStack.index(101);  // Will overflow
}

TEST_F(PSStackTest_1918, ErrorHandlingOnUnderflow_1918) {
    EXPECT_CALL(mockError, error(errSyntaxError, -1, "Stack underflow in PostScript function")).Times(1);
    psStack.index(-1);  // Will underflow
}