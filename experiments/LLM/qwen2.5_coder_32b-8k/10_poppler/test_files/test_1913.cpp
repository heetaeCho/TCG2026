#include <gtest/gtest.h>

#include "Function.cc" // Assuming the header file is included here



class PSStackTest_1913 : public ::testing::Test {

protected:

    PSStack stack;

};



TEST_F(PSStackTest_1913, EmptyOnInitialization_1913) {

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1913, PushIntMakesNotEmpty_1913) {

    stack.pushInt(42);

    EXPECT_FALSE(stack.empty());

}



TEST_F(PSStackTest_1913, PopIntReturnsCorrectValue_1913) {

    stack.pushInt(42);

    int value = stack.popInt();

    EXPECT_EQ(value, 42);

}



TEST_F(PSStackTest_1913, PopIntRestoresEmptyState_1913) {

    stack.pushInt(42);

    stack.popInt();

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1913, PushBoolMakesNotEmpty_1913) {

    stack.pushBool(true);

    EXPECT_FALSE(stack.empty());

}



TEST_F(PSStackTest_1913, PopBoolReturnsCorrectValue_1913) {

    stack.pushBool(true);

    bool value = stack.popBool();

    EXPECT_TRUE(value);

}



TEST_F(PSStackTest_1913, PushRealMakesNotEmpty_1913) {

    stack.pushReal(3.14);

    EXPECT_FALSE(stack.empty());

}



TEST_F(PSStackTest_1913, PopNumReturnsCorrectValueForReal_1913) {

    stack.pushReal(3.14);

    double value = stack.popNum();

    EXPECT_DOUBLE_EQ(value, 3.14);

}



TEST_F(PSStackTest_1913, PushIntAndPopNumReturnsCorrectValue_1913) {

    stack.pushInt(42);

    double value = stack.popNum();

    EXPECT_EQ(value, 42);

}



TEST_F(PSStackTest_1913, PushRealTwiceTopTwoAreNums_1913) {

    stack.pushReal(3.14);

    stack.pushReal(2.71);

    EXPECT_TRUE(stack.topTwoAreNums());

}



TEST_F(PSStackTest_1913, PushIntAndRealTopTwoAreNotBothInts_1913) {

    stack.pushInt(42);

    stack.pushReal(3.14);

    EXPECT_FALSE(stack.topTwoAreInts());

}



TEST_F(PSStackTest_1913, PushIntTwiceTopTwoAreInts_1913) {

    stack.pushInt(42);

    stack.pushInt(84);

    EXPECT_TRUE(stack.topTwoAreInts());

}



TEST_F(PSStackTest_1913, PushRealTopIsReal_1913) {

    stack.pushReal(3.14);

    EXPECT_TRUE(stack.topIsReal());

}



TEST_F(PSStackTest_1913, PushIntTopIsNotReal_1913) {

    stack.pushInt(42);

    EXPECT_FALSE(stack.topIsReal());

}



TEST_F(PSStackTest_1913, PushIntTopIsInt_1913) {

    stack.pushInt(42);

    EXPECT_TRUE(stack.topIsInt());

}



TEST_F(PSStackTest_1913, PushRealTopIsNotInt_1913) {

    stack.pushReal(3.14);

    EXPECT_FALSE(stack.topIsInt());

}



TEST_F(PSStackTest_1913, ClearEmptiesStack_1913) {

    stack.pushInt(42);

    stack.clear();

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1913, PopOnEmptyThrowsException_1913) {

    EXPECT_THROW(stack.popInt(), std::exception); // Assuming an exception is thrown on underflow

}



TEST_F(PSStackTest_1913, PushBeyondCapacityThrowsException_1913) {

    for (int i = 0; i < ::psStackSize; ++i) {

        stack.pushInt(i);

    }

    EXPECT_THROW(stack.pushInt(::psStackSize + 1), std::exception); // Assuming an exception is thrown on overflow

}
