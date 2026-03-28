#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Function.cc"

#include "Error.h"



class PSStackTest_1918 : public ::testing::Test {

protected:

    PSStack stack;

};



TEST_F(PSStackTest_1918, IndexDoesNothingIfOverflow_1918) {

    // Arrange

    EXPECT_CALL(::testing::A<GlobalErrorHandler>(), error(errSyntaxError, -1, "Stack underflow in PostScript function"))

        .Times(0);



    EXPECT_CALL(::testing::A<GlobalErrorHandler>(), error(errSyntaxError, -1, "Stack overflow in PostScript function"))

        .Times(0);



    // Act

    stack.index(1);



    // Assert

    // No assertions needed as we are checking that no errors were called.

}



TEST_F(PSStackTest_1918, IndexHandlesValidIndexing_1918) {

    // Arrange

    stack.pushInt(42);

    stack.pushInt(10);

    

    EXPECT_CALL(::testing::A<GlobalErrorHandler>(), error(errSyntaxError, -1, "Stack underflow in PostScript function"))

        .Times(0);



    EXPECT_CALL(::testing::A<GlobalErrorHandler>(), error(errSyntaxError, -1, "Stack overflow in PostScript function"))

        .Times(0);



    // Act

    stack.index(-1);  // This should move the top of the stack down by one position



    // Assert

    EXPECT_EQ(stack.popInt(), 42);

    EXPECT_EQ(stack.popInt(), 10);

}



TEST_F(PSStackTest_1918, IndexTriggersUnderflowError_1918) {

    // Arrange

    EXPECT_CALL(::testing::A<GlobalErrorHandler>(), error(errSyntaxError, -1, "Stack underflow in PostScript function"))

        .Times(1);



    stack.pushInt(42);

    

    // Act

    stack.index(-99);  // This should trigger an underflow as sp + i + 1 >= psStackSize



    // Assert

    EXPECT_TRUE(stack.empty());

}



TEST_F(PSStackTest_1918, IndexTriggersOverflowError_1918) {

    // Arrange

    EXPECT_CALL(::testing::A<GlobalErrorHandler>(), error(errSyntaxError, -1, "Stack overflow in PostScript function"))

        .Times(1);



    stack.pushInt(42);

    

    // Act

    stack.index(99);  // This should trigger an overflow as sp + i + 1 < 0



    // Assert

    EXPECT_TRUE(stack.empty());

}
