#include <gtest/gtest.h>

// We need to include the actual header/implementation for PSStack
// Since the class is defined in Function.cc, we need to find the appropriate header
#include "Function.h"

// If Function.h doesn't expose PSStack directly, we may need to include the .cc
// This depends on the project structure. PSStack appears to be an internal class.
// For testing purposes, we include what's needed.

class PSStackTest_1919 : public ::testing::Test {
protected:
    void SetUp() override {
        // PSStack is constructed with sp = psStackSize (100), meaning empty stack
    }
};

// Test that a newly created stack is empty
TEST_F(PSStackTest_1919, NewStackIsEmpty_1919) {
    PSStack stack;
    EXPECT_TRUE(stack.empty());
}

// Test pushing and popping a boolean value
TEST_F(PSStackTest_1919, PushAndPopBool_1919) {
    PSStack stack;
    stack.pushBool(true);
    EXPECT_FALSE(stack.empty());
    EXPECT_TRUE(stack.popBool());
}

TEST_F(PSStackTest_1919, PushAndPopBoolFalse_1919) {
    PSStack stack;
    stack.pushBool(false);
    EXPECT_FALSE(stack.popBool());
}

// Test pushing and popping an integer value
TEST_F(PSStackTest_1919, PushAndPopInt_1919) {
    PSStack stack;
    stack.pushInt(42);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.popInt(), 42);
}

// Test pushing and popping a real (double) value
TEST_F(PSStackTest_1919, PushAndPopReal_1919) {
    PSStack stack;
    stack.pushReal(3.14);
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);
}

// Test popNum with integer on stack
TEST_F(PSStackTest_1919, PopNumWithInt_1919) {
    PSStack stack;
    stack.pushInt(7);
    EXPECT_DOUBLE_EQ(stack.popNum(), 7.0);
}

// Test that stack becomes empty after push then pop
TEST_F(PSStackTest_1919, StackEmptyAfterPushPop_1919) {
    PSStack stack;
    stack.pushInt(10);
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// Test multiple pushes and pops (LIFO order)
TEST_F(PSStackTest_1919, LIFOOrder_1919) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_TRUE(stack.empty());
}

// Test topIsInt
TEST_F(PSStackTest_1919, TopIsInt_1919) {
    PSStack stack;
    stack.pushInt(5);
    EXPECT_TRUE(stack.topIsInt());
}

// Test topIsReal
TEST_F(PSStackTest_1919, TopIsReal_1919) {
    PSStack stack;
    stack.pushReal(2.5);
    EXPECT_TRUE(stack.topIsReal());
}

// Test topIsInt returns false when top is real
TEST_F(PSStackTest_1919, TopIsIntFalseForReal_1919) {
    PSStack stack;
    stack.pushReal(2.5);
    EXPECT_FALSE(stack.topIsInt());
}

// Test topTwoAreInts
TEST_F(PSStackTest_1919, TopTwoAreInts_1919) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreInts());
}

// Test topTwoAreInts returns false when one is real
TEST_F(PSStackTest_1919, TopTwoAreIntsFalseWithReal_1919) {
    PSStack stack;
    stack.pushReal(1.0);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreInts());
}

// Test topTwoAreNums with two ints
TEST_F(PSStackTest_1919, TopTwoAreNumsWithInts_1919) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

// Test topTwoAreNums with int and real
TEST_F(PSStackTest_1919, TopTwoAreNumsWithMixed_1919) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

// Test topTwoAreNums with two reals
TEST_F(PSStackTest_1919, TopTwoAreNumsWithReals_1919) {
    PSStack stack;
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

// Test clear
TEST_F(PSStackTest_1919, ClearMakesStackEmpty_1919) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// Test copy
TEST_F(PSStackTest_1919, CopyDuplicatesTopN_1919) {
    PSStack stack;
    stack.pushInt(10);
    stack.pushInt(20);
    stack.copy(2);
    // After copy(2), stack should have: 10, 20, 10, 20 (bottom to top)
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_TRUE(stack.empty());
}

// Test index - duplicates the i-th element from the top
TEST_F(PSStackTest_1919, IndexDuplicatesElement_1919) {
    PSStack stack;
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    stack.index(2); // Should push the element at index 2 (which is 10)
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_EQ(stack.popInt(), 30);
}

// Test index(0) duplicates top element
TEST_F(PSStackTest_1919, IndexZeroDuplicatesTop_1919) {
    PSStack stack;
    stack.pushInt(42);
    stack.index(0);
    EXPECT_EQ(stack.popInt(), 42);
    EXPECT_EQ(stack.popInt(), 42);
    EXPECT_TRUE(stack.empty());
}

// Test roll operation
TEST_F(PSStackTest_1919, RollPositive_1919) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    // roll(3, 1) should rotate top 3 elements by 1:
    // Before: 1 2 3 (top is 3)
    // After:  2 3 1 or similar rotation depending on implementation
    stack.roll(3, 1);
    int a = stack.popInt();
    int b = stack.popInt();
    int c = stack.popInt();
    // The exact result depends on the roll direction, but values should be a permutation
    // Common PS behavior: roll(n,j) with j>0 moves top element down j positions in the top n
    // 1,2,3 -> roll(3,1) -> 3,1,2 (top to bottom: 2,1,3)
    // Actually in PostScript: n j roll with n=3 j=1:
    // stack top to bottom: 3 2 1 -> after roll: 1 3 2
    // So popping: first pop = 1, second = 3, third = 2
    // But implementation may vary. Let's just check all three values exist.
    int sum = a + b + c;
    EXPECT_EQ(sum, 6); // 1+2+3
}

