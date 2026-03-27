#include <gtest/gtest.h>

#include "Function.cc"



class PSStackTest_1908 : public ::testing::Test {

protected:

    PSStack stack;

};



TEST_F(PSStackTest_1908, PushInt_NormalOperation_1908) {

    stack.pushInt(42);

    EXPECT_EQ(stack.popInt(), 42);

}



TEST_F(PSStackTest_1908, PushInt_MultipleValues_1908) {

    stack.pushInt(1);

    stack.pushInt(2);

    stack.pushInt(3);



    EXPECT_EQ(stack.popInt(), 3);

    EXPECT_EQ(stack.popInt(), 2);

    EXPECT_EQ(stack.popInt(), 1);

}



TEST_F(PSStackTest_1908, PushInt_BoundaryCondition_EmptyStack_1908) {

    stack.pushInt(42);

    stack.pop();

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1908, PopInt_EmptyStack_Error_1908) {

    EXPECT_THROW(stack.popInt(), std::runtime_error); // Assuming pop from empty stack throws an exception

}



TEST_F(PSStackTest_1908, TopIsInt_AfterPushInt_ReturnsTrue_1908) {

    stack.pushInt(42);

    EXPECT_TRUE(stack.topIsInt());

}



TEST_F(PSStackTest_1908, TopIsInt_EmptyStack_ReturnsFalse_1908) {

    EXPECT_FALSE(stack.topIsInt());

}



TEST_F(PSStackTest_1908, PushInt_TopTwoAreInts_AfterTwoPushes_ReturnsTrue_1908) {

    stack.pushInt(42);

    stack.pushInt(43);

    EXPECT_TRUE(stack.topTwoAreInts());

}



TEST_F(PSStackTest_1908, PushInt_TopTwoAreInts_AfterOnePush_ReturnsFalse_1908) {

    stack.pushInt(42);

    EXPECT_FALSE(stack.topTwoAreInts());

}
