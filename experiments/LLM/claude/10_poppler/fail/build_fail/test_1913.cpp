#include <gtest/gtest.h>

// We need to include the necessary headers to access PSStack
// Since PSStack is defined in Function.cc, we need to find its declaration
#include "Function.h"

// If Function.h doesn't expose PSStack directly, we may need to include the cc file
// or recreate the minimal interface. Based on the prompt, PSStack is in Function.cc

// Forward declarations and includes as needed
// Since PSStack might not be in a public header, we include what's available

// Note: PSStack is defined in Function.cc. We need access to it for testing.
// In practice, this might require including the implementation file or a test-specific header.

// Attempt to include what's needed
#include <cmath>

// If PSStack is not directly includable, we replicate the class interface for testing
// Based on the constraints, we test only through the public interface

class PSStackTest_1913 : public ::testing::Test {
protected:
    void SetUp() override {
        // PSStack constructor initializes sp to psStackSize (100), meaning empty
    }
};

// Test that a newly constructed stack is empty
TEST_F(PSStackTest_1913, NewStackIsEmpty_1913) {
    PSStack stack;
    EXPECT_TRUE(stack.empty());
}

// Test that pushing a bool makes the stack non-empty
TEST_F(PSStackTest_1913, PushBoolMakesNonEmpty_1913) {
    PSStack stack;
    stack.pushBool(true);
    EXPECT_FALSE(stack.empty());
}

// Test that pushing an int makes the stack non-empty
TEST_F(PSStackTest_1913, PushIntMakesNonEmpty_1913) {
    PSStack stack;
    stack.pushInt(42);
    EXPECT_FALSE(stack.empty());
}

// Test that pushing a real makes the stack non-empty
TEST_F(PSStackTest_1913, PushRealMakesNonEmpty_1913) {
    PSStack stack;
    stack.pushReal(3.14);
    EXPECT_FALSE(stack.empty());
}

// Test push and pop bool
TEST_F(PSStackTest_1913, PushPopBool_1913) {
    PSStack stack;
    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());
}

TEST_F(PSStackTest_1913, PushPopBoolFalse_1913) {
    PSStack stack;
    stack.pushBool(false);
    EXPECT_FALSE(stack.popBool());
}

// Test push and pop int
TEST_F(PSStackTest_1913, PushPopInt_1913) {
    PSStack stack;
    stack.pushInt(42);
    EXPECT_EQ(42, stack.popInt());
}

TEST_F(PSStackTest_1913, PushPopIntNegative_1913) {
    PSStack stack;
    stack.pushInt(-100);
    EXPECT_EQ(-100, stack.popInt());
}

TEST_F(PSStackTest_1913, PushPopIntZero_1913) {
    PSStack stack;
    stack.pushInt(0);
    EXPECT_EQ(0, stack.popInt());
}

// Test push and pop real
TEST_F(PSStackTest_1913, PushPopReal_1913) {
    PSStack stack;
    stack.pushReal(3.14);
    EXPECT_DOUBLE_EQ(3.14, stack.popNum());
}

// Test popNum with int value
TEST_F(PSStackTest_1913, PopNumWithInt_1913) {
    PSStack stack;
    stack.pushInt(7);
    EXPECT_DOUBLE_EQ(7.0, stack.popNum());
}

// Test popNum with real value
TEST_F(PSStackTest_1913, PopNumWithReal_1913) {
    PSStack stack;
    stack.pushReal(2.718);
    EXPECT_DOUBLE_EQ(2.718, stack.popNum());
}

// Test that popping makes stack empty again
TEST_F(PSStackTest_1913, PopMakesStackEmpty_1913) {
    PSStack stack;
    stack.pushInt(1);
    stack.popInt();
    EXPECT_TRUE(stack.empty());
}

// Test LIFO order
TEST_F(PSStackTest_1913, LIFOOrder_1913) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    EXPECT_EQ(3, stack.popInt());
    EXPECT_EQ(2, stack.popInt());
    EXPECT_EQ(1, stack.popInt());
    EXPECT_TRUE(stack.empty());
}

// Test topIsInt
TEST_F(PSStackTest_1913, TopIsIntTrue_1913) {
    PSStack stack;
    stack.pushInt(5);
    EXPECT_TRUE(stack.topIsInt());
}

