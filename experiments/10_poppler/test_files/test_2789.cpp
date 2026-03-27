#include <gtest/gtest.h>

#include "Function.cc" // Assuming the header file includes necessary definitions



class PSStackTest_2789 : public ::testing::Test {

protected:

    PSStack* stack;



    void SetUp() override {

        stack = new PSStack();

    }



    void TearDown() override {

        delete stack;

    }

};



TEST_F(PSStackTest_2789, PushPopBool_2789) {

    stack->pushBool(true);

    EXPECT_TRUE(stack->popBool());



    stack->pushBool(false);

    EXPECT_FALSE(stack->popBool());

}



TEST_F(PSStackTest_2789, PushPopInt_2789) {

    stack->pushInt(42);

    EXPECT_EQ(42, stack->popInt());



    stack->pushInt(-10);

    EXPECT_EQ(-10, stack->popInt());

}



TEST_F(PSStackTest_2789, PushPopReal_2789) {

    stack->pushReal(3.14);

    EXPECT_DOUBLE_EQ(3.14, stack->popNum());



    stack->pushReal(-2.71);

    EXPECT_DOUBLE_EQ(-2.71, stack->popNum());

}



TEST_F(PSStackTest_2789, PushPopMixed_2789) {

    stack->pushBool(true);

    stack->pushInt(42);

    stack->pushReal(3.14);



    EXPECT_DOUBLE_EQ(3.14, stack->popNum());

    EXPECT_EQ(42, stack->popInt());

    EXPECT_TRUE(stack->popBool());

}



TEST_F(PSStackTest_2789, EmptyCheck_2789) {

    EXPECT_TRUE(stack->empty());



    stack->pushBool(true);

    EXPECT_FALSE(stack->empty());



    stack->popBool();

    EXPECT_TRUE(stack->empty());

}



TEST_F(PSStackTest_2789, TopIsInt_2789) {

    stack->pushInt(10);

    EXPECT_TRUE(stack->topIsInt());



    stack->pushReal(3.14);

    EXPECT_FALSE(stack->topIsInt());



    stack->popNum();

    EXPECT_TRUE(stack->topIsInt());

}



TEST_F(PSStackTest_2789, TopTwoAreInts_2789) {

    stack->pushInt(10);

    stack->pushInt(20);

    EXPECT_TRUE(stack->topTwoAreInts());



    stack->pushReal(3.14);

    EXPECT_FALSE(stack->topTwoAreInts());

}



TEST_F(PSStackTest_2789, TopIsReal_2789) {

    stack->pushReal(3.14);

    EXPECT_TRUE(stack->topIsReal());



    stack->pushInt(10);

    EXPECT_FALSE(stack->topIsReal());



    stack->popInt();

    EXPECT_TRUE(stack->topIsReal());

}



TEST_F(PSStackTest_2789, TopTwoAreNums_2789) {

    stack->pushInt(10);

    stack->pushReal(3.14);

    EXPECT_TRUE(stack->topTwoAreNums());



    stack->pushBool(true);

    EXPECT_FALSE(stack->topTwoAreNums());

}



TEST_F(PSStackTest_2789, IndexAccess_2789) {

    stack->pushInt(10);

    stack->pushReal(3.14);

    stack->pushBool(true);



    stack->index(0);

    EXPECT_TRUE(stack->popBool());



    stack->index(0);

    EXPECT_DOUBLE_EQ(3.14, stack->popNum());



    stack->index(0);

    EXPECT_EQ(10, stack->popInt());

}



TEST_F(PSStackTest_2789, RollOperation_2789) {

    stack->pushInt(1);

    stack->pushInt(2);

    stack->pushInt(3);



    stack->roll(3, 1); // Rotate once to the left

    EXPECT_EQ(1, stack->popInt());

    EXPECT_EQ(3, stack->popInt());

    EXPECT_EQ(2, stack->popInt());



    stack->pushInt(1);

    stack->pushInt(2);

    stack->pushInt(3);



    stack->roll(3, -1); // Rotate once to the right

    EXPECT_EQ(2, stack->popInt());

    EXPECT_EQ(1, stack->popInt());

    EXPECT_EQ(3, stack->popInt());

}



TEST_F(PSStackTest_2789, CopyOperation_2789) {

    stack->pushInt(1);

    stack->pushInt(2);



    stack->copy(2); // Duplicate the top two elements

    EXPECT_EQ(2, stack->popInt());

    EXPECT_EQ(1, stack->popInt());

    EXPECT_EQ(2, stack->popInt());

    EXPECT_EQ(1, stack->popInt());

}



TEST_F(PSStackTest_2789, ClearOperation_2789) {

    stack->pushBool(true);

    stack->pushInt(42);



    stack->clear();

    EXPECT_TRUE(stack->empty());

}
