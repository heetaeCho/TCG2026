#include <gtest/gtest.h>
#include "Function.h"  // Include the header where PSStack and PSObject are defined

class PSStackTest_1909 : public ::testing::Test {
protected:
    PSStack stack;

    // Reset the stack before each test
    void SetUp() override {
        stack.clear();
    }
};

TEST_F(PSStackTest_1909, PushRealAddsToStack_1909) {
    stack.pushReal(3.14);
    EXPECT_EQ(stack.popNum(), 3.14);
}

TEST_F(PSStackTest_1909, PushBoolAddsToStack_1909) {
    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());
}

TEST_F(PSStackTest_1909, PushIntAddsToStack_1909) {
    stack.pushInt(42);
    EXPECT_EQ(stack.popInt(), 42);
}

TEST_F(PSStackTest_1909, PopOnEmptyStackThrowsError_1909) {
    EXPECT_THROW(stack.pop(), std::out_of_range);  // Assuming pop() throws an error on underflow
}

TEST_F(PSStackTest_1909, OverflowPreventsPush_1909) {
    for (int i = 0; i < 100; ++i) {
        stack.pushReal(i);
    }
    EXPECT_THROW(stack.pushReal(101), std::overflow_error);  // Assuming overflow error is thrown
}

TEST_F(PSStackTest_1909, TopIsIntReturnsTrueForInt_1909) {
    stack.pushInt(42);
    EXPECT_TRUE(stack.topIsInt());
}

TEST_F(PSStackTest_1909, TopIsRealReturnsTrueForReal_1909) {
    stack.pushReal(3.14);
    EXPECT_TRUE(stack.topIsReal());
}

TEST_F(PSStackTest_1909, TopTwoAreIntsReturnsTrueForTwoInts_1909) {
    stack.pushInt(42);
    stack.pushInt(43);
    EXPECT_TRUE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1909, CheckUnderflowPreventsPop_1909) {
    EXPECT_THROW(stack.pop(), std::out_of_range);  // Assuming underflow condition causes exception
}

TEST_F(PSStackTest_1909, PushAfterClearWorks_1909) {
    stack.pushReal(3.14);
    stack.clear();
    stack.pushInt(42);
    EXPECT_EQ(stack.popInt(), 42);
}

TEST_F(PSStackTest_1909, CheckTypeReturnsTrueForCorrectTypes_1909) {
    stack.pushReal(3.14);
    stack.pushInt(42);
    EXPECT_TRUE(stack.checkType(psReal, psReal));  // Should return true for same types
    EXPECT_FALSE(stack.checkType(psReal, psInt));  // Should return false for different types
}

TEST_F(PSStackTest_1909, RollWorksAsExpected_1909) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.roll(3, 1);  // roll top 3 items, 1st position will be moved to the end
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
}

TEST_F(PSStackTest_1909, CopyWorksAsExpected_1909) {
    stack.pushInt(1);
    stack.pushReal(3.14);
    stack.copy(2);  // copy top 2 elements
    EXPECT_EQ(stack.popReal(), 3.14);
    EXPECT_EQ(stack.popInt(), 1);
}