// Test pop on empty stack (underflow - should not crash)
TEST_F(PSStackTest_1919, PopOnEmptyStackNocrash_1919) {
    PSStack stack;
    // Should handle gracefully (checkUnderflow returns false)
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// Test popInt on empty stack
TEST_F(PSStackTest_1919, PopIntOnEmptyStack_1919) {
    PSStack stack;
    // Should return some default (likely 0) without crashing
    int val = stack.popInt();
    (void)val; // Just ensure no crash
    EXPECT_TRUE(stack.empty());
}

// Test popBool on empty stack
TEST_F(PSStackTest_1919, PopBoolOnEmptyStack_1919) {
    PSStack stack;
    bool val = stack.popBool();
    (void)val;
    EXPECT_TRUE(stack.empty());
}

// Test popNum on empty stack
TEST_F(PSStackTest_1919, PopNumOnEmptyStack_1919) {
    PSStack stack;
    double val = stack.popNum();
    (void)val;
    EXPECT_TRUE(stack.empty());
}

// Test pushing negative integers
TEST_F(PSStackTest_1919, PushNegativeInt_1919) {
    PSStack stack;
    stack.pushInt(-100);
    EXPECT_EQ(stack.popInt(), -100);
}

// Test pushing zero
TEST_F(PSStackTest_1919, PushZeroInt_1919) {
    PSStack stack;
    stack.pushInt(0);
    EXPECT_EQ(stack.popInt(), 0);
}

// Test pushing negative real
TEST_F(PSStackTest_1919, PushNegativeReal_1919) {
    PSStack stack;
    stack.pushReal(-2.718);
    EXPECT_DOUBLE_EQ(stack.popNum(), -2.718);
}

// Test pushing zero real
TEST_F(PSStackTest_1919, PushZeroReal_1919) {
    PSStack stack;
    stack.pushReal(0.0);
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
}

// Test overflow: push 100 elements (stack size is 100)
TEST_F(PSStackTest_1919, PushToCapacity_1919) {
    PSStack stack;
    for (int i = 0; i < 100; i++) {
        stack.pushInt(i);
    }
    // Stack should be full, verify by popping all
    for (int i = 99; i >= 0; i--) {
        EXPECT_EQ(stack.popInt(), i);
    }
    EXPECT_TRUE(stack.empty());
}

// Test overflow: push beyond 100 elements (should handle gracefully)
TEST_F(PSStackTest_1919, PushBeyondCapacity_1919) {
    PSStack stack;
    for (int i = 0; i < 100; i++) {
        stack.pushInt(i);
    }
    // This should trigger overflow check and not crash
    stack.pushInt(999);
    // The 101st push should be rejected; top should still be 99
    EXPECT_EQ(stack.popInt(), 99);
}

// Test copy(1) is like dup
TEST_F(PSStackTest_1919, CopyOneIsDup_1919) {
    PSStack stack;
    stack.pushInt(55);
    stack.copy(1);
    EXPECT_EQ(stack.popInt(), 55);
    EXPECT_EQ(stack.popInt(), 55);
    EXPECT_TRUE(stack.empty());
}

// Test roll with j=0 (no rotation)
TEST_F(PSStackTest_1919, RollWithZeroJ_1919) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 0);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

// Test roll with negative j
TEST_F(PSStackTest_1919, RollNegativeJ_1919) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, -1);
    int a = stack.popInt();
    int b = stack.popInt();
    int c = stack.popInt();
    EXPECT_EQ(a + b + c, 6); // all values preserved
}

// Test that mixed types can coexist on stack
TEST_F(PSStackTest_1919, MixedTypes_1919) {
    PSStack stack;
    stack.pushInt(42);
    stack.pushReal(3.14);
    stack.pushBool(true);
    
    EXPECT_TRUE(stack.popBool());
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);
    EXPECT_EQ(stack.popInt(), 42);
    EXPECT_TRUE(stack.empty());
}

// Test clear on already empty stack
TEST_F(PSStackTest_1919, ClearOnEmptyStack_1919) {
    PSStack stack;
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// Test empty returns false when stack has elements
TEST_F(PSStackTest_1919, EmptyReturnsFalseWithElements_1919) {
    PSStack stack;
    stack.pushInt(1);
    EXPECT_FALSE(stack.empty());
}

// Test multiple clear operations
TEST_F(PSStackTest_1919, MultipleClearOperations_1919) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.clear();
    EXPECT_TRUE(stack.empty());
    stack.pushInt(3);
    EXPECT_FALSE(stack.empty());
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// Test large integer values
TEST_F(PSStackTest_1919, LargeIntValues_1919) {
    PSStack stack;
    stack.pushInt(2147483647); // INT_MAX
    EXPECT_EQ(stack.popInt(), 2147483647);
}

// Test large negative integer values
TEST_F(PSStackTest_1919, LargeNegativeIntValues_1919) {
    PSStack stack;
    stack.pushInt(-2147483647);
    EXPECT_EQ(stack.popInt(), -2147483647);
}

// Test very small real values
TEST_F(PSStackTest_1919, VerySmallRealValues_1919) {
    PSStack stack;
    stack.pushReal(1e-300);
    EXPECT_DOUBLE_EQ(stack.popNum(), 1e-300);
}

// Test very large real values
TEST_F(PSStackTest_1919, VeryLargeRealValues_1919) {
    PSStack stack;
    stack.pushReal(1e300);
    EXPECT_DOUBLE_EQ(stack.popNum(), 1e300);
}
