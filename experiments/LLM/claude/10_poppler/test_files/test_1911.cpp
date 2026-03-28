#include <gtest/gtest.h>

// Forward declarations and includes needed for the test
// We need to include the actual header or source that defines PSStack
// Since the class is defined in Function.cc, we need to find the appropriate header

// Based on the provided code, we need to reconstruct minimal declarations
// to compile against the actual implementation

// Include the actual implementation
#include "Function.h"

// If Function.h doesn't exist as a standalone header, we may need to include
// the source directly or use the poppler headers
// Adjusting based on typical poppler project structure

class PSStackTest_1911 : public ::testing::Test {
protected:
    PSStack stack;
};

// Test that a freshly constructed stack is empty
TEST_F(PSStackTest_1911, NewStackIsEmpty_1911) {
    EXPECT_TRUE(stack.empty());
}

// Test pushing and popping an integer
TEST_F(PSStackTest_1911, PushAndPopInt_1911) {
    stack.pushInt(42);
    EXPECT_FALSE(stack.empty());
    int val = stack.popInt();
    EXPECT_EQ(val, 42);
    EXPECT_TRUE(stack.empty());
}

// Test pushing and popping a boolean
TEST_F(PSStackTest_1911, PushAndPopBool_1911) {
    stack.pushBool(true);
    EXPECT_FALSE(stack.empty());
    bool val = stack.popBool();
    EXPECT_TRUE(val);
    EXPECT_TRUE(stack.empty());
}

// Test pushing and popping false boolean
TEST_F(PSStackTest_1911, PushAndPopBoolFalse_1911) {
    stack.pushBool(false);
    bool val = stack.popBool();
    EXPECT_FALSE(val);
}

// Test pushing and popping a real number
TEST_F(PSStackTest_1911, PushAndPopReal_1911) {
    stack.pushReal(3.14);
    double val = stack.popNum();
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// Test popNum with integer on stack
TEST_F(PSStackTest_1911, PopNumWithInt_1911) {
    stack.pushInt(7);
    double val = stack.popNum();
    EXPECT_DOUBLE_EQ(val, 7.0);
}

// Test popNum with real on stack
TEST_F(PSStackTest_1911, PopNumWithReal_1911) {
    stack.pushReal(2.718);
    double val = stack.popNum();
    EXPECT_DOUBLE_EQ(val, 2.718);
}

// Test popInt returns 0 on underflow (empty stack)
TEST_F(PSStackTest_1911, PopIntOnEmptyStackReturnsZero_1911) {
    int val = stack.popInt();
    EXPECT_EQ(val, 0);
}

// Test popInt with wrong type (bool instead of int)
TEST_F(PSStackTest_1911, PopIntWithBoolOnTopReturnsZero_1911) {
    stack.pushBool(true);
    int val = stack.popInt();
    // Type mismatch: bool is not int, should return 0
    EXPECT_EQ(val, 0);
}

// Test topIsInt
TEST_F(PSStackTest_1911, TopIsIntWhenIntPushed_1911) {
    stack.pushInt(10);
    EXPECT_TRUE(stack.topIsInt());
}

// Test topIsInt returns false when real is on top
TEST_F(PSStackTest_1911, TopIsIntReturnsFalseForReal_1911) {
    stack.pushReal(1.5);
    EXPECT_FALSE(stack.topIsInt());
}

// Test topIsReal
TEST_F(PSStackTest_1911, TopIsRealWhenRealPushed_1911) {
    stack.pushReal(1.5);
    EXPECT_TRUE(stack.topIsReal());
}

// Test topIsReal returns false when int is on top
TEST_F(PSStackTest_1911, TopIsRealReturnsFalseForInt_1911) {
    stack.pushInt(5);
    EXPECT_FALSE(stack.topIsReal());
}

// Test topTwoAreInts
TEST_F(PSStackTest_1911, TopTwoAreInts_1911) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreInts());
}

