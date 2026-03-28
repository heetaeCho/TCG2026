#include <gtest/gtest.h>

// Include necessary headers from the poppler project
// We need to include the file that contains PSStack definition
// Since PSStack is defined in Function.cc, we need the corresponding header
#include "Function.h"

// If Function.h doesn't expose PSStack directly, we may need to include Function.cc
// This depends on the project structure. Let's try including what's needed.

class PSStackTest_2789 : public ::testing::Test {
protected:
    void SetUp() override {
        // Each test gets a fresh stack
    }
};

// Test: Default constructor creates an empty stack
TEST_F(PSStackTest_2789, DefaultConstructorCreatesEmptyStack_2789) {
    PSStack stack;
    EXPECT_TRUE(stack.empty());
}

// Test: Push and pop a boolean value (true)
TEST_F(PSStackTest_2789, PushPopBoolTrue_2789) {
    PSStack stack;
    stack.pushBool(true);
    EXPECT_FALSE(stack.empty());
    EXPECT_TRUE(stack.popBool());
}

// Test: Push and pop a boolean value (false)
TEST_F(PSStackTest_2789, PushPopBoolFalse_2789) {
    PSStack stack;
    stack.pushBool(false);
    EXPECT_FALSE(stack.empty());
    EXPECT_FALSE(stack.popBool());
}

// Test: Push and pop an integer value
TEST_F(PSStackTest_2789, PushPopInt_2789) {
    PSStack stack;
    stack.pushInt(42);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(42, stack.popInt());
}

// Test: Push and pop a negative integer
TEST_F(PSStackTest_2789, PushPopNegativeInt_2789) {
    PSStack stack;
    stack.pushInt(-100);
    EXPECT_EQ(-100, stack.popInt());
}

// Test: Push and pop zero integer
TEST_F(PSStackTest_2789, PushPopZeroInt_2789) {
    PSStack stack;
    stack.pushInt(0);
    EXPECT_EQ(0, stack.popInt());
}

// Test: Push and pop a real value
TEST_F(PSStackTest_2789, PushPopReal_2789) {
    PSStack stack;
    stack.pushReal(3.14);
    EXPECT_DOUBLE_EQ(3.14, stack.popNum());
}

// Test: Push and pop a negative real value
TEST_F(PSStackTest_2789, PushPopNegativeReal_2789) {
    PSStack stack;
    stack.pushReal(-2.718);
    EXPECT_DOUBLE_EQ(-2.718, stack.popNum());
}

// Test: popNum works with integer values too
TEST_F(PSStackTest_2789, PopNumWithInt_2789) {
    PSStack stack;
    stack.pushInt(7);
    EXPECT_DOUBLE_EQ(7.0, stack.popNum());
}

// Test: Stack is LIFO - multiple pushes and pops
TEST_F(PSStackTest_2789, StackIsLIFO_2789) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    EXPECT_EQ(3, stack.popInt());
    EXPECT_EQ(2, stack.popInt());
    EXPECT_EQ(1, stack.popInt());
    EXPECT_TRUE(stack.empty());
}

// Test: topIsInt returns true when top is integer
TEST_F(PSStackTest_2789, TopIsIntTrue_2789) {
    PSStack stack;
    stack.pushInt(10);
    EXPECT_TRUE(stack.topIsInt());
}

// Test: topIsInt returns false when top is real
TEST_F(PSStackTest_2789, TopIsIntFalseForReal_2789) {
    PSStack stack;
    stack.pushReal(1.5);
    EXPECT_FALSE(stack.topIsInt());
}

// Test: topIsInt returns false when top is bool
TEST_F(PSStackTest_2789, TopIsIntFalseForBool_2789) {
    PSStack stack;
    stack.pushBool(true);
    EXPECT_FALSE(stack.topIsInt());
}

// Test: topIsReal returns true when top is real
TEST_F(PSStackTest_2789, TopIsRealTrue_2789) {
    PSStack stack;
    stack.pushReal(2.5);
    EXPECT_TRUE(stack.topIsReal());
}

// Test: topIsReal returns false when top is int
TEST_F(PSStackTest_2789, TopIsRealFalseForInt_2789) {
    PSStack stack;
    stack.pushInt(5);
    EXPECT_FALSE(stack.topIsReal());
}

// Test: topTwoAreInts returns true when top two are ints
TEST_F(PSStackTest_2789, TopTwoAreIntsTrue_2789) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreInts());
}

// Test: topTwoAreInts returns false when one is real
TEST_F(PSStackTest_2789, TopTwoAreIntsFalseWithReal_2789) {
    PSStack stack;
    stack.pushReal(1.0);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreInts());
}

