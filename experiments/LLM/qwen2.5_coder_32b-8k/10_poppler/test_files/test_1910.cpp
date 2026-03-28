#include <gtest/gtest.h>

#include "Function.cc"



class PSStackTest_1910 : public ::testing::Test {

protected:

    PSStack stack;



    void SetUp() override {

        // Clear the stack before each test

        stack.clear();

    }

};



TEST_F(PSStackTest_1910, PopBool_EmptyStack_ReturnsFalse_1910) {

    EXPECT_FALSE(stack.popBool());

}



TEST_F(PSStackTest_1910, PopBool_TopIsNotBool_ReturnsFalse_1910) {

    stack.pushInt(42);

    EXPECT_FALSE(stack.popBool());

}



TEST_F(PSStackTest_1910, PopBool_NormalOperation_ReturnsCorrectValue_1910) {

    stack.pushBool(true);

    EXPECT_TRUE(stack.popBool());



    stack.pushBool(false);

    EXPECT_FALSE(stack.popBool());

}



TEST_F(PSStackTest_1910, PopBool_MultipleBools_ReturnsInLIFOOrder_1910) {

    stack.pushBool(true);

    stack.pushBool(false);

    EXPECT_FALSE(stack.popBool());

    EXPECT_TRUE(stack.popBool());

}
