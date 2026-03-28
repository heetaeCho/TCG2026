#include <gtest/gtest.h>

#include "Function.cc"  // Adjust path as necessary



class PSStackTest_1907 : public ::testing::Test {

protected:

    PSStack* ps_stack;



    void SetUp() override {

        ps_stack = new PSStack();

    }



    void TearDown() override {

        delete ps_stack;

    }

};



TEST_F(PSStackTest_1907, PushBool_NormalOperation_1907) {

    ps_stack->pushBool(true);

    EXPECT_EQ(ps_stack->popBool(), true);

}



TEST_F(PSStackTest_1907, PushBool_TopIsInt_AfterPushBool_1907) {

    ps_stack->pushBool(false);

    EXPECT_FALSE(ps_stack->topIsInt());

}



TEST_F(PSStackTest_1907, PushBool_MultipleBooleans_1907) {

    ps_stack->pushBool(true);

    ps_stack->pushBool(false);

    EXPECT_EQ(ps_stack->popBool(), false);

    EXPECT_EQ(ps_stack->popBool(), true);

}



TEST_F(PSStackTest_1907, PushBool_BoundaryCondition_EmptyStack_1907) {

    EXPECT_TRUE(ps_stack->empty());

    ps_stack->pushBool(true);

    EXPECT_FALSE(ps_stack->empty());

}



// Assuming checkOverflow() always returns true for simplicity

TEST_F(PSStackTest_1907, PushBool_ExceptionalCase_StackFull_1907) {

    // Simulate stack being full by pushing 100 elements

    for (int i = 0; i < 100; ++i) {

        ps_stack->pushBool(true);

    }

    EXPECT_FALSE(ps_stack->checkOverflow());  // This line assumes that checkOverflow() can be tested this way

}



TEST_F(PSStackTest_1907, PushBool_VerifyExternalInteractions_1907) {

    // No external interactions in this function, thus no mocks needed.

}