// Test: topTwoAreNums returns true for two ints
TEST_F(PSStackTest_2789, TopTwoAreNumsTwoInts_2789) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

// Test: topTwoAreNums returns true for two reals
TEST_F(PSStackTest_2789, TopTwoAreNumsTwoReals_2789) {
    PSStack stack;
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

// Test: topTwoAreNums returns true for mixed int and real
TEST_F(PSStackTest_2789, TopTwoAreNumsMixed_2789) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

// Test: topTwoAreNums returns false when one is bool
TEST_F(PSStackTest_2789, TopTwoAreNumsFalseWithBool_2789) {
    PSStack stack;
    stack.pushBool(true);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreNums());
}

// Test: pop removes top element
TEST_F(PSStackTest_2789, PopRemovesTopElement_2789) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pop();
    EXPECT_EQ(1, stack.popInt());
}

// Test: clear empties the stack
TEST_F(PSStackTest_2789, ClearEmptiesStack_2789) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// Test: clear on empty stack
TEST_F(PSStackTest_2789, ClearOnEmptyStack_2789) {
    PSStack stack;
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// Test: index duplicates element at position i onto top
TEST_F(PSStackTest_2789, IndexDuplicatesElement_2789) {
    PSStack stack;
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    // index(0) should duplicate top element (30)
    stack.index(0);
    EXPECT_EQ(30, stack.popInt());
    EXPECT_EQ(30, stack.popInt());
}

// Test: index with deeper element
TEST_F(PSStackTest_2789, IndexDeeperElement_2789) {
    PSStack stack;
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    // index(2) should duplicate element at position 2 (10)
    stack.index(2);
    EXPECT_EQ(10, stack.popInt());
}

// Test: copy duplicates top n elements
TEST_F(PSStackTest_2789, CopyTopNElements_2789) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.copy(2);
    // After copy(2), stack should be: 1 2 3 2 3
    EXPECT_EQ(3, stack.popInt());
    EXPECT_EQ(2, stack.popInt());
    EXPECT_EQ(3, stack.popInt());
    EXPECT_EQ(2, stack.popInt());
    EXPECT_EQ(1, stack.popInt());
}

// Test: copy(1) duplicates just the top
TEST_F(PSStackTest_2789, CopyOneElement_2789) {
    PSStack stack;
    stack.pushInt(42);
    stack.copy(1);
    EXPECT_EQ(42, stack.popInt());
    EXPECT_EQ(42, stack.popInt());
    EXPECT_TRUE(stack.empty());
}

// Test: roll with positive j
TEST_F(PSStackTest_2789, RollPositive_2789) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    // roll(3, 1): rotate top 3 elements by 1
    // Before: 1 2 3 (top is 3)
    // After roll(3,1): 3 1 2 (top is 2)
    stack.roll(3, 1);
    EXPECT_EQ(2, stack.popInt());
    EXPECT_EQ(1, stack.popInt());
    EXPECT_EQ(3, stack.popInt());
}

// Test: roll with negative j
TEST_F(PSStackTest_2789, RollNegative_2789) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    // roll(3, -1): rotate top 3 elements by -1
    stack.roll(3, -1);
    EXPECT_EQ(1, stack.popInt());
    EXPECT_EQ(3, stack.popInt());
    EXPECT_EQ(2, stack.popInt());
}

// Test: roll with j = 0 (no change)
TEST_F(PSStackTest_2789, RollZero_2789) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 0);
    EXPECT_EQ(3, stack.popInt());
    EXPECT_EQ(2, stack.popInt());
    EXPECT_EQ(1, stack.popInt());
}

// Test: empty returns true for new stack
TEST_F(PSStackTest_2789, EmptyOnNewStack_2789) {
    PSStack stack;
    EXPECT_TRUE(stack.empty());
}

// Test: empty returns false after push
TEST_F(PSStackTest_2789, NotEmptyAfterPush_2789) {
    PSStack stack;
    stack.pushInt(1);
    EXPECT_FALSE(stack.empty());
}