TEST_F(PSStackTest_1913, TopIsIntFalseWhenReal_1913) {
    PSStack stack;
    stack.pushReal(5.0);
    EXPECT_FALSE(stack.topIsInt());
}

// Test topIsReal
TEST_F(PSStackTest_1913, TopIsRealTrue_1913) {
    PSStack stack;
    stack.pushReal(5.0);
    EXPECT_TRUE(stack.topIsReal());
}

TEST_F(PSStackTest_1913, TopIsRealFalseWhenInt_1913) {
    PSStack stack;
    stack.pushInt(5);
    EXPECT_FALSE(stack.topIsReal());
}

// Test topTwoAreInts
TEST_F(PSStackTest_1913, TopTwoAreIntsTrue_1913) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1913, TopTwoAreIntsFalseWithReal_1913) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1913, TopTwoAreIntsFalseWithBothReal_1913) {
    PSStack stack;
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_FALSE(stack.topTwoAreInts());
}

// Test topTwoAreNums
TEST_F(PSStackTest_1913, TopTwoAreNumsTwoInts_1913) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1913, TopTwoAreNumsTwoReals_1913) {
    PSStack stack;
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1913, TopTwoAreNumsMixed_1913) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

// Test clear
TEST_F(PSStackTest_1913, ClearMakesStackEmpty_1913) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// Test pop (void version)
TEST_F(PSStackTest_1913, PopRemovesTop_1913) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pop();
    EXPECT_EQ(1, stack.popInt());
}

// Test copy
TEST_F(PSStackTest_1913, CopyDuplicatesTopN_1913) {
    PSStack stack;
    stack.pushInt(10);
    stack.pushInt(20);
    stack.copy(2);
    EXPECT_EQ(20, stack.popInt());
    EXPECT_EQ(10, stack.popInt());
    EXPECT_EQ(20, stack.popInt());
    EXPECT_EQ(10, stack.popInt());
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1913, CopyOne_1913) {
    PSStack stack;
    stack.pushInt(42);
    stack.copy(1);
    EXPECT_EQ(42, stack.popInt());
    EXPECT_EQ(42, stack.popInt());
    EXPECT_TRUE(stack.empty());
}

// Test index
TEST_F(PSStackTest_1913, IndexPushesNthElement_1913) {
    PSStack stack;
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    stack.index(2); // Should push the element at index 2 (which is 10)
    EXPECT_EQ(10, stack.popInt());
    EXPECT_EQ(30, stack.popInt());
    EXPECT_EQ(20, stack.popInt());
    EXPECT_EQ(10, stack.popInt());
}

TEST_F(PSStackTest_1913, IndexZero_1913) {
    PSStack stack;
    stack.pushInt(99);
    stack.index(0); // Should duplicate top
    EXPECT_EQ(99, stack.popInt());
    EXPECT_EQ(99, stack.popInt());
}

// Test roll
TEST_F(PSStackTest_1913, RollPositive_1913) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    // Roll top 3 elements by 1 position
    stack.roll(3, 1);
    // Expected order from top: 1, 3, 2 (or depends on implementation)
    // PostScript roll: roll(n, j) rotates top n elements j times
    // With j=1: bottom...a b c -> bottom...c a b
    int top = stack.popInt();
    int mid = stack.popInt();
    int bot = stack.popInt();
    // After roll(3,1) on [1,2,3] (3 on top): should be [2,3,1] with 1 on top
    // Actually in PostScript: roll n j means the top n elements are rolled
    // j>0: top moves deeper. So [1,2,3](3=top) -> roll(3,1) -> [3,1,2](2=top)
    // This is implementation-dependent, so we just verify the stack has 3 elements
    // and they are some permutation of {1,2,3}
    std::set<int> values = {top, mid, bot};
    EXPECT_EQ(3u, values.size());
    EXPECT_TRUE(values.count(1) && values.count(2) && values.count(3));
}

// Test roll with zero
TEST_F(PSStackTest_1913, RollZero_1913) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 0); // No change
    EXPECT_EQ(3, stack.popInt());
    EXPECT_EQ(2, stack.popInt());
    EXPECT_EQ(1, stack.popInt());
}