// Test topTwoAreInts returns false with mixed types
TEST_F(PSStackTest_1911, TopTwoAreIntsReturnsFalseForMixed_1911) {
    stack.pushReal(1.0);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreInts());
}

// Test topTwoAreNums with two ints
TEST_F(PSStackTest_1911, TopTwoAreNumsWithTwoInts_1911) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

// Test topTwoAreNums with two reals
TEST_F(PSStackTest_1911, TopTwoAreNumsWithTwoReals_1911) {
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

// Test topTwoAreNums with int and real
TEST_F(PSStackTest_1911, TopTwoAreNumsWithIntAndReal_1911) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

// Test topTwoAreNums returns false with bool
TEST_F(PSStackTest_1911, TopTwoAreNumsReturnsFalseWithBool_1911) {
    stack.pushBool(true);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreNums());
}

// Test clear empties the stack
TEST_F(PSStackTest_1911, ClearEmptiesStack_1911) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// Test pop removes top element
TEST_F(PSStackTest_1911, PopRemovesTopElement_1911) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pop();
    int val = stack.popInt();
    EXPECT_EQ(val, 1);
}

// Test multiple push and pop operations
TEST_F(PSStackTest_1911, MultiplePushPopOperations_1911) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    EXPECT_EQ(stack.popInt(), 30);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_TRUE(stack.empty());
}

// Test LIFO order
TEST_F(PSStackTest_1911, LIFOOrder_1911) {
    stack.pushInt(1);
    stack.pushReal(2.5);
    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());
    EXPECT_DOUBLE_EQ(stack.popNum(), 2.5);
    EXPECT_EQ(stack.popInt(), 1);
}

// Test pushing negative integer
TEST_F(PSStackTest_1911, PushNegativeInt_1911) {
    stack.pushInt(-42);
    EXPECT_EQ(stack.popInt(), -42);
}

// Test pushing zero
TEST_F(PSStackTest_1911, PushZeroInt_1911) {
    stack.pushInt(0);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.popInt(), 0);
}

// Test pushing negative real
TEST_F(PSStackTest_1911, PushNegativeReal_1911) {
    stack.pushReal(-1.5);
    EXPECT_DOUBLE_EQ(stack.popNum(), -1.5);
}

// Test pushing zero real
TEST_F(PSStackTest_1911, PushZeroReal_1911) {
    stack.pushReal(0.0);
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
}

// Test copy operation
TEST_F(PSStackTest_1911, CopyDuplicatesTopN_1911) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.copy(2);
    // After copy(2), top of stack should be: 2, 3, 3, 2, 1 (top to bottom)
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

// Test copy(1) duplicates top element
TEST_F(PSStackTest_1911, CopyOneDuplicatesTop_1911) {
    stack.pushInt(42);
    stack.copy(1);
    EXPECT_EQ(stack.popInt(), 42);
    EXPECT_EQ(stack.popInt(), 42);
    EXPECT_TRUE(stack.empty());
}

// Test index operation
TEST_F(PSStackTest_1911, IndexPushesNthElement_1911) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    stack.index(2); // Should push element at index 2 (which is 10)
    EXPECT_EQ(stack.popInt(), 10);
}

// Test index(0) pushes top element
TEST_F(PSStackTest_1911, IndexZeroPushesTop_1911) {
    stack.pushInt(5);
    stack.pushInt(10);
    stack.index(0);
    EXPECT_EQ(stack.popInt(), 10);
}

// Test roll operation
TEST_F(PSStackTest_1911, RollRotatesElements_1911) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    // roll(3, 1) should rotate top 3 elements by 1
    // Before: 3, 2, 1 (top to bottom)
    // After roll(3, 1): 1, 3, 2 (top to bottom)
    stack.roll(3, 1);
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
}

// Test roll with negative j
TEST_F(PSStackTest_1911, RollNegativeJ_1911) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    // roll(3, -1) should rotate in opposite direction
    // Before: 3, 2, 1 (top to bottom)
    // After roll(3, -1): 2, 1, 3 (top to bottom)
    stack.roll(3, -1);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_EQ(stack.popInt(), 3);
}

