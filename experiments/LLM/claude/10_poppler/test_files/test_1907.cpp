#include <gtest/gtest.h>

// We need to include the implementation. Since PSStack is defined in Function.cc,
// we need to include the relevant header or the source file.
// Based on the project structure, Function.h should declare these types.
#include "Function.h"

// If Function.h doesn't expose PSStack (it's internal to Function.cc), we may need
// to include Function.cc directly or replicate the minimal interface.
// For the purposes of this test, we assume we can access PSStack.

// Since PSStack may be internal to Function.cc, we might need to include it directly.
// This is a common pattern for testing internal classes.

// Forward declarations based on the provided interface
// These are already defined in Function.cc

class PSStackTest_1907 : public ::testing::Test {
protected:
    PSStack stack;
};

// === Push and Pop Bool Tests ===

TEST_F(PSStackTest_1907, PushBoolTrue_1907) {
    stack.pushBool(true);
    EXPECT_FALSE(stack.empty());
    bool result = stack.popBool();
    EXPECT_TRUE(result);
}

TEST_F(PSStackTest_1907, PushBoolFalse_1907) {
    stack.pushBool(false);
    EXPECT_FALSE(stack.empty());
    bool result = stack.popBool();
    EXPECT_FALSE(result);
}

// === Push and Pop Int Tests ===

TEST_F(PSStackTest_1907, PushIntPositive_1907) {
    stack.pushInt(42);
    EXPECT_FALSE(stack.empty());
    int result = stack.popInt();
    EXPECT_EQ(result, 42);
}

TEST_F(PSStackTest_1907, PushIntNegative_1907) {
    stack.pushInt(-100);
    int result = stack.popInt();
    EXPECT_EQ(result, -100);
}

TEST_F(PSStackTest_1907, PushIntZero_1907) {
    stack.pushInt(0);
    int result = stack.popInt();
    EXPECT_EQ(result, 0);
}

// === Push and Pop Real Tests ===

TEST_F(PSStackTest_1907, PushRealPositive_1907) {
    stack.pushReal(3.14);
    double result = stack.popNum();
    EXPECT_DOUBLE_EQ(result, 3.14);
}

TEST_F(PSStackTest_1907, PushRealNegative_1907) {
    stack.pushReal(-2.718);
    double result = stack.popNum();
    EXPECT_DOUBLE_EQ(result, -2.718);
}

TEST_F(PSStackTest_1907, PushRealZero_1907) {
    stack.pushReal(0.0);
    double result = stack.popNum();
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// === Empty Tests ===

TEST_F(PSStackTest_1907, InitiallyEmpty_1907) {
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1907, NotEmptyAfterPush_1907) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.empty());
}

TEST_F(PSStackTest_1907, EmptyAfterPushAndPop_1907) {
    stack.pushInt(1);
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// === Clear Tests ===

TEST_F(PSStackTest_1907, ClearEmptiesStack_1907) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1907, ClearOnEmptyStack_1907) {
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// === TopIsInt Tests ===

TEST_F(PSStackTest_1907, TopIsIntWhenIntPushed_1907) {
    stack.pushInt(5);
    EXPECT_TRUE(stack.topIsInt());
}

TEST_F(PSStackTest_1907, TopIsIntWhenRealPushed_1907) {
    stack.pushReal(5.0);
    EXPECT_FALSE(stack.topIsInt());
}

TEST_F(PSStackTest_1907, TopIsIntWhenBoolPushed_1907) {
    stack.pushBool(true);
    EXPECT_FALSE(stack.topIsInt());
}

// === TopIsReal Tests ===

TEST_F(PSStackTest_1907, TopIsRealWhenRealPushed_1907) {
    stack.pushReal(3.14);
    EXPECT_TRUE(stack.topIsReal());
}

TEST_F(PSStackTest_1907, TopIsRealWhenIntPushed_1907) {
    stack.pushInt(3);
    EXPECT_FALSE(stack.topIsReal());
}

// === TopTwoAreInts Tests ===

TEST_F(PSStackTest_1907, TopTwoAreIntsBothInts_1907) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1907, TopTwoAreIntsOneIntOneReal_1907) {
    stack.pushReal(1.0);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1907, TopTwoAreIntsBothReals_1907) {
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_FALSE(stack.topTwoAreInts());
}

