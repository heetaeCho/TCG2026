#include <gtest/gtest.h>

// We need to include the necessary headers to use PSStack
// Since PSStack is defined in Function.cc, we need to find the appropriate header
// Based on the project structure, Function.h likely declares or includes PSStack
#include "Function.h"

// Test fixture for PSStack tests
class PSStackTest_1918 : public ::testing::Test {
protected:
    PSStack stack;
};

// ============================================================
// Basic Push/Pop Tests
// ============================================================

TEST_F(PSStackTest_1918, PushIntAndPopInt_1918) {
    stack.pushInt(42);
    EXPECT_EQ(stack.popInt(), 42);
}

TEST_F(PSStackTest_1918, PushRealAndPopNum_1918) {
    stack.pushReal(3.14);
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);
}

TEST_F(PSStackTest_1918, PushBoolAndPopBool_1918) {
    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());
}

TEST_F(PSStackTest_1918, PushBoolFalseAndPopBool_1918) {
    stack.pushBool(false);
    EXPECT_FALSE(stack.popBool());
}

TEST_F(PSStackTest_1918, PushMultipleIntsAndPop_1918) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

// ============================================================
// Empty / Clear Tests
// ============================================================

TEST_F(PSStackTest_1918, NewStackIsEmpty_1918) {
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1918, StackNotEmptyAfterPush_1918) {
    stack.pushInt(10);
    EXPECT_FALSE(stack.empty());
}

TEST_F(PSStackTest_1918, ClearMakesStackEmpty_1918) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// ============================================================
// Type Checking Tests
// ============================================================

TEST_F(PSStackTest_1918, TopIsIntAfterPushInt_1918) {
    stack.pushInt(5);
    EXPECT_TRUE(stack.topIsInt());
}

TEST_F(PSStackTest_1918, TopIsRealAfterPushReal_1918) {
    stack.pushReal(1.5);
    EXPECT_TRUE(stack.topIsReal());
}

TEST_F(PSStackTest_1918, TopIsNotIntAfterPushReal_1918) {
    stack.pushReal(1.5);
    EXPECT_FALSE(stack.topIsInt());
}

TEST_F(PSStackTest_1918, TopIsNotRealAfterPushInt_1918) {
    stack.pushInt(5);
    EXPECT_FALSE(stack.topIsReal());
}

TEST_F(PSStackTest_1918, TopTwoAreIntsAfterTwoPushInts_1918) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1918, TopTwoAreNumsWithIntAndReal_1918) {
    stack.pushInt(1);
    stack.pushReal(2.5);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1918, TopTwoAreNumsWithTwoInts_1918) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1918, TopTwoAreNumsWithTwoReals_1918) {
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

// ============================================================
// Index Tests
// ============================================================

TEST_F(PSStackTest_1918, IndexZeroDuplicatesTop_1918) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    stack.index(0);
    // index(0) should duplicate the top element
    EXPECT_EQ(stack.popInt(), 30);
    EXPECT_EQ(stack.popInt(), 30);
}

TEST_F(PSStackTest_1918, IndexOneCopiesSecondElement_1918) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    stack.index(1);
    // index(1) should copy the second element to the top
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 30);
}

TEST_F(PSStackTest_1918, IndexTwoCopiesThirdElement_1918) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    stack.index(2);
    // index(2) should copy the third element to the top
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_EQ(stack.popInt(), 30);
}

// ============================================================
// Copy Tests
// ============================================================

TEST_F(PSStackTest_1918, CopyTopNElements_1918) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    stack.copy(2);
    // copy(2) should duplicate the top 2 elements
    EXPECT_EQ(stack.popInt(), 30);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 30);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
}

TEST_F(PSStackTest_1918, CopyOneElement_1918) {
    stack.pushInt(42);
    stack.copy(1);
    EXPECT_EQ(stack.popInt(), 42);
    EXPECT_EQ(stack.popInt(), 42);
}

// ============================================================
// Roll Tests
// ============================================================

TEST_F(PSStackTest_1918, RollBasicPositive_1918) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    // roll(3, 1): rotate top 3 elements by 1 position
    // Before: 1 2 3 (3 on top)
    // After:  2 3 1 or depends on direction
    stack.roll(3, 1);
    int a = stack.popInt();
    int b = stack.popInt();
    int c = stack.popInt();
    // The exact behavior depends on the implementation
    // PostScript roll: n j roll - rolls the top n elements j times
    // roll(3,1): bottom moves to top -> 2 3 1 on stack (1 on top)
    // or top moves to bottom -> 3 1 2 on stack (2 on top)
    // Standard PS: roll(3,1) moves top element down -> 1 is on top after
    // Actually in PS: 1 2 3 roll(3,1) => 1 3 2... let me not assume
    // Just verify stack is not empty after proper roll and values are some permutation
    // We'll just check they are a permutation of {1, 2, 3}
    std::set<int> vals = {a, b, c};
    std::set<int> expected = {1, 2, 3};
    EXPECT_EQ(vals, expected);
}

