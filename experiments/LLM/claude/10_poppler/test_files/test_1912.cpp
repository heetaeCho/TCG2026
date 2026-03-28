#include <gtest/gtest.h>

// Include necessary headers from the project
// We need to access the PSStack class and related types

// Forward declarations based on provided interface
enum PSObjectType { psBool = 0, psInt = 1, psReal = 2, psOperator = 3, psBlock = 4 };

// Since PSStack is defined in Function.cc, we need to include the appropriate header
// In the actual poppler project, Function.h should declare these
#include "Function.h"

// If Function.h doesn't expose PSStack directly, we may need to work around it.
// Based on the provided interface, PSStack is defined in Function.cc

class PSStackTest_1912 : public ::testing::Test {
protected:
    PSStack stack;
};

// ==================== pushInt / popInt Tests ====================

TEST_F(PSStackTest_1912, PushIntAndPopInt_1912) {
    stack.pushInt(42);
    EXPECT_EQ(stack.popInt(), 42);
}

TEST_F(PSStackTest_1912, PushIntAndPopNum_1912) {
    stack.pushInt(42);
    EXPECT_DOUBLE_EQ(stack.popNum(), 42.0);
}

TEST_F(PSStackTest_1912, PushMultipleIntsAndPopInOrder_1912) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

// ==================== pushReal / popNum Tests ====================

TEST_F(PSStackTest_1912, PushRealAndPopNum_1912) {
    stack.pushReal(3.14);
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);
}

TEST_F(PSStackTest_1912, PushRealAndPopNumNegative_1912) {
    stack.pushReal(-2.718);
    EXPECT_DOUBLE_EQ(stack.popNum(), -2.718);
}

TEST_F(PSStackTest_1912, PushRealZero_1912) {
    stack.pushReal(0.0);
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
}

// ==================== pushBool / popBool Tests ====================

TEST_F(PSStackTest_1912, PushBoolTrueAndPopBool_1912) {
    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());
}

TEST_F(PSStackTest_1912, PushBoolFalseAndPopBool_1912) {
    stack.pushBool(false);
    EXPECT_FALSE(stack.popBool());
}

// ==================== empty() Tests ====================

TEST_F(PSStackTest_1912, EmptyStackIsEmpty_1912) {
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1912, NonEmptyStackIsNotEmpty_1912) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.empty());
}

TEST_F(PSStackTest_1912, StackEmptyAfterPop_1912) {
    stack.pushInt(1);
    stack.popInt();
    EXPECT_TRUE(stack.empty());
}

// ==================== topIsInt / topIsReal Tests ====================

TEST_F(PSStackTest_1912, TopIsIntAfterPushInt_1912) {
    stack.pushInt(5);
    EXPECT_TRUE(stack.topIsInt());
}

TEST_F(PSStackTest_1912, TopIsRealAfterPushReal_1912) {
    stack.pushReal(5.0);
    EXPECT_TRUE(stack.topIsReal());
}

TEST_F(PSStackTest_1912, TopIsNotRealAfterPushInt_1912) {
    stack.pushInt(5);
    EXPECT_FALSE(stack.topIsReal());
}

TEST_F(PSStackTest_1912, TopIsNotIntAfterPushReal_1912) {
    stack.pushReal(5.0);
    EXPECT_FALSE(stack.topIsInt());
}

// ==================== topTwoAreInts / topTwoAreNums Tests ====================

TEST_F(PSStackTest_1912, TopTwoAreIntsWhenBothInts_1912) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1912, TopTwoAreNotIntsWhenOneIsReal_1912) {
    stack.pushReal(1.0);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1912, TopTwoAreNumsWithTwoInts_1912) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1912, TopTwoAreNumsWithTwoReals_1912) {
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1912, TopTwoAreNumsWithMixed_1912) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1912, TopTwoAreNotNumsWithBool_1912) {
    stack.pushBool(true);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreNums());
}

// ==================== clear() Tests ====================

TEST_F(PSStackTest_1912, ClearEmptiesStack_1912) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1912, ClearOnEmptyStack_1912) {
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// ==================== pop() Tests ====================

TEST_F(PSStackTest_1912, PopRemovesTopElement_1912) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pop();
    EXPECT_EQ(stack.popInt(), 1);
}

// ==================== copy() Tests ====================

TEST_F(PSStackTest_1912, CopyDuplicatesTopNElements_1912) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.copy(2);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
}

TEST_F(PSStackTest_1912, CopyOne_1912) {
    stack.pushInt(42);
    stack.copy(1);
    EXPECT_EQ(stack.popInt(), 42);
    EXPECT_EQ(stack.popInt(), 42);
}

// ==================== index() Tests ====================

TEST_F(PSStackTest_1912, IndexZeroDuplicatesTop_1912) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.index(0);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 20);
}

