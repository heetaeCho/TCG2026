#include <gtest/gtest.h>

// We need to include the necessary headers to access PSStack
// Since PSStack is defined in Function.cc, we need to include the appropriate header
#include "Function.h"

// If Function.h doesn't expose PSStack directly, we may need to work around it.
// Based on the provided interface, we'll test PSStack's public methods.

// Since PSStack might not be in a public header, we include the source directly
// or rely on whatever header exposes it. Adjust as needed for the build system.

class PSStackTest_1906 : public ::testing::Test {
protected:
    PSStack stack;

    void SetUp() override {
        stack.clear();
    }
};

// Test that a newly cleared stack is empty
TEST_F(PSStackTest_1906, ClearMakesStackEmpty_1906) {
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// Test pushing and popping a boolean true
TEST_F(PSStackTest_1906, PushAndPopBoolTrue_1906) {
    stack.pushBool(true);
    EXPECT_FALSE(stack.empty());
    bool result = stack.popBool();
    EXPECT_TRUE(result);
    EXPECT_TRUE(stack.empty());
}

// Test pushing and popping a boolean false
TEST_F(PSStackTest_1906, PushAndPopBoolFalse_1906) {
    stack.pushBool(false);
    bool result = stack.popBool();
    EXPECT_FALSE(result);
}

// Test pushing and popping an integer
TEST_F(PSStackTest_1906, PushAndPopInt_1906) {
    stack.pushInt(42);
    EXPECT_FALSE(stack.empty());
    int result = stack.popInt();
    EXPECT_EQ(result, 42);
    EXPECT_TRUE(stack.empty());
}

// Test pushing and popping a negative integer
TEST_F(PSStackTest_1906, PushAndPopNegativeInt_1906) {
    stack.pushInt(-100);
    int result = stack.popInt();
    EXPECT_EQ(result, -100);
}

// Test pushing and popping zero integer
TEST_F(PSStackTest_1906, PushAndPopZeroInt_1906) {
    stack.pushInt(0);
    int result = stack.popInt();
    EXPECT_EQ(result, 0);
}

// Test pushing and popping a real number
TEST_F(PSStackTest_1906, PushAndPopReal_1906) {
    stack.pushReal(3.14);
    double result = stack.popNum();
    EXPECT_DOUBLE_EQ(result, 3.14);
}

// Test pushing and popping a negative real
TEST_F(PSStackTest_1906, PushAndPopNegativeReal_1906) {
    stack.pushReal(-2.718);
    double result = stack.popNum();
    EXPECT_DOUBLE_EQ(result, -2.718);
}

// Test popNum with an integer on the stack
TEST_F(PSStackTest_1906, PopNumWithInt_1906) {
    stack.pushInt(7);
    double result = stack.popNum();
    EXPECT_DOUBLE_EQ(result, 7.0);
}

// Test topIsInt returns true when top is int
TEST_F(PSStackTest_1906, TopIsIntTrue_1906) {
    stack.pushInt(5);
    EXPECT_TRUE(stack.topIsInt());
}

// Test topIsInt returns false when top is real
TEST_F(PSStackTest_1906, TopIsIntFalseForReal_1906) {
    stack.pushReal(5.0);
    EXPECT_FALSE(stack.topIsInt());
}

// Test topIsInt returns false when top is bool
TEST_F(PSStackTest_1906, TopIsIntFalseForBool_1906) {
    stack.pushBool(true);
    EXPECT_FALSE(stack.topIsInt());
}

// Test topIsReal returns true when top is real
TEST_F(PSStackTest_1906, TopIsRealTrue_1906) {
    stack.pushReal(1.5);
    EXPECT_TRUE(stack.topIsReal());
}

// Test topIsReal returns false when top is int
TEST_F(PSStackTest_1906, TopIsRealFalseForInt_1906) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.topIsReal());
}

// Test topTwoAreInts when both are ints
TEST_F(PSStackTest_1906, TopTwoAreIntsBothInts_1906) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreInts());
}

// Test topTwoAreInts when one is real
TEST_F(PSStackTest_1906, TopTwoAreIntsMixedTypes_1906) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_FALSE(stack.topTwoAreInts());
}

// Test topTwoAreNums when both are ints
TEST_F(PSStackTest_1906, TopTwoAreNumsBothInts_1906) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

// Test topTwoAreNums when both are reals
TEST_F(PSStackTest_1906, TopTwoAreNumsBothReals_1906) {
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

// Test topTwoAreNums when mixed int and real
TEST_F(PSStackTest_1906, TopTwoAreNumsMixed_1906) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

// Test topTwoAreNums when one is bool
TEST_F(PSStackTest_1906, TopTwoAreNumsWithBool_1906) {
    stack.pushBool(true);
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreNums());
}

// Test empty on empty stack
TEST_F(PSStackTest_1906, EmptyOnEmptyStack_1906) {
    EXPECT_TRUE(stack.empty());
}

// Test empty after push
TEST_F(PSStackTest_1906, NotEmptyAfterPush_1906) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.empty());
}

// Test pop removes top element
TEST_F(PSStackTest_1906, PopRemovesTopElement_1906) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pop();
    int result = stack.popInt();
    EXPECT_EQ(result, 1);
}

// Test LIFO order
TEST_F(PSStackTest_1906, LIFOOrder_1906) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

// Test index duplicates the i-th element from top
TEST_F(PSStackTest_1906, IndexDuplicatesElement_1906) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    stack.index(2); // Should duplicate element at index 2 (which is 10)
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_EQ(stack.popInt(), 30);
}