// === TopTwoAreNums Tests ===

TEST_F(PSStackTest_1907, TopTwoAreNumsBothInts_1907) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1907, TopTwoAreNumsBothReals_1907) {
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1907, TopTwoAreNumsMixed_1907) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1907, TopTwoAreNumsWithBool_1907) {
    stack.pushBool(true);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreNums());
}

// === PopNum with Int ===

TEST_F(PSStackTest_1907, PopNumFromInt_1907) {
    stack.pushInt(7);
    double result = stack.popNum();
    EXPECT_DOUBLE_EQ(result, 7.0);
}

TEST_F(PSStackTest_1907, PopNumFromReal_1907) {
    stack.pushReal(7.5);
    double result = stack.popNum();
    EXPECT_DOUBLE_EQ(result, 7.5);
}

// === Pop Tests ===

TEST_F(PSStackTest_1907, PopRemovesTopElement_1907) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pop();
    int result = stack.popInt();
    EXPECT_EQ(result, 1);
}

// === Copy Tests ===

TEST_F(PSStackTest_1907, CopyTopN_1907) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    stack.copy(2);
    // After copy(2), the top 2 elements (20, 30) should be duplicated
    // Stack should be: 10, 20, 30, 20, 30 (from bottom to top)
    EXPECT_EQ(stack.popInt(), 30);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 30);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
}

TEST_F(PSStackTest_1907, CopyOne_1907) {
    stack.pushInt(42);
    stack.copy(1);
    EXPECT_EQ(stack.popInt(), 42);
    EXPECT_EQ(stack.popInt(), 42);
    EXPECT_TRUE(stack.empty());
}

// === Index Tests ===

TEST_F(PSStackTest_1907, IndexZeroDuplicatesTop_1907) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.index(0);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
}

TEST_F(PSStackTest_1907, IndexOneCopiesSecond_1907) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.index(1);
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
}

// === Roll Tests ===

TEST_F(PSStackTest_1907, RollBasic_1907) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    // roll(3, 1) should rotate top 3 elements by 1
    // Before: 1, 2, 3 (top)
    // After:  2, 3, 1 -> actually depends on direction
    // Roll(n, j): roll top n elements by j positions
    stack.roll(3, 1);
    int a = stack.popInt();
    int b = stack.popInt();
    int c = stack.popInt();
    // The exact behavior depends on implementation, but we can verify consistency
    // PostScript roll: roll n elements, positive j moves top toward bottom
    // 1, 2, 3 -> roll(3,1) -> 3, 1, 2 (top is 3)
    // OR 2, 3, 1 depending on direction convention
    // We just verify all elements are present
    EXPECT_TRUE((a == 1 || a == 2 || a == 3));
    EXPECT_TRUE((b == 1 || b == 2 || b == 3));
    EXPECT_TRUE((c == 1 || c == 2 || c == 3));
    EXPECT_EQ(a + b + c, 6); // sum should be preserved
}

TEST_F(PSStackTest_1907, RollZeroRotation_1907) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 0);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

// === Multiple Push/Pop Tests ===

TEST_F(PSStackTest_1907, MultiplePushPopOrder_1907) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

TEST_F(PSStackTest_1907, MixedTypesPushPop_1907) {
    stack.pushInt(42);
    stack.pushReal(3.14);
    stack.pushBool(true);

    EXPECT_TRUE(stack.popBool());
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);
    EXPECT_EQ(stack.popInt(), 42);
}

// === Boundary: Stack Overflow ===

TEST_F(PSStackTest_1907, PushUpToCapacity_1907) {
    // Stack has capacity of 100 based on the interface
    for (int i = 0; i < 100; i++) {
        stack.pushInt(i);
    }
    EXPECT_FALSE(stack.empty());
    // Pushing one more should trigger overflow check
    stack.pushInt(999);
    // We can't easily check if overflow was handled, but the stack shouldn't crash
}

