#include <gtest/gtest.h>



class PSStackTest_1914 : public ::testing::Test {

protected:

    PSStack stack;



    void SetUp() override {

        // Clear the stack before each test

        stack.clear();

    }

};



TEST_F(PSStackTest_1914, TopIsInt_ReturnsFalseForEmptyStack_1914) {

    EXPECT_FALSE(stack.topIsInt());

}



TEST_F(PSStackTest_1914, TopIsInt_ReturnsTrueAfterPushingInt_1914) {

    stack.pushInt(42);

    EXPECT_TRUE(stack.topIsInt());

}



TEST_F(PSStackTest_1914, TopIsInt_ReturnsFalseAfterPushingBool_1914) {

    stack.pushBool(true);

    EXPECT_FALSE(stack.topIsInt());

}



TEST_F(PSStackTest_1914, TopIsInt_ReturnsFalseAfterPushingReal_1914) {

    stack.pushReal(3.14);

    EXPECT_FALSE(stack.topIsInt());

}



TEST_F(PSStackTest_1914, TopIsInt_ReturnsTrueForMultipleInts_1914) {

    stack.pushInt(10);

    stack.pushInt(20);

    EXPECT_TRUE(stack.topIsInt());

    stack.pop();

    EXPECT_TRUE(stack.topIsInt());

}



TEST_F(PSStackTest_1914, TopIsInt_ReturnsFalseAfterPoppingLastInt_1914) {

    stack.pushInt(5);

    stack.pop();

    EXPECT_FALSE(stack.topIsInt());

}