// Test index with 0 duplicates top
TEST_F(PSStackTest_1906, IndexZeroDuplicatesTop_1906) {
    stack.pushInt(42);
    stack.index(0);
    EXPECT_EQ(stack.popInt(), 42);
    EXPECT_EQ(stack.popInt(), 42);
}

// Test copy duplicates top n elements
TEST_F(PSStackTest_1906, CopyDuplicatesTopN_1906) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.copy(2);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

// Test copy with 1 element
TEST_F(PSStackTest_1906, CopySingleElement_1906) {
    stack.pushInt(99);
    stack.copy(1);
    EXPECT_EQ(stack.popInt(), 99);
    EXPECT_EQ(stack.popInt(), 99);
}

// Test roll operation - basic positive roll
TEST_F(PSStackTest_1906, RollPositive_1906) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 1); // Roll top 3 elements up by 1
    // Expected: bottom was [1,2,3] top; after roll(3,1): [3,1,2] top
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_EQ(stack.popInt(), 3);
}

// Test roll with negative j
TEST_F(PSStackTest_1906, RollNegative_1906) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, -1); // Roll top 3 elements down by 1
    // Expected: bottom was [1,2,3] top; after roll(3,-1): [2,3,1] top
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
}

// Test roll with j=0 (no change)
TEST_F(PSStackTest_1906, RollZero_1906) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 0);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

// Test clear after pushing elements
TEST_F(PSStackTest_1906, ClearAfterPush_1906) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// Test multiple clears
TEST_F(PSStackTest_1906, MultipleClear_1906) {
    stack.clear();
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// Test pushing multiple types and popping correctly
TEST_F(PSStackTest_1906, MixedTypes_1906) {
    stack.pushInt(10);
    stack.pushReal(2.5);
    stack.pushBool(true);

    EXPECT_TRUE(stack.popBool());
    EXPECT_DOUBLE_EQ(stack.popNum(), 2.5);
    EXPECT_EQ(stack.popInt(), 10);
}

// Test boundary: push up to stack size (100 elements)
TEST_F(PSStackTest_1906, PushToMaxCapacity_1906) {
    for (int i = 0; i < 100; i++) {
        stack.pushInt(i);
    }
    EXPECT_FALSE(stack.empty());
    // Pop all and verify LIFO
    for (int i = 99; i >= 0; i--) {
        EXPECT_EQ(stack.popInt(), i);
    }
    EXPECT_TRUE(stack.empty());
}

// Test overflow: pushing more than 100 elements should be handled gracefully
TEST_F(PSStackTest_1906, OverflowProtection_1906) {
    for (int i = 0; i < 100; i++) {
        stack.pushInt(i);
    }
    // Pushing one more should not crash (overflow check)
    stack.pushInt(999);
    // The 101st push should be ignored; top should still be 99
    EXPECT_EQ(stack.popInt(), 99);
}

// Test underflow: popping from empty stack should be handled gracefully
TEST_F(PSStackTest_1906, UnderflowProtection_1906) {
    // This should not crash
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// Test topIsInt on empty stack
TEST_F(PSStackTest_1906, TopIsIntOnEmptyStack_1906) {
    // Should handle gracefully without crash
    EXPECT_FALSE(stack.topIsInt());
}

// Test topIsReal on empty stack
TEST_F(PSStackTest_1906, TopIsRealOnEmptyStack_1906) {
    EXPECT_FALSE(stack.topIsReal());
}

// Test topTwoAreInts with only one element
TEST_F(PSStackTest_1906, TopTwoAreIntsWithOneElement_1906) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreInts());
}

// Test topTwoAreNums with only one element
TEST_F(PSStackTest_1906, TopTwoAreNumsWithOneElement_1906) {
    stack.pushReal(1.0);
    EXPECT_FALSE(stack.topTwoAreNums());
}

// Test pushReal with zero
TEST_F(PSStackTest_1906, PushRealZero_1906) {
    stack.pushReal(0.0);
    EXPECT_TRUE(stack.topIsReal());
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
}

// Test large integer values
TEST_F(PSStackTest_1906, LargeIntValue_1906) {
    stack.pushInt(2147483647); // INT_MAX
    EXPECT_EQ(stack.popInt(), 2147483647);
}

// Test large negative integer
TEST_F(PSStackTest_1906, LargeNegativeInt_1906) {
    stack.pushInt(-2147483647);
    EXPECT_EQ(stack.popInt(), -2147483647);
}

// Test roll with n=1 (single element roll should be no-op)
TEST_F(PSStackTest_1906, RollSingleElement_1906) {
    stack.pushInt(5);
    stack.roll(1, 1);
    EXPECT_EQ(stack.popInt(), 5);
}

// Test copy with 0
TEST_F(PSStackTest_1906, CopyZeroElements_1906) {
    stack.pushInt(1);
    stack.copy(0);
    // Stack should remain unchanged
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_TRUE(stack.empty());
}

// Test index with 1 (second element from top)
TEST_F(PSStackTest_1906, IndexOne_1906) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.index(1);
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
}

// Test that pop followed by empty check works
TEST_F(PSStackTest_1906, PopUntilEmpty_1906) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pop();
    EXPECT_FALSE(stack.empty());
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// Test roll with full rotation (j == n, should be identity)
TEST_F(PSStackTest_1906, RollFullRotation_1906) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 3); // Full rotation = no change
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}
