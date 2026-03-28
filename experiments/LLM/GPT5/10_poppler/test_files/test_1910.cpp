#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/Function.cc"

// Test class to wrap PSStack
class PSStackTest_1910 : public ::testing::Test {
protected:
    PSStack stack;

    void SetUp() override {
        // Initialization code, if necessary
    }

    void TearDown() override {
        // Cleanup code, if necessary
    }
};

// Test for popBool under normal operation
TEST_F(PSStackTest_1910, PopBool_ValidStack_ReturnsBool_1910) {
    stack.pushBool(true);
    bool result = stack.popBool();
    EXPECT_TRUE(result);
}

// Test for popBool with stack underflow
TEST_F(PSStackTest_1910, PopBool_StackUnderflow_ReturnsFalse_1910) {
    bool result = stack.popBool();
    EXPECT_FALSE(result);
}

// Test for popBool with incorrect type (when the top of the stack is not bool)
TEST_F(PSStackTest_1910, PopBool_InvalidType_ReturnsFalse_1910) {
    stack.pushInt(10);
    bool result = stack.popBool();
    EXPECT_FALSE(result);
}

// Test for popInt under normal operation
TEST_F(PSStackTest_1910, PopInt_ValidStack_ReturnsInt_1910) {
    stack.pushInt(42);
    int result = stack.popInt();
    EXPECT_EQ(result, 42);
}

// Test for popInt with stack underflow
TEST_F(PSStackTest_1910, PopInt_StackUnderflow_ReturnsZero_1910) {
    int result = stack.popInt();
    EXPECT_EQ(result, 0);
}

// Test for popInt with incorrect type (when the top of the stack is not int)
TEST_F(PSStackTest_1910, PopInt_InvalidType_ReturnsZero_1910) {
    stack.pushBool(true);
    int result = stack.popInt();
    EXPECT_EQ(result, 0);
}

// Test for popNum under normal operation
TEST_F(PSStackTest_1910, PopNum_ValidStack_ReturnsNum_1910) {
    stack.pushReal(3.14);
    double result = stack.popNum();
    EXPECT_DOUBLE_EQ(result, 3.14);
}

// Test for popNum with stack underflow
TEST_F(PSStackTest_1910, PopNum_StackUnderflow_ReturnsZero_1910) {
    double result = stack.popNum();
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test for popNum with incorrect type (when the top of the stack is not a real/num)
TEST_F(PSStackTest_1910, PopNum_InvalidType_ReturnsZero_1910) {
    stack.pushInt(42);
    double result = stack.popNum();
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test for empty stack
TEST_F(PSStackTest_1910, Empty_EmptyStack_ReturnsTrue_1910) {
    EXPECT_TRUE(stack.empty());
}

// Test for non-empty stack
TEST_F(PSStackTest_1910, Empty_NonEmptyStack_ReturnsFalse_1910) {
    stack.pushBool(false);
    EXPECT_FALSE(stack.empty());
}

// Test for topIsInt when the top is an int
TEST_F(PSStackTest_1910, TopIsInt_ValidIntStack_ReturnsTrue_1910) {
    stack.pushInt(10);
    EXPECT_TRUE(stack.topIsInt());
}

// Test for topIsInt when the top is not an int
TEST_F(PSStackTest_1910, TopIsInt_InvalidTop_ReturnsFalse_1910) {
    stack.pushReal(3.14);
    EXPECT_FALSE(stack.topIsInt());
}

// Test for topIsReal when the top is a real number
TEST_F(PSStackTest_1910, TopIsReal_ValidRealStack_ReturnsTrue_1910) {
    stack.pushReal(3.14);
    EXPECT_TRUE(stack.topIsReal());
}

// Test for topIsReal when the top is not a real number
TEST_F(PSStackTest_1910, TopIsReal_InvalidTop_ReturnsFalse_1910) {
    stack.pushInt(42);
    EXPECT_FALSE(stack.topIsReal());
}

// Test for checking if top two elements are integers
TEST_F(PSStackTest_1910, TopTwoAreInts_ValidIntStack_ReturnsTrue_1910) {
    stack.pushInt(5);
    stack.pushInt(10);
    EXPECT_TRUE(stack.topTwoAreInts());
}

// Test for checking if top two elements are not integers
TEST_F(PSStackTest_1910, TopTwoAreInts_InvalidStack_ReturnsFalse_1910) {
    stack.pushInt(5);
    stack.pushReal(3.14);
    EXPECT_FALSE(stack.topTwoAreInts());
}

// Test for checkOverflow with valid conditions
TEST_F(PSStackTest_1910, CheckOverflow_ValidConditions_ReturnsTrue_1910) {
    // Assuming there's a valid checkOverflow implementation
    bool result = stack.checkOverflow();
    EXPECT_TRUE(result);  // Replace with actual expected condition
}

// Test for checkUnderflow when the stack is empty
TEST_F(PSStackTest_1910, CheckUnderflow_EmptyStack_ReturnsTrue_1910) {
    bool result = stack.checkUnderflow();
    EXPECT_TRUE(result);
}