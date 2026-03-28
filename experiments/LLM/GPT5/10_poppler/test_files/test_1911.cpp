#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/Function.cc"  // Include the header where PSStack is defined

class MockPSStack : public PSStack {
public:
    MOCK_METHOD(bool, checkUnderflow, (), (const, override));  // Mock checkUnderflow method
    MOCK_METHOD(bool, checkType, (PSObjectType t1, PSObjectType t2), (const, override));  // Mock checkType method
};

// Normal Operation Test Case
TEST_F(MockPSStack, popInt_1911) {
    PSStack stack;

    // Test pushing an int
    stack.pushInt(5);
    EXPECT_EQ(stack.popInt(), 5);
}

TEST_F(MockPSStack, popBool_1911) {
    PSStack stack;

    // Test pushing a bool
    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());
}

TEST_F(MockPSStack, popReal_1911) {
    PSStack stack;

    // Test pushing a real number
    stack.pushReal(3.14);
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);
}

// Boundary Conditions Test Cases
TEST_F(MockPSStack, popIntUnderflow_1911) {
    PSStack stack;

    // Test popInt underflow scenario
    EXPECT_CALL(*this, checkUnderflow()).WillOnce(testing::Return(true));  // Simulate underflow
    EXPECT_EQ(stack.popInt(), 0);  // Expect 0 on underflow
}

TEST_F(MockPSStack, pushIntOverflow_1911) {
    PSStack stack;

    // Test overflow behavior when pushing too many elements
    EXPECT_CALL(*this, checkOverflow(1)).WillOnce(testing::Return(true));  // Simulate overflow
    stack.pushInt(10);  // This will simulate the checkOverflow call internally
}

// Exceptional or Error Cases
TEST_F(MockPSStack, popIntWithWrongType_1911) {
    PSStack stack;

    // Simulate an incorrect type for pop
    EXPECT_CALL(*this, checkType(psInt, psInt)).WillOnce(testing::Return(false));  // Simulate type mismatch
    EXPECT_EQ(stack.popInt(), 0);  // Expect 0 due to incorrect type
}

TEST_F(MockPSStack, popBoolWithWrongType_1911) {
    PSStack stack;

    // Simulate an incorrect type for pop
    EXPECT_CALL(*this, checkType(psBool, psBool)).WillOnce(testing::Return(false));  // Simulate type mismatch
    EXPECT_FALSE(stack.popBool());  // Expect false due to incorrect type
}

// Verification of External Interactions (Mocking checkUnderflow and checkType)
TEST_F(MockPSStack, checkUnderflowInteraction_1911) {
    PSStack stack;
    EXPECT_CALL(*this, checkUnderflow()).WillOnce(testing::Return(true));
    
    stack.popInt();  // Should trigger the mock checkUnderflow
}

TEST_F(MockPSStack, checkTypeInteraction_1911) {
    PSStack stack;
    EXPECT_CALL(*this, checkType(psInt, psInt)).WillOnce(testing::Return(true));

    stack.pushInt(10);  // Should trigger the mock checkType
}