TEST_F(PSStackTest_1912, IndexOneCopiesSecondElement_1912) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.index(1);
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
}

// ==================== roll() Tests ====================

TEST_F(PSStackTest_1912, RollPositive_1912) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 1);
    // After roll(3,1): top n=3 elements rolled by j=1
    // Before: top -> 3, 2, 1
    // After roll by 1: top -> 1, 3, 2
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
}

TEST_F(PSStackTest_1912, RollNegative_1912) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, -1);
    // Before: top -> 3, 2, 1
    // After roll by -1: top -> 2, 1, 3
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_EQ(stack.popInt(), 3);
}

TEST_F(PSStackTest_1912, RollZero_1912) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 0);
    // No change
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

// ==================== popNum with int conversion Tests ====================

TEST_F(PSStackTest_1912, PopNumConvertsIntToDouble_1912) {
    stack.pushInt(100);
    double val = stack.popNum();
    EXPECT_DOUBLE_EQ(val, 100.0);
}

TEST_F(PSStackTest_1912, PopNumReturnsRealDirectly_1912) {
    stack.pushReal(99.99);
    double val = stack.popNum();
    EXPECT_DOUBLE_EQ(val, 99.99);
}

TEST_F(PSStackTest_1912, PopNumWithNegativeInt_1912) {
    stack.pushInt(-50);
    EXPECT_DOUBLE_EQ(stack.popNum(), -50.0);
}

TEST_F(PSStackTest_1912, PopNumWithLargeReal_1912) {
    stack.pushReal(1e300);
    EXPECT_DOUBLE_EQ(stack.popNum(), 1e300);
}

TEST_F(PSStackTest_1912, PopNumWithVerySmallReal_1912) {
    stack.pushReal(1e-300);
    EXPECT_DOUBLE_EQ(stack.popNum(), 1e-300);
}

// ==================== Underflow Tests ====================

TEST_F(PSStackTest_1912, PopNumOnEmptyStackReturnsZero_1912) {
    // Underflow condition: popNum should return 0 on empty stack
    double val = stack.popNum();
    EXPECT_DOUBLE_EQ(val, 0.0);
}

TEST_F(PSStackTest_1912, PopIntOnEmptyStack_1912) {
    // Underflow: popInt on empty stack
    int val = stack.popInt();
    EXPECT_EQ(val, 0);
}

TEST_F(PSStackTest_1912, PopBoolOnEmptyStack_1912) {
    // Underflow: popBool on empty stack
    bool val = stack.popBool();
    EXPECT_FALSE(val);
}

// ==================== Type mismatch Tests ====================

TEST_F(PSStackTest_1912, PopNumOnBoolReturnsZero_1912) {
    stack.pushBool(true);
    // popNum checks for psInt or psReal type, bool should fail type check
    double val = stack.popNum();
    EXPECT_DOUBLE_EQ(val, 0.0);
}

// ==================== Overflow Tests ====================

TEST_F(PSStackTest_1912, PushUpToStackLimit_1912) {
    // Stack has size 100, pushing 100 elements should work
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    EXPECT_FALSE(stack.empty());
    // Pop all and verify LIFO order
    for (int i = 99; i >= 0; --i) {
        EXPECT_EQ(stack.popInt(), i);
    }
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1912, PushBeyondStackLimitHandled_1912) {
    // Push 100 elements (filling the stack)
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    // Pushing one more should trigger overflow check; implementation may silently fail
    stack.pushInt(999);
    // We can't assert specific behavior beyond what the interface guarantees,
    // but at minimum the stack shouldn't crash
}

// ==================== Mixed type operations ====================

TEST_F(PSStackTest_1912, MixedPushAndPop_1912) {
    stack.pushInt(10);
    stack.pushReal(20.5);
    stack.pushBool(true);
    stack.pushInt(30);

    EXPECT_EQ(stack.popInt(), 30);
    EXPECT_TRUE(stack.popBool());
    EXPECT_DOUBLE_EQ(stack.popNum(), 20.5);
    EXPECT_DOUBLE_EQ(stack.popNum(), 10.0);
}

TEST_F(PSStackTest_1912, TopIsIntNotBool_1912) {
    stack.pushBool(true);
    EXPECT_FALSE(stack.topIsInt());
    EXPECT_FALSE(stack.topIsReal());
}

// ==================== Sequence of operations ====================

TEST_F(PSStackTest_1912, PushPopPushPop_1912) {
    stack.pushInt(1);
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_TRUE(stack.empty());
    stack.pushReal(2.0);
    EXPECT_DOUBLE_EQ(stack.popNum(), 2.0);
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1912, ClearAndReuse_1912) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.clear();
    EXPECT_TRUE(stack.empty());
    stack.pushInt(3);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_TRUE(stack.empty());
}
