#include <gtest/gtest.h>

#include "Function.cc" // Assuming this includes the necessary headers



class PSStackTest_1917 : public ::testing::Test {

protected:

    PSStack stack;



    void SetUp() override {

        stack.clear();

    }

};



TEST_F(PSStackTest_1917, TopTwoAreNums_ReturnsFalseWhenEmpty_1917) {

    EXPECT_FALSE(stack.topTwoAreNums());

}



TEST_F(PSStackTest_1917, TopTwoAreNums_ReturnsFalseWhenOneElement_1917) {

    stack.pushInt(1);

    EXPECT_FALSE(stack.topTwoAreNums());

}



TEST_F(PSStackTest_1917, TopTwoAreNums_ReturnsTrueForTwoIntegers_1917) {

    stack.pushInt(1);

    stack.pushInt(2);

    EXPECT_TRUE(stack.topTwoAreNums());

}



TEST_F(PSStackTest_1917, TopTwoAreNums_ReturnsTrueForIntegerAndReal_1917) {

    stack.pushReal(1.5);

    stack.pushInt(2);

    EXPECT_TRUE(stack.topTwoAreNums());

}



TEST_F(PSStackTest_1917, TopTwoAreNums_ReturnsFalseWhenTopIsNotNumber_1917) {

    stack.pushBool(true);

    stack.pushInt(2);

    EXPECT_FALSE(stack.topTwoAreNums());

}



TEST_F(PSStackTest_1917, TopTwoAreNums_ReturnsFalseWhenSecondIsNotNumber_1917) {

    stack.pushInt(1);

    stack.pushOperator();

    EXPECT_FALSE(stack.topTwoAreNums());

}



TEST_F(PSStackTest_1917, TopTwoAreNums_ReturnsTrueForRealNumbers_1917) {

    stack.pushReal(1.5);

    stack.pushReal(2.3);

    EXPECT_TRUE(stack.topTwoAreNums());

}