// Test: empty returns true after push and pop
TEST_F(PSStackTest_2789, EmptyAfterPushAndPop_2789) {
    PSStack stack;
    stack.pushInt(1);
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// Test: Overflow - push 100 elements (stack size is 100)
TEST_F(PSStackTest_2789, FillStackToCapacity_2789) {
    PSStack stack;
    for (int i = 0; i < 100; i++) {
        stack.pushInt(i);
    }
    EXPECT_FALSE(stack.empty());
    // Verify top element
    EXPECT_EQ(99, stack.popInt());
}

// Test: Overflow - pushing beyond capacity should handle gracefully
TEST_F(PSStackTest_2789, OverflowHandling_2789) {
    PSStack stack;
    for (int i = 0; i < 100; i++) {
        stack.pushInt(i);
    }
    // This push should be rejected (overflow)
    stack.pushInt(999);
    // The top should still be the last valid push
    EXPECT_EQ(99, stack.popInt());
}

// Test: Underflow - popping from empty stack
TEST_F(PSStackTest_2789, UnderflowPopInt_2789) {
    PSStack stack;
    // Popping from empty stack - should handle gracefully
    // The behavior is implementation-defined but shouldn't crash
    int val = stack.popInt();
    (void)val; // We just verify it doesn't crash
}

// Test: Underflow - popBool from empty stack
TEST_F(PSStackTest_2789, UnderflowPopBool_2789) {
    PSStack stack;
    bool val = stack.popBool();
    (void)val;
}

// Test: Underflow - popNum from empty stack
TEST_F(PSStackTest_2789, UnderflowPopNum_2789) {
    PSStack stack;
    double val = stack.popNum();
    (void)val;
}

// Test: Mixed type pushes and pops
TEST_F(PSStackTest_2789, MixedTypePushPop_2789) {
    PSStack stack;
    stack.pushInt(42);
    stack.pushReal(3.14);
    stack.pushBool(true);
    
    EXPECT_TRUE(stack.popBool());
    EXPECT_DOUBLE_EQ(3.14, stack.popNum());
    EXPECT_EQ(42, stack.popInt());
    EXPECT_TRUE(stack.empty());
}

// Test: Push real value of zero
TEST_F(PSStackTest_2789, PushRealZero_2789) {
    PSStack stack;
    stack.pushReal(0.0);
    EXPECT_DOUBLE_EQ(0.0, stack.popNum());
}

// Test: Large integer values
TEST_F(PSStackTest_2789, PushLargeInt_2789) {
    PSStack stack;
    stack.pushInt(2147483647); // INT_MAX
    EXPECT_EQ(2147483647, stack.popInt());
}

// Test: Large negative integer values
TEST_F(PSStackTest_2789, PushMinInt_2789) {
    PSStack stack;
    stack.pushInt(-2147483648); // INT_MIN
    EXPECT_EQ(-2147483648, stack.popInt());
}

// Test: topIsInt on empty stack
TEST_F(PSStackTest_2789, TopIsIntOnEmptyStack_2789) {
    PSStack stack;
    // Should handle gracefully - likely returns false
    EXPECT_FALSE(stack.topIsInt());
}

// Test: topIsReal on empty stack
TEST_F(PSStackTest_2789, TopIsRealOnEmptyStack_2789) {
    PSStack stack;
    EXPECT_FALSE(stack.topIsReal());
}

// Test: topTwoAreInts with only one element
TEST_F(PSStackTest_2789, TopTwoAreIntsOneElement_2789) {
    PSStack stack;
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreInts());
}

// Test: topTwoAreNums with only one element
TEST_F(PSStackTest_2789, TopTwoAreNumsOneElement_2789) {
    PSStack stack;
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreNums());
}

// Test: pop on empty stack doesn't crash
TEST_F(PSStackTest_2789, PopOnEmptyStack_2789) {
    PSStack stack;
    stack.pop(); // Should handle gracefully
    EXPECT_TRUE(stack.empty());
}

// Test: copy(0) should be a no-op
TEST_F(PSStackTest_2789, CopyZero_2789) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.copy(0);
    EXPECT_EQ(2, stack.popInt());
    EXPECT_EQ(1, stack.popInt());
    EXPECT_TRUE(stack.empty());
}

// Test: roll with n=1 should be a no-op regardless of j
TEST_F(PSStackTest_2789, RollSingleElement_2789) {
    PSStack stack;
    stack.pushInt(42);
    stack.roll(1, 5);
    EXPECT_EQ(42, stack.popInt());
}

// Test: Multiple clear and push cycles
TEST_F(PSStackTest_2789, MultipleClearCycles_2789) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.clear();
    EXPECT_TRUE(stack.empty());
    
    stack.pushInt(3);
    stack.pushInt(4);
    EXPECT_EQ(4, stack.popInt());
    EXPECT_EQ(3, stack.popInt());
    EXPECT_TRUE(stack.empty());
}

// Test: Very large real value
TEST_F(PSStackTest_2789, PushVeryLargeReal_2789) {
    PSStack stack;
    stack.pushReal(1e308);
    EXPECT_DOUBLE_EQ(1e308, stack.popNum());
}

// Test: Very small real value
TEST_F(PSStackTest_2789, PushVerySmallReal_2789) {
    PSStack stack;
    stack.pushReal(1e-308);
    EXPECT_DOUBLE_EQ(1e-308, stack.popNum());
}
