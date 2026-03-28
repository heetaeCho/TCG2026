#include <gtest/gtest.h>

// We need to include the necessary headers. Since PSStack is defined in Function.cc,
// we need to work with what's available. We'll include the relevant header.
// Based on the poppler project structure, Function.h should declare these types.
#include "Function.h"

// If Function.h doesn't expose PSStack directly (it's in the .cc file), we may need
// to include the .cc file directly for testing purposes.
// This is a common pattern when testing internal classes.
// However, since the prompt says the class is already implemented, we include as needed.

// If PSStack is not exposed via header, we include the source directly:
// #include "Function.cc"

// For the purpose of this test, we assume PSStack and related types are accessible.

class PSStackTest_1910 : public ::testing::Test {
protected:
    PSStack stack;
};

// ==================== pushBool / popBool Tests ====================

TEST_F(PSStackTest_1910, PushAndPopBoolTrue_1910) {
    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());
}

TEST_F(PSStackTest_1910, PushAndPopBoolFalse_1910) {
    stack.pushBool(false);
    EXPECT_FALSE(stack.popBool());
}

TEST_F(PSStackTest_1910, PopBoolFromEmptyStackReturnsFalse_1910) {
    // Underflow case: popping from empty stack should return false
    EXPECT_FALSE(stack.popBool());
}

TEST_F(PSStackTest_1910, PopBoolWithWrongTypeReturnsFalse_1910) {
    // Push an int, then try to popBool - type mismatch
    stack.pushInt(42);
    EXPECT_FALSE(stack.popBool());
}

TEST_F(PSStackTest_1910, PopBoolWithRealTypeReturnsFalse_1910) {
    stack.pushReal(3.14);
    EXPECT_FALSE(stack.popBool());
}

// ==================== pushInt / popInt Tests ====================

TEST_F(PSStackTest_1910, PushAndPopInt_1910) {
    stack.pushInt(42);
    EXPECT_EQ(stack.popInt(), 42);
}

TEST_F(PSStackTest_1910, PushAndPopIntZero_1910) {
    stack.pushInt(0);
    EXPECT_EQ(stack.popInt(), 0);
}

TEST_F(PSStackTest_1910, PushAndPopIntNegative_1910) {
    stack.pushInt(-100);
    EXPECT_EQ(stack.popInt(), -100);
}

TEST_F(PSStackTest_1910, PopIntFromEmptyStack_1910) {
    EXPECT_EQ(stack.popInt(), 0);
}

// ==================== pushReal / popNum Tests ====================

TEST_F(PSStackTest_1910, PushAndPopReal_1910) {
    stack.pushReal(3.14);
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);
}

TEST_F(PSStackTest_1910, PopNumWithInt_1910) {
    // popNum should work with int values too
    stack.pushInt(7);
    EXPECT_DOUBLE_EQ(stack.popNum(), 7.0);
}

TEST_F(PSStackTest_1910, PopNumFromEmptyStack_1910) {
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
}

// ==================== empty() Tests ====================

TEST_F(PSStackTest_1910, NewStackIsEmpty_1910) {
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1910, StackNotEmptyAfterPush_1910) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.empty());
}

TEST_F(PSStackTest_1910, StackEmptyAfterPushAndPop_1910) {
    stack.pushInt(1);
    stack.popInt();
    EXPECT_TRUE(stack.empty());
}

// ==================== clear() Tests ====================

TEST_F(PSStackTest_1910, ClearMakesStackEmpty_1910) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1910, ClearOnEmptyStack_1910) {
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// ==================== topIsInt() Tests ====================

TEST_F(PSStackTest_1910, TopIsIntWhenIntPushed_1910) {
    stack.pushInt(5);
    EXPECT_TRUE(stack.topIsInt());
}

TEST_F(PSStackTest_1910, TopIsIntFalseWhenRealPushed_1910) {
    stack.pushReal(5.0);
    EXPECT_FALSE(stack.topIsInt());
}

TEST_F(PSStackTest_1910, TopIsIntFalseWhenBoolPushed_1910) {
    stack.pushBool(true);
    EXPECT_FALSE(stack.topIsInt());
}

TEST_F(PSStackTest_1910, TopIsIntFalseOnEmptyStack_1910) {
    EXPECT_FALSE(stack.topIsInt());
}

// ==================== topIsReal() Tests ====================

TEST_F(PSStackTest_1910, TopIsRealWhenRealPushed_1910) {
    stack.pushReal(2.5);
    EXPECT_TRUE(stack.topIsReal());
}

TEST_F(PSStackTest_1910, TopIsRealFalseWhenIntPushed_1910) {
    stack.pushInt(2);
    EXPECT_FALSE(stack.topIsReal());
}

TEST_F(PSStackTest_1910, TopIsRealFalseOnEmptyStack_1910) {
    EXPECT_FALSE(stack.topIsReal());
}

// ==================== topTwoAreInts() Tests ====================

TEST_F(PSStackTest_1910, TopTwoAreIntsTrue_1910) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1910, TopTwoAreIntsFalseWithOneReal_1910) {
    stack.pushReal(1.0);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1910, TopTwoAreIntsFalseWithOnlyOneElement_1910) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1910, TopTwoAreIntsFalseOnEmpty_1910) {
    EXPECT_FALSE(stack.topTwoAreInts());
}

