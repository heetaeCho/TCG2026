#include <gtest/gtest.h>



// Mock dependencies if any (none needed in this case)



class PSStackTest_1915 : public ::testing::Test {

protected:

    PSStack* stack;



    void SetUp() override {

        stack = new PSStack();

    }



    void TearDown() override {

        delete stack;

    }

};



TEST_F(PSStackTest_1915, TopTwoAreInts_ReturnsFalse_EmptyStack_1915) {

    EXPECT_FALSE(stack->topTwoAreInts());

}



TEST_F(PSStackTest_1915, TopTwoAreInts_ReturnsFalse_OneElementStack_1915) {

    stack->pushInt(42);

    EXPECT_FALSE(stack->topTwoAreInts());

}



TEST_F(PSStackTest_1915, TopTwoAreInts_ReturnsTrue_TwoIntegersOnTop_1915) {

    stack->pushInt(42);

    stack->pushInt(84);

    EXPECT_TRUE(stack->topTwoAreInts());

}



TEST_F(PSStackTest_1915, TopTwoAreInts_ReturnsFalse_TopElementNotInt_1915) {

    stack->pushReal(3.14);

    stack->pushInt(42);

    EXPECT_FALSE(stack->topTwoAreInts());

}



TEST_F(PSStackTest_1915, TopTwoAreInts_ReturnsFalse_SecondTopElementNotInt_1915) {

    stack->pushInt(42);

    stack->pushReal(3.14);

    EXPECT_FALSE(stack->topTwoAreInts());

}



TEST_F(PSStackTest_1915, TopTwoAreInts_ReturnsTrue_AfterRollingStack_1915) {

    stack->pushInt(10);

    stack->pushInt(20);

    stack->pushInt(30);

    stack->roll(3, 1); // Stack now: 20 30 10

    EXPECT_TRUE(stack->topTwoAreInts());

}



TEST_F(PSStackTest_1915, TopTwoAreInts_ReturnsFalse_AfterRollingStackNonConsecutiveIntegers_1915) {

    stack->pushInt(10);

    stack->pushReal(3.14);

    stack->pushInt(20);

    stack->roll(3, 1); // Stack now: 10 20 3.14

    EXPECT_FALSE(stack->topTwoAreInts());

}