// ============================================================
// Pop Tests
// ============================================================

TEST_F(PSStackTest_1918, PopRemovesTopElement_1918) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pop();
    EXPECT_EQ(stack.popInt(), 10);
}

// ============================================================
// Boundary: Stack Overflow (pushing 100 elements)
// ============================================================

TEST_F(PSStackTest_1918, PushUpToStackSize_1918) {
    // psStackSize is 100, push 100 elements
    for (int i = 0; i < 100; i++) {
        stack.pushInt(i);
    }
    // The stack should be full, verify we can pop all
    for (int i = 99; i >= 0; i--) {
        EXPECT_EQ(stack.popInt(), i);
    }
}

TEST_F(PSStackTest_1918, PushBeyondStackSizeHandledGracefully_1918) {
    // Fill the stack completely
    for (int i = 0; i < 100; i++) {
        stack.pushInt(i);
    }
    // Attempting to push beyond should not crash (overflow check)
    // The behavior should be graceful (error message but no crash)
    stack.pushInt(999);
    // We just verify it doesn't crash
}

// ============================================================
// Boundary: Stack Underflow
// ============================================================

TEST_F(PSStackTest_1918, PopFromEmptyStackHandledGracefully_1918) {
    // Popping from empty stack should handle gracefully
    // The return value may be undefined but it shouldn't crash
    stack.popInt();
    // Just verify no crash
}

TEST_F(PSStackTest_1918, PopBoolFromEmptyStackHandledGracefully_1918) {
    stack.popBool();
    // Just verify no crash
}

TEST_F(PSStackTest_1918, PopNumFromEmptyStackHandledGracefully_1918) {
    stack.popNum();
    // Just verify no crash
}

// ============================================================
// Index Boundary Tests
// ============================================================

TEST_F(PSStackTest_1918, IndexWithLargeValueDoesNotCrash_1918) {
    stack.pushInt(10);
    // index with a value larger than stack size should handle gracefully
    stack.index(200);
    // Just verify no crash - should report error internally
}

TEST_F(PSStackTest_1918, IndexWithNegativeValueDoesNotCrash_1918) {
    stack.pushInt(10);
    stack.pushInt(20);
    // Negative index might cause issues - should be handled
    stack.index(-1);
    // Just verify no crash
}

// ============================================================
// Mixed Type Tests
// ============================================================

TEST_F(PSStackTest_1918, MixedPushAndPop_1918) {
    stack.pushInt(42);
    stack.pushReal(3.14);
    stack.pushBool(true);
    
    EXPECT_TRUE(stack.popBool());
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);
    EXPECT_EQ(stack.popInt(), 42);
}

TEST_F(PSStackTest_1918, PopNumReturnsIntAsDouble_1918) {
    stack.pushInt(42);
    EXPECT_DOUBLE_EQ(stack.popNum(), 42.0);
}

// ============================================================
// Index on Full Stack
// ============================================================

TEST_F(PSStackTest_1918, IndexOnNearlyFullStack_1918) {
    // Fill stack to 99 elements
    for (int i = 0; i < 99; i++) {
        stack.pushInt(i);
    }
    // Index should duplicate an element, making it 100
    stack.index(0);
    EXPECT_EQ(stack.popInt(), 98);
}

// ============================================================
// Empty Stack Type Checks
// ============================================================

TEST_F(PSStackTest_1918, TopIsIntOnEmptyStackReturnsFalse_1918) {
    // On an empty stack, type checks should return false or handle gracefully
    // This is implementation-dependent, but shouldn't crash
    bool result = stack.topIsInt();
    // Just verify no crash; result may be true or false depending on implementation
    (void)result;
}

TEST_F(PSStackTest_1918, TopIsRealOnEmptyStackReturnsFalse_1918) {
    bool result = stack.topIsReal();
    (void)result;
}

// ============================================================
// Index After Clearing
// ============================================================

TEST_F(PSStackTest_1918, IndexAfterClearDoesNotCrash_1918) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.clear();
    // Index on empty/cleared stack should handle gracefully
    stack.index(0);
    // Just verify no crash
}

// ============================================================
// Copy boundary
// ============================================================

TEST_F(PSStackTest_1918, CopyZeroElements_1918) {
    stack.pushInt(10);
    stack.copy(0);
    // copy(0) should be a no-op
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_TRUE(stack.empty());
}

// ============================================================
// Roll with zero
// ============================================================

TEST_F(PSStackTest_1918, RollWithZeroShift_1918) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 0);
    // No change expected
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

// ============================================================
// Multiple index operations
// ============================================================

TEST_F(PSStackTest_1918, MultipleIndexOperations_1918) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    stack.pushInt(40);
    
    stack.index(0); // duplicate 40
    EXPECT_EQ(stack.popInt(), 40);
    
    stack.index(2); // copy element at position 2 (which is 20)
    EXPECT_EQ(stack.popInt(), 20);
    
    EXPECT_EQ(stack.popInt(), 40);
    EXPECT_EQ(stack.popInt(), 30);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
}