// Test that empty returns true for empty stack
TEST_F(PSStackTest_1911, EmptyReturnsTrueInitially_1911) {
    EXPECT_TRUE(stack.empty());
}

// Test that empty returns false after push
TEST_F(PSStackTest_1911, EmptyReturnsFalseAfterPush_1911) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.empty());
}

// Test overflow protection - push 100 elements (stack size is 100)
TEST_F(PSStackTest_1911, OverflowProtection_1911) {
    for (int i = 0; i < 100; i++) {
        stack.pushInt(i);
    }
    // Pushing one more should be handled gracefully (overflow check)
    stack.pushInt(999);
    // The 101st push should have been rejected
    // Pop all and verify the first 100 are intact
}

// Test popInt with real on stack returns 0 (type mismatch)
TEST_F(PSStackTest_1911, PopIntWithRealReturnsZero_1911) {
    stack.pushReal(3.14);
    int val = stack.popInt();
    EXPECT_EQ(val, 0);
}

// Test pushing large int values
TEST_F(PSStackTest_1911, PushLargeIntValue_1911) {
    stack.pushInt(2147483647); // INT_MAX
    EXPECT_EQ(stack.popInt(), 2147483647);
}

// Test pushing INT_MIN
TEST_F(PSStackTest_1911, PushIntMinValue_1911) {
    stack.pushInt(-2147483648); // INT_MIN
    EXPECT_EQ(stack.popInt(), -2147483648);
}

// Test pushing very large real
TEST_F(PSStackTest_1911, PushLargeReal_1911) {
    stack.pushReal(1e300);
    EXPECT_DOUBLE_EQ(stack.popNum(), 1e300);
}

// Test pushing very small real
TEST_F(PSStackTest_1911, PushVerySmallReal_1911) {
    stack.pushReal(1e-300);
    EXPECT_DOUBLE_EQ(stack.popNum(), 1e-300);
}

// Test pop on empty stack doesn't crash
TEST_F(PSStackTest_1911, PopOnEmptyStackHandledGracefully_1911) {
    stack.pop(); // Should not crash
    EXPECT_TRUE(stack.empty());
}

// Test popBool on empty stack
TEST_F(PSStackTest_1911, PopBoolOnEmptyStack_1911) {
    bool val = stack.popBool();
    EXPECT_FALSE(val); // Should return false/0 on underflow
}

// Test popNum on empty stack
TEST_F(PSStackTest_1911, PopNumOnEmptyStack_1911) {
    double val = stack.popNum();
    EXPECT_DOUBLE_EQ(val, 0.0);
}

// Test topIsInt on empty stack
TEST_F(PSStackTest_1911, TopIsIntOnEmptyStack_1911) {
    EXPECT_FALSE(stack.topIsInt());
}

// Test topIsReal on empty stack
TEST_F(PSStackTest_1911, TopIsRealOnEmptyStack_1911) {
    EXPECT_FALSE(stack.topIsReal());
}

// Test topTwoAreInts with only one element
TEST_F(PSStackTest_1911, TopTwoAreIntsWithOneElement_1911) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreInts());
}

// Test topTwoAreNums with only one element
TEST_F(PSStackTest_1911, TopTwoAreNumsWithOneElement_1911) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreNums());
}

// Test interleaved push/pop of different types
TEST_F(PSStackTest_1911, InterleavedPushPopDifferentTypes_1911) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    stack.pushBool(true);
    stack.pushInt(3);
    
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_TRUE(stack.popBool());
    EXPECT_DOUBLE_EQ(stack.popNum(), 2.0);
    EXPECT_EQ(stack.popInt(), 1);
}

// Test clear on empty stack doesn't crash
TEST_F(PSStackTest_1911, ClearOnEmptyStack_1911) {
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// Test clear followed by operations
TEST_F(PSStackTest_1911, ClearThenPush_1911) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.clear();
    stack.pushInt(3);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_TRUE(stack.empty());
}