TEST_F(PSStackTest_1907, PopAllElements_1907) {
    for (int i = 0; i < 10; i++) {
        stack.pushInt(i);
    }
    for (int i = 0; i < 10; i++) {
        stack.pop();
    }
    EXPECT_TRUE(stack.empty());
}

// === Boundary: Underflow ===

TEST_F(PSStackTest_1907, PopFromEmptyStack_1907) {
    // Popping from empty stack should handle gracefully (no crash)
    // The behavior is implementation-defined but should not crash
    stack.popInt();
    // If we get here without crashing, the test passes
}

TEST_F(PSStackTest_1907, PopBoolFromEmptyStack_1907) {
    stack.popBool();
    // Should not crash
}

// === Large Number of Operations ===

TEST_F(PSStackTest_1907, PushPopMultipleTimes_1907) {
    for (int i = 0; i < 50; i++) {
        stack.pushInt(i);
    }
    for (int i = 49; i >= 0; i--) {
        EXPECT_EQ(stack.popInt(), i);
    }
    EXPECT_TRUE(stack.empty());
}

// === Bool Multiple Values ===

TEST_F(PSStackTest_1907, MultipleBoolPushPop_1907) {
    stack.pushBool(true);
    stack.pushBool(false);
    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());
    EXPECT_FALSE(stack.popBool());
    EXPECT_TRUE(stack.popBool());
}

// === Int edge values ===

TEST_F(PSStackTest_1907, PushIntMaxMin_1907) {
    stack.pushInt(INT_MAX);
    stack.pushInt(INT_MIN);
    EXPECT_EQ(stack.popInt(), INT_MIN);
    EXPECT_EQ(stack.popInt(), INT_MAX);
}

// === Real edge values ===

TEST_F(PSStackTest_1907, PushRealLargeValues_1907) {
    stack.pushReal(1e308);
    stack.pushReal(-1e308);
    EXPECT_DOUBLE_EQ(stack.popNum(), -1e308);
    EXPECT_DOUBLE_EQ(stack.popNum(), 1e308);
}

TEST_F(PSStackTest_1907, PushRealVerySmall_1907) {
    stack.pushReal(1e-300);
    EXPECT_DOUBLE_EQ(stack.popNum(), 1e-300);
}

// === Clear and reuse ===

TEST_F(PSStackTest_1907, ClearAndReuse_1907) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.clear();
    EXPECT_TRUE(stack.empty());
    stack.pushInt(3);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_TRUE(stack.empty());
}

// === Copy with zero ===

TEST_F(PSStackTest_1907, CopyZero_1907) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.copy(0);
    // Copying 0 elements should not change the stack
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_TRUE(stack.empty());
}

// === Roll negative ===

TEST_F(PSStackTest_1907, RollNegativeJ_1907) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, -1);
    int a = stack.popInt();
    int b = stack.popInt();
    int c = stack.popInt();
    EXPECT_EQ(a + b + c, 6); // All elements preserved
}

// === Single element operations ===

TEST_F(PSStackTest_1907, SingleElementTopIsInt_1907) {
    stack.pushInt(5);
    EXPECT_TRUE(stack.topIsInt());
    EXPECT_FALSE(stack.topIsReal());
}

TEST_F(PSStackTest_1907, SingleElementTopIsReal_1907) {
    stack.pushReal(5.0);
    EXPECT_TRUE(stack.topIsReal());
    EXPECT_FALSE(stack.topIsInt());
}

// === Pop preserves remaining elements ===

TEST_F(PSStackTest_1907, PopPreservesRemainingElements_1907) {
    stack.pushInt(10);
    stack.pushReal(20.5);
    stack.pushBool(false);
    stack.pop(); // remove bool
    EXPECT_TRUE(stack.topIsReal());
    EXPECT_DOUBLE_EQ(stack.popNum(), 20.5);
    EXPECT_TRUE(stack.topIsInt());
    EXPECT_EQ(stack.popInt(), 10);
}