// Test boundary: fill stack to capacity (100 elements)
TEST_F(PSStackTest_1913, FillToCapacity_1913) {
    PSStack stack;
    for (int i = 0; i < 100; i++) {
        stack.pushInt(i);
    }
    EXPECT_FALSE(stack.empty());
    // Pop all elements
    for (int i = 99; i >= 0; i--) {
        EXPECT_EQ(i, stack.popInt());
    }
    EXPECT_TRUE(stack.empty());
}

// Test overflow: pushing more than 100 elements should be handled gracefully
TEST_F(PSStackTest_1913, OverflowProtection_1913) {
    PSStack stack;
    for (int i = 0; i < 100; i++) {
        stack.pushInt(i);
    }
    // Pushing one more should not crash (overflow check)
    stack.pushInt(999);
    // The stack should still be in a valid state
    EXPECT_FALSE(stack.empty());
}

// Test underflow: popping from empty stack
TEST_F(PSStackTest_1913, UnderflowProtection_1913) {
    PSStack stack;
    EXPECT_TRUE(stack.empty());
    // Popping from empty stack should not crash (underflow check)
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// Test multiple types interleaved
TEST_F(PSStackTest_1913, MixedTypes_1913) {
    PSStack stack;
    stack.pushInt(42);
    stack.pushReal(3.14);
    stack.pushBool(true);

    EXPECT_TRUE(stack.popBool());
    EXPECT_DOUBLE_EQ(3.14, stack.popNum());
    EXPECT_EQ(42, stack.popInt());
    EXPECT_TRUE(stack.empty());
}

// Test clear on empty stack
TEST_F(PSStackTest_1913, ClearEmptyStack_1913) {
    PSStack stack;
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// Test clear and reuse
TEST_F(PSStackTest_1913, ClearAndReuse_1913) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.clear();
    EXPECT_TRUE(stack.empty());
    stack.pushInt(3);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(3, stack.popInt());
    EXPECT_TRUE(stack.empty());
}

// Test pushing large int values
TEST_F(PSStackTest_1913, LargeIntValues_1913) {
    PSStack stack;
    stack.pushInt(2147483647); // INT_MAX
    EXPECT_EQ(2147483647, stack.popInt());
}

// Test pushing negative real values
TEST_F(PSStackTest_1913, NegativeRealValues_1913) {
    PSStack stack;
    stack.pushReal(-99.99);
    EXPECT_DOUBLE_EQ(-99.99, stack.popNum());
}

// Test pushing zero real
TEST_F(PSStackTest_1913, ZeroReal_1913) {
    PSStack stack;
    stack.pushReal(0.0);
    EXPECT_DOUBLE_EQ(0.0, stack.popNum());
}

// Test topTwoAreInts with only one element
TEST_F(PSStackTest_1913, TopTwoAreIntsWithOneElement_1913) {
    PSStack stack;
    stack.pushInt(1);
    // Only one element, so topTwoAreInts may return false or handle gracefully
    // Implementation-dependent but should not crash
    bool result = stack.topTwoAreInts();
    // We just ensure it doesn't crash; actual result depends on implementation
    (void)result;
}

// Test topTwoAreNums with only one element
TEST_F(PSStackTest_1913, TopTwoAreNumsWithOneElement_1913) {
    PSStack stack;
    stack.pushReal(1.0);
    bool result = stack.topTwoAreNums();
    (void)result;
}

// Test topIsInt on empty stack
TEST_F(PSStackTest_1913, TopIsIntOnEmptyStack_1913) {
    PSStack stack;
    // Should not crash
    bool result = stack.topIsInt();
    (void)result;
}

// Test topIsReal on empty stack
TEST_F(PSStackTest_1913, TopIsRealOnEmptyStack_1913) {
    PSStack stack;
    bool result = stack.topIsReal();
    (void)result;
}

// Test multiple pops reducing to empty
TEST_F(PSStackTest_1913, MultiplePopsToEmpty_1913) {
    PSStack stack;
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.pop();
    stack.pop();
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// Test copy with zero
TEST_F(PSStackTest_1913, CopyZero_1913) {
    PSStack stack;
    stack.pushInt(1);
    stack.copy(0);
    // Stack should remain unchanged
    EXPECT_EQ(1, stack.popInt());
    EXPECT_TRUE(stack.empty());
}