// ==================== topTwoAreNums() Tests ====================

TEST_F(PSStackTest_1910, TopTwoAreNumsTwoInts_1910) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1910, TopTwoAreNumsTwoReals_1910) {
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1910, TopTwoAreNumsMixed_1910) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1910, TopTwoAreNumsFalseWithBool_1910) {
    stack.pushBool(true);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1910, TopTwoAreNumsFalseOnEmpty_1910) {
    EXPECT_FALSE(stack.topTwoAreNums());
}

// ==================== pop() Tests ====================

TEST_F(PSStackTest_1910, PopRemovesTopElement_1910) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pop();
    EXPECT_EQ(stack.popInt(), 1);
}

TEST_F(PSStackTest_1910, PopOnEmptyStackDoesNotCrash_1910) {
    // Should handle gracefully (underflow check)
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// ==================== index() Tests ====================

TEST_F(PSStackTest_1910, IndexDuplicatesTop_1910) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.index(0); // duplicate top
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 20);
}

TEST_F(PSStackTest_1910, IndexDuplicatesDeeper_1910) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    stack.index(2); // copy element at index 2 (which is 10)
    EXPECT_EQ(stack.popInt(), 10);
}

// ==================== copy() Tests ====================

TEST_F(PSStackTest_1910, CopyTopNElements_1910) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.copy(2); // copy top 2 elements
    // Stack should now be: 1 2 3 2 3 (from bottom to top)
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

TEST_F(PSStackTest_1910, CopyZeroElements_1910) {
    stack.pushInt(1);
    stack.copy(0);
    // Stack should still just have 1
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_TRUE(stack.empty());
}

// ==================== roll() Tests ====================

TEST_F(PSStackTest_1910, RollPositive_1910) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 1); // roll top 3 elements by 1
    // Before: 1 2 3 (top is 3)
    // After roll(3,1): 3 1 2 (top is 2)
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_EQ(stack.popInt(), 3);
}

TEST_F(PSStackTest_1910, RollNegative_1910) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, -1); // roll top 3 elements by -1
    // Before: 1 2 3 (top is 3)
    // After roll(3,-1): 2 3 1 (top is 1)
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
}

TEST_F(PSStackTest_1910, RollByZero_1910) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 0); // no change
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

// ==================== Overflow Tests ====================

TEST_F(PSStackTest_1910, OverflowProtection_1910) {
    // Stack has 100 slots, pushing 100 elements should work
    for (int i = 0; i < 100; i++) {
        stack.pushInt(i);
    }
    // Pushing one more should not crash (overflow check)
    stack.pushInt(999);
    // The 101st push should be rejected, so top should still be 99
    EXPECT_EQ(stack.popInt(), 99);
}

// ==================== Multiple types interleaved ====================

TEST_F(PSStackTest_1910, MultiplePushPopDifferentTypes_1910) {
    stack.pushBool(true);
    stack.pushInt(42);
    stack.pushReal(3.14);

    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);
    EXPECT_EQ(stack.popInt(), 42);
    EXPECT_TRUE(stack.popBool());
}

TEST_F(PSStackTest_1910, LIFOOrder_1910) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

// ==================== Bool edge cases ====================

TEST_F(PSStackTest_1910, MultipleBoolPushPop_1910) {
    stack.pushBool(true);
    stack.pushBool(false);
    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());
    EXPECT_FALSE(stack.popBool());
    EXPECT_TRUE(stack.popBool());
}

TEST_F(PSStackTest_1910, PopBoolAfterClear_1910) {
    stack.pushBool(true);
    stack.clear();
    EXPECT_FALSE(stack.popBool()); // underflow, returns false
}

// ==================== Real number edge cases ====================

TEST_F(PSStackTest_1910, PushRealNegative_1910) {
    stack.pushReal(-2.718);
    EXPECT_DOUBLE_EQ(stack.popNum(), -2.718);
}

TEST_F(PSStackTest_1910, PushRealZero_1910) {
    stack.pushReal(0.0);
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
}

// ==================== TopIsInt after pop ====================

TEST_F(PSStackTest_1910, TopIsIntAfterPopRevealsDifferentType_1910) {
    stack.pushReal(1.5);
    stack.pushInt(10);
    EXPECT_TRUE(stack.topIsInt());
    stack.pop();
    EXPECT_TRUE(stack.topIsReal());
}
